/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#include "LineFormat.h"
#include "CollisionManager.h"
#include "SceneManager.h"


using namespace rendering::formats;
using namespace rendering::models;


// Parameters used for giving unqiue names for rays
static int no = 65;
static std::string radius_name = "radius_ ";


rendering::formats::LineFormat::LineFormat() {}

rendering::formats::LineFormat::~LineFormat() {}

// Based on the vertex1 and vertex2, this constructor computes line slope and intercept
rendering::formats::LineFormat::LineFormat(
	VertexFormat* vertex1, VertexFormat* vertex2)
{
	this->vertex1 = vertex1;
	this->vertex2 = vertex2;

	this->slope = (vertex1->get_Y() - vertex2->get_Y()) / 
		(vertex1->get_X() - vertex2->get_X());
	this->y_intercept = -(this->slope * vertex1->get_X()) + vertex1->get_Y();

	this->name = "";
}


float rendering::formats::LineFormat::getDistanceBetweenTwoPoints(
	VertexFormat vertex1, VertexFormat vertex2)
{
	return sqrtf(pow(vertex2.get_X() - vertex1.get_X(), 2) +
		powf(vertex2.get_Y() - vertex1.get_Y(), 2));
}

// Check is this line contains a vertex given as parameter
// If the distance between a point and line limits (summed up) is equal to distance between line limits,
//then the line contains the point
bool rendering::formats::LineFormat::isLineContainingPoint(VertexFormat vertex)
{

	float point1_point2 = getDistanceBetweenTwoPoints(*this->vertex1, *this->vertex2);
	float point1_point = getDistanceBetweenTwoPoints(*this->vertex1, vertex);
	float point2_point = getDistanceBetweenTwoPoints(*this->vertex2, vertex);

	float result = point1_point2 - (point1_point + point2_point);

	if (abs(result) < 0.00001)
		return true;

	return false;
}


void rendering::formats::LineFormat::drawLineReflection(
	LineFormat incident_line, LineFormat surface_line,
	VertexFormat incident_surface_intersection_point, 
	long double angle, glm::vec4 color)
{
	// create a radius to be drawn
	RadiusDraw* radius = new RadiusDraw(this->vertex1, &incident_surface_intersection_point);
	// set radius length for the reflected line
	radius->length = getDistanceBetweenTwoPoints(
		*incident_line.vertex1, 
		incident_surface_intersection_point);

	// set the angle
	if (managers::CollisionManager::is_light_directly_from_source)
		radius->rotate_Z = managers::CollisionManager::getLightSourceRayAngle();
	else
		radius->rotate_Z = angle;

	// set color
	radius->vertex1->setColor(color);
	radius->vertex2->setColor(color);

	// set translation
	radius->translate = glm::vec3(this->vertex1->get_X(), this->vertex1->get_Y(), 0.0);

	// draw the line
	no++;
	radius_name[7] = no;
	managers::SceneManager::scene_manager->getModelManager()->createModel(radius, radius_name,
		managers::SceneManager::scene_manager->getShaderManager()->getProgram("colorShader"));

	// add ray name to a vector. Helpful for restoring the window
	managers::CollisionManager::scene_object_rays_names.push_back(radius_name);
}


// Compute reflected line equation and specific data
void rendering::formats::LineFormat::computeLineReflection(LineFormat line)
{
	// Get incident line intersection point on the surface line
	VertexFormat incident_surface_intersection_point = 
		VertexFormat(glm::vec4(getLineIntersectionPoint_X(line), 
			getLineIntersectionPoint_Y(line), 0.0, 1.0));

	if (line.isLineContainingPoint(incident_surface_intersection_point))
	{	
		// Get the reflected line equation
		LineFormat* line_reflected = getLineReflection(*this, line, incident_surface_intersection_point);

		// Compute angle of reflection
		long double angle = atan2f(
			managers::CollisionManager::incident_line->vertex2->get_Y() - 
			managers::CollisionManager::incident_line->vertex1->get_Y(),
			managers::CollisionManager::incident_line->vertex2->get_X() - 
			managers::CollisionManager::incident_line->vertex1->get_X());
		
		// Draw the line on the screen
		drawLineReflection(*this, line, incident_surface_intersection_point, angle, 
			managers::CollisionManager::incident_line->vertex1->getColor());

		// Compute the color for the next incident line, which now is the reflected line
		glm::vec4 color = glm::vec4(
			(line.vertex1->getColor().x + 
				managers::CollisionManager::incident_line->vertex1->getColor().x) / 2.0,
			(line.vertex1->getColor().y + 
				managers::CollisionManager::incident_line->vertex1->getColor().y) / 2.0,
			(line.vertex1->getColor().z + 
				managers::CollisionManager::incident_line->vertex1->getColor().z) / 2.0, 1.0);

		// Set the color
		line_reflected->vertex1->setColor(color);
		line_reflected->vertex2->setColor(color);

		// Set the next incident line as the current reflected line
		managers::CollisionManager::incident_line = new LineFormat(line_reflected->vertex1, line_reflected->vertex2);
	}
}

// Check if a line is intersecting another line testing: intersection point 
//and the right direction of the line. As we have line equation, we must ensure 
//that we do not go in the opposite direction
bool rendering::formats::LineFormat::isLineInteresectingLine(LineFormat line)
{

	if (slope == line.slope)
		return 0;

	VertexFormat incident_surface_intersection_point = 
		VertexFormat(glm::vec4(getLineIntersectionPoint_X(line), 
			getLineIntersectionPoint_Y(line), 0.0, 1.0));

	if (line.isLineContainingPoint(incident_surface_intersection_point))
	{
		LineFormat* line_reflected = getLineReflection(*this, line, incident_surface_intersection_point);

		long double angle = atan2f(
			managers::CollisionManager::incident_line->vertex2->get_Y() - 
			managers::CollisionManager::incident_line->vertex1->get_Y(),
			managers::CollisionManager::incident_line->vertex2->get_X() - 
			managers::CollisionManager::incident_line->vertex1->get_X());

		// check if line goes in the right direction
		if (isValidReflection(*this, line, incident_surface_intersection_point, angle))
			return 1;
	}

	return 0;
}

float rendering::formats::LineFormat::getLineIntersectionPoint_X(LineFormat line)
{
	float x;

	if (line.vertex1->get_X() == line.vertex2->get_X() )
	{
		x = line.vertex1->get_X();
	}
	else
		x = (line.y_intercept - y_intercept) / (slope - line.slope);

	return x;
}


float rendering::formats::LineFormat::getLineIntersectionPoint_Y(LineFormat line)
{
	float x = getLineIntersectionPoint_X(line);
	float y;

	if (vertex1->get_X() == vertex2->get_X())
	{
		float y = (line.slope * x + line.y_intercept);
		
	}
	else if (line.vertex1->get_X() == line.vertex2->get_X())
	{
		y = (slope * x + y_intercept);
	}
	else
		y = (slope * x + y_intercept);

	return y;
}

// A reflection is valid if the reflection angle is correct and also if the direction
//of the reflected line is correct
bool rendering::formats::LineFormat::isValidReflection(
	LineFormat incident_line, LineFormat line_surface, 
	VertexFormat incident_surface_intersection_point, long double angle)
{
	LineFormat* line_reflected = getLineReflection(
		incident_line, line_surface, incident_surface_intersection_point);

	// get the reflection angle
	// here we also do a translation to the world origin point
	long double anglee = atan2(
		incident_surface_intersection_point.get_Y() - incident_line.vertex1->get_Y(), 
		incident_surface_intersection_point.get_X() - incident_line.vertex1->get_X());

	// check the angle in order to draw the incident line in the right direction
	if (managers::CollisionManager::is_light_directly_from_source)
	{
		// check if the angle of incident line is between 0 - 180 degreees
		if (managers::CollisionManager::getLightSourceRayAngle() <= 3.14159265 && 
			atan2f(incident_surface_intersection_point.get_Y(), incident_surface_intersection_point.get_X()) <= 3.14159265
			&& managers::CollisionManager::getLightSourceRayAngle() >= 0.0 && 
			atan2f(incident_surface_intersection_point.get_Y(), incident_surface_intersection_point.get_X()) >= 0.0)
		{
			return true;
		}
		// check if the angle of incident line is between 181 - 360 degreees
		else if (managers::CollisionManager::getLightSourceRayAngle() <= 6.28318531 && 
			atan2f(incident_surface_intersection_point.get_Y(), incident_surface_intersection_point.get_X()) >= -3.14159265
			&& managers::CollisionManager::getLightSourceRayAngle() > 3.14159265 && 
			atan2f(incident_surface_intersection_point.get_Y(), incident_surface_intersection_point.get_X()) < 0.0)
		{
			return true;
		}
	}

	if (abs(anglee - angle) < 0.00001)
		return true;

	return false;

}


// Compute reflected line equation
rendering::formats::LineFormat* rendering::formats::LineFormat::getLineReflection(LineFormat incident_line,
	LineFormat surface_line, VertexFormat incident_surface_intersection_point)
{
	float d_x = surface_line.vertex2->get_X() - surface_line.vertex1->get_X();
	float d_y = surface_line.vertex2->get_Y() - surface_line.vertex1->get_Y();

	float magnitude = sqrtf(powf(d_y, 2) + powf(-d_x, 2));

	// Compute the normal line to the surface
	float normal_vector_x = d_y / magnitude;
	float normal_vector_y = -d_x / magnitude;

	// Compute incident line vector
	float incident_vector_x = incident_line.vertex1->get_X() - incident_surface_intersection_point.get_X();
	float incident_vector_y = incident_line.vertex1->get_Y() - incident_surface_intersection_point.get_Y();

	// Compute the vector for the reflected line
	float normal_incident_scalar_product = 
		normal_vector_x * incident_vector_x + normal_vector_y * incident_vector_y;
	normal_incident_scalar_product *= 2;

	float reflection_x = normal_incident_scalar_product * normal_vector_x;
	float reflection_y = normal_incident_scalar_product * normal_vector_y;

	reflection_x = -(reflection_x - incident_vector_x);
	reflection_y = -(reflection_y - incident_vector_y);

	// Get the reflected line equation and data
	LineFormat* line_reflection = new LineFormat(
		new VertexFormat(
			glm::vec4(incident_surface_intersection_point.get_X(), 
				incident_surface_intersection_point.get_Y(), 0.0, 1.0)),
		new VertexFormat(
			glm::vec4(incident_surface_intersection_point.get_X() - reflection_x, 
				incident_surface_intersection_point.get_Y() - reflection_y, 0.0, 1.0)));

	return line_reflection;
}


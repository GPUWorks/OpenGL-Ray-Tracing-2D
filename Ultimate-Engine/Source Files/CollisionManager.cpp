/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#include "CollisionManager.h"
#include "VertexFormat.h"


// Light source ray orientation (from 0 to 59)
int managers::CollisionManager::light_source_point = 0;
// True if was chosen another ray
bool managers::CollisionManager::light_source_point_changed = 1;
// Vector that keeps all collision objects
std::vector<rendering::formats::LineFormat*> managers::CollisionManager::scene_object_lines;
// Vector that keeps rays drawn on screen
std::vector<std::string> managers::CollisionManager::scene_object_rays_names;
// Incident line (always updated with the reflected line)
rendering::formats::LineFormat* managers::CollisionManager::incident_line;
// True if the incident line is from light source
bool managers::CollisionManager::is_light_directly_from_source;
// True if the camera was hit
bool managers::CollisionManager::is_camera_hit = false;
// While is_radius_drawing = true stop processing next line reflections
bool managers::CollisionManager::is_radius_drawing = false;
// True if space key was pressed
bool managers::CollisionManager::space_key_pressed = false;
// Max number of reflections
int managers::CollisionManager::max_no_of_rays = 20;

// Reset the scene
void managers::CollisionManager::reset()
{
	managers::CollisionManager::is_camera_hit = false;
	managers::CollisionManager::light_source_point_changed = 1;
	managers::CollisionManager::is_radius_drawing = false;
	managers::CollisionManager::space_key_pressed = false;
}

// Compute the incident line equation
void managers::CollisionManager::getLightSourceStartCoordinates()
{
	int light_source_rays_no = 60;
	float light_source_radius_length = 0.1f;
	
	float theta;

	rendering::formats::VertexFormat* vertex1 = new rendering::formats::VertexFormat();
	rendering::formats::VertexFormat* vertex2 = new rendering::formats::VertexFormat();

	glm::vec4 vertex_coordinates(0.0f, 0.0f, 0.0f, 1.0f);
	glm::vec4 vertex_color(1.0f, 1.0f, 0.0f, 1.0f);

	/**
	 * Compute coordinates for the first line point between two light_source_rays
	 **/
	theta = 2.0f * 3.1415926f * float(CollisionManager::light_source_point) / 
		float(light_source_rays_no);
	vertex_coordinates.x = (light_source_radius_length * cosf(theta)) / 2.0f;
	vertex_coordinates.y = (light_source_radius_length * sinf(theta)) / 2.0f;
	vertex_coordinates.z = 0.0f;
	vertex_coordinates.w = 1.0f;

	vertex1->setPosition(vertex_coordinates);
	vertex1->setColor(vertex_color);


	/**
	* Compute coordinates for the second line point between two light_source_rays
	**/
	if (CollisionManager::light_source_point + 1 == 60)
	{
		theta = 2.0f * 3.1415926f * float(0) / float(light_source_rays_no);
		vertex_coordinates.x = (light_source_radius_length * cosf(theta)) / 2;
		vertex_coordinates.y = (light_source_radius_length * sinf(theta)) / 2;
		vertex_coordinates.z = 0.0f;
		vertex_coordinates.w = 1.0f;
	}
	else
	{
		theta = 2.0f * 3.1415926f * float(CollisionManager::light_source_point + 1) / 
			float(light_source_rays_no);
		vertex_coordinates.x = (light_source_radius_length * cosf(theta)) / 2.0f;
		vertex_coordinates.y = (light_source_radius_length * sinf(theta)) / 2.0f;
		vertex_coordinates.z = 0.0f;
		vertex_coordinates.w = 1.0f;
	}

	vertex2->setPosition(vertex_coordinates);
	vertex2->setColor(vertex_color);
	

	rendering::formats::LineFormat* light_source_line = new rendering::formats::LineFormat(vertex1, vertex2);
	light_source_line->slope = -1 / light_source_line->slope;
	light_source_line->y_intercept = -(light_source_line->slope * light_source_line->vertex1->get_X()) + 
		light_source_line->vertex1->get_Y();

	// Set light source line as incident line
	managers::CollisionManager::incident_line = light_source_line;

	managers::CollisionManager::is_light_directly_from_source = true;
}


// Get the angle of the incident line comming from light source (in world space)
long double managers::CollisionManager::getLightSourceRayAngle()
{
	int light_source_rays_no = 60;

	// Angle of the line to be drawn (in world coordinates - radians)
	long double angle = 2.0f * 3.14159265f * 
		(long double)(managers::CollisionManager::light_source_point) / 
		(long double)(light_source_rays_no);

	/**
	* Because ray of light is starting from the middle of light_source_line,
	*we have to compute the angle for the middle point of line;
	**/
	long double element = 3.14159265f * (long double)(1) / 
		(long double)(light_source_rays_no);

	angle += element;


	return angle;
}

// Function that adds world space collision lines
void managers::CollisionManager::addSceneLine(
	rendering::formats::VertexFormat* vertex1, 
	rendering::formats::VertexFormat* vertex2)
{
	scene_object_lines.push_back(new rendering::formats::LineFormat(vertex1, vertex2));
}

// Add camera in the right-up corner (black triangle)
void managers::CollisionManager::addCamera(
	rendering::formats::VertexFormat* vertex1, 
	rendering::formats::VertexFormat* vertex2)
{
	rendering::formats::LineFormat* line = new rendering::formats::LineFormat(vertex1, vertex2);

	line->name = "camera";

	scene_object_lines.push_back(line);
}

// Function that draws a reflection ray if certain conditions are met
void managers::CollisionManager::drawRay()
{
	// Compute the next reflection line if the camera and max number of rays was not hit
	if (!managers::CollisionManager::is_camera_hit && 
		((int)managers::CollisionManager::scene_object_rays_names.size() < 
			managers::CollisionManager::max_no_of_rays))
	{
		managers::CollisionManager::checkForRadiusCollision();
	}
}


// Get the next reflection line
void managers::CollisionManager::checkForRadiusCollision()
{
	// If the ligth source ray was changed, get the new data for the incident line
	if (managers::CollisionManager::light_source_point_changed)
	{
		managers::CollisionManager::getLightSourceStartCoordinates();
		managers::CollisionManager::light_source_point_changed = 0;
	}

	// If a ray is currently drawing, don't check for another reflection line
	if (managers::CollisionManager::is_radius_drawing)
		return;

	float min_distance = (float)INT32_MAX;
	int idx_of_chosen_element = 0;
	int element_index = 0;

	// Get the surface line based on distance and intersection
	for (auto line : managers::CollisionManager::scene_object_lines)
	{
		if (managers::CollisionManager::incident_line->isLineInteresectingLine(*line))
		{
			float line_interesection_point_x = 
				managers::CollisionManager::incident_line->getLineIntersectionPoint_X(*line);
			float line_interesection_point_y = 
				managers::CollisionManager::incident_line->getLineIntersectionPoint_Y(*line);

			float distance = line->getDistanceBetweenTwoPoints(
				rendering::formats::VertexFormat(
					glm::vec4(line_interesection_point_x, line_interesection_point_y, 0.0, 1.0)),
				rendering::formats::VertexFormat(
					glm::vec4(managers::CollisionManager::incident_line->vertex1->get_X(), 
						managers::CollisionManager::incident_line->vertex1->get_Y(), 0.0, 1.0)));


			if (distance < min_distance)
			{
				min_distance = distance;
				idx_of_chosen_element = element_index;
			}
		}

		element_index++;
	}

	// Compute the incident line reflection with the line surface previously found, and then draw it
	managers::CollisionManager::incident_line->computeLineReflection(
		*managers::CollisionManager::scene_object_lines.at(idx_of_chosen_element));

	// Check if camera was hit
	if(managers::CollisionManager::scene_object_lines.at(idx_of_chosen_element)->name == "camera")
		managers::CollisionManager::is_camera_hit = true;


	if (is_camera_hit)
	{
		printf("\n\nCamera was reached\n\nPush: 'R' to reset the scene\n\n");
		return;
	}

	if ((int)managers::CollisionManager::scene_object_rays_names.size() >= managers::CollisionManager::max_no_of_rays)
	{
		printf("\n\n%d-rays limit hit. Camera was not reached\n\nPush: 'R' to reset the scene\n\n", 
			managers::CollisionManager::max_no_of_rays);
		return;
	}
}

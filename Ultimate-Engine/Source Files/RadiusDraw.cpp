/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#include "RadiusDraw.h"
#include "ModelManager.h"
#include "WindowsManager.h"
#include <glm/gtc/type_ptr.hpp>

using namespace rendering;
using namespace models;
using namespace formats;
using namespace managers;


float RadiusDraw::draw_speed = 1.0f;

RadiusDraw::RadiusDraw(rendering::formats::VertexFormat* vertex1, rendering::formats::VertexFormat* vertex2)
{
	this->vertex1 = vertex1;
	this->vertex2 = vertex2;

	this->partial_length = 1.0f;

	managers::CollisionManager::is_radius_drawing = true;

	this->is_draw_finished = false;
}

RadiusDraw::~RadiusDraw() { }

void RadiusDraw::create()
{
	this->vao = generateVAO();
	this->vbos.push_back(generateVBO());
	this->ibos.push_back(generateIBO());

	bindShaderInputData();
}

GLuint RadiusDraw::generateVBO()
{
	GLuint vbo;

	std::vector<VertexFormat> vertices;

	vertices.push_back(VertexFormat(glm::vec4(0.0, -0.01, 0.0, 1.0), vertex1->getColor()));
	vertices.push_back(VertexFormat(glm::vec4(0.0, 0.01, 0.0, 1.0), vertex1->getColor()));
	vertices.push_back(VertexFormat(glm::vec4(0.0001, 0.01, 0.0, 1.0), vertex1->getColor()));
	vertices.push_back(VertexFormat(glm::vec4(0.0001, -0.01, 0.0, 1.0), vertex1->getColor()));

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, &vertices[0], GL_STATIC_DRAW);

	return vbo;
}

GLuint RadiusDraw::generateIBO()
{
	GLuint ibo;

	std::vector<GLuint> indexes;

	indexes.push_back(0);
	indexes.push_back(1);
	indexes.push_back(2);
	indexes.push_back(2);
	indexes.push_back(3);
	indexes.push_back(0);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 6, &indexes[0], GL_STATIC_DRAW);

	return ibo;
}

GLuint RadiusDraw::generateVAO()
{
	GLuint vao;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	return vao;
}

void RadiusDraw::bindShaderInputData()
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));

	glBindVertexArray(0);
}


void RadiusDraw::setModelMatrix()
{
	glm::mat4 model_matrix1 = glm::mat4(1);
	model_matrix1 *= ModelManager::translate(translate.x, translate.y, 0.0);
	model_matrix1 *= ModelManager::rotateZ((float)rotate_Z);
	model_matrix1 *= ModelManager::scaleX(this->partial_length);

	if (managers::CollisionManager::is_light_directly_from_source)
	{
		this->partial_length = 300.0f;
	}


	if (((this->length * 10000) - (100.0f * this->draw_speed)) > this->partial_length)
		this->partial_length += (100.0f * this->draw_speed);
	else if (!this->is_draw_finished) {
		this->partial_length += (this->length * 10000) - this->partial_length;
		this->is_draw_finished = true;
		managers::CollisionManager::is_radius_drawing = false;
	}
	

	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, false, glm::value_ptr(model_matrix1));
}

void RadiusDraw::update()
{

}

void RadiusDraw::draw()
{
	glUseProgram(program);
	glBindVertexArray(vao);
	setModelMatrix();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


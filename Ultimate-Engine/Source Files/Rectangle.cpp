/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#include "Rectangle.h"
#include "ModelManager.h"
#include <glm/gtc/type_ptr.hpp>

using namespace rendering;
using namespace models;
using namespace formats;
using namespace managers;

Rectangle::Rectangle() { }

Rectangle::~Rectangle() { }

void Rectangle::create()
{
	this->vao = generateVAO();
	this->vbos.push_back(generateVBO());
	this->ibos.push_back(generateIBO());

	bindShaderInputData();
}

GLuint Rectangle::generateVBO()
{
	GLuint vbo;

	std::vector<VertexFormat> vertices;

	float scale = 1.3f;
	float x_translate = -0.15f;
	float y_translate = -0.75f;

	VertexFormat* rectangle_left_up = new VertexFormat(glm::vec4(-0.15 * scale + x_translate, 0.1 * scale + y_translate, 0.0, 1), glm::vec4(0.4, 0.2, 0.4, 1));
	VertexFormat* rectangle_left_down = new VertexFormat(glm::vec4(-0.15 * scale + x_translate, -0.1 * scale + y_translate, 0.0, 1), glm::vec4(0.4, 0.2, 0.4, 1));
	VertexFormat* rectangle_right_down = new VertexFormat(glm::vec4(0.15 * scale + x_translate, -0.1 * scale + y_translate, 0.0, 1), glm::vec4(0.4, 0.2, 0.4, 1));
	VertexFormat* rectangle_right_up = new VertexFormat(glm::vec4(0.15 * scale + x_translate, 0.1 * scale + y_translate, 0.0, 1), glm::vec4(0.4, 0.2, 0.4, 1));


	vertices.push_back(*rectangle_left_up);
	vertices.push_back(*rectangle_left_down);
	vertices.push_back(*rectangle_right_down);
	vertices.push_back(*rectangle_right_up);


	managers::CollisionManager::addSceneLine(rectangle_left_up, rectangle_left_down);
	managers::CollisionManager::addSceneLine(rectangle_left_down, rectangle_right_down);
	managers::CollisionManager::addSceneLine(rectangle_right_down, rectangle_right_up);
	managers::CollisionManager::addSceneLine(rectangle_right_up, rectangle_left_up);



	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, &vertices[0], GL_STATIC_DRAW);

	return vbo;
}

GLuint Rectangle::generateIBO()
{
	GLuint ibo;

	std::vector<GLuint> indexes;

	indexes.push_back(0);
	indexes.push_back(1);
	indexes.push_back(2);
	indexes.push_back(3);
	indexes.push_back(0);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 5, &indexes[0], GL_STATIC_DRAW);

	return ibo;
}

GLuint Rectangle::generateVAO()
{
	GLuint vao;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	return vao;
}

void Rectangle::bindShaderInputData()
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));

	glBindVertexArray(0);
}

void Rectangle::setModelMatrix()
{
	glm::mat4 model_matrix1 = glm::mat4(1);
	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, false, glm::value_ptr(model_matrix1));
}

void Rectangle::update()
{

}

void Rectangle::draw()
{
	glUseProgram(program);
	glBindVertexArray(vao);
	setModelMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, 0);
	//glDrawRangeElements(GL_LINE_STRIP, 0, 3, 6, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
}

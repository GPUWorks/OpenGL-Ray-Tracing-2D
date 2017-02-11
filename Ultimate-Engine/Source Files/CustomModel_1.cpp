/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#include "CustomModel_1.h"
#include "ModelManager.h"
#include <glm/gtc/type_ptr.hpp>

using namespace rendering;
using namespace models;
using namespace formats;
using namespace managers;

CustomModel_1::CustomModel_1() { }

CustomModel_1::~CustomModel_1() { }

void CustomModel_1::create()
{
	this->vao = generateVAO();
	this->vbos.push_back(generateVBO());
	this->ibos.push_back(generateIBO());

	bindShaderInputData();
}

GLuint CustomModel_1::generateVBO()
{
	GLuint vbo;

	std::vector<VertexFormat> vertices;

	float y_translate = 0.85f;

	VertexFormat* rectangle_right_down = new VertexFormat(glm::vec4(0.1, 0.1 + y_translate, 0.0, 1), glm::vec4(0.4, 0, 0.1, 1));
	VertexFormat* rectangle_right_up = new VertexFormat(glm::vec4(0.1, 0.15 + y_translate, 0.0, 1), glm::vec4(0.4, 0, 0.1, 1));
	VertexFormat* rectangle_left_up = new VertexFormat(glm::vec4(-0.3, 0.15 + y_translate, 0.0, 1), glm::vec4(0.4, 0, 0.1, 1));
	VertexFormat* rectangle_left_down = new VertexFormat(glm::vec4(-0.3, 0.1 + y_translate, 0.0, 1), glm::vec4(0.4, 0, 0.1, 1));
	
	VertexFormat* triangle_left_down = new VertexFormat(glm::vec4(-0.3, -0.35 + y_translate, 0.0, 1), glm::vec4(0.4, 0, 0.1, 1));
	VertexFormat* triangle_right_up = new VertexFormat(glm::vec4(-0.2, 0.1 + y_translate, 0.0, 1), glm::vec4(0.4, 0, 0.1, 1));

	vertices.push_back(*rectangle_right_down);
	vertices.push_back(*rectangle_right_up);
	vertices.push_back(*rectangle_left_up);
	vertices.push_back(*rectangle_left_down);

	vertices.push_back(*triangle_left_down);
	vertices.push_back(*triangle_right_up);


	managers::CollisionManager::addSceneLine(rectangle_right_down, rectangle_right_up);
	managers::CollisionManager::addSceneLine(rectangle_right_up, rectangle_left_up);
	managers::CollisionManager::addSceneLine(rectangle_left_up, rectangle_left_down);
	managers::CollisionManager::addSceneLine(rectangle_left_down, rectangle_right_down);
	managers::CollisionManager::addSceneLine(rectangle_left_down, triangle_left_down);
	managers::CollisionManager::addSceneLine(triangle_left_down, triangle_right_up);


	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 6, &vertices[0], GL_STATIC_DRAW);

	return vbo;
}

GLuint CustomModel_1::generateIBO()
{
	GLuint ibo;

	std::vector<GLuint> indexes;

	indexes.push_back(0);
	indexes.push_back(1);
	indexes.push_back(2);
	indexes.push_back(2);
	indexes.push_back(3);
	indexes.push_back(0);
	indexes.push_back(3);
	indexes.push_back(4);
	indexes.push_back(5);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 9, &indexes[0], GL_STATIC_DRAW);

	return ibo;
}

GLuint CustomModel_1::generateVAO()
{
	GLuint vao;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	return vao;
}

void CustomModel_1::bindShaderInputData()
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));

	glBindVertexArray(0);
}

void CustomModel_1::setModelMatrix()
{
	glm::mat4 model_matrix1 = glm::mat4(1);
	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, false, glm::value_ptr(model_matrix1));
}

void CustomModel_1::update()
{
	
}

void CustomModel_1::draw()
{
	glUseProgram(program);
	glBindVertexArray(vao);
	setModelMatrix();
	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

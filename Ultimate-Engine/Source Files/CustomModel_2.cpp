/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#include "CustomModel_2.h"
#include "ModelManager.h"
#include <glm/gtc/type_ptr.hpp>

using namespace rendering;
using namespace models;
using namespace formats;
using namespace managers;

CustomModel_2::CustomModel_2() { }

CustomModel_2::~CustomModel_2() { }

void CustomModel_2::create()
{
	this->vao = generateVAO();
	this->vbos.push_back(generateVBO());
	this->ibos.push_back(generateIBO());

	bindShaderInputData();
}

GLuint CustomModel_2::generateVBO()
{
	GLuint vbo;

	std::vector<VertexFormat> vertices;

	float x_translate = -0.54f;

	

	VertexFormat* triangle_1_right_down = new VertexFormat(glm::vec4(0.1 + x_translate, -0.1, 0.0, 1), glm::vec4(0.4, 0.7, 0.2, 1));
	VertexFormat* triangle_1_right_up = new VertexFormat(glm::vec4(0.1 + x_translate, 0.15, 0.0, 1), glm::vec4(0.4, 0.7, 0.2, 1));
	VertexFormat* triangle_1_left_up = new VertexFormat(glm::vec4(-0.3 + x_translate, 0.15, 0.0, 1), glm::vec4(0.4, 0.7, 0.2, 1));

	VertexFormat* triangle_2_left_down = new VertexFormat(glm::vec4(-0.3 + x_translate, 0.1, 0.0, 1), glm::vec4(0.4, 0.7, 0.2, 1));
	VertexFormat* triangle_2_right_down = new VertexFormat(glm::vec4(-0.2 + x_translate, 0.1, 0.0, 1), glm::vec4(0.4, 0.7, 0.2, 1));
	
	VertexFormat* rectangle_1_left_down = new VertexFormat(glm::vec4(-0.3 + x_translate, -0.35, 0.0, 1), glm::vec4(0.4, 0.7, 0.2, 1));
	VertexFormat* rectangle_1_right_down = new VertexFormat(glm::vec4(-0.2 + x_translate, -0.35, 0.0, 1), glm::vec4(0.4, 0.7, 0.2, 1));

	VertexFormat* rectangle_2_right_up = new VertexFormat(glm::vec4(-0.3 + x_translate, -0.25, 0.0, 1), glm::vec4(0.4, 0.7, 0.2, 1));
	VertexFormat* rectangle_2_left_up = new VertexFormat(glm::vec4(-0.4 + x_translate, -0.25, 0.0, 1), glm::vec4(0.4, 0.7, 0.2, 1));
	VertexFormat* rectangle_2_left_down = new VertexFormat(glm::vec4(-0.4 + x_translate, -0.35, 0.0, 1), glm::vec4(0.4, 0.7, 0.2, 1));


	vertices.push_back(*triangle_1_right_down);
	vertices.push_back(*triangle_1_right_up);
	vertices.push_back(*triangle_1_left_up);

	vertices.push_back(*triangle_2_left_down);
	vertices.push_back(*triangle_2_right_down);

	vertices.push_back(*rectangle_1_left_down);
	vertices.push_back(*rectangle_1_right_down);

	vertices.push_back(*rectangle_2_right_up);
	vertices.push_back(*rectangle_2_left_up);
	vertices.push_back(*rectangle_2_left_down);


	managers::CollisionManager::addSceneLine(triangle_1_right_down, triangle_1_right_up);
	managers::CollisionManager::addSceneLine(triangle_1_right_up, triangle_1_left_up);
	managers::CollisionManager::addSceneLine(triangle_1_left_up, triangle_2_left_down);
	managers::CollisionManager::addSceneLine(triangle_1_left_up, triangle_1_right_down);

	managers::CollisionManager::addSceneLine(triangle_2_left_down, rectangle_1_left_down);
	managers::CollisionManager::addSceneLine(rectangle_1_left_down, rectangle_1_right_down);
	managers::CollisionManager::addSceneLine(rectangle_1_right_down, triangle_2_right_down);

	managers::CollisionManager::addSceneLine(rectangle_2_right_up, rectangle_2_left_up);
	managers::CollisionManager::addSceneLine(rectangle_2_left_up, rectangle_2_left_down);
	managers::CollisionManager::addSceneLine(rectangle_2_left_down, rectangle_1_left_down);
	

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 10, &vertices[0], GL_STATIC_DRAW);

	return vbo;
}

GLuint CustomModel_2::generateIBO()
{
	GLuint ibo;

	std::vector<GLuint> indexes;

	indexes.push_back(0);
	indexes.push_back(1);
	indexes.push_back(2);
	indexes.push_back(2);
	indexes.push_back(3);
	indexes.push_back(4);
	indexes.push_back(4);
	indexes.push_back(3);
	indexes.push_back(5);
	indexes.push_back(4);
	indexes.push_back(5);
	indexes.push_back(6);
	indexes.push_back(5);
	indexes.push_back(7);
	indexes.push_back(8);
	indexes.push_back(5);
	indexes.push_back(8);
	indexes.push_back(9);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 18, &indexes[0], GL_STATIC_DRAW);

	return ibo;
}

GLuint CustomModel_2::generateVAO()
{
	GLuint vao;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	return vao;
}

void CustomModel_2::bindShaderInputData()
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));

	glBindVertexArray(0);
}

void CustomModel_2::setModelMatrix()
{
	glm::mat4 model_matrix1 = glm::mat4(1);

	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, false, glm::value_ptr(model_matrix1));
}

void CustomModel_2::update()
{

}

void CustomModel_2::draw()
{
	glUseProgram(program);
	glBindVertexArray(vao);
	setModelMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
	//glDrawRangeElements(GL_LINE_STRIP, 0, 3, 6, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
}

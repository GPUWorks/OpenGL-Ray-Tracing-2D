/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#include "Star.h"
#include "ModelManager.h"
#include <glm/gtc/type_ptr.hpp>

using namespace rendering;
using namespace models;
using namespace formats;
using namespace managers;

Star::Star() { }

Star::~Star() { }

void Star::create()
{
	this->vao = generateVAO();
	this->vbos.push_back(generateVBO());
	this->ibos.push_back(generateIBO());

	bindShaderInputData();
}

GLuint Star::generateVBO()
{
	GLuint vbo;

	std::vector<VertexFormat> vertices;

	float x_translate = -0.70f;
	float y_translate = 0.70f;

	VertexFormat* star_1 = new VertexFormat(glm::vec4(0.0 + x_translate, 0.1 + y_translate, 0.0, 1), glm::vec4(0, 0.6, 0, 1));
	VertexFormat* star_2 = new VertexFormat(glm::vec4(-0.02 + x_translate, 0.03 + y_translate, 0.0, 1), glm::vec4(0, 0.6, 0, 1));
	VertexFormat* star_3 = new VertexFormat(glm::vec4(-0.08 + x_translate, 0.03 + y_translate, 0.0, 1), glm::vec4(0, 0.6, 0, 1));
	VertexFormat* star_4 = new VertexFormat(glm::vec4(-0.03 + x_translate, -0.03 + y_translate, 0.0, 1), glm::vec4(0, 0.6, 0, 1));
	VertexFormat* star_5 = new VertexFormat(glm::vec4(-0.05 + x_translate, -0.1 + y_translate, 0.0, 1), glm::vec4(0, 0.6, 0, 1));
	VertexFormat* star_6 = new VertexFormat(glm::vec4(0.00 + x_translate, -0.05 + y_translate, 0.0, 1), glm::vec4(0, 0.6, 0, 1));
	VertexFormat* star_7 = new VertexFormat(glm::vec4(0.05 + x_translate, -0.1 + y_translate, 0.0, 1), glm::vec4(0, 0.6, 0, 1));
	VertexFormat* star_8 = new VertexFormat(glm::vec4(0.03 + x_translate, -0.03 + y_translate, 0.0, 1), glm::vec4(0, 0.6, 0, 1));
	VertexFormat* star_9 = new VertexFormat(glm::vec4(0.08 + x_translate, 0.03 + y_translate, 0.0, 1), glm::vec4(0, 0.6, 0, 1));
	VertexFormat* star_10 = new VertexFormat(glm::vec4(0.02 + x_translate, 0.03 + y_translate, 0.0, 1), glm::vec4(0, 0.6, 0, 1));


	vertices.push_back(*star_1);
	vertices.push_back(*star_2);
	vertices.push_back(*star_3);
	vertices.push_back(*star_4);
	vertices.push_back(*star_5);
	vertices.push_back(*star_6);
	vertices.push_back(*star_7);
	vertices.push_back(*star_8);
	vertices.push_back(*star_9);
	vertices.push_back(*star_10);


	managers::CollisionManager::addSceneLine(star_1, star_2);
	managers::CollisionManager::addSceneLine(star_2, star_3);
	managers::CollisionManager::addSceneLine(star_3, star_4);
	managers::CollisionManager::addSceneLine(star_4, star_5);
	managers::CollisionManager::addSceneLine(star_5, star_6);
	managers::CollisionManager::addSceneLine(star_6, star_7);
	managers::CollisionManager::addSceneLine(star_7, star_8);
	managers::CollisionManager::addSceneLine(star_8, star_9);
	managers::CollisionManager::addSceneLine(star_9, star_10);
	managers::CollisionManager::addSceneLine(star_10, star_1);


	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 10, &vertices[0], GL_STATIC_DRAW);

	return vbo;
}

GLuint Star::generateIBO()
{
	GLuint ibo;

	std::vector<GLuint> indexes;

	indexes.push_back(0);
	indexes.push_back(1);
	indexes.push_back(9);
	indexes.push_back(1);
	indexes.push_back(2);
	indexes.push_back(3);
	indexes.push_back(3);
	indexes.push_back(4);
	indexes.push_back(5);
	indexes.push_back(5);
	indexes.push_back(6);
	indexes.push_back(7);
	indexes.push_back(7);
	indexes.push_back(8);
	indexes.push_back(9);

	indexes.push_back(1);
	indexes.push_back(3);
	indexes.push_back(9);
	indexes.push_back(3);
	indexes.push_back(5);
	indexes.push_back(9);
	indexes.push_back(5);
	indexes.push_back(7);
	indexes.push_back(9);


	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 24, &indexes[0], GL_STATIC_DRAW);

	return ibo;
}

GLuint Star::generateVAO()
{
	GLuint vao;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	return vao;
}

void Star::bindShaderInputData()
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));

	glBindVertexArray(0);
}

void Star::setModelMatrix()
{
	glm::mat4 model_matrix1 = glm::mat4(1);
	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, false, glm::value_ptr(model_matrix1));
}

void Star::update() 
{

}

void Star::draw()
{
	glUseProgram(program);
	glBindVertexArray(vao);
	setModelMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLE_STRIP, 24, GL_UNSIGNED_INT, 0);
	//glDrawRangeElements(GL_LINE_STRIP, 0, 3, 6, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
}

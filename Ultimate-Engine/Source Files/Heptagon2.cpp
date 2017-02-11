/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#include "Heptagon2.h"
#include "ModelManager.h"
#include <glm/gtc/type_ptr.hpp>

using namespace rendering;
using namespace models;
using namespace formats;
using namespace managers;

Heptagon2::Heptagon2() { }

Heptagon2::~Heptagon2() { }

void Heptagon2::create()
{
	this->vao = generateVAO();
	this->vbos.push_back(generateVBO());
	this->ibos.push_back(generateIBO());

	bindShaderInputData();
}

GLuint Heptagon2::generateVBO()
{
	GLuint vbo;

	std::vector<VertexFormat> vertices;

	float scale = 0.8f;
	float x_translate = 0.0f;
	float y_translate = -0.35f;

	VertexFormat* heptagon_center = new VertexFormat(glm::vec4(0.0 * scale + x_translate, 0.0 * scale + y_translate, 0.0, 1), glm::vec4(0.2, 1.0, 0.3, 1));

	VertexFormat* heptagon_middle_up = new VertexFormat(glm::vec4(0.0 * scale + x_translate, 0.2 * scale + y_translate, 0.0, 1), glm::vec4(0.2, 1.0, 0.3, 1));
	VertexFormat* heptagon_left_up = new VertexFormat(glm::vec4(-0.2 * scale + x_translate, 0.08 * scale + y_translate, 0.0, 1), glm::vec4(0.2, 1.0, 0.3, 1));
	VertexFormat* heptagon_left_down_1 = new VertexFormat(glm::vec4(-0.2 * scale + x_translate, -0.06 * scale + y_translate, 0.0, 1), glm::vec4(0.2, 1.0, 0.3, 1));
	VertexFormat* heptagon_left_down_2 = new VertexFormat(glm::vec4(-0.08 * scale + x_translate, -0.2 * scale + y_translate, 0.0, 1), glm::vec4(0.2, 1.0, 0.3, 1));
	VertexFormat* heptagon_right_down_2 = new VertexFormat(glm::vec4(0.08 * scale + x_translate, -0.2 * scale + y_translate, 0.0, 1), glm::vec4(0.2, 1.0, 0.3, 1));
	VertexFormat* heptagon_right_down_1 = new VertexFormat(glm::vec4(0.2 * scale + x_translate, -0.06 * scale + y_translate, 0.0, 1), glm::vec4(0.2, 1.0, 0.3, 1));
	VertexFormat* heptagon_right_up = new VertexFormat(glm::vec4(0.2 * scale + x_translate, 0.08 * scale + y_translate, 0.0, 1), glm::vec4(0.2, 1.0, 0.3, 1));


	vertices.push_back(*heptagon_center);
	vertices.push_back(*heptagon_middle_up);
	vertices.push_back(*heptagon_left_up);
	vertices.push_back(*heptagon_left_down_1);
	vertices.push_back(*heptagon_left_down_2);
	vertices.push_back(*heptagon_right_down_2);
	vertices.push_back(*heptagon_right_down_1);
	vertices.push_back(*heptagon_right_up);


	managers::CollisionManager::addSceneLine(heptagon_middle_up, heptagon_left_up);
	managers::CollisionManager::addSceneLine(heptagon_left_up, heptagon_left_down_1);
	managers::CollisionManager::addSceneLine(heptagon_left_down_1, heptagon_left_down_2);
	managers::CollisionManager::addSceneLine(heptagon_left_down_2, heptagon_right_down_2);
	managers::CollisionManager::addSceneLine(heptagon_right_down_2, heptagon_right_down_1);
	managers::CollisionManager::addSceneLine(heptagon_right_down_1, heptagon_right_up);
	managers::CollisionManager::addSceneLine(heptagon_right_up, heptagon_middle_up);


	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 8, &vertices[0], GL_STATIC_DRAW);

	return vbo;
}

GLuint Heptagon2::generateIBO()
{
	GLuint ibo;

	std::vector<GLuint> indexes;

	indexes.push_back(0);
	indexes.push_back(1);
	indexes.push_back(2);
	indexes.push_back(3);
	indexes.push_back(4);
	indexes.push_back(5);
	indexes.push_back(6);
	indexes.push_back(7);
	indexes.push_back(1);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 9, &indexes[0], GL_STATIC_DRAW);

	return ibo;
}

GLuint Heptagon2::generateVAO()
{
	GLuint vao;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	return vao;
}

void Heptagon2::bindShaderInputData()
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));

	glBindVertexArray(0);
}

void Heptagon2::setModelMatrix()
{
	glm::mat4 model_matrix1 = glm::mat4(1);

	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, false, glm::value_ptr(model_matrix1));
}

void Heptagon2::update()
{

}

void Heptagon2::draw()
{
	glUseProgram(program);
	glBindVertexArray(vao);
	setModelMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLE_FAN, 9, GL_UNSIGNED_INT, 0);
	//glDrawRangeElements(GL_LINE_STRIP, 0, 3, 6, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
}

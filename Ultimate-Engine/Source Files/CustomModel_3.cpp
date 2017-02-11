/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#include "CustomModel_3.h"
#include "ModelManager.h"
#include <glm/gtc/type_ptr.hpp>

using namespace rendering;
using namespace models;
using namespace formats;
using namespace managers;

CustomModel_3::CustomModel_3() { }

CustomModel_3::~CustomModel_3() { }

void CustomModel_3::create()
{
	this->vao = generateVAO();
	this->vbos.push_back(generateVBO());
	this->ibos.push_back(generateIBO());

	bindShaderInputData();
}

GLuint CustomModel_3::generateVBO()
{
	GLuint vbo;

	std::vector<VertexFormat> vertices;

	float scale = 2.0f;
	float x_translate = 0.50f;
	float y_translate = -0.35f;

	VertexFormat* rectangle_1_left_down = new VertexFormat(glm::vec4(-0.1 * scale + x_translate, -0.02 * scale + y_translate, 0.0, 1), glm::vec4(1, 0, 0.3, 1));
	VertexFormat* rectangle_1_right_down = new VertexFormat(glm::vec4(0.2 * scale + x_translate, -0.02 * scale + y_translate, 0.0, 1), glm::vec4(1, 0, 0.3, 1));
	VertexFormat* rectangle_1_right_up = new VertexFormat(glm::vec4(0.2 * scale + x_translate, 0.02 * scale + y_translate, 0.0, 1), glm::vec4(1, 0, 0.3, 1));
	VertexFormat* rectangle_1_left_up = new VertexFormat(glm::vec4(-0.1 * scale + x_translate, 0.02 * scale + y_translate, 0.0, 1), glm::vec4(1, 0, 0.3, 1));

	VertexFormat* rectangle_2_left_up = new VertexFormat(glm::vec4(-0.03 * scale + x_translate, -0.02 * scale + y_translate, 0.0, 1), glm::vec4(1, 0, 0.3, 1));
	VertexFormat* rectangle_2_left_down = new VertexFormat(glm::vec4(-0.03 * scale + x_translate, -0.2 * scale + y_translate, 0.0, 1), glm::vec4(1, 0, 0.3, 1));
	VertexFormat* rectangle_2_right_down = new VertexFormat(glm::vec4(0.03 * scale + x_translate, -0.2 * scale + y_translate, 0.0, 1), glm::vec4(1, 0, 0.3, 1));
	VertexFormat* rectangle_2_right_up = new VertexFormat(glm::vec4(0.03 * scale + x_translate, -0.02 * scale + y_translate, 0.0, 1), glm::vec4(1, 0, 0.3, 1));

	VertexFormat* rectangle_3_right_down = new VertexFormat(glm::vec4(0.1 * scale + x_translate, -0.2 * scale + y_translate, 0.0, 1), glm::vec4(1, 0, 0.3, 1));
	VertexFormat* rectangle_3_right_up = new VertexFormat(glm::vec4(0.1 * scale + x_translate, -0.15 * scale + y_translate, 0.0, 1), glm::vec4(1, 0, 0.3, 1));
	VertexFormat* rectangle_3_left_up = new VertexFormat(glm::vec4(0.03 * scale + x_translate, -0.15 * scale + y_translate, 0.0, 1), glm::vec4(1, 0, 0.3, 1));



	vertices.push_back(*rectangle_1_left_down);
	vertices.push_back(*rectangle_1_right_down);
	vertices.push_back(*rectangle_1_right_up);
	vertices.push_back(*rectangle_1_left_up);

	vertices.push_back(*rectangle_2_left_up);
	vertices.push_back(*rectangle_2_left_down);
	vertices.push_back(*rectangle_2_right_down);
	vertices.push_back(*rectangle_2_right_up);

	vertices.push_back(*rectangle_3_right_down);
	vertices.push_back(*rectangle_3_right_up);
	vertices.push_back(*rectangle_3_left_up);



	managers::CollisionManager::addSceneLine(rectangle_1_left_down, rectangle_1_right_down);
	managers::CollisionManager::addSceneLine(rectangle_1_right_down, rectangle_1_right_up);
	managers::CollisionManager::addSceneLine(rectangle_1_right_up, rectangle_1_left_up);
	managers::CollisionManager::addSceneLine(rectangle_1_left_up, rectangle_1_left_down);

	managers::CollisionManager::addSceneLine(rectangle_2_left_up, rectangle_2_left_down);
	managers::CollisionManager::addSceneLine(rectangle_2_left_down, rectangle_2_right_down);
	managers::CollisionManager::addSceneLine(rectangle_2_right_down, rectangle_2_right_up);

	managers::CollisionManager::addSceneLine(rectangle_3_right_down, rectangle_3_right_up);
	managers::CollisionManager::addSceneLine(rectangle_3_right_up, rectangle_3_left_up);
	managers::CollisionManager::addSceneLine(rectangle_2_right_down, rectangle_3_right_down);


	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 11, &vertices[0], GL_STATIC_DRAW);

	return vbo;
}

GLuint CustomModel_3::generateIBO()
{
	GLuint ibo;

	std::vector<GLuint> indexes;

	indexes.push_back(0);
	indexes.push_back(1);
	indexes.push_back(2);

	indexes.push_back(0);
	indexes.push_back(2);
	indexes.push_back(3);

	indexes.push_back(4);
	indexes.push_back(5);
	indexes.push_back(6);

	indexes.push_back(4);
	indexes.push_back(6);
	indexes.push_back(7);

	indexes.push_back(6);
	indexes.push_back(8);
	indexes.push_back(9);

	indexes.push_back(10);
	indexes.push_back(6);
	indexes.push_back(9);


	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 18, &indexes[0], GL_STATIC_DRAW);

	return ibo;
}

GLuint CustomModel_3::generateVAO()
{
	GLuint vao;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	return vao;
}

void CustomModel_3::bindShaderInputData()
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));

	glBindVertexArray(0);
}

void CustomModel_3::setModelMatrix()
{
	glm::mat4 model_matrix1 = glm::mat4(1);

	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, false, glm::value_ptr(model_matrix1));
}

void CustomModel_3::update()
{

}

void CustomModel_3::draw()
{
	glUseProgram(program);
	glBindVertexArray(vao);
	setModelMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
	//glDrawRangeElements(GL_LINE_STRIP, 0, 3, 6, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
}

/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#include "Square.h"
#include "ModelManager.h"
#include <glm/gtc/type_ptr.hpp>

using namespace rendering;
using namespace models;
using namespace formats;
using namespace managers;

Square::Square() { }

Square::~Square() { }

void Square::create()
{
	this->vao = generateVAO();
	this->vbos.push_back(generateVBO());
	this->ibos.push_back(generateIBO());

	bindShaderInputData();
}

GLuint Square::generateVBO()
{
	GLuint vbo;

	std::vector<VertexFormat> vertices;

	float scale = 1.5f;
	float x_translate = 0.70f;
	float y_translate = -0.10f;

	VertexFormat* square_right_up = new VertexFormat(glm::vec4(0.07 * scale + x_translate, 0.07 * scale + y_translate, 0.0, 1), glm::vec4(0.9, 0, 0, 1));
	VertexFormat* square_left_up = new VertexFormat(glm::vec4(-0.07 * scale + x_translate, 0.07 * scale + y_translate, 0.0, 1), glm::vec4(0.9, 0, 0, 1));
	VertexFormat* square_left_down = new VertexFormat(glm::vec4(-0.07 * scale + x_translate, -0.07 * scale + y_translate, 0.0, 1), glm::vec4(0.9, 0, 0, 1));
	VertexFormat* square_right_down = new VertexFormat(glm::vec4(0.07 * scale + x_translate, -0.07 * scale + y_translate, 0.0, 1), glm::vec4(0.9, 0, 0, 1));
	


	vertices.push_back(*square_right_up);
	vertices.push_back(*square_left_up);
	vertices.push_back(*square_left_down);
	vertices.push_back(*square_right_down);


	managers::CollisionManager::addSceneLine(square_right_up, square_left_up);
	managers::CollisionManager::addSceneLine(square_left_up, square_left_down);
	managers::CollisionManager::addSceneLine(square_left_down, square_right_down);
	managers::CollisionManager::addSceneLine(square_right_down, square_right_up);


	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, &vertices[0], GL_STATIC_DRAW);

	return vbo;
}

GLuint Square::generateIBO()
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

GLuint Square::generateVAO()
{
	GLuint vao;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	return vao;
}

void Square::bindShaderInputData()
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));

	glBindVertexArray(0);
}

//int i = 0;
//glm::mat4 model_matrix1 = glm::mat4(1);

void Square::setModelMatrix()
{
	glm::mat4 model_matrix1 = glm::mat4(1);
	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, false, glm::value_ptr(model_matrix1));

	/*if(i % 100 == 0)
	model_matrix1 = glm::mat4(1);

	i++;*/
}



void Square::update()
{

}

void Square::draw()
{
	glUseProgram(program);
	glBindVertexArray(vao);
	setModelMatrix();
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

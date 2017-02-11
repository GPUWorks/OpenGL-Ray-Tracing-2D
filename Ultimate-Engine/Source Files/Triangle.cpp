/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#include "Triangle.h"
#include "ModelManager.h"
#include <glm/gtc/type_ptr.hpp>

using namespace rendering;
using namespace models;
using namespace formats;
using namespace managers;

Triangle::Triangle() { }

Triangle::~Triangle() { }

void Triangle::create()
{
	this->vao = generateVAO();
	this->vbos.push_back(generateVBO());
	this->ibos.push_back(generateIBO());

	bindShaderInputData();
}

GLuint Triangle::generateVBO()
{
	GLuint vbo;

	std::vector<VertexFormat> vertices;

	float scale = 1.5;
	float x_translate = -0.80f;
	float y_translate = 0.80f;

	VertexFormat* triangle_right_up = new VertexFormat(glm::vec4(0.15 * scale + x_translate, 0.15 * scale + y_translate, 0.0, 1), glm::vec4(0.6, 0.6, 0.4, 1));
	VertexFormat* triangle_left_up = new VertexFormat(glm::vec4(-0.15 * scale + x_translate, 0.15 * scale + y_translate, 0.0, 1), glm::vec4(0.6, 0.6, 0.4, 1));
	VertexFormat* triangle_left_down = new VertexFormat(glm::vec4(-0.15 * scale + x_translate, -0.15 * scale + y_translate, 0.0, 1), glm::vec4(0.6, 0.6, 0.4, 1));

	vertices.push_back(*triangle_right_up);
	vertices.push_back(*triangle_left_up);
	vertices.push_back(*triangle_left_down);


	managers::CollisionManager::addSceneLine(triangle_right_up, triangle_left_up);
	managers::CollisionManager::addSceneLine(triangle_left_up, triangle_left_down);
	managers::CollisionManager::addSceneLine(triangle_left_down, triangle_right_up);


	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 3, &vertices[0], GL_STATIC_DRAW);

	return vbo;
}

GLuint Triangle::generateIBO()
{
	GLuint ibo;

	std::vector<GLuint> indexes;

	indexes.push_back(0);
	indexes.push_back(1);
	indexes.push_back(2);
	indexes.push_back(0);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 4, &indexes[0], GL_STATIC_DRAW);

	return ibo;
}

GLuint Triangle::generateVAO()
{
	GLuint vao;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	return vao;
}

void Triangle::bindShaderInputData()
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));
	
	glBindVertexArray(0);
}

//int i = 0;
//glm::mat4 model_matrix1 = glm::mat4(1);

void Triangle::setModelMatrix()
{
	glm::mat4 model_matrix1 = glm::mat4(1);
	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, false, glm::value_ptr(model_matrix1));

	/*if(i % 100 == 0)
		model_matrix1 = glm::mat4(1);

	i++;*/
}



void Triangle::update()
{

}

void Triangle::draw()
{
	glUseProgram(program);
	glBindVertexArray(vao);
	setModelMatrix();
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 4, GL_UNSIGNED_INT, 0);
}

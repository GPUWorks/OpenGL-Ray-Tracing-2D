/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#include "Camera.h"
#include "ModelManager.h"
#include <glm/gtc/type_ptr.hpp>

using namespace rendering;
using namespace models;
using namespace formats;
using namespace managers;

Camera::Camera() { }

Camera::~Camera() { }

void Camera::create()
{
	this->vao = generateVAO();
	this->vbos.push_back(generateVBO());
	this->ibos.push_back(generateIBO());

	bindShaderInputData();
}

GLuint Camera::generateVBO()
{
	GLuint vbo;

	std::vector<VertexFormat> vertices;


	VertexFormat* camera_right_up = new VertexFormat(glm::vec4(1.0, 1.0, 0.0, 1), glm::vec4(0, 0, 0, 1));
	VertexFormat* camera_left_up = new VertexFormat(glm::vec4(0.70, 1.0, 0.0, 1), glm::vec4(0, 0, 0, 1));
	VertexFormat* camera_right_down = new VertexFormat(glm::vec4(1.0, 0.70, 0.0, 1), glm::vec4(0, 0, 0, 1));

	vertices.push_back(*camera_right_up);
	vertices.push_back(*camera_left_up);
	vertices.push_back(*camera_right_down);


	managers::CollisionManager::addCamera(camera_right_up, camera_left_up);
	managers::CollisionManager::addCamera(camera_left_up, camera_right_down);
	managers::CollisionManager::addCamera(camera_right_down, camera_right_up);


	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 3, &vertices[0], GL_STATIC_DRAW);

	return vbo;
}

GLuint Camera::generateIBO()
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

GLuint Camera::generateVAO()
{
	GLuint vao;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	return vao;
}

void Camera::bindShaderInputData()
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));

	glBindVertexArray(0);
}

//int i = 0;
//glm::mat4 model_matrix1 = glm::mat4(1);

void Camera::setModelMatrix()
{
	glm::mat4 model_matrix1 = glm::mat4(1);
	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, false, glm::value_ptr(model_matrix1));

	/*if(i % 100 == 0)
	model_matrix1 = glm::mat4(1);

	i++;*/
}



void Camera::update()
{

}

void Camera::draw()
{
	glUseProgram(program);
	glBindVertexArray(vao);
	setModelMatrix();
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 4, GL_UNSIGNED_INT, 0);
}

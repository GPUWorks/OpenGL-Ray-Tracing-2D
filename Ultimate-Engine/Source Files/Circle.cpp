/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#include "Circle.h"
#include "ModelManager.h"
#include <glm/gtc/type_ptr.hpp>

using namespace rendering;
using namespace models;
using namespace formats;
using namespace managers;

Circle::Circle() { }

Circle::~Circle() { }

void Circle::create()
{
	this->vao = generateVAO();
	this->vbos.push_back(generateVBO());
	this->ibos.push_back(generateIBO());

	bindShaderInputData();
}

GLuint Circle::generateVBO()
{
	GLuint vbo;

	std::vector<VertexFormat> vertices;

	int segments_no = 20;
	float radius = 0.15f;

	for (int i = 0; i < segments_no; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(segments_no);

		float x = radius * cosf(theta);
		float y = radius * sinf(theta);

		VertexFormat* circle_1 = new VertexFormat(glm::vec4(x + 0.09, y + 0.6, 0.0, 1), glm::vec4(0.5, 0, 1, 1));

		if (i + 1 == 20)
		{
			theta = 2.0f * 3.1415926f * float(0) / float(segments_no);
			float x_2 = (radius * cosf(theta));
			float y_2 = (radius * sinf(theta));

			VertexFormat* circle_2 = new VertexFormat(glm::vec4(x_2 + 0.09, y_2 + 0.6, 0.0, 1), glm::vec4(0.5, 0, 1, 1));

			managers::CollisionManager::addSceneLine(circle_1, circle_2);
		}
		else
		{
			theta = 2.0f * 3.1415926f * float(i + 1) / float(segments_no);
			float x_2 = (radius * cosf(theta));
			float y_2 = (radius * sinf(theta));

			VertexFormat* circle_2 = new VertexFormat(glm::vec4(x_2 + 0.09, y_2 + 0.6, 0.0, 1), glm::vec4(0.5, 0, 1, 1));

			managers::CollisionManager::addSceneLine(circle_1, circle_2);
		}

		vertices.push_back(*circle_1);
	}

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * segments_no, &vertices[0], GL_STATIC_DRAW);

	return vbo;
}

GLuint Circle::generateIBO()
{
	GLuint ibo;

	std::vector<GLuint> indexes;

	for (int i = 0; i < 20; i++)
	{
		indexes.push_back(i);
	}

	indexes.push_back(0);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 21, &indexes[0], GL_STATIC_DRAW);

	return ibo;
}

GLuint Circle::generateVAO()
{
	GLuint vao;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	return vao;
}

void Circle::bindShaderInputData()
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));

	glBindVertexArray(0);
}

//int i = 0;
//glm::mat4 model_matrix1 = glm::mat4(1);

void Circle::setModelMatrix()
{
	glm::mat4 model_matrix1 = glm::mat4(1);
	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, false, glm::value_ptr(model_matrix1));

	/*if(i % 100 == 0)
	model_matrix1 = glm::mat4(1);

	i++;*/
}



void Circle::update()
{

}

void Circle::draw()
{
	glUseProgram(program);
	glBindVertexArray(vao);
	setModelMatrix();
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glDrawElements(GL_TRIANGLE_FAN, 21, GL_UNSIGNED_INT, 0);
}

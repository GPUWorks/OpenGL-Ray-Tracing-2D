/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#include "Model.h"

using namespace rendering;
using namespace models;

Model::Model() { }

Model::~Model()
{
	destroy();
}

void Model::create()
{
	//this is abstract, we don't continue to override this method
}

void Model::draw()
{
	//this is abstract, we don't continue to override this method
}

void Model::update()
{
	//this is abstract, we don't continue to override this method
}

void Model::setProgram(GLuint program)
{
	this->program = program;
}

const GLuint Model::getProgram()
{
	return this->program;
}

const GLuint Model::getVao() const
{
	return vao;
}

const std::vector<GLuint> Model::getIbos() const
{
	return ibos;
}

const std::vector<GLuint> Model::getVbos() const
{
	return vbos;
}

void Model::destroy()
{
	glDeleteVertexArrays(1, &vao);

	if (!ibos.empty())
	{
		glDeleteBuffers(ibos.size(), &ibos[0]);
		ibos.clear();
	}

	if (!vbos.empty())
	{
		glDeleteBuffers(vbos.size(), &vbos[0]);
		vbos.clear();
	}
}

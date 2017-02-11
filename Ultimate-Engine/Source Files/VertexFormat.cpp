/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#include "VertexFormat.h"


rendering::formats::VertexFormat::VertexFormat() {}

rendering::formats::VertexFormat::VertexFormat(const glm::vec4 &iPos, const glm::vec4 &iColor)
{
	position = iPos;
	color = iColor;
}

rendering::formats::VertexFormat::VertexFormat(const glm::vec4 &iPos)
{
	position = iPos;
	color = glm::vec4(0.0, 0.0, 0.0, 1.0);
}

void rendering::formats::VertexFormat::setPosition(glm::vec4 position)
{
	this->position = position;
}

void rendering::formats::VertexFormat::setColor(glm::vec4 color)
{
	this->color = color;
}


glm::vec4 rendering::formats::VertexFormat::getPosition()
{
	return position;
}

glm::vec4 rendering::formats::VertexFormat::getColor()
{
	return color;
}

float rendering::formats::VertexFormat::get_X()
{
	return this->getPosition().x;
}

float rendering::formats::VertexFormat::get_Y()
{
	return this->getPosition().y;
}
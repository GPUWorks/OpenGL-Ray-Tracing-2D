/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#include "WindowInfo.h"


core::info::WindowInfo::WindowInfo()
{
	name = "OpenGL Default Window";
	width = 800; height = 600;
	x_position = 0;
	y_position = 0;
	reshapable = true;
}

core::info::WindowInfo::WindowInfo(std::string name,
	int start_position_x, int start_position_y,
	int width, int height,
	bool reshapable)
{

	this->name = name;
	this->x_position = start_position_x;
	this->y_position = start_position_y;

	this->width = width;
	this->height = height;
	this->reshapable = reshapable;
}

core::info::WindowInfo::WindowInfo(const WindowInfo& windowInfo)
{
	name = windowInfo.name;
	x_position = windowInfo.x_position;
	y_position = windowInfo.y_position;

	width = windowInfo.width;
	height = windowInfo.height;
	reshapable = windowInfo.reshapable;
}

void core::info::WindowInfo::operator=(const WindowInfo& windowInfo)
{
	name = windowInfo.name;

	x_position = windowInfo.x_position;
	y_position = windowInfo.y_position;

	width = windowInfo.width;
	height = windowInfo.height;
	reshapable = windowInfo.reshapable;
}

std::string core::info::WindowInfo::getName() const
{
	return name;
}

int core::info::WindowInfo::getWidth() const
{
	return width;
}

int core::info::WindowInfo::getHeight() const
{
	return height;
}

int core::info::WindowInfo::get_X_position() const
{
	return x_position;
}

int core::info::WindowInfo::get_Y_position() const
{
	return y_position;
}

bool core::info::WindowInfo::isReshapable() const
{
	return reshapable;
}

void core::info::WindowInfo::setWidth(int widht)
{
	this->width = width;
}

void core::info::WindowInfo::setHeight(int height)
{
	this->height = height;
}
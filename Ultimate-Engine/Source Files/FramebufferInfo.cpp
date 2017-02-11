/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#include "FramebufferInfo.h"

#include <glew\glew.h>
#include <freeglut\freeglut.h>


core::info::FramebufferInfo::FramebufferInfo()
{
	flags = GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH;
	msaa = false;
}

core::info::FramebufferInfo::FramebufferInfo(bool color, bool depth, bool stencil, bool msaa)
{
	flags = GLUT_DOUBLE;

	if (color)
		flags |= GLUT_RGBA | GLUT_ALPHA;
	if (depth)
		flags |= GLUT_DEPTH;
	if (stencil)
		flags |= GLUT_STENCIL;
	if (msaa)
		flags |= GLUT_MULTISAMPLE;

	this->msaa = msaa;
}

core::info::FramebufferInfo::FramebufferInfo(const FramebufferInfo& framebufferInfo)
{
	flags = framebufferInfo.flags;
	msaa = framebufferInfo.msaa;
}

void core::info::FramebufferInfo::operator=(const FramebufferInfo& info)
{
	flags = info.flags;
	msaa = info.msaa;
}

unsigned int core::info::FramebufferInfo::getFlags() const
{
	return flags;
}

bool core::info::FramebufferInfo::isUsingMsaa() const
{
	return msaa;
}
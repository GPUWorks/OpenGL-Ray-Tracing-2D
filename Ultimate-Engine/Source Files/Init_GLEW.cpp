/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#include "Init_GLEW.h"


void core::init::Init_GLEW::init()
{

	glewExperimental = GL_TRUE;

	if (glewInit() == GLEW_OK)
	{
		std::cout << "GLEW:\tInitialized\n" << std::endl;
	}
	else
	{
		std::cout << "GLEW:\tFailed to initialize\n" << std::endl;
		std::terminate();
	}

	if (glewIsSupported("GL_VERSION_3_3"))
	{
		std::cout << "GLEW:\tGL_VERSION_3_3 is 3.3\n\n";
	}
	else
	{
		std::cout << "GLEW:\tGL_VERSION_3_3 not supported\n\n";
	}
}
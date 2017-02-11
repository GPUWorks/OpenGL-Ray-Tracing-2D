/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#pragma once

#include <iostream>

#include "ContextInfo.h"
#include "FramebufferInfo.h"
#include "WindowInfo.h"
#include "Init_GLEW.h"
#include "IListener.h"
#include "KeyListener.h"


namespace core
{
	namespace init
	{
		class Init_GLUT
		{
			public:
				static void init(const core::info::WindowInfo& window,
					const core::info::ContextInfo& context,
					const core::info::FramebufferInfo& framebufferInfo);

			public:
				static void run(void);
				static void close();
				static void enterFullscreen();
				static void exitFullscreen();
				static void printOpenGLInfo(
					const core::info::WindowInfo& windowInfo,
					const core::info::ContextInfo& context);

			private:
				static core::listeners::IListener* windowListener;
				static core::listeners::KeyListener* keyListener;
				static core::info::WindowInfo windowInformation;
				static int frame;
				static int time;
				static int timebase;

			public:
				static void setWindowListener(core::listeners::IListener*& windowListener);
				static void setKeyListener(core::listeners::KeyListener*& keyListener);

			private:
				static void idleCallback(void);
				static void displayCallback(void);
				static void reshapeCallback(int width, int height);
				static void closeCallback();

				static void keyboardDownCallback(unsigned char key_pressed, int mouse_x, int mouse_y);
				static void keyboardUpCallback(unsigned char key_released, int mouse_x, int mouse_y);
				static void specialDownCallback(int key_pressed, int mouse_x, int mouse_y);
				static void specialUpCallback(int key_released, int mouse_x, int mouse_y);
				static void motionCallback(int mouse_x, int mouse_y);
				static void passiveMotionCallback(int mouse_x, int mouse_y);
				static void mouseCallback(int button, int state, int mouse_x, int mouse_y);
				static void mouseWheelCallback(int wheel, int direction, int mouse_x, int mouse_y);
		};
	}
}

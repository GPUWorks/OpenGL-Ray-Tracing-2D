/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#pragma once

namespace core
{
	namespace listeners
	{
		class KeyListener
		{
			public:

				virtual ~KeyListener() = 0;

				virtual void notifyReshape(int width, int height, int previos_width, int previous_height) {}

				virtual void notifyKeyPressed(unsigned char key_pressed, int mouse_x, int mouse_y) {}
				virtual void notifyKeyReleased(unsigned char key_released, int mouse_x, int mouse_y) {}
				virtual void notifySpecialKeyPressed(int key_pressed, int mouse_x, int mouse_y) {}
				virtual void notifySpecialKeyReleased(int key_released, int mouse_x, int mouse_y) {}
				virtual void notifyMouseDrag(int mouse_x, int mouse_y) {}
				virtual void notifyMouseMove(int mouse_x, int mouse_y) {}
				virtual void notifyMouseClick(int button, int state, int mouse_x, int mouse_y) {}
				virtual void notifyMouseScroll(int wheel, int direction, int mouse_x, int mouse_y) {}
		};

		inline KeyListener::~KeyListener() { }
	}
}

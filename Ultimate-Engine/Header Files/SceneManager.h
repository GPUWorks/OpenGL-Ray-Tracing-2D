/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#pragma once

#include "ShaderManager.h"
#include "ModelManager.h"
#include "IListener.h"
#include "KeyListener.h"


namespace managers
{
	class SceneManager : public core::listeners::IListener, public core::listeners::KeyListener
	{

	public:
		SceneManager();
		~SceneManager();

		static SceneManager* scene_manager;

		virtual void notifyBeginFrame();
		virtual void notifyDisplayFrame();
		virtual void notifyEndFrame();
		virtual void notifyReshape(int width, int height, int previos_width, int previous_height);

		virtual ShaderManager* getShaderManager();
		virtual ModelManager* getModelManager();


		virtual void notifyKeyPressed(unsigned char key_pressed, int mouse_x, int mouse_y);
		virtual void notifyKeyReleased(unsigned char key_released, int mouse_x, int mouse_y);
		virtual void notifySpecialKeyPressed(int key_pressed, int mouse_x, int mouse_y);
		virtual void notifySpecialKeyReleased(int key_released, int mouse_x, int mouse_y);
		virtual void notifyMouseDrag(int mouse_x, int mouse_y);
		virtual void notifyMouseMove(int mouse_x, int mouse_y);
		virtual void notifyMouseClick(int button, int state, int mouse_x, int mouse_y);
		virtual void notifyMouseScroll(int wheel, int direction, int mouse_x, int mouse_y);

	private:
		managers::ShaderManager* shader_manager;
		managers::ModelManager* models_manager;
	};
}

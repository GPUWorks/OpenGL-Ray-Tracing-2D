/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#include "CollisionManager.h"
#include "SceneManager.h"


managers::SceneManager* managers::SceneManager::scene_manager;

managers::SceneManager::SceneManager()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);

	shader_manager = new ShaderManager();
	models_manager = new ModelManager();
}

managers::SceneManager::~SceneManager()
{
	delete shader_manager;
	delete models_manager;
}

void managers::SceneManager::notifyBeginFrame()
{
	models_manager->update();
}

void managers::SceneManager::notifyDisplayFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(0.0, 0.0, 0.0, 1.0);

	models_manager->draw();
}

void managers::SceneManager::notifyEndFrame() { }

void managers::SceneManager::notifyReshape(int width, int height,
	int previos_width, int previous_height) { 

	glScissor(0, 0, width, height);
	glClearDepth(1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glScissor(20, 15, width - 40, height - 30);
	glClearDepth(1.0f);
	glClearColor(0.05f, 0.25f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(20, 15, width - 40, height - 30);
}

managers::ShaderManager* managers::SceneManager::getShaderManager()
{
	return shader_manager;
}

managers::ModelManager* managers::SceneManager::getModelManager()
{
	return models_manager;
}


void managers::SceneManager::notifyKeyPressed(unsigned char key_pressed, int mouse_x, int mouse_y)
{
	//printf("Key Pressed\n");

	if (key_pressed == 'r')
	{
		for (auto model_name : managers::CollisionManager::scene_object_rays_names)
		{
			managers::SceneManager::getModelManager()->deleteModel(model_name);
		}

		managers::CollisionManager::reset();
		managers::CollisionManager::scene_object_rays_names.clear();
	}

	if (key_pressed == '+')
	{
		rendering::models::RadiusDraw::draw_speed += 0.2f;

		if (rendering::models::RadiusDraw::draw_speed > 10.0f)
			rendering::models::RadiusDraw::draw_speed = 10.0f;

		printf("Draw speed increased to %2.1f (max 10.0)\n", 
			rendering::models::RadiusDraw::draw_speed);
	}

	if (key_pressed == '-')
	{
		rendering::models::RadiusDraw::draw_speed -= 0.2f;

		if (rendering::models::RadiusDraw::draw_speed < 0.0f)
			rendering::models::RadiusDraw::draw_speed = 0.0f;

		printf("Draw speed decreased to %2.1f (min 0.0)\n", 
			rendering::models::RadiusDraw::draw_speed);
	}

	if (key_pressed == ' ')
	{
		managers::CollisionManager::space_key_pressed = true;
		managers::CollisionManager::is_light_directly_from_source = false;
	}
}

void managers::SceneManager::notifyKeyReleased(unsigned char key_released, int mouse_x, int mouse_y)
{
	//printf("Key Released\n");
}

void managers::SceneManager::notifySpecialKeyPressed(int key_pressed, int mouse_x, int mouse_y)
{
	if (key_pressed == 100)
	{
		for (auto model_name : managers::CollisionManager::scene_object_rays_names)
		{
			managers::SceneManager::getModelManager()->deleteModel(model_name);
		}

		managers::CollisionManager::reset();
		managers::CollisionManager::scene_object_rays_names.clear();

		// LEFT
		managers::CollisionManager::light_source_point++;

		managers::CollisionManager::light_source_point_changed = 1;

		if (managers::CollisionManager::light_source_point == 60)
			managers::CollisionManager::light_source_point = 0;

		printf("Light Source Ray %d from 60 possible rays\n", managers::CollisionManager::light_source_point);
	}
	
	if (key_pressed == 102)
	{
		for (auto model_name : managers::CollisionManager::scene_object_rays_names)
		{
			managers::SceneManager::getModelManager()->deleteModel(model_name);
		}

		managers::CollisionManager::reset();
		managers::CollisionManager::scene_object_rays_names.clear();

		// RIGHT
		managers::CollisionManager::light_source_point--;

		managers::CollisionManager::light_source_point_changed = 1;

		if (managers::CollisionManager::light_source_point == -1)
			managers::CollisionManager::light_source_point = 59;

		printf("Light Source Ray %d from 60 possible rays\n", managers::CollisionManager::light_source_point);
	}

	if (key_pressed == 101)
	{
		managers::CollisionManager::max_no_of_rays++;
		printf("Number of max rays to be drawn increased: %d\n", managers::CollisionManager::max_no_of_rays);
	}

	if (key_pressed == 103)
	{
		managers::CollisionManager::max_no_of_rays--;

		if (managers::CollisionManager::max_no_of_rays < 1)
			managers::CollisionManager::max_no_of_rays = 1;

		printf("Number of max rays to be drawn decreased: %d\n", managers::CollisionManager::max_no_of_rays);
	}

}

void managers::SceneManager::notifySpecialKeyReleased(int key_released, int mouse_x, int mouse_y)
{
	//printf("Special Key Released\n");
}

void managers::SceneManager::notifyMouseDrag(int mouse_x, int mouse_y)
{
	//printf("%d Mouse Drag\n", mouse_x);
}

void managers::SceneManager::notifyMouseMove(int mouse_x, int mouse_y)
{
	//printf("Mouse Move\n");
}

void managers::SceneManager::notifyMouseClick(int button, int state, int mouse_x, int mouse_y)
{
	//printf("Mouse Click\n");
}

void managers::SceneManager::notifyMouseScroll(int wheel, int direction, int mouse_x, int mouse_y)
{
	//printf("Mouse Scroll\n");
}
/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#pragma once

#include "Init_GLUT.h"
#include "SceneManager.h"
#include "WindowsManager.h"
#include "VertexFormat.h"

using namespace rendering::formats;

void windowMain(managers::SceneManager *scene)
{
	scene->getShaderManager()->createProgram("colorShader",
		"Resource Files\\Shader Files\\Vertex_Shader.glsl",
		"Resource Files\\Shader Files\\Fragment_Shader.glsl");

	managers::SceneManager::scene_manager = scene;

	scene->getModelManager()->createModel(new rendering::models::LightSource(), "light_source", scene->getShaderManager()->getProgram("colorShader"));
	scene->getModelManager()->createModel(new rendering::models::Circle(), "circle", scene->getShaderManager()->getProgram("colorShader"));
	scene->getModelManager()->createModel(new rendering::models::Circle2(), "circle2", scene->getShaderManager()->getProgram("colorShader"));
	scene->getModelManager()->createModel(new rendering::models::Circle3(), "circle3", scene->getShaderManager()->getProgram("colorShader"));
	scene->getModelManager()->createModel(new rendering::models::CustomModel_1(), "custom_model_1", scene->getShaderManager()->getProgram("colorShader"));
	scene->getModelManager()->createModel(new rendering::models::CustomModel_2(), "custom_model_2", scene->getShaderManager()->getProgram("colorShader"));
	scene->getModelManager()->createModel(new rendering::models::Triangle(), "triangle", scene->getShaderManager()->getProgram("colorShader"));
	scene->getModelManager()->createModel(new rendering::models::Parallelogram(), "parallelogram", scene->getShaderManager()->getProgram("colorShader"));
	scene->getModelManager()->createModel(new rendering::models::CustomModel_3(), "custom_model_3", scene->getShaderManager()->getProgram("colorShader"));
	scene->getModelManager()->createModel(new rendering::models::Rectangle(), "rectangle", scene->getShaderManager()->getProgram("colorShader"));
	scene->getModelManager()->createModel(new rendering::models::Rectangle2(), "rectangle2", scene->getShaderManager()->getProgram("colorShader"));
	scene->getModelManager()->createModel(new rendering::models::Star(), "star", scene->getShaderManager()->getProgram("colorShader"));
	scene->getModelManager()->createModel(new rendering::models::Heptagon(), "heptagon", scene->getShaderManager()->getProgram("colorShader"));
	scene->getModelManager()->createModel(new rendering::models::Heptagon2(), "heptagon2", scene->getShaderManager()->getProgram("colorShader"));
	scene->getModelManager()->createModel(new rendering::models::Square(), "square", scene->getShaderManager()->getProgram("colorShader"));
	scene->getModelManager()->createModel(new rendering::models::Camera(), "camera", scene->getShaderManager()->getProgram("colorShader"));

	managers::CollisionManager::addSceneLine(new VertexFormat(glm::vec4(1.0, 1.0, 0.0, 1.0), glm::vec4(0.0, 0.0, 0.0, 1.0)), new VertexFormat(glm::vec4(-1.0, 1.0, 0.0, 1.0), glm::vec4(0.0, 0.0, 0.0, 1.0)));
	managers::CollisionManager::addSceneLine(new VertexFormat(glm::vec4(-1.0, 1.0, 0.0, 1.0), glm::vec4(0.0, 0.0, 0.0, 1.0)), new VertexFormat(glm::vec4(-1.0, -1.0, 0.0, 1.0), glm::vec4(0.0, 0.0, 0.0, 1.0)));
	managers::CollisionManager::addSceneLine(new VertexFormat(glm::vec4(-1.0, -1.0, 0.0, 1.0), glm::vec4(0.0, 0.0, 0.0, 1.0)), new VertexFormat(glm::vec4(1.0, -1.0, 0.0, 1.0), glm::vec4(0.0, 0.0, 0.0, 1.0)));
	managers::CollisionManager::addSceneLine(new VertexFormat(glm::vec4(1.0, -1.0, 0.0, 1.0), glm::vec4(0.0, 0.0, 0.0, 1.0)), new VertexFormat(glm::vec4(1.0, 1.0, 0.0, 1.0), glm::vec4(0.0, 0.0, 0.0, 1.0)));

}


int main(int argc, char **argv)
{
	core::info::WindowInfo window(std::string("OpenGL Window"), 0, 0, 800, 600, true);
	core::info::ContextInfo context(3, 3, true);
	core::info::FramebufferInfo frameBufferInfo(true, true, true, true);

	managers::windows::WindowsManager::create("window1", window, context, frameBufferInfo, windowMain);


	return 0;
}
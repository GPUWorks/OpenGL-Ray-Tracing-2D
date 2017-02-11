/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#include "WindowsManager.h"
#include "FramebufferInfo.h"
#include "WindowInfo.h"
#include "ContextInfo.h"
#include "IListener.h"
#include "KeyListener.h"
#include "Init_GLUT.h"


std::map<std::string, managers::SceneManager*> managers::windows::WindowsManager::windowsList;
int managers::windows::WindowsManager::fps = 0;
int managers::windows::WindowsManager::current_frame_no = 0;

managers::windows::WindowsManager::~WindowsManager() {}

void managers::windows::WindowsManager::create(
	const std::string name,
	const core::info::WindowInfo &window,
	const core::info::ContextInfo &context,
	const core::info::FramebufferInfo &frameBufferInfo,
	void (*windowMain) (SceneManager*)
	)
{
	core::init::Init_GLUT::init(window, context, frameBufferInfo);

	SceneManager *scene_manager = new SceneManager();

	core::listeners::IListener *scene_listener = scene_manager;
	core::listeners::KeyListener *key_listener = scene_manager;

	core::init::Init_GLUT::setWindowListener(scene_listener);
	core::init::Init_GLUT::setKeyListener(key_listener);

	(*windowMain)(scene_manager);

	core::init::Init_GLUT::run();

	delete scene_manager;
}

managers::SceneManager* managers::windows::WindowsManager::getWindow(const std::string name)
{
	return windowsList.at(name);
}
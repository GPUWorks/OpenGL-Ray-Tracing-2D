/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#pragma once

#include <string>
#include <map>
#include <string>

#include <../Header Files/SceneManager.h>
#include <../Header Files/FramebufferInfo.h>
#include <../Header Files/WindowInfo.h>
#include <../Header Files/ContextInfo.h>

namespace managers
{
	namespace windows
	{
		class WindowsManager
		{
			public:
				~WindowsManager();

				static int fps;
				static int current_frame_no;

				static void create(
					const std::string name,
					const core::info::WindowInfo &window,
					const core::info::ContextInfo &context,
					const core::info::FramebufferInfo &frameBufferInfo,
					void(*windowMain)(SceneManager*)
					);

				static managers::SceneManager* getWindow(const std::string name);

			private:
				static std::map<std::string, managers::SceneManager*> windowsList;

		};
	}
}
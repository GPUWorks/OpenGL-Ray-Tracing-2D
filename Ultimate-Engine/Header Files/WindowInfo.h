/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#pragma once

#include <string>


namespace core
{
	namespace info
	{
		class WindowInfo
		{
			std::string name;
			int width, height;
			int x_position, y_position;
			bool reshapable;

			public:
				WindowInfo();
				WindowInfo(std::string name,
					int position_x, int start_position_y,
					int width, int height,
					bool reshapable);
				WindowInfo(const WindowInfo& windowInfo);
				void operator=(const WindowInfo& windowInfo);

				void setWidth(int width);
				void setHeight(int height);

				std::string getName() const;
				int getWidth() const;
				int getHeight() const;
				int get_X_position() const;
				int get_Y_position() const;
				bool isReshapable() const;
		};
	}
}
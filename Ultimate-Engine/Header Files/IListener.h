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
		class IListener
		{
			public:

				virtual ~IListener() = 0;

				//drawing functions
				virtual void notifyBeginFrame() = 0;
				virtual void notifyDisplayFrame() = 0;
				virtual void notifyEndFrame() = 0;
				virtual void notifyReshape(
					int width,
					int height,
					int previous_width,
					int previous_height) = 0;
		};

		inline IListener::~IListener() { }
	}
}

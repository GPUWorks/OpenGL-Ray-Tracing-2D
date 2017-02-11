/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#pragma once


namespace core
{
	namespace info
	{
		class FramebufferInfo
		{
			unsigned int flags;
			bool msaa;

			public:
				FramebufferInfo();
				FramebufferInfo(bool color, bool depth, bool stencil, bool msaa);
				FramebufferInfo(const FramebufferInfo& framebufferInfo);
				void operator=(const FramebufferInfo& info);

				unsigned int getFlags() const;
				bool isUsingMsaa() const;
		};
	}
}
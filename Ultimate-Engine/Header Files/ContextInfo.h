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
		class ContextInfo
		{
			int major_version, minor_version;
			bool use_context_core;
		
			public:
				ContextInfo();
				ContextInfo(int major_version, int minor_version, bool use_core_functions);
				ContextInfo(const ContextInfo& windowInfo);
				void operator=(const ContextInfo &info);

				int getMajorVersion() const;
				int getMinorVersion() const;
				bool isUsingContextCore() const;
		};
	}
}
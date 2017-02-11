/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#include "ContextInfo.h"


core::info::ContextInfo::ContextInfo()
{
	major_version = 3;
	minor_version = 3;
	use_context_core = true;
}

core::info::ContextInfo::ContextInfo(int major_version, int minor_version, bool use_context_core)
{
	this->major_version = major_version;
	this->minor_version = minor_version;
	this->use_context_core = use_context_core;
}

core::info::ContextInfo::ContextInfo(const ContextInfo& windowInfo)
{
	major_version = windowInfo.major_version;
	minor_version = windowInfo.minor_version;
	use_context_core = windowInfo.use_context_core;
}

void core::info::ContextInfo::operator=(const ContextInfo &info)
{
	major_version = info.major_version;
	minor_version = info.minor_version;
	use_context_core = info.use_context_core;
}

int core::info::ContextInfo::getMajorVersion() const
{
	return major_version;
}

int core::info::ContextInfo::getMinorVersion() const
{
	return minor_version;
}

bool core::info::ContextInfo::isUsingContextCore() const
{
	return use_context_core;
}
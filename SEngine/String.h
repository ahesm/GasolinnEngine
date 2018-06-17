#pragma once

#include<string>

namespace gfunc
{
	class String
	{
	public:
		static std::string *Split(std::string strTarget, std::string strTok);
	};
}
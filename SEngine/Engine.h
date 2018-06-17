#pragma once

#include<string>
#include<SDL.h>

#include"Structs.h"

using namespace std;

namespace gasolinn
{
	class Engine
	{
	public:
		static int On(std::string title, Size size);
		static int On(std::string title, int width, int height);
		static int On(std::string title, Size size, Uint32 win_state);
		static int On(std::string title, int width, int height, int win_state);
		static int Run();
		static void Release();
	};
};
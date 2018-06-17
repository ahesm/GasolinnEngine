#pragma once

namespace gasolinn
{
	class Timer
	{
	private:
		unsigned long startTick;
		bool isFirst = false;

	public:
		static Timer *Create();
		bool Tick(int interval);
		void Reset();

		void Release();

	};
}
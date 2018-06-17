#include "Timer.h"

#include "System.h"

namespace gasolinn
{
	Timer *Timer::Create()
	{
		auto timer = new Timer();

		return timer;
	}

	bool Timer::Tick(int interval)
	{
		if (!isFirst) {
			startTick = System::tick;
			isFirst = true;
		}
		if (System::tick - startTick >= interval) {
			startTick = System::tick;
			return true;
		}
		return false;
	}

	void Timer::Reset()
	{
		startTick = System::tick;
	}

	void Timer::Release()
	{
		delete this;
	}
}
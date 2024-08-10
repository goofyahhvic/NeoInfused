#if !defined(NEO_SCOPED_TIMER_HPP)
#define NEO_SCOPED_TIMER_HPP

#include "NeoInfused/neo_core.hpp"

namespace neo {
	class ScopedTimer {
	public:
		using OnDestroyFn = std::function<void(const char*, std::chrono::duration<double, std::milli>)>;
		ScopedTimer(const char* name = "Unnamed Timer", const OnDestroyFn& on_destroy = [](const char* name, std::chrono::duration<double, std::milli> time) { NEO_TRACE_LOG("{0}: {1}", name, time); });
		~ScopedTimer(void);
	private:
		const char* m_Name;
		std::chrono::high_resolution_clock::time_point m_Time;
		OnDestroyFn m_OnDestroy;
	};
	using ScopedTimerOnDestroyFn = ScopedTimer::OnDestroyFn;
}

#endif // NEO_SCOPED_TIMER_HPP
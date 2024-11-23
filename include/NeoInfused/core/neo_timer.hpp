#if !defined(NEO_TIMER_HPP)
#define NEO_TIMER_HPP

#include "NeoInfused/neo_core.hpp"

#define NEO_TIMER_REGULAR(type, ...) neo::timer::callfn_t<type> timer([](int64_t duration) { NEO_TRACE_LOG(__VA_ARGS__); })
#define NEO_TIMER_SCOPED(type, ...)  neo::timer::scoped_t<type> timer([](int64_t duration) { NEO_TRACE_LOG(__VA_ARGS__); })

namespace neo {
	namespace timer {
		using time_point_t = std::chrono::high_resolution_clock::time_point;
		using log_fn = std::function<void(int64_t count)>;

		template<typename T = std::chrono::milliseconds>
		class callfn_t {
		public:
			inline callfn_t(const log_fn& log)
			: m_Start(std::chrono::high_resolution_clock::now()), m_Log(log) {}

			inline void time(void)
			{
				m_Log(std::chrono::duration_cast<T>(std::chrono::high_resolution_clock::now() - m_Start).count());
			}

		private:
			time_point_t m_Start;
			log_fn m_Log;
		};

		template<typename T = std::chrono::milliseconds>
		class scoped_t {
		public:
			inline scoped_t(const log_fn& log)
			: timer(log) {}

			inline ~scoped_t(void) { timer.time(); }
		private:
			callfn_t<T> timer;
		};
	}
}

#endif // NEO_TIMER_HPP
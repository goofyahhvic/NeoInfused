#if !defined(NEO_APP_HPP)
#define NEO_APP_HPP

#include "neo_window.hpp"
#include "neo_timer.hpp"

enum neo_app_system_type_t : uint8_t {
	NEO_SYSTEMTYPE_NONE = 0,
	NEO_SYSTEMTYPE_INIT,
	NEO_SYSTEMTYPE_SHUTDOWN,
	NEO_SYSTEMTYPE_UPDATE,
	NEO_SYSTEMTYPE_DRAW,
	NEO_SYSTEMTYPE_ONEVENT
};

namespace neo {
	namespace app {
		using system_type_t = neo_app_system_type_t;

		struct systems_t {
			neo::array_list_t<void(*)(void)> init;
			neo::array_list_t<void(*)(void)> shutdown;

			neo::array_list_t<void(*)(void)> update;
			neo::array_list_t<void(*)(void)> draw;
			neo::array_list_t<void(*)(event_t&)> on_event;
		};

		class app_t {
		public:
		public:
			inline app_t(void) { Init(); };
			inline ~app_t(void) noexcept(false) { Shutdown(); }
			void run(void);

			void add_system(system_type_t type, void* fn);
			inline const systems_t& systems(void) const { return m_Systems; }
		public:
			bool should_close = false;
		private:
			systems_t m_Systems;
		};
	} // namespace app 
	using app_t = app::app_t;
} // namespace neo

#endif // NEO_APP_HPP
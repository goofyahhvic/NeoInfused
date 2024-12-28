#if !defined(NEO_APP_HPP)
#define NEO_APP_HPP

#include "../neo_window.hpp"
#include "../neo_timer.hpp"

enum neo_app_subsystem_type_t : uint8_t {
	NEO_APP_SUBSYSTEM_TYPE_NONE = 0,
	NEO_APP_SUBSYSTEM_TYPE_INIT,
	NEO_APP_SUBSYSTEM_TYPE_SHUTDOWN,
	NEO_APP_SUBSYSTEM_TYPE_UPDATE,
	NEO_APP_SUBSYSTEM_TYPE_ON_EVENT
};

namespace neo {
	namespace app {
		using subsystem_type_t = neo_app_subsystem_type_t;

		struct subsystems_t {
			neo::array_list_t<void(*)(void)> init;
			neo::array_list_t<void(*)(void)> shutdown;

			neo::array_list_t<void(*)(void)> update;
			neo::array_list_t<void(*)(event_t&)> on_event;
		};

		class app_t;

		inline app_t* g_Instance = nullptr;

		class app_t {
		public:
			inline app_t(void) { g_Instance = this; };
			inline ~app_t(void) noexcept(false) { g_Instance = nullptr; }
			void run(void);

			void add_system(subsystem_type_t type, void* fn);
		public:
			bool should_close = false;
			subsystems_t subsystems;
		};
	} // namespace app 
	using app_t = app::app_t;
} // namespace neo

#endif // NEO_APP_HPP
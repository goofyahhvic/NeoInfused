#if !defined(NEO_APP_HPP)
#define NEO_APP_HPP

#include "../data_structures/neo_layer-storage.hpp"
#include "neo_window.hpp"

namespace neo {
	class app_t {
	public:
		typedef bool (*loop_condition_fn)(void);
	public:
		app_t(loop_condition_fn loop_condition = [](void) -> bool { return !app_t::Get().windows.empty(); });
		~app_t(void) noexcept(false);
		void run(void);

		[[nodiscard]] static app_t& Get(void);

		template<typename... _Args>
		inline window_t* create_window(_Args&&... __args) { return windows.emplace_back(std::forward<_Args>(__args)...); }

		inline bool destroy_window(window_t* window) { return windows.pop(window); }
	public:
		loop_condition_fn loop_condition;
		window::storage_t windows;
		event::queue_t event_queue;
		layer::storage_t layers;
	};

	[[nodiscard]] inline window::storage_t& GetWindows(void) { return app_t::Get().windows; }
	[[nodiscard]] inline layer::storage_t&  GetLayers(void) { return app_t::Get().layers; }
	[[nodiscard]] inline event::queue_t&    GetEventQueue(void) { return app_t::Get().event_queue; }
}

#endif // NEO_APP_HPP
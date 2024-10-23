#if !defined(INF_LOADER_HPP)
#define INF_LOADER_HPP

#include "inf_core.hpp"

#define INF_API_NONE 0
#define INF_API_VULKAN 1

#include "inf_error.hpp"

namespace inf {
	namespace Loader {
		void Load(renderer_api_t api);
		inline void Unload(void) { Loader::Load(INF_API_NONE); };

		typedef void (*init_api_fn)(void);
		inline init_api_fn init_api = nullptr;

		typedef void (*shutdown_api_fn)(void);
		inline shutdown_api_fn shutdown_api = nullptr;

		struct window_surface_t;

		typedef window_surface_t* (*create_window_surface_fn)(GLFWwindow* window);
		inline create_window_surface_fn create_window_surface = nullptr;

		typedef void (*destroy_window_surface_fn)(window_surface_t* surface);
		inline destroy_window_surface_fn destroy_window_surface = nullptr;

		typedef void (*set_error_callback_fn)(error::callback_fn error_callback);
		inline set_error_callback_fn set_error_callback = nullptr;

		inline renderer_api_t renderer_api = INF_API_NONE;
		inline void* current_library = nullptr;
	};

	inline bool g_Initialized = false;
	inline void InitializeAPI(void) { Loader::init_api(); g_Initialized = true; }
	inline void ShutdownAPI(void) { g_Initialized = false; Loader::shutdown_api(); }
} // namespace inf

#endif // INF_LOADER_HPP
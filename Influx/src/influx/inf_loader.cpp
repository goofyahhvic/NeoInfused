#include "inf_pch.hpp"
#include "influx/inf_loader.hpp"

namespace inf {
#if defined(NEO_PLATFORM_WINDOWS)
	#define LOAD_LIBRARY(x) current_library = LoadLibraryA(x ".dll")
	#define UNLOAD_LIBRARY() FreeLibrary((HMODULE)current_library)
	#define GET_FN(x) GetProcAddress((HMODULE)current_library, x)
#elif defined(NEO_PLATFORM_LINUX)
	#define LOAD_LIBRARY(x) current_library = dlopen(std::format("{}/lib" x ".so", std::filesystem::canonical("/proc/self/exe").parent_path().string()).c_str(), RTLD_LAZY)
	#define UNLOAD_LIBRARY() dlclose(current_library)
	#define GET_FN(x) dlsym(current_library, x)
#endif

	void Loader::Load(renderer_api_t api)
	{
		renderer_api = INF_API_NONE;
		if (!api)
		{
			if (!current_library)
				return;

			init_api = nullptr;
			shutdown_api = nullptr;

			create_window_surface = nullptr;
			destroy_window_surface = nullptr;
			get_window_surface_size = nullptr;

			set_error_callback = nullptr;

			UNLOAD_LIBRARY();
			current_library = nullptr;
			return;
		}
		if (current_library)
			UNLOAD_LIBRARY();

		if (api == INF_API_VULKAN)
			LOAD_LIBRARY("Influx-vk-bin");
		else
			throw std::runtime_error("unknown rendering api requested!");

		NEO_ASSERT(current_library, "Could not load the requested renderer api library!");

		init_api = (init_api_fn)GET_FN("InitAPI");
		shutdown_api = (shutdown_api_fn)GET_FN("ShutdownAPI");

		create_window_surface   = (create_window_surface_fn)GET_FN("CreateWindowSurface");
		destroy_window_surface  = (destroy_window_surface_fn)GET_FN("DestroyWindowSurface");
		get_window_surface_size = (get_window_surface_size_fn)GET_FN("GetWindowSurfaceSize");

		set_error_callback = (set_error_callback_fn)GET_FN("SetErrorCallback");
		set_error_callback([](error::type_t type, const char* msg, void* data)
		{
			throw std::runtime_error(msg);
		});

		renderer_api = api;
	}
}

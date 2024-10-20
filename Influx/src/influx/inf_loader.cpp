#include "inf_pch.hpp"
#include "influx/inf_loader.hpp"

namespace inf {
#if defined(NEO_PLATFORM_WINDOWS)
	#define LOAD_LIBRARY(x) s_CurrentLibrary = LoadLibraryA(x ".dll")
	#define UNLOAD_LIBRARY() FreeLibrary((HMODULE)s_CurrentLibrary)
	#define GET_FN(x) GetProcAddress((HMODULE)s_CurrentLibrary, x)
#elif defined(NEO_PLATFORM_LINUX)
	#define LOAD_LIBRARY(x) s_CurrentLibrary = dlopen(std::format("{}/lib" x ".so", std::filesystem::canonical("/proc/self/exe").parent_path().string()).c_str(), RTLD_LAZY)
	#define UNLOAD_LIBRARY() dlclose(s_CurrentLibrary)
	#define GET_FN(x) dlsym(s_CurrentLibrary, x)
#endif

	void Loader::Load(RendererAPI api)
	{
		s_RendererAPI = INF_API_NONE;
		if (!api)
		{
			if (!s_CurrentLibrary)
				return;

			init_api = nullptr;
			shutdown_api = nullptr;
			create_window_surface = nullptr;
			destroy_window_surface = nullptr;

			UNLOAD_LIBRARY();
			s_CurrentLibrary = nullptr;
			return;
		}
		if (s_CurrentLibrary)
			UNLOAD_LIBRARY();

		if (api == INF_API_VULKAN)
			LOAD_LIBRARY("Influx-vk-bin");
		else
			throw std::runtime_error("unknown rendering api requested!");

		NEO_ASSERT(s_CurrentLibrary, "Could not load the requested renderer api library!");

		init_api     =     (InitAPIFn)GET_FN("InitAPI");
		shutdown_api = (ShutdownAPIFn)GET_FN("ShutdownAPI");

		create_window_surface  =  (CreateWindowSurfaceFN)GET_FN("CreateWindowSurface");
		destroy_window_surface = (DestroyWindowSurfaceFN)GET_FN("DestroyWindowSurface");

		s_SetErrorCallback = (SetErrorCallbackFn)GET_FN("SetErrorCallback");
		s_SetErrorCallback([](ErrorType type, const char* msg, void* data)
		{
			throw std::runtime_error(msg);
		});

		s_RendererAPI = api;
	}
}

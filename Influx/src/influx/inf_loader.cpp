#include "inf_pch.hpp"
#include "influx/inf_loader.hpp"

namespace inf {
	void Loader::Load(renderer_api_t api)
	{
		switch (api)
		{
		case INF_API_NONE:
			lib.unload();
			return;
		case INF_API_VULKAN:
			lib.load(L"Influx-vk-bin");
			break;
		default:
			NEO_WARN_LOG("Unknown Renderering API requested!");
		}

		init_api = lib.fn<init_api_fn>("InitAPI");
		shutdown_api = lib.fn<shutdown_api_fn>("ShutdownAPI");

		build_shader = lib.fn<build_shader_fn>("BuildShader");
		set_shader_output_dir = lib.fn<set_shader_output_dir_fn>("SetShaderOutputDir");

		create_window_surface   = lib.fn<create_window_surface_fn>("CreateWindowSurface");
		destroy_window_surface  = lib.fn<destroy_window_surface_fn>("DestroyWindowSurface");
		get_window_surface_size = lib.fn<get_window_surface_size_fn>("GetWindowSurfaceSize");

		if (set_error_callback = lib.fn<set_error_callback_fn>("SetErrorCallback"))
			set_error_callback([](error::type_t type, const char* msg, void* data)
			{
				// temporary... although it's been like this since
				// the addition of the error callback :p
				throw std::runtime_error(msg);
			});

		renderer_api = api;
	}
}

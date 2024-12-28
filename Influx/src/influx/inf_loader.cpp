#include "inf_pch.hpp"
#include "influx/inf_loader.hpp"

namespace inf {
	void Loader::Load(renderer_api_t api)
	{
		switch (api)
		{
		case INF_API_NONE:
			m_Lib.unload();
			return;
		case INF_API_VULKAN:
			m_Lib.load(L"Influx-vk-bin");
			break;
		default:
			NEO_WARN_LOG("Unknown Renderering API requested!");
		}

		m_InitAPI = m_Lib.fn<init_api_fn>("InitAPI");
		m_ShutdownAPI = m_Lib.fn<shutdown_api_fn>("ShutdownAPI");
		
		create_shader = m_Lib.fn<create_shader_fn>("CreateShader");
		destroy_shader = m_Lib.fn<destroy_shader_fn>("DestroyShader");

		create_graphics_pipeline = m_Lib.fn<create_graphics_pipeline_fn>("CreateGraphicsPipeline");
		destroy_graphics_pipeline = m_Lib.fn<destroy_graphics_pipeline_fn>("DestroyGraphicsPipeline");

		attach_shader_to_pipeline = m_Lib.fn<attach_shader_to_pipeline_fn>("AttachShaderToPipeline");
		attach_shaders_to_pipeline = m_Lib.fn<attach_shaders_to_pipeline_fn>("AttachShadersToPipeline");
		init_graphics_pipeline = m_Lib.fn<init_shader_pipeline_fn>("InitGraphicsPipeline");

		set_shader_output_dir = m_Lib.fn<set_shader_output_dir_fn>("SetShaderOutputDir");
		set_shader_compiler_path = m_Lib.fn<set_shader_compiler_path_fn>("SetShaderCompilerPath");

		create_window_surface   = m_Lib.fn<create_window_surface_fn>("CreateWindowSurface");
		destroy_window_surface  = m_Lib.fn<destroy_window_surface_fn>("DestroyWindowSurface");
		get_window_surface_size = m_Lib.fn<get_window_surface_size_fn>("GetWindowSurfaceSize");

		if (m_SetErrorCallback = m_Lib.fn<set_error_callback_fn>("SetErrorCallback"))
			m_SetErrorCallback([](error::type_t type, const char* msg, void* data)
			{
				// temporary... although it's been like this since
				// the addition of the error callback :p
				throw std::runtime_error(msg);
			});

		m_RendererApi = api;
	}
}

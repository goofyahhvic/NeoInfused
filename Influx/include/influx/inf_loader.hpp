#if !defined(INF_LOADER_HPP)
#define INF_LOADER_HPP

#include "inf_core.hpp"

#define INF_API_NONE 0
#define INF_API_VULKAN 1

#include "inf_error.hpp"
#include "NeoInfused/core/neo_dynamic-library.hpp"

namespace inf {
	using neo::dll_t;
	namespace Loader {
		void Load(renderer_api_t api);
		inline void Unload(void) { Loader::Load(INF_API_NONE); };

	// window_surface
		struct window_surface_t;

		typedef window_surface_t* (*create_window_surface_fn)(GLFWwindow* window);
		inline create_window_surface_fn create_window_surface = nullptr;

		typedef void (*destroy_window_surface_fn)(window_surface_t* surface);
		inline destroy_window_surface_fn destroy_window_surface = nullptr;

		typedef const glm::uvec2* (*get_window_surface_size_fn)(window_surface_t* surface);
		inline get_window_surface_size_fn get_window_surface_size = nullptr;

	// shader
		using shader_handle_t = uint64_t;

		typedef shader_handle_t (*create_shader_fn)(const std::filesystem::path& filename, shader::stage_t stage);
		inline create_shader_fn create_shader = nullptr;

		typedef void (*destroy_shader_fn)(shader_handle_t handle);
		inline destroy_shader_fn destroy_shader = nullptr;

		struct shader_pipeline_t;
		
		typedef shader_pipeline_t* (*create_shader_pipeline_fn)(window_surface_t* surface);
		inline create_shader_pipeline_fn create_shader_pipeline = nullptr;

		typedef void (*destroy_shader_pipeline_fn)(shader_pipeline_t* pipeline);
		inline destroy_shader_pipeline_fn destroy_shader_pipeline = nullptr;

		typedef void (*attach_shader_to_pipeline_fn)(shader_pipeline_t* pipeline, shader_handle_t);
		inline attach_shader_to_pipeline_fn attach_shader_to_pipeline = nullptr;

		typedef void (*attach_shaders_to_pipeline_fn)(shader_pipeline_t* pipeline, const std::initializer_list<shader_handle_t>& shaders);
		inline attach_shaders_to_pipeline_fn attach_shaders_to_pipeline = nullptr;

		typedef void (*init_shader_pipeline_fn)(shader_pipeline_t* pipeline);
		inline init_shader_pipeline_fn init_shader_pipeline = nullptr;

		typedef void (*set_shader_output_dir_fn)(std::filesystem::path&& dir);
		inline set_shader_output_dir_fn set_shader_output_dir = nullptr;

		typedef void (*set_shader_compiler_path_fn)(std::filesystem::path&& glslc);
		inline set_shader_compiler_path_fn set_shader_compiler_path = nullptr;

	// private
		typedef void (*init_api_fn)(void);
		inline init_api_fn m_InitAPI = nullptr;

		typedef void (*shutdown_api_fn)(void);
		inline shutdown_api_fn m_ShutdownAPI = nullptr;
		
		typedef void (*set_error_callback_fn)(error::callback_fn error_callback);
		inline set_error_callback_fn m_SetErrorCallback = nullptr;

		inline renderer_api_t m_RendererApi = INF_API_NONE;
		inline dll_t m_Lib;
	};

	inline bool g_Initialized = false;
	inline void InitializeAPI(void) { Loader::m_InitAPI(); g_Initialized = true; }
	inline void ShutdownAPI(void) { g_Initialized = false; Loader::m_ShutdownAPI(); }
} // namespace inf

#endif // INF_LOADER_HPP
#if !defined(VK_SHADER_HPP)
#define VK_SHADER_HPP

#include "vk_core.hpp"
#include "vk_window-surface.hpp"

namespace vk {
	namespace shader {
		using stage_t = inf::shader::stage_t;
		VkShaderStageFlagBits StageToVkType(stage_t stage);

		using shader_t = VkPipelineShaderStageCreateInfo;
		using handle_t = uint64_t;

		struct pipeline_t {
			window_surface_t* surface;
			neo::array_list_t<handle_t> handles;
		};

		void Compile(const std::filesystem::path& shader_file);
		neo::bytes_t Load(const std::filesystem::path& shader_filename);

		VkShaderModule CreateModule(const std::filesystem::path& shader_file);

		handle_t Create(const std::filesystem::path& filename, stage_t stage);
		void Destroy(handle_t shader);

		pipeline_t* CreatePipeline(window_surface_t* surface);
		void AttachToPipeline(pipeline_t* pipeline, handle_t shader);
		void AttachToPipeline_M(pipeline_t* pipeline, const std::initializer_list<handle_t>& shaders);
		void InitPipeline(pipeline_t* pipeline);
		void DestroyPipeline(pipeline_t* pipeline);

		inline std::filesystem::path g_OutputDir;
		inline std::filesystem::path g_Compiler;

		inline neo::array_list_t<shader_t> g_Shaders;
	} // namespace shader
	using shader_t = shader::shader_t;
	using shader_handle_t = shader::handle_t;
	using shader_create_info_t = shader::create_info_t;
	using shader_pipeline_t = shader::pipeline_t;
} // namespace vk

#endif // VK_SHADER_HPP
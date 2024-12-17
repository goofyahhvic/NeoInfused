#include "vk_pch.hpp"
#include "vk_shader.hpp"

namespace vk {
	void shader::Build(const std::filesystem::path& shader_file)
	{
		if (g_OutputDir.empty())
		{
			INFVK_WARN_LOG("No shader output directory defined! Using executable directory.");
			g_OutputDir = GetExecPath().parent_path();
		}

		std::string shader_file_str = shader_file.lexically_normal().string();
		std::filesystem::path output = g_OutputDir / shader_file.filename().replace_extension(".spv");

		INFVK_TRACE_LOG("Building {} to {}", shader_file_str.c_str(), g_OutputDir.C_STR());

	#if defined(NEO_PLATFORM_WINDOWS)
		char* vulkan_sdk = getenv("VULKAN_SDK");
		if (!vulkan_sdk)
		{
			g_ErrorCallback(INF_ERROR_NONE, "No VULKAN_SDK environment variable defined!", nullptr);
			return;
		}
		system(std::format("{}/Bin/glslc.exe {} -o {}", vulkan_sdk, shader_file_str.c_str(), output.C_STR()).c_str());
	#elif defined(NEO_PLATFORM_LINUX)
		system(std::format("glslc {} -o {}", shader_file_str.c_str(), output.c_str()).c_str());
	#endif 
	}
} // namespace vk

EXPORT_FN void BuildShader(const std::filesystem::path& shader_file) { vk::shader::Build(shader_file); }
EXPORT_FN void SetShaderOutputDir(std::filesystem::path&& dir) { vk::shader::g_OutputDir = dir; }

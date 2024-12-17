#include "vk_pch.hpp"
#include "vk_shader.hpp"

namespace vk {
	void shader::Build(const std::filesystem::path& shader_file)
	{
		if (g_ShaderCompiler.empty())
		{
		#if defined(NEO_PLATFORM_WINDOWS)
			g_ShaderCompiler = std::filesystem::path(g_VulkanSDK) / "Bin/glslc.exe";
		#elif defined(NEO_PLATFORM_LINUX)
			g_ShaderCompiler = "glslc";
		#endif
			INFVK_WARN_LOG("No shader compiler path defined! Using {}", g_ShaderCompiler.C_STR());
		}

		if (g_OutputDir.empty())
		{
			g_OutputDir = GetExecPath().parent_path();
			INFVK_WARN_LOG("No shader output directory defined! Using {}", g_OutputDir.C_STR());
		}

		std::string shader_file_str = shader_file.lexically_normal().string();
		std::filesystem::path output = g_OutputDir / shader_file.filename().replace_extension(".spv");

		INFVK_TRACE_LOG("Building {} to {}", shader_file_str.c_str(), g_OutputDir.C_STR());
		system(std::format("{} {} -o {}", g_ShaderCompiler.C_STR(), shader_file_str.c_str(), output.C_STR()).c_str());
	}
} // namespace vk

EXPORT_FN void BuildShader(const std::filesystem::path& shader_file) { vk::shader::Build(shader_file); }
EXPORT_FN void SetShaderOutputDir(std::filesystem::path&& dir) { vk::shader::g_OutputDir = dir; }
EXPORT_FN void SetShaderCompilerPath(std::filesystem::path&& path) { vk::shader::g_ShaderCompiler = path; }

#include "vk_pch.hpp"
#include "vk_shader.hpp"

//#include <shaderc/shaderc.hpp>

namespace vk {
	VkShaderStageFlagBits shader::StageToVkType(shader::stage_t stage)
	{
		switch (stage)
		{
		case INF_SHADER_STAGE_VERTEX:   return VK_SHADER_STAGE_VERTEX_BIT;
		case INF_SHADER_STAGE_FRAGMENT: return VK_SHADER_STAGE_FRAGMENT_BIT;
		}
		return VK_SHADER_STAGE_FLAG_BITS_MAX_ENUM;
	}

	void shader::Compile(const std::filesystem::path& shader_file)
	{
		if (g_Compiler.empty())
		{
		#if defined(NEO_PLATFORM_WINDOWS)
			g_Compiler = std::filesystem::path(g_VulkanSDK) / "Bin\\glslc.exe";
		#elif defined(NEO_PLATFORM_LINUX)
			g_Compiler = "glslc";
		#endif
			INFVK_WARN_LOG("No shader compiler path defined! Using {}", g_Compiler.C_STR());
		}

		if (g_OutputDir.empty())
		{
			g_OutputDir = GetExecPath().parent_path();
			INFVK_WARN_LOG("No shader output directory defined! Using {}", g_OutputDir.C_STR());
		}

		std::string shader_file_str = shader_file.lexically_normal().string();
		std::filesystem::path output = g_OutputDir / shader_file.filename().replace_extension(".spv");

		if (!std::filesystem::exists(output)
		|| std::filesystem::last_write_time(output)
		< std::filesystem::last_write_time(shader_file))
		{
			INFVK_TRACE_LOG("Building {} to {}", shader_file_str.c_str(), g_OutputDir.C_STR());
			system(std::format("{} {} -o {}", g_Compiler.C_STR(), shader_file_str.c_str(), output.C_STR()).c_str());
		}
	}

	neo::bytes_t shader::Load(const std::filesystem::path& shader_filename)
	{
		std::filesystem::path shader_path = g_OutputDir / shader_filename;
		std::ifstream file(shader_path, std::ios::ate | std::ios::binary);
		if (!file.is_open())
		{
			g_ErrorCallback(
				INF_ERROR_NONE,
				std::format("Failed to open file {}", shader_path.C_STR()).c_str(),
				nullptr
			);
			return {};
		}

		size_t size = file.tellg();
		neo::bytes_t file_data(size);

		file.seekg(0);
		file.read(file_data.ptr(), size);
		file.close();

		return file_data;
	}

	VkShaderModule shader::CreateModule(const std::filesystem::path& shader_file)
	{
		VkShaderModuleCreateInfo create_info{};
		create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;

		shader::Compile(shader_file);
		neo::bytes_t code = shader::Load(shader_file.filename().replace_extension(".spv"));
		while (code.size() % 4)
			code.emplace(0);

		create_info.codeSize = code.size();
		create_info.pCode = (uint32_t*)code.ptr();

		VkShaderModule module = VK_NULL_HANDLE;
		if (vkCreateShaderModule(core::g_LogicalDevice, &create_info, nullptr, &module) != VK_SUCCESS)
		{
			g_ErrorCallback(INF_OBJECT_CREATION_FAILURE, "Failed to create shader module!", nullptr);
			return VK_NULL_HANDLE;
		}

		return module;
	}

	shader::handle_t shader::Create(const shader::create_info_t& info)
	{
		shader::handle_t shader = shader::g_Shaders.emplace();
		g_Shaders[shader].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;

		g_Shaders[shader].module = shader::CreateModule(info.filename);
		if (!g_Shaders[shader].module)
			return NEO_INVALID_HANDLE;

		g_Shaders[shader].stage = shader::StageToVkType(info.stage);
		g_Shaders[shader].pName = "main";

		g_Shaders[shader].pSpecializationInfo = nullptr;
		g_Shaders[shader].pName = nullptr;
		g_Shaders[shader].flags = 0;

		return shader;
	}

	void shader::Destroy(shader::handle_t shader)
	{
		vkDestroyShaderModule(core::g_LogicalDevice, g_Shaders[shader].module, nullptr);
		memset(g_Shaders.ptr() + shader, 0, sizeof(shader_t));

		if (shader == g_Shaders.size() - 1)
			g_Shaders.resize(g_Shaders.size() - 1);
	}

	static VkPipelineDynamicStateCreateInfo dynamicStateInfo(const neo::array_vec_t<VkDynamicState>& states)
	{
		VkPipelineDynamicStateCreateInfo dynamic_state_info{};
		dynamic_state_info.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamic_state_info.dynamicStateCount = (uint32_t)states.size();
		dynamic_state_info.pDynamicStates = states.ptr();
		return dynamic_state_info;
	}

	static VkPipelineViewportStateCreateInfo viewportInfo(void)
	{
		VkPipelineViewportStateCreateInfo viewport_state_info{};
		viewport_state_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewport_state_info.viewportCount = 1;
		viewport_state_info.scissorCount = 1;
		return viewport_state_info;
	}

	static VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo(void)
	{
		VkPipelineInputAssemblyStateCreateInfo input_assembly_info{};
		input_assembly_info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		input_assembly_info.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		input_assembly_info.primitiveRestartEnable = VK_FALSE;
		return input_assembly_info;
	}

	static VkPipelineVertexInputStateCreateInfo vertexInputInfo(void)
	{
		VkPipelineVertexInputStateCreateInfo vertex_input_info{};
		vertex_input_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

		vertex_input_info.vertexBindingDescriptionCount = 0;
		vertex_input_info.pVertexBindingDescriptions = nullptr;

		vertex_input_info.vertexAttributeDescriptionCount = 0;
		vertex_input_info.pVertexAttributeDescriptions = nullptr;
		return vertex_input_info;
	}

	static VkPipelineRasterizationStateCreateInfo rasterizationInfo(void)
	{
		VkPipelineRasterizationStateCreateInfo rasterization_info{};
		rasterization_info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;

		rasterization_info.depthClampEnable = VK_FALSE;
		rasterization_info.rasterizerDiscardEnable = VK_FALSE;

		rasterization_info.polygonMode = VK_POLYGON_MODE_FILL;
		rasterization_info.lineWidth = 1.0f;

		rasterization_info.cullMode = VK_CULL_MODE_BACK_BIT;
		rasterization_info.frontFace = VK_FRONT_FACE_CLOCKWISE;

		rasterization_info.depthBiasEnable = VK_FALSE;
		rasterization_info.depthBiasConstantFactor = 0.0f;
		rasterization_info.depthBiasClamp = 0.0f;
		rasterization_info.depthBiasSlopeFactor = 0.0f;
		return rasterization_info;
	}

	static VkPipelineColorBlendAttachmentState colorBlendAttachment(bool enabled)
	{
		VkPipelineColorBlendAttachmentState color_blend_attachment{};
		color_blend_attachment.colorWriteMask =
			VK_COLOR_COMPONENT_R_BIT |
			VK_COLOR_COMPONENT_G_BIT |
			VK_COLOR_COMPONENT_B_BIT |
			VK_COLOR_COMPONENT_A_BIT;

		if (enabled)
		{
			color_blend_attachment.blendEnable = VK_FALSE;

			color_blend_attachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
			color_blend_attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
			color_blend_attachment.colorBlendOp = VK_BLEND_OP_ADD;

			color_blend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
			color_blend_attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
			color_blend_attachment.alphaBlendOp = VK_BLEND_OP_ADD;
		} else
		{
			color_blend_attachment.blendEnable = VK_TRUE;

			color_blend_attachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
			color_blend_attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
			color_blend_attachment.colorBlendOp = VK_BLEND_OP_ADD;

			color_blend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
			color_blend_attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
			color_blend_attachment.alphaBlendOp = VK_BLEND_OP_ADD;
		}
		return color_blend_attachment;
	}

	static VkPipelineMultisampleStateCreateInfo multisampleInfo(bool enabled)
	{
		VkPipelineMultisampleStateCreateInfo multisample_info{};
		multisample_info.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;

		multisample_info.sampleShadingEnable = VK_FALSE;
		multisample_info.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
		multisample_info.minSampleShading = 1.0f;
		multisample_info.pSampleMask = nullptr;
		multisample_info.alphaToCoverageEnable = VK_FALSE;
		multisample_info.alphaToOneEnable = VK_FALSE;

		return multisample_info;
	}

	shader::pipeline_t* shader::CreatePipeline(window_surface_t* surface)
	{
		shader::pipeline_t* pipeline = neo::tmalloc<shader::pipeline_t>(1);
		pipeline->surface = surface;
		new (&pipeline->handles) neo::array_list_t<shader::handle_t>();

		return pipeline;
	}

	void shader::AttachToPipeline(shader::pipeline_t* pipeline, shader::handle_t handle)
	{
		pipeline->handles.emplace(handle);
	}

	void shader::AttachToPipeline_M(
		shader::pipeline_t* pipeline,
		const std::initializer_list<shader::handle_t>& handles)
	{
		if (pipeline->handles.free_space() < handles.size())
			pipeline->handles.reallocate(pipeline->handles.capacity() + handles.size());
		
		for (shader::handle_t handle : handles)
			pipeline->handles.emplace(handle);
	}

	void shader::InitPipeline(shader::pipeline_t* pipeline)
	{
		neo::array_vec_t<VkDynamicState> dynamic_states = {
			VK_DYNAMIC_STATE_VIEWPORT,
			VK_DYNAMIC_STATE_SCISSOR
		};
		VkPipelineDynamicStateCreateInfo dynamic_state_info = dynamicStateInfo(dynamic_states);
		VkPipelineViewportStateCreateInfo viewport_info = viewportInfo();
		VkPipelineInputAssemblyStateCreateInfo input_assembly_info = inputAssemblyInfo();
		VkPipelineVertexInputStateCreateInfo vertex_input_info = vertexInputInfo();
		VkPipelineRasterizationStateCreateInfo rasterization_info = rasterizationInfo();
		VkPipelineColorBlendAttachmentState color_blend_attachment = colorBlendAttachment(true);
		VkPipelineMultisampleStateCreateInfo multisample_info = multisampleInfo(true);

		//VkPipelineDepthStencilStateCreateInfo depth_stencil_create_info{};
	}

	void shader::DestroyPipeline(shader::pipeline_t* pipeline)
	{

		free(pipeline);
	}
} // namespace vk
using namespace vk;

EXPORT_FN shader::handle_t CreateShader(const shader::create_info_t& info)
{
	return shader::Create(info);
}

EXPORT_FN void DestroyShader(shader::handle_t shader)
{
	return shader::Destroy(shader);
}

EXPORT_FN shader::pipeline_t* CreateShaderPipeline(window_surface_t* surface)
{
	return shader::CreatePipeline(surface);
}

EXPORT_FN void AttachShaderToPipeline(
	shader::pipeline_t* pipeline,
	shader::handle_t shader)
{
	return shader::AttachToPipeline(pipeline, shader);
}

EXPORT_FN void AttachShadersToPipeline(
	shader::pipeline_t* pipeline,
	const std::initializer_list<shader::handle_t>& shaders)
{
	return shader::AttachToPipeline_M(pipeline, shaders);
}

EXPORT_FN void InitShaderPipeline(shader::pipeline_t* pipeline)
{
	return shader::InitPipeline(pipeline);
}

EXPORT_FN void DestroyShaderPipeline(shader::pipeline_t* pipeline)
{
	return shader::DestroyPipeline(pipeline);
}

EXPORT_FN void SetShaderOutputDir(const std::filesystem::path& dir)
{
	shader::g_OutputDir = dir;
}

EXPORT_FN void SetShaderCompilerPath(std::filesystem::path&& glslc)
{
	shader::g_Compiler = glslc;
}

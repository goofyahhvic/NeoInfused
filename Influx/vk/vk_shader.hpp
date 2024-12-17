#if !defined(VK_SHADER_HPP)
#define VK_SHADER_HPP

#include "vk_core.hpp"

namespace vk {
	namespace shader {
		void Build(const std::filesystem::path& shader_file);

		inline std::filesystem::path g_OutputDir;
	}
}

#endif // VK_SHADER_HPP
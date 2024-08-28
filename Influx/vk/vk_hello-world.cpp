#include "vk_pch.hpp"

EXPORT_FN uint32_t ExtensionCountE(void)
{
	uint32_t extension_count = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);
	return extension_count;
}
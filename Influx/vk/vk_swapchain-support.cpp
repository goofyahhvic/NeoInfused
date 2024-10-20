#include "vk_pch.hpp"
#include "vk_swapchain-support.hpp"

namespace vk {
	SwapchainSupport::SwapchainSupport(VkPhysicalDevice device, VkSurfaceKHR surface)
	: formats(0), present_modes(0)
	{
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &capabilities);

		uint32_t format_count;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &format_count, nullptr);

		if (format_count)
		{
			formats.reallocate(format_count, format_count);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &format_count, formats.ptr());
		}

		uint32_t present_mode_count;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &present_mode_count, nullptr);

		if (present_mode_count)
		{
			present_modes.reallocate(present_mode_count, present_mode_count);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &present_mode_count, present_modes.ptr());
			if (format_count)
				m_Supported = true;
		}
	}
}

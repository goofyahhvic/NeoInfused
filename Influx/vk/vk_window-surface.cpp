#include "vk_pch.hpp"
#include "vk_window-surface.hpp"

#include "vk_swapchain-support.hpp"

namespace vk {
	static VkSurfaceFormatKHR pickSurfaceFormat(const neo::array_list_t<VkSurfaceFormatKHR>& formats)
	{
		for (auto it = formats.begin(); it != formats.end(); it++)
			if (it->format == VK_FORMAT_R8G8B8A8_SRGB &&
				it->colorSpace == VK_COLORSPACE_SRGB_NONLINEAR_KHR)
				return *it;
		return formats[0];
	}

	static VkPresentModeKHR pickPresentMode(const neo::array_list_t<VkPresentModeKHR>& present_modes)
	{
		for (auto it = present_modes.begin(); it != present_modes.end(); it++)
			if (*it == VK_PRESENT_MODE_MAILBOX_KHR)
				return *it;
		return VK_PRESENT_MODE_FIFO_KHR;
	}

	static VkExtent2D pickResolution(const VkSurfaceCapabilitiesKHR& capabilities, int window_width, int window_height)
	{
		if (capabilities.currentExtent.width != UINT32_MAX)
			return capabilities.currentExtent;

		return {
			std::clamp<uint32_t>(window_width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width),
			std::clamp<uint32_t>(window_height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height),
		};
	}

	static std::tuple<VkSwapchainKHR, VkFormat, VkExtent2D> createSwapchain(GLFWwindow* window, VkSurfaceKHR surface, swapchain_support_t& swapchain_support)
	{
		std::tuple<VkSwapchainKHR, VkFormat, VkExtent2D> swapchain_info;
		auto&[swapchain, format, extent] = swapchain_info;

		int window_width = 0, window_height = 0;
		glfwGetWindowSize(window, &window_height, &window_height);

		VkSwapchainCreateInfoKHR create_info = {};
		create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		create_info.surface = surface;

		create_info.imageFormat = pickSurfaceFormat(swapchain_support.formats).format;
		format = create_info.imageFormat;

		create_info.imageExtent = pickResolution(swapchain_support.capabilities, window_width, window_height);
		extent = create_info.imageExtent;

		create_info.imageColorSpace = pickSurfaceFormat(swapchain_support.formats).colorSpace;

		create_info.imageArrayLayers = 1;
		create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		if (swapchain_support.capabilities.maxImageCount > 0 &&
			swapchain_support.capabilities.minImageCount + 1 > swapchain_support.capabilities.maxImageCount)
			create_info.minImageCount = swapchain_support.capabilities.maxImageCount;
		else 
			create_info.minImageCount = swapchain_support.capabilities.minImageCount + 1;

		QueueFamilyIndices indices = Core::GetQueueFamilies(Core::g_PhysicalDevice);
		uint32_t indices_arr[] = { indices.graphics, indices.present };

		if (indices.graphics != indices.present)
		{
			create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			create_info.queueFamilyIndexCount = 2;
			create_info.pQueueFamilyIndices = indices_arr;
		} else
		{
			create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		}

		create_info.preTransform = swapchain_support.capabilities.currentTransform;
		create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		create_info.presentMode = pickPresentMode(swapchain_support.present_modes);
		create_info.clipped = VK_TRUE;
		create_info.oldSwapchain = VK_NULL_HANDLE;

		if (vkCreateSwapchainKHR(Core::g_LogicalDevice, &create_info, nullptr, &swapchain) != VK_SUCCESS)
		{
			g_ErrorCallback(INF_ERROR_NONE, "Failed to create window surface!", nullptr);
			swapchain = nullptr;
		}

		return swapchain_info;
	}

	window_surface_t* CreateWindowSurface(GLFWwindow* window)
	{
		window_surface_t* _this = new window_surface_t;

		if (glfwCreateWindowSurface(Core::g_Instance, window, nullptr, &_this->surface) != VK_SUCCESS)
		{
			delete _this;
			g_ErrorCallback(INF_ERROR_NONE, "Failed to create window surface!", nullptr);
			return nullptr;
		}

		swapchain_support_t swapchain_support(Core::g_PhysicalDevice, _this->surface);
		if (!swapchain_support)
		{
			delete _this;
			g_ErrorCallback(INF_ERROR_NONE, "Swapchain is not compatible with window surface!", nullptr);
			return nullptr;
		}

		{
			auto[swapchain, format, extent] = createSwapchain(window, _this->surface, swapchain_support);
			_this->swapchain = swapchain;
			_this->format = format;
			_this->extent = extent;
		}

		uint32_t image_count;
		vkGetSwapchainImagesKHR(Core::g_LogicalDevice, _this->swapchain, &image_count, nullptr);
		_this->images.reallocate(image_count, image_count);
		vkGetSwapchainImagesKHR(Core::g_LogicalDevice, _this->swapchain, &image_count, _this->images.ptr());

		return _this;
	}

	void DestroyWindowSurface(window_surface_t* _this)
	{
		vkDestroySwapchainKHR(Core::g_LogicalDevice, _this->swapchain, nullptr);
		vkDestroySurfaceKHR(Core::g_Instance, _this->surface, nullptr);
		delete _this;
	}
}

EXPORT_FN vk::window_surface_t* CreateWindowSurface(GLFWwindow* window) { return vk::CreateWindowSurface(window); }
EXPORT_FN void DestroyWindowSurface(vk::window_surface_t* _this) { return vk::DestroyWindowSurface(_this); }

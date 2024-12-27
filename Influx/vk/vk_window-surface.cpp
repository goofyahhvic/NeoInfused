#include "vk_pch.hpp"
#include "vk_window-surface.hpp"

#include "vk_swapchain-support.hpp"

namespace vk {
	static VkSurfaceFormatKHR pickSurfaceFormat(const neo::array_list_t<VkSurfaceFormatKHR>& formats)
	{
		for (auto it = formats.begin(); it != formats.end(); it++)
			if (it->format == VK_FORMAT_R32G32B32A32_SFLOAT
			&& it->colorSpace == VK_COLOR_SPACE_ADOBERGB_NONLINEAR_EXT)
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

	struct swapchain_info_t
	{
		VkSwapchainKHR swapchain;
		VkSurfaceFormatKHR format;
		VkExtent2D extent;
	};

	static swapchain_info_t createSwapchain(GLFWwindow* window, VkSurfaceKHR surface, swapchain_support_t& swapchain_support)
	{
		swapchain_info_t swapchain_info{};
		swapchain_info.format = pickSurfaceFormat(swapchain_support.formats);

		int window_width = 0, window_height = 0;
		glfwGetWindowSize(window, &window_height, &window_height);

		VkSwapchainCreateInfoKHR create_info {};
		create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		create_info.surface = surface;

		create_info.imageFormat = swapchain_info.format.format;
		create_info.imageColorSpace = swapchain_info.format.colorSpace;

		create_info.imageExtent = pickResolution(swapchain_support.capabilities, window_width, window_height);
		swapchain_info.extent = create_info.imageExtent;

		create_info.imageArrayLayers = 1;
		create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		if (swapchain_support.capabilities.maxImageCount > 0
		&& swapchain_support.capabilities.minImageCount + 1 > swapchain_support.capabilities.maxImageCount)
			create_info.minImageCount = swapchain_support.capabilities.maxImageCount;
		else 
			create_info.minImageCount = swapchain_support.capabilities.minImageCount + 1;

		queue_family_indices_t indices = core::GetQueueFamilies(core::g_PhysicalDevice);
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

		if (vkCreateSwapchainKHR(core::g_LogicalDevice, &create_info, nullptr, &swapchain_info.swapchain) != VK_SUCCESS)
		{
			g_ErrorCallback(INF_OBJECT_CREATION_FAILURE, "Failed to create window surface!", nullptr);
			swapchain_info.swapchain = nullptr;
		}

		return swapchain_info;
	}

	window_surface_t* CreateWindowSurface(GLFWwindow* window)
	{
		window_surface_t* surface = new window_surface_t;
		memset(surface, 0, sizeof(window_surface_t));

		if (glfwCreateWindowSurface(core::g_Instance, window, nullptr, &surface->surface) != VK_SUCCESS)
		{
			delete surface;
			g_ErrorCallback(INF_OBJECT_CREATION_FAILURE, "Failed to create window surface!", nullptr);
			return nullptr;
		}

		swapchain_support_t swapchain_support(core::g_PhysicalDevice, surface->surface);
		if (!swapchain_support)
		{
			delete surface;
			g_ErrorCallback(INF_ERROR_NONE, "Swapchain is not compatible with window surface!", nullptr);
			return nullptr;
		}

		{
			swapchain_info_t swapchain_info = createSwapchain(window, surface->surface, swapchain_support);
			surface->swapchain = swapchain_info.swapchain;
			surface->format = swapchain_info.format.format;
			
			surface->size.x = swapchain_info.extent.width;
			surface->size.y = swapchain_info.extent.height;
			INFVK_TRACE_LOG("Created swapchain [ w: {}, h: {} ]", surface->size.x, surface->size.y);
		}

		uint32_t image_count;
		vkGetSwapchainImagesKHR(core::g_LogicalDevice, surface->swapchain, &image_count, nullptr);

		surface->images.reallocate(image_count, image_count);
		vkGetSwapchainImagesKHR(core::g_LogicalDevice, surface->swapchain, &image_count, surface->images.ptr());

		surface->image_views.reallocate(image_count, image_count);
		for (size_t i = 0; i < image_count; i++)
		{
			VkImageViewCreateInfo create_info{};
			create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			create_info.image = surface->images[i];

			create_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
			create_info.format = surface->format;

			create_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			create_info.subresourceRange.baseMipLevel = 0;
			create_info.subresourceRange.levelCount = 1;
			create_info.subresourceRange.baseArrayLayer = 0;
			create_info.subresourceRange.layerCount = 1;

			if (vkCreateImageView(core::g_LogicalDevice, &create_info, nullptr, &surface->image_views[i]) != VK_SUCCESS)
			{
				g_ErrorCallback(INF_ERROR_NONE, "Failed to create image views!", nullptr);
				return nullptr;
			}
		}

		surface->viewport.x = 0.0f;
		surface->viewport.y = 0.0f;
		surface->viewport.width = surface->size.x;
		surface->viewport.height = surface->size.y;
		surface->viewport.minDepth = 0.0f;
		surface->viewport.maxDepth = 1.0f;

		surface->scissor.offset.x = 0;
		surface->scissor.offset.y = 0;
		surface->scissor.extent.width = surface->size.x;
		surface->scissor.extent.height = surface->size.y;

		return surface;
	}

	void DestroyWindowSurface(window_surface_t* _this)
	{
		for (auto image_view : _this->image_views)
			vkDestroyImageView(core::g_LogicalDevice, image_view, nullptr);

		vkDestroySwapchainKHR(core::g_LogicalDevice, _this->swapchain, nullptr);
		vkDestroySurfaceKHR(core::g_Instance, _this->surface, nullptr);
		delete _this;
	}

} // namespace vk
using namespace vk;

EXPORT_FN window_surface_t* CreateWindowSurface(GLFWwindow* window)
{
	return vk::CreateWindowSurface(window);
}

EXPORT_FN void DestroyWindowSurface(vk::window_surface_t* _this)
{
	return vk::DestroyWindowSurface(_this);
}

EXPORT_FN const glm::uvec2* GetWindowSurfaceSize(vk::window_surface_t* _this)
{
	return &_this->size;
}

EXPORT_FN void SetWindowSurfaceViewport(window_surface_t* surface,
										float x, float y, float w, float h)
{
	surface->viewport.x = x;
	surface->viewport.y = y;
	surface->viewport.width = w;
	surface->viewport.height = h;
}

EXPORT_FN void SetWindowSurfaceScissor(window_surface_t* surface,
									   int32_t x, int32_t y, int32_t w, int32_t h)
{
	surface->scissor.offset.x = x;
	surface->scissor.offset.y = y;
	surface->scissor.extent.width = w;
	surface->scissor.extent.height = h;
}

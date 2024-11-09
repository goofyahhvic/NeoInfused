#if !defined(VK_WINDOW_SURFACE_HPP)
#define VK_WINDOW_SURFACE_HPP

namespace vk {
	struct window_surface_t {
		VkSurfaceKHR surface = VK_NULL_HANDLE;
		VkSwapchainKHR swapchain = VK_NULL_HANDLE;
		VkFormat format = VK_FORMAT_UNDEFINED;
		glm::uvec2 size = { 0, 0 };
		neo::array_list_t<VkImage> images = neo::array_list_t<VkImage>(0);
		neo::array_list_t<VkImageView> image_views = neo::array_list_t<VkImageView>(0);
	};

	window_surface_t* CreateWindowSurface(GLFWwindow* window);
	void DestroyWindowSurface(window_surface_t* surface);
}

#endif // VK_WINDOW_SURFACE_HPP
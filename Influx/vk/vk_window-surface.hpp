#if !defined(VK_WINDOW_SURFACE_HPP)
#define VK_WINDOW_SURFACE_HPP

namespace vk {
	struct window_surface_t {
		VkSurfaceKHR surface;
		VkSwapchainKHR swapchain;
		VkFormat format;
		glm::uvec2 size;
		neo::array_list_t<VkImage> images;
		neo::array_list_t<VkImageView> image_views;
		VkViewport viewport;
		VkRect2D scissor;
	};

	window_surface_t* CreateWindowSurface(GLFWwindow* window);
	void DestroyWindowSurface(window_surface_t* surface);
}

#endif // VK_WINDOW_SURFACE_HPP
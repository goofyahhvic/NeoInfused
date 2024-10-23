#if !defined(VK_WINDOW_SURFACE_HPP)
#define VK_WINDOW_SURFACE_HPP

namespace vk {
	struct window_surface_t {
		VkSurfaceKHR surface = VK_NULL_HANDLE;
		VkSwapchainKHR swapchain = VK_NULL_HANDLE;
	};

	window_surface_t* CreateWindowSurface(GLFWwindow* window);
	void DestroyWindowSurface(window_surface_t* surface);
}

#endif // VK_WINDOW_SURFACE_HPP
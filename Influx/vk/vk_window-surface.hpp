#if !defined(VK_WINDOW_SURFACE_HPP)
#define VK_WINDOW_SURFACE_HPP

namespace vk {
	struct WindowSurface {
		VkSurfaceKHR surface = VK_NULL_HANDLE;
		VkSwapchainKHR swapchain = VK_NULL_HANDLE;
	};

	WindowSurface* CreateWindowSurface(GLFWwindow* window);
	void DestroyWindowSurface(WindowSurface* surface);
}

#endif // VK_WINDOW_SURFACE_HPP
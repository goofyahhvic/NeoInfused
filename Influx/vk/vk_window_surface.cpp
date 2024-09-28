#include "vk_pch.hpp"
#include "vk_window_surface.hpp"

using namespace vk;
EXPORT_FN vk_WindowSurface* CreateWindowSurface(GLFWwindow* window)
{
	vk_WindowSurface* _this = new vk_WindowSurface;

	if (glfwCreateWindowSurface(Core::m_Instance, window, nullptr, &_this->surface) != VK_SUCCESS)
	{
		delete _this;
		_this = nullptr;
	}

	return _this;
}

EXPORT_FN void DestroyWindowSurface(vk_WindowSurface* _this)
{
	vkDestroySurfaceKHR(Core::m_Instance, _this->surface, nullptr);
	delete _this;
}
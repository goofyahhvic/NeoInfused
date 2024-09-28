#include "inf_pch.hpp"
#include "influx/inf_window-surface.hpp"

namespace inf {
	WindowSurface::WindowSurface(GLFWwindow* window)
	: m_Surface(nullptr)
	{
		if (!g_Initialized)
			inf::InitializeAPI();

		m_Surface = Loader::create_window_surface(window);
	}
	void WindowSurface::destroy(void)
	{
		Loader::destroy_window_surface(m_Surface);
		m_Surface = nullptr;
	}
}
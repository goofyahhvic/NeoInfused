#include "inf_pch.hpp"
#include "influx/inf_window-surface.hpp"

namespace inf {
	window_surface_t::window_surface_t(GLFWwindow* window)
	: m_Surface(nullptr)
	{
		if (!g_Initialized)
			inf::InitializeAPI();

		m_Surface = Loader::create_window_surface(window);
	}
	void window_surface_t::destroy(void)
	{
		Loader::destroy_window_surface(m_Surface);
		m_Surface = nullptr;
	}
}
#include "inf_pch.hpp"
#include "influx/inf_window-surface.hpp"

#include "NeoInfused/core/neo_window.hpp"

namespace inf {
	window_surface_t::window_surface_t(neo::window_t* window)
	: window(window), m_Surface(nullptr)
	{
		if (!g_Initialized)
			inf::InitializeAPI();

		m_Surface = Loader::create_window_surface(window->native());
		NEO_ASSERT(m_Surface, "Failed to create window surface!");
	}

	void window_surface_t::destroy(void)
	{
		if (!m_Surface)
			return;

		Loader::destroy_window_surface(m_Surface);
		m_Surface = nullptr;
	}
}
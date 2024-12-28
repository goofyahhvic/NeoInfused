#include "neo_pch.hpp"
#include "NeoInfused/core/app/neo_window-subsystem.hpp"

#include "NeoInfused/core/app/neo_app.hpp"

namespace neo::subsystems {
	window_t::window_t(uint32_t width, uint32_t height,
					   const char* title)
	: window(width, height, title)
	{
		s_This = this;
	}

	void window_t::AddSystems(void)
	{
		app::g_Instance->add_system(NEO_APP_SUBSYSTEM_TYPE_ON_EVENT, OnEvent);
	}

	void window_t::OnEvent(neo::event_t& e)
	{
		s_This->input.on_event(e);
		if (e.type == NEO_WINDOW_CLOSE_EVENT)
			app::g_Instance->should_close = true;
	}
} // namespace neo::app::subsystems

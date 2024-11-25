#include "neo_pch.hpp"
#include "NeoInfused/core/neo_app.hpp"

namespace neo {
	void app_t::add_system(app::system_type_t type, void* fn)
	{
		switch (type)
		{
		case NEO_SYSTEMTYPE_INIT:
			m_Systems.init.emplace((void (*)(void))fn);
			break;
		case NEO_SYSTEMTYPE_SHUTDOWN:
			m_Systems.shutdown.emplace((void (*)(void))fn);
			break;
		case NEO_SYSTEMTYPE_UPDATE:
			m_Systems.update.emplace((void (*)(void))fn);
			break;
		case NEO_SYSTEMTYPE_DRAW:
			m_Systems.draw.emplace((void (*)(void))fn);
			break;
		case NEO_SYSTEMTYPE_ONEVENT:
			m_Systems.on_event.emplace((void (*)(event_t&))fn);
			break;
		default:
			return;
		}
	}

	void app_t::run(void)
	{
		for (auto init_fn : m_Systems.init)
			init_fn();

		while (!should_close)
		{
			for (auto update_fn : m_Systems.update)
				update_fn();

			for (auto draw_fn : m_Systems.draw)
				draw_fn();

			for (event_t& e : event::poll())
			{
				for (auto on_event_fn : m_Systems.on_event)
				{
					on_event_fn(e);
					if (e.handled)
						break;
				}
			}
		}

		for (auto shutdown_fn : m_Systems.shutdown)
			shutdown_fn();
	}
} // namespace neo

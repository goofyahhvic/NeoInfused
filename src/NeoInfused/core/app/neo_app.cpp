#include "neo_pch.hpp"
#include "NeoInfused/core/app/neo_app.hpp"

namespace neo {
	void app_t::add_system(app::system_type_t type, void* fn)
	{
		switch (type)
		{
		case NEO_APP_SYSTEM_TYPE_INIT:
			systems.init.emplace((void (*)(void))fn);
			break;
		case NEO_APP_SYSTEM_TYPE_SHUTDOWN:
			systems.shutdown.emplace((void (*)(void))fn);
			break;
		case NEO_APP_SYSTEM_TYPE_UPDATE:
			systems.update.emplace((void (*)(void))fn);
			break;
		case NEO_APP_SYSTEM_TYPE_ON_EVENT:
			systems.on_event.emplace((void (*)(event_t&))fn);
			break;
		default:
			return;
		}
	}

	void app_t::run(void)
	{
		for (auto init_fn : systems.init)
			init_fn();

		while (!should_close)
		{
			for (auto update_fn : systems.update)
				update_fn();

			for (event_t& e : event::poll())
			{
				for (auto on_event_fn : systems.on_event)
				{
					on_event_fn(e);
					if (e.handled)
						break;
				}
			}
		}

		for (auto shutdown_fn : systems.shutdown)
			shutdown_fn();
	}
} // namespace neo

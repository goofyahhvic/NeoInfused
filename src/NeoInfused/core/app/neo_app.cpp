#include "neo_pch.hpp"
#include "NeoInfused/core/app/neo_app.hpp"

namespace neo {
	void app_t::add_system(app::subsystem_type_t type, void* fn)
	{
		switch (type)
		{
		case NEO_APP_SUBSYSTEM_TYPE_INIT:
			subsystems.init.emplace((void (*)(void))fn);
			break;
		case NEO_APP_SUBSYSTEM_TYPE_SHUTDOWN:
			subsystems.shutdown.emplace((void (*)(void))fn);
			break;
		case NEO_APP_SUBSYSTEM_TYPE_UPDATE:
			subsystems.update.emplace((void (*)(void))fn);
			break;
		case NEO_APP_SUBSYSTEM_TYPE_ON_EVENT:
			subsystems.on_event.emplace((void (*)(event_t&))fn);
			break;
		default:
			return;
		}
	}

	void app_t::run(void)
	{
		for (auto init_fn : subsystems.init)
			init_fn();

		while (!should_close)
		{
			for (auto update_fn : subsystems.update)
				update_fn();

			for (event_t& e : event::poll())
			{
				for (auto on_event_fn : subsystems.on_event)
				{
					on_event_fn(e);
					if (e.handled)
						break;
				}
			}
		}

		for (auto shutdown_fn : subsystems.shutdown)
			shutdown_fn();
	}
} // namespace neo

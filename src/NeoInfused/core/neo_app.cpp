#include "neo_pch.hpp"
#include "NeoInfused/core/neo_app.hpp"

namespace neo {
	static app_t* app = nullptr;
	app_t& app_t::Get(void) { return *app; }

	app_t::app_t(loop_condition_fn loop_condition)
	: event_queue(64), loop_condition(loop_condition)
	{
		NEO_ASSERT(!app, "Cannot create multiple instances of App!");
		app = this;
	}
	app_t::~app_t(void) noexcept(false) { app = nullptr; }

	void app_t::run(void)
	{
		while (loop_condition())
		{
			for (auto it = layers.begin(); it != layers.end(); it++)
				if ((*it)->state & NEO_LAYERSTATE_UPDATABLE)
					(*it)->update();

			for (auto it = layers.rbegin(); it != layers.rend(); it++)
				if ((*it)->state & NEO_LAYERSTATE_VISIBLE)
					(*it)->draw();

			for (event_t& e : event::poll(event_queue))
			{
				if (e.type == NEO_WINDOW_CLOSE_EVENT)
					windows.pop(e.window);

				for (layer_t* layer : layers)
				{
					if (!(layer->state & NEO_LAYERSTATE_ENABLED)) continue;
					layer->on_event(e);
					if (e.handled) break;
				}
			}

			std::this_thread::sleep_for(16ms);
		}
	}
} // namespace neo

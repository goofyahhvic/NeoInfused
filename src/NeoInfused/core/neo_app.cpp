#include "neo_pch.hpp"
#include "NeoInfused/core/neo_app.hpp"

namespace neo {
	static App* _This = nullptr;
	App& App::Get(void) { return *_This; }

	App::App(void)
	{
		NEO_ASSERT(!_This, "Cannot create multiple instances of App!");
		_This = this;
	}
	App::~App(void) noexcept(false) { _This = nullptr; }

	void App::run(void)
	{
		while (loop_condition())
		{
			for (auto it = layers.begin(); it != layers.end(); it++)
				if ((*it)->state & NEO_LAYERSTATE_UPDATABLE)
					(*it)->update();

			for (auto it = layers.rbegin(); it != layers.rend(); it++)
				if ((*it)->state & NEO_LAYERSTATE_VISIBLE)
					(*it)->draw();

			for (Event& e : event_queue.poll_events())
			{
				if (e.type == NEO_WINDOW_CLOSE_EVENT)
					windows.destroy_window(e.window_id);

				for (Layer* layer : layers)
				{
					if (!(layer->state & NEO_LAYERSTATE_ENABLED)) continue;
					layer->on_event(e);
					if (e.handled) break;
				}
			}

			std::this_thread::sleep_for(16ms);
		}
	}
}

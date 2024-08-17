#include "neo_pch.hpp"
#include "NeoInfused/core/neo_app.hpp"

namespace neo {
	App::App(const InitInfo& info, const glm::vec4& clear_color)
	: clear_color(clear_color),
	main_loop_condition([this]() -> bool { return !windows.empty(); }),
	m_Core(info)
	{
		NEO_ASSERT(!s_This, "Cannot create multiple instances of App!");
		s_This = this;
	}

	void App::run(void)
	{
		while (main_loop_condition())
		{
			for (auto layer : layers)
				if ((layer->state & NEO_LAYERSTATE_UPDATABLE) == NEO_LAYERSTATE_UPDATABLE)
					layer->update();

			for (auto& window : windows)
			{
				for (auto it = layers.rbegin(); it != layers.rend(); it++)
					if (((*it)->state & NEO_LAYERSTATE_VISIBLE) == NEO_LAYERSTATE_VISIBLE)
						(*it)->draw();
			}

			for (Event& e : event_handler.poll_events())
			{
				if (e.type == NEO_WINDOW_CLOSE_EVENT)
					windows.destroy_window(e.window_id);

				for (auto layer : layers)
				{
					if (e.handled) break;
					if ((layer->state & NEO_LAYERSTATE_ENABLED) != NEO_LAYERSTATE_ENABLED) continue;
					layer->on_event(e);
				}

			}
		}
	}
}

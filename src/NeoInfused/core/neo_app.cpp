#include "neo_pch.hpp"
#include "NeoInfused/core/neo_app.hpp"

namespace neo {
	using namespace std::chrono_literals;
	App::App(const InitInfo& info, glm::vec4 clear_color)
	: clear_color(clear_color),
	on_event([this](const Event& e) {
		if (e.type == NEO_WINDOW_RESIZE_EVENT) {
			Context::Get().set_viewport(
				windows.at(e.window_id),
				((const neo::WindowResizeEvent&)e).width,
				((const neo::WindowResizeEvent&)e).height
			);
		} else if (e.type == NEO_WINDOW_CLOSE_EVENT) {
			windows.destroy_window(e.window_id);
			windows.empty();
		}
		for (auto layer : layers) {
			if (e.handled) break;
			if ((layer->state & NEO_LAYERSTATE_ENABLED) != NEO_LAYERSTATE_ENABLED) continue;
			layer->on_event(e);
		}

	}), main_loop_condition([this]() -> bool {
		return !windows.empty();
	}), m_Core(info) {
		NEO_ASSERT(!s_This, "Cannot create multiple instances of App!");
		s_This = this;
	}

	void App::run(void) {
        while (main_loop_condition()) {
			for (auto layer : layers)
				if ((layer->state & NEO_LAYERSTATE_UPDATABLE) == NEO_LAYERSTATE_UPDATABLE)
					layer->update();

			for (Window* window : windows) {
				Context::Get().new_frame(window, clear_color);
				for (auto it = layers.rbegin(); it != layers.rend(); it++)
					if (((*it)->state & NEO_LAYERSTATE_VISIBLE) == NEO_LAYERSTATE_VISIBLE)
						(*it)->draw(window->id());
				Context::Get().present(window);
			}

			for (Event& e : event_handler.poll_events()) {
				on_event(e);
			}
        }
	}
}

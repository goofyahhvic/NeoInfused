#include "neo_pch.hpp"
#include "NeoInfused/core/neo_app.hpp"

namespace neo {
	App* App::m_This = nullptr;

	App::App(int32_t width, int32_t height, const char* title)
	: window(width, height, title), layer_group() {
		NEO_ASSERT(!App::m_This, "Cannot create multiple instances of App!");
		App::m_This = this;

		window.on_event = [this](const Event* e) {
			this->_on_event(e);
		};
	}
	void App::run(void) {
        while (!window.should_close) {
			PollEvents();
			this->_update();
			this->_draw();
        }
	}

	void App::_on_event(const Event* e) {
		if (e->type() == neo::EventType::WindowResize) {
			NEO_CONTEXT()->set_viewport(
				&window,
				((neo::WindowResizeEvent*)e)->width(),
				((neo::WindowResizeEvent*)e)->height()
			);
		}
		for (auto layer : layer_group) {
			if (e->handled) break;
			if ((layer->state & NEO_LAYERSTATE_ENABLED) != NEO_LAYERSTATE_ENABLED) continue;
			layer->on_event(e);
		}
	}
	void App::_update(void) {
		for (auto layer : layer_group)
			if ((layer->state & NEO_LAYERSTATE_UPDATABLE) == NEO_LAYERSTATE_UPDATABLE)
				layer->update();
	}
	void App::_draw(void) {
		NEO_CONTEXT()->new_frame(&window, { 0.5f, 0.5f, 1.0f, 1.0f });
		for (auto layer : layer_group)
			if ((layer->state & NEO_LAYERSTATE_VISIBLE) == NEO_LAYERSTATE_VISIBLE)
				layer->draw();
		NEO_CONTEXT()->present(&window);
	}
}

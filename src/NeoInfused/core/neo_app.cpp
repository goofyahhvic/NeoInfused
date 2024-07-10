#include "neo_pch.hpp"
#include "NeoInfused/core/neo_app.hpp"

namespace neo {
	App* App::m_This = nullptr;

	App::App(int32_t width, int32_t height, const std::string& title)
	: window(width, height, title), layer_group(), frame_buffer() {
		NEO_ASSERT(!App::m_This, "Cannot create multiple instances of App!");
		App::m_This = this;

		window.on_event = [this](const Event* e) {
			this->_on_event(e);
		};
	}
	void App::run(size_t frame_buffer_size) {
		frame_buffer.initialize(frame_buffer_size);
        while (!window.should_close) {
			PollEvents();
			this->_update();
			this->_draw();
			frame_buffer.flush();
        }
	}

	void App::_on_event(const Event* e) {
		if (e->type() == neo::EventType::WindowResize) {
			Context::Get()->set_viewport(
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
		Context::Get()->new_frame(&window, clear_color);
		for (auto layer : layer_group)
			if ((layer->state & NEO_LAYERSTATE_VISIBLE) == NEO_LAYERSTATE_VISIBLE)
				layer->draw();
		Context::Get()->present(&window);
	}
}

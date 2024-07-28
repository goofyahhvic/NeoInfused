#if !defined(NEO_APP_HPP)
#define NEO_APP_HPP

#include "NeoInfused/graphics/neo_context.hpp"
#include "neo_layer-storage.hpp"
#include "neo_window-storage.hpp"
#include "neo_scoped-timer.hpp"
#include "neo_event-handler.hpp"

namespace neo {
	class App {
	public:
		App(const InitInfo& info, glm::vec4 clear_color = {0.5f, 0.5f, 1.0f, 1.0f});
		~App(void) noexcept(false) = default;
		void run(void);

		static inline App* Get(void) { return s_This; }
	private:
		Core m_Core;
		static inline App* s_This = nullptr;
	public:
		WindowStorage windows;
		LayerStorage layers;
		EventHandler event_handler;
		glm::vec4 clear_color;
		const std::function<void(const Event&)> on_event;
		std::function<bool(void)> main_loop_condition;
	};
}

#endif // NEO_APP_HPP
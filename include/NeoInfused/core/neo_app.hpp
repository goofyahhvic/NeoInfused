#if !defined(NEO_APP_HPP)
#define NEO_APP_HPP

#include "NeoInfused/graphics/neo_context.hpp"
#include "../data_structures/neo_layer-storage.hpp"
#include "../data_structures/neo_window-storage.hpp"
#include "../data_structures/neo_typed-arena.hpp"
#include "../data_structures/neo_event-handler.hpp"
#include "../data_structures/neo_scene-storage.hpp"
#include "neo_scoped-timer.hpp"

namespace neo {
	class App {
	public:
		App(const InitInfo& info, const glm::vec4& clear_color = {0.5f, 0.5f, 1.0f, 1.0f});
		~App(void) noexcept(false) = default;
		void run(void);

		[[nodiscard]] static inline App& Get(void) { return *s_This; }
	private:
		Core m_Core;
		static inline App* s_This = nullptr;
	public:
		WindowStorage windows;
		EventHandler event_handler;
		glm::vec4 clear_color;
		LayerStorage layers;
		SceneStorage scenes;
		const std::function<void(const Event&)> on_event;
		std::function<bool(void)> main_loop_condition;
	};
	
	[[nodiscard]] inline WindowStorage& GetWindows(void) { return App::Get().windows; }
	[[nodiscard]] inline LayerStorage&  GetLayers(void) { return App::Get().layers; }
	[[nodiscard]] inline SceneStorage&  GetScenes(void) { return App::Get().scenes; }
	[[nodiscard]] inline EventHandler&  GetEventHandler(void) { return App::Get().event_handler; }
}

#endif // NEO_APP_HPP
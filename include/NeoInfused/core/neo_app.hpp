#if !defined(NEO_APP_HPP)
#define NEO_APP_HPP

#include "../data_structures/neo_layer-storage.hpp"
#include "../data_structures/neo_window-storage.hpp"
#include "../data_structures/neo_typed-arena.hpp"
#include "../data_structures/neo_event-queue.hpp"
#include "../data_structures/neo_scene-storage.hpp"

namespace neo {
	class App {
	public:
		typedef bool (*LoopConditionFn)(void);
	public:
		App(int argc, char** argv, const glm::vec4& clear_color = { 0.12f, 0.12f, 0.18f, 1.0f });
		~App(void) noexcept(false) = default;
		void run(void);

		[[nodiscard]] static App& Get(void);
	private:
		Core m_Core;
	public:
		glm::vec4 clear_color;
		WindowStorage windows;
		LoopConditionFn loop_condition;
		EventQueue event_queue;
		LayerStorage layers;
		SceneStorage scenes;
	};

	[[nodiscard]] inline WindowStorage& GetWindows(void) { return App::Get().windows; }
	[[nodiscard]] inline LayerStorage&  GetLayers(void) { return App::Get().layers; }
	[[nodiscard]] inline SceneStorage&  GetScenes(void) { return App::Get().scenes; }
	[[nodiscard]] inline EventQueue&    GetEventHandler(void) { return App::Get().event_queue; }
}

#endif // NEO_APP_HPP
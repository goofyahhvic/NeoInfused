#if !defined(NEO_APP_HPP)
#define NEO_APP_HPP

#include "../data_structures/neo_layer-storage.hpp"
#include "../data_structures/neo_window-storage.hpp"
#include "../data_structures/neo_typed-arena.hpp"
#include "../data_structures/neo_event-queue.hpp"
#include "../data_structures/neo_scene-storage.hpp"

namespace neo {
	[[nodiscard]] inline WindowStorage& GetWindows(void);

	class App {
	public:
		typedef bool (*LoopConditionFn)(void);
	public:
		App(void);
		~App(void) noexcept(false);
		void run(void);

		[[nodiscard]] static App& Get(void);
	public:
		WindowStorage windows;
		LoopConditionFn loop_condition = [](void) -> bool { return !GetWindows().empty(); };
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
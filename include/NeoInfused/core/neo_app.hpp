#if !defined(NEO_APP_HPP)
#define NEO_APP_HPP

#include "../data_structures/neo_layer-storage.hpp"
#include "../data_structures/neo_window-storage.hpp"
#include "../data_structures/neo_scene-storage.hpp"
#include "../template/neo_typed-arena.hpp"

namespace neo {
	using EventQueue = Arena<Event>;
	void PollEvents(EventQueue& queue);

	[[nodiscard]] inline WindowStorage& GetWindows(void);
	class App {
	public:
		typedef bool (*LoopConditionFn)(void);
	public:
		App(LoopConditionFn loop_condition = [](void) -> bool { return !GetWindows().empty(); });
		~App(void) noexcept(false);
		void run(void);

		[[nodiscard]] static App& Get(void);
	public:
		WindowStorage windows;
		LoopConditionFn loop_condition;
		EventQueue event_queue;
		LayerStorage layers;
		SceneStorage scenes;
	};

	[[nodiscard]] inline WindowStorage& GetWindows(void) { return App::Get().windows; }
	[[nodiscard]] inline LayerStorage&  GetLayers(void) { return App::Get().layers; }
	[[nodiscard]] inline SceneStorage&  GetScenes(void) { return App::Get().scenes; }
	[[nodiscard]] inline EventQueue&    GetEventQueue(void) { return App::Get().event_queue; }
}

#endif // NEO_APP_HPP
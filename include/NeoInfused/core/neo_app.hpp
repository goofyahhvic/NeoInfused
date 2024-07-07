#if !defined(NEO_APP_HPP)
#define NEO_APP_HPP

#include "NeoInfused/graphics/neo_context.hpp"
#include "neo_layer-group.hpp"

namespace neo {
	class App {
	public:
		App(int32_t width = 1280, int32_t height = 720, const char* title = "Unnamed Application");
		virtual ~App(void) noexcept(false) = default;
	public:
		virtual void run(void);
		static inline App* Get(void) { return App::m_This; }
	protected:
		virtual void _on_event(const Event* e);
		virtual void _update(void);
		virtual void _draw();
	public:
		Window window;
		LayerGroup layer_group;
	private:
		static App* m_This;
	};
}

#endif // NEO_APP_HPP
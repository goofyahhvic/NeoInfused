#if !defined(NEO_APP_HPP)
#define NEO_APP_HPP

#include "NeoInfused/graphics/neo_context.hpp"
#include "neo_layer-group.hpp"
#include "neo_frame-buffer.hpp"

namespace neo {
	class App {
	public:
		App(int32_t width = 1280, int32_t height = 720, const std::string& title = Core::GetExecName());
		virtual ~App(void) noexcept(false) = default;
	public:
		virtual void run(size_t frame_buffer_size);
		static inline App* Get(void) { return App::m_This; }
	protected:
		virtual void _on_event(const Event* e);
		virtual void _update(void);
		virtual void _draw();
	public:
		Window window;
		LayerGroup layer_group;
		FrameBuffer frame_buffer;
		glm::vec4 clear_color = { 0.5f, 0.5f, 1.0f, 1.0f };
	private:
		static App* m_This;
	};
}

#endif // NEO_APP_HPP
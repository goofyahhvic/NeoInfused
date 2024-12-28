#if !defined(INF_RENDERER_HPP)
#define INF_RENDERER_HPP

#include "inf_loader.hpp"
#include "inf_window-surface.hpp"
#include "inf_shader.hpp"

namespace inf {
	class renderer_t {
	public:
		renderer_t(neo::window_t& window);
		~renderer_t(void);

		void attach_shader(shader::handle_t handle);
		void attach_shaders(const std::initializer_list<shader::handle_t>& handles);

		void init(void);

		inline operator bool(void) const { return window_surface && m_GraphicsPipeline; }
	public:
		window_surface_t window_surface;
	private:
		Loader::graphics_pipeline_t* m_GraphicsPipeline;
	};
} // namespace inf

#endif // INF_RENDERER_HPP
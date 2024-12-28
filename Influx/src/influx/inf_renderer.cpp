#include "inf_pch.hpp"
#include "influx/inf_renderer.hpp"

namespace inf {
	renderer_t::renderer_t(neo::window_t& window)
	: window_surface(&window),
	m_GraphicsPipeline(Loader::create_graphics_pipeline(window_surface.native()))
	{

	}

	renderer_t::~renderer_t(void)
	{
		Loader::destroy_graphics_pipeline(m_GraphicsPipeline);
	}

	void renderer_t::attach_shader(shader::handle_t handle)
	{
		Loader::attach_shader_to_pipeline(m_GraphicsPipeline, handle);
	}

	void renderer_t::attach_shaders(const std::initializer_list<shader::handle_t>& handles)
	{
		Loader::attach_shaders_to_pipeline(m_GraphicsPipeline, handles);
	}

	void renderer_t::init(void)
	{
		Loader::init_graphics_pipeline(m_GraphicsPipeline);
	}

} // namespace inf

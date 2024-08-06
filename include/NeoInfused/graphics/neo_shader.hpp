#if !defined(NEO_SHADER_HPP)
#define NEO_SHADER_HPP

#include "neo_shader_src.hpp"

namespace neo {
	class ShaderProgram {
	public:
		ShaderProgram(void) = default;
		virtual ~ShaderProgram(void) = default;
		static ShaderProgram* Create(const char* vertex_shader_src = Shaders::default_vertex, const char* fragment_shader_src = Shaders::default_fragment);

		virtual void bind(void) const = 0;
	};
}

#endif // NEO_SHADER_HPP
#include "neo_pch.hpp"
#include "NeoInfused/graphics/neo_shader.hpp"

#include "NeoInfused/graphics/gl/neo-gl_shader.hpp"

namespace neo {
	ShaderProgram* ShaderProgram::Create(const char* vs_src, const char* fs_src)
	{
		if (Context::API() == NEO_RENDERERAPI_OPENGL)
			return new gl::ShaderProgram(vs_src, fs_src);
		return nullptr;
	}
} // namespace neo

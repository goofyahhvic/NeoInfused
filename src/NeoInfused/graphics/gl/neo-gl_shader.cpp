#include "neo_pch.hpp"
#include "NeoInfused/graphics/gl/neo-gl_shader.hpp"

namespace neo::gl {
	static uint32_t createShader(const char* src, int32_t type)
	{
		uint32_t shader = glCreateShader(type);
		glShaderSource(shader, 1, &src, nullptr);
		glCompileShader(shader);

	#if !defined (NEO_CONFIG_DIST)
		int32_t success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char error[1024];
			glGetShaderInfoLog(shader, 1024, nullptr, error);
			throw std::runtime_error(NEO_FORMAT("Shader compilation error: {0}", error));
		}
	#endif
		return shader;
	}

	ShaderProgram::ShaderProgram(const char* vertex_shader_src, const char* fragment_shader_src)
		: program(glCreateProgram())
	{
		uint32_t vertex = createShader(vertex_shader_src, GL_VERTEX_SHADER),
			fragment = createShader(fragment_shader_src, GL_FRAGMENT_SHADER);
		glAttachShader(program, vertex);
		glAttachShader(program, fragment);
		glLinkProgram(program);

	#if !defined (NEO_CONFIG_DIST)
		int32_t success;
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success)
		{
			char error[1024];
			glGetProgramInfoLog(program, 1024, nullptr, error);
			throw std::runtime_error(NEO_FORMAT("Program linking error: {0}", error));
		}
	#endif
		glDetachShader(program, vertex);
		glDetachShader(program, fragment);

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	ShaderProgram::~ShaderProgram(void)
	{
		glDeleteProgram(program);
	}

	void ShaderProgram::bind(void) const
	{
		glUseProgram(program);
	}
} // namespace neo::gl

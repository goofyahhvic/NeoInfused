#include "neo_pch.hpp"
#include "NeoInfused/graphic/neo_shader.hpp"

namespace neo {
    uint32_t CreateShader(const char* shader_src, int32_t type) {
        uint32_t shader = glCreateShader(type);
        glShaderSource(shader, 1, &shader_src, nullptr);
        glCompileShader(shader);

    #if !defined (NEO_CONFIG_DIST)
        int32_t success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char error[1024];
            glGetShaderInfoLog(shader, 1024, nullptr, error);
            throw std::runtime_error(NEO_FORMAT("Shader compilation error: {0}", error));
        }
    #endif
        return shader;
    }
    void DestroyShader(uint32_t shader) {
        glDeleteShader(shader);
    }

    ShaderProgram::ShaderProgram(const char* vshader_src, const char* fshader_src) {
        uint32_t vshader = CreateShader(vshader_src, GL_VERTEX_SHADER);
        uint32_t fshader = CreateShader(fshader_src, GL_FRAGMENT_SHADER);

        m_Program = glCreateProgram();
        glAttachShader(m_Program, vshader);
        glAttachShader(m_Program, fshader);
        glLinkProgram(m_Program);

    #if !defined (NEO_CONFIG_DIST)
        int32_t success;
        glGetProgramiv(m_Program, GL_LINK_STATUS, &success);
        if (!success) {
            char error[1024];
            glGetProgramInfoLog(m_Program, 1024, nullptr, error);
            throw std::runtime_error(NEO_FORMAT("Program linking error: {0}", error));
        }
    #endif

        glDeleteShader(fshader);
        glDeleteShader(vshader);
    }
    ShaderProgram::~ShaderProgram(void) {
        glDeleteProgram(m_Program);
    }

    void ShaderProgram::use(void) {
        glUseProgram(m_Program);
    }
} // namespace neo

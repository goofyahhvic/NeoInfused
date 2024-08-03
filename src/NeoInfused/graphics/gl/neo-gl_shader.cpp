#include "neo_pch.hpp"
#include "NeoInfused/graphics/gl/neo-gl_shader.hpp"

namespace neo { namespace gl {
    uint32_t CreateShader(ShaderCreateInfo info) {
        uint32_t shader = glCreateShader(info.type);
        glShaderSource(shader, 1, &(info.src), nullptr);
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
    
    ShaderProgram::ShaderProgram(const std::vector<uint32_t>& shaders) {
        m_Program = glCreateProgram();
        for (uint32_t shader : shaders)
            glAttachShader(m_Program, shader);
    
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
    
        for (uint32_t shader : shaders)
            glDeleteShader(shader);
    }
    ShaderProgram::~ShaderProgram(void) {
        glDeleteProgram(m_Program);
    }
    
    void ShaderProgram::bind(void) const {
        glUseProgram(m_Program);
    }
} // namespace gl
} // namespace neo

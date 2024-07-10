#if !defined(NEO_GL_SHADER_HPP)
#define NEO_GL_SHADER_HPP

#include "NeoInfused/neo_core.hpp"

namespace neo {
    struct gl_ShaderCreateInfo {
        const char* src;
        int32_t type;
    };

    uint32_t gl_CreateShader(gl_ShaderCreateInfo info);

    class gl_ShaderProgram {
    public:
        gl_ShaderProgram(const std::vector<uint32_t>& shaders);
        ~gl_ShaderProgram(void);

        void bind(void) const;
        inline uint32_t get(void) const { return m_Program; }
    private:
        uint32_t m_Program;
    };
} // namespace neo

#endif // NEO_GL_SHADER_HPP
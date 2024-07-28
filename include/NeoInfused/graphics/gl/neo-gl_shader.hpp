#if !defined(NEO_GL_SHADER_HPP)
#define NEO_GL_SHADER_HPP

#include "NeoInfused/neo_core.hpp"

namespace neo { namespace gl {
    struct ShaderCreateInfo {
        const char* src;
        int32_t type;
    };
    uint32_t CreateShader(ShaderCreateInfo info);
    class ShaderProgram {
    public:
        ShaderProgram(const std::vector<uint32_t>& shaders);
        ~ShaderProgram(void);

        void bind(void) const;
        inline uint32_t get(void) const { return m_Program; }
    private:
        uint32_t m_Program;
    };
} // namespace gl
} // namespace neo

#endif // NEO_GL_SHADER_HPP
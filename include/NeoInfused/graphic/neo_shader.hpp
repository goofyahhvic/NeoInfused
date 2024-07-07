#if !defined(NEO_SHADER_HPP)
#define NEO_SHADER_HPP

#include "NeoInfused/neo_core.hpp"

namespace neo {
    uint32_t CreateShader(const char* shader_src, int32_t type);
    void DestroyShader(uint32_t shader);

    class ShaderProgram {
    public:
        ShaderProgram(const char* vertex_shader_src, const char* fragment_shader_src);
        ~ShaderProgram(void);

        void use(void);
        inline uint32_t program(void) const { return m_Program; }
    private:
        uint32_t m_Program;
    };
} // namespace neo

#endif // NEO_SHADER_HPP
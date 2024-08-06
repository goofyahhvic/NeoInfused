#if !defined(NEO_GL_SHADER_HPP)
#define NEO_GL_SHADER_HPP

#include "../neo_shader.hpp"

namespace neo::gl {
    class ShaderProgram : public neo::ShaderProgram {
    public:
        ShaderProgram(const char* vertex_shader_src, const char* fragment_shader_src);
        ~ShaderProgram(void);

        void bind(void) const;
        inline operator uint32_t (void) const { return program; }
    public:
        const uint32_t program;
    };
} // namespace neo::gl

#endif // NEO_GL_SHADER_HPP
#if !defined(NEO_GL_CONTEXT_HPP)
#define NEO_GL_CONTEXT_HPP

#include "../neo_context.hpp"

namespace neo {
    class glContext : public Context {
        friend class Context;
        glContext(void) = default;
        ~glContext(void) = default;
    public:
        void initialize(Window* window) override;
        void terminate(void) override;

        void set_viewport(Window* window, uint32_t width, uint32_t height);
        void new_frame(Window* window, const glm::vec4& color = {0, 0, 0, 255});
        void present(Window* window);
    };
} // namespace neo

#endif // NEO_GL_CONTEXT_HPP
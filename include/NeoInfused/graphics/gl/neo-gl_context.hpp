#if !defined(NEO_GL_CONTEXT_HPP)
#define NEO_GL_CONTEXT_HPP

#include "../neo_context.hpp"

namespace neo::gl {
    class Context : public neo::Context {
    public:
        void initialize(Window* window) override;

        void set_viewport(Window* window, uint32_t width, uint32_t height);
        void new_frame(Window* window, const glm::vec4& color = { 0, 0, 0, 255 });
        void present(Window* window);
    private:
        friend class neo::Context;
        Context(void) = default;
        ~Context(void) = default;
    };
} // namespace neo::gl

#endif // NEO_GL_CONTEXT_HPP
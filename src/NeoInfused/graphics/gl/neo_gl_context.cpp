#include "NeoInfused/neo_core.hpp"
#include "neo_pch.hpp"
#include "NeoInfused/graphics/gl/neo-gl_context.hpp"

#include "NeoInfused/core/neo_window.hpp"
#include <GLFW/glfw3.h>

namespace neo {
    Context* Context::Create_GL(void) {
        NEO_ASSERT(!Context::m_This, "Cannot create multiple Contexts!");
        Context::m_This = new glContext();
        return Context::m_This;
    }

    void glContext::initialize(Window* window) {
        glfwMakeContextCurrent(window->m_Window);
        NEO_ASSERT_FUNC(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize glad!");

        NEO_TRACE_LOG(
            "Loaded OpenGL version {0}" NEO_LOG_CONTINUE "with device {1}" NEO_LOG_CONTINUE "in GLSL version {2}",
            (const char*)glGetString(GL_VERSION),
            (const char*)glGetString(GL_RENDERER),
            (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION)
        );
        Context::m_Initialized = true;
    }
    void glContext::terminate(void) {
        Context::m_Initialized = false;
    }

    void glContext::set_viewport(Window* window, uint32_t width, uint32_t height) {
        glfwMakeContextCurrent(window->m_Window);
        glViewport(0, 0, width, height);
    }
    void glContext::new_frame(Window* window, const glm::vec4& color) {
        glfwMakeContextCurrent(window->m_Window);
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    void glContext::present(Window* window) {
        glfwSwapBuffers(window->m_Window);
    }
} // namespace neo
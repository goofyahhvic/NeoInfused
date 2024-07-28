#if !defined(NEO_WINDOW_HPP)
#define NEO_WINDOW_HPP

#include "NeoInfused/core/neo_event.hpp"

namespace neo {
    namespace gl { class Context; }

    class Window {
    public:
        inline uint64_t id(void) const { return m_Id; }

        inline uint32_t width(void) const { return m_Width; }
        inline uint32_t height(void) const { return m_Height; }
        void set_size(uint32_t width, uint32_t height);

        void set_title(const char* title);
        const char* title(void) const;
    public:
        bool should_close = false;
    private:
        friend class gl::Context;
        friend class Context;
        friend class WindowStorage;

        Window(void) = default;
        Window(uint32_t id, uint32_t width, uint32_t height, const std::string& title);
        Window(Window&& other) noexcept;
        Window(const Window& other) = delete;
        ~Window(void);

        static void _SetGLFWCallbacks(GLFWwindow* _window);
    public:
        static void _GLFWPollEvents(void);
    private:
        GLFWwindow* m_Window;
        uint32_t m_Width, m_Height;
        uint32_t m_Id;
        bool m_Focus;
    };
} // namespace neo

#endif // NEO_WINDOW_HPP
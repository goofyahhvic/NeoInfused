#if !defined(NEO_WINDOW_HPP)
#define NEO_WINDOW_HPP

#include "NeoInfused/core/neo_event.hpp"

namespace neo {
    class Window {
        friend class Core;
        friend class glContext;
    public:
        Window(int32_t width = 1280, int32_t height = 720, const char* title = "Unnamed Window");
        ~Window(void);
    public:
        inline uint16_t id(void) const { return m_Id; }
        static Window* GetFromID(uint16_t id) { return m_Windows.at(id); }

        inline uint32_t width(void) const { return m_Width; }
        inline uint32_t height(void) const { return m_Height; }

        static void SetGLFWCallbacks(GLFWwindow* _window);
    public:
        std::function<void(const Event*)> on_event = [](const Event*) {};
        bool should_close = false;
    private:
        GLFWwindow* m_Window;
        uint32_t m_Width, m_Height;
        uint16_t m_Id;

        static uint16_t m_LastId;
        static std::unordered_map<uint16_t, Window*> m_Windows;
    };

    void PollEvents(void);
} // namespace neo

#endif // NEO_WINDOW_HPP
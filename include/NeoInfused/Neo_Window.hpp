#if !defined(NEO_WINDOW_HPP)
#define NEO_WINDOW_HPP

#include "NeoInfused/Sprite/Neo_Graphic2D.hpp"

#define NEO_BOUND_WINDOW neo::Window::GetBound()
#define NEO_BOUND_DISPLAY neo::Window::GetBound()->display()

namespace neo {
    class Window {
        Window(void) = default;
        ~Window(void) = default;
    public:
        struct CreateInfo {
            int32_t x = SDL_WINDOWPOS_CENTERED, y = SDL_WINDOWPOS_CENTERED;
            int32_t width = 1280, height = 720;
            int32_t display_width = width, display_height = height;
            const std::string& title = "Unnamed Window";
        };
        static void Init(void);
        static void Cleanup(void);
    
        static Window* New(const CreateInfo& info);
        static void Delete(Window* _this);
    public:
        inline Graphic2D* display(void) { return m_Display; }
        inline const Graphic2D* display(void) const { return m_Display; }
        void present_display(void);

        inline void bind(void) { Window::m_BoundWindow = this; }
        static inline Window* GetBound(void) { return Window::m_BoundWindow; }

        inline uint32_t id(void) const { return SDL_GetWindowID(m_Window); }
        static uint32_t GetID(SDL_Window* window);

        static inline Window* GetFromID(uint32_t id) { return Window::m_Windows.at(id); }
        static SDL_Window* GetNativeFromID(uint32_t id);

        inline void set_on_close(const std::function<void(void*)>& on_close) { m_OnClose = on_close; }
        static inline bool NoWindows(void) { return Window::m_Windows.empty(); }

        inline bool should_close(void) const { return m_ShouldClose; }
        inline void close(void* user_data = nullptr) { m_ShouldClose = true; m_OnClose(user_data); }

        inline uint32_t width(void) const { return SDL_GetWindowSurface(m_Window)->w; }
        inline uint32_t height(void) const { return SDL_GetWindowSurface(m_Window)->h; }

        void set_width(uint32_t new_width);
        void set_height(uint32_t new_height);
        void set_size(uint32_t new_width, uint32_t new_height);
        void increase_size(uint32_t width_amount, uint32_t height_amount);

        inline int32_t x(void) const { return m_X; }
        inline int32_t y(void) const { return m_Y; }
        void update_pos(void);

        void rename(const char* new_title);
        std::string get_name(void) const { return SDL_GetWindowTitle(m_Window); }

        inline SDL_Window* native(void) const { return m_Window; }
        inline operator bool() const { return (bool)m_Window; }
    private:
        SDL_Window* m_Window;
        Graphic2D* m_Display;
        int32_t m_X, m_Y;
        bool m_ShouldClose = false;
        std::function<void(void*)> m_OnClose = [](void*){};

        static Window* m_BoundWindow;
        static std::unordered_map<uint32_t, Window*> m_Windows;
    };
    using WindowCreateInfo = Window::CreateInfo;
} // namespace neo

#endif // NEO_WINDOW_HPP
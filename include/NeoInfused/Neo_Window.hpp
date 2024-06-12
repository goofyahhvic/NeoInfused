#if !defined(NEO_WINDOW_HPP)
#define NEO_WINDOW_HPP

#include "NeoInfused/Core/Neo_Core.hpp"

namespace neo {
    union Color {
        struct { uint8_t r, g, b, a; };
        uint32_t rgba = 0x000000FF;
    };

    class Window {
        Window(void) = default;
        ~Window(void) = default;
    public:
        struct CreateInfo {
            int32_t x = SDL_WINDOWPOS_CENTERED, y = SDL_WINDOWPOS_CENTERED;
            int32_t width = 1280, height = 720;
            int32_t draw_width = width, draw_height = height;
            const std::string& title = "Unnamed Window";
        };
        friend class Display;
        class Display {
        public:
            Display(Window* window);
            ~Display(void) = default;
        public:
            void clear(Color color = {});
            void present(void);

            Color* at(uint32_t x, uint32_t y);
            void set_at(uint32_t x, uint32_t y, Color color);

            void blit(SDL_Surface* surface, SDL_Rect* position = nullptr, SDL_Rect* portion = nullptr);

            void update_size(void);
        private:
            Window* m_Window;
        };

        static void Init(void);
        static void Cleanup(void);
    
        static Window* New(const CreateInfo& info);
        static void Delete(Window* _this);
    public:
        inline Display* const display(void) const { return m_Display; }

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

        void rename(const char* new_title);

        inline SDL_Window* get_native(void) const { return m_Window; }
        inline operator bool() const { return (bool)m_Window; }
    private:
        SDL_Window* m_Window;
        SDL_Surface *m_WindowSurface, *m_DrawSurface;
        Display* m_Display; 
        bool m_ShouldClose = false;
        std::function<void(void*)> m_OnClose = [](void*){};

        static Window* m_BoundWindow;
        static std::unordered_map<uint32_t, Window*> m_Windows;
    };
    using WindowCreateInfo = Window::CreateInfo;
} // namespace neo

#endif // NEO_WINDOW_HPP
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
            inline uint32_t width(void) const { return m_Window->m_DrawSurface->w; }
            inline uint32_t height(void) const { return m_Window->m_DrawSurface->h; }

            void update_size(void);
            void set_width(uint32_t new_width);
            void set_height(uint32_t new_height);
            void set_size(uint32_t new_width, uint32_t new_height);
            void increase_size(uint32_t width_amount, uint32_t height_amount);

            void clear(Color color = {0, 0, 0, 255});
            void present(void);

            Color* at(uint32_t x, uint32_t y);
            void set_at(uint32_t x, uint32_t y, Color color);

            void blit(SDL_Surface* surface, SDL_Rect* position = nullptr, SDL_Rect* portion = nullptr);
        private:
            Window* m_Window;
        };

        static void Init(void);
        static void Cleanup(void);
    
        static Window* New(const CreateInfo& info);
        static void Delete(Window* _this);
    public:
        inline uint32_t width(void) const { return m_WindowSurface->w; }
        inline uint32_t height(void) const { return m_WindowSurface->h; }
        void update_size(void);

        void set_width(uint32_t new_width);
        void set_height(uint32_t new_height);
        void set_size(uint32_t new_width, uint32_t new_height);
        void increase_size(uint32_t width_amount, uint32_t height_amount);

        inline int32_t x(void) const { return m_X; }
        inline int32_t y(void) const { return m_Y; }
        void update_pos(void);

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

        inline SDL_Window* native(void) const { return m_Window; }
        inline operator bool() const { return (bool)m_Window; }
    private:
        SDL_Window* m_Window;
        int32_t m_X, m_Y;
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
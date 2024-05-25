#if !defined(NEO_WINDOW_HPP)
#define NEO_WINDOW_HPP

#include "NeoInfused/Core/Neo_Core.hpp"

namespace neo {
    class Window {
        Window(void) = default;
        ~Window(void) = default;
    public:
        struct Pos { const int32_t &x, &y; };
        struct CopyPos { int32_t x, y; };

        struct Size { const int32_t &w, &h; };
        struct CopySize { int32_t w, h; };

        struct Rect { const int32_t &x, &y; const int32_t &w, &h; };
        struct CopyRect { int32_t x, y; int32_t w, h; };

        struct Data {
            int32_t x = SDL_WINDOWPOS_CENTERED, y = SDL_WINDOWPOS_CENTERED;
            int32_t w = 1280, h = 720;
            std::string title = "Unnamed Window"; 
            uint32_t index = 0;
        };
        struct CreateInfo {
            int32_t w = 1280, h = 720;
            const std::string& title = "Unnamed Window";
            int32_t flags = SDL_WINDOW_SHOWN;
            int32_t x = SDL_WINDOWPOS_CENTERED, y = SDL_WINDOWPOS_CENTERED;
            inline operator Data() const { return { x, y, w, h, title }; }
        };
    public:
        static void Init(void);
        static void Terminate(void);
    public:
        static Window* New(const CreateInfo& info);
        static void Delete(Window* _this);
    public:
        inline void bind(void) { Window::m_BoundWindow = this; }
        static inline void Bind(Window* window) { Window::m_BoundWindow = window; }
        static inline Window* GetBound(void) { return Window::m_BoundWindow; }

        void set_pos(int32_t x = SDL_WINDOWPOS_CENTERED, int32_t y = SDL_WINDOWPOS_CENTERED);
        void set_x(int32_t x = SDL_WINDOWPOS_CENTERED);
        void set_y(int32_t y = SDL_WINDOWPOS_CENTERED);

        void set_size(int32_t w, int32_t h);
        void set_width(int32_t w);
        void set_height(int32_t h);
        void increase_size(int32_t w, int32_t h);

        void set_rect(const CopyRect& rect);
        void rename(const std::string& title);
        inline const std::string& get_name(void) const { return m_Data.title; }

        inline int32_t get_x(void) { this->_update_pos();  return m_Data.x; }
        inline int32_t get_y(void) { this->_update_pos();  return m_Data.y; }
        inline int32_t get_w(void) { this->_update_size(); return m_Data.w; }
        inline int32_t get_h(void) { this->_update_size(); return m_Data.h; }

        inline void get_pos(int32_t* x, int32_t* y) { this->_update_pos(); *x = m_Data.x; *y = m_Data.y; }
        inline Pos get_pos(void) { this->_update_pos(); return { m_Data.x, m_Data.y}; }
        inline CopyPos get_copy_pos(void) { this->_update_pos(); return { m_Data.x, m_Data.y}; }

        inline void get_size(int32_t* w, int32_t* h) { this->_update_size(); *w = m_Data.w; *h = m_Data.h; }
        inline Size get_size(void) { this->_update_size(); return { m_Data.w, m_Data.h }; }
        inline CopySize get_copy_size(void) { this->_update_size(); return { m_Data.w, m_Data.h }; }

        inline void get_rect(int32_t* x, int32_t* y,uint32_t* w, int32_t* h) { this->_update_rect(); *x = m_Data.x; *y = m_Data.y; *w = m_Data.w; *h = m_Data.h; }
        inline Rect get_rect(void) { this->_update_rect(); return { m_Data.x, m_Data.y, m_Data.w, m_Data.h }; }     
        inline CopyRect get_copy_rect(void) { this->_update_rect(); return { m_Data.x, m_Data.y, m_Data.w, m_Data.h }; }     

        inline const Data& get_data(void) const { return m_Data; }
        inline SDL_Window* get_native(void) const { return m_Window; }
        inline operator bool() const { return (m_Window); }
    private:
        void _update_pos(void);
        void _update_size(void);
        void _update_rect(void);
    private:
        SDL_Window* m_Window;
        Data m_Data;
        static Window* m_BoundWindow;
        static std::vector<SDL_Window*> m_Windows;
    };
    using WindowCreateInfo = Window::CreateInfo;
} // namespace neo

#endif // NEO_WINDOW_HPP
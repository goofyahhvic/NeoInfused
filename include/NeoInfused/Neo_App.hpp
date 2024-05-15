#if !defined(NEO_APP_HPP)
#define NEO_APP_HPP

#include "./Sprite/Neo_SpriteHandle.hpp"

namespace neo {
    class App {
    public:
        struct WindowData {
            int32_t x, y;
            size_t w, h;
            std::string title;
        };

        struct WindowPos { int32_t x, y; };
        using  WindowSize = core::Size;
        struct WindowRect { int32_t x, y; size_t w, h; };

        struct WindowPosR { const int32_t &x, &y; };
        struct WindowSizeR { const size_t &w, &h; };
        struct WindowRectR { const int32_t &x, &y; const size_t &w, &h; };
    public:
        App(int32_t x = SDL_WINDOWPOS_CENTERED, int32_t y = SDL_WINDOWPOS_CENTERED, size_t w = 1280, size_t h = 720, const char* title = "Unnamed Application");
        virtual ~App(void);
    public:
        virtual void run(void);
    public: 
        inline static App* Get(void) { return sm_This; }

        inline const WindowData& get_window_data(void) const { return m_WindowData; }

        void set_window_pos(int32_t x = SDL_WINDOWPOS_CENTERED, int32_t y = SDL_WINDOWPOS_CENTERED);
        inline void set_window_pos(const WindowPos& pos) { this->set_window_pos(pos.x, pos.y); }
        inline void set_window_pos(const WindowPosR& pos) { this->set_window_pos(pos.x, pos.y); }

        void set_window_x(int32_t x);
        void set_window_y(int32_t y);

        void set_window_size(size_t w, size_t h);
        inline void set_window_size(const WindowSize& size) { this->set_window_size(size.w, size.h); }
        inline void set_window_size(const WindowSizeR& size)  { this->set_window_size(size.w, size.h); }

        void set_window_width(size_t w); 
        void set_window_height(size_t h);

        void increase_window_size(size_t w, size_t h);
        inline void increase_window_size(const WindowSize& size) { this->increase_window_size(size.w, size.h); }
        inline void increase_window_size(const WindowSizeR& size)  { this->increase_window_size(size.w, size.h); }

        void rename_window(const char* title);
        inline void set_window_title(const char* title) { this->rename_window(title); }

        inline int32_t get_window_x(void) { this->_get_window_pos(); return m_WindowData.x; }
        inline int32_t get_window_y(void) { this->_get_window_pos(); return m_WindowData.y; }

        inline WindowPos get_window_pos_c(void) { this->_get_window_pos(); return { m_WindowData.x, m_WindowData.y }; }
        inline WindowPosR get_window_pos(void)    { this->_get_window_pos(); return { m_WindowData.x, m_WindowData.y }; }

        inline void get_window_pos_r(int32_t& x, int32_t& y) { this->_get_window_pos(); x = m_WindowData.x; y = m_WindowData.y; }
        inline void get_window_pos_p(int32_t* x, int32_t* y) { this->_get_window_pos(); *x = m_WindowData.x; *y = m_WindowData.y; }

        inline size_t get_window_width(void)  { this->_get_window_size(); return m_WindowData.w; }
        inline size_t get_window_height(void) { this->_get_window_size(); return m_WindowData.h; }

        inline WindowSize get_window_size_c(void) { this->_get_window_size(); return { m_WindowData.w, m_WindowData.h }; }
        inline WindowSizeR get_window_size(void)    { this->_get_window_size(); return { m_WindowData.w, m_WindowData.h }; }

        inline void get_window_size_r(size_t& w, size_t& h) { this->_get_window_size(); w = m_WindowData.w; h = m_WindowData.h; }
        inline void get_window_size_p(size_t* w, size_t* h) { this->_get_window_size(); *w = m_WindowData.w; *h = m_WindowData.h; }

        inline WindowRect get_window_rect_c(void) { this->_get_window_rect(); return { m_WindowData.x, m_WindowData.y, m_WindowData.w, m_WindowData.h }; }
        inline WindowRectR get_window_rect(void)   { this->_get_window_rect(); return { m_WindowData.x, m_WindowData.y, m_WindowData.w, m_WindowData.h }; }

        inline void get_window_rect_r(int32_t& x, int32_t& y, size_t& w, size_t& h) { this->_get_window_rect(); x = m_WindowData.x; y = m_WindowData.y; w = m_WindowData.w; h = m_WindowData.h; }
        inline void get_window_rect_p(int32_t* x, int32_t* y, size_t* w, size_t* h) { this->_get_window_rect(); *x = m_WindowData.x; *y = m_WindowData.y; *w = m_WindowData.w; *h = m_WindowData.h; }

        inline SDL_Window* get_window(void) { return m_Window; }
        inline SDL_Renderer* get_renderer(void) { return m_Renderer; }

        inline bool should_close(void) const { return m_Close; }
        inline void close(bool value = true) { m_Close = value; }

    protected:
        virtual void handle_event(SDL_Event* e);
        virtual void update(void);
        virtual void draw(void);

    private:
        void init_sdl(void);
        void cleanup_sdl(void);

        void _get_window_pos(void);
        void _get_window_size(void);
        void _get_window_rect(void);
    protected:
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;

        bool m_Close;
        WindowData m_WindowData;

    private:
        static App* sm_This;
    };
    using WindowData  = App::WindowData;

    using WindowPosR   = App::WindowPosR;
    using WindowSizeR  = App::WindowSizeR;
    using WindowRectR = App::WindowRectR;

    using WindowPos  = App::WindowPos;
    using WindowSize = App::WindowSize;
    using WindowRect = App::WindowRect;
} // namespace neo

#endif // NEO_APP_HPP
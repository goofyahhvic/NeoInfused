#if !defined(NEO_APP_HPP)
#define NEO_APP_HPP

#include "NeoInfused/Core/Neo_Core.hpp"
#include "./Sprite/Neo_SpriteHandler.hpp"

namespace neo {
    class App {
    public:
        struct WindowData {
            int32_t x, y;
            uint32_t w, h;
            std::string title;
        };

        struct WindowPos { int32_t x, y; };
        using  WindowSize = neo_core::Size;
        struct WindowRect { int32_t x, y; uint32_t w, h; };

        struct WindowPosR { const int32_t &x, &y; };
        struct WindowSizeR { const uint32_t &w, &h; };
        struct WindowRectR { const int32_t &x, &y; const uint32_t &w, &h; };
    public:
        App(int32_t x = SDL_WINDOWPOS_CENTERED, int32_t y = SDL_WINDOWPOS_CENTERED, uint32_t w = 1280, uint32_t h = 720, const char* title = "Unnamed Application");
        virtual ~App(void);
    public:
        virtual void run(void);
    public: 
        inline static App* Get(void) { return App::s_This; }

        inline const WindowData& get_window_data(void) const { return this->window_data; }

        void set_window_pos(int32_t x = SDL_WINDOWPOS_CENTERED, int32_t y = SDL_WINDOWPOS_CENTERED);
        inline void set_window_pos(const WindowPos& pos) { App::set_window_pos(pos.x, pos.y); }
        inline void set_window_pos(const WindowPosR& pos) { App::set_window_pos(pos.x, pos.y); }

        void set_window_x(int32_t x);
        void set_window_y(int32_t y);

        void set_window_size(uint32_t w, uint32_t h);
        inline void set_window_size(const WindowSize& size) { App::set_window_size(size.w, size.h); }
        inline void set_window_size(const WindowSizeR& size)  { App::set_window_size(size.w, size.h); }

        void set_window_width(uint32_t w); 
        void set_window_height(uint32_t h);

        void increase_window_size(uint32_t w, uint32_t h);
        inline void increase_window_size(const WindowSize& size) { App::increase_window_size(size.w, size.h); }
        inline void increase_window_size(const WindowSizeR& size)  { App::increase_window_size(size.w, size.h); }

        void rename_window(const char* title);
        inline void set_window_title(const char* title) { App::rename_window(title); }

        inline int32_t get_window_x(void) { App::_get_window_pos(); return this->window_data.x; }
        inline int32_t get_window_y(void) { App::_get_window_pos(); return this->window_data.y; }

        inline WindowPos get_window_pos_c(void) { App::_get_window_pos(); return { this->window_data.x, this->window_data.y }; }
        inline WindowPosR get_window_pos(void)  { App::_get_window_pos(); return { this->window_data.x, this->window_data.y }; }

        inline void get_window_pos_r(int32_t& x, int32_t& y) { App::_get_window_pos();  x = this->window_data.x;  y = this->window_data.y; }
        inline void get_window_pos_p(int32_t* x, int32_t* y) { App::_get_window_pos(); *x = this->window_data.x; *y = this->window_data.y; }

        inline uint32_t get_window_width(void)  { App::_get_window_size(); return this->window_data.w; }
        inline uint32_t get_window_height(void) { App::_get_window_size(); return this->window_data.h; }

        inline WindowSize get_window_size_c(void) { App::_get_window_size(); return { this->window_data.w, this->window_data.h }; }
        inline WindowSizeR get_window_size(void)  { App::_get_window_size(); return { this->window_data.w, this->window_data.h }; }

        inline void get_window_size_r(uint32_t& w, uint32_t& h) { App::_get_window_size();  w = this->window_data.w;  h = this->window_data.h; }
        inline void get_window_size_p(uint32_t* w, uint32_t* h) { App::_get_window_size(); *w = this->window_data.w; *h = this->window_data.h; }

        inline WindowRect get_window_rect_c(void) { App::_get_window_rect(); return { this->window_data.x, this->window_data.y, this->window_data.w, this->window_data.h }; }
        inline WindowRectR get_window_rect(void)  { App::_get_window_rect(); return { this->window_data.x, this->window_data.y, this->window_data.w, this->window_data.h }; }

        inline void get_window_rect_r(int32_t& x, int32_t& y, uint32_t& w, uint32_t& h) { App::_get_window_rect();  x = this->window_data.x;  y = this->window_data.y;  w = this->window_data.w;  h = this->window_data.h; }
        inline void get_window_rect_p(int32_t* x, int32_t* y, uint32_t* w, uint32_t* h) { App::_get_window_rect(); *x = this->window_data.x; *y = this->window_data.y; *w = this->window_data.w; *h = this->window_data.h; }

        inline SDL_Window* get_window(void)     { return this->window; }
        inline SDL_Renderer* get_renderer(void) { return this->renderer; }

        inline bool should_close(void) const { return this->_should_close; }
        inline void close(bool value = true) { this->_should_close = value; }

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
        SDL_Window* window;
        SDL_Renderer* renderer;

        bool _should_close;
        WindowData window_data;

    private:
        static App* s_This;
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
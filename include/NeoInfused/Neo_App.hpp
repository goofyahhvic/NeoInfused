#if !defined(NEO_APP_HPP)
#define NEO_APP_HPP

#include "NeoInfused/Core/Neo_Core.hpp"
#include "./Layer/Neo_Layer.hpp"
#include "./Neo_Renderer.hpp"

namespace neo {
    struct WindowData {
        int32_t x, y;
        uint32_t w, h;
        std::string title;
    };
    class App {
    public:
        App(int32_t x = SDL_WINDOWPOS_CENTERED, int32_t y = SDL_WINDOWPOS_CENTERED, uint32_t w = 1280, uint32_t h = 720, const char* title = "Unnamed Application");
        virtual ~App(void);
    public:
        virtual void run(void);
    public: 
        inline static App* Get(void) { return App::m_This; }

        inline const WindowData& get_window_data(void) const { return m_WindowData; }

        void set_window_pos(int32_t x, int32_t y);
        void set_window_x(int32_t x);
        void set_window_y(int32_t y);
        void center_window(void);

        void set_window_size(uint32_t w, uint32_t h);
        void set_window_width(uint32_t w); 
        void set_window_height(uint32_t h);
        void increase_window_size(uint32_t w, uint32_t h);

        void rename_window(const char* title);
        inline void set_window_title(const char* title) { this->rename_window(title); }

        inline int32_t get_window_x(void) { this->_get_window_pos(); return this->m_WindowData.x; }
        inline int32_t get_window_y(void) { this->_get_window_pos(); return this->m_WindowData.y; }

        inline void get_window_pos(int32_t& x, int32_t& y) { this->_get_window_pos();  x = this->m_WindowData.x;  y = this->m_WindowData.y; }
        inline void get_window_pos(int32_t* x, int32_t* y) { this->_get_window_pos(); *x = this->m_WindowData.x; *y = m_WindowData.y; }

        inline uint32_t get_window_width(void)  { this->_get_window_size(); return m_WindowData.w; }
        inline uint32_t get_window_height(void) { this->_get_window_size(); return m_WindowData.h; }

        inline void get_window_size(uint32_t& w, uint32_t& h) { this->_get_window_size();  w = m_WindowData.w;  h = m_WindowData.h; }
        inline void get_window_size(uint32_t* w, uint32_t* h) { this->_get_window_size(); *w = m_WindowData.w; *h = m_WindowData.h; }

        inline void get_window_rect(int32_t& x, int32_t& y, uint32_t& w, uint32_t& h) { this->_get_window_pos();  x = m_WindowData.x;  y = m_WindowData.y;  w = m_WindowData.w;  h = m_WindowData.h; }
        inline void get_window_rect(int32_t* x, int32_t* y, uint32_t* w, uint32_t* h) { this->_get_window_rect(); *x = m_WindowData.x; *y = m_WindowData.y; *w = m_WindowData.w; *h = m_WindowData.h; }

        inline SDL_Window* get_window(void) { return m_Window; }
        inline Renderer& get_renderer(void) { return m_Renderer; }

        inline bool should_close(void) const { return m_ShouldClose; }
        inline void close(bool value = true) { m_ShouldClose = value; }
    protected:
        virtual void _update(void);
        virtual void _draw(void);
        virtual void _handle_event(SDL_Event* e);
    private:
        void _get_window_pos(void);
        void _get_window_size(void);
        void _get_window_rect(void);
    protected:
        SDL_Window* m_Window;
        Renderer m_Renderer;

        bool m_ShouldClose;
        WindowData m_WindowData;

        std::deque<Layer*> m_Layers;
    private:
        static App* m_This;
    };
} // namespace neo

#endif // NEO_APP_HPP
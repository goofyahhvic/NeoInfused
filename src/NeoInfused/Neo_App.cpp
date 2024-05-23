#include "Neo_PCH.hpp"
#include "NeoInfused/Neo_App.hpp"

namespace neo {
    App* App::m_This;

    App::App(int32_t x, int32_t y, uint32_t w, uint32_t h, const char* title)
        : m_Window(nullptr), m_Renderer(), m_ShouldClose(false), m_Layers() {
        NEO_ASSERT(!App::m_This, "Cannot create multiple instances of neo::App!");
        App::m_This = this;

        m_WindowData.x = x;
        m_WindowData.y = y;
        m_WindowData.w = w;
        m_WindowData.h = h;
        m_WindowData.title = std::string(title);

        m_Window = SDL_CreateWindow(
            m_WindowData.title.c_str(),
            m_WindowData.x, m_WindowData.y,
            m_WindowData.w, m_WindowData.h,
            SDL_WINDOW_SHOWN
        );
        NEO_ASSERT(m_Window, "Failed to create SDL_Window: {0}", SDL_GetError());

        m_Renderer = Renderer(m_Window, SDL_RENDERER_ACCELERATED);
        Renderer::Bind(&m_Renderer);
        m_Renderer.set_draw_color();
    }
    App::~App(void) {
        m_Renderer.destroy();
        SDL_DestroyWindow(m_Window);
    }
 
    void App::run(void) {
        while (!m_ShouldClose) {
            m_Renderer.clear();

            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    m_ShouldClose = true;
                    goto EndLoop;
                }
                this->_handle_event(&e);
            }
            this->_update();
            this->_draw();
            EndLoop:
            m_Renderer.present();
        }
    }
    void App::_handle_event(SDL_Event* e) {
        for (auto layer : m_Layers) {
            if (layer->enabled()) {
                if (layer->handle_event(e))
                    continue;
                else
                    break;
            }
        }
    }
    void App::_update(void) {
        for (auto layer : m_Layers) {
            if (layer->enabled()) {
                layer->update();
            }
        }
    }
    void App::_draw(void) {
        for (auto layer : m_Layers) {
            if (layer->enabled()) {
                layer->draw();
            }
        }
    }

    void App::set_window_pos(int32_t x, int32_t y) {
        m_WindowData.x = x;
        m_WindowData.y = y;
        SDL_SetWindowPosition(m_Window, x, y);
    }
    void App::set_window_x(int32_t x) {
        m_WindowData.x = x;
        SDL_SetWindowPosition(m_Window, x, m_WindowData.y);
    }
    void App::set_window_y(int32_t y) {
        m_WindowData.y = y;
        SDL_SetWindowPosition(m_Window, m_WindowData.x, y);
    }
    void App::center_window(void) {
        m_WindowData.x = SDL_WINDOWPOS_CENTERED;
        m_WindowData.y = SDL_WINDOWPOS_CENTERED;
        SDL_SetWindowPosition(m_Window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    }

    void App::set_window_size(uint32_t w, uint32_t h) {
        m_WindowData.w = w;
        m_WindowData.h = h;
        SDL_SetWindowSize(m_Window, w, h);
    }
    void App::set_window_width(uint32_t w)  {
        m_WindowData.w = w;
        SDL_SetWindowSize(m_Window, w, m_WindowData.h);
    }
    void App::set_window_height(uint32_t h) {
        m_WindowData.h = h;
        SDL_SetWindowSize(m_Window, m_WindowData.w, h);
    }
    void App::increase_window_size(uint32_t w, uint32_t h) {
        m_WindowData.w += w;
        m_WindowData.h += h;
        SDL_SetWindowSize(m_Window, m_WindowData.w, m_WindowData.h);
    }

    void App::rename_window(const char* title) {
        m_WindowData.title = std::string(title);
        SDL_SetWindowTitle(m_Window, title);
    }

    void App::_get_window_pos(void)  {
        int x, y = 0;
        SDL_GetWindowPosition(m_Window, &x, &y);
        m_WindowData.x = x;
        m_WindowData.y = y;
    }
    void App::_get_window_size(void) {
        int w, h = 0;
        SDL_GetWindowSize(m_Window, &w, &h);
        m_WindowData.w = w;
        m_WindowData.h = h;
    }
    void App::_get_window_rect(void) {
        SDL_Rect rect {};
        SDL_GetWindowPosition(m_Window, &rect.x, &rect.y);
        SDL_GetWindowSize(m_Window, &rect.w, &rect.h);
        m_WindowData.x = rect.x;
        m_WindowData.y = rect.y;
        m_WindowData.w = rect.w;
        m_WindowData.h = rect.h;
    }

} // namespace neo

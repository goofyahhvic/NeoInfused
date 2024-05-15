#include "Neo_PCH.hpp"
#include "NeoInfused/Neo_App.hpp"

namespace neo {
    App* App::sm_This;

    App::App(int32_t x, int32_t y, size_t w, size_t h, const char* title)
        : m_Window(nullptr), m_Renderer(nullptr), m_Close(false) {
        NEO_ASSERT(!sm_This, "Cannot create multiple instances of neo::App!");
        sm_This = this;

        m_WindowData.x = x;
        m_WindowData.y = y;
        m_WindowData.w = w;
        m_WindowData.h = h;
        m_WindowData.title = std::string(title);

        App::init_sdl();
    }
    App::~App(void) {
        App::cleanup_sdl();
    }
 
    void App::run(void) {
        while (!m_Close) {
            SDL_RenderClear(m_Renderer);

            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    m_Close = true;
                    goto EndLoop;
                }
                this->handle_event(&e);
            }
            this->update();
            this->draw();
            EndLoop:
            SDL_RenderPresent(m_Renderer);
        }
    }
    void App::handle_event(SDL_Event* e) {}
    void App::update(void) {}
    void App::draw(void) {}

    void App::init_sdl(void) {
        int flags;

        flags = SDL_INIT_EVERYTHING;
        NEO_ASSERT_FUNC(!SDL_Init(flags), "Failed to initialize SDL: {0}", SDL_GetError());
        
        flags = SDL_WINDOW_SHOWN;
        m_Window = SDL_CreateWindow(
            m_WindowData.title.c_str(),
            m_WindowData.x, m_WindowData.y,
            m_WindowData.w, m_WindowData.h,
            flags
        );
        NEO_ASSERT(m_Window, "Failed to create SDL_Window: {0}", SDL_GetError());

        flags = SDL_RENDERER_ACCELERATED;
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

        m_Renderer = SDL_CreateRenderer(m_Window, -1, flags);
        NEO_ASSERT(m_Renderer, "Failed to create SDL_Renderer: {0}", SDL_GetError());
        SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);

        IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    }
    void App::cleanup_sdl(void) {
        IMG_Quit();

        SDL_DestroyRenderer(m_Renderer);
        SDL_DestroyWindow(m_Window);
        SDL_Quit();
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

    void App::set_window_size(size_t w, size_t h) {
        m_WindowData.w = w;
        m_WindowData.h = h;
        SDL_SetWindowSize(m_Window, w, h);
    }
    void App::set_window_width(size_t w)  {
        m_WindowData.w = w;
        SDL_SetWindowSize(m_Window, w, m_WindowData.h);
    }
    void App::set_window_height(size_t h) {
        m_WindowData.h = h;
        SDL_SetWindowSize(m_Window, m_WindowData.w, h);
    }
    void App::increase_window_size(size_t w, size_t h) {
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

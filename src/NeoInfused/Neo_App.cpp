#include "Neo_PCH.hpp"
#include "NeoInfused/Neo_App.hpp"

namespace neo {
    App* App::s_This;

    App::App(int32_t x, int32_t y, size_t w, size_t h, const char* title)
        : window(nullptr), renderer(nullptr), _should_close(false) {
        NEO_ASSERT(!App::s_This, "Cannot create multiple instances of neo::App!");
        App::s_This = this;

        this->window_data.x = x;
        this->window_data.y = y;
        this->window_data.w = w;
        this->window_data.h = h;
        this->window_data.title = std::string(title);

        App::init_sdl();
    }
    App::~App(void) {
        App::cleanup_sdl();
    }
 
    void App::run(void) {
        while (!this->_should_close) {
            SDL_RenderClear(renderer);

            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    this->_should_close = true;
                    goto EndLoop;
                }
                this->handle_event(&e);
            }
            this->update();
            this->draw();
            EndLoop:
            SDL_RenderPresent(renderer);
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
        this->window = SDL_CreateWindow(
            this->window_data.title.c_str(),
            this->window_data.x, this->window_data.y,
            this->window_data.w, this->window_data.h,
            flags
        );
        NEO_ASSERT(this->window, "Failed to create SDL_Window: {0}", SDL_GetError());

        flags = SDL_RENDERER_ACCELERATED;
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

        this->renderer = SDL_CreateRenderer(this->window, -1, flags);
        NEO_ASSERT(this->renderer, "Failed to create SDL_Renderer: {0}", SDL_GetError());
        SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);

        IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    }
    void App::cleanup_sdl(void) {
        IMG_Quit();

        SDL_DestroyRenderer(this->renderer);
        SDL_DestroyWindow(this->window);
        SDL_Quit();
    }

    void App::set_window_pos(int32_t x, int32_t y) {
        this->window_data.x = x;
        this->window_data.y = y;
        SDL_SetWindowPosition(this->window, x, y);
    }
    void App::set_window_x(int32_t x) {
        this->window_data.x = x;
        SDL_SetWindowPosition(this->window, x, window_data.y);
    }
    void App::set_window_y(int32_t y) {
        this->window_data.y = y;
        SDL_SetWindowPosition(this->window, window_data.x, y);
    }

    void App::set_window_size(size_t w, size_t h) {
        this->window_data.w = w;
        this->window_data.h = h;
        SDL_SetWindowSize(this->window, w, h);
    }
    void App::set_window_width(size_t w)  {
        this->window_data.w = w;
        SDL_SetWindowSize(this->window, w, window_data.h);
    }
    void App::set_window_height(size_t h) {
        this->window_data.h = h;
        SDL_SetWindowSize(this->window, window_data.w, h);
    }
    void App::increase_window_size(size_t w, size_t h) {
        this->window_data.w += w;
        this->window_data.h += h;
        SDL_SetWindowSize(this->window, window_data.w, window_data.h);
    }

    void App::rename_window(const char* title) {
        this->window_data.title = std::string(title);
        SDL_SetWindowTitle(this->window, title);
    }

    void App::_get_window_pos(void)  {
        int x, y = 0;
        SDL_GetWindowPosition(this->window, &x, &y);
        this->window_data.x = x;
        this->window_data.y = y;
    }
    void App::_get_window_size(void) {
        int w, h = 0;
        SDL_GetWindowSize(this->window, &w, &h);
        this->window_data.w = w;
        this->window_data.h = h;
    }
    void App::_get_window_rect(void) {
        SDL_Rect rect {};
        SDL_GetWindowPosition(this->window, &rect.x, &rect.y);
        SDL_GetWindowSize(this->window, &rect.w, &rect.h);
        this->window_data.x = rect.x;
        this->window_data.y = rect.y;
        this->window_data.w = rect.w;
        this->window_data.h = rect.h;
    }

} // namespace neo

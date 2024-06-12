#include "Neo_PCH.hpp"
#include "NeoInfused/Neo_Window.hpp"

namespace neo {
    Window* Window::m_BoundWindow = nullptr;
    std::unordered_map<uint32_t, Window*> Window::m_Windows;

    Window::Display::Display(Window* window)
        : m_Window(window) {

    }
    void Window::Display::clear(Color color) {
        SDL_FillRect(
            m_Window->m_DrawSurface,
            nullptr,
            color.rgba
        );
    }
    void Window::Display::present(void) {
        SDL_BlitScaled(m_Window->m_DrawSurface, nullptr, m_Window->m_WindowSurface, nullptr);
        SDL_UpdateWindowSurface(m_Window->m_Window);
    }

    Color* Window::Display::at(uint32_t x, uint32_t y) {
        return &((Color*)m_Window->m_DrawSurface->pixels)[x + (y * m_Window->m_DrawSurface->w)];
    }
    void Window::Display::set_at(uint32_t x, uint32_t y, Color color) {
        ((Color*)m_Window->m_DrawSurface->pixels)[x + (y * m_Window->m_DrawSurface->w)] = color;
    }

    void Window::Display::blit(SDL_Surface* surface, SDL_Rect* position, SDL_Rect* portion) {
        SDL_BlitScaled(surface, portion, m_Window->m_DrawSurface, position);
    }

    void Window::Display::update_size(void) {
        m_Window->m_WindowSurface = SDL_GetWindowSurface(m_Window->m_Window);
        
        SDL_Surface* new_draw_surface = SDL_CreateRGBSurfaceWithFormat(
            0,
            m_Window->m_WindowSurface->w, m_Window->m_WindowSurface->h,
            32, SDL_PIXELFORMAT_RGBA32
        );

        SDL_FreeSurface(m_Window->m_DrawSurface);
        m_Window->m_DrawSurface = new_draw_surface;
    }

    void Window::Init(void) {

    }
    void Window::Cleanup(void) {
        if (Window::m_Windows.empty()) return;
        for (const auto& [id, window] : Window::m_Windows)
            SDL_DestroyWindow(window->m_Window);
        Window::m_Windows.clear();
    }

    Window* Window::New(const Window::CreateInfo& info) {
        Window* _this = new Window;
        _this->m_Window = SDL_CreateWindow(
            info.title.c_str(),
            info.x, info.y,
            info.width, info.height,
            SDL_WINDOW_RESIZABLE
        );
        _this->m_WindowSurface = SDL_GetWindowSurface(_this->m_Window);
        _this->m_DrawSurface = SDL_CreateRGBSurfaceWithFormat(0, info.draw_width, info.draw_height, 32, SDL_PIXELFORMAT_RGBA32);
        _this->m_Display = new Display(_this);

        Window::m_Windows[SDL_GetWindowID(_this->m_Window)] = _this;
        if (!Window::m_BoundWindow) Window::m_BoundWindow = _this;

        return _this;
    }
    void Window::Delete(Window* _this) {
        if (!_this->m_Window) return;
        if (_this == Window::m_BoundWindow)
            Window::m_BoundWindow = nullptr;
        
        delete _this->m_Display;
        SDL_FreeSurface(_this->m_DrawSurface);
        Window::m_Windows.erase(SDL_GetWindowID(_this->m_Window));
        SDL_DestroyWindow(_this->m_Window);
        delete _this;
    }

    uint32_t Window::GetID(SDL_Window* window) {
        return SDL_GetWindowID(window);
    }
    SDL_Window* Window::GetNativeFromID(uint32_t id) {
        return SDL_GetWindowFromID(id);
    }

    void Window::rename(const char* new_title) {
        SDL_SetWindowTitle(m_Window, new_title);
    }
} // namespace neo

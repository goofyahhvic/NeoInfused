#include "Neo_PCH.hpp"
#include "NeoInfused/Neo_Window.hpp"

namespace neo {
    Window* Window::m_BoundWindow = nullptr;
    std::unordered_map<uint32_t, Window*> Window::m_Windows;

    void Window::present_display(void) {
        SDL_BlitScaled(m_Display->surface(), nullptr, SDL_GetWindowSurface(m_Window), nullptr);
        SDL_UpdateWindowSurface(m_Window);
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
        _this->m_Display = new Graphic2D(info.display_width, info.display_height);

        Window::m_Windows[SDL_GetWindowID(_this->m_Window)] = _this;
        if (!Window::m_BoundWindow) Window::m_BoundWindow = _this;

        return _this;
    }
    void Window::Delete(Window* _this) {
        if (!_this->m_Window) return;
        if (_this == Window::m_BoundWindow)
            Window::m_BoundWindow = nullptr;
        
        delete _this->m_Display;
        Window::m_Windows.erase(SDL_GetWindowID(_this->m_Window));
        SDL_DestroyWindow(_this->m_Window);
        delete _this;
    }

    void Window::set_width(uint32_t new_width) {
        SDL_SetWindowSize(m_Window, new_width, SDL_GetWindowSurface(m_Window)->h);
    }
    void Window::set_height(uint32_t new_height) {
        SDL_SetWindowSize(m_Window, SDL_GetWindowSurface(m_Window)->w, new_height);
    }
    void Window::set_size(uint32_t new_width, uint32_t new_height) {
        SDL_SetWindowSize(m_Window, new_width, new_height);
    }
    void Window::increase_size(uint32_t width_amount, uint32_t height_amount) {
        SDL_SetWindowSize(m_Window, width_amount + SDL_GetWindowSurface(m_Window)->w, height_amount + SDL_GetWindowSurface(m_Window)->h);
    }
    void Window::update_pos(void) {
        SDL_GetWindowPosition(m_Window, &m_X, &m_Y);
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

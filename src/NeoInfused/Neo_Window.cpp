#include "Neo_PCH.hpp"
#include "NeoInfused/Neo_Window.hpp"

namespace neo {
    Window* Window::m_BoundWindow;
    std::unordered_map<uint32_t, Window*> Window::m_Windows;

    void Window::Init(void) {
        Window::m_BoundWindow = nullptr;
    }
    void Window::Terminate(void) {
        if (Window::m_Windows.empty()) return;
        for (const auto& [id, window] : Window::m_Windows)
            SDL_DestroyWindow(window->m_Window);
        Window::m_Windows.clear();
    }

    Window* Window::New(const Window::CreateInfo& info) {
        Window* _this = new Window;
        _this->m_Data = info;
        _this->m_Window = SDL_CreateWindow(info.title.c_str(), info.x, info.y, info.w, info.h, info.flags);

        Window::m_Windows[SDL_GetWindowID(_this->m_Window)] = _this;
        if (!Window::m_BoundWindow) Window::m_BoundWindow = _this;

        return _this;
    }
    void Window::Delete(Window* _this) {
        if (!_this->m_Window) return;
        if (_this == Window::m_BoundWindow)
            Window::m_BoundWindow = nullptr;

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

    void Window::_update_pos(void) const {
        SDL_GetWindowPosition(m_Window, &(m_Data.x), &(m_Data.y));
    }
    void Window::_update_size(void) const {
        SDL_GetWindowSize(m_Window, &(m_Data.w), &(m_Data.h));
    }
    void Window::_update_rect(void) const {
        SDL_GetWindowPosition(m_Window, &(m_Data.x), &(m_Data.y));
        SDL_GetWindowSize(m_Window, &(m_Data.w), &(m_Data.h));
    }

    void Window::set_pos(int32_t x, int32_t y) {
        m_Data.x = x;
        m_Data.y = y;
        SDL_SetWindowPosition(m_Window, x, y);
    }
    void Window::set_x(int32_t x) {
        this->_update_pos();
        m_Data.x = x;
        SDL_SetWindowPosition(m_Window, x, m_Data.y);
    }
    void Window::set_y(int32_t y) {
        this->_update_pos();
        m_Data.y = y;
        SDL_SetWindowPosition(m_Window, m_Data.x, y);
    }

    void Window::set_size(int32_t w, int32_t h) {
        m_Data.w = w;
        m_Data.h = h;
        SDL_SetWindowSize(m_Window, w, h);
    }
    void Window::set_width(int32_t w) {
        this->_update_size();
        m_Data.w = w;
        SDL_SetWindowSize(m_Window, w, m_Data.h);
    }
    void Window::set_height(int32_t h) {
        this->_update_size();
        m_Data.h = h;
        SDL_SetWindowSize(m_Window, m_Data.w, h);
    }

    void Window::rename(const std::string& title) {
        m_Data.title = title;
        SDL_SetWindowTitle(m_Window, title.c_str());
    }
} // namespace neo

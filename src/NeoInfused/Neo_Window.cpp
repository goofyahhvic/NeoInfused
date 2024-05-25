#include "Neo_PCH.hpp"
#include "NeoInfused/Neo_Window.hpp"

namespace neo {
    Window* Window::m_BoundWindow;
    std::vector<SDL_Window*> Window::m_Windows;

    void Window::Init(void) {
        Window::m_BoundWindow = nullptr;
    }
    void Window::Terminate(void) {
        if (Window::m_Windows.empty()) return;
        for (auto window : Window::m_Windows)
            SDL_DestroyWindow(window);
        Window::m_Windows.clear();
    }

    Window* Window::New(const Window::CreateInfo& info) {
        Window* _this = new Window;

        _this->m_Data = info;
        _this->m_Window = SDL_CreateWindow(
            info.title.c_str(),
            info.x, info.y,
            info.w, info.h,
            info.flags
        );
        _this->m_Data.index = Window::m_Windows.size();
        Window::m_Windows.push_back(_this->m_Window);
        return _this;
    }
    void Window::Delete(Window* _this) {
        if (!_this->m_Window) return;
        Window::m_Windows.erase(Window::m_Windows.begin() + _this->m_Data.index);
        SDL_DestroyWindow(_this->m_Window);
        delete _this;
    }

    void Window::_update_pos(void) {
        SDL_GetWindowPosition(m_Window, &(m_Data.x), &(m_Data.y));
    }
    void Window::_update_size(void) {
        SDL_GetWindowSize(m_Window, &(m_Data.w), &(m_Data.h));
    }
    void Window::_update_rect(void) {
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

    void Window::set_rect(const Window::CopyRect& rect) {
        m_Data.x = rect.x;
        m_Data.y = rect.y;
        m_Data.w = rect.w;
        m_Data.h = rect.h;
        SDL_SetWindowPosition(m_Window, rect.x, rect.y);
        SDL_SetWindowSize(m_Window, rect.w, rect.h);
    }
    void Window::rename(const std::string& title) {
        m_Data.title = title;
        SDL_SetWindowTitle(m_Window, title.c_str());
    }
} // namespace neo

#include "Neo_PCH.hpp"
#include "NeoInfused/Neo_App.hpp"

namespace neo {
    App* App::m_This;

    App::App(const Window::CreateInfo& window_create_info) : m_Layers() {
        NEO_ASSERT(!App::m_This, "Cannot create multiple instances of neo::App!");
        App::m_This = this;

        m_Window = Window::New(window_create_info);
    }
    App::~App(void) {
        Window::Delete(m_Window);
    }
 
    void App::run(void) {
        while (!m_Window->should_close()) {
            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                this->_handle_event(&e);
            }
            
            m_Window->display()->fill(m_ClearColor);
            this->_update();
            this->_draw();
            m_Window->present_display();
        }
    }
    void App::_handle_event(SDL_Event* e) {
        switch (e->window.event) {
            case SDL_WINDOWEVENT_MOVED:
                m_Window->update_pos();
                break;
            case SDL_WINDOWEVENT_CLOSE:
                return Window::GetFromID(e->window.windowID)->close();
                break;
        }
        for (auto layer : m_Layers) {
            if (!layer->enabled()) continue;
            if (!layer->handle_event(e)) return;
        }
    }
    void App::_update(void) {
        for (auto layer : m_Layers) {
            if (!layer->enabled()) continue;
            layer->update();
        }
    }
    void App::_draw(void) {
        for (auto it = m_Layers.rbegin(); it != m_Layers.rend(); it++) {
            if (!(*it)->enabled()) continue;
            (*it)->draw();
        }
    }
} // namespace neo

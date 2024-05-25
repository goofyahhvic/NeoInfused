#include "Neo_PCH.hpp"
#include "NeoInfused/Neo_App.hpp"

namespace neo {
    App* App::m_This;

    App::App(const Window::CreateInfo& window_create_info)
        : m_ShouldClose(false), m_Layers() {
        NEO_ASSERT(!App::m_This, "Cannot create multiple instances of neo::App!");
        App::m_This = this;

        m_Window = Window::New(window_create_info);
        m_Window->bind();

        m_Renderer = Renderer::New(SDL_RENDERER_ACCELERATED);
        m_Renderer->bind();
        m_Renderer->set_draw_color();
    }
    App::~App(void) {
        Renderer::Delete(m_Renderer);
        Window::Delete(m_Window);
    }
 
    void App::run(void) {
        while (!m_ShouldClose) {
            m_Renderer->clear();

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
            m_Renderer->present();
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
} // namespace neo

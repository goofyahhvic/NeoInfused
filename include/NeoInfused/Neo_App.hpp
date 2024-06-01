#if !defined(NEO_APP_HPP)
#define NEO_APP_HPP

#include "./Layer/Neo_LayerGroup.hpp"
#include "./Neo_Window.hpp"
#include "./Neo_Renderer.hpp"

namespace neo {
    class App {
    public:
        App(const Window::CreateInfo& window_create_info);
        virtual ~App(void);
    public:
        virtual void run(void);
    public: 
        inline static App* Get(void) { return App::m_This; }

        inline Window* get_window(void) { return m_Window; }
        inline Renderer* get_renderer(void) { return m_Renderer; }
    protected:
        virtual void _update(void);
        virtual void _draw(void);
        virtual void _handle_event(SDL_Event* e);
    protected:
        Window* m_Window;
        Renderer* m_Renderer;

        LayerGroup m_Layers;
    private:
        static App* m_This;
    };
} // namespace neo

#endif // NEO_APP_HPP
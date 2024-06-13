#if !defined(NEO_APP_HPP)
#define NEO_APP_HPP

#include "./Layer/Neo_LayerGroup.hpp"
#include "./Neo_Window.hpp"

namespace neo {
    class App {
    public:
        App(const Window::CreateInfo& window_create_info);
        virtual ~App(void);
    public:
        virtual void run(void);

        inline static App* Get(void) { return App::m_This; }
        inline Window* window(void) { return m_Window; }
    protected:
        virtual void _update(void);
        virtual void _draw(void);
        virtual void _handle_event(SDL_Event* e);
    protected:
        Window* m_Window;
        LayerGroup m_Layers;
    private:
        static App* m_This;
    };
} // namespace neo

#endif // NEO_APP_HPP
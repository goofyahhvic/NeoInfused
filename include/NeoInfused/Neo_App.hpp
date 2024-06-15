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
        
        inline void set_clear_color(Color new_clear_color) { m_ClearColor = new_clear_color; }
        inline Color clear_color(void) const { return m_ClearColor; }

        inline static App* Get(void) { return App::m_This; }
        inline static const App* GetConst(void) { return App::m_This; }

        inline Window* window(void) { return m_Window; }
        inline const Window* window(void) const { return m_Window; }

        inline LayerGroup& layers(void) { return m_Layers; }
        inline const LayerGroup& layers(void) const { return m_Layers; }
    protected:
        virtual void _update(void);
        virtual void _draw(void);
        virtual void _handle_event(SDL_Event* e);
    protected:
        Window* m_Window;
        LayerGroup m_Layers;
        Color m_ClearColor = {0, 0, 0, 255};
    private:
        static App* m_This;
    };
} // namespace neo

#endif // NEO_APP_HPP
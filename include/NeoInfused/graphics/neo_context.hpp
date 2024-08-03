#if !defined(NEO_RENDERER_HPP)
#define NEO_RENDERER_HPP

#include "NeoInfused/core/neo_window.hpp"

enum neo_RendererAPI {
    NEO_RENDERERAPI_NONE = 0,
    NEO_RENDERERAPI_OPENGL,
    NEO_RENDERERAPI_VULKAN
#if defined(NEO_PLATFORM_WINDOWS)
   ,NEO_RENDERAPI_DIRECTX
#endif // NEO_PLATFORM_WINDOWS
};

namespace neo {
    using RendererAPI = neo_RendererAPI;
    class Context {
        friend class Core;
    public:
        static Context* Create_GL(void);
        static inline void Destroy(void) { delete Context::m_This; Context::m_This = nullptr; }
    
        [[nodiscard]] static inline Context& Get(void) { return *Context::m_This; }
        [[nodiscard]] static inline RendererAPI GetAPI(void) { return (RendererAPI)Context::m_API; }
        [[nodiscard]] static inline bool Initialized(void) { return Context::m_Initialized; }
    public:
        virtual void initialize(Window* window) = 0;
        virtual void terminate(void) = 0;

        virtual void set_viewport(Window* window, uint32_t width, uint32_t height) = 0;
        virtual void new_frame(Window* window, const glm::vec4& color = {0, 0, 0, 255}) = 0;
        virtual void present(Window* window) = 0;
    protected:
        static Context* m_This;
        static RendererAPI m_API;
        static bool m_Initialized;
    };
}

#endif // NEO_RENDERER_HPP
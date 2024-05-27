#if !defined(NEO_RENDERER_HPP)
#define NEO_RENDERER_HPP

#include "./Neo_Window.hpp"

namespace neo {
    class Renderer {
        Renderer(void) : m_Renderer(nullptr) {}
        ~Renderer(void) = default;
    public:
        static void Init(void);
        static void Terminate(void);    
        struct BlitInfo;
    public:
        static Renderer* New(int16_t flags, Window* window = Window::GetBound(), int16_t driver_index = -1);
        static void Delete(Renderer* _this);
    public:
        void blit(const BlitInfo& info) const;

        void clear(void);
        void present(void) const;

        void set_scale(float x, float y);
        void set_draw_color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 255);

        inline void bind(void) { Renderer::m_BoundRenderer = this; }
        static inline void Bind(Renderer* renderer) { Renderer::m_BoundRenderer = renderer; }
        static inline Renderer* GetBound(void) { return Renderer::m_BoundRenderer; }

        inline SDL_Renderer* get_native(void) { return m_Renderer; }
        inline const SDL_Renderer* get_native(void) const { return m_Renderer; }
        inline operator bool() const { return (m_Renderer); }
    private:
        SDL_Renderer* m_Renderer;
        size_t m_RendererIndex;
        static Renderer* m_BoundRenderer;
        static std::vector<SDL_Renderer*> m_Renderers;
    };

    struct Renderer::BlitInfo {
        SDL_Texture* texture;
        SDL_FRect* dest_rect;
        SDL_Rect* src_rect = nullptr;
        double angle = 0.0f;
        SDL_FPoint* center = nullptr;
        SDL_RendererFlip flip = SDL_FLIP_NONE;
    };
    using RendererBlitInfo = Renderer::BlitInfo;
} // namespace neo

#endif // NEO_RENDERER_HPP
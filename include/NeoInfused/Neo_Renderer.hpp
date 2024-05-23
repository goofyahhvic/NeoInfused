#if !defined(NEO_RENDERER_HPP)
#define NEO_RENDERER_HPP

namespace neo {
    class Renderer {
    public:
        Renderer(void) = default;
        ~Renderer(void) = default;
        struct BlitInfo;
    public:
        static void Init(void);
        static void Terminate(void);    
    public:
        Renderer(SDL_Window* window, int32_t flags);
        void destroy(void);
    public:
        void blit(SDL_Texture* texture, SDL_FRect* dest_rect = nullptr, SDL_Rect* src_rect = nullptr, double angle = 0.0f, SDL_FPoint* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
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
    private:
        SDL_Renderer* m_Renderer;
        static Renderer* m_BoundRenderer;
        static int32_t m_NewRendererIndex;
        static std::list<SDL_Renderer*> m_Renderers;
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
#if !defined(NEO_TEXTURE_HPP)
#define NEO_TEXTURE_HPP

#include "NeoInfused/Core/Neo_Core.hpp"
#include "NeoInfused/Neo_Renderer.hpp"

namespace neo {
    class Texture {
        Texture(void) = default;
        ~Texture(void) = default;
    public:
        struct DrawInfo {
            SDL_FRect* dest_rect = nullptr;
            SDL_Rect* src_rect = nullptr;
            double angle = 0.0f;
            SDL_FPoint* center = nullptr;
            SDL_RendererFlip flip = SDL_FLIP_NONE;
        };
    public:
        static Texture* New(const std::filesystem::path& path);
        static void Delete(Texture* _this);
    public:
        void set(const std::filesystem::path& path);
        inline void draw(const DrawInfo& info, Renderer* renderer = Renderer::GetBound()) const { renderer->blit({ m_Texture, info.dest_rect, info.src_rect, info.angle, info.center, info.flip }); }
        inline operator bool() const { return (bool)m_Texture; }
    private:
        SDL_Texture* m_Texture;
    };
} // namespace neo

#endif // NEO_TEXTURE_HPP
#if !defined(NEO_TEXTURE_HPP)
#define NEO_TEXTURE_HPP

#include "NeoInfused/Core/Neo_Core.hpp"
#include "NeoInfused/Neo_Window.hpp"

namespace neo {
    Color* GetPixelFromSurface(SDL_Surface* surface, int x, int y);
    void SetPixelFromSurface(SDL_Surface* surface, int x, int y, Color color);

    SDL_Surface* MirrorSurface_H(SDL_Surface* src);
    SDL_Surface* MirrorSurface_V(SDL_Surface* src);
    SDL_Surface* MirrorSurface_HV(SDL_Surface* src);

    class Texture {
        Texture(void) = default;
        ~Texture(void) = default;
    public:
        static Texture* New(const std::filesystem::path& path);
        static Texture* NewFrom(const Texture* src);

        static Texture* NewMirrored_H(const Texture* src);
        static Texture* NewMirrored_V(const Texture* src);
        static Texture* NewMirrored_HV(const Texture* src);

        static void Delete(Texture* _this);
    public:
        void mirror_h(void);
        void mirror_v(void);
        void mirror_hv(void);

        inline uint32_t surface_width(void) const { return m_Surface->w; }
        inline uint32_t surface_height(void) const { return m_Surface->h; }

        void set(const std::filesystem::path& path);
        inline void draw(SDL_Rect* position = nullptr, SDL_Rect* portion = nullptr, Window* window = Window::GetBound()) const { window->display()->blit(m_Surface, position, portion); }
        inline operator bool() const { return (bool)m_Surface; }
    private:
        SDL_Surface* m_Surface;
    };
} // namespace neo

#endif // NEO_TEXTURE_HPP
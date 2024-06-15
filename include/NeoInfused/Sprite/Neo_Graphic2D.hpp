#if !defined(NEO_GRAPHIC2D_HPP)
#define NEO_GRAPHIC2D_HPP

#include "NeoInfused/Core/Neo_Core.hpp"

namespace neo {
    inline Color GetPixelFromSurface(const SDL_Surface* surface, int x, int y) { return ((Color*)surface->pixels)[x + (y * surface->w)]; }
    inline void SetPixelFromSurface(SDL_Surface* surface, int x, int y, Color color) { ((Color*)surface->pixels)[x + (y * surface->w)] = color; }

    SDL_Surface* MirrorSurface_H(const SDL_Surface* src);
    SDL_Surface* MirrorSurface_V(const SDL_Surface* src);
    SDL_Surface* MirrorSurface_HV(const SDL_Surface* src);

    class Graphic2D {
    public:
        Graphic2D(void) : m_Surface(nullptr) {}
        Graphic2D(uint32_t width, uint32_t height);
        Graphic2D(uint32_t width, uint32_t height, Color* pixels);
        Graphic2D(const std::filesystem::path& image_path);

        void destroy(void) { SDL_FreeSurface(m_Surface); m_Surface = nullptr; }
        virtual ~Graphic2D(void) { this->destroy(); }

        virtual void clone(const Graphic2D* src);

        void CreateMirroredFrom_H(const Graphic2D* src);
        void CreateMirroredFrom_V(const Graphic2D* src);
        void CreateMirroredFrom_HV(const Graphic2D* src);
    public:
        virtual void blit(Graphic2D* where, SDL_Rect* position = nullptr, SDL_Rect* portion = nullptr) const;
        virtual void blit_stretch(Graphic2D* where, SDL_Rect* position = nullptr, SDL_Rect* portion = nullptr) const;

        virtual inline void fill(Color color = {0, 0, 0, 255}, SDL_Rect* portion = nullptr) { SDL_FillRect(m_Surface, portion, color.rgba); }

        virtual inline Color at(uint32_t x, uint32_t y) const { return GetPixelFromSurface(m_Surface, x, y); }
        virtual inline void set_at(uint32_t x, uint32_t y, Color color) { SetPixelFromSurface(m_Surface, x, y, color); }

        virtual void mirror_h(void);
        virtual void mirror_v(void);
        virtual void mirror_hv(void);

        virtual inline uint32_t width(void) const { return m_Surface->w; }
        virtual inline uint32_t height(void) const { return m_Surface->h; }
        inline SDL_Surface* surface(void) { return m_Surface; }
    protected:
        SDL_Surface* m_Surface;
    };
} // namespace neo

#endif // NEO_GRAPHIC2D_HPP
#if !defined(NEO_GRAPHIC2D_HPP)
#define NEO_GRAPHIC2D_HPP

#include "NeoInfused/Core/Neo_Core.hpp"
#include "NeoInfused/ECS/Neo_BasicComponents.hpp"

namespace neo {
    inline Color GetPixelFromSurface(const SDL_Surface* surface, int x, int y) { return ((Color*)surface->pixels)[x + (y * surface->w)]; }
    inline void SetPixelFromSurface(SDL_Surface* surface, int x, int y, Color color) { ((Color*)surface->pixels)[x + (y * surface->w)] = color; }

    SDL_Surface* MirrorSurface_H(const SDL_Surface* src);
    SDL_Surface* MirrorSurface_V(const SDL_Surface* src);
    SDL_Surface* MirrorSurface_HV(const SDL_Surface* src);

    class Graphic2D {
    public:
        inline Graphic2D(void) : m_Surface(nullptr) {}
        inline Graphic2D(uint32_t width, uint32_t height) { this->set_surface(width, height); }
        inline Graphic2D(uint32_t width, uint32_t height, Color* pixels) { this->set_surface(width, height, pixels); }
        inline Graphic2D(const std::filesystem::path& image_path) { this->set_surface(image_path); }

        void set_surface(uint32_t width, uint32_t height);
        void set_surface(uint32_t width, uint32_t height, Color* pixels);
        void set_surface(const std::filesystem::path& image_path);

        inline void destroy(void) { SDL_FreeSurface(m_Surface); m_Surface = nullptr; }
        virtual ~Graphic2D(void) { this->destroy(); }

        virtual void clone(const Graphic2D* src);

        void create_mirroredH_from(const Graphic2D* src);
        void create_mirroredV_from(const Graphic2D* src);
        void create_mirroredHV_from(const Graphic2D* src);
    public:
        virtual void blit(Graphic2D* where, const Vec4& position, SDL_Rect* portion = nullptr) const;
        virtual void blit_stretch(Graphic2D* where, const Vec4& position, SDL_Rect* portion = nullptr) const;

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
    
    void DrawSprite(const Graphic2D* what, Graphic2D* where, const Vec4& position, SDL_Rect* portion = nullptr);
} // namespace neo

#endif // NEO_GRAPHIC2D_HPP
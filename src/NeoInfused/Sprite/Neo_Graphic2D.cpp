#include "Neo_PCH.hpp"
#include "NeoInfused/Sprite/Neo_Graphic2D.hpp"

namespace neo {
    SDL_Surface* MirrorSurface_H(const SDL_Surface* src) {
        SDL_Surface* mirrored = SDL_CreateRGBSurface(0, src->w, src->h, src->format->BitsPerPixel, src->format->Rmask, src->format->Gmask, src->format->Bmask, src->format->Amask);
        for (int y = 0; y < src->h; y++) {
            for (int x = 0; x < src->w; x++) {
                SetPixelFromSurface(mirrored, x, y, GetPixelFromSurface(src, src->w - x - 1, y));
            }
        }
        return mirrored;
    }
    SDL_Surface* MirrorSurface_V(const SDL_Surface* src) {
        SDL_Surface* mirrored = SDL_CreateRGBSurface(0, src->w, src->h, src->format->BitsPerPixel, src->format->Rmask, src->format->Gmask, src->format->Bmask, src->format->Amask);
        for (int y = 0; y < src->h; y++) {
            for (int x = 0; x < src->w; x++) {
                SetPixelFromSurface(mirrored, x, y, GetPixelFromSurface(src, x, src->h - y - 1));
            }
        }
        return mirrored;
    }
    SDL_Surface* MirrorSurface_HV(const SDL_Surface* src) {
        SDL_Surface* mirrored = SDL_CreateRGBSurface(0, src->w, src->h, src->format->BitsPerPixel, src->format->Rmask, src->format->Gmask, src->format->Bmask, src->format->Amask);
        for (int y = 0; y < src->h; y++) {
            for (int x = 0; x < src->w; x++) {
                SetPixelFromSurface(mirrored, x, y, GetPixelFromSurface(src, src->w - x - 1, src->h - y - 1));
            }
        }
        return mirrored;
    }

    Graphic2D::Graphic2D(uint32_t width, uint32_t height) {
        m_Surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);
    }
    Graphic2D::Graphic2D(uint32_t width, uint32_t height, Color* pixels) {
        m_Surface = SDL_CreateRGBSurfaceWithFormatFrom(pixels, width, height, 32, width*4, SDL_PIXELFORMAT_RGBA32);
    }
    Graphic2D::Graphic2D(const std::filesystem::path& image_path) {
        if (!std::filesystem::exists(image_path)) {
            NEO_ERROR_LOG("Failed to load image in {0}", image_path.C_STR);
            m_Surface = SDL_CreateRGBSurfaceWithFormat(0, 2, 2, 32, SDL_PIXELFORMAT_RGBA32);
            SetPixelFromSurface(m_Surface, 0, 0, {0, 0, 0, 255});
            SetPixelFromSurface(m_Surface, 1, 1, {0, 0, 0, 255});
            SetPixelFromSurface(m_Surface, 0, 1, {255, 100, 255, 255});
            SetPixelFromSurface(m_Surface, 1, 0, {255, 100, 255, 255});
            return;
        }
        m_Surface = IMG_Load(image_path.C_STR);
    }

    void Graphic2D::CreateMirroredFrom_H(const Graphic2D* src) {
        m_Surface = MirrorSurface_H(src->m_Surface);
    }
    void Graphic2D::CreateMirroredFrom_V(const Graphic2D* src) {
        m_Surface = MirrorSurface_V(src->m_Surface);
    }
    void Graphic2D::CreateMirroredFrom_HV(const Graphic2D* src) {
        m_Surface = MirrorSurface_HV(src->m_Surface);
    }

    void Graphic2D::blit(Graphic2D* where, SDL_Rect* position, SDL_Rect* portion) const {
        SDL_BlitSurface(m_Surface, portion, where->m_Surface, position);
    }
    void Graphic2D::blit_stretch(Graphic2D* where, SDL_Rect* position, SDL_Rect* portion) const {
        SDL_BlitScaled(m_Surface, portion, where->m_Surface, position);
    }

    void Graphic2D::mirror_h(void) {
        SDL_Surface* mirrored = MirrorSurface_H(m_Surface);
        SDL_FreeSurface(m_Surface);
        m_Surface = mirrored;
    }
    void Graphic2D::mirror_v(void) {
        SDL_Surface* mirrored = MirrorSurface_V(m_Surface);
        SDL_FreeSurface(m_Surface);
        m_Surface = mirrored;
    }
    void Graphic2D::mirror_hv(void) {
        SDL_Surface* mirrored = MirrorSurface_HV(m_Surface);
        SDL_FreeSurface(m_Surface);
        m_Surface = mirrored;
    }

    Graphic2D::Graphic2D(const Graphic2D& src) {
        m_Surface = SDL_CreateRGBSurface(
            0, src.m_Surface->w, src.m_Surface->h,
            src.m_Surface->format->BitsPerPixel,
            src.m_Surface->format->Rmask,
            src.m_Surface->format->Gmask,
            src.m_Surface->format->Bmask,
            src.m_Surface->format->Amask
        );
        SDL_BlitSurface(src.m_Surface, nullptr, m_Surface, nullptr);
    }
    Graphic2D::Graphic2D(const Graphic2D* src) {
        m_Surface = SDL_CreateRGBSurface(
            0, src->m_Surface->w, src->m_Surface->h,
            src->m_Surface->format->BitsPerPixel,
            src->m_Surface->format->Rmask,
            src->m_Surface->format->Gmask,
            src->m_Surface->format->Bmask,
            src->m_Surface->format->Amask
        );
        SDL_BlitSurface(src->m_Surface, nullptr, m_Surface, nullptr);
    }
    void Graphic2D::operator=(const Graphic2D& src) {
        m_Surface = SDL_CreateRGBSurface(
            0, src.m_Surface->w, src.m_Surface->h,
            src.m_Surface->format->BitsPerPixel,
            src.m_Surface->format->Rmask,
            src.m_Surface->format->Gmask,
            src.m_Surface->format->Bmask,
            src.m_Surface->format->Amask
        );
        SDL_BlitSurface(src.m_Surface, nullptr, m_Surface, nullptr);
    }
} // namespace neo

#include "Neo_PCH.hpp"
#include "NeoInfused/Sprite/Neo_Texture.hpp"

namespace neo {
    Color* GetPixelFromSurface(SDL_Surface* surface, int x, int y) {
        return &((Color*)surface->pixels)[x + (y * surface->w)];
    }
    void SetPixelFromSurface(SDL_Surface* surface, int x, int y, Color color) {
        ((Color*)surface->pixels)[x + (y * surface->w)] = color;
    }

    SDL_Surface* MirrorSurface_H(SDL_Surface* src) {
        SDL_Surface* mirrored = SDL_CreateRGBSurface(0, src->w, src->h, src->format->BitsPerPixel, src->format->Rmask, src->format->Gmask, src->format->Bmask, src->format->Amask);
        for (int y = 0; y < src->h; y++) {
            for (int x = 0; x < src->w; x++) {
                SetPixelFromSurface(mirrored, x, y, *GetPixelFromSurface(src, src->w - x - 1, y));
            }
        }
        return mirrored;
    }
    SDL_Surface* MirrorSurface_V(SDL_Surface* src) {
        SDL_Surface* mirrored = SDL_CreateRGBSurface(0, src->w, src->h, src->format->BitsPerPixel, src->format->Rmask, src->format->Gmask, src->format->Bmask, src->format->Amask);
        for (int y = 0; y < src->h; y++) {
            for (int x = 0; x < src->w; x++) {
                SetPixelFromSurface(mirrored, x, y, *GetPixelFromSurface(src, x, src->h - y - 1));
            }
        }
        return mirrored;
    }
    SDL_Surface* MirrorSurface_HV(SDL_Surface* src) {
        SDL_Surface* mirrored = SDL_CreateRGBSurface(0, src->w, src->h, src->format->BitsPerPixel, src->format->Rmask, src->format->Gmask, src->format->Bmask, src->format->Amask);
        for (int y = 0; y < src->h; y++) {
            for (int x = 0; x < src->w; x++) {
                SetPixelFromSurface(mirrored, x, y, *GetPixelFromSurface(src, src->w - x - 1, src->h - y - 1));
            }
        }
        return mirrored;
    }
    Texture* Texture::New(const std::filesystem::path& path) {
        Texture* _this = new Texture;
        if (!std::filesystem::exists(path)) {
            NEO_ERROR_LOG("Failed to load image in {0}", path.C_STR);
            _this->m_Surface = SDL_CreateRGBSurfaceWithFormat(0, 2, 2, 32, SDL_PIXELFORMAT_RGBA32);
            ((Color*)_this->m_Surface->pixels)[0 + (0 * _this->m_Surface->w)] = { 0,   0, 0,   255 };
            ((Color*)_this->m_Surface->pixels)[1 + (1 * _this->m_Surface->w)] = { 0,   0, 0,   255 };
            ((Color*)_this->m_Surface->pixels)[1 + (0 * _this->m_Surface->w)] = { 255, 100, 255, 255 };
            ((Color*)_this->m_Surface->pixels)[0 + (1 * _this->m_Surface->w)] = { 255, 100, 255, 255 };
            
            return _this;
        }
        NEO_TRACE_LOG("Loading texture from {0}", path.C_STR);
        _this->m_Surface = IMG_Load(path.C_STR);
        return _this;
    }
    Texture* Texture::NewFrom(const Texture* src) {
        Texture* _this = new Texture;
        _this->m_Surface = SDL_CreateRGBSurface(
            0, src->m_Surface->w, src->m_Surface->h,
            src->m_Surface->format->BitsPerPixel,
            src->m_Surface->format->Rmask,
            src->m_Surface->format->Gmask,
            src->m_Surface->format->Bmask,
            src->m_Surface->format->Amask
        );
        SDL_BlitSurface(src->m_Surface, nullptr, _this->m_Surface, nullptr);
        return _this;
    }
    void Texture::Delete(Texture* _this) {
        if (!_this) return;
        SDL_FreeSurface(_this->m_Surface);
        delete _this;
    }

    Texture* Texture::NewMirrored_H(const Texture* src) {
        Texture* _this = new Texture;
        _this->m_Surface = MirrorSurface_H(src->m_Surface);
        return _this;
    }
    Texture* Texture::NewMirrored_V(const Texture* src) {
        Texture* _this = new Texture;
        _this->m_Surface = MirrorSurface_V(src->m_Surface);
        return _this;
    }
    Texture* Texture::NewMirrored_HV(const Texture* src) {
        Texture* _this = new Texture;
        _this->m_Surface = MirrorSurface_HV(src->m_Surface);
        return _this;
    }

    void Texture::mirror_h(void) {
        SDL_Surface* mirrored = MirrorSurface_H(m_Surface);
        SDL_FreeSurface(m_Surface);
        m_Surface = mirrored;
    }
    void Texture::mirror_v(void) {
        SDL_Surface* mirrored = MirrorSurface_V(m_Surface);
        SDL_FreeSurface(m_Surface);
        m_Surface = mirrored;
    }
    void Texture::mirror_hv(void) {
        SDL_Surface* mirrored = MirrorSurface_HV(m_Surface);
        SDL_FreeSurface(m_Surface);
        m_Surface = mirrored;
    }

    void Texture::set(const std::filesystem::path& path) {
        if (!std::filesystem::exists(path)) {
            NEO_ERROR_LOG("Failed to load image in {0}", path.C_STR);
            return;
        }
        if (!m_Surface) {
            NEO_TRACE_LOG("Loading texture from {0}", path.C_STR);
            m_Surface = IMG_Load(path.C_STR);
            return;
        }
        SDL_FreeSurface(m_Surface);
        NEO_TRACE_LOG("Loading texture from {0}", path.C_STR);
        m_Surface = IMG_Load(path.C_STR);
    }
} // namespace neo

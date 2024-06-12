#include "Neo_PCH.hpp"
#include "NeoInfused/Sprite/Neo_Texture.hpp"

namespace neo {
    void ddddddraw(void) {}
    Texture* Texture::New(const std::filesystem::path& path) {
        Texture* _this = new Texture;
        if (!std::filesystem::exists(path)) {
            NEO_ERROR_LOG("Failed to load image in {0}", path.C_STR);
            _this->m_Surface = SDL_CreateRGBSurfaceWithFormat(0, 2, 2, 32, SDL_PIXELFORMAT_RGBA32);
            ((Color*)_this->m_Surface->pixels)[0 + (0 * _this->m_Surface->w)] = { 0,   0, 0,   255 };
            ((Color*)_this->m_Surface->pixels)[1 + (1 * _this->m_Surface->w)] = { 0,   0, 0,   255 };
            ((Color*)_this->m_Surface->pixels)[1 + (0 * _this->m_Surface->w)] = { 255, 100, 255, 255 };
            ((Color*)_this->m_Surface->pixels)[0 + (1 * _this->m_Surface->w)] = { 255, 100, 255, 255 };

            ddddddraw();
            return _this;
        }
        NEO_TRACE_LOG("Loading texture from {0}", path.C_STR);
        _this->m_Surface = IMG_Load(path.C_STR);
        return _this;
    }
    void Texture::Delete(Texture* _this) {
        if (!_this) return;
        SDL_FreeSurface(_this->m_Surface);
        delete _this;
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

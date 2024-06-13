#include "Neo_PCH.hpp"
#include "NeoInfused/Sprite/Neo_SpriteSheet.hpp"

#include <cstdint>

namespace neo {
    SpriteSheet* SpriteSheet::New(const std::filesystem::path& path, uint32_t width, uint32_t height) {
        SpriteSheet* _this = new SpriteSheet;

        _this->m_Texture = Texture::New(path);
        _this->m_CellWidth = width;
        _this->m_CellHeight = height;

        return _this;
    }    
    SpriteSheet* SpriteSheet::NewFrom(const Texture* src, uint32_t width, uint32_t height) {
        SpriteSheet* _this = new SpriteSheet;

        _this->m_Texture = Texture::NewFrom(src);
        _this->m_CellWidth = width;
        _this->m_CellHeight = height;

        return _this;
    }
    SpriteSheet* SpriteSheet::NewFrom(const SpriteSheet* src) {
        SpriteSheet* _this = new SpriteSheet;

        _this->m_Texture = Texture::NewFrom(src->m_Texture);
        _this->m_CellWidth = src->m_CellWidth;
        _this->m_CellHeight = src->m_CellHeight;

        return _this;
    }

    SpriteSheet* SpriteSheet::NewMirrored_H(const SpriteSheet* src) {
        SpriteSheet* _this = new SpriteSheet;

        _this->m_Texture = Texture::NewMirrored_H(src->m_Texture);
        _this->m_CellWidth = src->m_CellWidth;
        _this->m_CellHeight = src->m_CellHeight;

        return _this;
    }
    SpriteSheet* SpriteSheet::NewMirrored_V(const SpriteSheet* src) {
        SpriteSheet* _this = new SpriteSheet;

        _this->m_Texture = Texture::NewMirrored_V(src->m_Texture);
        _this->m_CellWidth = src->m_CellWidth;
        _this->m_CellHeight = src->m_CellHeight;

        return _this;
    }
    SpriteSheet* SpriteSheet::NewMirrored_HV(const SpriteSheet* src) {
        SpriteSheet* _this = new SpriteSheet;

        _this->m_Texture = Texture::NewMirrored_HV(src->m_Texture);
        _this->m_CellWidth = src->m_CellWidth;
        _this->m_CellHeight = src->m_CellHeight;

        return _this;
    }

    void SpriteSheet::Delete(SpriteSheet* _this) {
        Texture::Delete(_this->m_Texture);
        delete _this;
    }
    
    SpriteSheet::Cell SpriteSheet::at(uint32_t row, uint32_t col, uint32_t h_amount, uint32_t v_amount) const {
        return { this, {
            (int)(col * m_CellHeight),
            (int)(row * m_CellWidth),
            (int)(h_amount * m_CellHeight),
            (int)(h_amount * m_CellWidth)
        } };
    }
    void SpriteSheet::draw_cell(uint32_t row, uint32_t col, uint32_t h_amount, uint32_t v_amount, SDL_Rect* position, Window* window) const {
        SDL_Rect portion = {
            (int)(col * m_CellHeight),
            (int)(row * m_CellWidth),
            (int)(h_amount * m_CellHeight),
            (int)(v_amount * m_CellWidth)
        };
        m_Texture->draw(position, &portion, window);
    }
}

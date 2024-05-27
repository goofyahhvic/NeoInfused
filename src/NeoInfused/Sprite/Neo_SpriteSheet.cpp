#include "Neo_PCH.hpp"
#include "NeoInfused/Sprite/Neo_SpriteSheet.hpp"

#include <cstdint>

namespace neo {
    SpriteSheet* SpriteSheet::New(const SpriteSheet::CreateInfo& info) {
        NEO_ASSERT(info.texture, "Cannot create SpriteSheet with a null texture!");
        SpriteSheet* _this = new SpriteSheet;
        _this->m_Data = info;
        return _this;
    }    
    void SpriteSheet::Delete(SpriteSheet* _this) {
        Texture::Delete(_this->m_Data.texture);
        delete _this;
    }
    SpriteSheet::Cell SpriteSheet::at(uint32_t row, uint32_t col) const {
        return { this, {
            (int)(col * m_Data.cell_height),
            (int)(row * m_Data.cell_width),
            (int)m_Data.cell_height,
            (int)m_Data.cell_width
        } };
    }
    void SpriteSheet::draw_cell(uint32_t row, uint32_t col, const SpriteSheet::CellDrawInfo& info) const {
        SDL_Rect portion = {
            (int)(col * m_Data.cell_height),
            (int)(row * m_Data.cell_width),
            (int)m_Data.cell_height,
            (int)m_Data.cell_width
        };
        m_Data.texture->draw({ info.dest_rect, &portion, info.angle, info.center, info.flip });
    }
}
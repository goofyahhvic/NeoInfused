#include "Neo_PCH.hpp"
#include "NeoInfused/Sprite/Neo_SpriteSheet.hpp"

namespace neo {
    SpriteSheet::SpriteSheet(uint32_t width, uint32_t height, uint32_t cell_size)
        : Graphic2D(width, height), m_CellSize(cell_size) {
        
    }
    SpriteSheet::SpriteSheet(uint32_t width, uint32_t height, uint32_t cell_size, Color* pixels)
        : Graphic2D(width, height, pixels), m_CellSize(cell_size) {

    }
    SpriteSheet::SpriteSheet(uint32_t cell_size, const std::filesystem::path& image_path) 
        : Graphic2D(image_path), m_CellSize(cell_size) {

    }

    void SpriteSheet::blit_cell(Graphic2D* where, uint32_t row, uint32_t col, uint32_t horizontal_amount, uint32_t vertical_amount, SDL_Rect* position) const {
        SDL_Rect portion = {
            (int)(col * m_CellSize),
            (int)(row * m_CellSize),
            (int)(horizontal_amount * m_CellSize),
            (int)(vertical_amount * m_CellSize)
        };
        SDL_BlitSurface(m_Surface, &portion, where->surface(), position);
    }
    void SpriteSheet::blit_cell_stretch(Graphic2D* where, uint32_t row, uint32_t col, uint32_t horizontal_amount, uint32_t vertical_amount, SDL_Rect* position) const {
        SDL_Rect portion = {
            (int)(col * m_CellSize),
            (int)(row * m_CellSize),
            (int)(horizontal_amount * m_CellSize),
            (int)(vertical_amount * m_CellSize)
        };
        SDL_BlitScaled(m_Surface, &portion, where->surface(), position);
    }
    void SpriteSheet::fill_cell(uint32_t row, uint32_t col, uint32_t horizontal_amount, uint32_t vertical_amount, Color color) {
        SDL_Rect portion = {
            (int)(col * m_CellSize),
            (int)(row * m_CellSize),
            (int)(horizontal_amount * m_CellSize),
            (int)(vertical_amount * m_CellSize)
        };
        SDL_FillRect(m_Surface, &portion, color.rgba);
    }
} // namespace neo

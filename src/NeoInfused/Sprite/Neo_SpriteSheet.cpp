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

    void SpriteSheet::blit_cell(Graphic2D* where, uint32_t row, uint32_t col, const Vec4& position, uint32_t horizontal_amount, uint32_t vertical_amount) const {
        SDL_Rect portion = {
            (int)(col * m_CellSize),
            (int)(row * m_CellSize),
            (int)(horizontal_amount * m_CellSize),
            (int)(vertical_amount * m_CellSize)
        };
        SDL_Rect _position = position;
        SDL_BlitSurface(m_Surface, &portion, where->surface(), &_position);
    }
    void SpriteSheet::blit_cell_stretch(Graphic2D* where, uint32_t row, uint32_t col, const Vec4& position, uint32_t horizontal_amount, uint32_t vertical_amount) const {
        SDL_Rect portion = {
            (int)(col * m_CellSize),
            (int)(row * m_CellSize),
            (int)(horizontal_amount * m_CellSize),
            (int)(vertical_amount * m_CellSize)
        };
        SDL_Rect _position = position;
        SDL_BlitScaled(m_Surface, &portion, where->surface(), &_position);
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

    void SpriteSheet::clone(const SpriteSheet* src) {
        m_Surface = SDL_CreateRGBSurface(
            0, src->m_Surface->w, src->m_Surface->h,
            src->m_Surface->format->BitsPerPixel,
            src->m_Surface->format->Rmask,
            src->m_Surface->format->Gmask,
            src->m_Surface->format->Bmask,
            src->m_Surface->format->Amask
        );
        SDL_BlitSurface(src->m_Surface, nullptr, m_Surface, nullptr);
        m_CellSize = src->m_CellSize;
    }

    void SpriteSheet::CreateMirroredFrom_H(const SpriteSheet* src) {
        m_Surface = MirrorSurface_H(src->m_Surface);
        m_CellSize = src->m_CellSize;
    }
    void SpriteSheet::CreateMirroredFrom_V(const SpriteSheet* src) {
        m_Surface = MirrorSurface_V(src->m_Surface);
        m_CellSize = src->m_CellSize;
    }
    void SpriteSheet::CreateMirroredFrom_HV(const SpriteSheet* src) {
        m_Surface = MirrorSurface_HV(src->m_Surface);
        m_CellSize = src->m_CellSize;
    }

    void SpriteSheetCell::clone(const SpriteSheetCell* src) {
        m_SpriteSheet = src->m_SpriteSheet;
        m_Row = src->m_Row;
        m_Col = src->m_Col;
        m_HorizontalAmount = src->m_HorizontalAmount;
        m_VerticalAmount = src->m_VerticalAmount;
    }
} // namespace neo

#if !defined(NEO_SPRITE_SHEET_HPP)
#define NEO_SPRITE_SHEET_HPP

#include <cstdint>
#include "./Neo_Texture.hpp"

namespace neo {
    class SpriteSheet {
        SpriteSheet(void) = default;
        ~SpriteSheet(void) = default;
    public:
        struct CreateInfo {
            Texture* texture = nullptr;
            uint32_t width = 0, height = 0, cell_width = 0, cell_height = 0;
        };
        using Data = CreateInfo;
        struct Cell {
            const SpriteSheet* const ss = nullptr;
            SDL_Rect portion = { 0, 0, 0, 0 };
        };
        struct CellDrawInfo {
            uint32_t row, col;
            uint32_t horizontal_amount = 1, vertical_amount = 1;
            SDL_FRect* dest_rect = nullptr;
            double angle = 0.0f;
            SDL_FPoint* center = nullptr;
            SDL_RendererFlip flip = SDL_FLIP_NONE;
        };

        static SpriteSheet* New(const CreateInfo& info);
        static void Delete(SpriteSheet* _this);
    public:
        Cell at(uint32_t row, uint32_t col) const;
        inline void draw(const Texture::DrawInfo& info) const { m_Data.texture->draw(info); }
        inline void draw_cell(Cell& cell, const CellDrawInfo& info) const { m_Data.texture->draw({ info.dest_rect, &cell.portion, info.angle, info.center, info.flip }); }
        void draw_cell(const CellDrawInfo& info) const;
    private:
        Data m_Data;
    };
    using SpriteSheetCreateInfo = SpriteSheet::CreateInfo;
    using SpriteSheetCell = SpriteSheet::Cell;
}

#endif // !defined(NEO_SPRITE_SHEET_HPP)
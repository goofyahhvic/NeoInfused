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
        static SpriteSheet* New(const CreateInfo& info);
        static void Delete(SpriteSheet* _this);
    public:
        Cell at(uint32_t row, uint32_t col) const;
        inline void draw(SDL_Rect* position, SDL_Rect* portion = nullptr, Window* window = Window::GetBound()) const { m_Data.texture->draw(position, portion, window); }
        void draw_cell(uint32_t row, uint32_t col, uint32_t h_amount = 1, uint32_t v_amount = 1, SDL_Rect* position = nullptr, Window* window = Window::GetBound()) const;
    private:
        Data m_Data;
    };
    using SpriteSheetCreateInfo = SpriteSheet::CreateInfo;
    using SpriteSheetCell = SpriteSheet::Cell;
}

#endif // !defined(NEO_SPRITE_SHEET_HPP)
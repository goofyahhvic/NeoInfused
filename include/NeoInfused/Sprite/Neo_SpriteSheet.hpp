#if !defined(NEO_SPRITESHEET_HPP)
#define NEO_SPRITESHEET_HPP

#include "NeoInfused/Sprite/Neo_Graphic2D.hpp"

namespace neo {
    class SpriteSheet : public Graphic2D {
    public:
        SpriteSheet(uint32_t width, uint32_t height, uint32_t cell_size);
        SpriteSheet(uint32_t width, uint32_t height, uint32_t cell_size, Color* pixels);
        SpriteSheet(uint32_t cell_size, const std::filesystem::path& image_path);
        ~SpriteSheet(void) = default;
    public:
        void blit_cell(Graphic2D* where, uint32_t row, uint32_t col, uint32_t horizontal_amount = 1, uint32_t vertical_amount = 1, SDL_Rect* position = nullptr) const;
        void blit_cell_stretch(Graphic2D* where, uint32_t row, uint32_t col, uint32_t horizontal_amount = 1, uint32_t vertical_amount = 1, SDL_Rect* position = nullptr) const;
        void fill_cell(uint32_t row, uint32_t col, uint32_t horizontal_amount, uint32_t vertical_amount, Color color = {0, 0, 0, 255});

        inline uint32_t cell_size(void) const { return m_CellSize; }
    private:
        uint32_t m_CellSize;
    };

    class SpriteSheetCell : public Graphic2D {
    public:
        SpriteSheetCell(uint32_t row, uint32_t col, uint32_t horizontal_amount, uint32_t vertical_amount, SpriteSheet* sprite_sheet) : Graphic2D(), m_SpriteSheet(sprite_sheet), m_Row(row), m_Col(col), m_HorizontalAmount(horizontal_amount), m_VerticalAmount(vertical_amount) {}
        ~SpriteSheetCell(void) = default;
    public:
        inline void blit(Graphic2D* where, SDL_Rect* position = nullptr, SDL_Rect* portion = nullptr) const override { m_SpriteSheet->blit_cell(where, m_Row, m_Col, m_HorizontalAmount, m_VerticalAmount, position); }
        inline void blit_stretch(Graphic2D* where, SDL_Rect* position = nullptr, SDL_Rect* portion = nullptr) const override {m_SpriteSheet->blit_cell_stretch(where, m_Row, m_Col, m_HorizontalAmount, m_VerticalAmount, position); }

        inline void fill(Color color = {0, 0, 0, 255}, SDL_Rect* portion = nullptr) override { m_SpriteSheet->fill_cell(m_Row, m_Col, m_HorizontalAmount, m_VerticalAmount, color); }

        inline Color at(uint32_t x, uint32_t y) const override { return GetPixelFromSurface(m_SpriteSheet->surface(), m_Col * m_SpriteSheet->cell_size() + x, m_Row * m_SpriteSheet->cell_size() + y); }
        inline void set_at(uint32_t x, uint32_t y, Color color) override { SetPixelFromSurface(m_SpriteSheet->surface(), m_Col * m_SpriteSheet->cell_size() + x, m_Row * m_SpriteSheet->cell_size() + y, color); }

        inline void set_row(uint32_t new_row) { m_Row = new_row; }
        inline void set_col(uint32_t new_col) { m_Col = new_col; }

        inline void set_horizontal_amount(uint32_t new_horizontal_amount) { m_HorizontalAmount = new_horizontal_amount; }
        inline void set_vertical_amount(uint32_t new_vertical_amount) { m_VerticalAmount = new_vertical_amount; }

        inline void set(uint32_t new_row, uint32_t new_col, uint32_t new_horizontal_amount = 1, uint32_t new_vertical_amount = 1) { m_Row = new_row; m_Col = new_col; m_HorizontalAmount = new_horizontal_amount; m_VerticalAmount = new_vertical_amount; }

        inline uint32_t row(void) const { return m_Row; }
        inline uint32_t col(void) const { return m_Col; }
        inline uint32_t horizontal_amount(void) const { return m_HorizontalAmount; }
        inline uint32_t vertical_amount(void) const { return m_VerticalAmount; }

        inline uint32_t width(void) const override { return m_SpriteSheet->cell_size(); }
        inline uint32_t height(void) const override { return m_SpriteSheet->cell_size(); }

        inline SpriteSheet* sprite_sheet(void) { return m_SpriteSheet; }
    private:
        SpriteSheet* m_SpriteSheet;
        uint32_t m_Row, m_Col, m_HorizontalAmount, m_VerticalAmount;
    };
    using SS_Cell = SpriteSheetCell;
} // namespace neo

#endif // NEO_SPRITESHEET_HPP
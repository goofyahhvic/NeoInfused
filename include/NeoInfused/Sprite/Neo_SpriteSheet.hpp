#if !defined(NEO_SPRITE_SHEET_HPP)
#define NEO_SPRITE_SHEET_HPP

#include <cstdint>
#include "./Neo_Texture.hpp"

namespace neo {
    class SpriteSheet {
        SpriteSheet(void) = default;
        ~SpriteSheet(void) = default;
    public:
        struct Cell {
            const SpriteSheet* const ss = nullptr;
            SDL_Rect portion = { 0, 0, 0, 0 };
        };
        static SpriteSheet* New(const std::filesystem::path& path, uint32_t cell_width, uint32_t cell_height);
        static SpriteSheet* NewFrom(const SpriteSheet* src);
        static SpriteSheet* NewFrom(const Texture* src, uint32_t cell_width, uint32_t cell_height);

        static SpriteSheet* NewMirrored_H(const SpriteSheet* src);
        static SpriteSheet* NewMirrored_V(const SpriteSheet* src);
        static SpriteSheet* NewMirrored_HV(const SpriteSheet* src);

        static void Delete(SpriteSheet* _this);
    public:
        inline void mirror_h(void) { m_Texture->mirror_h(); }
        inline void mirror_v(void) { m_Texture->mirror_v(); }
        inline void mirror_hv(void) { m_Texture->mirror_hv(); }

        Cell at(uint32_t row, uint32_t col, uint32_t h_amount = 1, uint32_t v_amount = 1) const;
        inline void draw(SDL_Rect* position = nullptr, SDL_Rect* portion = nullptr, Window* window = Window::GetBound()) const { m_Texture->draw(position, portion, window); }
        void draw_cell(uint32_t row, uint32_t col, uint32_t h_amount = 1, uint32_t v_amount = 1, SDL_Rect* position = nullptr, Window* window = Window::GetBound()) const;

        inline Texture* texture(void) const { return m_Texture; }
        inline uint32_t cell_width(void) const { return m_CellWidth; }
        inline uint32_t cell_height(void) const { return m_CellHeight; }
    private:
        Texture* m_Texture;
        uint32_t m_CellWidth, m_CellHeight;
    };
    using SpriteSheetCell = SpriteSheet::Cell;
    using SS_Cell = SpriteSheet::Cell;
}

#endif // !defined(NEO_SPRITE_SHEET_HPP)
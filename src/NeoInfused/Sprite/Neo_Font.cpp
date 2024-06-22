#include "Neo_PCH.hpp"
#include "NeoInfused/Sprite/Neo_Font.hpp"

namespace neo {
    void Font::set_font(const std::filesystem::path& ttf_path, int32_t size) {
        m_Font = TTF_OpenFont(ttf_path.C_STR, size);
    }
    void Font::destroy(void) {
        TTF_CloseFont(m_Font);
        m_Font = nullptr;
    }

    void Font::draw_text(Graphic2D* where, const Vec2& pos, const char* text, Color color) const {
        SDL_Surface* surface = TTF_RenderUTF8_Blended(m_Font, text, {
            color.r, color.g, color.b, color.a
        });
        SDL_Rect _pos = { round(pos.x), round(pos.y), surface->w, surface->h };
        SDL_BlitSurface(surface, nullptr, where->surface(), &_pos);
        SDL_FreeSurface(surface);
    }
    void Font::draw_text_scaled(Graphic2D* where, const Vec3& pos, const char* text, Color color) const {
        SDL_Surface* surface = TTF_RenderUTF8_Blended(m_Font, text, {
            color.r, color.g, color.b, color.a
        });
        SDL_Rect _pos = {
            round(pos.x), round(pos.y),
            round(surface->w * pos.z), round(surface->h * pos.z)
        };
        SDL_BlitScaled(surface, nullptr, where->surface(), &_pos);
        SDL_FreeSurface(surface);
    }
    void Font::draw_text_scaled_wh(Graphic2D* where, const Vec4& pos, const char* text, Color color) const {
        SDL_Surface* surface = TTF_RenderUTF8_Blended(m_Font, text, {
            color.r, color.g, color.b, color.a
        });
        SDL_Rect _pos = pos;
        SDL_BlitScaled(surface, nullptr, where->surface(), &_pos);
        SDL_FreeSurface(surface);
    }
} // namespace neo

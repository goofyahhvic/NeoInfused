#include "Neo_PCH.hpp"
#include "NeoInfused/Sprite/Neo_Text.hpp"

namespace neo {
    Text::Text(const Font* font, const char* text, Color color)
    : m_Text(text), m_Font(font), m_Color(color) {
        m_Surface = TTF_RenderUTF8_Blended(font->m_Font, text, color);
    }
    void Text::set_surface(const Font* font, const char* new_text, Color color) {
        m_Font = font;
        m_Text = new_text;
        m_Color = color;
        m_Surface = TTF_RenderUTF8_Blended(font->m_Font, new_text, color);
    }
    void Text::update_changes(void) {
        m_Surface = TTF_RenderUTF8_Blended(m_Font->m_Font, m_Text.c_str(), m_Color);
    }
} // namespace neo

#if !defined(NEO_TEXT_HPP)
#define NEO_TEXT_HPP

#include "./Neo_Font.hpp"

namespace neo {
    class Text : public Graphic2D {
    public:
        Text(const Font* font, const char* text, Color color = NEO_COLOR_WHITE);
        void set_surface(const Font* new_font, const char* new_text, Color color = NEO_COLOR_WHITE);
        
        inline const std::string& str(void) const { return m_Text; }
        inline const Font* font(void) const { return m_Font; }
        inline Color color(void) const { return m_Color; }

        inline char operator[](size_t index) const { return m_Text[index]; }
        inline char at(size_t index) const { return m_Text[index]; }

        inline void set_at(char _char, size_t index) { m_Text[index] = _char; }
        void update_changes(void);
    private:
        std::string m_Text;
        const Font* m_Font;
        Color m_Color;
    }; 
} // namespace neo

#endif // NEO_TEXT_HPP
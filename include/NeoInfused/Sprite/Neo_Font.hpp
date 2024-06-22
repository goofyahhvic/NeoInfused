#if !defined(NEO_FONT_HPP)
#define NEO_FONT_HPP

#include "./Neo_Graphic2D.hpp"

namespace neo {
    class Font {
        friend class Text;
    public:
        inline Font(const std::filesystem::path& ttf_path, int32_t size) { this->set_font(ttf_path, size); }
        inline ~Font(void) { this->destroy(); }

        void set_font(const std::filesystem::path& ttf_path, int32_t size);
        void destroy(void);
    public:
        void draw_text(Graphic2D* where, const Vec2& pos, const char* text, Color color = { 255, 255, 255, 255 }) const;
        void draw_text_scaled(Graphic2D* where, const Vec3& pos, const char* text, Color color = { 255, 255, 255, 255 }) const;
        void draw_text_scaled_wh(Graphic2D* where, const Vec4& pos, const char* text, Color color = { 255, 255, 255, 255 }) const;
    private:
        TTF_Font* m_Font;
    };
} // namespace neo

#endif // NEO_FONT_HPP
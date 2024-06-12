#if !defined(NEO_TEXTURE_HPP)
#define NEO_TEXTURE_HPP

#include "NeoInfused/Core/Neo_Core.hpp"
#include "NeoInfused/Neo_Window.hpp"

namespace neo {
    class Texture {
        Texture(void) = default;
        ~Texture(void) = default;
    public:
        static Texture* New(const std::filesystem::path& path);
        static void Delete(Texture* _this);
    public:
        void set(const std::filesystem::path& path);
        inline void draw(SDL_Rect* position = nullptr, SDL_Rect* portion = nullptr, Window* window = Window::GetBound()) const { window->display()->blit(m_Surface, position, portion); }
        inline operator bool() const { return (bool)m_Surface; }
    private:
        SDL_Surface* m_Surface;
    };
} // namespace neo

#endif // NEO_TEXTURE_HPP
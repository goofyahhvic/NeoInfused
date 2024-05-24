#if !defined(NEO_TEXTURE_HPP)
#define NEO_TEXTURE_HPP

#include "NeoInfused/Core/Neo_Core.hpp"
#include "NeoInfused/Neo_Renderer.hpp"

namespace neo {
    class Texture {
    public:
        struct DrawInfo {
            SDL_FRect* dest_rect = nullptr;
            SDL_Rect* src_rect = nullptr;
            double angle = 0.0f;
            SDL_FPoint* center = nullptr;
            SDL_RendererFlip flip = SDL_FLIP_NONE;
        };
        enum class State { None = -1, Null = 0, Created = 1, Failed = 2 };
    public:
        Texture(void) : m_Texture(nullptr), m_State(State::Null) {}
        Texture(const std::filesystem::path& path);

        Texture(const Texture& texture);
        void operator=(const Texture& texture);

        void destroy(void);
        ~Texture(void) { (*m_RefCount)--; if (!(*m_RefCount)) this->destroy(); }
    public:
        void set(const std::filesystem::path& path);
        inline void draw(const DrawInfo& info, Renderer* renderer = Renderer::GetBound()) const { renderer->blit(m_Texture, info.dest_rect, info.src_rect, info.angle, info.center, info.flip); }
        inline State state(void) const { return m_State; }
        inline operator bool() const { return (m_State == State::Created); }
    private:
        SDL_Texture* m_Texture;
        State m_State;
        uint32_t* m_RefCount;
    };
} // namespace neo

#endif // NEO_TEXTURE_HPP
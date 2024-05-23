#if !defined(NEO_SPRITE_HANDLE_HPP)
#define NEO_SPRITE_HANDLE_HPP

#include "NeoInfused/Core/Neo_Core.hpp"
#include "NeoInfused/Neo_Renderer.hpp"
#include "./Neo_TextureRegistry.hpp"

namespace neo {
    class TextureHandle {
    public:
        struct DrawInfo {
            SDL_FRect* dest_rect = nullptr;
            SDL_Rect* src_rect = nullptr;
            double angle = 0.0f;
            SDL_FPoint* center = nullptr;
            SDL_RendererFlip flip = SDL_FLIP_NONE;
        };
        enum class State { None = -1, Null = 0, Created = 1 };
    public:
        TextureHandle(void) { m_State = State::None; };
        ~TextureHandle(void) = default;
    private:
        TextureHandle(id32_t id, State state = State::None) : m_Id(id), m_State(state) {};
    public:
        // creates a null texture if path is invalid
        static inline TextureHandle CreateTexture(const std::filesystem::path& path) { TextureHandle texture = TextureHandle(TextureRegistry::CreateTexture(path), State::Created); if (!TextureRegistry::GetTexture(texture.m_Id)) texture.m_State = State::Null; return texture; }
        // creates a blank texture if path is invalid
        static inline TextureHandle CreateTextureB(const std::filesystem::path& path) { return TextureHandle(TextureRegistry::CreateTextureB(path), State::Created); }
        // creates a null texture
        static inline TextureHandle CreateTexture(void) { return TextureHandle(TextureRegistry::CreateTexture(), State::Null); }

        inline void destroy(void) { TextureRegistry::DestroyTexture(m_Id); m_State = State::Null; }

        // won't do anything if path is invalid
        // should be called from a texture that already exists
        inline void set_texture(const std::filesystem::path& path) { TextureRegistry::SetTexture(m_Id, path); }
        // sets to a blank texture if path is invalid
        // should be called from a texture that already exists
        inline void set_texture_b(const std::filesystem::path& path) { TextureRegistry::SetTextureB(m_Id, path); m_State = State::Created; }

        // won't destroy the original texture before setting the value, and won't do anything if path is invalid.
        // useful for reusing memory, since destroyed textures stay in the texture registry so indecies don't move.
        inline void set_destroyed_texture(const std::filesystem::path& path) { if (TextureRegistry::SetNullTexture(m_Id, path) != UINT32_MAX) m_State = State::Created; }
        // won't destroy the original texture before setting the value, and will set to a blank texture if path is invalid.
        // useful for reusing memory, since destroyed textures stay in the texture registry so indecies don't move.
        inline void set_destroyed_texture_b(const std::filesystem::path& path) { TextureRegistry::SetNullTextureB(m_Id, path); m_State = State::Created; }

        inline void draw(const DrawInfo& info, Renderer* renderer = Renderer::GetBound()) const { renderer->blit({ TextureRegistry::GetTexture(m_Id), info.dest_rect, info.src_rect, info.angle, info.center, info.flip }); }

        inline id32_t get_id(void) const { return m_Id; }
        inline State get_state(void) const { return m_State; }

        inline operator bool() const { return (m_State == State::Created); }
    private:
        id32_t m_Id;
        State m_State;
    };
    using TextureDrawInfo = TextureHandle::DrawInfo;
    using TextureState = TextureHandle::State;
} // namespace neo

#endif // NEO_SPRITE_HANDLE_HPP
#if !defined(NEO_SPRITE_HANDLE_HPP)
#define NEO_SPRITE_HANDLE_HPP

#include "NeoInfused/Core/Neo_Core.hpp"
#include "./Neo_TextureRegistry.hpp"

namespace neo {
    class TextureHandle {
        TextureHandle(id_t id) : id(id) {};
    public:
        TextureHandle() = default;
        ~TextureHandle() = default;
    public:
        // creates a null texture if path is invalid
        static inline TextureHandle CreateTexture(const std::filesystem::path& path) { return TextureHandle(TextureRegistry::CreateTexture(path)); }
        // creates a blank texture if path is invalid
        static inline TextureHandle CreateTextureB(const std::filesystem::path& path) { return TextureHandle(TextureRegistry::CreateTextureB(path)); }
        // creates a null texture
        static inline TextureHandle CreateTexture(void) { return TextureHandle(TextureRegistry::CreateTexture()); }

        static inline void DestroyTexture(TextureHandle* s) { TextureRegistry::DestroyTexture(s->id); }
        inline void destroy(void) { TextureRegistry::DestroyTexture(TextureHandle::id); }

        // won't do anything if path is invalid
        inline void set_texture(const std::filesystem::path& path) { return TextureRegistry::SetTexture(TextureHandle::id, path); }
        // sets to a blank texture if path is invalid
        inline void set_texture_b(const std::filesystem::path& path) { return TextureRegistry::SetTextureB(TextureHandle::id, path); }
        // sets to a null texture if path is invalid
        inline void set_texture_n(const std::filesystem::path& path) { return TextureRegistry::SetTextureN(TextureHandle::id, path); }

        // won't destroy the original texture before setting the value, and won't do anything if path is invalid.
        // useful for reusing memory, since destroyed textures stay in the texture registry so indecies don't move.
        inline void set_null_texture(const std::filesystem::path& path) { return TextureRegistry::SetNullTexture(TextureHandle::id, path); }
        // won't destroy the original texture before setting the value, and will set to a blank texture if path is invalid.
        // useful for reusing memory, since destroyed textures stay in the texture registry so indecies don't move.
        inline void set_null_texture_b(const std::filesystem::path& path) { return TextureRegistry::SetNullTextureB(TextureHandle::id, path); }
        // won't destroy the original texture before setting the value, and will set to a null texture if path is invalid.
        // useful for reusing memory, since destroyed textures stay in the texture registry so indecies don't move.
        inline void set_null_texture_n(const std::filesystem::path& path) { return TextureRegistry::SetNullTextureN(TextureHandle::id, path); }

        void draw(float dest_x, float dest_y, float dest_w, float dest_h, int32_t src_x, int32_t src_y, int32_t src_w, int32_t src_h) const;
        void draw(float dest_x, float dest_y, float dest_w, float dest_h) const;
        void draw(const SDL_FRect* dest_rect, const SDL_Rect* src_rect = nullptr) const;

        inline id_t get_id(void) const { return TextureHandle::id; }
        inline const SDL_Texture* get_texture(void) const { return TextureRegistry::GetTexture(TextureHandle::id); }
    private:
        id_t id;
    };
} // namespace neo

#endif // NEO_SPRITE_HANDLE_HPP
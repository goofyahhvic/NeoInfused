#if !defined(NEO_TEXTURE_REGISTRY_HPP)
#define NEO_TEXTURE_REGISTRY_HPP

#include "NeoInfused/Core/Neo_Core.hpp"

namespace neo {
    class TextureRegistry {
        TextureRegistry() = default;
        ~TextureRegistry() = default;
    public:
        // by default allocates 8kb of ram
        static void Alloc(uint32_t arena_size = 1000);
        static void ReAlloc(uint32_t new_arena_size);
        static void DestroyAll(void);
        // destroys all textures, then frees the memory
        static void Free(void);
    public:
        // creates a null texture if path is invalid.
        static index32_t CreateTexture(const std::filesystem::path& path);
        // creates a null texture
        static index32_t CreateTexture(void);
        // creates a blank texture if path is invalid.
        static index32_t CreateTextureB(const std::filesystem::path& path);

        static index32_t DestroyTexture(const index32_t id);

        // won't do anything if path is invalid.
        static index32_t SetTexture(const index32_t id, const std::filesystem::path& path);
        // creates a blank texture if path is invalid.
        static index32_t SetTextureB(const index32_t id, const std::filesystem::path& path);

        // won't destroy the original texture at the sent index, and won't do anything if path is invalid.
        // useful for reusing memory, since destroyed SDL_Textures stay in the registry so indecies don't move.
        static index32_t SetNullTexture(const index32_t id, const std::filesystem::path& path);
        // won't destroy the original texture at the sent index, and creates a blank texture if path is invalid.
        // useful for reusing memory, since destroyed SDL_Textures stay in the registry so indecies don't move.
        static index32_t SetNullTextureB(const index32_t id, const std::filesystem::path& path);
        static inline SDL_Texture* GetTexture(const index32_t id) { return m_Arena[id]; }

        static index32_t FindFirstOf(SDL_Texture* texture);
        static index32_t FindLastOf(SDL_Texture* texture);

        static inline uint32_t Size(void) { return m_ArenaSize; }
        static inline uint32_t GetInsertIndex(void) { return m_ArenaInsertIndex; }
    private:
        static index32_t _PushTexture(SDL_Texture* texture);
        // doesnt check if path is invalid
        static SDL_Texture* _LoadTexture(const std::filesystem::path& path);
        // returns nullptr if path is invalid
        static SDL_Texture* _LoadTextureN(const std::filesystem::path& path);
        // returns a blank texture if path is invalid
        static SDL_Texture* _LoadTextureB(const std::filesystem::path& path);
    private:
        static SDL_Texture** m_Arena;
        static uint32_t m_ArenaSize, m_ArenaInsertIndex;
    };
} // namespace neo

#endif // NEO_TEXTURE_REGISTRY_HPP
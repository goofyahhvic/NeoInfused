#if !defined(NEO_TEXTURE_REGISTRY_HPP)
#define NEO_TEXTURE_REGISTRY_HPP

#include "NeoInfused/Core/Neo_Core.hpp"

namespace neo {
    class TextureRegistry {
        TextureRegistry() = default;
        ~TextureRegistry() = default;
    public:
        static void Init(void);
        static void Reset(void);
    public:
        // creates a null texture if path is invalid.
        static id_t CreateTexture(const std::filesystem::path& path);
        // creates a null texture
        static id_t CreateTexture(void);
        // creates a blank texture if path is invalid.
        static id_t CreateTextureB(const std::filesystem::path& path);

        static void DestroyTexture(const id_t id);

        // won't do anything if path is invalid.
        static void SetTexture(const id_t id, const std::filesystem::path& path);
        // creates a blank texture if path is invalid.
        static void SetTextureB(const id_t id, const std::filesystem::path& path);
        // creates a null texture if path is invalid.
        static void SetTextureN(const id_t id, const std::filesystem::path& path);

        // won't destroy the original texture at the sent index, and won't do anything if path is invalid.
        // useful for reusing memory, since destroyed SDL_Textures stay in the registry so indecies don't move.
        static void SetNullTexture(const id_t id, const std::filesystem::path& path);
        // won't destroy the original texture at the sent index, and creates a blank texture if path is invalid.
        // useful for reusing memory, since destroyed SDL_Textures stay in the registry so indecies don't move.
        static void SetNullTextureB(const id_t id, const std::filesystem::path& path);
        // won't destroy the original texture at the sent index, and creates a null texture if path is invalid.
        // useful for reusing memory, since destroyed SDL_Textures stay in the registry so indecies don't move.
        static void SetNullTextureN(const id_t id, const std::filesystem::path& path);
        static inline SDL_Texture* GetTexture(const id_t id) { return TextureRegistry::s_Registry[id]; }

        static id_t FindFirstOf(SDL_Texture* texture);
        static id_t FindLastOf(SDL_Texture* texture);

        static inline index_t Size(void) { return TextureRegistry::s_Registry.size(); }

        static inline std::vector<SDL_Texture*> GetRegistry(void) { return TextureRegistry::s_Registry; }
        static inline const std::vector<SDL_Texture*>& GetRegistryR(void) { return TextureRegistry::s_Registry; }
    private:
        static id_t PushTexture(SDL_Texture* texture);
        // doesnt check if path is invalid
        static SDL_Texture* LoadTexture(const std::filesystem::path& path);
        // returns nullptr if path is invalid
        static SDL_Texture* LoadTextureN(const std::filesystem::path& path);
        // returns a blank texture if path is invalid
        static SDL_Texture* LoadTextureB(const std::filesystem::path& path);
    private:
        static std::vector<SDL_Texture*> s_Registry;
    };
} // namespace neo

#endif // NEO_TEXTURE_REGISTRY_HPP
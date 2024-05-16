#if !defined(NEO_SPRITE_REGISTRY_HPP)
#define NEO_SPRITE_REGISTRY_HPP

#include <cstdint>

namespace neo {
    class SpriteRegistry {
        SpriteRegistry() = default;
        ~SpriteRegistry() = default;
    public:
        static void Init(void);
        static void Terminate(void);
    public:
        static uint64_t CreateSprite(const std::filesystem::path& path);
        static void DestroySprite(uint64_t index);

        static inline SDL_Texture* GetSprite(uint64_t index) { return SpriteRegistry::s_Registry[index]; }
        static inline const std::vector<SDL_Texture*>& GetMainRegistry() { return SpriteRegistry::s_Registry; }
        static inline const std::vector<uint64_t>& GetDestroyedSprites() { return SpriteRegistry::s_DestroyedSprites; }
    private:
        static std::vector<SDL_Texture*> s_Registry;
        static std::vector<uint64_t> s_DestroyedSprites;
    };
} // namespace neo

#endif // NEO_SPRITE_REGISTRY_HPP
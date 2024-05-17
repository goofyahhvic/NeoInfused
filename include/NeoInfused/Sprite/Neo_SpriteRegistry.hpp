#if !defined(NEO_SPRITE_REGISTRY_HPP)
#define NEO_SPRITE_REGISTRY_HPP

#include "NeoInfused/Core/Neo_Core.hpp"

namespace neo {
    class SpriteRegistry {
        SpriteRegistry() = default;
        ~SpriteRegistry() = default;
    public:
        static void Init(void);
        static void Reset(void);
    public:
        static id_t CreateSprite(const std::filesystem::path& path);
        static void DestroySprite(id_t id);

        static inline SDL_Texture* GetSprite(id_t id) { return SpriteRegistry::s_Registry[id]; }
        static inline const std::vector<SDL_Texture*>& GetMainRegistry() { return SpriteRegistry::s_Registry; }
    private:
        static std::vector<SDL_Texture*> s_Registry;
    };
} // namespace neo

#endif // NEO_SPRITE_REGISTRY_HPP
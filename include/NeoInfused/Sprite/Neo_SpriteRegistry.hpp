#if !defined(NEO_SPRITE_REGISTRY_HPP)
#define NEO_SPRITE_REGISTRY_HPP

#include <cstdint>
#include "./Neo_SpriteData.hpp"

namespace neo {
    class SpriteRegistry {
        SpriteRegistry() = default;
        ~SpriteRegistry() = default;
    public:
        static void Init(void);
        static void Terminate(void);
    public:
        static uint64_t PushSpriteData(SpriteData* s);
        static void DestroySpriteData(uint64_t index);

        static inline SpriteData* GetSpriteData(uint64_t index) { return registry[index]; }
    private:
        static std::vector<SpriteData*> registry;
        static std::vector<uint64_t> destroyed_sprites;
    };
} // namespace neo

#endif // NEO_SPRITE_REGISTRY_HPP
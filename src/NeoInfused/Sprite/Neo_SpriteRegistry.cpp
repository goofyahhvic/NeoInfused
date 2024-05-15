#include "Neo_PCH.hpp"
#include "NeoInfused/Sprite/Neo_SpriteRegistry.hpp"

namespace neo {
    std::vector<SpriteData*> SpriteRegistry::registry;
    std::vector<uint64_t> SpriteRegistry::destroyed_sprites;

    void SpriteRegistry::Init(void) {
        registry.clear();
        destroyed_sprites.clear();
    }
    void SpriteRegistry::Terminate(void) {
        Init();
    }

    uint64_t SpriteRegistry::PushSpriteData(SpriteData* s) {
        uint64_t index = 0;
        if (destroyed_sprites.empty()) {
            index = registry.size();
            registry.push_back(s);
            return index;
        }
        index = destroyed_sprites[destroyed_sprites.size()-1];
        registry[index] = s;
        destroyed_sprites.pop_back();
        return index;
    }
    void SpriteRegistry::DestroySpriteData(uint64_t index) {
        neo::DestroySpriteData(registry[index]);
        registry[index] = nullptr;
        destroyed_sprites.push_back(index);
    }
} // namespace neo

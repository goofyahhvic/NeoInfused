#if !defined(NEO_SPRITE_HANDLER_HPP)
#define NEO_SPRITE_HANDLER_HPP

#include "NeoInfused/Core/Neo_Core.hpp"
#include "./Neo_SpriteHandle.hpp"

namespace neo {
    class SpriteHandler {
        SpriteHandler() = default;
        ~SpriteHandler() = default;
    public:
        static inline SpriteHandle CreateSprite(const std::filesystem::path& path) { return SpriteHandle(SpriteRegistry::CreateSprite(path)); }
        static inline void DestroySprite(SpriteHandle s) { SpriteRegistry::DestroySprite(s.id); }
    };
} // namespace neo

#endif // NEO_SPRITE_HANDLER_HPP
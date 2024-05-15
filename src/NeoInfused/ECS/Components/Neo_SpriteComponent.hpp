#if !defined(NEO_SPRITE_COMPONENT_HPP)
#define NEO_SPRITE_COMPONENT_HPP

#include "./Neo_Entity.hpp"
#include "Engine/Neo_Sprite.hpp"

namespace neo {
    struct SpriteComponent {
        Sprite* s;
    };
    struct SpriteComponentCell {
        Entity e;
        SpriteComponent component;
    };
} // namespace neo

#endif // NEO_SPRITE_COMPONENT_HPP
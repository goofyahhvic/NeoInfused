#if !defined(NEO_SPRITE_HPP)
#define NEO_SPRITE_HPP

#include "./Neo_TextureHandle.hpp"

namespace neo {
    struct Sprite {
        TextureHandle texture;
        SDL_Rect src_rect;
    };
} // namespace neo

#endif // NEO_SPRITE_HPP
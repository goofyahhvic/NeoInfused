#if !defined(NEO_BASIC_COMPONENTS_HPP)
#define NEO_BASIC_COMPONENTS_HPP

#include "NeoInfused/Core/Neo_Core.hpp"
#include <SDL2/SDL.h>

namespace neo {
    struct Vec2 {
        float x, y;
    };
    struct Vec3 {
        float x, y, z;
    };
    struct Vec4 {
        float x, y, w, h;
        inline operator SDL_FRect(void) const { return {x, y, w, h}; }
        inline operator SDL_Rect(void) const { return { round(x), round(y), round(w), round(h) }; }
    };
} // namespace neo

#endif // NEO_BASIC_COMPONENTS_HPP
#if !defined(NEO_SPRITE_HANDLE_HPP)
#define NEO_SPRITE_HANDLE_HPP

#include "NeoInfused/Core/Neo_Core.hpp"
#include "./Neo_SpriteRegistry.hpp"

namespace neo {
    class SpriteHandle {
        SpriteHandle(id_t id) : id(id) {};
        friend class SpriteHandler;
    public:
        SpriteHandle() = default;
        ~SpriteHandle() = default;
    public:
        inline void destroy(void) { SpriteRegistry::DestroySprite(SpriteHandle::id); }

        void draw(float x, float y, float w, float h);
        void draw(SDL_FRect*  rect);
        void draw(SDL_FRect&  rect);
        void draw(SDL_FRect&& rect);
    private:
        id_t id;
    };
    using Sprite = SpriteHandle;
} // namespace neo

#endif // NEO_SPRITE_HANDLE_HPP
#include "Neo_PCH.hpp"
#include "NeoInfused/Sprite/Neo_SpriteHandle.hpp"

#include "NeoInfused/Neo_App.hpp"

namespace neo {
    void SpriteHandle::draw(float x, float y, float w, float h) {
        SDL_FRect rect = { x, y, w, h };
        SDL_RenderCopyF(App::Get()->get_renderer(), SpriteRegistry::GetSprite(SpriteHandle::id), NULL, &rect);
    }
    void SpriteHandle::draw(SDL_FRect* rect) {
        SDL_RenderCopyF(App::Get()->get_renderer(), SpriteRegistry::GetSprite(SpriteHandle::id), NULL, rect);
    }
    void SpriteHandle::draw(SDL_FRect& rect) {
        SDL_RenderCopyF(App::Get()->get_renderer(), SpriteRegistry::GetSprite(SpriteHandle::id), NULL, &rect);
    }
    void SpriteHandle::draw(SDL_FRect&& rect) {
        SDL_RenderCopyF(App::Get()->get_renderer(), SpriteRegistry::GetSprite(SpriteHandle::id), NULL, &rect);
    }
} // namespace neo

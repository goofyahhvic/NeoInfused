#include "Neo_PCH.hpp"
#include "./Neo_SpriteData.hpp"

#include "Engine/Neo_App.hpp"

namespace neo {
    SpriteData* CreateSpriteData(float x, float y, float w, float h, const std::filesystem::path& path) {
        SpriteData* s = (SpriteData*) malloc(sizeof(SpriteData));

        s->rect.x = x;
        s->rect.y = y;
        s->rect.w = w;
        s->rect.h = h;

        if (!std::filesystem::exists(path)) {
            NEO_ERROR_LOG("File does not exist!: {0}", path.c_str());

            SDL_Color color = { 0x00, 0xff, 0xff, 0x00 };
            SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(&color, 1, 1, 8, 0, 0, 0, 0, 0);
            s->texture = SDL_CreateTextureFromSurface(NEO_APP_RENDERER, surface);
            SDL_FreeSurface(surface);

            return s;
        }
        NEO_TRACE_LOG("Loading {0}", path.c_str());
        s->texture = IMG_LoadTexture(NEO_APP_RENDERER, path.c_str());

        return s;
    }
    void DestroySpriteData(SpriteData* s) {
        SDL_DestroyTexture(s->texture);
        free(s);
    }

    void DrawSpriteData(SpriteData* s) {
        SDL_RenderCopyF(NEO_APP_RENDERER, s->texture, NULL, &s->rect);
    }
} // namespace neo

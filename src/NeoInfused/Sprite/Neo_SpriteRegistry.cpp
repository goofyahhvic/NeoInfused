#include "Neo_PCH.hpp"
#include "NeoInfused/Sprite/Neo_SpriteRegistry.hpp"

#include "NeoInfused/Neo_App.hpp"

namespace neo {
    std::vector<SDL_Texture*> SpriteRegistry::s_Registry;

    void SpriteRegistry::Init(void) {
        SpriteRegistry::s_Registry.clear();
    }
    void SpriteRegistry::Reset(void) {
        for (index_t i = 0; i < s_Registry.size(); i++) {
            if (s_Registry[i]) {
                SpriteRegistry::DestroySprite(i);
            }
        }
        SpriteRegistry::s_Registry.clear();
    }

    uint64_t SpriteRegistry::CreateSprite(const std::filesystem::path& path) {
        SDL_Texture* sprite = nullptr;
        if (std::filesystem::exists(path)) {
            NEO_TRACE_LOG("Loading {0}", path.c_str());
            sprite = IMG_LoadTexture(App::Get()->get_renderer(), path.c_str());
        } else {
            NEO_ERROR_LOG("File does not exist!: {0}", path.c_str());

            SDL_Color color = { 0x00, 0xff, 0xff, 0x00 };
            SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(&color, 1, 1, 8, 0, 0, 0, 0, 0);
            sprite = SDL_CreateTextureFromSurface(App::Get()->get_renderer(), surface);
            SDL_FreeSurface(surface);
        }
        index_t index = 0;
        index = SpriteRegistry::s_Registry.size();
        SpriteRegistry::s_Registry.push_back(sprite);
        return index;
    }
    void SpriteRegistry::DestroySprite(id_t id) {
        SDL_DestroyTexture(SpriteRegistry::s_Registry[id]);
        SpriteRegistry::s_Registry[id] = nullptr;
    }
} // namespace neo

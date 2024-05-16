#include "Neo_PCH.hpp"
#include "NeoInfused/Sprite/Neo_SpriteRegistry.hpp"

#include "NeoInfused/Neo_App.hpp"

namespace neo {
    std::vector<SDL_Texture*> SpriteRegistry::s_Registry;
    std::vector<uint64_t> SpriteRegistry::s_DestroyedSprites;

    void SpriteRegistry::Init(void) {
        SpriteRegistry::s_Registry.clear();
        SpriteRegistry::s_DestroyedSprites.clear();
    }
    void SpriteRegistry::Terminate(void) {
        Init();
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

        uint64_t index = 0;
        if (SpriteRegistry::s_DestroyedSprites.empty()) {
            index = SpriteRegistry::s_Registry.size();
            SpriteRegistry::s_Registry.push_back(sprite);
            return index;
        }
        index = SpriteRegistry::s_DestroyedSprites[SpriteRegistry::s_DestroyedSprites.size()-1];
        SpriteRegistry::s_Registry[index] = sprite;
        SpriteRegistry::s_DestroyedSprites.pop_back();
        return index;
    }
    void SpriteRegistry::DestroySprite(uint64_t index) {
        SDL_DestroyTexture(SpriteRegistry::s_Registry[index]);
        SpriteRegistry::s_Registry[index] = nullptr;
        SpriteRegistry::s_DestroyedSprites.push_back(index);
    }
} // namespace neo

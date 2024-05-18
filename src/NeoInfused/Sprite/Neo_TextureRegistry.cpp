#include "Neo_PCH.hpp"
#include "NeoInfused/Sprite/Neo_TextureRegistry.hpp"

#include "NeoInfused/Neo_App.hpp"

namespace neo {
    std::vector<SDL_Texture*> TextureRegistry::s_Registry;

    void TextureRegistry::Init(void) {
        TextureRegistry::s_Registry.clear();
    }
    void TextureRegistry::Reset(void) {
        for (index_t i = 0; i < s_Registry.size(); i++) {
            if (s_Registry[i]) {
                SDL_DestroyTexture(TextureRegistry::s_Registry[i]);
                TextureRegistry::s_Registry[i] = nullptr;
            }
        }
        TextureRegistry::s_Registry.clear();
    }

    SDL_Texture* TextureRegistry::LoadTexture(const std::filesystem::path& path) {
#if defined(NEO_PLATFORM_LINUX)
        NEO_TRACE_LOG("Loading {0}", path.string().c_str());
        return IMG_LoadTexture(App::Get()->get_renderer(), path.c_str());
#elif defined(NEO_PLATFORM_WINDOWS)
        NEO_TRACE_LOG("Loading {0}", path.string().c_str());
        return IMG_LoadTexture(App::Get()->get_renderer(), path.string().c_str());
#endif // NEO_PLATFORM_LINUX
    }
    SDL_Texture* TextureRegistry::LoadTextureN(const std::filesystem::path& path) {
        if (!std::filesystem::exists(path)) {
#if defined(NEO_PLATFORM_LINUX)
            NEO_ERROR_LOG("File does not exist!: {0}", path.c_str());
#elif defined(NEO_PLATFORM_WINDOWS)
            NEO_ERROR_LOG("File does not exist!: {0}", path.string().c_str());
#endif // NEO_PLATFORM_LINUX
            return nullptr;
        }
#if defined(NEO_PLATFORM_LINUX)
        return IMG_LoadTexture(App::Get()->get_renderer(), path.c_str());
#elif defined(NEO_PLATFORM_WINDOWS)
        return IMG_LoadTexture(App::Get()->get_renderer(), path.string().c_str());
#endif // NEO_PLATFORM_LINUX
    }
    SDL_Texture* TextureRegistry::LoadTextureB(const std::filesystem::path& path) {
#if defined(NEO_PLATFORM_LINUX)
        if (std::filesystem::exists(path)) {
            NEO_TRACE_LOG("Loading {0}", path.c_str());
            return IMG_LoadTexture(App::Get()->get_renderer(), path.c_str());
        } else {
            NEO_ERROR_LOG("File does not exist!: {0}", path.c_str());
#elif defined(NEO_PLATFORM_WINDOWS)
        if (std::filesystem::exists(path)) {
            NEO_TRACE_LOG("Loading {0}", path.string().c_str());
            return IMG_LoadTexture(App::Get()->get_renderer(), path.string().c_str());
        } else {
            NEO_ERROR_LOG("File does not exist!: {0}", path.string().c_str());
#endif // NEO_PLATFORM_LINUX
            SDL_Color color = { 0x00, 0xff, 0xff, 0x00 };
            SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(&color, 1, 1, 8, 0, 0, 0, 0, 0);

            SDL_Texture* new_texture = SDL_CreateTextureFromSurface(App::Get()->get_renderer(), surface);
            SDL_FreeSurface(surface);
            return new_texture;
        }
    }
    
    id_t TextureRegistry::PushTexture(SDL_Texture* texture) {
        index_t index = TextureRegistry::s_Registry.size();
        TextureRegistry::s_Registry.push_back(texture);
        return index;
    }

    id_t TextureRegistry::CreateTexture(const std::filesystem::path& path) {
        return TextureRegistry::PushTexture(TextureRegistry::LoadTextureN(path));
    }
    id_t TextureRegistry::CreateTexture(void) {
        return TextureRegistry::PushTexture(nullptr);
    }
    id_t TextureRegistry::CreateTextureB(const std::filesystem::path& path) {
        return TextureRegistry::PushTexture(TextureRegistry::LoadTextureB(path));
    }

    void TextureRegistry::DestroyTexture(const id_t id) {
        SDL_DestroyTexture(TextureRegistry::s_Registry[id]);
        TextureRegistry::s_Registry[id] = nullptr;
    }

    void TextureRegistry::SetTexture(const id_t id, const std::filesystem::path& path) {
        if (!std::filesystem::exists(path)) {
#if defined(NEO_PLATFORM_LINUX)
            NEO_TRACE_LOG("Loading {0}", path.c_str());
#elif defined(NEO_PLATFORM_WINDOWS)
            NEO_TRACE_LOG("Loading {0}", path.string().c_str());
#endif // NEO_PLATFORM_LINUX
            return;
        }
        SDL_DestroyTexture(TextureRegistry::s_Registry[id]);
        TextureRegistry::s_Registry[id] = TextureRegistry::LoadTexture(path); 
    }
    void TextureRegistry::SetTextureB(const id_t id, const std::filesystem::path& path) {
        SDL_DestroyTexture(TextureRegistry::s_Registry[id]);
        TextureRegistry::s_Registry[id] = TextureRegistry::LoadTextureB(path); 
    }
    void TextureRegistry::SetTextureN(const id_t id, const std::filesystem::path& path) {
        SDL_DestroyTexture(TextureRegistry::s_Registry[id]);
        TextureRegistry::s_Registry[id] = TextureRegistry::LoadTextureN(path); 
    }

    void TextureRegistry::SetNullTexture(const id_t id, const std::filesystem::path& path) {
        if (!std::filesystem::exists(path)) {
#if defined(NEO_PLATFORM_LINUX)
            NEO_ERROR_LOG("File does not exist!: {0}", path.c_str());
#elif defined(NEO_PLATFORM_WINDOWS)
            NEO_ERROR_LOG("File does not exist!: {0}", path.string().c_str());
#endif // NEO_PLATFORM_LINUX
            return;
        }
        TextureRegistry::s_Registry[id] = TextureRegistry::LoadTexture(path); 
    }
    void TextureRegistry::SetNullTextureB(const id_t id, const std::filesystem::path& path) {
        TextureRegistry::s_Registry[id] = TextureRegistry::LoadTextureB(path); 
    }
    void TextureRegistry::SetNullTextureN(const id_t id, const std::filesystem::path& path) {
        TextureRegistry::s_Registry[id] = TextureRegistry::LoadTextureN(path); 
    }

    id_t TextureRegistry::FindFirstOf(SDL_Texture* texture) {
        index_t i = 0;
        for (auto it = TextureRegistry::s_Registry.begin(); it != TextureRegistry::s_Registry.end(); it++) {
            if (*it == texture)
                return i;
            i++;
        }
        return NEO_ID_MAX;
    }
    id_t TextureRegistry::FindLastOf(SDL_Texture* texture) {
        index_t i = TextureRegistry::s_Registry.size()-1;
        for (auto it = TextureRegistry::s_Registry.rbegin(); it != TextureRegistry::s_Registry.rend(); it++) {
            if (*it == texture)
                return i;
            i--;
        }
        return NEO_ID_MAX;
    }
} // namespace neo

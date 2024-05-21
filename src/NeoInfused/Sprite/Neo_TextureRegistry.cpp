#include "Neo_PCH.hpp"
#include "NeoInfused/Sprite/Neo_TextureRegistry.hpp"

#include "NeoInfused/Neo_App.hpp"

namespace neo {
    std::vector<SDL_Texture*> TextureRegistry::m_Registry;

    void TextureRegistry::Init(void) {
        m_Registry.clear();
    }
    void TextureRegistry::Reset(void) {
        for (index_t i = 0; i < m_Registry.size(); i++) {
            if (m_Registry[i]) {
                SDL_DestroyTexture(m_Registry[i]);
                m_Registry[i] = nullptr;
            }
        }
        m_Registry.clear();
    }

    SDL_Texture* TextureRegistry::_LoadTexture(const std::filesystem::path& path) {
#if defined(NEO_PLATFORM_LINUX)
        NEO_TRACE_LOG("Loading {0}", path.c_str());
        return IMG_LoadTexture(App::Get()->get_renderer(), path.c_str());
#elif defined(NEO_PLATFORM_WINDOWS)
        NEO_TRACE_LOG("Loading {0}", path.string().c_str());
        return IMG_LoadTexture(App::Get()->get_renderer(), path.string().c_str());
#endif // NEO_PLATFORM_LINUX
    }
    SDL_Texture* TextureRegistry::_LoadTextureN(const std::filesystem::path& path) {
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
    SDL_Texture* TextureRegistry::_LoadTextureB(const std::filesystem::path& path) {
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
    
    id_t TextureRegistry::_PushTexture(SDL_Texture* texture) {
        index_t index = m_Registry.size();
        m_Registry.push_back(texture);
        return index;
    }

    id_t TextureRegistry::CreateTexture(const std::filesystem::path& path) {
        return TextureRegistry::_PushTexture(TextureRegistry::_LoadTextureN(path));
    }
    id_t TextureRegistry::CreateTexture(void) {
        return TextureRegistry::_PushTexture(nullptr);
    }
    id_t TextureRegistry::CreateTextureB(const std::filesystem::path& path) {
        return TextureRegistry::_PushTexture(TextureRegistry::_LoadTextureB(path));
    }

    void TextureRegistry::DestroyTexture(const id_t id) {
        SDL_DestroyTexture(TextureRegistry::m_Registry[id]);
        TextureRegistry::m_Registry[id] = nullptr;
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
        SDL_DestroyTexture(TextureRegistry::m_Registry[id]);
        m_Registry[id] = TextureRegistry::_LoadTexture(path); 
    }
    void TextureRegistry::SetTextureB(const id_t id, const std::filesystem::path& path) {
        SDL_DestroyTexture(m_Registry[id]);
        m_Registry[id] = TextureRegistry::_LoadTextureB(path); 
    }
    void TextureRegistry::SetTextureN(const id_t id, const std::filesystem::path& path) {
        SDL_DestroyTexture(m_Registry[id]);
        m_Registry[id] = TextureRegistry::_LoadTextureN(path); 
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
        m_Registry[id] = TextureRegistry::_LoadTexture(path); 
    }
    void TextureRegistry::SetNullTextureB(const id_t id, const std::filesystem::path& path) {
        m_Registry[id] = TextureRegistry::_LoadTextureB(path); 
    }
    void TextureRegistry::SetNullTextureN(const id_t id, const std::filesystem::path& path) {
        m_Registry[id] = TextureRegistry::_LoadTextureN(path); 
    }

    id_t TextureRegistry::FindFirstOf(SDL_Texture* texture) {
        index_t i = 0;
        for (auto it = m_Registry.begin(); it != m_Registry.end(); it++) {
            if (*it == texture)
                return i;
            i++;
        }
        return NEO_ID_MAX;
    }
    id_t TextureRegistry::FindLastOf(SDL_Texture* texture) {
        index_t i = m_Registry.size()-1;
        for (auto it = m_Registry.rbegin(); it != m_Registry.rend(); it++) {
            if (*it == texture)
                return i;
            i--;
        }
        return NEO_ID_MAX;
    }
} // namespace neo

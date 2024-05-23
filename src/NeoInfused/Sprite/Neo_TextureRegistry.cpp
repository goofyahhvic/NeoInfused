#include "Neo_PCH.hpp"
#include "NeoInfused/Sprite/Neo_TextureRegistry.hpp"

#include "NeoInfused/Neo_App.hpp"

namespace neo {
    SDL_Texture** TextureRegistry::m_Arena;
    uint32_t TextureRegistry::m_ArenaSize, TextureRegistry::m_ArenaInsertIndex;

    void TextureRegistry::Alloc(uint32_t arena_size) {
        m_Arena = (SDL_Texture**) malloc(arena_size*8);
        m_ArenaSize = arena_size;
        m_ArenaInsertIndex = 0;
    }
    void TextureRegistry::ReAlloc(uint32_t new_arena_size) {
        if (m_ArenaInsertIndex > new_arena_size) {
            throw std::runtime_error("[TextureRegistry]: Cannot realloc size smaller than the insert index!");
        }
        m_Arena = (SDL_Texture**) realloc(m_Arena, new_arena_size);
        m_ArenaSize = new_arena_size;
    }
    void TextureRegistry::DestroyAll(void) {
        for (index32_t i = 0; i < m_ArenaInsertIndex; i++) {
            if (m_Arena[i]) {
                SDL_DestroyTexture(m_Arena[i]);
                m_Arena[i] = nullptr;
            }
        }
        m_ArenaInsertIndex = 0;
    }
    void TextureRegistry::Free(void) {
        TextureRegistry::DestroyAll();
        free(m_Arena);
        m_Arena = nullptr;
        m_ArenaSize = 0;
    }
    index32_t TextureRegistry::_PushTexture(SDL_Texture* texture) {
        m_Arena[m_ArenaInsertIndex] = texture;
        m_ArenaInsertIndex++;
        return m_ArenaInsertIndex-1;
    }

    SDL_Texture* TextureRegistry::_LoadTexture(const std::filesystem::path& path) {
#if defined(NEO_PLATFORM_LINUX)
        NEO_TRACE_LOG("Loading {0}", path.c_str());
        return IMG_LoadTexture(Renderer::GetBound()->get_native(), path.c_str());
#elif defined(NEO_PLATFORM_WINDOWS)
        NEO_TRACE_LOG("Loading {0}", path.string().c_str());
        return IMG_LoadTexture(Renderer::GetBound()->get_native(), path.string().c_str());
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
        NEO_TRACE_LOG("Loading {0}", path.c_str());
        return IMG_LoadTexture(Renderer::GetBound()->get_native(), path.c_str());
#elif defined(NEO_PLATFORM_WINDOWS)
        NEO_TRACE_LOG("Loading {0}", path.string().c_str());
        return IMG_LoadTexture(Renderer::GetBound()->get_native(), path.string().c_str());
#endif // NEO_PLATFORM_LINUX
    }
    SDL_Texture* TextureRegistry::_LoadTextureB(const std::filesystem::path& path) {
#if defined(NEO_PLATFORM_LINUX)
        if (std::filesystem::exists(path)) {
            NEO_TRACE_LOG("Loading {0}", path.c_str());
            return IMG_LoadTexture(Renderer::GetBound()->get_native(), path.c_str());
        } else {
            NEO_ERROR_LOG("File does not exist!: {0}", path.c_str());
#elif defined(NEO_PLATFORM_WINDOWS)
        if (std::filesystem::exists(path)) {
            NEO_TRACE_LOG("Loading {0}", path.string().c_str());
            return IMG_LoadTexture(Renderer::GetBound()->get_native(), path.string().c_str());
        } else {
            NEO_ERROR_LOG("File does not exist!: {0}", path.string().c_str());
#endif // NEO_PLATFORM_LINUX
            SDL_Color color = { 0x00, 0xff, 0xff, 0x00 };
            SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(&color, 1, 1, 8, 0, 0, 0, 0, 0);

            SDL_Texture* new_texture = SDL_CreateTextureFromSurface(Renderer::GetBound()->get_native(), surface);
            SDL_FreeSurface(surface);
            return new_texture;
        }
    }
    
    index32_t TextureRegistry::CreateTexture(const std::filesystem::path& path) {
        return TextureRegistry::_PushTexture(TextureRegistry::_LoadTextureN(path));
    }
    index32_t TextureRegistry::CreateTexture(void) {
        return TextureRegistry::_PushTexture(nullptr);
    }
    index32_t TextureRegistry::CreateTextureB(const std::filesystem::path& path) {
        return TextureRegistry::_PushTexture(TextureRegistry::_LoadTextureB(path));
    }

    index32_t TextureRegistry::DestroyTexture(const index32_t id) {
        SDL_DestroyTexture(m_Arena[id]);
        m_Arena[id] = nullptr;
        return id;
    }

    index32_t TextureRegistry::SetTexture(const index32_t id, const std::filesystem::path& path) {
        if (!std::filesystem::exists(path)) {
#if defined(NEO_PLATFORM_LINUX)
            NEO_TRACE_LOG("File does not exist!: {0}", path.c_str());
#elif defined(NEO_PLATFORM_WINDOWS)
            NEO_TRACE_LOG("File does not exist!: {0}", path.string().c_str());
#endif // NEO_PLATFORM_LINUX
            return UINT32_MAX;
        }
        SDL_DestroyTexture(m_Arena[id]);
        m_Arena[id] = TextureRegistry::_LoadTexture(path); 
        return id;
    }
    index32_t TextureRegistry::SetTextureB(const index32_t id, const std::filesystem::path& path) {
        SDL_DestroyTexture(m_Arena[id]);
        m_Arena[id] = TextureRegistry::_LoadTextureB(path); 
        return id;
    }

    index32_t TextureRegistry::SetNullTexture(const index32_t id, const std::filesystem::path& path) {
        if (!std::filesystem::exists(path)) {
#if defined(NEO_PLATFORM_LINUX)
            NEO_ERROR_LOG("File does not exist!: {0}", path.c_str());
#elif defined(NEO_PLATFORM_WINDOWS)
            NEO_ERROR_LOG("File does not exist!: {0}", path.string().c_str());
#endif // NEO_PLATFORM_LINUX
            return UINT32_MAX;
        }
        m_Arena[id] = TextureRegistry::_LoadTexture(path); 
        return id;
    }
    index32_t TextureRegistry::SetNullTextureB(const index32_t id, const std::filesystem::path& path) {
        m_Arena[id] = TextureRegistry::_LoadTextureB(path);
        return id;
    }

    index32_t TextureRegistry::FindFirstOf(SDL_Texture* texture) {
        SDL_Texture* it = m_Arena[0];
        for (index32_t i = 0; i < m_ArenaInsertIndex; i++) {
            NEO_TRACE_LOG("[FindFirstOf] i: {0}", i);
            if (it == texture)
                return i;
            it = m_Arena[i+1];
        }
        return UINT32_MAX;
    }
    index32_t TextureRegistry::FindLastOf(SDL_Texture* texture) {
        SDL_Texture* it = m_Arena[m_ArenaInsertIndex-1];
        for (index32_t i = m_ArenaInsertIndex; i > 0; i--) {
            if (it == texture)
                return (index32_t) i-1;
            it = m_Arena[i-2];
        }
        return UINT32_MAX;
    }
} // namespace neo

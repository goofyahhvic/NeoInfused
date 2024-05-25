#include "Neo_PCH.hpp"
#include "NeoInfused/Sprite/Neo_Texture.hpp"

#include "NeoInfused/Neo_Renderer.hpp"

namespace neo {
    Texture::Texture(const std::filesystem::path& path) {
        if (!std::filesystem::exists(path)) {
            NEO_ASSERT(NULL, "Failed to load image in {0}", path.C_STR);
            m_State = State::Failed;
            return;
        }
        NEO_TRACE_LOG("Loading texture from {0}", path.C_STR);
        m_Texture = IMG_LoadTexture(Renderer::GetBound()->get_native(), path.C_STR);
        m_RefCount = new uint32_t;
        (*m_RefCount) = 1;
        m_State = State::Created;
    }
    void Texture::destroy(void) {
        if (!m_Texture) return;
        m_State = State::Null;
        SDL_DestroyTexture(m_Texture);
        m_Texture = nullptr;
        delete m_RefCount;
    }

    Texture::Texture(const Texture& texture) {
        m_Texture = texture.m_Texture;
        m_State = texture.m_State;
        m_RefCount = texture.m_RefCount;
        (*m_RefCount)++;
    }
    void Texture::operator=(const Texture& texture) {
        m_Texture = texture.m_Texture;
        m_State = texture.m_State;
        m_RefCount = texture.m_RefCount;
        (*m_RefCount)++;
    }

    void Texture::set(const std::filesystem::path& path) {
        if (!std::filesystem::exists(path)) {
            NEO_ASSERT(NULL, "Failed to load image in {0}", path.C_STR);
            m_State = State::Failed;
            return;
        }
        if (!m_Texture) {
            NEO_TRACE_LOG("Loading texture from {0}", path.C_STR);
            m_Texture = IMG_LoadTexture(Renderer::GetBound()->get_native(), path.C_STR);
            m_State = State::Created;
            return;
        }
        SDL_DestroyTexture(m_Texture);
        NEO_TRACE_LOG("Loading texture from {0}", path.C_STR);
        m_Texture = IMG_LoadTexture(Renderer::GetBound()->get_native(), path.C_STR);
        m_State = State::Created;
    }
} // namespace neo

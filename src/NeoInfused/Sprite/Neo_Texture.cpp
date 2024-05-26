#include "Neo_PCH.hpp"
#include "NeoInfused/Sprite/Neo_Texture.hpp"

#include "NeoInfused/Neo_Renderer.hpp"

namespace neo {
    Texture* Texture::New(const std::filesystem::path& path) {
        if (!std::filesystem::exists(path)) {
            NEO_ASSERT(NULL, "Failed to load image in {0}", path.C_STR);
            return nullptr;
        }
        Texture* _this = new Texture;
        NEO_TRACE_LOG("Loading texture from {0}", path.C_STR);
        _this->m_Texture = IMG_LoadTexture(Renderer::GetBound()->get_native(), path.C_STR);
        return _this;
    }
    void Texture::Delete(Texture* _this) {
        if (!_this) return;
        SDL_DestroyTexture(_this->m_Texture);
        delete _this;
    }

    void Texture::set(const std::filesystem::path& path) {
        if (!std::filesystem::exists(path)) {
            NEO_ASSERT(NULL, "Failed to load image in {0}", path.C_STR);
            return;
        }
        if (!m_Texture) {
            NEO_TRACE_LOG("Loading texture from {0}", path.C_STR);
            m_Texture = IMG_LoadTexture(Renderer::GetBound()->get_native(), path.C_STR);
            return;
        }
        SDL_DestroyTexture(m_Texture);
        NEO_TRACE_LOG("Loading texture from {0}", path.C_STR);
        m_Texture = IMG_LoadTexture(Renderer::GetBound()->get_native(), path.C_STR);
    }
} // namespace neo

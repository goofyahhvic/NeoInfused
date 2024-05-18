#include "Neo_PCH.hpp"
#include "NeoInfused/Sprite/Neo_TextureHandle.hpp"

#include "NeoInfused/Neo_App.hpp"

namespace neo {
    void TextureHandle::draw(float dest_x, float dest_y, float dest_w, float dest_h, int32_t src_x, int32_t src_y, int32_t src_w, int32_t src_h) const {
        SDL_FRect dest_rect = { dest_x, dest_y, dest_w, dest_h };
        SDL_Rect  src_rect  = { src_x,  src_y,  src_w,  src_h };
        SDL_RenderCopyF(App::Get()->get_renderer(), TextureRegistry::GetTexture(TextureHandle::id), &src_rect, &dest_rect);
    }
    void TextureHandle::draw(float dest_x, float dest_y, float dest_w, float dest_h) const {
        SDL_FRect dest_rect = { dest_x, dest_y, dest_w, dest_h };
        SDL_RenderCopyF(App::Get()->get_renderer(), TextureRegistry::GetTexture(TextureHandle::id), NULL, &dest_rect);
    }
    void TextureHandle::draw(const SDL_FRect* dest_rect, const SDL_Rect* src_rect) const {
        SDL_RenderCopyF(App::Get()->get_renderer(), TextureRegistry::GetTexture(TextureHandle::id), src_rect, dest_rect);
    }
} // namespace neo

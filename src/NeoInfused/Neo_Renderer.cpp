#include "Neo_PCH.hpp"
#include "NeoInfused/Neo_Renderer.hpp"

namespace neo {
    Renderer* Renderer::m_BoundRenderer;
    int32_t Renderer::m_NewRendererIndex;
    std::list<SDL_Renderer*> Renderer::m_Renderers;

    void Renderer::Init(void) {
        Renderer::m_NewRendererIndex = -1;
    }
    void Renderer::Terminate(void) {
        for (auto renderer : Renderer::m_Renderers) 
            SDL_DestroyRenderer(renderer);
        Renderer::m_Renderers.clear();
    }

    Renderer::Renderer(SDL_Window* window, int32_t flags) {
        m_Renderer = SDL_CreateRenderer(window, Renderer::m_NewRendererIndex, flags);
        NEO_ASSERT(m_Renderer, "Failed to create SDL_Renderer: {0}", SDL_GetError());
        SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);

        Renderer::m_NewRendererIndex++;
        Renderer::m_Renderers.push_back(m_Renderer);
    }
    void Renderer::destroy(void) {
        Renderer::m_Renderers.remove(m_Renderer);
        SDL_DestroyRenderer(m_Renderer);
        m_Renderer = nullptr;
    }

    void Renderer::blit(SDL_Texture* texture, SDL_FRect* dest_rect, SDL_Rect* src_rect, double angle, SDL_FPoint* center, SDL_RendererFlip flip) const {
        SDL_RenderCopyExF(m_Renderer, texture, src_rect, dest_rect, angle, center, flip);
    }
    void Renderer::blit(const BlitInfo& info) const {
        SDL_RenderCopyExF(m_Renderer, info.texture, info.src_rect, info.dest_rect, info.angle, info.center, info.flip);
    }

    void Renderer::clear(void) {
        SDL_RenderClear(m_Renderer);
    }
    void Renderer::present(void) const {
        SDL_RenderPresent(m_Renderer);
    }
    void Renderer::set_draw_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        SDL_SetRenderDrawColor(m_Renderer, r, g, b, a);
    }
    void Renderer::set_scale(float x, float y) {
        SDL_RenderSetScale(m_Renderer, x, y);
    }
} // namespace neo

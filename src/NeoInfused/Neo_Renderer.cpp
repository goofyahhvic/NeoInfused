#include "Neo_PCH.hpp"
#include "NeoInfused/Neo_Renderer.hpp"

namespace neo {
    Renderer* Renderer::m_BoundRenderer;
    std::vector<SDL_Renderer*> Renderer::m_Renderers;

    void Renderer::Init(void) {
        Renderer::m_BoundRenderer = nullptr;
    }
    void Renderer::Terminate(void) {
        if (Renderer::m_Renderers.empty()) return;
        for (auto renderer : Renderer::m_Renderers) 
            SDL_DestroyRenderer(renderer);
        Renderer::m_Renderers.clear();
    }

    Renderer* Renderer::New(int16_t flags, Window* window, int16_t driver_index) {
        Renderer* _this = new Renderer;
        _this->m_Renderer = SDL_CreateRenderer(window->get_native(), -1, flags);
        _this->m_RendererIndex = Renderer::m_Renderers.size();

        Renderer::m_Renderers.push_back(_this->m_Renderer);
        if (!Renderer::m_BoundRenderer) Renderer::m_BoundRenderer = _this;

        return _this;
    }
    void Renderer::Delete(Renderer* _this) {
        if (!_this->m_Renderer) return;
        if (_this == Renderer::m_BoundRenderer)
            Renderer::m_BoundRenderer = nullptr;

        Renderer::m_Renderers.erase(Renderer::m_Renderers.begin() + _this->m_RendererIndex);
        SDL_DestroyRenderer(_this->m_Renderer);
        delete _this;
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

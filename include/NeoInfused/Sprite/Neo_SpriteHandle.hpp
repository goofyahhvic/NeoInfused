#if !defined(NEO_SPRITE_HPP)
#define NEO_SPRITE_HPP

#include "./Neo_SpriteRegistry.hpp"

namespace neo {
    class SpriteHandle {
    #define SPRITE_DATA SpriteRegistry::GetSpriteData(m_Id)
        SpriteHandle(uint64_t id) : m_Id(id) {};
    public:
        SpriteHandle() = default;
        ~SpriteHandle() = default;
        
        static inline SpriteHandle CreateSprite(float x, float y, float w, float h, const std::filesystem::path& path) { return SpriteHandle(SpriteRegistry::PushSpriteData(CreateSpriteData(x, y, w, h, path))); }

        static inline void DestroySprite(SpriteHandle s) { SpriteRegistry::DestroySpriteData(s.m_Id); }
        inline void destroy(void) { SpriteRegistry::DestroySpriteData(m_Id); }

        inline void draw(void) const { DrawSpriteData(SPRITE_DATA); }

    public:
        inline float get_x(void) const { return SPRITE_DATA->rect.x; }
        inline float get_y(void) const { return SPRITE_DATA->rect.y; }
        inline float get_w(void) const { return SPRITE_DATA->rect.w; }
        inline float get_h(void) const { return SPRITE_DATA->rect.h; }

        inline void get_pos(float* x, float* y) const { *x = SPRITE_DATA->rect.x; *y = SPRITE_DATA->rect.y; }
        inline void get_pos(float& x, float& y) const { x = SPRITE_DATA->rect.x; y = SPRITE_DATA->rect.y; }
        inline glm::vec2 get_pos(void) const { return { SPRITE_DATA->rect.x, SPRITE_DATA->rect.y }; }

        inline void get_size(float* w, float* h) const { *w = SPRITE_DATA->rect.w; *h = SPRITE_DATA->rect.h; }
        inline void get_size(float& w, float& h) const { w = SPRITE_DATA->rect.w; h = SPRITE_DATA->rect.h; }
        inline glm::vec2 get_size(void) const { return { SPRITE_DATA->rect.w, SPRITE_DATA->rect.h }; }

        inline SDL_FRect get_rect(void) const { return SPRITE_DATA->rect; }

        inline void set_x(float x) { SPRITE_DATA->rect.x = x; }
        inline void set_y(float y) { SPRITE_DATA->rect.y = y; }
        inline void set_w(float w) { SPRITE_DATA->rect.w = w; }
        inline void set_h(float h) { SPRITE_DATA->rect.h = h; }

        inline void set_pos(float x, float y) { SPRITE_DATA->rect.x = x; SPRITE_DATA->rect.y = y; }
        inline void set_size(float w, float h) { SPRITE_DATA->rect.w = w; SPRITE_DATA->rect.h = h; }

        inline void move(float x, float y) { SPRITE_DATA->rect.x += x; SPRITE_DATA->rect.y += y; }
        inline void increase_size(float w, float h) { SPRITE_DATA->rect.w += w; SPRITE_DATA->rect.h += h; }

        inline void set_rect(float x, float y, float w, float h) { SPRITE_DATA->rect = { x, y, w, h }; }
    private:
        uint64_t m_Id;
    };
    using Sprite = SpriteHandle;
} // namespace neo

#endif // NEO_SPRITE_HPP
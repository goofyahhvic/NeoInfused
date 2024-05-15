#if !defined(NEO_SPRITE_DATA_HPP)
#define NEO_SPRITE_DATA_HPP

namespace neo {
    struct SpriteData {
        SDL_FRect rect;
        SDL_Texture* texture;
    };

    SpriteData* CreateSpriteData(float x, float y, float w, float h, const std::filesystem::path& path);
    void DestroySpriteData(SpriteData* s);
    void DrawSpriteData(SpriteData* s);
} // namespace neo

#endif // NEO_SPRITE_DATA_HPP
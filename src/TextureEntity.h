#ifndef TEXTURE_ENTITY_H
#define TEXTURE_ENTITY_H

#include <engine/Sprite.h>

struct EntityPosition
{
    int x = 0;
    int y = 0;
};

enum class EntityAlign
{
    LeftUpper = 0,
    Center = 1
};

class TextureEntity
{
public:
    TextureEntity();
    TextureEntity(const std::shared_ptr<Sprite>& texture, EntityAlign align = EntityAlign::LeftUpper);
    
    virtual void update(const double delta);
    virtual void render(SDL_Renderer* renderer) const;
    
    // get and set position of sprite
    void setPosition(const EntityPosition position);
    EntityPosition getPosition() const;
    
    // change size by multiplying
    void setSizeMultiplier(const float multiplier);
    
    // return rect of sprite
    SDL_Rect getTextureRect() const;
    
    // get texture of sprite
    const std::shared_ptr<Sprite>& getTexture() const;
    
private:
    std::shared_ptr<Sprite> texture;
    
    EntityPosition position;
    EntityAlign align = EntityAlign::LeftUpper;
    
    float sizeMultiplier = 1.0f;
};

#endif 

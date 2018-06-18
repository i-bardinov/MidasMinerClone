#ifndef TEXTURE_ENTITY_H
#define TEXTURE_ENTITY_H

#include <Texture.h>

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
    TextureEntity(std::shared_ptr<Texture> texture, EntityAlign align = EntityAlign::LeftUpper);
    
    virtual void update(const double delta);
    virtual void render(SDL_Renderer * renderer) const;
    
    // get and set position of sprite
    void setPosition(const EntityPosition position);
    EntityPosition getPosition() const;
    
    // change size by multiplying
    void setSizeMultiplier(const float multiplier);
    
    // return rect of sprite
    SDL_Rect getTextureRect() const;
    
    // get and set texture of sprite
    std::shared_ptr<Texture> getTexture() const;
    void setTexture(const std::shared_ptr<Texture> texture);
    
private:
    std::shared_ptr<Texture> texture;
    
    EntityPosition position;
    EntityAlign align = EntityAlign::LeftUpper;
    
    float sizeMultiplier = 1.0f;
};

#endif 

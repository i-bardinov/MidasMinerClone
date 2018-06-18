#include "TextureEntity.h"

TextureEntity::TextureEntity()
{
    
}

TextureEntity::TextureEntity(const std::shared_ptr<Texture>& _texture, EntityAlign _align)
{
    this->texture = _texture;
    this->align = _align;
}

void TextureEntity::setPosition(const EntityPosition _position)
{
    this->position = _position;
}

EntityPosition TextureEntity::getPosition() const
{
    return position;
}

void TextureEntity::setSizeMultiplier(const float multiplier)
{
    this->sizeMultiplier = multiplier;
}

SDL_Rect TextureEntity::getTextureRect() const
{
    SDL_Rect rect;
    if(align == EntityAlign::LeftUpper)
    {
        rect.x = position.x;
        rect.y = position.y;
    }
    else if(align == EntityAlign::Center)
    {
        rect.x = position.x - texture->getWidth() * sizeMultiplier / 2;
        rect.y = position.y - texture->getHeight() * sizeMultiplier / 2;
    }

    if(texture)
    {
        rect.w = texture->getWidth() * sizeMultiplier;
        rect.h = texture->getHeight() * sizeMultiplier;
    }
        
    return rect;
}

const std::shared_ptr<Texture>& TextureEntity::getTexture() const
{
    return texture;
}

void TextureEntity::update(const double delta)
{
    
}

void TextureEntity::render(SDL_Renderer * renderer) const
{
    SDL_Rect rect = getTextureRect();
    if(texture)
        SDL_RenderCopy(renderer, texture->getSDLTexture(), NULL, &rect);
}

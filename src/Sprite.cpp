#include "Sprite.h"

Sprite::Sprite()
{
    
}

Sprite::Sprite(SDL_Texture* img)
{
    texture.reset(img);
    // get the width and height of the texture
    SDL_QueryTexture(texture.get(), NULL, NULL, &width, &height);
}

SDL_Texture* Sprite::getSDLTexture() const
{
    return texture.get();
}

void Sprite::setTransparency(const Uint8 transparency)
{
    SDL_SetTextureAlphaMod(texture.get(), transparency);
}

const int Sprite::getWidth() const
{
    return width;
}

const int Sprite::getHeight() const
{
    return height;
}

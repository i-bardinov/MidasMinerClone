#include "Texture.h"

Texture::Texture()
{
    
}

Texture::Texture(SDL_Texture* img)
{
    texture.reset(img);
    // get the width and height of the texture
    SDL_QueryTexture(texture.get(), NULL, NULL, &width, &height);
}

SDL_Texture* Texture::getSDLTexture() const
{
    return texture.get();
}

void Texture::setTransparency(const Uint8 transparency)
{
    SDL_SetTextureAlphaMod(texture.get(), transparency);
}

const int Texture::getWidth() const
{
    return width;
}

const int Texture::getHeight() const
{
    return height;
}

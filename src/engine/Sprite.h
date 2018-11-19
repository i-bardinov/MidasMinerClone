#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <memory>

class Sprite
{
public:
    Sprite();
    Sprite(SDL_Texture* img);
    
    SDL_Texture* getSDLTexture() const;
    
    void setTransparency(const Uint8 transparency);
    
    // return base size of texture
    const int getWidth() const;
    const int getHeight() const;
    
private:
    std::unique_ptr<SDL_Texture, void(*)(SDL_Texture *)> texture = std::unique_ptr<SDL_Texture, void (*)(SDL_Texture *)>(nullptr, SDL_DestroyTexture);
    
    int width = 0;
    int height = 0;
};

#endif 

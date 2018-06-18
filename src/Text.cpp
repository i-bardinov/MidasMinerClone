#include "Text.h"
#include <iostream>

Text::Text()
{
    
}

Text::Text(const std::shared_ptr<Font>& _font, const std::string& _text)
{
    this->font = _font;
    this->text = _text;
}

void Text::setPosition(const int x, const int y)
{
    positionX = x;
    positionY = y;
}

void Text::setText(const std::string& _text)
{
    this->text = _text;
}

void Text::setColor(const Uint8 _r, const Uint8 _g, const Uint8 _b, const Uint8 _a)
{
    color.r = _r;
    color.g = _g;
    color.b = _b;
    color.a = _a;
}

const std::shared_ptr<Font>& Text::getFont() const
{
    return font;
}

void Text::render(SDL_Renderer* renderer) const
{
    if(!font)
        return;
    
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font->getSDLFont(), text.c_str(), color);
    if(!textSurface)
    {
        std::cout << "TTF_RenderText_Solid Error: " << TTF_GetError() << std::endl;
    }
    else
    {
        //Create texture from surface pixels
        SDL_Texture *mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if(!mTexture)
        {
            std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        }
        else
        {
            //Get image dimensions
            int mWidth = textSurface->w;
            int mHeight = textSurface->h;
            SDL_Rect renderQuad = { positionX, positionY, mWidth, mHeight };
            SDL_RenderCopy(renderer, mTexture, NULL, &renderQuad);
        }
        
        //Get rid of old surface
        SDL_DestroyTexture(mTexture);
    }
    SDL_FreeSurface(textSurface);
}

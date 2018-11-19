#ifndef FONT_H
#define FONT_H

#include <SDL_ttf.h>
#include <memory>

class Font
{
public:
    Font();
    Font(TTF_Font* font);
    
    TTF_Font* getSDLFont() const;
    
private:
    std::unique_ptr<TTF_Font, void(*)(TTF_Font *)> font = std::unique_ptr<TTF_Font, void (*)(TTF_Font *)>(nullptr, TTF_CloseFont);
};

#endif

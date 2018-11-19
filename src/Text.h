#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <SDL.h>

#include <engine/Font.h>

class Text
{
public:
    Text();
    Text(const std::shared_ptr<Font>& font, const std::string& text);
    
    // setter methods for text (position, text, color)
    void setPosition(const int x, const int y);
    void setText(const std::string& text);
    void setColor(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a = 0);
    
    // return Font for this text
    const std::shared_ptr<Font>& getFont() const;
    
    virtual void render(SDL_Renderer* renderer) const;
    
private:
    std::shared_ptr<Font> font;
    std::string text;
    SDL_Color color = { 255, 255, 255 };
    
    int positionX = 0;
    int positionY = 0;
};
#endif

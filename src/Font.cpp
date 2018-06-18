#include "Font.h"

Font::Font()
{
    
}

Font::Font(TTF_Font *_font)
{
    font.reset(_font);
}

TTF_Font * Font::getSDLFont() const
{
    return font.get();
}

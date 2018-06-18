#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <list>
#include <string>

#include "Texture.h"
#include "Font.h"
#include "Sound.h"
#include "Music.h"

class Engine
{
public:
    Engine();
    ~Engine();
    
    // init engine
    bool init();
    // update engine
    bool update(std::list<int>& inputs);
    // render clean and draw
    void renderStart() const;
    void renderStop() const;
    
    // get mouse positions
    const int getMousePositionX() const;
    const int getMousePositionY() const;
    
    SDL_Renderer * getRenderer() const;
    
    // load game assets in engine
    std::shared_ptr<Texture> loadTexture(const std::string& textureName);
    std::shared_ptr<Font> loadFont(const std::string& fontName);
    std::shared_ptr<Sound> loadSound(const std::string& soundName);
    std::shared_ptr<Music> loadMusic(const std::string& musicName);
    
private:
    std::unique_ptr<SDL_Window, void(*)(SDL_Window *)> window = std::unique_ptr<SDL_Window, void (*)(SDL_Window*)>(nullptr, SDL_DestroyWindow);
    std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer *)> renderer = std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)>(nullptr, SDL_DestroyRenderer);
    
    int mousePosX = 0;
    int mousePosY = 0;
};

#endif

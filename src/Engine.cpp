#include <iostream>

#include "Engine.h"
#include "Const.h"
#include "Game.h"

Engine::Engine()
{
    
}

Engine::~Engine()
{
    SDL_Quit();
    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
}

bool Engine::init()
{
    // let's init SDL2
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    // let's init SDL2 TTF
    if(TTF_Init() != 0)
    {
        std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
        return false;
    }
    
    // init audio
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) != 0)
    {
        std::cout << "Mix_OpenAudio Error: " << Mix_GetError() << std::endl;
        return false;
    }
    
    // create a window
    window.reset(SDL_CreateWindow("MidasMinerClone", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE));
    if(!window)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    // create a renderer for window
    renderer.reset(SDL_CreateRenderer(window.get(), -1,  SDL_RENDERER_ACCELERATED));
    if(!renderer)
    {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    return true;
}

bool Engine::update(std::list<int>& inputs)
{
    SDL_Event event;
    
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                inputs.push_back(InputEvent::Quit);
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
                {
                    inputs.push_back(InputEvent::Restart);
                } else if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                {
                    inputs.push_back(InputEvent::Pause);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                inputs.push_back(InputEvent::MouseClickDown);
                break;
            case SDL_MOUSEBUTTONUP:
                inputs.push_back(InputEvent::MouseClickUp);
                break;
            case SDL_MOUSEMOTION:
                mousePosX = event.motion.x;
                mousePosY = event.motion.y;
                break;
        }

    }
    
    return true;
}

void Engine::renderStart() const
{
    // clear the screen
    SDL_RenderClear(renderer.get());
}

void Engine::renderStop() const
{
    // flip the backbuffer
    SDL_RenderPresent(renderer.get());
}

SDL_Renderer * Engine::getRenderer() const
{
    return renderer.get();
}

const int Engine::getMousePositionX() const
{
    return mousePosX;
}

const int Engine::getMousePositionY() const
{
    return mousePosY;
}

std::shared_ptr<Texture> Engine::loadTexture(const std::string& textureName)
{
    std::string fullPath = ASSETS_PATH + textureName;
    // load our image
    SDL_Texture* img = IMG_LoadTexture(renderer.get(), fullPath.c_str());
    if(!img)
    {
        std::cout << "IMG_LoadTexture Error: " << SDL_GetError() << std::endl;
    }
    
    std::shared_ptr<Texture> texture(new Texture(img));
    
    return texture;
}

std::shared_ptr<Font> Engine::loadFont(const std::string& fontName)
{
    std::string fullPath = ASSETS_PATH + fontName;
    // load our font
    TTF_Font *ttfFont = TTF_OpenFont(fullPath.c_str(), 32);
    if(!ttfFont)
    {
        std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
    }
    
    std::shared_ptr<Font> font(new Font(ttfFont));
    
    return font;
}

std::shared_ptr<Sound> Engine::loadSound(const std::string& soundName)
{
    std::string fullPath = ASSETS_PATH + soundName;
    // Load our sound effect
    Mix_Chunk *chunk = Mix_LoadWAV(fullPath.c_str());
    if(!chunk)
    {
        std::cout << "Mix_LoadWAV Error: " << TTF_GetError() << std::endl;
    }
    
    std::shared_ptr<Sound> sound(new Sound(chunk));
    
    return sound;
}

std::shared_ptr<Music> Engine::loadMusic(const std::string& musicName)
{
    std::string fullPath = ASSETS_PATH + musicName;
    // Load our music
    Mix_Music *mus = Mix_LoadMUS(fullPath.c_str());
    if(!mus)
    {
        std::cout << "Mix_LoadMUS Error: " << TTF_GetError() << std::endl;
    }
    
    std::shared_ptr<Music> music(new Music(mus));
    
    return music;
}

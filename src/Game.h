#ifndef GAME_H
#define GAME_H

#include "engine/Engine.h"

#include <vector>
#include <list>
#include <string>

#include "TextureEntity.h"
#include "engine/Sprite.h"
#include "engine/Font.h"
#include "engine/Sound.h"
#include "engine/Music.h"
#include "Text.h"
#include "Gem.h"
#include "Field.h"

enum InputEvent
{
    Quit = 0,
    MouseClickUp,
    MouseClickDown,
    Restart,
    Pause
};

enum class GameState
{
    None = 0,
    Inited,
    Loading,
    Playing,
    Paused,
    Ended
};

class Game
{
public:
	Game();

    // main methods in game
	bool init();
	void update();
    void restart();
    
private:
    void render() const;
    
    // load assets
    void loadTextures();
    void loadFonts();
    void loadAudio();
            
    Engine engine;
    Field playField;
    
    int prevGemClick = -1;
        
    std::list<int> inputs;
    
    bool quitSignalReceived = false;
    GameState state = GameState::None;
    double prevTime = 0.0f;
    double waitTime = 0.0f;
    
    std::shared_ptr<Font> font;
    
    // game music
    std::shared_ptr<Music> musicStart;
    std::shared_ptr<Music> musicGameOver;
        
    TextureEntity background;
    Text scoreText, timerText, startText, restartText;
};

#endif

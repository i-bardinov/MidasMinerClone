#include <iostream>
#include <ctime>

#include "Game.h"
#include "Const.h"
#include "Texture.h"

Game::Game()
{

}

bool Game::init()
{
	srand((unsigned)time(0));
    
    if(!engine.init())
    {
        std::cout << "Error when try to init Engine!" << std::endl;
        return false;
    }
    
    // load assets
    loadTextures();
    loadFonts();
    loadAudio();
    
    // initial state
    state = GameState::Inited;
    
	return true;
}

void Game::restart()
{
    // reset timer and state
    waitTime = 20 * (GEM_ROWS * GEM_COLUMNS);
    state = GameState::Loading;
    // generate field
    playField.generateGems();
    // play sound
    musicStart->play();
    // reset score
    playField.setScore(0);
}

void Game::update()
{
    prevTime = static_cast<double>(SDL_GetTicks());
    
	while(!quitSignalReceived)
    {
        double deltaTime = static_cast<double>(SDL_GetTicks()) - prevTime;
        prevTime = static_cast<double>(SDL_GetTicks());
        
        // wait while field appears
        if(waitTime > 0.0f)
        {
            waitTime -= deltaTime;
        } else if(state == GameState::Loading) {
            state = GameState::Playing;
            playField.startTimer();
        }
        
        // end game when timer is ended
        if(state == GameState::Playing && playField.getTimer() <= 0.0f)
        {
            state = GameState::Ended;
            playField.reset();
            musicGameOver->play();
        }
        
        if(!engine.update(inputs))
        {
            quitSignalReceived = true;
        }
        
        // input signals
        while(inputs.size() > 0)
        {
            int event = inputs.front();
            switch(event)
            {
                case InputEvent::Quit:
                    quitSignalReceived = true;
                    break;
                    
                case InputEvent::Restart:
                    playField.reset();
                    restart();
                    break;
                    
                case InputEvent::Pause:
                    if(state == GameState::Paused)
                        state = GameState::Playing;
                    else if(state == GameState::Playing)
                        state = GameState::Paused;
                    break;
                    
                case InputEvent::MouseClickDown:
                    if(state == GameState::Playing)
                    {
                        prevGemClick = playField.getGemPosByMouseCoordinates(engine.getMousePositionX(), engine.getMousePositionY());
                        playField.onGemClick(prevGemClick);
                    }
                    break;
                    
                case InputEvent::MouseClickUp:
                    if(state == GameState::Playing)
                    {
                        int pos = playField.getGemPosByMouseCoordinates(engine.getMousePositionX(), engine.getMousePositionY());
                        if(prevGemClick != pos)
                        {
                            prevGemClick = pos;
                            playField.onGemClick(prevGemClick);
                        }
                    }
                    break;
                    
                default:
                    break;
            }
            
            inputs.pop_front();
        }
        
        playField.update(deltaTime);
        
        scoreText.setText(TEXT_SCORE + std::to_string(playField.getScore()));
        
        int yourTime = static_cast<int>(playField.getTimer() / 1000.0f);
        int minutes = yourTime / 60;
        if(yourTime > 0)
        {
            yourTime = yourTime % 60;
        }
        std::string addditionalString = TEXT_TIME + std::to_string(minutes) + ":";
        if(yourTime < 10)
            addditionalString += "0";
        timerText.setText(addditionalString + std::to_string(yourTime));

        render();
        
        SDL_Delay(10);
    }
}

void Game::render() const
{
    engine.renderStart();
    
    background.render(engine.getRenderer());
    if(state == GameState::Inited)
    {
        startText.render(engine.getRenderer());
    }
    if(state == GameState::Ended)
    {
        restartText.render(engine.getRenderer());
        scoreText.render(engine.getRenderer());
    }
    if(state == GameState::Playing || state == GameState::Paused)
    {
        scoreText.render(engine.getRenderer());
        timerText.render(engine.getRenderer());
    }
    playField.render(engine.getRenderer());
    
    engine.renderStop();
}

void Game::loadTextures()
{
    std::shared_ptr<Texture> backgroundTexture = engine.loadTexture(IMAGE_BACKGROUND);
    std::shared_ptr<Texture> blueGemTexture = engine.loadTexture(IMAGE_BLUE_GEM);
    std::shared_ptr<Texture> redGemTexture = engine.loadTexture(IMAGE_RED_GEM);
    std::shared_ptr<Texture> yellowGemTexture = engine.loadTexture(IMAGE_YELLOW_GEM);
    std::shared_ptr<Texture> purpleGemTexture = engine.loadTexture(IMAGE_PURPLE_GEM);
    std::shared_ptr<Texture> greenGemTexture = engine.loadTexture(IMAGE_GREEN_GEM);
    
    std::vector<std::shared_ptr<Texture> > textures;
    textures.push_back(blueGemTexture);
    textures.push_back(redGemTexture);
    textures.push_back(yellowGemTexture);
    textures.push_back(purpleGemTexture);
    textures.push_back(greenGemTexture);
    
    playField.setTextures(textures);
    
    background = TextureEntity(backgroundTexture);
}

void Game::loadFonts()
{
    font = engine.loadFont(FONT_MAIN);
    
    scoreText = Text(font, "");
    scoreText.setPosition(25, 10);
    
    startText = Text(font, TEXT_START);
    startText.setPosition(WINDOW_WIDTH / 3.1f, WINDOW_HEIGHT / 2.3f);
    
    restartText = Text(font, TEXT_RESTART);
    restartText.setPosition(WINDOW_WIDTH / 3.2f, WINDOW_HEIGHT / 2.3f);
    
    timerText = Text(font, " ");
    timerText.setPosition(WINDOW_WIDTH - 175, 10);
}

void Game::loadAudio()
{
    std::vector< std::shared_ptr<Sound> > soundsCollapse;
    soundsCollapse.push_back(engine.loadSound(SOUND_COLLAPSE_1));
    soundsCollapse.push_back(engine.loadSound(SOUND_COLLAPSE_2));
    soundsCollapse.push_back(engine.loadSound(SOUND_COLLAPSE_3));
    playField.setCollapseSounds(soundsCollapse);

    musicGameOver = engine.loadMusic(MUSIC_GAMEOVER);
    musicStart = engine.loadMusic(MUSIC_START);
    musicStart->setVolume(60);
}

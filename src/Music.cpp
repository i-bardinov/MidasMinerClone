#include "Music.h"
#include <iostream>

Music::Music()
{
    
}

Music::Music(Mix_Music* _sound)
{
    music.reset(_sound);
}

void Music::play() const
{
    if(!music)
        return;
    
    Mix_VolumeMusic(volume);
    // play sound
    if(Mix_PlayMusic(music.get(), 1) == -1)
    {
        std::cout << "Mix_PlayMusic Error: " << Mix_GetError() << std::endl;
        return;
    }
}

void Music::setVolume(Uint8 _volume)
{
    this->volume = _volume;
}

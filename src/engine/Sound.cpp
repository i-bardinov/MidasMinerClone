#include "Sound.h"
#include <iostream>

Sound::Sound()
{
    
}

Sound::Sound(Mix_Chunk* _sound)
{
    sound.reset(_sound);
}

void Sound::play() const
{
    if(!sound)
        return;
    
    // play sound
    if(Mix_PlayChannel(-1, sound.get(), 0) == -1)
    {
        std::cout << "Mix_PlayChannel Error: " << Mix_GetError() << std::endl;
        return;
    }
}

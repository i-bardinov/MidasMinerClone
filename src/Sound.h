#ifndef SOUND_H
#define SOUND_H

#include <SDL_mixer.h>
#include <memory>

class Sound
{
public:
    Sound();
    Sound(Mix_Chunk *sound);
    
    // play sound method
    void play() const;
    
private:
    std::unique_ptr<Mix_Chunk, void(*)(Mix_Chunk *)> sound = std::unique_ptr<Mix_Chunk, void (*)(Mix_Chunk *)>(nullptr, Mix_FreeChunk);
};

#endif

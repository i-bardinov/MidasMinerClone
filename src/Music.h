#ifndef MUSIC_H
#define MUSIC_H

#include <SDL_mixer.h>
#include <memory>

class Music
{
public:
    Music();
    Music(Mix_Music *sound);
    
    // play music method
    void play() const;
    
    void setVolume(Uint8 volume);
    
private:
    std::unique_ptr<Mix_Music, void(*)(Mix_Music *)> music = std::unique_ptr<Mix_Music, void (*)(Mix_Music *)>(nullptr, Mix_FreeMusic);
    Uint8 volume = 128;
};

#endif

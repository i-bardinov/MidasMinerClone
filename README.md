It is a Midas Miner clone. It can be build with cmake and SDL2.
It uses these libraries:
- SDL2;
- SDL_image;
- SDL_ttf;
- SDL_mixer;
Use 'brew install sdl2 sdl2_image sdl2_mixer sdl2_ttf' to install these libraries.

It uses CMake as a build system. Run following commands from terminal in that folder:
- 'mkdir build'
- 'cd build'
- 'cmake ..'
- 'cmake --build .'
- '../bin/MidasMinerClone'

Game consist of Game.cpp as a controller part and another different flexible parts with different settings.
Assets are in bin/assets folder.
MacOS executable in bin folder.

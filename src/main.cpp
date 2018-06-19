#include <iostream>

#include "Game.h"

int main(int argc, char* argv[])
{
	Game game;
    
    // try to init game
	if(!game.init())
    {
        std::cout << "There was error when try to init game!" << std::endl;
		return 1;
    }
    
    // update game (it's a loop, break on error or exit signal)
	game.update();

	return 0;
}

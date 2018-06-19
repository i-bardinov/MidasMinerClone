#ifndef CONST_H
#define CONST_H

#include <string>

const int WINDOW_WIDTH = 755;
const int WINDOW_HEIGHT = 600;

const double GAME_TIMER = 60000.0f;
const double ADDITIONAL_TIMER = 2000.0f;

const std::string ASSETS_PATH = "./assets/";

const std::string IMAGE_BACKGROUND  = "Background.jpg";
const std::string IMAGE_RED_GEM     = "Red.png";
const std::string IMAGE_BLUE_GEM    = "Blue.png";
const std::string IMAGE_GREEN_GEM   = "Green.png";
const std::string IMAGE_PURPLE_GEM  = "Purple.png";
const std::string IMAGE_YELLOW_GEM  = "Yellow.png";
const std::string FONT_MAIN         = "font.ttf";

const std::string MUSIC_START       = "start.ogg";
const std::string MUSIC_GAMEOVER    = "gameover.ogg";

const std::string SOUND_COLLAPSE_1  = "collapse1.wav";
const std::string SOUND_COLLAPSE_2  = "collapse2.wav";
const std::string SOUND_COLLAPSE_3  = "collapse3.wav";

const std::string TEXT_SCORE        = "Score: ";
const std::string TEXT_TIME         = "Time: ";
const std::string TEXT_START        = "Press SPACE to start!";
const std::string TEXT_SCORE_FINISH = "Your score: ";
const std::string TEXT_RESTART      = "Press SPACE to restart!";

const int GEM_ROWS                  = 8;
const int GEM_COLUMNS               = 8;
const int GEM_SIZE                  = 52;
const double GEM_COLLAPSE_TIME_MS   = 200.0f;

const int SCORE_PER_GEM             = 50;
const int SCORE_REMOVING            = 10;
const double SCORE_TIME_REMOVING_MS = 5000.0f;

const int FIELD_START_X             = WINDOW_WIDTH / 2 - GEM_SIZE * GEM_COLUMNS / 2;
const int FIELD_START_Y             = WINDOW_HEIGHT / 2 - GEM_SIZE * GEM_ROWS / 2;
const int FIELD_END_X               = FIELD_START_X + GEM_SIZE * GEM_ROWS;
const int FIELD_END_Y               = FIELD_START_Y + GEM_SIZE * GEM_COLUMNS;

#endif

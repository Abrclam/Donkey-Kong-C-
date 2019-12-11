#pragma once
//constant variables that don't change
const float FPS = 60;
const int SCREEN_W = 800;
const int SCREEN_H = 800;
const int BARREL_SIZE = 20;
const int PLATFORM_WIDTH = 80;
const int PLATFORM_HEIGHT = 30;
const int LADDER_WIDTH = 55;
const int LADDER_HEIGHT = 305;


//changing height for ladder
//int LADDER_HEIGHT = 40;

//enumerations to help remember what numbers represent which directions
enum MYKEYS{KEY_UP,KEY_DOWN,KEY_LEFT,KEY_RIGHT, KEY_SPACE};
enum DIRECTIONS{UP,DOWN,LEFT,RIGHT,SPACE};
enum ITEM_IDS{BARREL,PLATFORM,PLAYER, LADDER};

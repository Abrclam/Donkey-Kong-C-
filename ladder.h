#pragma once
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <vector>
using namespace std;//needed for vectors
#include "GameObject.h"

class ladder :public gameObject {

public:
	ladder(int x, int y, ALLEGRO_BITMAP* img);
	void draw();

};

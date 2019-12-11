#include "Ladder.h"
#include "globals.h"

ladder::ladder(int x, int y, ALLEGRO_BITMAP* img) {
	xPos = x;
	yPos = y;
	pic = img;
	ID = LADDER;
}
void ladder::draw() {
	al_draw_bitmap(pic, xPos, yPos, NULL);
}

#include "player.h"
#include "globals.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <iostream>
using namespace std;
player::player() {//constructor
	//position of player
	xPos = 100;
	yPos = SCREEN_H - 70;

	//player velocity
	xVel = 0;
	yVel = 0;

	isOnGround = false;
	CanJump = false;
	OnLadder = false;
	ID = PLAYER;
}

void player::moveLeft() { xVel--; }


void player::climb() { 
	if (OnLadder) {
		yVel--;
		cout << "climbin!";
	}
}


void player::moveRight() { xVel++;  }

void player::Jump() {
	if (CanJump && !OnLadder) {
		yVel -= 12;
		cout << "we do be jumping tho ";
	}
}

void player::draw() {
	al_draw_filled_rectangle(xPos, yPos, xPos + 30, yPos + 30, al_map_rgb(160, 90, 60));
}

void player::move(vector<gameObject*>stuff) {
	cout << "flag 0: onladder is " << OnLadder << endl;
	//cout << "onladder is "<<OnLadder;
	//cout << "canjump is " << CanJump << endl;
	//deal with platform collision
	vector<gameObject*>::iterator iter;
	int x;
	int y;

	//go thru vector, find platforms, get their positions, check if we've (player) has collided
	for (iter = stuff.begin(); iter != stuff.end(); iter++) {
		if ((*iter)->getID() == PLATFORM) {//only deal with platform collision here
			x = (*iter)->getX();
			y = (*iter)->getY();

			if (VerticalCollision(xPos, yPos, 32, 32, (*iter)->getX(), (*iter)->getY(), PLATFORM_WIDTH, PLATFORM_HEIGHT, yVel) == 2) {
				yVel = -1.0;
				isOnGround = true;
			}
			if (VerticalCollision(xPos, yPos, 32, 32, (*iter)->getX(), (*iter)->getY(), PLATFORM_WIDTH, PLATFORM_HEIGHT, yVel) == 1) {
				yVel = 0.0;
				isOnGround = true;
			}
		}
	}

	//go thru vector, find ladder, get their positions, check if we've (player) has collided
	for (iter = stuff.begin(); iter != stuff.end(); iter++) {
		if ((*iter)->getID() == LADDER) {//only deal with ladder collision here
			x = (*iter)->getX();
			y = (*iter)->getY();
			//cout << "checking collision with " << (*iter)->getX() << " "<<(*iter)->getY() << endl;
			if (LadderCollision(xPos, yPos, 32, 32, (*iter)->getX(), (*iter)->getY(), LADDER_WIDTH, LADDER_HEIGHT) == 1) {
				//yVel = -1.0;
				//isOnGround = true;
				OnLadder = true;
				//cout << "I'm jus vibin on tha ladder." << endl;
				cout << "flag 1: onladder is " << OnLadder << endl;
				CanJump = false;
				break;
			}
			else {
				OnLadder = false; //added by mo
				cout << "set onladder to false!" << endl << endl << endl;
			}
	
			cout << "flag 2: onladder is " << OnLadder << endl;
		}
	}

	cout << "flag 3: onladder is " << OnLadder << endl;
	//update player position by adding velocity
	xPos += xVel;
	yPos += yVel;

	//FRICTION 
	xVel *= .7; //smaller = more fric

	//GRAVITY
	if (isOnGround == false) {
		yVel += 1;//fall speed
		CanJump = false;//turn off flying / double jump
	}
	else {
		yVel = 0;//stop falling when grounded
		CanJump = true;
	}

	//check if falling for gravity
	if (yPos + 30 > SCREEN_H)
		isOnGround = true;
	else
		isOnGround = false;

	//set terminal velocity (don't fall too fast)
	if (yVel > 5)
		yVel = 5;

	//bounds checking (no offscreen)
	if (xPos < 0)
		xPos = 0;
	if (xPos + 32 > SCREEN_W)
		xPos = SCREEN_W - 32;

	cout << "flag 4: onladder is " << OnLadder << endl;
}

//collision function that differs based on how close your feet are to the ground that lets you walk up stairs
int player::VerticalCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2, int ydir) {

	if ((ydir >= 0) && //mo changed = to ==
		(x1 + w1 > x2) &&
		(x1 < x2 + w2) &&
		(y1 + h1 + 4 > y2) &&//4 means you're close to ground
		(y1 < y2)) {
		return 2;
	}
	else if ((ydir >= 0) &&
		(x1 + w1 > x2) &&
		(x1 < x2 + w2) &&
		(y1 + h1 + 6 > y2) &&
		(y1 < y2)) {
		return 1;
	}
	else
		return false;
}

int player::LadderCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	if ((x1 + w1 > x2) &&//have we hit from the left?
		(x1 < x2 + w2) && //have we hit from the right?
		(y1 + h1 > y2) && //hit from above
		(y1 < y2 + h2))
		return 1;
	else
		return 0;


}

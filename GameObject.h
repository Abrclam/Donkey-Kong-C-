#pragma once
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <vector>
using namespace std;

class gameObject {
private: //only gameObjects can access these

protected: //only child classes can acccess
	int xPos;
	int yPos;
	int ID;
	bool isOnGround;
	bool OnLadder;
	ALLEGRO_BITMAP* pic;

public: //all parts of program can access these
	//regular functions
	int getX();
	int getY();
	int getID();
	bool getLadder();
	//virtual functions
	virtual void move(vector<gameObject*>stuff);
	virtual void draw();

};

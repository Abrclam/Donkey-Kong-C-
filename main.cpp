//allegro headers
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

//headers we write
#include "platform.h"
#include "Barrel.h"
#include "globals.h"
#include "player.h"
#include "GameObject.h"
#include "Ladder.h"

//standard c++ libraries
#include <iostream>
#include <vector>
using namespace std;


int main() {
	//set up allegro///////////////////////////
	al_init();
	al_install_keyboard();
	al_init_primitives_addon();
	al_init_image_addon();
	cout << "flag1" << endl;
	//set up game screen, event queue and timer/////////////////////////
	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_W, SCREEN_H);
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
	ALLEGRO_BITMAP* picture = al_load_bitmap("platform.png");
	ALLEGRO_BITMAP* picture2 = al_load_bitmap("barrel.png");
	ALLEGRO_BITMAP* picture3 = al_load_bitmap("ladder.png");
	

	al_convert_mask_to_alpha(picture2, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(picture3, al_map_rgb(255, 255, 255));
	al_start_timer(timer);
	cout << "flag1.5" << endl;
	//game variables
	bool key[4] = { false,false,false,false };//holds clicks
	bool redraw = true; //variable needed for render section
	bool doexit = false; //handles game loop

	//tell event queue what to look for
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	cout << "flag2" << endl;
	//create all the game objects

	//vector to hold all the game objects
	vector<gameObject*>objects;
	vector<gameObject*>::iterator iter;

	//PLATFORMS///////////////////
	//create bottom row of platforms
	for (int i = 0; i < 5; i++) {
		platform* newPlat = new platform(i * PLATFORM_WIDTH, SCREEN_H - PLATFORM_HEIGHT, picture); //left side is flat
		objects.push_back(newPlat);
	}
	for (int i = 0; i < 5; i++) {
		platform *newPlat = new platform(i * PLATFORM_WIDTH+ SCREEN_W /2, (SCREEN_H- PLATFORM_HEIGHT)-i*5,picture);
		objects.push_back(newPlat);
	}
	//second row
	for (int i = 0; i < 8; i++) {
		platform* newPlat = new platform(i * PLATFORM_WIDTH ,600 +i*5, picture);
		objects.push_back(newPlat);
	}
	//middle row
	for (int i = 0; i < 7; i++) {
		platform* newPlat = new platform(i * PLATFORM_WIDTH + SCREEN_W / 2-100, (SCREEN_H - PLATFORM_HEIGHT-300) - i * 5, picture);
		objects.push_back(newPlat);
	}
	//top row
	for (int i = 0; i < 8; i++) {
		platform* newPlat = new platform(i * PLATFORM_WIDTH, 300 + i * 5, picture);
		objects.push_back(newPlat);
	}


	//ladder
	for (int i = 1; i > 0; i--) {
		ladder* newLad = new ladder(i * 380,(600- i * 10), picture3);
		objects.push_back(newLad);
	}

	//barrels/////////////////////////////////
	barrel* b1 = new barrel(100, 100, picture2);
	barrel* b2 = new barrel(rand() % 500 - 1000, rand() % 500 - 1000, picture2);
	barrel* b3 = new barrel(rand() % 500 - 1000, rand() % 500 - 1000, picture2);
	barrel* b4 = new barrel(rand() % 500 - 1000, rand() % 500 - 1000, picture2);
	barrel* b5 = new barrel(rand() % 500 - 1000, rand() % 500 - 1000, picture2);
	barrel* b6 = new barrel(rand() % 500 - 1000, rand() % 500 - 1000, picture2);
	barrel* b7 = new barrel(rand() % 500 - 1000, rand() % 500 - 1000, picture2);
	barrel* b8 = new barrel(rand() % 500 - 1000, rand() % 500 - 1000, picture2);
	objects.push_back(b1);
	objects.push_back(b2);
	objects.push_back(b3);
	objects.push_back(b4);
	objects.push_back(b5);
	objects.push_back(b6);
	objects.push_back(b7);
	objects.push_back(b8);

	//player//////////////////////
	player* p1 = new player();
	objects.push_back(p1);
	while (!doexit) {//game loop//////////////////
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//timer (physics) section/////////////
		if (ev.type == ALLEGRO_EVENT_TIMER) {

			//keyboard
			if (key[KEY_UP] && p1->getLadder() == false) {
				p1->Jump();
			}
			if (key[KEY_LEFT]) {
				p1->moveLeft();
			}
			if (key[KEY_RIGHT]) {
				p1->moveRight();
			}
			if (key[KEY_UP] &&  p1->getLadder() == true) {
				p1->climb();
			}
			//move ALL game objects
			for (iter = objects.begin(); iter != objects.end(); iter++) {
				(*iter)->move(objects);
			}
			redraw = true;
		}
		//keyboard and screen sections////////////////
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;

			case ALLEGRO_KEY_SPACE:
				key[KEY_SPACE] = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;

			case ALLEGRO_KEY_SPACE:
				key[KEY_SPACE] = false;
				break;

			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
		}
		//render section/////////////////////
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));//wipe screen black

			//draw objects
			for (iter = objects.begin(); iter != objects.end(); iter++) {
				(*iter)->draw();
			}
			al_flip_display(); //flip everything from memory onto the screen

		}//end render

	}//end game loop
	//clean up memory
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	return 0;
}//end main

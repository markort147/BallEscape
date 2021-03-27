//============================================================================
// Name        : SDLBasic.cpp
// Author      : markort147
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <sstream>
#include "Screen.h"
#include "Ball.h"
using namespace std;
using namespace markort147;

bool ballCollides(Ball ball1, Ball ball2, Screen screen);


int main(int argc, char *argv[]) {

	Screen screen(Screen::SCREEN_SIZE_800_600);

	if (screen.init() == false) {
		cout << "Error initializing SDL." << endl;
		return 1;
	}

	srand(time(NULL));

	Ball ball(0., 0., 10, false, 0., screen.getScreenRatio());
	Ball bonus1(7, false, 0., screen.getScreenRatio());
	Ball bonus2(7, false, 0., screen.getScreenRatio());
	Ball bonus3(7, false, 0., screen.getScreenRatio());
	Ball malus1(7, false, 0., screen.getScreenRatio());
	Ball malus2(7, false, 0., screen.getScreenRatio());
	Ball malus3(7, false, 0., screen.getScreenRatio());

	int elapsed;
	Uint8 score = 0;
//	Uint8 oldScore = 0;

	bool quit = false;
	//	Uint8 *screenObjects = new Uint8[Screen::SCREEN_WIDTH * Screen::SCREEN_HEIGHT]();

	cout << "Press the arrows to move the ball" << endl;
	cout << "Press the space-bar to stop or start the ball" << endl;
	cout << "Press 1 to set screen size 400x300" << endl;
	cout << "Press 2 to set screen size 800x600" << endl;
	cout << "Press 3 to set screen size 1200x900" << endl;

	int lastBonusUpdateTime = SDL_GetTicks();

	while (!quit) {

		elapsed = SDL_GetTicks();

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			Uint32 eventType = event.type;
			if (eventType == SDL_KEYDOWN) {
				switch(event.key.keysym.scancode) {
				case Ball::MOVE_LEFT:
				case Ball::MOVE_RIGHT:
				case Ball::MOVE_UP:
				case Ball::MOVE_DOWN:
					ball.setMoving(true);
					ball.setDirection(event.key.keysym.scancode);
					break;
				case SDL_SCANCODE_SPACE:
					ball.setMoving(!ball.isMoving());
//					cout << "pressed space" << endl;
					break;;
				case SDL_SCANCODE_1:
					screen.resize(Screen::SCREEN_SIZE_400_300);
					break;
				case SDL_SCANCODE_2:
					screen.resize(Screen::SCREEN_SIZE_800_600);
					break;
				case SDL_SCANCODE_3:
					screen.resize(Screen::SCREEN_SIZE_1200_900);
					break;
				default:
					break;
				}
			} else if (eventType == SDL_QUIT) {
				ball.setMoving(false);
				quit = true;
			}
//			else if (eventType == SDL_WINDOWEVENT) {
//				if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
//					screen.resize(event.window.data1, event.window.data2);
//					ball.resize(screen.getScreenRatio());
//					bonus1.resize(screen.getScreenRatio());
//					bonus2.resize(screen.getScreenRatio());
//					bonus3.resize(screen.getScreenRatio());
//					malus1.resize(screen.getScreenRatio());
//					malus2.resize(screen.getScreenRatio());
//					malus3.resize(screen.getScreenRatio());
//				}
//			}
		}

		screen.clear();
		//		screen.boxBlur(score);
		ball.update(elapsed, score);

		//		cout << "x=" << x << endl;
		//		cout << "y=" << y << endl;

		if (bonus1.m_exist && ballCollides(ball, bonus1, screen)) {
			//			cout << "Got Bonus!" << endl;
			if (score != 255)
				score++;
			bonus1.m_exist = false;
		}
		if (bonus2.m_exist && ballCollides(ball, bonus2, screen)) {
			//			cout << "Got Bonus!" << endl;
			if (score != 255)
				score++;
			bonus2.m_exist = false;
		}
		if (bonus3.m_exist && ballCollides(ball, bonus3, screen)) {
			//			cout << "Got Bonus!" << endl;
			if (score != 255)
				score++;
			bonus3.m_exist = false;
		}
		if (malus1.m_exist && ballCollides(ball, malus1, screen)) {
			//			cout << "Got Malus!" << endl;
			if (score != 0)
				score--;
			malus1.m_exist = false;
		}
		if (malus2.m_exist && ballCollides(ball, malus2, screen)) {
			//			cout << "Got Malus!" << endl;
			if (score != 0)
				score--;
			malus2.m_exist = false;
		}
		if (malus3.m_exist && ballCollides(ball, malus3, screen)) {
			//			cout << "Got Malus!" << endl;
			if (score != 0)
				score--;
			malus3.m_exist = false;
		}

		if (elapsed - lastBonusUpdateTime >= 3000 - 3000*score*.01) {
			bonus1.m_x = bonus1.randPosX();
			bonus1.m_y = bonus1.randPosY();
			bonus2.m_x = bonus2.randPosX();
			bonus2.m_y = bonus2.randPosY();
			bonus3.m_x = bonus3.randPosX();
			bonus3.m_y = bonus3.randPosY();
			malus1.m_x = malus1.randPosX();
			malus1.m_y = malus1.randPosY();
			malus2.m_x = malus2.randPosX();
			malus2.m_y = malus2.randPosY();
			malus3.m_x = malus3.randPosX();
			malus3.m_y = malus3.randPosY();
			bonus1.m_exist = true;
			bonus2.m_exist = true;
			bonus3.m_exist = true;
			malus1.m_exist = true;
			malus2.m_exist = true;
			malus3.m_exist = true;
			lastBonusUpdateTime = SDL_GetTicks();
			//			cout << "bonus! (x,y)=" << bonus1.m_x << "," << bonus1.m_y << endl;
		}

		if (bonus1.m_exist)
			screen.drawSphere(bonus1, 0, 255, 255);
		if (bonus2.m_exist)
			screen.drawSphere(bonus2, 0, 255, 255);
		if (bonus3.m_exist)
			screen.drawSphere(bonus3, 0, 255, 255);
		if (malus1.m_exist)
			screen.drawSphere(malus1, 255, 0, 0);
		if (malus2.m_exist)
			screen.drawSphere(malus2, 255, 0, 0);
		if (malus3.m_exist)
			screen.drawSphere(malus3, 255, 0, 0);

		screen.drawSphere(ball, 248, 255, 17);

		//update screen
//		char *scoreC = itoa(score);
		stringstream ss;
		ss << "Score: " << (int) score;
		string text = ss.str();
		screen.update(text);

//		if (oldScore != score) {
//			oldScore = score;
//			cout << "Score: " << (int) score << endl;
//		}

	}
	screen.close();

	cout << "Bye!" << endl;

	return 0;
}

bool ballCollides(Ball ball1, Ball ball2, Screen screen) {
	double halfScreenWidth = screen.getScreenWidth() / 2;
	double halfScreenHeight = screen.getScreenHeight() / 2;
	double x1 = (ball1.m_x + 1) * halfScreenWidth;
	double y1 = ball1.m_y * halfScreenWidth + halfScreenHeight;
	double x2 = (ball2.m_x + 1) * halfScreenWidth;
	double y2 = ball2.m_y * halfScreenWidth + halfScreenHeight;
	int radius1 = ball1.m_radius;
	int radius2 = ball2.m_radius;
	bool output = false;

	if ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)
			<= (radius1 + radius2) * (radius1 + radius2)) {
		output = true;
	}

	return output;

}

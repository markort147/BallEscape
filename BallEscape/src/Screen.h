/*
 * Screen.h
 *
 *  Created on: 13 mar 2021
 *      Author: Marco
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <string>
#include <stdlib.h>
#include <cstring> //for memset
#include "Ball.h"

using namespace std;

namespace markort147 {

class Screen {
public:
	const static int SCREEN_WIDTH = 800;
	const static int SCREEN_HEIGHT = 600;
	const static Uint32 RGBA888_BLACK = 0x000000FF;
	const static Uint32 RGBA888_WHITE = 0xFFFFFFFF;
	const static Uint8 OBJ_BALL = 1;
	const static Uint8 OBJ_BONUS = 2;
	const static Uint8 OBJ_MALUS = 3;
private:
	float screenRatio;
	int screenWidth;
	int screenHeight;
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Texture *m_texture;
	Uint32 *m_buffer;
	Uint32 *m_buffer2;
//	Uint8 *m_screenObjects;
public:
	Screen();
	bool init();
	bool processEvents();
	void update(string);
	void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
	void close();
	void clear();
	void boxBlur(Uint8);
	void resize(int newWidth, int newHeight);
	void drawSphere(Ball, Uint8, Uint8, Uint8);

	void setScreenHeight(int screenHeight) {
		this->screenHeight = screenHeight;
	}

	float getScreenRatio() const {
		return screenRatio;
	}

	void setScreenRatio(float screenRatio) {
		this->screenRatio = screenRatio;
	}

	void setScreenWidth(int screenWidth) {
		this->screenWidth = screenWidth;
	}

	int getScreenHeight() const {
		return screenHeight;
	}

	int getScreenWidth() const {
		return screenWidth;
	}
private:
	void drawText(string);
};

} /* namespace caveofprogramming */

#endif /* SCREEN_H_ */

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
//	const static int SCREEN_WIDTH_1 = 400;
//	const static int SCREEN_HEIGHT_1 = 300;
//	const static int SCREEN_WIDTH_2 = 800;
//	const static int SCREEN_HEIGHT_2 = 600;
//	const static int SCREEN_WIDTH_3 = 1200;
//	const static int SCREEN_HEIGHT_3 = 900;
	const static Uint8 SCREEN_SIZE_400_300 = 1;
	const static Uint8 SCREEN_SIZE_800_600 = 2;
	const static Uint8 SCREEN_SIZE_1200_900 = 3;
	const static Uint32 RGBA888_BLACK = 0x000000FF;
	const static Uint32 RGBA888_WHITE = 0xFFFFFFFF;
	const static Uint8 OBJ_BALL = 1;
	const static Uint8 OBJ_BONUS = 2;
	const static Uint8 OBJ_MALUS = 3;
private:
	Uint32 *m_buffer_400_300;
	Uint32 *m_buffer_800_600;
	Uint32 *m_buffer_1200_900;
	float screenRatio;
	int screenWidth;
	int screenHeight;
	Uint8 screenSize;
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Texture *m_texture;
	Uint32 *m_buffer;
	Uint32 *m_buffer2;
	TTF_Font *m_ttfFont;
//	Uint8 *m_screenObjects;
public:
	Screen(Uint8 screenSize);
	bool init();
	bool processEvents();
	void update(string);
	void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
	void close();
	void clear();
//	void boxBlur(Uint8);
	void resize(Uint8 screenSize);
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

} /* namespace markort147 */

#endif /* SCREEN_H_ */

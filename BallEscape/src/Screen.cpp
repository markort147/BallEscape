/*
 * Screen.cpp
 *
 *  Created on: 13 mar 2021
 *      Author: Marco
 */

#include "Screen.h"
#include <iostream>

using namespace std;

namespace markort147 {

Screen::Screen() : m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer(NULL), m_buffer2(NULL), m_ttfFont(NULL) {
	screenWidth = SCREEN_WIDTH;
	screenHeight = SCREEN_HEIGHT;
	screenRatio = (float) screenWidth / SCREEN_HEIGHT;
}

void Screen::resize(int newWidth, int newHeight) {
	setScreenWidth(newWidth);
	setScreenHeight(newHeight);
	setScreenRatio((float) newWidth / newHeight);
}

bool Screen::init() {

	if(TTF_Init() < 0) {
		return false;
	}

	m_ttfFont = TTF_OpenFont("./font/arial.ttf", 50); //this opens a font style and sets a size

	if(m_ttfFont == NULL) {
		cout << "font null" << endl;
	}

//	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//		return false;
//	}
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return false;
	}

	m_window = SDL_CreateWindow("WINDOW 1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Screen::SCREEN_WIDTH, Screen::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	//	m_window = SDL_CreateWindow("WINDOW 1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Screen::SCREEN_WIDTH, Screen::SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STATIC, Screen::SCREEN_WIDTH,
			Screen::SCREEN_HEIGHT);

	if (m_window == NULL) {
		SDL_Quit();
		return false;
	}
	if (m_renderer == NULL) {
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	if (m_texture == NULL) {
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	m_buffer = new Uint32[Screen::SCREEN_WIDTH * Screen::SCREEN_HEIGHT];
	m_buffer2 = new Uint32[Screen::SCREEN_WIDTH * Screen::SCREEN_HEIGHT];
	if (m_buffer == NULL) {
		SDL_DestroyTexture(m_texture);
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}
	if (m_buffer2 == NULL) {
		delete[] m_buffer;
		SDL_DestroyTexture(m_texture);
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}


	//	m_screenObjects = new Uint8[Screen::SCREEN_WIDTH * Screen::SCREEN_HEIGHT]();

	this->clear();

	return true;
}

void Screen::update(string text) {
	SDL_UpdateTexture(m_texture, NULL, m_buffer, Screen::SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
	drawText(text);
	SDL_RenderPresent(m_renderer);
}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
		return;
	}

	Uint32 color = 0;

	color += red;
	color <<= 8;
	color += green;
	color <<= 8;
	color += blue;
	color <<= 8;
	color += 0xFF; //alpha

	m_buffer[y * Screen::SCREEN_WIDTH + x] = color;
}

bool Screen::processEvents() {
	SDL_Event event;
	Uint32 eventType;
	while (SDL_PollEvent(&event)) {
		eventType = event.type;
		if (eventType == SDL_QUIT) {
			return true;
		}
	}
	return false;
}

void Screen::close() {
	delete[] m_buffer;
	delete[] m_buffer2;
	SDL_DestroyTexture(m_texture);
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
	TTF_Quit();
}

void Screen::clear() {
	//	memset(m_buffer, 0x000000FF,
	//			Screen::SCREEN_WIDTH * Screen::SCREEN_HEIGHT * sizeof(Uint32));
	//	memset(m_buffer2, Screen::RGBA888_BLACK,
	//			Screen::SCREEN_WIDTH * Screen::SCREEN_HEIGHT * sizeof(Uint32));
	for (int i = 0; i < Screen::SCREEN_HEIGHT * Screen::SCREEN_WIDTH; i++) {
		m_buffer[i] = Screen::RGBA888_BLACK;
		m_buffer2[i] = Screen::RGBA888_BLACK;
	}
}

void Screen::boxBlur(Uint8 score) {
	//Swap the buffers
	Uint32 *temp_buffer = m_buffer;
	m_buffer = m_buffer2;
	m_buffer2 = temp_buffer;

	for (int y = 0; y < SCREEN_HEIGHT; y++) {
		for (int x = 0; x < SCREEN_WIDTH; x++) {

			int redTotal = 0;
			int greenTotal = 0;
			int blueTotal = 0;

			for (int row = -1; row <= 1; row++) {
				for (int col = -1; col <= 1; col++) {
					int curX = x + col;
					int curY = y + row;

					if (curX >= 0 && curX < SCREEN_WIDTH && curY >= 0
							&& curY < SCREEN_HEIGHT) {
						Uint32 color = m_buffer2[curY * SCREEN_WIDTH + curX];
						Uint8 red = (color & 0xFF000000) >> 24;
						Uint8 green = (color & 0x00FF0000) >> 16;
						Uint8 blue = (color & 0x0000FF00) >> 8;

						redTotal += red;
						greenTotal += green;
						blueTotal += blue;
					}
				}
			}

			int divisor = 9;
			//			divisor = 20 - score/2.;
			//			if(divisor < 12) divisor = 12;
			Uint8 red = redTotal / divisor;
			Uint8 green = greenTotal / divisor;
			Uint8 blue = blueTotal / divisor;

			setPixel(x, y, red, green, blue);

		}
	}

}

void Screen::drawSphere(Ball ball, Uint8 red, Uint8 green, Uint8 blue) {
	double HALF_SCREEN_WIDTH = screenWidth / 2.;
	//	double HALF_SCREEN_HEIGHT = SCREEN_HEIGHT / 2;
	int x = (ball.m_x + 1) * HALF_SCREEN_WIDTH;
	int y = (ball.m_y + (double) screenHeight / screenWidth)
					* HALF_SCREEN_WIDTH;
	int radius = ball.m_radius;

	for (int dx = -radius; dx <= radius; dx++) {
		for (int dy = -radius; dy <= radius; dy++) {
			int final_x = x + dx;
			int final_y = y + dy;
			if (dx * dx + dy * dy <= radius * radius)
				setPixel(final_x, final_y, red, green, blue);
		}
	}
}

void Screen::drawText(string text) {

	SDL_Color white = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

	const char * c = text.c_str();

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(m_ttfFont, c, white); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	SDL_Texture* message = SDL_CreateTextureFromSurface(m_renderer, surfaceMessage); //now you can convert it into a texture

	SDL_Rect messageRect; //create a rect
	messageRect.x = 0;  //controls the rect's x coordinate
	messageRect.y = 0; // controls the rect's y coordinte
	messageRect.w = 60; // controls the width of the rect
	messageRect.h = 25; // controls the height of the rect

	//Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understand

	//Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

	SDL_RenderCopy(m_renderer, message, NULL, &messageRect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
}

} /* namespace caveofprogramming */


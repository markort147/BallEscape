/*
 * Ball.h
 *
 *  Created on: 15 mar 2021
 *      Author: Marco
 */

#ifndef BALL_H_
#define BALL_H_

#include "SDL2/SDL.h"

namespace markort147 {

struct Ball {
//	const static int BALL_RADIUS = 10;
	const static double BALL_SPEED = 0.0014;
	const static int MOVE_LEFT = SDL_SCANCODE_LEFT;
	const static int MOVE_RIGHT = SDL_SCANCODE_RIGHT;
	const static int MOVE_UP = SDL_SCANCODE_UP;
	const static int MOVE_DOWN = SDL_SCANCODE_DOWN;
	double m_x;
	double m_y;
	int m_radius;
	bool m_exist;
private:
	bool m_moving;
	double m_direction;
	int lastTime;
	double m_screenRatio;
	double xUpperBound;
	double xLowerBound;
	double yUpperBound;
	double yLowerBound;
private:
	void init(double, double, int, bool, double, bool, double);
public:
	Ball(double x, double y, int radius, bool moving, double direction, double screenRatio);
	Ball(int radius, bool moving, double direction, double screenRatio);
	virtual ~Ball();
	void update(int, Uint8);
	void setMoving(bool);
	void resize(double);
	void setDirection(int);
	static bool ballCollides(Ball, Ball);

	double getXLowerBound() const {
		return xLowerBound;
	}

	double getXUpperBound() const {
		return xUpperBound;
	}

	double getYLowerBound() const {
		return yLowerBound;
	}

	double getYUpperBound() const {
		return yUpperBound;
	}
	double randPosX();
	double randPosY();

	bool isMoving() const {
		return m_moving;
	}
};

} /* namespace markort147 */

#endif /* BALL_H_ */

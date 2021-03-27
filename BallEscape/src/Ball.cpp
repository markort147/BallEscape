/*
 * Ball.cpp
 *
 *  Created on: 15 mar 2021
 *      Author: Marco
 */

#include "Ball.h"
#include "Screen.h"
#include <math.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

namespace markort147 {

Ball::Ball(double x, double y, int radius, bool moving, double direction, double screenRatio) :
										lastTime(0) {
	init(x, y, radius, moving, direction, true, screenRatio);
}


Ball::Ball(int radius, bool moving, double direction, double screenRatio) :
										lastTime(0) {
	init(0, 0, radius, moving, direction, true, screenRatio);
	m_x = randPosX();
	m_y = randPosY();
	//	cout << "ball created: " << m_x << "," << m_y << endl;
}

void Ball::init(double x, double y, int radius, bool moving, double direction,
		bool exist, double screenRatio) {
	m_moving = moving;
	m_direction = direction;
	m_x = x;
	m_y = y;
	m_radius = radius;
	m_exist = exist;
	m_screenRatio = screenRatio;
	xUpperBound = min(1.,m_screenRatio);
	xLowerBound = -min(1.,m_screenRatio);
	yUpperBound = min(1.,1/m_screenRatio);
	yLowerBound = -min(1.,1/m_screenRatio);
	//	cout << "m_screenRatio: " << m_screenRatio << endl;
}

void Ball::resize(double screenRatio) {
	m_screenRatio = screenRatio;
	xUpperBound = min(1.,m_screenRatio);
	xLowerBound = -min(1.,m_screenRatio);
	yUpperBound = min(1.,1/m_screenRatio);
	yLowerBound = -min(1.,1/m_screenRatio);
}

void Ball::update(int elapsed, Uint8 score) {
	int interval = elapsed - lastTime;

	if (m_moving) {

		double ballSpeed = BALL_SPEED + BALL_SPEED * 0.01 * score;

		double x_speed = ballSpeed * cos(m_direction);
		double y_speed = ballSpeed * sin(m_direction);
		m_x += x_speed * interval;
		m_y += y_speed * interval;

		if (m_x <= xLowerBound)  m_x = xUpperBound;
		else if (m_x >= xUpperBound)  m_x = xLowerBound;
		if (m_y <= yLowerBound) m_y = yUpperBound;
		else if (m_y >= yUpperBound) m_y = yLowerBound;

//		cout << "m_x=" << m_x << endl;
//		cout << "m_y=" << m_y << endl;
//		cout << "xLowerBound=" << xLowerBound << endl;
//		cout << "yLowerBound=" << yLowerBound << endl;

	}

	lastTime = elapsed;

}

void Ball::setMoving(bool moving) {
	m_moving = moving;
	//	if(m_moving) cout << "ball's moving" << endl;
}

void Ball::setDirection(int input) {
	switch (input) {
	case Ball::MOVE_LEFT:
		m_direction = M_PI;
		break;
	case Ball::MOVE_RIGHT:
		m_direction = 0;
		break;
	case Ball::MOVE_DOWN:
		m_direction = M_PI / 2;
		break;
	case Ball::MOVE_UP:
		m_direction = 3 * M_PI / 2;
		break;
	default:
		break;
	}
	//		cout << "direction update: " << m_direction << endl;
}

Ball::~Ball() {
	// TODO Auto-generated destructor stub
}


double Ball::randPosX() {
	return ((double)rand()/RAND_MAX)*(xUpperBound - xLowerBound) + xLowerBound;
}
double Ball::randPosY() {
	return ((double)rand()/RAND_MAX)*(yUpperBound - yLowerBound) + yLowerBound;
}

} /* namespace markort147 */

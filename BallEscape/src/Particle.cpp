/*
 * Particle.cpp
 *
 *  Created on: 14 mar 2021
 *      Author: Marco
 */

#include <stdlib.h>
#include <math.h>
#include "Particle.h"
#include "Screen.h"

namespace markort147 {

Particle::Particle() {
	init();
}

void Particle::init() {
	m_x = 0;
	m_y = 0;
	m_direction = (2 * M_PI * rand()) / RAND_MAX;
	m_speed = (0.03 * rand()) / RAND_MAX;
	m_speed *= m_speed;
}

Particle::~Particle() {
	// TODO Auto-generated destructor stub
}

void Particle::update(int interval) {
	if (rand() < RAND_MAX / 2.) {
		m_direction += interval * 0.001;
	} else {
		m_direction -= interval * 0.0005;
	}

	double x_speed = m_speed * cos(m_direction);
	double y_speed = m_speed * sin(m_direction);

	m_x += x_speed * interval;
	m_y += y_speed * interval;

	if (m_x < -1 || m_x > 1 || m_y < -1 || m_y > 1) {
		init();
	}

	if (rand() < RAND_MAX / 500.) {
		init();
	}

//		x_speed *= -1;
//	if(m_y < -1 || m_y > 1) y_speed *= -1;

}

} /* namespace caveofprogramming */

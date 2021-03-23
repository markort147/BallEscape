/*
 * Particle.h
 *
 *  Created on: 14 mar 2021
 *      Author: Marco
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

namespace markort147 {

struct Particle {
	double m_x;
	double m_y;
private:
	double m_speed;
	double m_direction;
private:
	void init();
public:
	Particle();
	virtual ~Particle();
	void update(int);
};

} /* namespace caveofprogramming */

#endif /* PARTICLE_H_ */

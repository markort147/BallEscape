/*
 * Swarm.h
 *
 *  Created on: 14 mar 2021
 *      Author: Marco
 */

#ifndef SWARM_H_
#define SWARM_H_

#include "Particle.h"

namespace markort147 {

class Swarm {
public:
	const static int NPARTICLES = 5000;
private:
	Particle *m_pParticles;
	int lastTime;
public:
	Swarm();
	virtual ~Swarm();
	const Particle* const getParticles() {
		return m_pParticles;
	}
	void update(int);
};

} /* namespace caveofprogramming */

#endif /* SWARM_H_ */

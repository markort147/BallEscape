/*
 * Properties.h
 *
 *  Created on: 21 mar 2021
 *      Author: Marco
 */

#ifndef PROPERTIES_H_
#define PROPERTIES_H_

namespace markort147 {

class Properties {
private:
	unsigned int bonusNum;
	unsigned int malusNum;
	unsigned int bonusRadius;
	unsigned int malusRadius;
public:
	Properties();
	virtual ~Properties();
};

} /* namespace markort147 */

#endif /* PROPERTIES_H_ */

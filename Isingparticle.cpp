/*
 * Isingparticle.cpp
 *
 *  Created on: Feb 24, 2015
 *      Author: jmayo
 */

#include "Isingparticle.h"


	IsingParticle::IsingParticle(){spin=1;}// sets a spin to +1
	void IsingParticle::flipspin(){spin*=-1;}// change spin
	int IsingParticle::spinValue() const { return spin;}//return value
	// TODO Auto-generated constructor stub


IsingParticle::~IsingParticle(){



}

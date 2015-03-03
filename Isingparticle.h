/*
 * IsingParticle.h
 *
 *  Created on: Feb 24, 2015
 *      Author: jmayo
 */

#ifndef ISINGPARTICLE_H_
#define ISINGPARTICLE_H_


class IsingParticle{
      private:
       int spin; // -ve or +ve
      public:
       ~IsingParticle();
       IsingParticle();// Set spins in up position
       void flipspin();//flips the spin
       int spinValue() const;//returns the spin value
};
#endif

/* ISINGPARTICLE_H_ */


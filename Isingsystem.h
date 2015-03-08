/*
 * Isingsystem.h
 *
 *  Created on: Feb 24, 2015
 */

#ifndef ISINGSYSTEM_H_
#define ISINGSYSTEM_H_
#include "Isingparticle.h"
#define ISINGSIZE 8 // size of the array
class IsingSystem{
 private:
  IsingParticle particles[ISINGSIZE][ISINGSIZE];//Initialises an array of ising particles (all of spin +1) of a give size
  int current_column;//random selection
  int current_row;//random selection
  int left_column;
  int right_column;
  int up_row;//increment for neighbour
  int down_row;//increment for neighbour
  void find_neighbours();
 public:
  ~IsingSystem();
  IsingSystem();
  void choose(); // Choose a particle in the lattice
  void perturb(); // Spin-flip for the chosen particle
  void print(); // Prints the lattice configuration
  void reset();//Resets lattice to default
  double localEnergy(); // Interaction energy for the chosen particle
  double totalEnergy(); // Total energy for the lattice
  double magnetisation(); // Magnetisation of the system
};
#endif         //  Author: jmayo

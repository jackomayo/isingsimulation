/*
 * Isingsystem.cpp
 *
 *  Created on: Feb 24, 2015
 *      Author: jmayo
 */


#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<cmath>
#include "Isingsystem.h"
#include "Isingparticle.h"
#define ISINGSIZE 8

// sets randomly selected particle to 0,0
IsingSystem::IsingSystem(){
	up_row=0;
	down_row=0;
	right_column=0;
	left_column=0;
  current_column=0;
  current_row=0;
 }
// selects a particle in the array
void IsingSystem::choose(){
  current_column=rand() % ISINGSIZE;
  current_row=rand() % ISINGSIZE;
 // cout<< "Co-ordinates are"<<current_column<< <<current_row<< endl; //exercise 2 test debug

 }
//initial spin flip for peturbation
void IsingSystem::perturb(){
  particles[current_row][current_column].flipspin();
 }
// Visual representation of spin directions
void IsingSystem::print(){
  int i,j;
  for(i=0;i<ISINGSIZE;i++){
    for(j=0;j<ISINGSIZE;j++){
     particles[i][j].spinValue()>0 ? printf("+ ") : printf("- ");
    }
  printf("\n");
  }
 printf("\n");
 }
//particle's neighbours
void IsingSystem::find_neighbours(){
  current_row==0 ? up_row=ISINGSIZE-1 : up_row=current_row-1;
  current_row==ISINGSIZE-1 ? down_row=0 : down_row=current_row+1;
  current_column==0 ? left_column=ISINGSIZE-1 : left_column=current_column-1;
  current_column==ISINGSIZE-1 ? right_column=0 : right_column=current_column+1;
 }
/*Resets array to intial configuration(all +1 spin)*/
void IsingSystem::reset(){
  int i,j;
  for(i=0;i<ISINGSIZE;i++){
    for(j=0;j<ISINGSIZE;j++){
      if (particles[i][j].spinValue()<0) particles[i][j].flipspin();
    }
  }
 }

//Calculates energy of randomly selected particle
double IsingSystem::localEnergy(){
  double Energy=0;
  find_neighbours();
  particles[current_row][current_column].spinValue()== particles[up_row][current_column].spinValue()? Energy-- : Energy++;
  particles[current_row][current_column].spinValue()== particles[down_row][current_column].spinValue()? Energy-- : Energy++;
  particles[current_row][current_column].spinValue()== particles[current_row][left_column].spinValue()? Energy-- : Energy++;
  particles[current_row][current_column].spinValue()== particles[current_row][right_column].spinValue()? Energy-- : Energy++;
  return Energy;
 }
/*Sums and halves all the local energies of the array for total enegry of the system*/
double IsingSystem::totalEnergy(){
  double Energy=0;
  int store_row,store_column;
  store_row=current_row;
  store_column=current_column;
  int i,j;
  for(i=0;i<ISINGSIZE;i++){
    for(j=0;j<ISINGSIZE;j++){
       current_row=i;
       current_column=j;
       Energy+=localEnergy();
    }
  }
  current_row=store_row;
  current_column=store_column;
  return Energy/2;
 }

// sums spin values for magnetisation
double IsingSystem::magnetisation(){
  double magnet=0;
  int i,j;
  for(i=0;i<ISINGSIZE;i++){
    for(j=0;j<ISINGSIZE;j++){
     magnet+=particles[i][j].spinValue();
    }
  }
  magnet*=(1/(pow(ISINGSIZE,2)));
  return fabs(magnet);
 }

IsingSystem::~IsingSystem() {
	// TODO Auto-generated destructor stub
}

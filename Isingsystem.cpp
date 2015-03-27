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
#define ISINGSIZE 64

// sets randomly selected particle to 0,0
IsingSystem::IsingSystem(){

//	initialisation necessary to work on windows (not on linux tho) shouldnt be necessary no idea why it is

	current_column=0;
	current_row=0;
	up=current_row+1;
	down=current_row-1;
	right=current_column+1;
	left=current_column-1;
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
// ASCI print of spin config used
void IsingSystem::print(){
  int i,j;
  for(i=0;i<ISINGSIZE;i++){
    for(j=0;j<ISINGSIZE;j++){
    if( particles[i][j].spinValue()>0 ){ printf("+ ");}

    else{ printf("- ");}
    }
  printf("\n");
  }
 printf("\n");
 }
//particle's neighbours
void IsingSystem::find_neighbours(){
  if (current_row==0) { up=ISINGSIZE-1;}
  else{ up=current_row-1;}

  if( current_row==ISINGSIZE-1) { down=0;}
  else{ down=current_row+1;}

  if(current_column==0) {left=ISINGSIZE-1 ;}
  else{ left=current_column-1;}

  if(current_column==ISINGSIZE-1){ right=0 ;}
  else{ right=current_column+1;}
 }
//all +ve
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
  double E=0;
  find_neighbours();
  if(particles[current_row][current_column].spinValue()== particles[up][current_column].spinValue())
  { E-- ;}
  else{ E++;}

  if(particles[current_row][current_column].spinValue()== particles[down][current_column].spinValue())
  { E--;}
  else{ E++;}

  if(particles[current_row][current_column].spinValue()== particles[current_row][left].spinValue())
  {E--;}
  else{ E++;}

  if(particles[current_row][current_column].spinValue()== particles[current_row][right].spinValue())
  { E--;}
  else{ E++;}
  return E;
 }
/*Sums and halves all the local energies of the array for total enegry of the system*/
double IsingSystem::totalEnergy(){
  double E_tot=0;
  int store_row,store_column;
  store_row=current_row;
  store_column=current_column;
  int i,j;
  for(i=0;i<ISINGSIZE;i++){
    for(j=0;j<ISINGSIZE;j++){
       current_row=i;
       current_column=j;
       E_tot+=localEnergy();
    }
  }
  current_row=store_row;
  current_column=store_column;
  return E_tot/2;
 }

// sums spin values for magnetisation
double IsingSystem::magnetisation(){
  double m=0;
  int i,j;
  for(i=0;i<ISINGSIZE;i++){
    for(j=0;j<ISINGSIZE;j++){
     m+=particles[i][j].spinValue();
    }
  }
  m*=(1/(pow(ISINGSIZE,2)));
  return fabs(m);
 }

IsingSystem::~IsingSystem() {
	// TODO Auto-generated destructor stub
}

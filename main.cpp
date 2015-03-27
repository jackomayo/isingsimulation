#include<stdlib.h> 
#include<stdio.h>
#include<math.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Isingsystem.h"
#include "Isingparticle.h"
#include "Statistics.h"
#define ISINGSIZE 64
using namespace std;

int main (void)

{

cout<<"Are we cooking?\n..........................\n\n"<< endl;

setvbuf(stdout, NULL, _IONBF, 0);
setvbuf(stderr, NULL, _IONBF, 0);


 ofstream myfile;
 myfile.open ("64x64simulationresultsmega.txt");


 //energy variables and perturbation condition

double E_i,E_f,deltaE,r;
double T;//for some reason wont work as a double

IsingSystem lattice;
 
 int i,j;
 int const Nmcs=350000, rmax=200;
 
 //variable init
 double mag_av, Merr,Cerr,Cv;
 
 cout<<"Cooking data:"<<endl;

for(T=0.5;T<6;T+=0.02){

//debug print to make sure all works
//cout<<"t= "<<T<< endl;


  Statistics specheat;
  Statistics magnet;
  Statistics specheaterror;

   for(j=0;j<rmax;j++){
                       
//declare energy and megnetisation set for individial configurations



     for(i=0;i<Nmcs;i++){
       //particle choose
       lattice.choose();


       E_i=lattice.localEnergy();

       //change spin
       lattice.perturb();

       //sets energy
       E_f=lattice.localEnergy();

       deltaE=E_f-E_i;
     
       //random number for pet cond.
       r=((double) rand()/RAND_MAX);
      
       //Perturbation condition
       if (r>exp(-1*(deltaE/T))) lattice.perturb();
    
    
       //point conditions to prevent multiple configurations and for thermalisation to occur

       if(i>Nmcs/2 && i%(ISINGSIZE*ISINGSIZE)==0){



    	   magnet.add(lattice.magnetisation());

    	   specheat.add(lattice.totalEnergy());


    	   }



     }




      Cv =(1/((T*T)*(ISINGSIZE*ISINGSIZE))) *( (specheat.getSqAverage() - specheat.getAverage()*specheat.getAverage()));


       specheaterror.add(Cv);



   }


  
     //Magnetisation
     mag_av=magnet.getAverage();
     //specific heat error
     Cerr=(1/sqrt(specheaterror.getNumber()))*sqrt(specheaterror.getSqAverage() - pow(specheaterror.getAverage(),2));


     //magnetisation error
	 Merr=(1/sqrt(magnet.getNumber()))*sqrt(magnet.getSqAverage() - pow(magnet.getAverage(),2));

  

myfile<< setprecision(7) << T <<" "<< mag_av <<" "<< Merr <<" "<< Cv <<" "<< Cerr << endl;



cout<< T <<" "<< mag_av <<" "<< Merr <<" "<< Cv <<" "<< Cerr << endl;


//printout asci representations below and above curie temp

if((T<=1.501 && T>=1.499) || (T<=5.001 && T>=4.999)){
	cout<<T<<endl;
	lattice.print();
	cout<<endl;
}


//reset array
  lattice.reset();

 }


 

myfile.close();
 
cout<<"cooked!"<<endl;

 return 0;    
}

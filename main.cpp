#include<stdlib.h> 
#include<stdio.h>
#include<math.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Isingsystem.h"
#include "Isingparticle.h"
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
float T;//for some reason wont work as a double

IsingSystem Array;
 
 int i,j,points;
 int const Nmcs=5000000, rmax=300;
 
 //variable init
 double Ctot,Ctot2,CAvg,CAv2,E_av,E2av,Etot,Etot2,magtot, magtot2,mag_av,mag_av2, Merr,Cerr;
 
 cout<<"Cooking data:"<<endl;

for(T=0.5;T<6;T+=0.01){

//debug print to make sure all works
//cout<<"t= "<<T<< endl;

  Ctot=0;
  Ctot2=0;
                       
   for(j=0;j<rmax;j++){
                       
//declare energy and megnetisation set for individial configurations
     magtot=0;
     magtot2=0;
     Etot=0;
     Etot2=0; 
     points=0;

     for(i=0;i<Nmcs;i++){
       //particle choose
       Array.choose();


       E_i=Array.localEnergy();

       //change spin
       Array.perturb();

       //sets energy
       E_f=Array.localEnergy();

       deltaE=E_f-E_i;
     
       //random number for pet cond.
       r=((double) rand()/RAND_MAX);
      
       //Perturbation condition
       if (r>exp(-1*(deltaE/T))) Array.perturb();
    
    
       //point conditions to prevent multiple configurations and for thermalisation to occur

       if(i>Nmcs/2 && i%(ISINGSIZE*ISINGSIZE)==0){

    	// magnetisation
        magtot+=Array.magnetisation();

        // magnetisation squared
        magtot2+=pow(Array.magnetisation(),2);

        // energy data
        Etot+=Array.totalEnergy();

        // energy squared
        Etot2+=pow(Array.totalEnergy(),2);





        //data points increment
         points++;      }



     }


     // average magnetisation
     mag_av=magtot/points;


     // average magnetisation squared
    mag_av2=magtot2/points;
  
    // average energy
    E_av=Etot/points;

    // average energy squared
    E2av=Etot2/points;

    // specific heat
       Ctot=Ctot+((E2av-(E_av*E_av))/((T*T)*(ISINGSIZE*ISINGSIZE)));

       //Collects specific heat squared
       Ctot2=Ctot2+(pow((E2av-(E_av*E_av))/((T*T)*(ISINGSIZE*ISINGSIZE)),2));


   }

   //Calculates the average specific heat
   CAvg=Ctot/rmax;
  
   //Calculates the average specific heat squared
   CAv2=Ctot2/rmax;
  
   //specific heat error
   Cerr=sqrt((CAv2-pow(CAvg,2))/rmax);
  
   //magnetisation error
   Merr=sqrt((mag_av2-pow(mag_av,2))/points);


  

myfile<< setprecision(7) << T <<" "<< mag_av <<" "<< Merr <<" "<< CAvg <<" "<< Cerr << endl;



cout<< T <<" "<< mag_av <<" "<< Merr <<" "<< CAvg <<" "<< Cerr << endl;


//printout asci representations below and above curie temp

if((T<=1.51 && T>=1.49) || (T<=5.01 && T>=4.99)){
	cout<<T<<endl;
	Array.print();
	cout<<endl;
}


//reset array
  Array.reset();

 }


 

myfile.close();
 
cout<<"cooked!"<<endl;

 return 0;    
}

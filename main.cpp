#include<stdlib.h> 
#include<stdio.h>
#include<math.h>
#include <iostream>
#include "Isingsystem.h"
#include "Isingparticle.h"
#define ISINGSIZE 8


int main (void)

{

printf("Are we cooking?\n..........................\n\n");

setvbuf(stdout, NULL, _IONBF, 0);
setvbuf(stderr, NULL, _IONBF, 0);


IsingSystem MyArray;

 IsingSystem MyArray;//Initialises 2D ising array
// printf("are we cooking?");

 //output file
 FILE *results;
 results=fopen("Simulation_Results_8x8","w");
 //Initialises the varible initial energy, final energy and change in energy
 double Ei,Ef,Edif;
 //Initialises perturbation condition
 double r;
 //Initialises temperature constant
 double T;
 
//Initialises counter vaiables; i is the thermalisation for loop counter, j is the simulation repetition counter,
//and DataCounter counts the number of data points collected per simulation
 int i,j,DataCounter;
 
 //Initialises Monte Carlo Number of simulations Nc and the number of Monte Carlo repetitions jmax
 int const Nc=1000000, jmax=100;
 
//Initialises magnetic variables, sum of magnetisation, sum of magnetisation squared, average magnetisation and average magnetisation squated
 double MagSum, Mag2Sum,AvMag,Av2Mag;
 
//Initialises energetic variables, sum of energies, sum of energies squared, average energies and average energies squared
 double Eav,E2av,Esum,E2sum;
 
 double CvSum,Cv2Sum,CvAv,Cv2Av;//Initialises specific heat sum, specific heat squared sum, specific heat average and specific heat squared average 
 
 //Initialises magnetic specific heat error
 double Merr,Cverr;
 

 printf("Cooking data; Please wait...\n");

 printf("Cooking data; Please wait...\n\n\n");
 
 
//Loops Monte Carlo simulation for required number of temperatures
for(T=0.5;T<6;T+=0.02){


 printf("t= %lf \n ", T);

//(Re)sets specific heat counter variables
  CvSum=0;                     
  Cv2Sum=0;
                       
   for(j=0;j<jmax;j++){
                       
/*(Re)sets magnetic and energetic counter variables*/             
     MagSum=0; 
     Mag2Sum=0;
     Esum=0;
     E2sum=0; 
     DataCounter=0;
   
   
//actual simulation
     for(i=0;i<Nc;i++){
       // select particle
       MyArray.choose();
       //sets initial energy
       Ei=MyArray.localEnergy();

       //Changes spin of selected particle
       MyArray.perturb();

       //Takes energy of selected particle and sets it to final energy
       Ef=MyArray.localEnergy();

       //Finds difference of final and initial energy
       Edif=Ef-Ei;
     
       //Generates a random number between 0 and 1 and sets it to perturbation condition
       r=((double) rand()/RAND_MAX);
      
       //Compares perturbation condition to exp(-Edif/T), if perturbation condition is larger the selected particle's spin is changed back
       if (r>exp(-1*(Edif/T))) MyArray.perturb();
    
    
       //Data collection conditions given, data only collected from half of the Monte Carlo simulation, allowing the array to thermalise
       //aswell as only collected for every nth loop, where n is the size of the array, to avoid correlations
       if(i>Nc/2 && i%(ISINGSIZE*ISINGSIZE)==0){

    	//Collects magnetisation data
        MagSum+=MyArray.magnetisation();

        //Collects magnetisation squared data
        Mag2Sum+=pow(MyArray.magnetisation(),2);

        //Collects energy data
        Esum+=MyArray.totalEnergy();

        //Collects energy squared data
        E2sum+=pow(MyArray.totalEnergy(),2);

        //Counts amount of data collected
               }
        DataCounter++;


     }
   

     //Calculates average magnetisation
     AvMag=MagSum/DataCounter;


     //Calculates average magnetisation squared
    Av2Mag=Mag2Sum/DataCounter;
  
    //Calculates average energy
    Eav=Esum/DataCounter;

    //Calculates average energy squared
    E2av=E2sum/DataCounter;
 
    //Collects specific heat
    CvSum+=(E2av-pow(Eav,2))/(pow(T,2)*pow(ISINGSIZE,2));

    //Collects specific heat squared
    Cv2Sum+=pow((E2av-pow(Eav,2))/(pow(T,2)*pow(ISINGSIZE,2)),2);

  }
  
   //Calculates the average specific heat
   CvAv=CvSum/jmax;
  
   //Calculates the average specific heat squared
   Cv2Av=Cv2Sum/jmax;
  
   //Calculates specific heat error
   Cverr=sqrt((Cv2Av-pow(CvAv,2))/jmax);
  
   //Calculates magnetisation error
   Merr=sqrt((Av2Mag-pow(AvMag,2))/DataCounter);
  
  

   //output to file
  fprintf(results,"%lf %lf %lf %lf %lf\n",T,AvMag,Merr,CvAv,Cverr);
  
//reset array
  MyArray.reset();
 }
 
 fclose(results);
 
 printf("cooked!\n");

 return 0;    
}

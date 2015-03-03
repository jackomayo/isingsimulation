#include<stdlib.h> 
#include<stdio.h>
#include<cmath>
#include <iostream>
#include "Isingsystem.h"
#include "Isingparticle.h"
#define ISINGSIZE 16


int main (void)
{
 IsingSystem MyArray;//Initialises 2D ising array
 
//output file
 FILE *results;
 results=fopen("Simulation_Results_32x32","w");
 
 double Ei,Ef,Edif;//Initialises the varible initial energy, final energy and change in energy
 double r;//Initialises perturbation condition 
 double T;//Initialises temperature constant
 
/*Initialises counter vaiables; i is the thermalisation for loop counter, j is the simulation repetition counter, 
and DataCounter counts the number of data points collected per simulation*/
 int i,j,DataCounter;
 
 int const Nc=1000000, jmax=100;//Initialises Monte Carlo Number of simulations Nc and the number of Monte Carlo repetitions jmax
 
/*Initialises magnetic variables, sum of magnetisation, sum of magnetisation squared, average magnetisation and average magnetisation squated*/
 double MagSum, Mag2Sum,AvMag,Av2Mag;
 
/*Initialises energetic variables, sum of energies, sum of energies squared, average energies and average energies squared*/
 double Eav,E2av,Esum,E2sum;
 
 double CvSum,Cv2Sum,CvAv,Cv2Av;//Initialises specific heat sum, specific heat squared sum, specific heat average and specific heat squared average 
 
 double Merr,Cverr;//Initialises magnetic specific heat error
 
 printf("Generating Data; Please wait...\n\n\n");
 
 
/*Loops Monte Carlo simulation for required number of temperatures*/
for(T=0.5;T<6;T+=0.02){
 
/*(Re)sets specific heat counter variables*/                        
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
                                       
       MyArray.choose();// select particle
       Ei=MyArray.localEnergy();//sets initial energy
     
       MyArray.perturb();//Changes spin of selected particle
       Ef=MyArray.localEnergy();//Takes energy of selected particle and sets it to final energy
     
       Edif=Ef-Ei;//Finds difference of final and initial energy
     
       r=((double) rand()/RAND_MAX);//Generates a random number between 0 and 1 and sets it to perturbation condition 
      
/*Compares perturbation condition to exp(-Edif/T), if perturbation condition is larger the selected particle's spin is changed back*/ 
       if (r>exp(-1*(Edif/T))) MyArray.perturb();
    
    
/*Data collection conditions given, data only collected from half of the Monte Carlo simulation, allowing the array to thermalise
aswell as only collected for every nth loop, where n is the size of the array, to avoid correlations*/
       if(i>Nc/2 && i%(ISINGSIZE*ISINGSIZE)==0){
        MagSum+=MyArray.magnetisation();//Collects magnetisation data
        Mag2Sum+=pow(MyArray.magnetisation(),2);//Collects magnetisation squared data
        Esum+=MyArray.totalEnergy();//Collects energy data
        E2sum+=pow(MyArray.totalEnergy(),2);//Collects energy squared data
        DataCounter++;//Counts amount of data collected
       }
     }
   
    AvMag=MagSum/DataCounter;//Calculates average magnetisation 
  
    Av2Mag=Mag2Sum/DataCounter;//Calculates average magnetisation squared
  
    Eav=Esum/DataCounter;//Calculates average energy 

    E2av=E2sum/DataCounter;//Calculates average energy squared
 
    CvSum+=(E2av-pow(Eav,2))/(pow(T,2)*pow(ISINGSIZE,2));//Collects specific heat
    Cv2Sum+=pow((E2av-pow(Eav,2))/(pow(T,2)*pow(ISINGSIZE,2)),2);//Collects specific heat squared

  }
  
  CvAv=CvSum/jmax;//Calculates the average specific heat
  
  Cv2Av=Cv2Sum/jmax;//Calculates the average specific heat squared
  
  
  Cverr=sqrt((Cv2Av-pow(CvAv,2))/jmax);//Calculates specific heat error
  
  Merr=sqrt((Av2Mag-pow(AvMag,2))/DataCounter);//Calculates magnetisation error
  
  
  fprintf(results,"%lf %lf %lf %lf %lf\n",T,AvMag,Merr,CvAv,Cverr);//prints off data to specified text file
  

  MyArray.reset();
 }
 
 fclose(results);
 
 printf("done!\n");   
 system("pause");
 return 0;    
}

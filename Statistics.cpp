/*
 * Statistics.cpp
 *
 *  Created on: 27 Mar 2015
 *      Author: Jack Mayo
 */
#include <cmath>
#include "Statistics.h"

namespace std {

Statistics::Statistics() {
	n=0;
	                         sum=0.0;
	                         sumsq=0.0;
	// TODO Auto-generated constructor stub

}
int Statistics::getNumber() const{
    return n;
}
double Statistics::getAverage() const {
       if(n==0) return 0.;
       return sum/n;
}

double Statistics::getSqAverage() const {
       if(n==0) return -1;
       return sumsq/n;
}

void Statistics::add(double x) {
     n++;
     sum += x;
     sumsq += x*x;
}
Statistics::~Statistics() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */

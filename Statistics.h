/*
 * Statistics.h
 *
 *  Created on: 27 Mar 2015
 *      Author: Jack Mayo
 */

#ifndef STATISTICS_H_
#define STATISTICS_H_

namespace std {

class Statistics {
private:
            int n;
            double sum;
            double sumsq;
public:
	Statistics();
              int getNumber() const;
              double getAverage() const;
              double getSqAverage() const;
              void add(double x);
	virtual ~Statistics();
};

} /* namespace std */

#endif /* STATISTICS_H_ */

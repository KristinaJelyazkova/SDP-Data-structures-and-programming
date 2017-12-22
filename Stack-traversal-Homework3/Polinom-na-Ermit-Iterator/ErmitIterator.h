#ifndef _ERMITITERATOR_
#define _ERMITITERATOR_

#include<iostream>
#include<stack>

class Ermit {
public:
	Ermit(double, unsigned int);
	bool foundResult() const;
	double getNext();

private:
	double x;
	unsigned int n;
	std::stack< std::pair<double, unsigned int> > info;
};

#endif
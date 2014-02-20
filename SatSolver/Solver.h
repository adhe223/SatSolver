#ifndef SOLVER_H
#define SOLVER_H

#include "Population.h"
#include <string>

class Solver {
public:
	Solver(std::string filename, int popSize);

private:
	Population * myPop;
};

#endif
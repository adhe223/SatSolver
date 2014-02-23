#ifndef SOLVER_H
#define SOLVER_H

#include "Population.h"
#include "Solution.h"
#include <string>

class Solver {
public:
	Solver(std::string filename, int popSize);

	void geneticSolve();

private:
	Population * myPop;
	std::string filename;
};

#endif
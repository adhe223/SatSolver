#ifndef SOLVER_H
#define SOLVER_H

#include "Population.h"
#include "Solution.h"
#include <string>

class Solver {
public:
	Solver(std::string filename);

	void readClauses();
	void geneticSolve(int popSize);
	void walkSolve();

private:
	Population * myPop;
	std::string filename;
	std::vector<Clause*> clauses;
};

#endif
#ifndef GENETICSOLVER_H
#define GENETICSOLVER_H
#include "Population.h"
#include "Clause.h"
#include "Solver.h"
#include <string>

class GeneticSolver {
public:
	GeneticSolver(Population * inPop, std::string inFilename);

	void assignFitness();
	void readClauses();

private:
	Population * myPop;
	std::vector<Clause*> clauses;
	std::string filename;
};

#endif
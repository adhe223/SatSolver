#ifndef GENETICSOLVER_H
#define GENETICSOLVER_H
#include "Population.h"
#include "Clause.h"
#include "Solver.h"

class GeneticSolver : public  Solver{
public:
	GeneticSolver(Population * inPop, std::string inFilename);

	void assignFitness();

private:
	//Population * myPop;
};

#endif
#ifndef GENETICSOLVER_H
#define GENETICSOLVER_H
#include "Population.h"

class GeneticSolver {
public:
	GeneticSolver(Population * inPop, std::string inFilename);

	void assignFitness(string filename);

private:
	Population * myPop;
	std::string filename;
};

#endif
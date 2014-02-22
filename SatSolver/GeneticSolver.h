#ifndef GENETICSOLVER_H
#define GENETICSOLVER_H
#include "Population.h"
#include "Clause.h"
#include "Solver.h"
#include "Solution.h"
#include <string>

class GeneticSolver {
public:
	GeneticSolver(Population * inPop, std::string inFilename);

	void assignFitness();
	void selection();
	void mutate();
	Solution * isSolved();

	//Used strictly for debugging
	int getTopFitness();
	

private:
	Solution * cross(int parentPoolSize);
	void readClauses();

	Population * myPop;
	std::vector<Clause*> clauses;
	std::string filename;

	const double POP_CUTOFF = .3;
	const double MUTATE_PROB = .1;
};

#endif
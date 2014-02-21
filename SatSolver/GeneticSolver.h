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
	void readClauses();
	void selection();
	bool mycompare(Solution * sol1, Solution * sol2);

private:
	Population * myPop;
	std::vector<Clause*> clauses;
	std::string filename;
};

#endif
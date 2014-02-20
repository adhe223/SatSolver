#ifndef	POPULATION_H
#define POPULATION_H

#include "Solution.h"
#include "Clause.h"
#include <vector>

class Population {
public:
	Population(int numVars, int popSize);
	Population(const Population & inPop);

	void assignGeneticFitness(vector<Clause*> inClause);	//Takes in the cosntraints to judge against

private:
	std::vector<Solution*> solutions;
};

#endif
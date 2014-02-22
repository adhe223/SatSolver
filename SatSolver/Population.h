#ifndef	POPULATION_H
#define POPULATION_H

#include "Solution.h"
#include "Clause.h"
#include <vector>

class Population {
public:
	Population(std::string inFilename, int popSize);
	Population(const Population & inPop);
	~Population();

	void assignGeneticFitness(std::vector<Clause*> & inClause);	//Takes in the cosntraints to judge against
	std::vector<Solution*> & getSolutions();
	void resetSolutions(std::vector<Solution *> & inSolutions);

private:
	std::vector<Solution*> solutions;
};

#endif
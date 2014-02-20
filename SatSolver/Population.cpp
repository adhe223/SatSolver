#include "Population.h"
#include "Clause.h"
using namespace std;

Population::Population(int numVars, int popSize) {
	for (int i = 0; i < popSize; i++) {
		solutions.push_back(new Solution(numVars));
	}
}

Population::Population(const Population & inPop) {
	solutions = inPop.solutions;
}

void Population::assignGeneticFitness(vector<Clause> inClause) {
	//Fitness will be 1 for every constaint the variable satisfies
	int fitCount = 0;

	for (int i = 0; i < solutions.size(); i++) {
		//Read in each clause and check if it is satisfied

	}
}
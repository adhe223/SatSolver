#ifndef GENETICSOLVER_H
#define GENETICSOLVER_H
#include "Population.h"
#include "Clause.h"
#include "Solver.h"
#include "Solution.h"
#include <string>

class GeneticSolver {
public:
	GeneticSolver(Population * inPop, std::vector<Clause*> inClauses);

	void assignFitness();
	void selection();
	void mutate();
	bool isSolved(int roundCount);
	bool isStuck(int currCount);
	int getStuckCount();
	int getStuckLimit();
	void genocide(Population * inPop);	//Reset pop

	//Used for debugging output
	int getTopFitness();
	

private:
	Solution * cross(int parentPoolSize);

	Population * myPop;
	std::vector<Clause*> clauses;

	int stuckCount;	//Number of times the function has gotten stuck

	//Tweakers
	const int STUCK_LIMIT = 15;
	const int STUCK_THRESHOLD = 200;
	const double POP_CUTOFF = .15;
	const double MUTATE_PROB = .05;
};

#endif
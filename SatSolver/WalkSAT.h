#ifndef WALKSAT_H
#define WALKSAT_H

#include "Population.h"
#include "Solution.h"
#include "Clause.h"
#include <vector>


class WalkSAT {
public:
	WalkSAT(std::vector<Clause*> inClauses, std::string inFilename);
	~WalkSAT();

	int getMaxFlips();
	bool isSolved(int flipCount);
	void walk();
	int numClauseSat(Solution * sol);
	Solution * getSol();

	//Data Gathering purposes
	int maxC;

private:
	Solution * getBestSol();

	Solution * mySol;
	std::vector<int> unsatClauses;
	std::vector<Clause*> clauses;

	//Tweakers
	const double RANDOM_WALK_PROB = .5;
	const double MAX_FLIPS = 10000;
};

#endif
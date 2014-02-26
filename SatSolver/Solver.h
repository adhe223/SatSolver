#ifndef SOLVER_H
#define SOLVER_H

#include "Population.h"
#include "Solution.h"
#include <string>
#include <Windows.h>

class Solver {
public:
	Solver(std::string filename);

	void readClauses();
	void geneticSolve(int popSize);
	void walkSolve();

	//For data gathering purposes
	DWORD begin;
	DWORD end;
private:
	Population * myPop;
	std::string filename;
	std::vector<Clause*> clauses;


};

#endif
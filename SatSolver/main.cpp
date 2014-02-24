#include "Population.h"
#include "GeneticSolver.h"
#include "Solution.h"
#include <random>
#include <ctime>
#include <iostream>
using namespace std;

//Size of population
const int POP_SIZE = 100;

//Genetic Algorithm tweaks are found in its h file private members
int main() {
	srand(time(NULL));

	Solution * solution = NULL;
	
	Solver * solver = new Solver("10.44.1667358355.cnf");
	solver->readClauses();
	solver->geneticSolve(POP_SIZE);
	solver->walkSolve();

	cin.ignore(200, '\n');
	return 0;
}
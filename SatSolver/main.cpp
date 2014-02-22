#include "Population.h"
#include "GeneticSolver.h"
#include "Solution.h"
#include <random>
#include <ctime>
#include <iostream>
using namespace std;

//Genetic Algorithm tweaks are found in its h file private members
int main() {
	srand(time(NULL));

	Solution * solution = NULL;
	
	Solver * solver = new Solver("10.48.1494607484.cnf", 2000);
	solution = solver->geneticSolve();

	//Now we need to display the solution
	solution->printSolution();

	cin.ignore(200, '\n');
	return 0;
}
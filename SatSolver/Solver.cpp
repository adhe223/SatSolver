#include "Solver.h"
#include "Population.h"
#include "GeneticSolver.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

Solver::Solver(string inFilename, int popSize) {
	filename = inFilename;
	myPop = new Population(inFilename, popSize);
}

Solution * Solver::geneticSolve() {
	GeneticSolver * gs = new GeneticSolver(myPop, filename);
	bool solutionFound = false;
	Solution * solution = NULL;
	int roundCount = 1;

	while (!solutionFound) {
		solution = gs->isSolved();			//Check if the problem is solved
		if (solution != NULL) {
			//We have solution!
			return solution;
		}

		gs->assignFitness();	//judges fitness of population

		cout << "Beginning round " << roundCount << " with a best fitness of " << gs->getTopFitness() << "!" << endl;

		gs->selection();		//Select the best of pop
		gs->mutate();			//Mutate the pop

		roundCount++;
	}
}
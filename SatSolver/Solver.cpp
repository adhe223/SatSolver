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

void Solver::geneticSolve() {
	cout << "Working..." << endl << endl;

	GeneticSolver * gs = new GeneticSolver(myPop, filename);
	bool solutionFound = false;
	int roundCount = 1;

	while (!solutionFound) {
		//Check if the problem is solved
		if (gs->isSolved(roundCount)) {
			//We have solution!
			return;
		}

		if (gs->isStuck(roundCount)) {
			//Algorithm is stuck
			if (gs->getStuckCount() < gs->getStuckLimit()) {
				roundCount = 0;
				gs->genocide(myPop);
			}
			else {
				//else quit
				cout << "The problem is either unsatisfiable (most likely) or too difficult to solve without more time!" << endl;
				return;
			}
		}
		gs->assignFitness();	//judges fitness of population

		//Debug print statement
		cout << "Beginning round " << roundCount << " with a best fitness of " << gs->getTopFitness() << "!" << endl;

		gs->selection();		//Select the best of pop
		gs->mutate();			//Mutate the pop

		roundCount++;
	}
}
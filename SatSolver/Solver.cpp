#include "Solver.h"
#include "Population.h"
#include "GeneticSolver.h"
#include "WalkSAT.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

Solver::Solver(string inFilename) {
	filename = inFilename;
	myPop = NULL;
}

void Solver::readClauses() {
	ifstream inFile;
	inFile.open(filename);
	string line;
	bool loop = true;

	while (loop) {
		getline(inFile, line);
		if (line[0] == 'p') { loop = false; }	//We are where we need to be now
	}

	while (getline(inFile, line)) {
		vector<int> constraints;
		stringstream ss(line, ios_base::in);

		if (ss.str()[0] != 'c') {	//Make sure it's not a comment
			int toAdd;

			loop = true;
			while (loop){		//Read in values until ss is empty
				ss >> toAdd;
				if (toAdd == 0) { loop = false; }	//If 0 we have reached the end of the clause
				else { constraints.push_back(toAdd); }
			}

			//All the variables have been read into the clause, now push onto the clauses vector
			clauses.push_back(new Clause(constraints));
		}
	}
}

void Solver::geneticSolve(int popSize) {
	myPop = new Population(filename, popSize);
	cout << "Working on Genetic Solver..." << endl << endl;

	readClauses();
	GeneticSolver * gs = new GeneticSolver(myPop, clauses);
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

void Solver::walkSolve() {
	cout << "Working on WalkSAT..." << endl << endl;

	readClauses();
	WalkSAT * ws = new WalkSAT(clauses, filename);
	bool solutionFound = false;
	
	for (int i = 0; i < ws->getMaxFlips(); i++) {
		cout << "Beginning WalkSAT round " << i << " with a score of " << ws->numClauseSat(ws->getSol()) << endl;
		if (ws->isSolved(i)) {
			return;
		}

		ws->walk();
	}

	cout << "Was not able to solve the SAT problem with WalkSAT!" << endl;
}
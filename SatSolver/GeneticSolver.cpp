#include "GeneticSolver.h"
#include "Solution.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

GeneticSolver::GeneticSolver(Population * inPop, string inFilename) {
	//Make a deep copy to work with
	myPop = new Population(*inPop);

	filename = inFilename;
}

void GeneticSolver::assignFitness() {
	myPop->assignGeneticFitness(clauses);
}

void GeneticSolver::readClauses() {
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

void GeneticSolver::selection() {
	//Select the best members of the population and remove the rest. Use a priority queue to find the best ones
	//priority_queue<Solution *> pq = priority_queue<Solution *>();
	vector<Solution *> vectSolutions;
	vector<Solution *> tempSolutions = myPop->getSolutions();

	for (int i = 0; i < tempSolutions.size(); i++) {
		vectSolutions.push_back(tempSolutions[i]);
	}

	//All of our solutions are now in the vector, we need to sort
	sort(vectSolutions.begin(), vectSolutions.end(), mycompare);

	int foo = 5;
}

bool GeneticSolver::mycompare(Solution * sol1, Solution * sol2) { return (sol1->getFitness() > sol2->getFitness()); }
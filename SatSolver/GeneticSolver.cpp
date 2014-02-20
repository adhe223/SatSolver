#include "GeneticSolver.h"
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

GeneticSolver::GeneticSolver(Population * inPop, string inFilename) {
	//Make a deep copy to work with
	myPop = new Population(*inPop);

	filename = inFilename;
}

void GeneticSolver::assignFitness() {
	myPop->assignGeneticFitness(clauses);
}

void GeneticSolver::readClauses(string filename) {
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
		int toAdd;

		while (!ss.eof) {		//Read in values until ss is empty
		ss >> toAdd;
		constraints.push_back(toAdd);
		}

		//All the variables have been read into the clause, now push onto the clauses vector
		clauses.push_back(new Clause(constraints));
	}
}
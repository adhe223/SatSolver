#include "Population.h"
#include "Clause.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

Population::Population(string inFilename, int popSize) {
	//initialize the parameters we will use to create our population
	int numVars = -1;

	//Read in the file and find how many vairiables there are
	bool loop = true;
	string line;
	string filename = inFilename;
	ifstream inStream(filename);

	//Get to the line starting with p
	while (loop) {
		getline(inStream, line);
		if (line[0] == 'p') {
			loop = false;
			stringstream ss(line, ios_base::in);

			//Get the numvar info
			string temp;

			ss >> temp;
			ss >> temp;

			//Should be at the numVar data now
			ss >> numVars;
		}
	}

	for (int i = 0; i < popSize; i++) {
		solutions.push_back(new Solution(numVars));
	}
}

Population::Population(const Population & inPop) {
	solutions = inPop.solutions;
}

Population::~Population() {
	for (int i = 0; i < solutions.size(); i++) {
		delete solutions[i];
	}
}

void Population::assignGeneticFitness(vector<Clause*> & inClauses) {
	//Fitness will be +1 for every constraint the variable satisfies


	//Check each solution against the clauses and see the results
	for (int j = 0; j < solutions.size(); j++) {
		int fitCount = 0;

		for (int i = 0; i < inClauses.size(); i++) {
			if (inClauses[i]->satisfy(solutions[j])) { 
				fitCount++; 
			}
		}

		//Checked each clause, now set the fitness for that particular solution
		solutions[j]->setFitness(fitCount);
	}
}

vector<Solution *> & Population::getSolutions() {
	return solutions;
}

//Make sure this does not leak memory
void Population::resetSolutions(std::vector<Solution *> & inSolutions) {
	for (int i = 0; i < solutions.size(); i++) {
		delete solutions[i];
	}

	solutions = inSolutions;
}
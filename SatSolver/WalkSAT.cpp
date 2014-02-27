#include "WalkSAT.h"
#include <iostream>
#include <random>
#include <fstream>
#include <sstream>

using namespace std;

WalkSAT::WalkSAT(std::vector<Clause*> inClauses, string inFilename) {
	clauses = inClauses;

	//Randomly initialize our solution
	//Read in the file and find how many vairiables there are
	int numVars = -1;
	bool loop = true;
	string line;
	ifstream inStream(inFilename);

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

	//Create our initial solution
	vector<bool> vars;
	for (int i = 0; i < numVars; i++) {
		int randValue = rand() % 2;
		bool randBool;
		if (randValue == 0) { randBool = false; }
		else { randBool = true; }
		vars.push_back(randBool);
	}

	mySol = new Solution(vars);
	maxC = -1;
}

WalkSAT::~WalkSAT() {
	delete mySol;
}

int WalkSAT::getMaxFlips() {
	return MAX_FLIPS;
}

bool WalkSAT::isSolved(int flipCount) {
	bool isSolved = true;
	unsatClauses.clear();	//Reset unsatClauses

	for (int i = 0; i < clauses.size(); i++) {
		if (!clauses[i]->satisfy(mySol)) {
			unsatClauses.push_back(i);	//Maintain this to not waste this computation in randomly selecting later
			isSolved = false;
		}
	}

	if (isSolved) {
		cout << "WalkSAT has solved the problem in " << flipCount << " flips!" << endl;

		ofstream output;
		output.open("results.txt", ios_base::app);
		output << endl << "Solved with WalkSAT!" << endl;
		mySol->printSolution(output);
		output.close();
	}

	return isSolved;
}

void WalkSAT::walk() {
	//Randomly select an unsat clause to use
	int randClause = rand() % unsatClauses.size();
	Clause * clause = clauses[unsatClauses[randClause]];

	//Randomly choose whether to flip a random value in the model or to flip whichever symbol maximizes clauses sat
	int choice = rand() % 100;
	if (choice < RANDOM_WALK_PROB * 100) {
		//random walk
		vector<bool> & vars = mySol->getVarsRef();
		vector<int> & constraints = clause->getConstraints();
		int indexToFlip = abs(constraints[rand() % constraints.size()]);	//This is the variable to switch

		//Now flip that constraint in our solution
		if (vars[indexToFlip - 1] == true) {
			vars[indexToFlip - 1] = false;
		}
		else {
			vars[indexToFlip - 1] = true;
		}
	}
	//To DO!!!! : Make sure this does not change the actual solution for each test
	else {	//Flip whichever symbol in clause maximizes the # of satisfied clauses
		Solution * toDel = mySol;
		mySol = getBestSol();
		delete toDel;
	}
}

int WalkSAT::numClauseSat(Solution * sol) {
	int numSat = 0;

	for (int i = 0; i < clauses.size(); i++) {
		if (clauses[i]->satisfy(sol)) {
			numSat++;
		}
	}

	return numSat;
}

Solution * WalkSAT::getBestSol() {
	Solution * maxSol = NULL;
	int maxSat = -1;

	//Find out which variable flip results in the best solutions (max # of clauses sat)
	for (int i = 0; i < mySol->getVarsRef().size(); i++) {
		vector<bool> vars = mySol->getVarsCopy();	//We want a copy here! Not a reference!
		//Flip the var
		if (vars[i] == true) {
			vars[i] = false;
		}
		else {
			vars[i] = true;
		}
		Solution * tempSol = new Solution(vars);	//Create a new solution with the modified vars
		int numSat = numClauseSat(tempSol);	//Compute score
		tempSol->setFitness(numSat);
		if (numSat > maxSat) {
			maxSat = numSat;
			if (maxSol != NULL) { delete maxSol; }
			maxSol = tempSol;
		}
		else {
			delete tempSol;
		}
	}

	return maxSol;
}

Solution * WalkSAT::getSol() {
	return mySol;
}
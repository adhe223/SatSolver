#include "Solution.h"
#include <random>
#include <iostream>
#include <ctime>
using namespace std;

Solution::Solution(int numVarsIn) {
	for (int i = 1; i <= numVarsIn; i++) {
		int randomInt = rand() % 2;	//Random int that is 0 or 1
		if (randomInt > 0) {
			vars.push_back(i);	//push a variable on that is positive (asserted)
		}
		else {
			randomInt = randomInt - (2 * randomInt);
			vars.push_back(randomInt);
		}
	}

	fitness = -1;
}

Solution::Solution(const Solution & inSol) {
	vars = inSol.vars;
	fitness = inSol.fitness;
}

Solution::Solution(vector<bool> inVars) {
	vars = inVars;
	fitness = -1;
}

int Solution::getFitness() {
	return fitness;
}

void Solution::setFitness(int inFit) {
	fitness = inFit;
}

bool Solution::getIndex(int index) {
	return vars[index - 1];
}

vector<bool> Solution::getVars() {
	return vars;
}

//Easier for genetic algorithm to place this here
void Solution::mutateVars(double mutateProb) {
	for (int i = 0; i < vars.size(); i++) {
		int randInt = rand() % 100;
		if (randInt < mutateProb * 100) {
			//Flip the var
			if (vars[i]) { vars[i] = false; }
			else { vars[i] = true; }
		}
	}
}

void Solution::printSolution() {
	cout << endl;

	for (int i = 0; i < vars.size(); i++) {
		if (vars[i]) { cout << i + 1 << "   "; }
		else { cout << "-" << i + 1 << "   "; }
	}

	cout << endl;
}


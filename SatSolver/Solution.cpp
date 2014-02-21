#include "Solution.h"
#include <random>
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

int Solution::getFitness() {
	return fitness;
}

void Solution::setFitness(int inFit) {
	fitness = inFit;
}

int Solution::getIndex(int index) {
	return vars[index - 1];
}

/*
bool Solution::operator() (Solution & sol1, Solution & sol2) {
	return sol1.getFitness() > sol2.getFitness();
}
*/


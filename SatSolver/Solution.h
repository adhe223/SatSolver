#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>

class Solution {
public:
	Solution(int numVars);
	Solution(const Solution & inSol);

	int getFitness();
	void setFitness(int inFit);
	int getIndex(int index);

private:
	std::vector<bool> vars;
	int fitness;
};

#endif
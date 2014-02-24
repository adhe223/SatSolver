#include "GeneticSolver.h"
#include "Solution.h"
#include "helper.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
#include <random>
#include <ctime>
#include <iostream>
using namespace std;

GeneticSolver::GeneticSolver(Population * inPop, vector<Clause*> inClauses) {
	//Make a deep copy to work with
	myPop = new Population(*inPop);

	clauses = inClauses;
	stuckCount = 0;
}

void GeneticSolver::assignFitness() {
	myPop->assignGeneticFitness(clauses);
}

void GeneticSolver::selection() {
	//Select the best members of the population and remove the rest
	vector<Solution *> & sols = myPop->getSolutions();
	int popSize = sols.size();

	//All of our solutions are now in the vector, we need to sort
	sort(sols.begin(), sols.end(), mycompare);

	//Now we use the cutoff to prune the population
	int trimSize = POP_CUTOFF * sols.size();

	//Delete the remaining, but have a probability of POP_CUTOFF/5 of keeping a worse solution for diversity
	int toErase = sols.size() - 1;
	while (sols.size() > trimSize) {
		if (rand() % 101 > (POP_CUTOFF / 5) * 100) {
			//Solution * pToErase = sols[toErase];	//Memory Leak!!!! Why is this breaking?
			sols.erase(sols.begin() + toErase);
			//delete pToErase;	
		}

		toErase--;
	}

	//Refill the population with children
	while (sols.size() < popSize) {
		/*The crossing algorithm I use will randomly select two of the original parents and breed
		them into children. So 30% of the resulting pop will be the original parents and 70% will
		be children randomly bred from the parent pool.*/
		sols.push_back(cross(trimSize));
	}

	int foo = 5;

	//We now have a new population!
}

Solution * GeneticSolver::cross(int parentPoolSize) {
	//From my research I found that having more than two parents increases the probably of a fit child, so
	//I'll use 4 parents.
	vector<Solution *> & sols = myPop->getSolutions();

	//Randomly pick two parents from the original parent pool to breed a child
	Solution * parent0 = sols[rand() % parentPoolSize];
	Solution * parent1 = sols[rand() % parentPoolSize];
	Solution * parent2 = sols[rand() % parentPoolSize];
	Solution * parent3 = sols[rand() % parentPoolSize];
	if (parent0 == parent1) { return parent1; } //If same, just return

	//Now look at each constraint and randomly select which parent the child inherits it from
	vector<bool> buildChild;
	vector<bool> vars0 = parent0->getVarsRef();
	vector<bool> vars1 = parent1->getVarsRef();
	vector<bool> vars2 = parent2->getVarsRef();
	vector<bool> vars3 = parent3->getVarsRef();

	for (int i = 0; i < vars0.size(); i++) {
		int fromParent = rand() % 4;

		if (fromParent == 0) { buildChild.push_back(vars0[i]); }
		else if (fromParent == 1) { buildChild.push_back(vars1[i]); }
		else if (fromParent == 2) { buildChild.push_back(vars2[i]); }
		else { buildChild.push_back(vars3[i]); }
	}

	//Now create the new child and return it
	return new Solution(buildChild);
}

void GeneticSolver::mutate() {
	vector<Solution *> & sols = myPop->getSolutions();

	for (int i = 0; i < sols.size(); i++) {
		sols[i]->mutateVars(MUTATE_PROB);
	}
}

bool GeneticSolver::isSolved(int roundCount) {
	int numClauses = clauses.size();

	//If we have a solution with a fitness == to numClauses then the SAT problem is solved
	vector<Solution *> & sols = myPop->getSolutions();
	for (int i = 0; i < sols.size(); i++) {
		if (sols[i]->getFitness() == numClauses) {
			cout << "You have solved the SAT problem on round " << (stuckCount * STUCK_THRESHOLD) + roundCount << "!" << endl;
			sols[i]->printSolution();
			return true;
		}
	}

	return false;
}

int GeneticSolver::getTopFitness() {
	return myPop->getSolutions()[0]->getFitness();
}

bool GeneticSolver::isStuck(int currCount) {
	if (currCount > STUCK_THRESHOLD) {
		stuckCount++;
		cout << endl << "Got stuck, resetting the population." << endl;
		return true;
	}
	else {
		return false;
	}
}

int GeneticSolver::getStuckCount() {
	return stuckCount;
}

int GeneticSolver::getStuckLimit() {
	return STUCK_LIMIT;
}

void GeneticSolver::genocide(Population * inPop) {
	//Make a deep copy to work with
	myPop = new Population(*inPop);
}
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
using namespace std;

GeneticSolver::GeneticSolver(Population * inPop, string inFilename) {
	//Make a deep copy to work with
	myPop = new Population(*inPop);

	filename = inFilename;
	readClauses();
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
	vector<bool> vars0 = parent0->getVars();
	vector<bool> vars1 = parent1->getVars();
	vector<bool> vars2 = parent2->getVars();
	vector<bool> vars3 = parent3->getVars();

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

//							***TO DO!!!!***
/*At the moment can only handle problems with a solution. Need to add the ability to recognize that it is
stuck or that there is no solution.*/
Solution * GeneticSolver::isSolved() {
	int numClauses = clauses.size();

	//If we have a solution with a fitness == to numClauses then the SAT problem is solved
	vector<Solution *> & sols = myPop->getSolutions();
	for (int i = 0; i < sols.size(); i++) {
		if (sols[i]->getFitness() == numClauses) {
			return sols[i];
		}
	}

	return NULL;
}

int GeneticSolver::getTopFitness() {
	return myPop->getSolutions()[0]->getFitness();
}
#include "GeneticSolver.h"
using namespace std;

GeneticSolver::GeneticSolver(Population * inPop, string inFilename) {
	//Make a deep copy to work with
	myPop = new Population(*inPop);

	filename = inFilename;
}

void GeneticSolver::assignFitness(string filename) {
	myPop->assignGeneticFitness(filename);
}
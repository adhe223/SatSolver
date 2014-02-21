#include "Population.h"
#include "GeneticSolver.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int main() {
	Population * pop = new Population("bla.txt", 100);
	GeneticSolver * gs = new GeneticSolver(pop, "bla.txt");
	gs->readClauses();
	gs->assignFitness();
	gs->selection();

	return 0;
}
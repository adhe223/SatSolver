#include "Population.h"
#include "GeneticSolver.h"
#include "Solution.h"
#include <random>
#include <ctime>
#include <iostream>
#include <fstream>
#include <Windows.h>
using namespace std;

//Size of population
const int POP_SIZE = 100;

//Genetic Algorithm tweaks are found in its h file private members
int main() {
	srand(time(NULL));

	Solution * solution = NULL;

	//Test harness
	ifstream infile;
	infile.open("files.txt");
	string filename;
	while (getline(infile, filename)) {

		Solver * solver = new Solver(filename);

		//Data Gathering purposes
		ofstream output;
		output.open("results.txt", ios_base::app);
		output << endl << endl << endl << "File: " << filename << endl;
		output.close();

		solver->readClauses();

		for (int i = 0; i < 10; i++) {
			solver->geneticSolve(POP_SIZE);
			solver->walkSolve();
		}

		delete solver;
	}

	return 0;
}
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
const int NUM_TESTS = 10;

//Genetic Algorithm tweaks are found in its h file private members
int main() {
	srand(time(NULL));

	Solution * solution = NULL;

	//Test harness
	ifstream infile;

	//If non existant file or points to wrong folder nothing will happen
	infile.open("files.txt");	//Place the files to read here. Will read to end of file
	string filename;
	while (getline(infile, filename)) {

		Solver * solver = new Solver(filename);

		//Data Gathering purposes
		ofstream output;
		output.open("results.txt", ios_base::app);	//Outputs to this file
		output << endl << endl << endl << "File: " << filename << endl;
		output.close();

		solver->readClauses();

		for (int i = 0; i < NUM_TESTS; i++) {
			solver->geneticSolve(POP_SIZE);
			solver->walkSolve();
		}

		delete solver;
	}

	cin.ignore(200, '\n');
	return 0;
}
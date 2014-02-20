#include "Solver.h"
#include "Population.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

Solver::Solver(string inFilename, int popSize) {
	//initialize the parameters we will use to create our population
	int numVars = -1;

	//Read in the file and find how many vairiables there are
	bool loop = true;
	string line;
	string filename = inFilename;
	ifstream inStream(filename);

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

	//Now construct the population with the correct number of variables
	pop = new Population(numVars, popSize);
}
#include "Clause.h"
#include <math.h>
using namespace std;

Clause::Clause(vector<int> inConstraints) {
	constraints = inConstraints;
}

bool Clause::satisfy(Solution * toCheck) {
	bool satisfy = false;

	for (int i = 0; i < constraints.size(); i++) {
		if (constraints[i] > 0 && toCheck->getIndex(abs(constraints[i])) == true) {	//Test if the vars do not match
			satisfy = true;
		}
		else if (constraints[i] < 0 && toCheck->getIndex(abs(constraints[i])) == false) {
			satisfy = true;
		}
	}

	return satisfy;
}

vector<int> & Clause::getConstraints() {
	return constraints;
}
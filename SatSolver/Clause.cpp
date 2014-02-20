#include "Clause.h"
using namespace std;

Clause::Clause(vector<int> inConstraints) {
	constraints = inConstraints;
}

bool Clause::satisfy(Solution * toCheck) {
	bool satisfy = true;

	for (int i = 0; i < constraints.size(); i++) {
		if (constraints[i] > 0 && toCheck->getIndex[abs(constraints[i])] == 0) {	//Test if the vars do not match
			satisfy = false;
		}
		else if (constraints[i] < 0 && toCheck->getIndex[abs(constraints[i])] > 0) {
			satisfy = false;
		}
	}

	return satisfy;
}
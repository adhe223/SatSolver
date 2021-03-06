#ifndef CLAUSE_H
#define CLAUSE_H
#include "Solution.h"
#include <vector>

class Clause {
public:
	Clause(std::vector<int> inConstraints);

	bool satisfy(Solution * toCheck);
	std::vector<int> & getConstraints();

private:
	std::vector<int> constraints;
};

#endif
#include "helper.h"
using namespace std;

bool mycompare(Solution * sol1, Solution * sol2) {
	return (sol1->getFitness() > sol2->getFitness());
}
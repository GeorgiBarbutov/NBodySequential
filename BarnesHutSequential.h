#ifndef BARNESHUTSEQUENTIAL_H         
#define BARNESHUTSEQUENTIAL_H        

#include "Body.h"
#include "Node.h"

class BarnesHutSequential {
private:
	Node* BuildTree(Body* randomBodies, int bodyCount);
public:
	void compute(Body* randomBodies, int bodyCount, double maxT, double dt, double theta);
};

#endif
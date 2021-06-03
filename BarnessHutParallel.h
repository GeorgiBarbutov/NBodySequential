#ifndef BARNESHUTPARALLEL_H         
#define BARNESHUTPARALLEL_H        

#include "Body.h"
#include "Node.h"

class BarnesHutParallel {
private:
	int threadCount;

	Node* BuildTree(Body* randomBodies, int bodyCount);
public:
	BarnesHutParallel(int threadCount);

	int getThreadCount();
	void setThreadCount(int threadCount);

	void compute(Body* randomBodies, int bodyCount, double maxT, double dt, double theta);
};

#endif
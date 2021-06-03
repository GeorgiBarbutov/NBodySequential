#include "BarnesHutParallel.h"
#include "Body.h"
#include <omp.h>
#include <iostream>

using namespace std;

const double MIN_X = -10000;
const double MAX_X = 10000;
const double MIN_Y = -10000;
const double MAX_Y = 10000;
const double G = 6.6743e-11;

BarnesHutParallel::BarnessHutParallel(int threadCount) {
	this->threadCount = threadCount;
}

int BarnesHutParallel::getThreadCount() {
	return this->threadCount;
}
void BarnesHutParallel::setThreadCount(int threadCount) {
	this->threadCount = threadCount;
}

void BarnesHutParallel::compute(Body* randomBodies, int bodyCount, double maxT, double dt, double theta) {
	for (double i = 0.0; i < maxT; i += dt)
	{
		Node* treeRoot = BuildTree(randomBodies, bodyCount);

		treeRoot->calculateMassDistribution();

		for (int j = 0; j < bodyCount; j++)
		{
			Point force = treeRoot->calculateForce(randomBodies[j], theta, G);
			randomBodies[j].updateVelocity(dt, force);
			randomBodies[j].updatePosition(dt);
		}
		delete treeRoot;
	}
}

Node* BarnesHutParallel::BuildTree(Body* randomBodies, int bodyCount)
{
	double start = omp_get_wtime();

	Node* treeRoot = new Node(MIN_X, MIN_Y, MAX_X, MAX_Y, true);
	treeRoot->setBodyCount(bodyCount);
	treeRoot->setIsExternal(false);

	Node NW = Node(MIN_X, (MAX_Y + MIN_Y) / 2, (MAX_X + MIN_X) / 2, MAX_Y);
	Node NE = Node((MAX_X + MIN_X) / 2, (MAX_Y + MIN_Y) / 2, MAX_X, MAX_Y);
	Node SW = Node(MIN_X, MIN_Y, (MAX_X + MIN_X) / 2, (MAX_Y + MIN_Y) / 2);
	Node SE = Node((MAX_X + MIN_X) / 2, MIN_Y, MAX_X, (MAX_Y + MIN_Y) / 2);
	Node* level2 = new Node[4]{ NW, NE, SW, SE };

	int threadNumber;
	if (this->threadCount > 4) {
		threadNumber = 4;
	}
	omp_set_num_threads(threadNumber);
#pragma omp parallel 
	{
		int id = omp_get_thread_num();
		int tNumber = omp_get_num_threads(); 
		if (tNumber == 4)
		{
			Node node = level2[id];
			for (int i = 0; i < bodyCount; i++)
			{
				if (node.isBodyInside(randomBodies[i]))
				{
					node.insert(randomBodies[i]);
				}
			}
		}
		else if (tNumber == 2)
		{
			Node node1 = level2[id];
			Node node2 = level2[id + 2];
			for (int i = 0; i < bodyCount; i++)
			{
				if (node1.isBodyInside(randomBodies[i]))
				{
					node1.insert(randomBodies[i]);
				}
				else if (node2.isBodyInside(randomBodies[i]))
				{
					node2.insert(randomBodies[i]);
				}
			}
		}
	}
	treeRoot->setNE(&NE);
	treeRoot->setNW(&NW);
	treeRoot->setSW(&SW);
	treeRoot->setSE(&SE);

	double end = omp_get_wtime();
	//cout << end - start << "\n";
	return treeRoot;
}
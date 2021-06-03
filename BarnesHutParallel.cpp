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

BarnesHutParallel::BarnesHutParallel(int threadCount) {
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

		calculateMassDistribution(treeRoot);

		omp_set_num_threads(this->threadCount);
#pragma omp parallel for
		for (int j = 0; j < bodyCount; j++)
		{
			Point force = treeRoot->calculateForce(randomBodies[j], theta, G);
			randomBodies[j].updateVelocity(dt, force);
			randomBodies[j].updatePosition(dt);
		}

		delete treeRoot;
	}
}

void BarnesHutParallel::calculateMassDistribution(Node* treeRoot)
{
	Node* NW = treeRoot->getNW();
	Node* NE = treeRoot->getNE();
	Node* SW = treeRoot->getSW();
	Node* SE = treeRoot->getSE();
	Node** level2 = new Node * [4]{ NW, NE, SW, SE };

	double totalMass = 0.0;
	Point centerMass = Point(0, 0);

	omp_set_num_threads(this->threadCount);
#pragma omp parallel for
	for (int j = 0; j < 4; j++)
	{
		if (level2[j] != nullptr)
		{
			level2[j]->calculateMassDistribution();
		}
	}

	for (int j = 0; j < 4; j++)
	{
		if (level2[j] != nullptr)
		{
			totalMass += level2[j]->getTotalMass();
			centerMass = centerMass + (level2[j]->getCenterMass() * level2[j]->getTotalMass());
		}
	}
	treeRoot->setTotalMass(totalMass);
	treeRoot->setCenterMass(centerMass / totalMass);
}

Node* BarnesHutParallel::BuildTree(Body* randomBodies, int bodyCount)
{
	Node* treeRoot = new Node(MIN_X, MIN_Y, MAX_X, MAX_Y, true);
	for (int i = 0; i < bodyCount; i++)
	{
		treeRoot->insert(randomBodies[i]);
	}

	return treeRoot;
}
#include "Body.h"
#include "BarnesHutSequential.h"
#include <iostream>

using namespace std;

const double MIN_X = -10000;
const double MAX_X = 10000;
const double MIN_Y = -10000;
const double MAX_Y = 10000;
const double G = 6.6743e-11;

void BarnesHutSequential::compute(Body* randomBodies, int bodyCount, double maxT, double dt, double theta) {
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

Node* BarnesHutSequential::BuildTree(Body* randomBodies, int bodyCount)
{
	Node* treeRoot = new Node(MIN_X, MIN_Y, MAX_X, MAX_Y, true);
	for (int i = 0; i < bodyCount; i++)
	{
		treeRoot->insert(randomBodies[i]);
	}
	return treeRoot;
}
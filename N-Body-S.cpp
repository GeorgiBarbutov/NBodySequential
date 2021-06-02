#include <iostream>
#include <random>
#include "point.h"  
#include "Node.h"
#include "Body.h"

using namespace std;

const double MIN_X = -10000;
const double MAX_X = 10000;
const double MIN_Y = -10000;
const double MAX_Y = 10000;
const double G = 6.6743e-11;
const double theta = 1;
const double dt = 0.1;

double getRandomDouble(double min, double max)
{
	random_device rd;
	default_random_engine eng(rd());
	uniform_real_distribution<double> distr(min, max);

	return distr(eng);
};

Body* generateRandomBodies(int count) 
{

	Body* bodies = new Body[count];

	for (int i = 0; i < count; i++)
	{
		Point newPoint = Point(getRandomDouble(MIN_X /100, MAX_X / 100), getRandomDouble(MIN_Y / 100, MAX_Y / 100));
		Point initial_velocity = Point(getRandomDouble(-1, 1), getRandomDouble(-1, 1));
		bodies[i] = Body(newPoint, getRandomDouble(0, 10), initial_velocity);
	}

	return bodies;
}

Node* BuildTree(Body* randomBodies, int bodyCount) 
{
	Node* treeRoot = new Node(MIN_X, MIN_Y, MAX_X, MAX_Y, true);
	for (int i = 0; i < bodyCount; i++)
	{
		treeRoot->insert(randomBodies[i]);
	}

	return treeRoot;
}

void BH(Body* randomBodies, int bodyCount, double maxT)
{
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

int main() 
{
	int bodyCount = 100;
	double maxT = 1000;

	Body* randomBodies = generateRandomBodies(bodyCount);

	for (int i = 0; i < 100; i++)
	{
		cout << i << ": x: " << randomBodies[i].getPoint().getX() << "y: " << randomBodies[i].getPoint().getY() << "\n";
	}

	BH(randomBodies, bodyCount, maxT);

	for (int i = 0; i < 100; i++)
	{
		cout << i << ": x: " << randomBodies[i].getPoint().getX() << "y: " << randomBodies[i].getPoint().getY() << "\n";
	}
	
	return 0;
};
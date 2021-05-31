#include <iostream>
#include <random>
#include "point.h"  
#include "Node.h"

using namespace std;

const double MIN_X = 0;
const double MAX_X = 100;
const double MIN_Y = 0;
const double MAX_Y = 100;

double getRandomDouble()
{
	random_device rd;
	default_random_engine eng(rd());
	uniform_real_distribution<double> distr(MIN_X, MAX_X);

	return distr(eng);
};

Point* generateRandomPoints(int count) {

	Point* points = new Point[count];

	for (int i = 0; i < count; i++) {
		points[i] = Point(getRandomDouble(), getRandomDouble(), getRandomDouble());
	}

	return points;
}

Node* BuildTree(Point* randomPoints, int pointCount) {
	Node* treeRoot = new Node(MIN_X, MIN_Y, MAX_X, MAX_Y);
	for (int i = 0; i < pointCount; i++)
	{
		treeRoot->insert(&randomPoints[i]);
	}

	return treeRoot;
}

void BH(Point* randomPoints, int pointCount) {
	Node* treeRoot = BuildTree(randomPoints, pointCount);

	treeRoot->calculateMassDistribution();
}

int main() {
	int pointCount = 100;

	Point* randomPoints = generateRandomPoints(pointCount);

	//Point a[] = { Point(10, 10, 1), Point(80, 10, 2), Point(80, 80, 3), Point(10, 80, 4), Point(70, 10, 5), Point(10, 60, 6),  Point(70, 80, 7), Point(20, 10, 8), Point(90, 10, 9), Point(82, 80, 10), };

	//randomPoints = a;

	BH(randomPoints, pointCount);

	return 0;
};
#include "node.h"   
#include <iostream>

using namespace::std;

Node::Node() {
	this->isRoot = false;
	this->isExternal = true;
	this->NW = NULL;
	this->NE = NULL;
	this->SW = NULL;
	this->SE = NULL;
	this->existingPoint = NULL;
	this->minX = 0.0;
	this->minY = 0.0;
	this->maxX = 0.0;
	this->maxY = 0.0;
	this->totalMass = 0.0;
	this->centerX = 0.0;
	this->centerY = 0.0;
	this->centerMassX = 0.0;
	this->centerMassY = 0.0;
	this->pointCount = 0;
}
Node::Node(double minX, double minY, double maxX, double maxY, bool isRoot) {
	this->isRoot = isRoot;
	this->isExternal = true;
	this->NW = NULL;
	this->NE = NULL;
	this->SW = NULL;
	this->SE = NULL;
	this->existingPoint = NULL;
	this->minX = minX;
	this->minY = minY;
	this->maxX = maxX;
	this->maxY = maxY;
	this->totalMass = 0.0;
	this->centerX = (this->maxX + this->minX) / 2;
	this->centerY = (this->maxY + this->minY) / 2;
	this->centerMassX = 0.0;
	this->centerMassY = 0.0;
	this->pointCount = 0;
}

double Node::getMinX() {
	return this->minX;
}
double Node::getMinY() {
	return this->minY;
}
double Node::getMaxX() {
	return this->maxX;
}
double Node::getMaxY() {
	return this->maxY;
}
double Node::getTotalMass() {
	return this->totalMass;
}
double Node::getCenterX() {
	return this->centerX;
}
double Node::getCenterY() {
	return this->centerY;
}
double Node::getCenterMassX() {
	return this->centerMassX;
}
double Node::getCenterMassY() {
	return this->centerMassY;
}
int Node::getPointCount(){
	return this->pointCount;
}
Node* Node::getNW() {
	return this->NW;
}
Node* Node::getNE() {
	return this->NE;
}
Node* Node::getSW() {
	return this->SW;
}
Node* Node::getSE() {
	return this->SE;
}
Point* Node::getExistingPoint() {
	return this->existingPoint;
}
bool Node::getIsRoot() {
	return this->isRoot;
}
bool Node::getIsExternal() {
	return this->isExternal;
}
void Node::setMinX(double minX) {
	this->minX = minX;
}
void Node::setMinY(double minY) {
	this->minY = minY;
}
void Node::setMaxX(double maxX) {
	this->maxX = maxX;
}
void Node::setMaxY(double maxY) {
	this->maxY = maxY;
}
void Node::setTotalMass(double totalMass) {
	this->totalMass = totalMass;
}
void Node::setCenterX(double centerX) {
	this->centerX = centerX;
}
void Node::setCenterY(double centerY) {
	this->centerY = centerY;
}
void Node::setCenterMassX(double centerMassX) {
	this->centerMassX = centerMassX;
}
void Node::setCenterMassY(double centerMassY) {
	this->centerMassY = centerMassY;
}
void Node::setPointCount(int pointCount) {
	this->pointCount = pointCount;
}
void Node::setNW(Node* NW) {
	this->NW = NW;
}
void Node::setNE(Node* NE) {
	this->NE = NE;
}
void Node::setSW(Node* SW) {
	this->SW = SW;
}
void Node::setSE(Node* SE) {
	this->SE = SE;
}
void Node::setExistingPoint(Point* point) {
	this->existingPoint = point;
}
void Node::setIsRoot(bool isRoot) {
	this->isRoot= isRoot;
}
void Node::setIsExternal(bool isExternal) {
	this->isExternal= isExternal;
}

Node* Node::getQuadrant(Point* point) {
	if (point->getX() > this->minX && point->getX() < centerX && point->getY() > this->minY && point->getY() < centerY) {
		if (NW == NULL) {
			NW = new Node(this->minX, this->minY, centerX, centerY);
		}
		return NW;
	}
	else if (point->getX() > this->minX && point->getX() > centerX && point->getY() > this->minY && point->getY() < centerY) {
		if (NE == NULL) {
			NE = new Node(centerX, this->minY, this->maxX, centerY);
		}
		return NE;
	}
	else if (point->getX() > this->minX && point->getX() < centerX && point->getY() > this->minY && point->getY() > centerY) {
		if (SW == NULL) {
			SW = new Node(this->minX, centerY, centerX, this->maxY);
		}
		return SW;
	}
	else if (point->getX() > this->minX && point->getX() > centerX && point->getY() > this->minY && point->getY() > centerY) {
		if (SE == NULL) {
			SE = new Node(centerX, centerY, this->maxX, this->maxY);
		}
		return SE;
	}

	return NULL;
}

void Node::insert(Point* point) {
	if (this->pointCount > 1) {
		Node* quadrant = getQuadrant(point);
		quadrant->insert(point);
	}
	else if (this->pointCount == 1) {
		Node* quadrant = getQuadrant(this->existingPoint);
		quadrant->insert(this->existingPoint);
		Node* quadrant2 = getQuadrant(point);
		quadrant2->insert(point);

		this->isExternal = false;
	} else {
		setExistingPoint(point);
	}

	this->pointCount++;
}

void Node::addMassAndCenterMass(Node* quadrant) {
	if (quadrant != NULL) {
		quadrant->calculateMassDistribution();
		this->totalMass += quadrant->getTotalMass();
		this->centerMassX += quadrant->getCenterMassX() * quadrant->getTotalMass();
		this->centerMassY += quadrant->getCenterMassY() * quadrant->getTotalMass();
	}
}

void Node::calculateMassDistribution() {
	if (this->pointCount == 1) {
		this->totalMass = this->existingPoint->getMass();
		this->centerMassX = this->existingPoint->getX();
		this->centerMassY = this->existingPoint->getY();
	}
	else {
		this->totalMass = 0;
		this->centerMassX = 0;
		this->centerMassY = 0;

		addMassAndCenterMass(NW);
		addMassAndCenterMass(NE);
		addMassAndCenterMass(SW);
		addMassAndCenterMass(SE);

		this->centerMassX /= this->totalMass;
		this->centerMassY /= this->totalMass;
	}
}

Point* Node::appliedForce(Point* targetPoint, Point* influencePoint)
{
	Point* force = new Point(0, 0);

	if (targetPoint == influencePoint)
		return force;

	double x1 = targetPoint->getX();
	double x2 = influencePoint->getX();
	double y1 = targetPoint->getY();
	double y2 = influencePoint->getY();
	double m1 = targetPoint->getMass();
	double m2 = influencePoint->getMass();

	double r = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	if (r > 0)
	{
		double k = (m1 * m2) / (r * r * r);

		force->setX(force->getX() + k * (x2 - x1));
		force->setY(force->getY() + k * (y2 - y1));
	}
	else
	{
		force->setX(0);
		force->setY(0);
	}

	return force;
}
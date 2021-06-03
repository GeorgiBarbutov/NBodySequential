#include "node.h"   
#include <iostream>
#include "Body.h"

using namespace::std;

Node::Node() 
{
	this->isRoot = false;
	this->isExternal = true;
	this->NW = nullptr;
	this->NE = nullptr;
	this->SW = nullptr;
	this->SE = nullptr;
	this->minX = 0.0;
	this->minY = 0.0;
	this->maxX = 0.0;
	this->maxY = 0.0;
	this->totalMass = 0.0;
	this->center = Point(0, 0);
	this->centerMass = Point(0, 0);
	this->bodyCount = 0;
}
Node::Node(double minX, double minY, double maxX, double maxY, bool isRoot) 
{
	this->isRoot = isRoot;
	this->isExternal = true;
	this->NW = nullptr;
	this->NE = nullptr;
	this->SW = nullptr;
	this->SE = nullptr;
	this->minX = minX;
	this->minY = minY;
	this->maxX = maxX;
	this->maxY = maxY;
	this->totalMass = 0.0;
	this->center = Point((this->maxX + this->minX) / 2, (this->maxY + this->minY) / 2);
	this->centerMass = Point(0, 0);
	this->bodyCount = 0;
}

Node::~Node()
{
	delete NW;
	delete NE;
	delete SW;
	delete SE;
}

double Node::getMinX()
{
	return this->minX;
}
double Node::getMinY() 
{
	return this->minY;
}
double Node::getMaxX() 
{
	return this->maxX;
}
double Node::getMaxY()
{
	return this->maxY;
}
double Node::getTotalMass()
{
	return this->totalMass;
}
Point Node::getCenter()
{
	return this->center;
}
Point Node::getCenterMass()
{
	return this->centerMass;
}
int Node::getBodyCount()
{
	return this->bodyCount;
}
Node* Node::getNW()
{
	return this->NW;
}
Node* Node::getNE()
{
	return this->NE;
}
Node* Node::getSW()
{
	return this->SW;
}
Node* Node::getSE()
{
	return this->SE;
}
Body Node::getExistingBody()
{
	return this->existingBody;
}
bool Node::getIsRoot()
{
	return this->isRoot;
}
bool Node::getIsExternal()
{
	return this->isExternal;
}
void Node::setMinX(double minX)
{
	this->minX = minX;
}
void Node::setMinY(double minY)
{
	this->minY = minY;
}
void Node::setMaxX(double maxX)
{
	this->maxX = maxX;
}
void Node::setMaxY(double maxY)
{
	this->maxY = maxY;
}
void Node::setTotalMass(double totalMass)
{
	this->totalMass = totalMass;
}
void Node::setCenter(Point& center)
{
	this->center = center;
}
void Node::setCenterMass(Point centerMass)
{
	this->centerMass = centerMass;
}
void Node::setBodyCount(int bodyCount)
{
	this->bodyCount = bodyCount;
}
void Node::setNW(Node* NW)
{
	this->NW = NW;
}
void Node::setNE(Node* NE)
{
	this->NE = NE;
}
void Node::setSW(Node* SW)
{
	this->SW = SW;
}
void Node::setSE(Node* SE)
{
	this->SE = SE;
}
void Node::setExistingBody(Body& body)
{
	this->existingBody = body;
}
void Node::setIsRoot(bool isRoot)
{
	this->isRoot = isRoot;
}
void Node::setIsExternal(bool isExternal)
{
	this->isExternal = isExternal;
}

//return the quadrant in which the body is found
Node* Node::getQuadrant(Body& body)
{
	double bx = body.getPoint().getX();
	double by = body.getPoint().getY();
	double cx = this->center.getX();
	double cy = this->center.getY();

	if (bx < cx && by >= cy)
	{
		if (NW == NULL)
		{
			NW = new Node(this->minX, cy, cx, this->maxY);
		}
		return NW;
	}
	else if (bx >= cx && by >= cy)
	{
		if (NE == NULL)
		{
			NE = new Node(cx, cy, this->maxX, this->maxY);
		}
		return NE;
	}
	else if (bx < cx && by < cy)
	{
		if (SW == NULL)
		{
			SW = new Node(this->minX, this->minY, cx, cy);
		}
		return SW;
	}
	else if (bx >= cx && by < cy)
	{
		if (SE == NULL)
		{
			SE = new Node(cx, this->minY, this->maxX, cy);
		}
		return SE;
	}

	return NULL;
}

//insert a new body in the quadtree
void Node::insert(Body& body)
{
	if (this->bodyCount > 1)
	{
		Node* quadrant = getQuadrant(body);
		quadrant->insert(body);
	}
	else if (this->bodyCount == 1)
	{
		Node* quadrant = getQuadrant(this->existingBody);
		quadrant->insert(this->existingBody);
		Node* quadrant2 = getQuadrant(body);
		quadrant2->insert(body);

		this->isExternal = false;
	}
	else
	{
		setExistingBody(body);
	}

	this->bodyCount++;
}

void Node::addMassAndCenterMass(Node* quadrant)
{
	if (quadrant != nullptr)
	{
		quadrant->calculateMassDistribution();
		this->totalMass += quadrant->getTotalMass();
		this->centerMass = this->centerMass + (quadrant->getCenterMass() * quadrant->getTotalMass());
	}
}

//calculate mass and center of mass recursively
void Node::calculateMassDistribution()
{
	if (this->isExternal)
	{
		this->totalMass = this->existingBody.getMass();
		this->centerMass.set(this->existingBody.getPoint().getX(), this->existingBody.getPoint().getY());
	}
	else
	{
		this->totalMass = 0;
		this->centerMass.set(0, 0);

		addMassAndCenterMass(NW);
		addMassAndCenterMass(NE);
		addMassAndCenterMass(SW);
		addMassAndCenterMass(SE);

		this->centerMass = this->centerMass / this->totalMass;
	}
}

//calculate force exerted from influence to target
Point Node::appliedForce(Body& target, Point& influence, double influenceMass, double G)
{
	Point direction = influence - target.getPoint();
	double r = direction.length();
	direction.normalize();

	Point force = Point();
	if (target.getPoint() == influence)
	{
		return force;
	}

	double F = G * target.getMass() * influenceMass / (r * r);
	force = direction * F + force;

	return force;
}

Point Node::getChildAppliedForce(Node* quadrant, Body& target, double theta, double G)
{
	Point force = Point();

	if (quadrant != nullptr)
	{
		force = quadrant->calculateForce(target, theta, G);
	}

	return force;
}

//calculates force from all bodies to target recursively over the quadtree
Point Node::calculateForce(Body& target, double theta, double G)
{
	Point force = Point();

	//size of quadrant
	double d = this->maxX - this->minX;
	//targetPoint distance from center of mass
	double r = target.getPoint().distance(this->centerMass);

	if (this->isExternal)
	{
		Point existingBodyPoint = this->existingBody.getPoint();
		force = appliedForce(target, existingBodyPoint, this->existingBody.getMass(), G);
	}
	else if (d / r <= theta) // calculate force of all bodies in an internal as a single body
	{
		force = appliedForce(target, this->centerMass, this->totalMass, G);
	}
	else
	{
		force = force + getChildAppliedForce(this->NW, target, theta, G);
		force = force + getChildAppliedForce(this->NE, target, theta, G);
		force = force + getChildAppliedForce(this->SW, target, theta, G);
		force = force + getChildAppliedForce(this->SE, target, theta, G);
	}

	return force;
}

bool Node::isBodyInside(Body& body) {
	return body.getPoint().getX() >= this->minX && body.getPoint().getX() < this->maxX 
		&& body.getPoint().getY() >= this->minY && body.getPoint().getY() < this->maxY;
}
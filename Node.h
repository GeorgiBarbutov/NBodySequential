#ifndef NODE_H         
#define NODE_H         

#include "Point.h"
#include "Body.h"

class Node 
{
private:
	bool isRoot;
	bool isExternal;
	Node* NW;
	Node* NE;
	Node* SW;
	Node* SE;
	double minX;
	double minY;
	double maxX;
	double maxY;
	Point center;
	double totalMass;
	Point centerMass;
	int bodyCount;
	Body existingBody;

	Node* getQuadrant(Body& body);
	void addMassAndCenterMass(Node* quadrant);
	Point appliedForce(Body& target, Point& influence, double influenceMass, double G);
	Point getChildAppliedForce(Node* quadrant, Body& targetBody, double theta, double G);

public:
	Node();
	Node(double minX, double minY, double maxX, double maxY, bool isRoot = false);
	~Node();

	double getMinX();
	double getMinY();
	double getMaxX();
	double getMaxY();
	double getTotalMass(); 
	Point getCenter();
	Point getCenterMass();
	int getBodyCount();
	Node* getNW();
	Node* getNE();
	Node* getSW();
	Node* getSE();
	Body getExistingBody();
	bool getIsRoot();
	bool getIsExternal();
	void setMinX(double minX);
	void setMinY(double minY);
	void setMaxX(double maxX);
	void setMaxY(double maxY);
	void setTotalMass(double totalMass);
	void setCenter(Point& center);
	void setCenterMass(Point& centerMass);
	void setBodyCount(int bodyCount);
	void setNW(Node* NW);
	void setNE(Node* NE);
	void setSW(Node* SW);
	void setSE(Node* SE);
	void setExistingBody(Body& body);
	void setIsRoot(bool isRoot);
	void setIsExternal(bool isExternal);

	void insert(Body& point);
	void calculateMassDistribution();
	Point calculateForce(Body& targetBody, double theta, double G);
};

#endif

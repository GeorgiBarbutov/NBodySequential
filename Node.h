#include "Point.h"
#ifndef NODE_H         
#define NODE_H         

class Node {

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
	double centerX;
	double centerY;
	double totalMass;
	double centerMassX;
	double centerMassY;
	int pointCount;
	Point* existingPoint;

	Node* getQuadrant(Point* point);
	void addMassAndCenterMass(Node* quadrant);
	Point* appliedForce(Point* target, Point* influence);

public:
	Node();
	Node(double minX, double minY, double maxX, double maxY, bool isRoot = false);

	double getMinX();
	double getMinY();
	double getMaxX();
	double getMaxY();
	double getTotalMass();
	double getCenterX();
	double getCenterY();
	double getCenterMassX();
	double getCenterMassY();
	int getPointCount();
	Node* getNW();
	Node* getNE();
	Node* getSW();
	Node* getSE();
	Point* getExistingPoint();
	bool getIsRoot();
	bool getIsExternal();
	void setMinX(double minX);
	void setMinY(double minY);
	void setMaxX(double maxX);
	void setMaxY(double maxY);
	void setTotalMass(double totalMass);
	void setCenterX(double centerX);
	void setCenterY(double centerY);
	void setCenterMassX(double centerMassX);
	void setCenterMassY(double centerMassY);
	void setPointCount(int pointCount);
	void setNW(Node* NW);
	void setNE(Node* NE);
	void setSW(Node* SW);
	void setSE(Node* SE);
	void setExistingPoint(Point* point);
	void setIsRoot(bool isRoot);
	void setIsExternal(bool isExternal);

	void insert(Point* point);
	void calculateMassDistribution();
};

#endif

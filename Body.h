#ifndef BODY_H         
#define BODY_H         

#include "Point.h"

class Body {

private:
	Point point;
	double mass;
	Point velocity;

public:
	Body();
	Body(Point& point, double mass, Point& velocity);
	Point getPoint();
	double getMass();
	Point getVelocity();
	void setPoint(Point& point);
	void setMass(double mass);
	void setVelocity(Point& velocity);

	void updateVelocity(double dt, Point& force);
	void updatePosition(double dt);

	Point operator-(const Body& body);
	bool operator==(const Body& body);
};

#endif
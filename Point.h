#ifndef POINT_H         
#define POINT_H         

class Point {

private:
	double x;
	double y;
	double mass;

public:
	Point();
	Point(double x, double y, double mass);
	Point(double x, double y);
	double getX();
	double getY();
	double getMass();
	void setX(double x);
	void setY(double y);
	void setMass(double mass);
};

#endif
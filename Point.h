#ifndef POINT_H         
#define POINT_H         

class Point
{
private:
	double x;
	double y;

public:
	Point();
	Point(double x, double y);
	double getX();
	double getY();
	void setX(double x);
	void setY(double y);
	void set(double x, double y);

	double length();
	double distance(Point& point);
	void normalize();

	bool operator==(const Point& point);
	Point operator+(const Point& point);
	Point operator-(const Point& point);
	Point operator*(const double coeficient);
	Point operator/(const double coeficient);
};

#endif
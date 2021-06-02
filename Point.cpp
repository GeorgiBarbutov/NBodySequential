#include "point.h"   
#include <iostream>

Point::Point() 
{
	this->x = 0.0;
	this->y = 0.0;
}

Point::Point(double x, double y)
{
	this->x = x;
	this->y = y;
}

double Point::getX() 
{
	return this->x;
}
double Point::getY() 
{
	return this->y;
}
void Point::setX(double x) 
{
	this->x = x;
}
void Point::setY(double y) 
{
	this->y = y;
}
void Point::set(double x, double y)
{
	this->x = x;
	this->y = y;
}

double Point::length()
{
	Point empty = Point();
	return this->distance(empty);
}

double Point::distance(Point& point)
{
	return sqrt((this->x - point.getX()) * (this->x - point.getX()) + (this->y - point.getY()) * (this->y - point.getY()));
}

void Point::normalize()
{
	double lengthOf = this->length();
	this->x /= lengthOf;
	this->y /= lengthOf;
}

bool Point::operator==(const Point& point)
{
	return this->x == point.x && this->y == point.y;
}

Point Point::operator+(const Point& point)
{
	return Point(this->x + point.x, this->y + point.y);
}

Point Point::operator-(const Point& point)
{
	return Point(this->x - point.x, this->y - point.y);
}

Point Point::operator*(double coeficient)
{
	return Point(this->x * coeficient, this->y * coeficient);
}

Point Point::operator/(double coeficient)
{
	return Point(this->x / coeficient, this->y / coeficient);
}
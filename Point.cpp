#include "point.h"   
#include <iostream>

Point::Point() {
	this->x = 0.0;
	this->y = 0.0;
	this->mass = 0.0;
}

Point::Point(double x, double y, double mass) {
	this->x = x;
	this->y = y;
	this->mass = mass;
}

Point::Point(double x, double y) {
	this->x = x;
	this->y = y;
	this->mass = 0.0;
}

double Point::getX() {
	return this->x;
}

double Point::getY() {
	return this->y;
}

double Point::getMass() {
	return this->mass;
}

void Point::setX(double x) {
	this->x = x;
}

void Point::setY(double y) {
	this->y = y;
}

void Point::setMass(double mass) {
	this->mass = mass;
}
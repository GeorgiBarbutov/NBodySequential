#include "Body.h"

Body::Body()
{
	this->point = Point(0, 0);
	this->mass = 0.0;
	this->velocity = Point(0, 0);
}

Body::Body(Point& point, double mass, Point& velocity)
{
	this->point = point;
	this->velocity = velocity;
	this->mass = mass;
}

Point Body::getPoint()
{
	return this->point;
}

Point Body::getVelocity()
{
	return this->velocity;
}

double Body::getMass()
{
	return this->mass;
}

void Body::setPoint(Point& point)
{
	this->point = point;
}

void Body::setVelocity(Point& velocity)
{
	this->velocity = velocity;
}

void Body::setMass(double mass)
{
	this->mass = mass;
}

void Body::updateVelocity(double dt, Point& force)
{
	force = force * (dt / this->mass);
	this->velocity = this->velocity - force;
}

void Body::updatePosition(double dt)
{
	this->point = this->point + this->velocity * dt;
}

Point Body::operator-(const Body& body) 
{
	return this->point - body.point;
}

bool Body::operator==(const Body& body)
{
	return this->point == body.point && this->velocity == body.velocity && this->mass == body.mass;
}

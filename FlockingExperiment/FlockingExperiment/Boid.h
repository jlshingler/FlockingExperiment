// Boid.h - The boid objects: their necessary variables, behaviors, etc.

#pragma once
#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <cmath>

#include "Common.h"

class Boid
{
public:
	Boid();
	Boid(float locx, float locy, float heading[2], colorObject color);
	~Boid();

	void randomMove();
	void flocking(Boid* boids);
	void move(Boid* boids);
	float& getX();
	void setX(float newX);
	float& getY();
	void setY(float newY);
	float getHeading();
	colorObject getColor();

private:
	float x;
	float y;
	float heading[2];
	colorObject color;
};


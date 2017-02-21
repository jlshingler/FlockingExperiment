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
	Boid(float locx, float locy, float heading[2], int color);
	~Boid();

	void move(Boid* boids);
	void randomMove();
	void flocking(Boid* boids);
	float& getX();
	void setX(float newX);
	float& getY();
	void setY(float newY);
	float getHeading();
	int getColor();

private:
	float x;
	float y;
	float heading[2];
	int color;
};


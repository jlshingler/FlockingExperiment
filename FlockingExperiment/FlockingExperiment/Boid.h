#pragma once
#include "stdafx.h"

#include <iostream>
#include <windows.h>
#include <vector>
#include <cmath>

#include "Common.h"

class Boid
{
public:
	Boid(float locx, float locy, float heading[2]);
	~Boid();

	void move(std::vector<Boid> &boids);
	void randomMove();
	void flocking(std::vector<Boid> &boids);
	float& getX();
	void setX(float newX);
	float& getY();
	void setY(float newY);
	float getHeading();

private:
	float x;
	float y;
	float heading[2];
};


// Common.h
#pragma once

#include <vector>
#include "Dependencies/freeglut/freeglut.h"

const int window_width = 800;
const int window_height = 600;

const float posx = 395.0f; // default starting point. will randomized in the future
const float posy = 295.0f;
const float size = 5.0f;

struct boid { // calling them boids bc why not
	float x;
	float y;
	float heading[2];
};

extern std::vector<boid> boids;
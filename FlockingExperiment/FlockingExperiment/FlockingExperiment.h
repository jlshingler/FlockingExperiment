// FlockingExperiment.h

#include "stdafx.h"

#include <iostream>
#include <windows.h>
#include <vector>
#include <cmath>
#include "Dependencies/freeglut/freeglut.h"

const int window_width = 800;
const int window_height = 600;
const int interval = 1000 / 60;

float posx = 395.0f; // default starting point. will randomized in the future
float posy = 295.0f;
float size = 10.0f;

const float maxSpeed = 1.0f;
const float maxRotation = 10.0f;

struct boid{ // calling them boids bc why not
	float x;
	float y;
};

std::vector<boid> boids;

// initialize triangle
void drawTriangle(float x, float y, float width, float height);

// initialize squares
void drawSquare(float x, float y, float width, float height);

// configure opengl for 2d
void enable2D(int width, int height);

void randomMove(int i);

// control movement
void move();

void draw();

void update(int value);
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
float size = 5.0f;

const float maxSpeed = 5.0f;
const float maxRotation = 10.0f;
const float sep = 0.5f; // separation
const float neighborhood = 1000.0f; // neighborhood

struct boid{ // calling them boids bc why not
	float x;
	float y;
	float heading[2];
};

std::vector<boid> boids;

// initialize triangle
void drawTriangle(float x, float y, float width, float height);

// initialize squares
void drawSquare(float x, float y, float width, float height);

// configure opengl for 2d
void enable2D(int width, int height);

void randomMove(int i);

// main flocking function 
void flocking(int i); 

// control movement
void move();

void draw();

void update(int value);
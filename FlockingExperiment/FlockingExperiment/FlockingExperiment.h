// FlockingExperiment.h

#include "stdafx.h"

#include <iostream>
#include <windows.h>
#include <vector>
#include <cmath>
#include "Dependencies/freeglut/freeglut.h"

#include "Boid.h"

std::vector<Boid> boids;

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
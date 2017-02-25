// FlockingExperiment.h - The main execution of the program

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <cmath>
#include <thread>
#include "Dependencies/freeglut/freeglut.h"

#include "Boid.h"
#include "Display.h"

#define VK_RETURN 0x0D
#define BOIDS_MAX_SIZE 2000

Boid boids[BOIDS_MAX_SIZE];
Display d;

void draw();
void processKeystrokes();
void update(int value);
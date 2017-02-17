// FlockingExperiment.h

#include "stdafx.h"

#include <iostream>
#include <windows.h>
#define VK_RETURN 0x0D
#include <vector>
#include <cmath>
#include "Dependencies/freeglut/freeglut.h"

#include "Boid.h"
#include "Display.h"

std::vector<Boid> boids;
Display d;

void draw();

// detect keystrokes to add boids (or change modes in the future)
void processKeystrokes();

void update(int value);
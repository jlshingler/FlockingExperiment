// Display.h - The main display functions for drawing on the screen

#pragma once
#include "stdafx.h"
#include "Dependencies/freeglut/freeglut.h"
#include <string>

#include "Boid.h"

class Display
{
public:
	Display();
	~Display();

	void drawText(float x, float y, std::string text, colorObject color);
	void drawTriangle(float x, float y, float width, float height);
	void drawSquare(float x, float y, float width, float height, colorObject color);
	void enable2D(int width, int height);
};


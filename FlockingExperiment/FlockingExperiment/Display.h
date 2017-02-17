#pragma once
#include "stdafx.h"
#include "Dependencies/freeglut/freeglut.h"
#include <string>
#include <vector>
#include "Boid.h"

class Display
{
public:
	Display();
	~Display();

	void drawText(float x, float y, std::string text);
	void drawTriangle(float x, float y, float width, float height);
	void drawSquare(float x, float y, float width, float height);
	void enable2D(int width, int height);
};


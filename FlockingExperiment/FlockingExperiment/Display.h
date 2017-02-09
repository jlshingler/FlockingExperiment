#pragma once
#include "stdafx.h"
#include "Dependencies/freeglut/freeglut.h"
class Display
{
public:
	Display(int argc, char** argv);
	~Display();

	void draw();
	void drawTriangle(float x, float y, float width, float height);
	void drawSquare(float x, float y, float width, float height);
	void enable2D(int width, int height);
};


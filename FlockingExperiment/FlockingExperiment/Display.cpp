// Display.cpp

#include "stdafx.h"
#include "Display.h"

Display::Display(){}

Display::~Display(){}

void Display::drawText(float x, float y, std::string text, colorObject color) {
	glColor3f(color.r, color.g, color.b); 
	glRasterPos2f(x, y);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char*)text.c_str());
}

void Display::drawTriangle(float x, float y, float width, float height) {
	glBegin(GL_TRIANGLES);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + (width / 2), y + height);
	glEnd();
}

void Display::drawSquare(float x, float y, float width, float height, colorObject color) {
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();
}

// configure opengl for 2d
void Display::enable2D(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
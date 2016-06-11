// FlockingExperiment.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include <iostream>
#include <windows.h>
#include <vector>
#include "Dependencies/freeglut/freeglut.h"

// graphics referenced from pong tutorial http://noobtuts.com/cpp/2d-pong-game

int window_width = 800;
int window_height = 600;
int interval = 1000 / 60;

float tposx = 385.0f;
float tposy = 295.0f;
float tsize = 10.0f;

float sposx = 405.0f;
float sposy = 295.0f;
float ssize = 10.0f;

//initialize triangle
void drawTriangle(float x, float y, float width, float height) { 
	glBegin(GL_TRIANGLES);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + (width / 2), y + height);
	glEnd();
}

void drawSquare(float x, float y, float width, float height){
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();
}

void enable2D(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix(); //Save the transformations performed thus far

	drawTriangle(tposx, tposy, tsize, tsize);
	drawSquare(sposx, sposy, ssize, ssize);
	
	glutSwapBuffers();
}

void update(int value) {
	glutTimerFunc(interval, update, 0);

	glutPostRedisplay();
}

int _tmain(int argc, char** argv)
{
	// initialize opengl (via glut)
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("");

	// Register callback functions  
	glutDisplayFunc(draw);
	glutTimerFunc(interval, update, 0);

	// setup scene to 2d mode and set draw color to white
	enable2D(window_width, window_height);
	glColor3f(1.0f, 1.0f, 1.0f);

	// start
	glutMainLoop();
	return 0;
}


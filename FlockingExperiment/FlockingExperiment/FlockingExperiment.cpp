// FlockingExperiment.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include <iostream>
#include <windows.h>
#include <vector>
#include "Dependencies/freeglut/freeglut.h"

// graphics referenced from pong tutorial http://noobtuts.com/cpp/2d-pong-game
// other references (such as research/starting points for flocking behavior):
// Programming Principles and Practice Using C++ by Bjarne Stroustrup
// Artificial Intelligence for Games Second Edition by Ian Millington & John Funge
// Programming Game AI by Example by Mat Buckland
// http://www.kfish.org/boids/pseudocode.html
// Flocks, herds and schools: A distributed behavioral model by Craig W. Reynolds


int window_width = 800;
int window_height = 600;
int interval = 1000 / 60;

float posx = 395.0f; // default starting point. will randomized in the future
float posy = 295.0f;
float size = 10.0f;

float maxSpeed = 10.0f;
float maxRotation = 10.0f;

struct boid{ // calling them boids bc why not
	float x;
	float y;
};

std::vector<boid> boids;

bool flipSwitch = true;

// initialize triangle
void drawTriangle(float x, float y, float width, float height) { 
	glBegin(GL_TRIANGLES);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + (width / 2), y + height);
	glEnd();
}

// initialize squares
void drawSquare(float x, float y, float width, float height){
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();
}

// configure opengl for 2d
void enable2D(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// for now VERY basic movement to test. just move across the screen and back.
void move(){ 
	for (int i = 0; i < boids.size(); i++){
		if (boids[i].x < 650 && !flipSwitch){
			boids[i].x += 1;
			boids[i].y += 1;
		}
		else if (boids[i].x > 150 && flipSwitch) {
			boids[i].x -= 1;
			boids[i].y -= 1;
		}
		else{
			flipSwitch = !flipSwitch;
		}
	}
}

void draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix(); // save the transformations performed thus far

	for (boid b : boids){ // draw each boid
		drawSquare(b.x, b.y, size, size);
	}

	glutSwapBuffers();
}

void update(int value) {
	move(); // call movement

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

	// initialize test boids
	boid testBoid;
	testBoid.x = posx;
	testBoid.y = posy;
	boids.push_back(testBoid);

	boid testBoid2;
	testBoid2.x = posx;
	testBoid2.y = posy + 20.0f;
	boids.push_back(testBoid2);

	// register callback functions  
	glutDisplayFunc(draw);
	glutTimerFunc(interval, update, 0);

	// setup scene to 2d mode and set draw color to white
	enable2D(window_width, window_height);
	glColor3f(1.0f, 1.0f, 1.0f);

	// start
	glutMainLoop();
	return 0;
}


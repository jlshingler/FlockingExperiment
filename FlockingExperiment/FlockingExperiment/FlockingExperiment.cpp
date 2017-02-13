// FlockingExperiment.cpp
//
#include "stdafx.h"
#include "FlockingExperiment.h"

// graphics referenced from pong tutorial http://noobtuts.com/cpp/2d-pong-game
// other references (such as research/starting points for flocking behavior):
// Programming Principles and Practice Using C++ by Bjarne Stroustrup
// Artificial Intelligence for Games Second Edition by Ian Millington & John Funge
// Programming Game AI by Example by Mat Buckland
// http://www.kfish.org/boids/pseudocode.html
// Flocks, herds and schools: A distributed behavioral model by Craig W. Reynolds


void drawText(float x, float y, std::string text) {
	glRasterPos2f(x, y);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char*)text.c_str());
}

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

void draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix(); // save the transformations performed thus far

	char buffer[65];
	_itoa_s(boids.size(), buffer, 10);
	std::string message = std::string("Press 'Enter' to Add Boids (There are ") + std::string(buffer) + std::string(" Boids Currently)");
	drawText(window_width / 2 - 220, window_height - 15, message);

	for (Boid b : boids){ // draw each boid
		drawSquare(b.getX(), b.getY(), size, size);
	}

	glutSwapBuffers();
}

void keyboard() {
	// left racket
	if (GetAsyncKeyState(VK_RETURN)){
		float x = posx + ((float)rand() / ((RAND_MAX) / 15));
		float y = posy + ((float)rand() / ((RAND_MAX) / 15));
		float heading[2];
		heading[0] = (((float)rand() / (RAND_MAX)));
		heading[1] = (((float)rand() / (RAND_MAX)));
		Boid boid(x, y, heading);
		boids.push_back(boid);
	}

}

void update(int value) {
	keyboard();

	for (Boid &b : boids){ // draw each boid
		b.move(boids);
	}
//	std::cout << boids[0].getX() << std::endl;

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
	for (int i = 0; i < 100; i++){
		float x = posx + ((float)rand() / ((RAND_MAX) / 15));
		float y = posy + ((float)rand() / ((RAND_MAX) / 15));
		float heading[2];
		heading[0] = (((float)rand() / (RAND_MAX)));
		heading[1] = (((float)rand() / (RAND_MAX)));
		Boid boid(x, y, heading);
		boids.push_back(boid);
	}

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


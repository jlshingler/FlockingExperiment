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

void draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix(); // save the transformations performed thus far

	char buffer[65];
	_itoa_s(boids.size(), buffer, 10);
	std::string message = std::string("Press 'Enter' to Add Boids (There are ") + std::string(buffer) + std::string(" Boids Currently)");
	d.drawText(window_width / 2 - 220, window_height - 15, message);

	for (Boid b : boids){ // draw each boid
		d.drawSquare(b.getX(), b.getY(), size, size);
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
	d.enable2D(window_width, window_height);
	glColor3f(1.0f, 1.0f, 1.0f);

	// start
	glutMainLoop();
	return 0;
}


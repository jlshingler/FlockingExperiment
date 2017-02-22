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

// handle drawing
void draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix(); // save the transformations performed thus far

	char buffer[65];
	_itoa_s(lastBoid, buffer, 10);
	std::string message = std::string("Press 'Enter' to Add Boids (There are ") + std::string(buffer) + std::string(" Boids Currently)");
	d.drawText(window_width / 2 - 220, window_height - 15, message, textColor);

	for (int i = 0; i < lastBoid; i++){ // draw each boid
		d.drawSquare(boids[i].getX(), boids[i].getY(), size, size, boids[i].getColor());
	}

	glutSwapBuffers();
}

// detect keystrokes to add boids (or change modes in the future)
void processKeystrokes() {
	if (GetAsyncKeyState(VK_RETURN)){
		if (lastBoid < BOIDS_MAX_SIZE) {
			float x = posx + ((float)rand() / ((RAND_MAX) / 15));
			float y = posy + ((float)rand() / ((RAND_MAX) / 15));
			float heading[2];
			heading[0] = (((float)rand() / (RAND_MAX)));
			heading[1] = (((float)rand() / (RAND_MAX)));
			Boid boid(x, y, heading, newBoidsColor);
			boids[lastBoid] = boid;
			lastBoid++; //increment
		}
	}

}

// actions on each frame
void update(int value) {
	processKeystrokes();

	for (int i = 0; i < lastBoid; i++){ // move each boid based on behavior (see Boid.cpp)
		boids[i].move(boids);
	}

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
	for (int i = 0; i < lastBoid; i++){
		float x = posx + ((float)rand() / ((RAND_MAX) / 15));
		float y = posy + ((float)rand() / ((RAND_MAX) / 15));
		float heading[2];
		heading[0] = (((float)rand() / (RAND_MAX)));
		heading[1] = (((float)rand() / (RAND_MAX)));
		Boid boid(x, y, heading, startBoidsColor);
		boids[i] = boid;
	}

	// register callback functions  
	glutDisplayFunc(draw);
	glutTimerFunc(interval, update, 0);

	// setup scene to 2d mode and set default draw color to white
	d.enable2D(window_width, window_height);
	glColor3f(1.0f, 1.0f, 1.0f);

	// start
	glutMainLoop();
	return 0;
}


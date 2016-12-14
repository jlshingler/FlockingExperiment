// FlockingExperiment.cpp
//
#include "stdafx.h"
#include "Drawing.h"
#include "FlockingExperiment.h"
#include "Behavior.h"
#include "Common.h"

// graphics referenced from pong tutorial http://noobtuts.com/cpp/2d-pong-game
// other references (such as research/starting points for flocking behavior):
// Programming Principles and Practice Using C++ by Bjarne Stroustrup
// Artificial Intelligence for Games Second Edition by Ian Millington & John Funge
// Programming Game AI by Example by Mat Buckland
// http://www.kfish.org/boids/pseudocode.html
// Flocks, herds and schools: A distributed behavioral model by Craig W. Reynolds

// control movement
void move(){ 

	for (int i = 0; i < boids.size(); i++){
		randomMove(i);
		flocking(i);

		// wrap position so boids stay on screen
		//if (boids[i].x > window_width){
		//	boids[i].x = boids[i].x - window_width;
		//}
		//if (boids[i].x < 0){
		//	boids[i].x = window_width + boids[i].x;
		//}
		//if (boids[i].y > window_height){
		//	boids[i].y = boids[i].y - window_height;
		//}
		//if (boids[i].y < 0){
		//	boids[i].y = window_height + boids[i].y;
		//}

		if (boids[i].x > window_width || boids[i].x < 0 || boids[i].y > window_height || boids[i].y < 0){
			boids[i].x = posx + ((float)rand() / ((RAND_MAX)* 15));
			boids[i].y = posy + (((float)rand() / ((RAND_MAX)) * 15));
			boids[i].heading[0] = (((float)rand() / (RAND_MAX)));
			boids[i].heading[1] = (((float)rand() / (RAND_MAX)));
		}

		/*if (boids[i].x > window_width){ //maybe do push back?
			boids[i].x = window_width;
			boids[i].heading[0] = boids[i].heading[0] * -1;
		}
		if (boids[i].x < 0){
			boids[i].x = 0;
			boids[i].heading[0] = boids[i].heading[0] * -1;
		}
		if (boids[i].y > window_height){
			boids[i].y = window_height;
			boids[i].heading[1] = boids[i].heading[1] * -1;
		}
		if (boids[i].y < 0){
			boids[i].y = 0;
			boids[i].heading[1] = boids[i].heading[1] * -1;
		}*/
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
	for (int i = 0; i < 100; i++){
		boid test;
		test.x = posx + ((float)rand() / ((RAND_MAX) * 15));
		test.y = posy + (((float)rand() / ((RAND_MAX)) * 15));
		test.heading[0] = (((float)rand() / (RAND_MAX)));
		test.heading[1] = (((float)rand() / (RAND_MAX)));
		boids.push_back(test);
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


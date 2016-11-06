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

void randomMove(int i){
	float angle = ((float)rand() / (RAND_MAX)) * ((float)(2 * 3.14159));
	float movex = sin(angle);
	float movey = cos(angle);
	boids[i].x += movex * maxSpeed;
	boids[i].y += movey * maxSpeed;
}

// movement behavior calculations
void flocking(int i){
	float movex = 0; // how far boid will move in x direction
	float movey = 0; // how far boid will move in y direction
	float cenx = 0; // center x of group
	float ceny = 0; // center y of group
	int neighborCount = 0; // neighbors (for getting avg)
	float avgHeading[2] = { 0, 0 };
	for (int j = 0; j < boids.size(); j++){
		if (j != i){
			//get distance
			float distx = boids[i].x - boids[j].x;
			float disty = boids[i].y - boids[j].y;
			float length = sqrt((distx * distx) + (disty * disty));
			float angle = sin(disty / length);
			if (length < neighborhood){
				if (length < sep){ // separation
					if (distx < 0){
						movex += sin(angle);
					}
					else{
						movex -= sin(angle);
					}
					if (disty < 0){
						movey += cos(angle);
					}
					else{
						movey -= cos(angle);
					}
				}
				neighborCount += 1; // increment neighbor stats as we go
				cenx += boids[j].x;
				ceny += boids[j].y;
				avgHeading[0] += boids[j].heading[0];
				avgHeading[1] += boids[j].heading[1];
			}
		}
	}
	if (neighborCount > 0){
		float weight = 100.0f; //cohesion
		cenx /= neighborCount; //avg center position
		ceny /= neighborCount;
		float distx = boids[i].x - cenx; 
		float disty = boids[i].y - ceny;
		float length = sqrt((distx * distx) + (disty * disty));
		float angle = sin(disty / length);
		if (distx < 0){
			movex -= sin(angle) * weight;
		}
		else{
			movex += sin(angle) * weight;
		}
		if (disty < 0){
			movey -= cos(angle) * weight;
		}
		else{
			movey += cos(angle) * weight;
		}
	}
	
	boids[i].heading[0] = (movex + avgHeading[0] + boids[i].heading[0]) / (boids.size() + 1); //allignment
	boids[i].heading[1] = (movey + avgHeading[1] + boids[i].heading[1]) / (boids.size() + 1);
	boids[i].x += boids[i].heading[0] / maxSpeed;
	boids[i].y += boids[i].heading[1] / maxSpeed;
}

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


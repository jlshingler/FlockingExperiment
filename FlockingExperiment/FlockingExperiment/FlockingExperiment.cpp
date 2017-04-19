// FlockingExperiment.cpp

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
			lastBoid++; // increment
		}
	}

}

void boidLoop(int start, int finish, Boid* test) {
	//protect entire for-loop
	//acquire lock (mutex)
	flockLock.lock();
	//std::cout << "start: " << start << ", end: " << finish << std::endl;
	for (int i = start; i < finish; i++) { // move each boid based on behavior (see Boid.cpp)
		boids[i].move(test);
	}
	flockLock.unlock();
	//release lock
}

// actions on each frame
void update(int value) {
	processKeystrokes();

	//protect the array copy so it doesn't get interrupted
	//acquire lock
	//flockLock.lock();
	//Boid test[BOIDS_MAX_SIZE]; //make temp (will be rewritten each update) copy so that each boid will have the same base info for movement calcs
	//memcpy(test, boids, 5 * sizeof *boids);
	//flockLock.unlock();
	//release lock

	//boidLoop(0, lastBoid, boids);

	std::thread t3(boidLoop, 0, (lastBoid / 4), boids);
	std::thread t4(boidLoop, (lastBoid / 4), (lastBoid / 2), boids);
	std::thread t5(boidLoop, (lastBoid / 2), (3 * lastBoid / 4), boids);
	std::thread t6(boidLoop, (3 * lastBoid / 4), lastBoid, boids);
	t3.join();
	t4.join();
	t5.join();
	t6.join();
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

	/*std::thread t1;
	std::thread t2;*/

	// register callback functions  
	glutDisplayFunc(draw);
	glutTimerFunc(interval, update, 0);

	// setup scene to 2d mode and set default draw color to white
	d.enable2D(window_width, window_height);
	glColor3f(1.0f, 1.0f, 1.0f);

	// start
	glutMainLoop();

	/*t1.join();
	t2.join();*/
	return 0;
}


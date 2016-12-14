// Behavior.cpp
#include "stdafx.h"
#include "Behavior.h"
#include "Common.h"

void randomMove(int i) {
	float angle = ((float)rand() / (RAND_MAX)) * ((float)(2 * 3.14159));
	float movex = sin(angle);
	float movey = cos(angle);
	boids[i].x += movex * maxSpeed;
	boids[i].y += movey * maxSpeed;
}

// movement behavior calculations
void flocking(int i) {
	float movex = 0; // how far boid will move in x direction
	float movey = 0; // how far boid will move in y direction
	float cenx = 0; // center x of group
	float ceny = 0; // center y of group
	int neighborCount = 0; // neighbors (for getting avg)
	float avgHeading[2] = { 0, 0 };
	for (int j = 0; j < boids.size(); j++) {
		if (j != i) {
			//get distance
			float distx = boids[i].x - boids[j].x;
			float disty = boids[i].y - boids[j].y;
			float length = sqrt((distx * distx) + (disty * disty));
			float angle = sin(disty / length);
			if (length < neighborhood) {
				if (length < sep) { // separation
					if (distx < 0) {
						movex += sin(angle);
					}
					else {
						movex -= sin(angle);
					}
					if (disty < 0) {
						movey += cos(angle);
					}
					else {
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
	if (neighborCount > 0) {
		float weight = 100.0f; //cohesion
		cenx /= neighborCount; //avg center position
		ceny /= neighborCount;
		float distx = boids[i].x - cenx;
		float disty = boids[i].y - ceny;
		float length = sqrt((distx * distx) + (disty * disty));
		float angle = sin(disty / length);
		if (distx < 0) {
			movex -= sin(angle) * weight;
		}
		else {
			movex += sin(angle) * weight;
		}
		if (disty < 0) {
			movey -= cos(angle) * weight;
		}
		else {
			movey += cos(angle) * weight;
		}
	}

	boids[i].heading[0] = (movex + avgHeading[0] + boids[i].heading[0]) / (boids.size() + 1); //allignment
	boids[i].heading[1] = (movey + avgHeading[1] + boids[i].heading[1]) / (boids.size() + 1);
	boids[i].x += boids[i].heading[0] / maxSpeed;
	boids[i].y += boids[i].heading[1] / maxSpeed;
}
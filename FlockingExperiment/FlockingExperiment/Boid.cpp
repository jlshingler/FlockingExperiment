#include "stdafx.h"
#include "Boid.h"


Boid::Boid(float locx, float locy, float set_heading[2])
{
	x = locx;
	y = locy;
	heading[0] = set_heading[0];
	heading[1] = set_heading[1];
}


Boid::~Boid()
{
}

void Boid::randomMove(){
	float angle = ((float)rand() / (RAND_MAX)) * ((float)(2 * 3.14159));
	float movex = sin(angle);
	float movey = cos(angle);
	setX(x + movex);
	setY(y + movey);
}

// movement behavior calculations
void Boid::flocking(std::vector<Boid> &boids){
	float movex = 0; // how far boid will move in x direction
	float movey = 0; // how far boid will move in y direction
	float cenx = 0; // center x of group
	float ceny = 0; // center y of group
	int neighborCount = 0; // neighbors (for getting avg)
	float avgHeading[2] = { 0, 0 };

	for (int j = 0; j < boids.size(); j++){
		//get distance
		float distx = x - boids[j].getX();
		float disty = y - boids[j].getY();
		float length = sqrt((distx * distx) + (disty * disty));
		if (length != 0){
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
		float distx = x - cenx;
		float disty = y - ceny;
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
	
	heading[0] = (movex + avgHeading[0] + heading[0]) / (boids.size() + 1); //allignment
	heading[1] = (movey + avgHeading[1] + heading[1]) / (boids.size() + 1);
	setX(x + heading[0] / maxSpeed);
	setY(y + heading[1] / maxSpeed);
}

// control movement
void Boid::move(std::vector<Boid> &boids){

	randomMove();
	flocking(boids);

	//// wrap position so boids stay on screen
	//if (getX() > window_width){
	//	setX(this->x - window_width);
	//}
	//if (getX() < 0){
	//	boids[i].x = window_width + boids[i].x;
	//}
	//if (getY() > window_height){
	//	boids[i].y = boids[i].y - window_height;
	//}
	//if (getY() < 0){
	//	boids[i].y = window_height + boids[i].y;
	//}

	if (getX() > window_width || getX() < 0 || getY() > window_height || getY() < 0){
		this->x = posx + ((float)rand() / ((RAND_MAX)) * 15);
		this->y = posy + ((float)rand() / ((RAND_MAX)) * 15);
		this->heading[0] = (((float)rand() / (RAND_MAX)));
		this->heading[1] = (((float)rand() / (RAND_MAX)));
	}

	//old code cleanup later
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

float& Boid::getX(){
	return x;
}

void Boid::setX(float newX){
	this->x = newX;
}

float& Boid::getY(){
	return y;
}

void Boid::setY(float newY){
	this->y = newY;
}

float Boid::getHeading(){
	return 0;
}
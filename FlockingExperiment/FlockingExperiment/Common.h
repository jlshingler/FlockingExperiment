#pragma once

const int window_width = 800;
const int window_height = 600;
const int interval = 1000 / 60;

const float posx = 395.0f; // default starting point. will randomized in the future
const float posy = 295.0f;
const float size = 5.0f;

const float maxSpeed = 5.0f;
const float maxRotation = 10.0f;
const float sep = 0.5f; // separation
const float neighborhood = 1000.0f; // neighborhood

static int lastBoid = 100; //initial size of boids array

struct colorObject { 
	float r;
	float g;
	float b;
};

const colorObject startBoidsColor = { 0.5f, 1.0f, 1.0f}; //color defaults to denote different objects
const colorObject newBoidsColor = { 1.0f, 1.0f, 0.5f };
const colorObject textColor = { 1.0f, 1.0f, 1.0f };
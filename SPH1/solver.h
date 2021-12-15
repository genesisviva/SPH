#pragma once

#include "vector_2D.h"
#include <stdlib.h>
#include <stdio.h>

#define _USE_MATH_DEFINES
#include <math.h>


// Constants
const static double H = 0.0457;				
const static double DEFAULT_MASS = 0.02;		
const static double DENSITY_0 = 1000;		
const static double GAS_CONST = 3;		
const static double VISCOSITY = 3.5;			
const static double DT = 0.001;				
const static double EXTERNAL_FORCE_X = 0.0;			
const static double EXTERNAL_FORCE_Y = -9.81;

const static double POLY6 = 315.0 / (64.0 * M_PI * pow(H, 9));
const static double SPIKY_GRAD = -45.0 / (M_PI * pow(H, 6));
const static double VISC_LAP = 45.0 / (M_PI * pow(H,6));


const static double BOUNDARY = 0.005;			
const static double BOUND_DAMP = -0.5;	 



struct Particle
{
	// Use for dynamic particles
	Particle(vector_2D position, vector_2D velocity, int id_)
	{
		id = id_;
		mass = DEFAULT_MASS;
		density = DENSITY_0;
		pressure = 0.f;
		acceleration = 0.f;
		this->position = position;
		this->velocity = velocity;
	}


	int id;

	float mass;
	float density;
	float pressure;

	vector_2D position;
	vector_2D velocity;
	vector_2D evelocity;
	vector_2D acceleration;
};


class Solver
{
public:
	Solver();
	~Solver();

	void initialize();
	void update();
	void addParticle(vector_2D pos, vector_2D vel = vector_2D(0.0f, 0.0f));

	Particle* particles[1000000];
	float worldSize_width;
	float worldSize_height;
	int currentParticles = 0;

private:

	void ForwardEuler();
	void calculateDensityPressure();
	void calculateForces();


	vector_2D external_force;
	float timeStep;
	
};

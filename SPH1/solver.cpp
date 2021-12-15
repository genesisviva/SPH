#include "solver.h"

Solver::Solver()
{

}

Solver::~Solver()
{
	free(particles);
}

void Solver::initialize()
{
	worldSize_width = 1.0f;
	worldSize_height = 1.0f;


	external_force.x = EXTERNAL_FORCE_X;
	external_force.y = EXTERNAL_FORCE_Y;
}

void Solver::update()
{
	calculateDensityPressure();
	
	calculateForces();
	
	ForwardEuler();
}

void Solver::calculateDensityPressure()
{
	for (int i = 0; i < currentParticles; i++)		//For each particle
	{
		particles[i]->density = 0;				//Zeroing this particle density

		for (int j = 0; j < currentParticles; j++)	//For each other particle
		{
			vector_2D r = particles[i]->position - particles[j]->position;	//Distance between i (current) particle and j (another) particle (Each coordinate)
			float r2 = r * r;		//Real distance

			if (r2 >= H*H)		//Check if j particle is inside radius where POLY6 kernel !=0
			{
				continue;
			}

			particles[i]->density += particles[j]->mass * POLY6 * pow(H*H - r2, 3);	//Formula 1 (notes)
		}
		particles[i]->pressure = (pow(particles[i]->density / DENSITY_0, 7) - 1) * GAS_CONST;

	}
}

float tempo, tempo2;

void Solver::calculateForces()
{	
	for (int i = 0; i < currentParticles; i++)	//For each particle
	{
		particles[i]->acceleration = 0;			//for each particle a = 0

		
		for (int j = 0; j < currentParticles; j++)	//For each other particle
		{
			if (i == j)								//Skip same particle
				continue;						

			vector_2D r0 = particles[i]->position - particles[j]->position;		//Distance between i (current) particle and j (another) particle (Each coordinate)
			float r2 = r0.x * r0.x + r0.y * r0.y;							//Real distance squared
			
			if (r2 < H*H)													//Check if particle is inside radius where SPIKY and VISC kernels both !=0
			{
				float r = sqrt(r2);											//Real distance

				float V = particles[j]->mass / particles[j]->density / 2;	
				float Kr = H - r;
				float Kp = SPIKY_GRAD * Kr * Kr;

				float tempForce = V*(particles[i]->pressure + particles[j]->pressure) * Kp;//Force Calc (notes)
				particles[i]->acceleration -= r0 * tempForce / r;						

				vector_2D rV = particles[j]->evelocity - particles[i]->evelocity;

				float Kv = VISC_LAP * (H - r);
				tempForce = V * VISCOSITY * Kv;
				particles[i]->acceleration += rV * tempForce * 2;
			}
		}
		particles[i]->acceleration = particles[i]->acceleration / particles[i]->density;

	}
}

void Solver::ForwardEuler() 
{
	for (int i = 0; i < currentParticles; i++)
	{

		particles[i]->velocity += particles[i]->acceleration * DT + external_force * DT;
		particles[i]->position += particles[i]->velocity * DT;

		if (particles[i]->position.x >= worldSize_width)
		{
			particles[i]->velocity.x = particles[i]->velocity.x * BOUND_DAMP;
			particles[i]->position.x = worldSize_width - BOUNDARY;
		}

		if (particles[i]->position.x < 0)
		{
			particles[i]->velocity.x = particles[i]->velocity.x * BOUND_DAMP;
			particles[i]->position.x = BOUNDARY;
		}

		if (particles[i]->position.y >= worldSize_height)
		{
			particles[i]->velocity.y = particles[i]->velocity.y * BOUND_DAMP;
			particles[i]->position.y = worldSize_height - BOUNDARY;
		}

		if (particles[i]->position.y < 0)
		{
			particles[i]->velocity.y = particles[i]->velocity.y * BOUND_DAMP;
			particles[i]->position.y = BOUNDARY;
		}

		

		particles[i]->evelocity = (particles[i]->evelocity + particles[i]->velocity) / 2;
	}
}

void Solver::addParticle(vector_2D pos, vector_2D vel)
{
		particles[currentParticles] = new Particle(pos, vel, currentParticles);
		particles[currentParticles]->mass = DEFAULT_MASS;
		currentParticles++;
}





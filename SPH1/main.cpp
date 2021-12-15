#define _CRT_SECURE_NO_WARNINGS



#include "stdlib.h"
#include "math.h"
#include <iostream>
#include <GL\glut.h>
#include "vector_2D.h"
#include "solver.h"



const double WINDOW_WIDTH = 800;
const double WINDOW_HEIGTH = 800;
const double GRID_TRANSFORM = 0.01;

int keyPause = 1;

Solver* sphSolver;


	void Dam_Break(int dam_width)					//dam heigth = 2*dam width	
{
	int particleCtr = 0;

	for (int x = 0; x < dam_width; x++)
		for (int y = 0; y < dam_width*2; y++)
		{
			sphSolver->addParticle(vector_2D(x * GRID_TRANSFORM, y * 2 * GRID_TRANSFORM));
			particleCtr++;
		}


	std::cout << "Number of Particles: " << particleCtr << std::endl;
}

void init()
{
	sphSolver = new Solver();
	sphSolver->initialize();
	Dam_Break(20);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, sphSolver->worldSize_width, 0.0, sphSolver->worldSize_height);
	glutIgnoreKeyRepeat(false);
	std::cout << "Space   - Resume/Pause" << std::endl;
}

void render()
{

	glColor3f(0.0, 0.0, 1.0);
	glPointSize(10);
	for(int x = 0; x < sphSolver->currentParticles; x++)
	{
		glBegin(GL_POINTS);
		glVertex2d(sphSolver->particles[x]->position.x, sphSolver->particles[x]->position.y);
		glEnd();
	}	

}

void display()
{
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 1.0f);
	if(keyPause == 0)
		sphSolver->update();
	render();
	glutSwapBuffers();
	glutSetWindowTitle("SPH");
	
}


void idle()
{
	glutPostRedisplay();
}


void process_keyboard(unsigned char key, int x, int y)
{
	if (key == ' ')
	{
		keyPause = 1 - keyPause;
	}

}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGTH);
	glutCreateWindow("SPH");
	init();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(process_keyboard);
	glutMainLoop();

	return 0;
}

#include "GL/freeglut.h"
#include "GL/gl.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <iostream>
#include "ArrayHelper.cpp"
#include <unistd.h>

int length;
int delay;
int* arr;
void (*sort)(int*, int);
void renderFunction()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	
	float l = (float) length;
	float widthAdder = 1/l;

	for(int i = 0; i < length; ++i)
	{
		glBegin(GL_POLYGON);
		
		// + 1 so value of 0 has height of 1
		float arrayIndexHeightRation = 2*(arr[i] + 1)/l;
		float widthIndexAdder = 2*i/l;

		float leftX   = -1 + widthIndexAdder;
		float rightX  = leftX + widthAdder;
		float bottomY = -1;
		float topY    = bottomY + arrayIndexHeightRation;

		// bottom left
		glColor4f(1,0,0,0);
		glVertex2f(leftX, bottomY);

		// bottom right
		glColor4f(0,1,0,0);
		glVertex2f(rightX, bottomY);

		// top right
		glColor4f(0,0,1,0);
		glVertex2f(rightX, topY);

		// top left
		glColor4f(0,0,0,1);
		glVertex2f(leftX, topY);

		glEnd();
	}

	glFlush();
}

void swap(int index1, int index2)
{
	std::swap(arr[index1], arr[index2]);
	renderFunction();
	usleep(delay);
}

void keyboardEvent(unsigned char c, int x, int y)
{
	if(c == 27)
	{
		// exit on escape key pressed
		exit(0);
		free(arr);
	}
	else if(c == 115)
	{
		// start on `s` key pressed
		sort(arr, length);
	}
}

/* Main method - main entry point of application
the freeglut library does the window creation work for us, 
regardless of the platform. */
int setUpGlutAndArray(int argc, char** argv, void (*sortingAlgorithm)(int*, int))
{
	sort = sortingAlgorithm;
	arr = (int*) malloc(sizeof(int) * length);
	for(int i = 0; i < length; ++i)
	{
		arr[i] = i;
	}

	randomizeArray(arr, length);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(length,length);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Sort Visualization");

	glutDisplayFunc(renderFunction);
	glutKeyboardFunc(keyboardEvent);

	glutMainLoop();
}

// testing code
int main(int argc, char** argv)
{
	length = 400;
	setUpGlutAndArray(argc, argv);
	free(arr);
	return 0;
}

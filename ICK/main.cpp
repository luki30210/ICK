#include <iostream>
#include "FiguresController.h"

FiguresController figuresController;
FiguresController backgroundController;
float lx = 0.0f, lz = -1.0f;	// actual vector representing the camera's direction
float x = 0.0f, z = 5.0f;	// XZ position of the camera
float angle = 0.0f;		// angle for rotating triangle


void changeSize(int w, int h)
{
	if (h == 0) h = 1;	// Prevent a divide by zero, when window is too short (you cant make a window of zero width)
	float ratio = w * 1.0 / h;

	glMatrixMode(GL_PROJECTION);	// Use the Projection Matrix
	glLoadIdentity();		// Reset Matrix
	glViewport(0, 0, w, h);	// Set the viewport to be the entire window
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);	// Set the correct perspective.

	glMatrixMode(GL_MODELVIEW);	// Get Back to the Modelview
}

void renderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Color and Depth Buffers
	glLoadIdentity();	// Reset transformations

	// Set the camera
	gluLookAt(x, 1.0f, z,
		x + lx, 1.0f, z + lz,
		0.0f, 1.0f, 0.0f);

	/* ------------------------------ TUTAJ KOD ------------------------------ */
	
	figuresController.paintFigures();
	backgroundController.paintFigures();

	/* ----------------------------------------------------------------------- */
	
	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y)
{

	if (key == 27)
		exit(0);

}

void processSpecialKeys(int key, int xx, int yy)
{

	float fraction = 0.1f;

	switch (key) {
	case GLUT_KEY_LEFT:
		angle -= 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_RIGHT:
		angle += 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_UP:
		x += lx * fraction;
		z += lz * fraction;
		break;
	case GLUT_KEY_DOWN:
		x -= lx * fraction;
		z -= lz * fraction;
		break;
	}

}

int main(int argc, char **argv)
{

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 100);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("OpenGL Figures");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// Init figures
	figuresController.loadFiguresFromFile("Resources/data/example.xml");
	figuresController.setColor(100, 100, 255);
	backgroundController.loadFiguresFromFile("Resources/data/background.xml");
	backgroundController.setColor(0, 255, 0);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}
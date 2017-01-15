#include <iostream>
#include "FiguresController.h"
#include "CameraController.h"

FiguresController figuresController;
FiguresController backgroundController;
CameraController cameraController;

void changeSize(int w, int h)
{
	if (h == 0) h = 1;	// Prevent a divide by zero, when window is too short (you cant make a window of zero width)
	float ratio = w * 1.0f / h;

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

	glTranslatef(-CameraController::cameraX, 0.0f, -CameraController::cameraZ);
	glRotatef(CameraController::cameraRotationY, 1.0f, 0.0f, 0.0f);
	glRotatef(CameraController::cameraRotationX, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, CameraController::cameraY, 0.0f);
	
	//gluLookAt(CameraController::cameraX, CameraController::cameraY, CameraController::cameraZ, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	/* ------------------------------ TUTAJ KOD ------------------------------ */
	
	figuresController.paintFigures();
	backgroundController.paintBackground();

	/* ----------------------------------------------------------------------- */
	
	glutSwapBuffers();
}

void Update()
{
	cameraController.UpdateKeyboardInput();
	glutPostRedisplay();
}

void KeyboardCallback(unsigned char key, int x, int y)
{
	cameraController.ManageKeyboardCallback(key, true);
}

void KeyboardUpCallback(unsigned char key, int x, int y)
{
	cameraController.ManageKeyboardCallback(key, false);
}

void MouseWheelCallback(int wheel, int direction, int x, int y)
{
	if (direction > 0.0f)
	{
		CameraController::cameraY -= 1.0f;
	}
	if(direction < 0.0f)
	{ 
		CameraController::cameraY += 1.0f;
	}
}

void MouseMotionCallback(int x, int y)
{
	
	CameraController::cameraRotationX += (x - cameraController.currentX) / 10.0f;
	CameraController::cameraRotationY += (y - cameraController.currentY) / 10.0f;

	cameraController.currentX = x;
	cameraController.currentY = y;
}

void MouseCallback(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		cameraController.currentX = x;
		cameraController.currentY = y;
	}
}

void timer(int value)
{
	Update();
	glutTimerFunc(1000 / 60, timer, 0);
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
	//glutIdleFunc(Update);
	glutKeyboardFunc(KeyboardCallback);
	glutKeyboardUpFunc(KeyboardUpCallback);
	glutMouseWheelFunc(MouseWheelCallback);
	glutMotionFunc(MouseMotionCallback);
	glutMouseFunc(MouseCallback);
	timer(0);

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
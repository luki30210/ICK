#include "main.h"

int main(int argc, char **argv)
{
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 100);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("OpenGL Figures");

	antTweakBar();
	glutIgnoreKeyRepeat(1);
	registerCallbacks();
	Timer(0);
	glEnable(GL_DEPTH_TEST);	// OpenGL init

	// Init figures
	figuresController.loadFiguresFromFile("Resources/data/example.xml");
	backgroundController.loadFiguresFromFile("Resources/data/background.xml");

	focalLength = 200.0f;	// Ustawienie ogniskowej

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}


/*
FPS Control

SPACEBAR - prze��cza tryb pracy kamer� - sterowanie kamer� za pomoc� klawiatury i myszki
W, A, S, D - poruszanie si� kamer�
mouse - rozgl�danie si� (rotacja Yaw i Pitch)
left/right mouse button - zwi�kszenie/obni�enie wysoko�ci na kt�rej znajduje si� kamera

*/
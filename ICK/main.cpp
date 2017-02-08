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

SPACEBAR - prze³¹cza tryb pracy kamer¹ - sterowanie kamer¹ za pomoc¹ klawiatury i myszki
W, A, S, D - poruszanie siê kamer¹
mouse - rozgl¹danie siê (rotacja Yaw i Pitch)
left/right mouse button - zwiêkszenie/obni¿enie wysokoœci na której znajduje siê kamera

*/
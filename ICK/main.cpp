#include "MainController.h"

int main(int argc, char **argv)
{
	// Inicjowanie GLUT i tworzenie okna
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 100);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("OpenGL Figures");

	MainController::Init();

	glEnable(GL_DEPTH_TEST);	// OpenGL init

	// Init figures
	MainController::loadFiguresFromFile("Resources/data/example.xml");
	MainController::loadFiguresFromFile("Resources/data/background.xml");

	glutMainLoop();	// enter GLUT event processing cycle

	return 1;
}
#include <iostream>
#include "FiguresController.h"

FiguresController figuresController;
FiguresController backgroundController;

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear buffers (color, depth)
	glClearColor(0.0, 0.0, 0.0, 1.0);		// Set background

	figuresController.paintFigures();
	backgroundController.paintFigures();

	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y)
{

	switch (key) {
		case 27:
			exit(0);
			break;
	}

}

void processSpecialKeys(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_END:
		exit(0);
		break;
	}

}


int main(int argc, char **argv)
{

	figuresController.loadFiguresFromFile("Resources/data/example.xml");
	std::vector<Figure> figures2 = figuresController.getFigures();
	backgroundController.loadFiguresFromFile("Resources/data/background.xml");

	figuresController.setColor(255, 255, 255);
	backgroundController.setColor(0, 255, 0);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 100);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("OpenGL Figures");

	glEnable(GL_DEPTH_TEST);

	// register callbacks
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	// enter GLUT event processing loop
	glutMainLoop();

	return 1;
}



/*
Klasa Point --- > 2 pola typu int x i y, oznaczajace pozycje x i y punktu w przestrzeni, klasa zawiera standardowe gettery i settery getX() setX() getY() setY()

Klasa Figure --- > zawiera pole typu std::vector<Point>, zawiera 2 metody publiczne getPoints() zwracaj¹c¹ std::vector<Point> ze wszystkimi punktami, oraz addPoint(), wstawiaj¹c¹ punkt do figury

funkcja loadFigures(char * xmlName, std::vector<Figure>& figures) xmlName - > sciezka do pliku xml, figures referencja do vectora przechowujacego figury

obs³uga wygl¹da tak ¿e tworzy siê std::vector<Figure> , podaje sie go do funkcji loadFigures(), a ona wczytuje do tego vectora wszystkie figury z pliku xml

Przyklad dostania sie do poszczegolnych punktow danej figury podany jest ponizej

for (int i = 0; i < figures2.size(); i++) {
	std::vector<Point> points = figures2[i].getPoints();
	std::cout << "Figure " << i + 1 << ":" << std::endl;
	for (int j = 0; j < points.size(); j++) {
		std::cout << "[" << j << "] (" << points[j].getX() << "," << points[j].getY() << ")" << std::endl;
	}
	std::cout << std::endl;
}
*/
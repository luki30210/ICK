#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"

#include <iostream>
#include <vector>
#include "xml/Point.h"
#include "xml/Figure.h"
#include "xml/tinyxml2/tinyxml2.h"

void loadFigures(char * xmlName, std::vector<Figure>& figures);


void renderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.3, 0.3, 1.0);

	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	
	//PRZYKLAD UZYCIA FUNKCJI loadFigures() i obs�ugi figur

	/*
		Klasa Point --- > 2 pola typu int x i y, oznaczajace pozycje x i y punktu w przestrzeni, klasa zawiera standardowe gettery i settery getX() setX() getY() setY()

		Klasa Figure --- > zawiera pole typu std::vector<Point>, zawiera 2 metody publiczne getPoints() zwracaj�c� std::vector<Point> ze wszystkimi punktami, oraz addPoint(), wstawiaj�c� punkt do figury

		funkcja loadFigures(char * xmlName, std::vector<Figure>& figures) xmlName - > sciezka do pliku xml, figures referencja do vectora przechowujacego figury

		obs�uga wygl�da tak �e tworzy si� std::vector<Figure> , podaje sie go do funkcji loadFigures(), a ona wczytuje do tego vectora wszystkie figury z pliku xml

		Przyklad dostania sie do poszczegolnych punktow danej figury podany jest ponizej
	*/
	std::vector<Figure> figures;
	loadFigures("Resources/data/example.xml", figures);
	for (int i = 0; i < figures.size(); i++) {
		std::vector<Point> points = figures[i].getPoints();
		std::cout << "Figure " << i + 1 << ":" << std::endl;
		for (int j = 0; j < points.size(); j++) {
			std::cout << "[" << j << "] (" << points[j].getX() << "," << points[j].getY() << ")" <<std::endl;
		}
		std::cout << std::endl;
	}
	//KONIEC PRZYKLADU

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL First Window");

	glewInit();
	if (glewIsSupported("GL_VERSION_4_5"))
	{
		std::cout << " GLEW Version is 4.5\n ";
	}
	else
	{
		std::cout << "GLEW 4.5 not supported\n ";
	}

	glEnable(GL_DEPTH_TEST);
	// register callbacks
	glutDisplayFunc(renderScene);

	glutMainLoop();

	return 0;
}
void loadFigures(char * xmlName, std::vector<Figure>& figures) {
	using namespace tinyxml2;
	XMLDocument doc;
	doc.LoadFile(xmlName);

	XMLElement * figureElement = doc.FirstChildElement("root")->FirstChildElement("figure");//->FirstChildElement("point")->FirstAttribute()->IntValue();

	while (figureElement != nullptr) {
		Figure figure;
		XMLElement * pointElement = figureElement->FirstChildElement("point");
		while (pointElement != nullptr) {
			int x, y;
			pointElement->QueryAttribute("x", &x);
			pointElement->QueryAttribute("y", &y);
			Point point(x, y);
			figure.addPoint(point);
			pointElement = pointElement->NextSiblingElement();
		}
		figures.push_back(figure);
		figureElement = figureElement->NextSiblingElement();
	}
}
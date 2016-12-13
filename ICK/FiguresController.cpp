#include "FiguresController.h"



FiguresController::FiguresController()
{
}


FiguresController::~FiguresController()
{
}


void FiguresController::loadFiguresFromFile(char *filename) {
	figures.clear();
	using namespace tinyxml2;
	XMLDocument doc;
	doc.LoadFile(filename);

	XMLElement * figureElement = doc.FirstChildElement("root")->FirstChildElement("figure");

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
		this->figures.push_back(figure);
		figureElement = figureElement->NextSiblingElement();
	}
}

void FiguresController::paintFigure(int figureNumber)
{
	std::vector<Point> singleFigurePoints = this->getFigures()[figureNumber].getPoints();

	glBegin(GL_QUADS);
		glColor3f(0.3f, 0.65f, 1.0f);	// Light blue
		for (int i = 0; i < singleFigurePoints.size(); i++)
		{
			GLfloat x = (GLfloat)singleFigurePoints[i].getX() / (1280/2) - 1,
				y = (GLfloat)singleFigurePoints[i].getY() / (720 / 2) - 1;
			glVertex2f(x, y);
		}
	glEnd();
}

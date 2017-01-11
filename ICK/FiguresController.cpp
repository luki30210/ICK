#include "FiguresController.h"



FiguresController::FiguresController()
{
	this->color[0] = 0.3f;
	this->color[1] = 0.65f;
	this->color[2] = 1.0f;
	this->color[3] = 1.f;
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

void FiguresController::paintFigure(std::vector<Point> singleFigurePoints, float height)
{
	glBegin(GL_QUADS);
		glColor3f(color[0],color[1], color[2]);
		for (int i = 0; i < singleFigurePoints.size(); i++)
		{
			GLfloat x = (GLfloat)singleFigurePoints[i].getX() / (1280/2) - 1,
				y = (GLfloat)singleFigurePoints[i].getY() / (720 / 2) - 1;
			glVertex3f(x, height, y);
		}
	glEnd();
}

void FiguresController::paintFigures()
{
	for (int figureNumber = 0; figureNumber < this->figures.size(); figureNumber++)
	{
		this->paintFigure(this->figures[figureNumber].getPoints(), 0.1f);
	}
}

void FiguresController::paintBackground()
{
	for (int figureNumber = 0; figureNumber < this->figures.size(); figureNumber++)
	{
		this->paintFigure(this->figures[figureNumber].getPoints(), 0.0f);
	}
}
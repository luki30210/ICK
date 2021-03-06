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
		int r, g, b;
		figureElement->QueryAttribute("r", &r);
		figureElement->QueryAttribute("g", &g);
		figureElement->QueryAttribute("b", &b);
		printf("%d %d %d\n", r,g,b);
	    figure.setColor(r, g, b);
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
void FiguresController::paintFigure(Figure figure, float height)
{
	std::vector<Point> singleFigurePoints = figure.getPoints();
	glBegin(GL_POLYGON);
		glColor3f(figure.r(),figure.g(),figure.b());
		for (int i = 0; i < singleFigurePoints.size(); i++)
		{
			GLfloat x = -(GLfloat)singleFigurePoints[i].getX() / 720 - 1;
			GLfloat y = (GLfloat)singleFigurePoints[i].getY() / 720 - 1;
			glVertex3f(x, height, y);
		}
	glEnd();
}

void FiguresController::paintFigures()
{
	for (int figureNumber = 0; figureNumber < this->figures.size(); figureNumber++)
	{
		this->paintFigure(this->figures[figureNumber], 0.001f);
	}
}

void FiguresController::paintBackground()
{
	for (int figureNumber = 0; figureNumber < this->figures.size(); figureNumber++)
	{
		this->paintFigure(this->figures[figureNumber], 0.0f);
	}
}
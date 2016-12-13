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
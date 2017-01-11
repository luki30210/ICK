#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "xml/Figure.h"
#include "xml/tinyxml2/tinyxml2.h"
#include <vector>

class FiguresController
{

private:
	std::vector<Figure> figures;
	void paintFigure(std::vector<Point> singleFigurePoints, float height);
	double color[4];
	int above = 0;

public:
	FiguresController();
	~FiguresController();
	std::vector<Figure> getFigures() {
		return this->figures;
	}
	void setColor(int r, int g, int b, int alfa = 255) {
		double rNorm, gNorm, bNorm, alfaNorm;
		rNorm = r / 255.f;
		gNorm = g / 255.f;
		bNorm = b / 255.f;
		alfaNorm = alfa / 255.f;
		color[0] = rNorm;
		color[1] = gNorm;
		color[2] = bNorm;
		color[3] = alfaNorm;
	}
	void loadFiguresFromFile(char *filename);
	void paintFigures();
	void paintBackground();
};


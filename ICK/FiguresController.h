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
	void paintFigure(Figure figure, float height);
	double color[4];
	int above = 0;

public:
	FiguresController();
	~FiguresController();
	std::vector<Figure> getFigures() {
		return this->figures;
	}
	void loadFiguresFromFile(char *filename);
	void paintFigures();
	void paintBackground();
};


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

public:
	FiguresController();
	~FiguresController();
	std::vector<Figure> getFigures() {
		return this->figures;
	}
	void loadFiguresFromFile(char *filename);
	void paintFigure(int figureNumber);		// na razie public, póŸniej dorobi siê funkcjê rysuj¹c¹ wszystkie figury wykorzystuj¹c¹ private paintFigure()

};


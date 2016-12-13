#pragma once
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
};


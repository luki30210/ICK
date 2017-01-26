#ifndef FIGURE_H
#define FIGURE_H
#include<vector>
#include"Point.h"
/*
Klasa s³u¿¹ca do opisu figury na p³asczyŸnie, oraz przechowywnia informacji o jej kolorze.
*/
class Figure
{

public:
	Figure() {}
	virtual ~Figure() {}
	//Metoda zwraca wszystkie punkty sk³adaj¹ce siê na figurê
	std::vector<Point> getPoints() { return this->points; }
	//Metoda s³u¿¹ca do dodania punktu do figury.
	void addPoint(Point& point) { points.push_back(point); }
	//Metoda ustawiaj¹ca kolor figury, kolor opisywany jest za pomoc¹ modelu RGB, czwarty parametr o nazwie alfa okreœla przezroczystoœæ koloru.
	void setColor(int r, int g, int b, int alfa=255);
	//Zwraca sk³adow¹ r z modelu rgb
	double r() {
		return color[0];
	}
	//Zwraca sk³adow¹ g z modelu rgb
	double g() {
		return color[1];
	}
	//Zwraca sk³adow¹ b z modelu rgb
	double b() {
		return color[2];
	}
	//Zwraca wartoœæ parametru alfa, okreœlaj¹c¹ przezroczystoœæ koloru
	double a() {
		return color[3];
	}


protected:

private:
	//Kontener przechowuj¹cy wspó³rzedne x, y puntów sk³adaj¹cych siê na figurê, Klasa Point, to klasa stworzona w celu opisywania informacji
    // o punkcie.
	std::vector<Point> points;
	//Tablica przechowuj¹ca informacje o kolorze figury
	double color[4];


};

#endif // FIGURE_H



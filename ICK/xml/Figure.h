#ifndef FIGURE_H
#define FIGURE_H
#include<vector>
#include"Point.h"
/*
Klasa s�u��ca do opisu figury na p�asczy�nie, oraz przechowywnia informacji o jej kolorze.
*/
class Figure
{

public:
	Figure() {}
	virtual ~Figure() {}
	//Metoda zwraca wszystkie punkty sk�adaj�ce si� na figur�
	std::vector<Point> getPoints() { return this->points; }
	//Metoda s�u��ca do dodania punktu do figury.
	void addPoint(Point& point) { points.push_back(point); }
	//Metoda ustawiaj�ca kolor figury, kolor opisywany jest za pomoc� modelu RGB, czwarty parametr o nazwie alfa okre�la przezroczysto�� koloru.
	void setColor(int r, int g, int b, int alfa=255);
	//Zwraca sk�adow� r z modelu rgb
	double r() {
		return color[0];
	}
	//Zwraca sk�adow� g z modelu rgb
	double g() {
		return color[1];
	}
	//Zwraca sk�adow� b z modelu rgb
	double b() {
		return color[2];
	}
	//Zwraca warto�� parametru alfa, okre�laj�c� przezroczysto�� koloru
	double a() {
		return color[3];
	}


protected:

private:
	//Kontener przechowuj�cy wsp�rzedne x, y punt�w sk�adaj�cych si� na figur�, Klasa Point, to klasa stworzona w celu opisywania informacji
    // o punkcie.
	std::vector<Point> points;
	//Tablica przechowuj�ca informacje o kolorze figury
	double color[4];


};

#endif // FIGURE_H



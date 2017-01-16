#ifndef FIGURE_H
#define FIGURE_H
#include<vector>
#include"Point.h"

class Figure
{

public:
	Figure() {}
	virtual ~Figure() {}

	std::vector<Point> getPoints() { return this->points; }
	void addPoint(Point& point) { points.push_back(point); }
	void setColor(int r, int g, int b, int alfa=255);
	double r() {
		return color[0];
	}
	double g() {
		return color[1];
	}
	double b() {
		return color[2];
	}
	double a() {
		return color[3];
	}


protected:

private:
	std::vector<Point> points;
	double color[4];


};

#endif // FIGURE_H



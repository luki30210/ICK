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

protected:

private:
	std::vector<Point> points;
};

#endif // FIGURE_H



#ifndef POINT_H
#define POINT_H


class Point
{
public:
	Point(int x, int y) { this->x = x; this->y = y; }

	int getX() { return x; }
	void setX(int val) { x = val; }
	int getY() { return y; }
	void setY(int val) { y = val; }

protected:

private:
	int x;
	int y;
};

#endif // POINT_H

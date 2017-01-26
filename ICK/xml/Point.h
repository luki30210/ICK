#ifndef POINT_H
#define POINT_H
/*
Klasa s³u¿¹ca do opisu Punkty
Sk³ada siê z 2 pól sk³adowych x,y, oraz metod do ich ustawiania i pobierania.
*/

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

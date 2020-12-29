#pragma once
class Point {
	int x, y;
	friend class Corona;
	friend class Human;
	friend class Items;
public:
	Point(int xx = 0, int yy = 0) :x(xx), y(yy) {}
	int& operator[](int id)
	{
		if (id == 0)return x;
		else if (id == 1)return y;
	}
	bool operator==(const Point& p){
		if (x == p.x && y == p.y)
			return true;
		else return false;
	}
	void operator+= (const Point& p) { x += p.x, y += p.y; }
};
#pragma once
#include "���»�_Canvas.h"
#include "���»�_Point.h"
#include "���»�_Human.h"
class Items {
	friend class CoronaWorld;
protected:
	string name, icon;
	Point p;
public:
	Items(string n = "����", string i = "��", int x = 0, int y = 0)
		: name(n), icon(i), p(x, y) {}
	virtual ~Items() {}
	void draw(Canvas& canvas) { canvas.draw(p.x, p.y, icon); }
	virtual void active(Human* h)
	{
		h->life++;
	}
};
class Slow:public Items {
public:
	Slow(string n = "������", string i = "��", int x = 0, int y = 0)
		:Items(n, i, x, y) {}
	~Slow(){}
	void active(Human* h)
	{
		h->Stimer = 100;
	}
};
class Invinc :public Items {
public:
	Invinc(string n = "����", string i = "��", int x = 0, int y = 0)
		:Items(n, i, x, y) {}
	~Invinc(){}
	void active(Human* h)
	{
		h->Itimer = 70;
	}
};
#pragma once
#include "김태산_Human.h"
#include "김태산_Canvas.h"
#include "김태산_Point.h"
#include "김태산_Matrix.h"
class Corona {
protected:
	string name, icon; // name은 코로나이름, icon은 아이템 유무용
	Point p;
	virtual void clip(int maxx, int maxy) {
		if (p[0] < 0)p[0] = 0;
		if (p[0] >= maxx)p[0] = maxx - 1;
		if (p[1] < 0)p[1] = 0;
		if (p[1] >= maxy)p[1] = maxy - 1;
	} // Bcorona를 위한 가상함수
public:
	static int nCorona;
	Corona(string n = "김태산", string i = "※", int x=0, int y=0) // 멤버초기화 리스트 디폴트값
		:name(n), icon(i), p(x, y) {
		nCorona++;
	}
	virtual ~Corona() {
		nCorona--;
	} // 가상 소멸자이다. Corona가 사라지면 실행됨.
	virtual void draw(Canvas& canvas) { canvas.draw(p.x, p.y, icon); } 
	virtual void move(Matrix& world,int maxx, int maxy) {
		world.elem(p[1], p[0]) = 0;
		int num = rand() % 9 + 1;
		p += Point(num % 3 - 1, num / 3 - 1);
		clip(maxx, maxy);
		world.elem(p[1], p[0]) = 1;
	}
	void print() {
		cout << "\t" << name << icon <<  endl;
	}
};
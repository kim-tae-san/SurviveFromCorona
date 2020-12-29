#pragma once
#include "김태산_Corona.h"
#include <conio.h>
class Pcorona :public Corona { // 진화코로나는 최대 2칸 움직일 수 있다.
	int clock = 0;
public:
	Pcorona(string n = "진화코로나", string i = "◈", int x = 0, int y = 0)
		:Corona(n, i, x, y) {}
	~Pcorona() {}
	void move(Matrix& world, int maxx, int maxy) {
		if (clock % 2 == 0)
		{
			world.elem(p[1], p[0]) = 0;
			p[0] += rand() % 5 - 2;
			p[1] += rand() % 5 - 2;
			clip(maxx, maxy);
			world.elem(p[1], p[0]) = 1;
		}
		clock++;
	}
};
class Scorona :public Corona { // 슈퍼코로나는 플레이어를 따라간다.
	Human* h;
	int clock=0;
public:
	Scorona(Human* h,string n = "슈퍼코로나", string i = "★", int x = 0, int y = 0)
		:Corona(n, i, x, y),h(h){}
	~Scorona() { }
	void move(Matrix& world, int maxx, int maxy) {
		if (clock % 6 == 0) {
			world.elem(p[1], p[0]) = 0;
			if (h->p[0] > p[0]) p[0]++;
			else p[0]--;
			if (h->p[1] > p[1]) p[1]++;
			else p[1]--;
			clip(maxx, maxy);
			world.elem(p[1], p[0]) = 1;
			clock = 0;
		}
		clock++;
	}
};
class Bcorona :public Corona { // 거대코로나는 9칸을 차지한다.
	void clip(int maxx, int maxy) {
		if (p[0] < 1)p[0] = 1;
		if (p[0] >= maxx-1)p[0] = maxx - 2;
		if (p[1] < 1)p[1] = 1;
		if (p[1] >= maxy-1)p[1]= maxy - 2;
	}
public:
	Bcorona(string n = "거대코로나", string i = "■", int x = 0, int y = 0)
		:Corona(n, i, x, y) {}
	~Bcorona() {}
	void move(Matrix& world, int maxx, int maxy) {
		int num = rand() % 9 + 1;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
				world.elem(p[1]-1+j, p[0]-1+i) = 0; // Bcorona 아이콘 그리기
		}
		world.elem(p[1], p[0]) = 0;
		p += Point(num / 3 - 1, num % 3 - 1);
		clip(maxx, maxy);
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
				world.elem(p[1] - 1 + j, p[0] - 1 + i) = 1; // Bcorona 아이콘 그리기
		}
	}
	void draw(Canvas& canvas) {
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
				canvas.draw(p[0]-1+i, p[1]-1+j, icon);
		}
	}
};
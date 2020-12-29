#pragma once
#include "���»�_Human.h"
#include "���»�_Canvas.h"
#include "���»�_Point.h"
#include "���»�_Matrix.h"
class Corona {
protected:
	string name, icon; // name�� �ڷγ��̸�, icon�� ������ ������
	Point p;
	virtual void clip(int maxx, int maxy) {
		if (p[0] < 0)p[0] = 0;
		if (p[0] >= maxx)p[0] = maxx - 1;
		if (p[1] < 0)p[1] = 0;
		if (p[1] >= maxy)p[1] = maxy - 1;
	} // Bcorona�� ���� �����Լ�
public:
	static int nCorona;
	Corona(string n = "���»�", string i = "��", int x=0, int y=0) // ����ʱ�ȭ ����Ʈ ����Ʈ��
		:name(n), icon(i), p(x, y) {
		nCorona++;
	}
	virtual ~Corona() {
		nCorona--;
	} // ���� �Ҹ����̴�. Corona�� ������� �����.
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
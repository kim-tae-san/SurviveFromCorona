#pragma once
#include "���»�_Canvas.h"
#include "���»�_Point.h"
#include "���»�_Matrix.h"
#include <conio.h>
enum direction { Left = 75, Right = 77, Up = 72, Down = 80 };
class Human{
	string name, icon; // name�� �ڷγ��̸�, icon�� ������ ������
	Point p;
	friend class Scorona;
	friend class CoronaWorld; // active�� ����
	void clip(int maxx, int maxy) {
		if (p.x < 0)p.x = 0;
		if (p.x >= maxx)p.x = maxx - 1;
		if (p.y < 0)p.y = 0;
		if (p.y >= maxy)p.y = maxy - 1; 
	}
public:
	int Stimer = 0; // ������ Ÿ�̸�
	int Itimer = 0; // ���� Ÿ�̸�
	int life = 5; // �÷��̾� ���
	Human(string n = "���»�", string i = "��", int x = 0, int y = 0) // ����ʱ�ȭ ����Ʈ ����Ʈ��
		:name(n), icon(i), p(x, y) {}
	 ~Human() {}
	void draw(Canvas& canvas) { canvas.draw(p.x, p.y, icon); } // Call by Reference
	int getDirkey() { return _getche() == 224 ? _getche() : 0; }
	void move(int maxx, int maxy) {
		char ch = getDirkey();
		if (ch == Left)p.x--;
		else if (ch == Right)p.x++;
		else if (ch == Up)p.y--;
		else if (ch == Down)p.y++;
		else return;
		clip(maxx, maxy);
	}
	bool isSlow() {
		if (Stimer > 0)
		{
			Stimer--;
			return true;
		}
		return false;
	}
	bool isInvinc() {
		if (Itimer > 0)
		{
			Itimer--;
			return true;
		}
		return false;
	}
	void print() {
		cout << "\t" << name << icon << endl;
		cout << "���� ���:";
		for (int i = 0; i < life; i++ )
			cout << "��";
		cout << "\n";
	}
	void Hit(Matrix& world)
	{
		if (world.elem(p.y, p.x) == 1)
			life--;
	}
};
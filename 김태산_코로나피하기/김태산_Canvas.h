#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#define MAXLINES 100
using namespace std;
class Canvas {
	string line[MAXLINES]; // ȭ����¿� ���ڿ�
	int xMax, yMax; //���� ũ��
public:
	Canvas(int nx = 10, int ny = 10) :xMax(nx), yMax(ny) {
		for (int y = 0; y < yMax; y++)
			line[y] = string(xMax, '  '); // ������ 2byte�̾�� �ϹǷ� ���� ��ĭ
	}
	void draw(int x, int y, string val) {
		if (x >= 0 && y >= 0 && x < xMax && y < yMax)
			line[y].replace(x * 2, 2, val);
	}
	void clear(string val = "  ") {
		for (int y = 0; y < yMax; y++)
			for (int x = 0; x < xMax; x++)
				draw(x, y, val);
	}
	void print(const char* title = "<My Canvas>",int Level=0) { // ĵ���� ���
		system("cls");
		cout << title << "  Level : " << Level << endl;
		for (int y = 0; y < yMax; y++)
			cout << line[y] <<"|"<< endl;
		for (int x = 0; x < xMax; x++)
			cout << "��";
		cout << endl;
	}
};
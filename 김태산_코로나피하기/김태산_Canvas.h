#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#define MAXLINES 100
using namespace std;
class Canvas {
	string line[MAXLINES]; // 화면출력용 문자열
	int xMax, yMax; //맵의 크기
public:
	Canvas(int nx = 10, int ny = 10) :xMax(nx), yMax(ny) {
		for (int y = 0; y < yMax; y++)
			line[y] = string(xMax, '  '); // 공백이 2byte이어야 하므로 공백 두칸
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
	void print(const char* title = "<My Canvas>",int Level=0) { // 캔버스 출력
		system("cls");
		cout << title << "  Level : " << Level << endl;
		for (int y = 0; y < yMax; y++)
			cout << line[y] <<"|"<< endl;
		for (int x = 0; x < xMax; x++)
			cout << "ㅡ";
		cout << endl;
	}
};
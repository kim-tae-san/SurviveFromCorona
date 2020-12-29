#pragma once
class Matrix {
	int rows, cols; // 행 열 
	int** map; // 2차원 배열의 동적할당을 위한 이중포인터
public:
	Matrix(int r = 0, int c = 0) :rows(r), cols(c) {
		map = new int* [cols];
		for (int i = 0; i < cols; i++)
			map[i] = new int[rows];
	}
	~Matrix() {
		if (map != NULL) {
			for (int i = 0; i < cols; i++)
				delete[] map[i];
			delete[] map;
		}
	}
	int& elem(int x, int y) { return map[y][x]; } // Map(x,y)와 같은값 
};
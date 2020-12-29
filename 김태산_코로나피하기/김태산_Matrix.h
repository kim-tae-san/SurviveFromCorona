#pragma once
class Matrix {
	int rows, cols; // �� �� 
	int** map; // 2���� �迭�� �����Ҵ��� ���� ����������
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
	int& elem(int x, int y) { return map[y][x]; } // Map(x,y)�� ������ 
};
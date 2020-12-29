#pragma once
#include <iostream>
#include <fstream>
#include "���»�_Exception.h"
using namespace std;
#define NUM_MVP 5
struct PlayInfo {
	string name;
	int Level;
	int life;
	PlayInfo(string na = "������", int lev = 0, int life = 0)
		:name(na),Level(lev),life(life) {}
	~PlayInfo() {}
};
class RankingBoard {
	PlayInfo MVP[NUM_MVP];
	int nMVP = NUM_MVP;
public:
	void load(string filename)
	{
		ifstream is;
		is.open(filename);
		if (!is)
			throw(FileExeption(filename, false));
		for (int i = 0; i < nMVP; i++)
		{
			is >> MVP[i].name >>MVP[i].Level>>MVP[i].life;
		}
		is.close();
	}
	void store(string filename)
	{
		ofstream os;
		os.open(filename);
		if (!os) {
			throw(FileExeption(filename, true));
		}
		for (int i = 0; i < nMVP; i++)
		{
			os <<  " " << MVP[i].name <<" "<<MVP[i].Level <<" "<<MVP[i].life << "\n";
		}
		os.close();
	}
	void print(string title = "���� ��ŷ") {
		cout << endl << title << endl;
		for (int i = 0; i < nMVP; i++)
		{
			cout << "[" << i + 1 << "��]" << MVP[i].name << "\t" << " " << "Level : " << MVP[i].Level;
			if (MVP[i].life > 0)
			{
				cout << "  ��� : ";
				for (int j= 0; j < MVP[i].life; j++) {
					cout << "��";
				}
			}
			cout << "\n";
		}
		cout << "���͸� �Է��ϼ���.";
		getchar();
		cout << endl;
	}
	void add(int Level,int life)
	{
		if (Level <= MVP[nMVP - 1].Level)return ;

		int pos = nMVP - 1;
		for (; pos > 0; pos--) { //��ŷ�Է�
			if (Level < MVP[pos - 1].Level)
				break;
			else if (Level == MVP[pos - 1].Level)
			{
				if (life <= MVP[pos - 1].life)
					break;
			}
			if (pos > 1)
				MVP[pos - 1] = MVP[pos - 2];
			else
				MVP[1] = MVP[0];
		}
		cout << "\n[" << pos + 1 << "��] �̸��� �Է��ϼ���: ";
		cin >> MVP[pos].name;
		MVP[pos].Level = Level;
		MVP[pos].life = life;
	}
};
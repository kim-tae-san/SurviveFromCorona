#pragma once
#include <iostream>
#include <fstream>
#include "김태산_Exception.h"
using namespace std;
#define NUM_MVP 5
struct PlayInfo {
	string name;
	int Level;
	int life;
	PlayInfo(string na = "생존자", int lev = 0, int life = 0)
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
	void print(string title = "게임 랭킹") {
		cout << endl << title << endl;
		for (int i = 0; i < nMVP; i++)
		{
			cout << "[" << i + 1 << "위]" << MVP[i].name << "\t" << " " << "Level : " << MVP[i].Level;
			if (MVP[i].life > 0)
			{
				cout << "  목숨 : ";
				for (int j= 0; j < MVP[i].life; j++) {
					cout << "♥";
				}
			}
			cout << "\n";
		}
		cout << "엔터를 입력하세요.";
		getchar();
		cout << endl;
	}
	void add(int Level,int life)
	{
		if (Level <= MVP[nMVP - 1].Level)return ;

		int pos = nMVP - 1;
		for (; pos > 0; pos--) { //랭킹입력
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
		cout << "\n[" << pos + 1 << "위] 이름을 입력하세요: ";
		cin >> MVP[pos].name;
		MVP[pos].Level = Level;
		MVP[pos].life = life;
	}
};
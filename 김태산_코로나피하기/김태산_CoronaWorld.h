#pragma once
#include "김태산_Canvas.h"
#include "김태산_Corona.h"
#include "김태산_Matrix.h"
#include "김태산_VariousCorona.h"
#include "김태산_Human.h"
#include "김태산_Items.h"
#include <windows.h>
#define MAXCORS 8
#define MAXITEMS 6
class CoronaWorld {
	Matrix world;
	int xMax, yMax, nCor,nItems=0; // x,y 맵의 크기, nCor 코로나의 수
	int Level = 0;
	int clock = 0;
	int isexist[MAXITEMS] = { 0 }; // 동적 할당한 구역 제외용
	Corona* pCor[MAXCORS]; // 코로나 배열
	Human* player;
	Items* pItem[MAXITEMS];
	Canvas canvas;
	int& Map(int x, int y) { return world.elem(x, y); } // 좌표에 수를 입력받기위한 함수 (lvalue가능)
	void print() {
		canvas.clear(); // canvas를 초기화시킴
		for (int i = 0; i <nCor; i++)
			pCor[i]->draw(canvas); // Cor[i]에서 canvas를 복사생성자를 통해 Corona의 매개변수 대입.
		for (int i = 0; i < nItems; i++)
		{
			if (isexist[i] == 0)
			{
				pItem[i]->draw(canvas);
			}
		}
		player->draw(canvas);
		canvas.print("[ Survive from Corona ]",Level);
		player->print();
		for (int i = 0; i <nCor ; i++)
			pCor[i]->print(); //코로나 정보 출력
		printCount(); // 남은 코로나 수 출력
	}
	static void printCount() {
		cout << "\t" << "전체 코로나의 수 : " << Corona::nCorona << endl;
	}
	void Levelup()
	{
		static int nWalked = 0;
		if (nWalked % 200 == 0) {
			switch (Level / 2) {
			case 0:
				Cadd(new Corona("코로나", "※", rand() % xMax, rand() % yMax));
				nWalked += 100;
				break;
			case 1:
				Iadd(new Items("포션", "♥", rand() % xMax, rand() % yMax));
				Cadd(new Pcorona("진화코로나", "◈", rand() % xMax, rand() % yMax));
				nWalked += 50;
				break;
			case 2:
				Iadd(new Slow("느려짐", "♨", rand() % xMax, rand() % yMax));
				Cadd(new Scorona(player, "슈퍼코로나", "★", rand() % xMax, rand() % yMax));
				break;
			case 3:
				Iadd(new Invinc("무적", "♬", rand() % xMax, rand() % yMax));
				Cadd(new Bcorona("거대코로나", "■", rand() % (xMax - 2) + 1, rand() % (yMax - 2) + 1));
				break;
			default:
				break;
			}
			Level++;
		}
		nWalked++;
	}
	bool isDone(Human* h)
	{
		if (h->life == 0)
			return true;
		else 
			return false;
	}
public:
	CoronaWorld(int w, int h) :world(w, h), canvas(w, h), xMax(w), yMax(h) {
		nCor = 0;
		for (int y = 0; y < yMax; y++) {
			for (int x = 0; x < xMax; x++)
			{
				Map(y, x)=0;
			}
		}
	}
	~CoronaWorld() {
		for (int i = 0; i < nCor; i++)
			delete pCor[i];
		delete player;
		for (int i = 0; i < nItems; i++)
		{
			if (isexist[i] == 0)
				delete pItem[i];
		}

	}
	void Cadd(Corona* m) { // 코로나의 정보를 pCor 배열에 복사함
		if (nCor < MAXCORS)
			pCor[nCor++] = m;
	}
	void Iadd(Items* i) {
		if (nItems < MAXITEMS)
			pItem[nItems++] = i;
	}
	void Hadd(Human* h) {
		player = h;
	}
	void play(int maxwalk, int wait) {
		print();
		cerr << "엔터를 누르세요. . .";
		getchar();
		for (int i = 0; i < maxwalk; i++) {
			if (Level < 8)
				Levelup();
			if (player->isSlow()) {
				cout << "느려짐 시간 :" << player->Stimer << endl;
				clock = i % 2;
			}
			else clock = 0;
			for (int j = 0; j < nCor; j++)
			{
				if (clock)
					break;
				pCor[j]->move(world,xMax, yMax);
			}
			if (_kbhit())
			{
				player->move(xMax, yMax);
				for (int j = 0; j < nItems; j++)
				{
					if (isexist[j] == 0 && player->p == pItem[j]->p) // 논리연산자의 순서
					{
						pItem[j]->active(player);
						isexist[j] = 1;
						delete pItem[j];
					}
				}
			}
			if (!player->isInvinc())
				player->Hit(world);
			else
				cout<<"무적 시간:" << player->Itimer<<endl;
			print();
			if (isDone(player))
			{
				cout << "코로나에 감염되었습니다..." <<"\n"<<"엔터키 입력.."<< endl;
				getchar();
				return;
			}
			Sleep(wait);
		}
		cout << "코로나로 부터 해방되었습니다.. 이제 이 세상에 코로나는 없습니다."<<"\n" << "엔터키 입력.." << endl;
		getchar();
	}
	inline int level() { return Level; }
	inline int life() { return player->life; }
};
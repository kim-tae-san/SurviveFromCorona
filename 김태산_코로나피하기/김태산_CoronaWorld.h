#pragma once
#include "���»�_Canvas.h"
#include "���»�_Corona.h"
#include "���»�_Matrix.h"
#include "���»�_VariousCorona.h"
#include "���»�_Human.h"
#include "���»�_Items.h"
#include <windows.h>
#define MAXCORS 8
#define MAXITEMS 6
class CoronaWorld {
	Matrix world;
	int xMax, yMax, nCor,nItems=0; // x,y ���� ũ��, nCor �ڷγ��� ��
	int Level = 0;
	int clock = 0;
	int isexist[MAXITEMS] = { 0 }; // ���� �Ҵ��� ���� ���ܿ�
	Corona* pCor[MAXCORS]; // �ڷγ� �迭
	Human* player;
	Items* pItem[MAXITEMS];
	Canvas canvas;
	int& Map(int x, int y) { return world.elem(x, y); } // ��ǥ�� ���� �Է¹ޱ����� �Լ� (lvalue����)
	void print() {
		canvas.clear(); // canvas�� �ʱ�ȭ��Ŵ
		for (int i = 0; i <nCor; i++)
			pCor[i]->draw(canvas); // Cor[i]���� canvas�� ��������ڸ� ���� Corona�� �Ű����� ����.
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
			pCor[i]->print(); //�ڷγ� ���� ���
		printCount(); // ���� �ڷγ� �� ���
	}
	static void printCount() {
		cout << "\t" << "��ü �ڷγ��� �� : " << Corona::nCorona << endl;
	}
	void Levelup()
	{
		static int nWalked = 0;
		if (nWalked % 200 == 0) {
			switch (Level / 2) {
			case 0:
				Cadd(new Corona("�ڷγ�", "��", rand() % xMax, rand() % yMax));
				nWalked += 100;
				break;
			case 1:
				Iadd(new Items("����", "��", rand() % xMax, rand() % yMax));
				Cadd(new Pcorona("��ȭ�ڷγ�", "��", rand() % xMax, rand() % yMax));
				nWalked += 50;
				break;
			case 2:
				Iadd(new Slow("������", "��", rand() % xMax, rand() % yMax));
				Cadd(new Scorona(player, "�����ڷγ�", "��", rand() % xMax, rand() % yMax));
				break;
			case 3:
				Iadd(new Invinc("����", "��", rand() % xMax, rand() % yMax));
				Cadd(new Bcorona("�Ŵ��ڷγ�", "��", rand() % (xMax - 2) + 1, rand() % (yMax - 2) + 1));
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
	void Cadd(Corona* m) { // �ڷγ��� ������ pCor �迭�� ������
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
		cerr << "���͸� ��������. . .";
		getchar();
		for (int i = 0; i < maxwalk; i++) {
			if (Level < 8)
				Levelup();
			if (player->isSlow()) {
				cout << "������ �ð� :" << player->Stimer << endl;
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
					if (isexist[j] == 0 && player->p == pItem[j]->p) // ���������� ����
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
				cout<<"���� �ð�:" << player->Itimer<<endl;
			print();
			if (isDone(player))
			{
				cout << "�ڷγ��� �����Ǿ����ϴ�..." <<"\n"<<"����Ű �Է�.."<< endl;
				getchar();
				return;
			}
			Sleep(wait);
		}
		cout << "�ڷγ��� ���� �ع�Ǿ����ϴ�.. ���� �� ���� �ڷγ��� �����ϴ�."<<"\n" << "����Ű �Է�.." << endl;
		getchar();
	}
	inline int level() { return Level; }
	inline int life() { return player->life; }
};
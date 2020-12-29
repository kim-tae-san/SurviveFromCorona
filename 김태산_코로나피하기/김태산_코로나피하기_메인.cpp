#include "���»�_CoronaWorld.h"
#include "���»�_Ranking.h"
#include <time.h>
int Corona::nCorona = 0; // �ڷγ� �ʵ忡 �ִ� nCorona ���� �� �ʱ�ȭ
void main()
{
	int Dif;
	string fname;
	srand((unsigned int)time(NULL));
	RankingBoard rank;
	cout << " ���̵��� �����ϼ��� : 1. ���� 2. ���� 3. �����" << endl;
	try {
		cin >> Dif;
		if (Dif > 3 || Dif < 1)
			throw(Dif);
	}
	catch (int N) {
		cout << "Error : �߸��� ���̵� �Դϴ�, 1~3�� ���ڸ� �Է����ּ���."<<"\n"<< "�Էµ� ����:" << N << endl;
		exit(0);
	}
	switch (Dif)
	{
	case 1:
		fname = "CoronaWorld[Easy].rnk";
		break;
	case 2:
		fname = "CoronaWorld[Normal].rnk";
		break;
	case 3:
		fname = "CoronaWorld[Hard].rnk";
		break;
	default:
		break;
	}
    try {
		rank.load(fname);
	}
	catch (FileExeption e)
	{
		char str[80];
		string passwd, correct = "265314";
		cout << "������ ��й�ȣ�� �Է��ϼ���: ";
		for (int i = 0;; i++)
		{
			str[i] = _getch();
			putchar('*');
			if (str[i] == '\r') {
				str[i] = NULL;
				passwd = str;
				cout << "\n";
				break;
			}
		}
		if (passwd != correct)
		{
			cout << "��й�ȣ�� ���� �ʽ��ϴ�. ���� ����.\n\n";
			exit(0);
		}
		e.Fprintf();
	}
	rank.print("[���� ��ŷ:����]");
	CoronaWorld game(30 - 6 * Dif, 30 - 6 * Dif);
	getchar();
	game.Hadd(new Human("������", "��", rand() % (30 - 6 * Dif), rand() % (30 - 6 * Dif)));
	game.play(1700, 10);
	printf("-----------���� ����---------------\n");
	rank.add(game.level(),game.life());
	rank.print("[���� ��ŷ: ����]");
	try {
		rank.store(fname);
	}
	catch (FileExeption e)
	{
		char str[80];
		string passwd, correct = "265314";
		e.Fprintf();
		cout <<"\n" << "������ ��й�ȣ�� �Է��ϼ���: ";
		for (int i = 0;; i++)
		{
			str[i] = _getch();
			putchar('*');
			if (str[i] == '\r') {
				str[i] = '\0';
				passwd = str;
				cout << "\n";
				break;
			}
		}
		if (passwd != correct)
		{
			cout << "��й�ȣ�� ���� �ʽ��ϴ�. ���� ����.\n";
			exit(0);
		}
		switch (Dif)
		{
		case 1:
			fname = "CoronaWorld[Easy]_New.rnk";
			break;
		case 2:
			fname = "CoronaWorld[Normal]_New.rnk";
			break;
		case 3:
			fname = "CoronaWorld[Hard]_New.rnk";
			break;
		default:
			break;
		}
		rank.store(fname);
	}
}
#include "김태산_CoronaWorld.h"
#include "김태산_Ranking.h"
#include <time.h>
int Corona::nCorona = 0; // 코로나 필드에 있는 nCorona 선언 후 초기화
void main()
{
	int Dif;
	string fname;
	srand((unsigned int)time(NULL));
	RankingBoard rank;
	cout << " 난이도를 선택하세요 : 1. 쉬움 2. 보통 3. 어려움" << endl;
	try {
		cin >> Dif;
		if (Dif > 3 || Dif < 1)
			throw(Dif);
	}
	catch (int N) {
		cout << "Error : 잘못된 난이도 입니다, 1~3의 숫자를 입력해주세요."<<"\n"<< "입력된 숫자:" << N << endl;
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
		cout << "관리자 비밀번호를 입력하세요: ";
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
			cout << "비밀번호가 맞지 않습니다. 게임 종료.\n\n";
			exit(0);
		}
		e.Fprintf();
	}
	rank.print("[게임 랭킹:시작]");
	CoronaWorld game(30 - 6 * Dif, 30 - 6 * Dif);
	getchar();
	game.Hadd(new Human("생존자", "♀", rand() % (30 - 6 * Dif), rand() % (30 - 6 * Dif)));
	game.play(1700, 10);
	printf("-----------게임 종료---------------\n");
	rank.add(game.level(),game.life());
	rank.print("[게임 랭킹: 종료]");
	try {
		rank.store(fname);
	}
	catch (FileExeption e)
	{
		char str[80];
		string passwd, correct = "265314";
		e.Fprintf();
		cout <<"\n" << "관리자 비밀번호를 입력하세요: ";
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
			cout << "비밀번호가 맞지 않습니다. 게임 종료.\n";
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
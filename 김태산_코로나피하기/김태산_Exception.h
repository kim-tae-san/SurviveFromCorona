#pragma once
#include <string>
using namespace std;
struct FileExeption {
	string filename;
	bool bRead; // �б����϶� true , �������϶� false
	FileExeption(string name, bool b) :filename(name), bRead(b) {}
	void Fprintf() {
		if (bRead)
			cout << "������ �б����Դϴ�. ���ο� ������ ����ϴ�.";
		else
			cout << "������ �����ϴ�. ���ο� ������ ����ϴ�.";
	}
};
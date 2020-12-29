#pragma once
#include <string>
using namespace std;
struct FileExeption {
	string filename;
	bool bRead; // 읽기모드일때 true , 쓰기모드일때 false
	FileExeption(string name, bool b) :filename(name), bRead(b) {}
	void Fprintf() {
		if (bRead)
			cout << "파일이 읽기모드입니다. 새로운 파일을 만듭니다.";
		else
			cout << "파일이 없습니다. 새로운 파일을 만듭니다.";
	}
};
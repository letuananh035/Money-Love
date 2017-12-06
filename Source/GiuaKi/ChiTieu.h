#pragma once
#include <ctime>
#include <string>
#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
#include <Objbase.h>
#pragma comment(lib, "Ole32.lib")
using namespace Gdiplus;
using namespace std;
enum TypeChiTieu{
	AN,
	DICHUYEN,
	NHA,
	CHO,
	DICHVU,
	LUONG,
	KHOANTHUKHAC,
	THU, // Chỉ sử dụng vẽ biểu đồ
	CHI // Chỉ sử dụng vẽ biểu đồ
};
class ChiTieu
{
public:
	TypeChiTieu type;
	int tien;
	//time_t date;
	TCHAR chuthich[200];
	TCHAR* getStringType();
	Color getColor();
	TCHAR* getImage();
	TCHAR* getMoney();
	ChiTieu();
	~ChiTieu();
};

TCHAR* MakeMoney(int money);
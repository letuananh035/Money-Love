#include "stdafx.h"
#include "ChiTieu.h"


ChiTieu::ChiTieu()
{
}


ChiTieu::~ChiTieu()
{
}


TCHAR* ChiTieu::getStringType(){
	if (type == AN) return L"Ăn uống";
	else if (type == TypeChiTieu::CHO) return L"Mua Sắm";
	else if (type == TypeChiTieu::DICHUYEN) return L"Di chuyển";
	else if (type == TypeChiTieu::DICHVU) return L"Dịch vụ";
	else if (type == TypeChiTieu::KHOANTHUKHAC) return L"Khoản thu khác";
	else if (type == TypeChiTieu::LUONG) return L"Lương";
	else if (type == TypeChiTieu::NHA) return L"Nhà";
}

Color ChiTieu::getColor(){
	if (type == LUONG || type == KHOANTHUKHAC) return Color(255, 52, 152, 219);
	return  Color(255, 231, 76, 60);
}

TCHAR* ChiTieu::getImage(){
	if (type == AN) return L"Data/restaurant.png";
	else if (type == TypeChiTieu::CHO) return L"Data/cart.png";
	else if (type == TypeChiTieu::DICHUYEN) return L"Data/taxi.png";
	else if (type == TypeChiTieu::DICHVU) return L"Data/navigation.png";
	else if (type == TypeChiTieu::KHOANTHUKHAC) return L"Data/coin.png";
	else if (type == TypeChiTieu::LUONG) return L"Data/money-bag.png";
	else if (type == TypeChiTieu::NHA) return L"Data/house.png";
}

TCHAR* ChiTieu::getMoney(){
	/*std::wstring buffer = std::to_wstring(this->tien);
	std::wstring result = L"";
	int check = 0;
	for (int i = buffer.length() - 1; i >= 0; i--){
		if (check == 3 && buffer[i] != '-'){
			result = L"," + result;
			check = 0;
		}
		result = buffer[i] + result;
		check++;
	}
	result += L" đ";
	TCHAR* resultTchar = new TCHAR[result.size() + 1];
	_tcscpy(resultTchar, result.c_str());
	return resultTchar;*/
	return MakeMoney(this->tien);
}

TCHAR* MakeMoney(int money){
	std::wstring buffer = std::to_wstring(money);
	std::wstring result = L"";
	int check = 0;
	for (int i = buffer.length() - 1; i >= 0; i--){
		if (check == 3 && buffer[i] != '-'){
			result = L"," + result;
			check = 0;
		}
		result = buffer[i] + result;
		check++;
	}
	result += L" đ";
	TCHAR* resultTchar = new TCHAR[result.size() + 1];
	_tcscpy(resultTchar, result.c_str());
	return resultTchar;
}
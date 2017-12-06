#include "stdafx.h"
#include "DataManager.h"
#include <ctime>

DataManager::DataManager()
{
}


DataManager::~DataManager()
{
}


void DataManager::MakeDate(){
	time_t now = time(0);
	tm *ltm = localtime(&now);
	this->date.day = ltm->tm_mday;
	this->date.month = 1 + ltm->tm_mon;
	this->date.year = 1900 + ltm->tm_year;
	this->date.thu = ltm->tm_wday;
}

TCHAR* DataManager::getMoney(){
	int sum = 0;
	for (int i = 0; i < listChiTieu.size(); ++i){
		if (listChiTieu[i].type == LUONG || listChiTieu[i].type == TypeChiTieu::KHOANTHUKHAC){
			sum += listChiTieu[i].tien;
		}
		else{
			sum -= listChiTieu[i].tien;
		}
	}
	/*std::wstring buffer = std::to_wstring(sum);
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
	return  MakeMoney(sum);
}
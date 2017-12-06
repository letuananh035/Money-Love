#pragma once

#include "ChiTieu.h"
#include <vector>
struct Date{
	int day;
	int month;
	int year;
	int thu;
	bool operator==(const Date &other){
		return (this->day == other.day && this->month == other.month && this->year == other.year);
	}
};
class DataManager
{
public:
	vector<ChiTieu> listChiTieu;
	Date date;
	void MakeDate();
	TCHAR* getMoney();
	DataManager();
	~DataManager();
};


#include "Date.h"

//cria uma date do dia atual
Date::Date(){
	time_t t = time(0);   // get time now
	struct tm  now;
	localtime_s(&now,&t);

	year = (now.tm_year + 1900);
	month = (now.tm_mon + 1);
	day = now.tm_mday;
	totaldays = day + 32 * month + 367 * year;
	is_valid = true;
}
int maxmonthday(int month){
	switch (month){
	case 4: case 6: case 9: case 11:
		return 30;
	case 2:
		return 29;
	default:
		return 31;
	}
}
Date::Date(string dataStr){
	string tmp;
	int pos;
	bool notfoundchar = false;
	pos = dataStr.find('/');
	if (pos == -1)
		notfoundchar = true;
	else {
		tmp = dataStr.substr(0, pos);
		day = stoi(tmp);
		dataStr.erase(0, pos + 1);
		pos = dataStr.find('/');
		if (pos == -1)
			notfoundchar = true;
		else {
			tmp = dataStr.substr(0, pos);
			month = stoi(tmp);
			dataStr.erase(0, pos + 1);
			year = stoi(dataStr);
			totaldays = day + 32 * month + 367 * year;
		}
	}

	int tmpmonth = month;
	if (notfoundchar || month > 12 || day > maxmonthday(tmpmonth))
		is_valid = false;
	else
		is_valid = true;
		
}

int Date::getDay() const{
	return day;
}

int Date::getMonth() const{
	return month;
}

int Date::getYear() const{
	return year;
}

int Date::getTotaldays() const{
	return totaldays;
}

bool Date::getis_valid() const{
	return is_valid;
}

void Date::setDay(int dia){
	day = dia;
	totaldays = day + 32 * month + 367 * year;
}

void Date::setMonth(int mes){
	month = mes;
	totaldays = day + 32 * month + 367 * year;
}

void Date::setYear(int ano){
	year = ano;
	totaldays = day + 32 * month + 367 * year;
}

void Date::save(ofstream & out) const{
	out << day << '/' << month << '/' << year;
	return;
}

ostream& operator<<(ostream& out, const Date & data){
	out << data.day << '/' << data.month << '/' << data.year;
	return out;
}

bool operator<(const Date &date1, const Date &date2){
	return date1.totaldays < date2.totaldays;
}

#include "Functions.h"



int leInteiro(int minimum){
	int inttoread;
	bool is_valid = false;

	while (!is_valid){
		if (!(cin >> inttoread) || inttoread < minimum){
			cerr << "Invalid Input!" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Tente novamente: ";
		}
		else is_valid = true;
	}
	return inttoread;
}

bool menu_input_error(unsigned short int &toinput, const int maxop){

	if ((!(cin >> toinput)) || toinput < 1 || toinput > maxop)
	{
		cerr << "Invalid Input!" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return false;
	}
	return true;
}

string strtrim(string str)
{
	while (isspace(*str.begin()))
		str.erase(str.begin());

	while (isspace(*str.rbegin()))
		str.erase(str.length() - 1);
	return str;
}

string readstring(){
	string newname;
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); //needed to eleminate \n from the buffer before using getline(cin,...)
	while (true)                                         
	{
		getline(cin, newname);
		bool whiteSpacesOnly = all_of(newname.begin(), newname.end(), isspace);
		if (newname.length() > 25){
			cin.clear();
			cin.ignore(1000, '\n');
			cerr << "Invalid Input!" << endl;
			cout << "Tente novamente: ";
		}
		else if (newname == "" || whiteSpacesOnly){
			cin.clear();
			cerr << "Invalid Input!" << endl;
			cout << "Tente novamente: ";
		}
		else break;
	}
	newname= strtrim(newname);
	newname.at(0) = toupper(newname.at(0));
	return newname;
}
#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

#include "Date.h"
#include "Functions.h"


using namespace std;


class Transaction {
private:
	unsigned int idClient;
	Date data; // na forma DD/MM/AAAAA
	vector<string> productsbought;

public:
	Transaction(unsigned int id, vector<string> productsbought);
	Transaction(ifstream & in); // transacao na forma de  idCliente ; data ; lista de produtos
	unsigned int getIdClient() const;
	Date getData() const;
	vector < string > getProductsbought() const;
	void save(ofstream & out) const; // guarda a transacao
	friend ostream& operator<<(ostream& out, const Transaction & trans); // mostra a transacao
	friend bool operator<(const Transaction &tran1, const Transaction &tran2);
};


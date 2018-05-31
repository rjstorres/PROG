#pragma once


#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "Date.h"
#include "Functions.h"
using namespace std;


class Client {
private:
	unsigned int id;
	string name;
	Date Clientcard;
	float volPurchased;
	

public:
	Client(unsigned int id, string name);
	Client(ifstream & in);
	string getName() const;
	unsigned int getId() const;
	float getVolPurchased() const;
	void setname(string newname);
	void setvolPurchased(float addtovolpurchased);
	void save(ofstream & out) const;
	friend ostream& operator<<(ostream& out, const Client & cli);  // mostra informacao do cliente no ecra
	friend bool operator<(const Client &cli1, const Client &cli2); // compara 2 clientes (1 cliente e menor que outro se o seu nome for "alfabeticamente" inferior)
};

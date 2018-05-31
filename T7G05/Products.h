#pragma once



#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "Functions.h"
using namespace std;



class Product {
private:
	string name;
	float price;


public:
	Product(ifstream & in);
	string getName() const;
	float getPrice() const;
	friend ostream& operator<<(ostream& out, const Product & prod); // mostra um produto
	friend bool operator<(const Product &prod1, const Product &prod2); // compara dois produtos (1 produto e mais pequeno que outro se o seu nome for "alfabeticamente inferior"
};


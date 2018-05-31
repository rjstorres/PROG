#include "Products.h"



Product::Product(ifstream & in){ // nome ; custo
	string line, tmp;
	int pos;

	getline(in, line);
	pos = line.find(';');
	tmp = line.substr(0, pos);
	name = strtrim(tmp);
	line.erase(0, pos + 1);
	price = stof(line);
}

string Product::getName() const {
	return name;
}

float Product::getPrice() const {
	return price;
}

ostream& operator<<(ostream& out, const Product & prod){
	out << setw(19) << left <<  prod.name << setw(5) << right << setprecision(2) << fixed << prod.price;
	return out;

}


bool operator<(const Product &prod1, const Product &prod2){
	return prod1.name < prod2.name;
}


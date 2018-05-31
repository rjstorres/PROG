#include "Transaction.h"


Transaction::Transaction(unsigned int id, vector < string > productsbought){
	idClient = id;
	this->productsbought = productsbought;
	data = Date{};
}

Transaction::Transaction(ifstream & in){ // le uma transacao na forma de  idcliente ; data ; lista produtos
	string line, tmp;
	int pos;

	getline(in, line);
	pos = line.find(';');
	tmp = line.substr(0, pos);
	idClient = stoi(tmp);
	line.erase(0, pos + 1);
	pos = line.find(';');
	tmp = line.substr(0, pos);
	data = Date(tmp);
	line.erase(0, pos + 1);

	pos = 0;
	while (pos != -1){
		pos = line.find(',');
		if (pos != -1){
			tmp = line.substr(0, pos);
			tmp = strtrim(tmp);
			line.erase(0, pos + 1);
			productsbought.push_back(tmp);
		}
		else{
			line = strtrim(line);
			productsbought.push_back(line);
		}
	}

}

unsigned int Transaction::getIdClient() const{
	return idClient;
}

Date Transaction::getData() const{
	return data;
}

vector < string > Transaction::getProductsbought() const{
	return productsbought;
}

void Transaction::save(ofstream & out) const{ // transacao guardada como na forma de  idcliente ; data ; lista produtos
	out << idClient << " ; " << data << " ; ";
	for (size_t i = 0; i < productsbought.size(); i++){
		if (i != productsbought.size() - 1)
			out << productsbought.at(i) << " , ";
		else
			out << productsbought.at(i) << endl;
	}
	return;
}


ostream& operator<<(ostream& out, const Transaction & trans){
	out << setw(5) << trans.idClient << setw(6) << trans.data << "  ";
	cout << trans.productsbought.at(0);
	for (size_t i = 1; i < trans.productsbought.size(); i++)
		out << " , " << trans.productsbought.at(i);
	return out;
}

bool operator<(const Transaction &tran1, const Transaction &tran2){
	return tran1.data<tran2.data;
}

#include "Client.h"


Client::Client(unsigned int id, string name){
	this->id = id;
	this->name = name;
	Clientcard = Date();
	volPurchased = 0.0;
}

Client::Client(ifstream & in){
	string line, tmp;
	int pos;
	
	getline(in, line);
	pos = line.find(';');
	tmp = line.substr(0, pos);
	id = stoi(tmp);
	line.erase(0, pos + 1);
	pos = line.find(';');
	tmp = line.substr(0, pos);
	tmp = strtrim(tmp);
	tmp.at(0)=toupper(tmp.at(0));
	name = tmp;
	line.erase(0, pos + 1);
	pos = line.find(';');
	tmp = line.substr(0, pos);
	Clientcard = Date(tmp);
	line.erase(0, pos + 1);
	volPurchased = stof(line);
}


string Client::getName() const{
	return name;
}

unsigned int Client::getId() const{
	return id;
}

float Client::getVolPurchased() const{
	return volPurchased;
}
void Client::setname(string newname){
	name = newname;
}

void Client::setvolPurchased(float addtovolpurchased){
	volPurchased += addtovolpurchased;
}

void Client::save(ofstream & out) const{
	out << id << " ; " << name << " ; " << Clientcard << " ; " << setprecision(2) << fixed << volPurchased << endl;
	return;
}

ostream& operator<<(ostream& out, const Client & cli){
	out << setw(5) << cli.id << setw(25) << cli.name << setw(10) << cli.Clientcard << setw(10) << setprecision(2) << fixed << cli.volPurchased; 
	return out;
}


bool operator<(const Client &cli1, const Client &cli2){
	return cli1.volPurchased<cli2.volPurchased;
}

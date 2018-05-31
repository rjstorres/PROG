#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <map>
#include <set>

#include "Products.h"
#include "Functions.h"
#include "Client.h"
#include "Transaction.h"
#include "defs.h"
#include "Date.h"

using namespace std;

class Supermarket 
{
public:
	Supermarket(string store, string clientsFile, string productsFile, string transactionsFile);
	//gestão de clientes
	void List_all_clients() const; //lista todos os clientes em ordem alfabética
	void change_client_name(); //muda o nome de um cliente
	void creat_new_client(); //cria novo cliente
	void remove_client();
	//gestão de transacoes
	void aux_l_t_b_d(Date date1, Date date2) const;
	void list_transactions_beetween_dates(Supermarket supermercado) const;
	void list_client_transactions() const;
	void make_transaction();
	//informacoes
	void list_client_info() const;
	void list_day_transactions() const;
	void list_all_transactions() const;
	void list_all_products() const;
	//recomendacoes
	void recommendations() const;
	void bottom10() const;
	//save and operator << 
	void save() const;
	friend ostream& operator<<(ostream& out, const Supermarket & super);

private:
	string store; // nome da loja
	string clientsFile, productsFile, transactionsFile; // nome dos
	// ficheiros de
	// clientes,
	// produtos e
	// transacoes
	bool modified_Transactions; // flag que fica a true se for preciso guardar no final as transacoes
	bool modified_clients; // flag que fica a true se for preciso guardar no final os clienets
	unsigned int maxClientsId; // variavel que guarda o identificador unico do cliente com o maior identiicador
	vector< Client > allclients; // vetor que guarda a informacao dos clientes existentes
	vector< Product > allproducts; // vetor que guarda a informacao dos produtos disponiveis
	vector< Transaction > alltransactions; // vetor que guarda a informacao das ttransacoes efetuadas
	map< string, unsigned int> clientIdx;  // map para "traduzir" nome do cliente no indice dele no vetor de clientes
	map <unsigned int, unsigned int> idtoclient; //map para "traduzir" id do cliente e a sua posição no vetor
	map< string, unsigned int> productIdx;  // map para "traduzir" nome do produto no indice dele no vetor de produtos
	multimap<unsigned int, unsigned int> transactionIdx;// multima para "traduzir" o id nas suas posições no vetor

};
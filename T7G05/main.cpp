#include <iostream>
#include <string>
#include <vector>

#include "supermarket.h"
#include "Menus.h"
#include "defs.h"

using namespace std;
int main(){	
	string loja, fichClients, fichProdutos, fichTransacoes;
	bool exist_file = false;
	ifstream fclients;
	ifstream fproducts;
	ifstream ftransactions;
	cout << TAB_BIG << "Bem-vindo ao programa que o ajudara a gerir o Vender++" << endl << endl;
	// pede a informacoo sobre o nome da loja e os 3 ficheiros com
	// informacoo de clientes, produtos e transacoes

	while (!exist_file) {
		cout << "Insira o nome da loja pertencente ao grupo Vende++:" << endl;
		cin >> loja;
		cout << "Insira o nome do ficheiro que contem a informacao dos clientes: " << endl;
		cin >> fichClients;
		cout << "Insira o nome do ficheiro que contem a informacao dos produtos disponiveis:" << endl;
		cin >> fichProdutos;
		cout << "Insira o nome do ficheiro que contem a informacao das transacoes realizadas: " << endl;
		cin >> fichTransacoes;

		fclients.open(fichClients);
		fproducts.open(fichProdutos);
		ftransactions.open(fichTransacoes);

		if (fclients.is_open() && fproducts.is_open() && ftransactions.is_open()){
			exist_file = true;
		}
		else
			cerr << "Erro ao tentar abrir os ficheiros!" << endl << "Tente novamente!" << endl << endl;
		fclients.close();
		fproducts.close();
		ftransactions.close();
	}

	Supermarket supermercado(loja, fichClients, fichProdutos,fichTransacoes);
	system("cls");
	cout << TAB_BIG << "Informacao da loja " << loja << " do supermercado Vende++:" << endl << endl;
	cout << supermercado << endl;  // mostra estatisticas da loja*/

	// menu inicial com as grandes opcoes
	// que implementam as funcioanlidades
	// disonibilizadas
	Home_menu(supermercado);
	supermercado.save();
	return 0;
}
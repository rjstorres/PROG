#include "Menus.h"

/******************************************
* Gestao de Clientes
******************************************/
void Client_management_menu(Supermarket &supermercado){
	unsigned short int optionCMM;
	bool go_exitCMM = false;

	while (!go_exitCMM){
		system("cls");
		cout << TAB_BIG << "Menu Gestao Clientes" << endl;
		cout << endl;
		cout << TAB << "1 - Listar clientes" << endl;
		cout << TAB << "2 - Criar cliente" << endl;
		cout << TAB << "3 - Editar nome de um cliente" << endl;
		cout << TAB << "4 - Remover cliente" << endl;
		cout << TAB << "5 - Voltar ao menu inicial" << endl << endl;

		cout << "Escolha uma opcao: ";
		while (!menu_input_error(optionCMM, 5)){
			cout << "Escolha uma opcao: ";
		}

		switch (optionCMM)
		{
		case 1:
			supermercado.List_all_clients();
			break;
		case 2:
			supermercado.creat_new_client();
			break;
		case 3:
			supermercado.change_client_name();
			break;
		case 4:
			supermercado.remove_client();
			break;
		case 5:
			go_exitCMM = true;
			break;
		}
	}
	return;
}


/******************************************
* Gestao de Transacoes
******************************************/
void Transactions_management_menu(Supermarket &supermercado){
	unsigned short int optionTMM;
	bool go_exitTMM = false;

	while (!go_exitTMM){
		system("cls");
		cout << TAB_BIG << "Menu Gestao Transacoes" << endl;
		cout << endl;
		cout << TAB << "1 - Listar todas as transacoes num intervalo de tempo data" << endl;
		cout << TAB << "2 - Listar transacoes de um cliente (atraves do seu nome)" << endl;
		cout << TAB << "3 - Efetuar transacoes" << endl;
		cout << TAB << "4 - Voltar ao menu inicial" << endl << endl;
		cout << "Escolha uma opcao: ";

		while (!menu_input_error(optionTMM, 4)){
			cout << "Escolha uma opcao: ";
		}

		switch (optionTMM)
		{
		case 1:
			supermercado.list_transactions_beetween_dates(supermercado);
			break;
		case 2:
			supermercado.list_client_transactions();
			break;
		case 3:
			supermercado.make_transaction();
			break;
		case 4:
			go_exitTMM = true;
			break;
		}
	}
	return;
}

/******************************************
* Menu de Informações
******************************************/
void Information_menu(Supermarket &supermercado){
	unsigned short int optionIM;
	bool go_exitIM = false;

	while (!go_exitIM)
	{
		system("cls");
		cout << TAB_BIG << "Visualizar informacao:" << endl;
		cout << endl;
		cout << TAB << "1 - Visualizar informacao de um Cliente" << endl;
		cout << TAB << "2 - Visualizar transacoes de um dia" << endl;
		cout << TAB << "3 - Visualizar todas as transacoes" << endl;
		cout << TAB << "4 - Visualizar produtos disponiveis" << endl;
		cout << TAB << "5 - Voltar ao menu inicial" << endl << endl;

		cout << "Escolha uma opcao: ";
		while (!menu_input_error(optionIM, 6)){
			cout << "Escolha uma opcao: ";
		}

		switch (optionIM)
		{
		case 1:
			supermercado.list_client_info();
			break;
		case 2:
			supermercado.list_day_transactions();
			break;
		case 3:
			supermercado.list_all_transactions();
			break;
		case 4:
			supermercado.list_all_products();
			break;
		case 5:
			go_exitIM = true;
			break;
		}
	}
	return;
}

/******************************************
* Menu de recomendações
******************************************/
void Recommendations_menu(Supermarket &supermercado){
	unsigned short int optionRM;
	bool go_exitRM = false;

	while (!go_exitRM)
	{
		system("cls");
		cout << TAB_BIG << "Recomendacoes:" << endl;
		cout << endl;
		cout << TAB << "1 - Campanha Bottom10" << endl;
		cout << TAB << "2 - Recomendacao personalizada" << endl;
		cout << TAB << "3 - Voltar ao menu inicial" << endl << endl;

		cout << "Escolha uma opcao: ";
		while (!menu_input_error(optionRM, 3)){
			cout << "Escolha uma opcao: ";
		}

		switch (optionRM)
		{
		case 1:
			supermercado.bottom10();
			break;
		case 2:
			supermercado.recommendations();
			break;
		case 3:
			go_exitRM = true;
			break;
		}
	}
	return;
}


/******************************************
* Menu Inicial
******************************************/
void Home_menu(Supermarket &supermercado){
	unsigned short int optionHM;
	bool go_exitHM = false;

	while (!go_exitHM){
		system("cls");
		cout << TAB_BIG << "Menu Inicial" << endl;
		cout << endl;
		cout << TAB << "1 - Gestao de clientes" << endl;
		cout << TAB << "2 - Informacoes sobre clientes, transacoes e produtos" << endl;
		cout << TAB << "3 - Gestao de transacoes" << endl;
		cout << TAB << "4 - Recomendacoes" << endl;
		cout << TAB << "5 - Sair do programa" << endl << endl;

		cout << "Escolha uma opcao: ";

		while (!menu_input_error(optionHM, 5)){
			cout << "Escolha uma opcao: ";
		}

		switch (optionHM)
		{
		case 1:
			Client_management_menu(supermercado);
			break;
		case 2:
			Information_menu(supermercado);
			break;
		case 3:
			Transactions_management_menu(supermercado);
			break;
		case 4:
			Recommendations_menu(supermercado);
			break;
		case 5:
			go_exitHM = true;
			break;
		}
	}
	return;
}



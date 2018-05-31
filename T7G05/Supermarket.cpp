#include "Supermarket.h"

//construtor
Supermarket::Supermarket (string loja, string fichClients, string fichProdutos, string fichTransacoes){
	store = loja;
	clientsFile = fichClients;
	productsFile = fichProdutos;
	transactionsFile = fichTransacoes;
	modified_Transactions = false;
	modified_clients = false;
	//used to get vectors
	int tmp;
	string stmp;
	//from textfile to vector allclients
	
	ifstream clients;
	clients.open(clientsFile);
	getline(clients,stmp); //number of clients on a string
	tmp = stoi(stmp); //numberofclients
	for (int i = 0; i < tmp; i++)
		allclients.push_back(Client(clients));
	clients.close();

	//max clients
	maxClientsId = 0;//inicialize at 0 because minimum Id is 1
	for (size_t i = 0; i < allclients.size(); i++){
		if (allclients.at(i).getId()>maxClientsId)
			maxClientsId = allclients.at(i).getId();
	}

	//from textfile to vector all products
	ifstream products;
	products.open(productsFile);
	getline(products, stmp); //number of products on a string
	tmp = stoi(stmp); //numberofproducts
	for (int i = 0; i < tmp; i++)
		allproducts.push_back(Product(products));
	products.close();


	//from textfile to vector all products
	ifstream transactions;
	transactions.open(transactionsFile);
	getline(transactions, stmp); //number of products on a string
	tmp = stoi(stmp); //numberofproducts
	for (int i = 0; i < tmp; i++)
		alltransactions.push_back(Transaction(transactions));
	transactions.close();

	//maps with name/id of a client and position on repective vector
	for (unsigned int i = 0; i < allclients.size(); i++){
		clientIdx.insert(pair <string, unsigned int>(allclients.at(i).getName(), i));
		idtoclient.insert(pair <unsigned int, unsigned int>(allclients.at(i).getId(), i));
	}

	//map with product and position in the vector
	for (unsigned int i = 0; i < allproducts.size(); i++)
		productIdx.insert(pair <string, unsigned int>(allproducts.at(i).getName(), i));

	//map for transactions id->position on the vector
	for (unsigned int i = 0; i < alltransactions.size(); i++)
		transactionIdx.insert(pair <int, unsigned int>(alltransactions.at(i).getIdClient(), i));
}

//gestão de clientes
void Supermarket::List_all_clients() const{
	system("cls");
	cout << TAB_BIG << TAB_BIG << TAB << "Lista de todos os Clientes" << endl << endl;
	cout << endl;
	cout << setw(5) << "ID" << setw(25) << "NOME" << setw(17) << "DATA" << setw(10) << "VALOR" << endl;

	for (map <string, unsigned int>::const_iterator it = clientIdx.begin() ; it != clientIdx.end(); it++){
		cout << allclients.at(it->second) << endl;
	}
	cout << endl;

	system("PAUSE");
	return;
}

void Supermarket::change_client_name(){
	int idtofind;
	map<unsigned int, unsigned int>::iterator it;
	string newname;
	cout << "Insira o seu ID de client: ";
	idtofind = leInteiro(0);
	it = idtoclient.find(idtofind);
	
	if (it == idtoclient.end()){
		cerr << endl << "Esse ID nao existe, crie um novo cliente ou verifique o seu ID!" << endl<<endl;
	}
	else {
		cout << "Insira o seu novo nome: ";
		newname = readstring();
		if (clientIdx.count(newname) > 0)
			cerr << endl << "Esse nome ja existe, aconselhamos a manter o seu nome!" << endl << endl;
		else {
			int tmp;
			tmp = it->second;
			allclients.at(tmp).setname(newname);
			//refresh map, name->positioninvector
			clientIdx.clear();
			for (unsigned int i = 0; i < allclients.size(); i++)
				clientIdx.insert(pair <string, unsigned int>(allclients.at(i).getName(), i));
			modified_clients = true;
			cout<< endl << "Nome de cliente alterado com sucesso!" << endl << endl;
		}
	}

	system("PAUSE");
	return;
}

void Supermarket::creat_new_client(){
	string newname;
	
	cout << "Insira o seu nome (max: 25 caracteres): ";
	newname = readstring();

	if (clientIdx.count(newname) == 0)
	{
		maxClientsId++;
		allclients.push_back(Client(maxClientsId, newname));
		idtoclient.insert(pair <unsigned int, unsigned int>(maxClientsId, allclients.size() - 1));
		clientIdx.insert(pair <string, unsigned int>(newname, allclients.size() - 1));
		cout << endl << "Cliente criado com sucesso!!" << endl;
		cout << "O seu ID: " << maxClientsId  << endl << "O seu nome: " << newname << endl << endl;
		modified_clients = true;
	}
	else
		cerr <<endl<< "Esse nome ja existe! \nNao foi possivel criar novo cliente!" << endl<<endl;
	system("PAUSE");
	return;
}

void Supermarket::remove_client(){
	int idtofind;
	map<unsigned int, unsigned int>::iterator it;

	cout << "Qual e o ID do cliente que pretende remover: ";
	idtofind = leInteiro(0);
	it = idtoclient.find(idtofind);
	if (idtoclient.count(idtofind) == 0)
		cerr <<endl << "Esse ID nao existe!" << endl << "Nao foi possivel remover cliente!" << endl<< endl;
	else {
		int tmp = it->second;
		allclients.erase(allclients.begin() + tmp);
		cout <<endl << "Cliente removido com sucesso!" << endl << endl;
		modified_clients = true;
		
		//atualizar maps fazer função
		clientIdx.clear();
		idtoclient.clear();
		for (unsigned int i = 0; i < allclients.size(); i++){
			clientIdx.insert(pair <string, unsigned int>(allclients.at(i).getName(), i));
			idtoclient.insert(pair <unsigned int, unsigned int>(allclients.at(i).getId(), i));
		}
	}

	system("PAUSE");
	return;
}

//gestão de transacoes
void Supermarket::aux_l_t_b_d(Date date1, Date date2) const{
	system("cls");
	cout << TAB_BIG << TAB_BIG << "Tansacoes efetuadas entre " << date1 << " e " << date2 << endl;
	cout << endl;
	cout << setw(5) << "ID" << setw(13) << "DATA" << "  " << "Produtos" << endl;
	for (size_t i = 0; i < alltransactions.size(); i++)
	{
		if (date1 < alltransactions.at(i).getData() && alltransactions.at(i).getData() < date2)
			cout << alltransactions.at(i) << endl;
	}
	cout << endl;
	system("PAUSE");
	return;
}
void Supermarket::list_transactions_beetween_dates(Supermarket supermercado) const{
	string sdate1, sdate2;
	Date date1, date2;
	cout << "Insira uma data (dd/mm/yyyy):";
	cin >> sdate1;
	cout << "Insira outra data (dd/mm/yyyy):";
	cin >> sdate2;
	date1 = Date(sdate1);
	date2 = Date(sdate2);

	if (!(date1.getis_valid()||date2.getis_valid())){
		cerr << "Inseriu pelo menos uma data invalida!!" << endl << endl;
		system("PAUSE");
		return;
	}

	if (date1 < date2)
		supermercado.aux_l_t_b_d(date1, date2);
	else
		supermercado.aux_l_t_b_d(date2, date1);
	return;
}

void Supermarket::list_client_transactions() const{
	int idofname;
	set <Transaction> transofaclient;
	string nametofind;
	map <string, unsigned int>::const_iterator it;
	cout << "Insira o nome do cliente que quer procurar: ";
	nametofind = readstring();
	it = clientIdx.find(nametofind);
	system("cls");
	cout << TAB_BIG << TAB_BIG << TAB_BIG << "Transacoes de " << nametofind << endl;
	if (it == clientIdx.end()){
		cerr<< endl << "Nao existe nenhum cliente com esse nome! \nVerifique o seu nome de cliente, ou crie novo cliente!" << endl << endl;
		system("PAUSE");
		return;
	}

	idofname = allclients.at(it->second).getId();
	
	if (transactionIdx.count(idofname)==0){
		cerr << endl << "Verificamos que nao efetuou nenhuma transacao...\nSendo entao impossivel usar esta opcao...\nUse a nossa loja e efetue algumas compras!" << endl << endl;
		system("PAUSE");
		return;
	}
	
	for (multimap<unsigned int, unsigned int>::const_iterator itr = transactionIdx.find(idofname); itr != transactionIdx.end() && itr->first == idofname; itr++){
		transofaclient.insert(alltransactions.at(itr->second));
	}

	cout << endl;
	cout << setw(5) << "ID" << setw(13) << "DATA" << "  " << "Produtos" << endl;

	for (Transaction const& trans : transofaclient)
	{
		cout << trans << endl;
	}
	cout << endl;
	system("PAUSE");
	return;
}

void Supermarket::make_transaction() {
	unsigned short int optionproducttobuy;
	vector <string> productsbought;
	vector< Product > tmp = allproducts;
	unsigned int i = 1, idthatbuys;
	float cost = 0;
	bool stop_buying = false;
	sort(tmp.begin(), tmp.end());
	
	
	//menu com produtos e respectivo preço
	system("cls");
	cout << TAB_BIG << "Bem vindo ao " << store << endl;
	cout <<TAB <<"O que gostaria de comprar: " << endl << endl;
	
	cout << TAB << "     " << setw(19) << left << "Product" << setw(5) << right << "Price" << endl;
	for (i; i<= tmp.size(); i++){
		cout << TAB <<setw(2)<< i << " - " << tmp.at(i-1) << endl;
	}
	cout << TAB << i << " - " << "Nao quero comprar mais nada!" << endl << endl;
	
	
	//vetor com todos os produtos que o cliente quer comprar
	while (!stop_buying)
	{
		cout << "Escolha uma opcao: ";
		while (!menu_input_error(optionproducttobuy, i)){
			cout << "Escolha uma opcao: ";
		}
		if (optionproducttobuy == i)
			stop_buying = true;
		else{
			productsbought.push_back(tmp.at(optionproducttobuy-1).getName());
			cost += tmp.at(optionproducttobuy - 1).getPrice();
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	
	if (productsbought.size() == 0)
		return;

	cout << "Insira o seu ID de cliente: ";
	idthatbuys = leInteiro(0);
	if (idtoclient.count(idthatbuys) == 0){
		cerr << endl << "Nao conseguimos encontrar o seu id na nossa base de dados\nVerifique o seu ID ou crie novo cliente!" << endl << endl;
		system("PAUSE");
		return;
	}
	//refresh transactions
	Transaction tmade(idthatbuys,productsbought);
	alltransactions.push_back(tmade);
	modified_Transactions = true;
	transactionIdx.insert(make_pair(idthatbuys,alltransactions.size()-1));

	//refresh clients
	map < unsigned int, unsigned int>::iterator itr = idtoclient.find(idthatbuys);
	allclients.at(itr->second).setvolPurchased(cost);
	modified_clients = true;
	
	cout << endl <<  "Transacao efetuda com sucesso!!" << endl << endl;
	system("PAUSE");
	return;
}
//informacoes

void Supermarket::list_client_info() const{
	map <unsigned int, unsigned int>::const_iterator it;
	unsigned int idtofind;
	cout << "Insira o seu ID: ";
	idtofind = leInteiro(0);
	system("cls");
	it = idtoclient.find(idtofind);
	if (it == idtoclient.end()){
		cerr << endl << "Nao existe nenhum cliente com esse ID! \nVerifique o seu ID de cliente, ou crie novo cliente!" << endl << endl;
		system("PAUSE");
		return;
	}

	cout << endl;
	cout << setw(5) << "ID" << setw(25) << "NOME" << setw(17) << "DATA" << setw(10) << "VALOR" << endl;

	cout << allclients.at(it->second) << endl;
	cout << endl;
	system("PAUSE");
	return;
}

void Supermarket::list_all_transactions() const{
	multiset <Transaction> sortedalltran;
	for (size_t i = 0; i < alltransactions.size(); i++)
		sortedalltran.insert(alltransactions.at(i));
	system("cls");
	cout << TAB_BIG << TAB_BIG << TAB << "Todas as transacoes efetuadas em "<< store << endl << endl;
	cout << setw(5) << "ID" << setw(13) << "DATA" << "  " << "Produtos" << endl;

	for (Transaction const& trans : sortedalltran)
	{
		cout << trans << endl;
	}
	cout << endl;
	system("PAUSE");
	return;
}

void Supermarket::list_all_products() const {
	system("cls");
	cout << TAB_BIG << TAB_BIG << TAB << "Produtos disponiveis em " << store << endl;
	cout << endl << TAB << setw(19) << left << "Product" << setw(5) << right << "Price" << endl << endl;
	for (size_t i = 0; i < allproducts.size(); i++)
		cout << TAB << allproducts.at(i) << endl;
	cout << endl;
	system("PAUSE");
	return;
}

void Supermarket::list_day_transactions() const{
	string sdate1;
	bool validdate;
	Date date1;
	cout << "Insira uma data (dd/mm/yyyy): ";
	cin >> sdate1;
	date1 = Date(sdate1);

	validdate = date1.getis_valid();
	if (!validdate){
		cerr << "Inseriu uma data invalida!!" << endl<<endl;
		system("PAUSE");
		return;
	}

	system("cls");
	cout << TAB_BIG << TAB_BIG << TAB << "Transacoes efetuadas no dia " << sdate1 << endl << endl;
	cout << setw(5) << "ID" << setw(13) << "DATA" << "  " << "Produtos" << endl;

	for (size_t i = 0; i < alltransactions.size(); i++){
		if (alltransactions.at(i).getData().getTotaldays() == date1.getTotaldays())
			cout << alltransactions.at(i) << endl;
	}
	cout << endl;
	system("PAUSE");
	return;
}

//recommendations
void Supermarket::recommendations() const {
	unsigned int idline, targetid, counter = 0, maxequal = 0;
	bool bought_different = false;
	string productrecommended;
	vector< vector <bool> > matrix(allclients.size(), vector<bool>(allproducts.size(), false));
	vector <bool> clienttransactions;
	vector <unsigned int> clients_that_bought_equal;
	vector <string> progrecommends;
	map< unsigned int, unsigned int>::const_iterator lineitr;
	
	//serve construir a matriz de booleanos
	for (size_t i = 0; i < alltransactions.size(); i++){
		idline = alltransactions.at(i).getIdClient();

		lineitr = idtoclient.find(idline);//procura id
		
		if (lineitr == idtoclient.end())
			continue; //cliente pode ter sido removido
		
		vector <string > tmp = alltransactions.at(i).getProductsbought();
		for (size_t j = 0; j < tmp.size(); j++) //procura produtos comprados na transacao e mete a true no respectivo lugar (linha = cliente que comprou, coluna = produtos) 
		{
			map< string, unsigned int>::const_iterator columnitr;
			columnitr = productIdx.find(tmp.at(j));
			matrix.at(lineitr->second).at(columnitr->second) = true;
		}
	}
	//
	system("cls");
	cout << TAB_BIG << "Bem-vindo ao nosso programa de recomendacao personalizada!" << endl << endl;
	
	cout << "Insira o seu ID: ";
	targetid = leInteiro(0);

	lineitr = idtoclient.find(targetid);
	//se o cliente nao existir
	if (lineitr == idtoclient.end()){
			cerr << endl << "Nao conseguimos encontrar o seu id na nossa base de dados...\nVerifique o seu ID ou crie novo cliente!" << endl << endl;
			system("PAUSE");
			return;
	}
	//se o cliente nao fez nenhuma transacao
	if (transactionIdx.count(targetid) == 0){
		cerr << endl << "Verificamos que nao efetuou nenhuma transacao...\nSendo entao impossivel usar esta opcao\nUse a nossa loja e efetue algumas compras!" << endl << endl;
		system("PAUSE");
		return;
	}

	clienttransactions = matrix.at(lineitr->second);//transacoes do cliente alvo
	
	//	obtem um vetor com os clientes que compraram o maior quantidade de produtos igual ao que o cliente alvo comprou
	for (size_t i = 0; i < matrix.size(); i++){
		if (i != lineitr->second){
			for (size_t ii = 0; ii < matrix.at(i).size(); ii++){
				if (matrix.at(i).at(ii) && clienttransactions.at(ii))
					counter++;
				else if (matrix.at(i).at(ii))
					bought_different = true;
			}
			if (counter == maxequal && bought_different)
				clients_that_bought_equal.push_back(i);
			else if (counter > maxequal && bought_different){
				maxequal = counter;
				clients_that_bought_equal.clear();
				clients_that_bought_equal.push_back(i);
			}
			bought_different = false;
			counter = 0;
		}
	}
	// produtos comprados pelos clientes selecionados e nao pelo cliente alvo
	for (size_t i = 0; i < clients_that_bought_equal.size(); i++){
		for (size_t ii = 0; ii < matrix.at(clients_that_bought_equal.at(i)).size(); ii++){
			if (matrix.at(clients_that_bought_equal.at(i)).at(ii) && !clienttransactions.at(ii)){
				progrecommends.push_back(allproducts.at(ii).getName());
			}
		}
	}

	counter = 0;
	maxequal = 0;
	if (progrecommends.size() == 0){
		cout << "O cliente que inseriu e um dos nossos melhores clientes!\nSendo entao complicado recomendar-lhe um produto que ainda nao tenha comprado\nDesejamos-lhe continuacao de boas compras, e obrigado!" << endl << endl;
		system("PAUSE");
		return;
	}

	productrecommended = progrecommends.at(0); //em caso de apenas haver produtos não repetidos devolvemos o 1º do vetor
	for (size_t i = 0; i < progrecommends.size(); i++){
		for (size_t ii = 0; ii < progrecommends.size(); ii++){
			if (ii != i){
				if (progrecommends.at(i) == progrecommends.at(ii))
					counter++;
			}
		}
		if (counter > maxequal){
			productrecommended = progrecommends.at(i);
			maxequal = counter;
		}
		counter = 0;
	}

	cout << "O nosso software recomenda-lhe comprar: " << productrecommended << endl;
	cout << "Desejamos-lhe boas compras!" << endl << endl;
	
	system("PAUSE");
	return;
}

bool compare_commonbottom10_client(const vector < bool > commonproducts, const vector < bool > boolclient){
	unsigned int i;
	bool bought_different = false;
	for (i = 0; i < commonproducts.size(); i++){
		if (commonproducts.at(i) && !boolclient.at(i))
			break;
		else if (!commonproducts.at(i) && boolclient.at(i))
			bought_different = true;
	}
	return ((i == commonproducts.size()) && bought_different);
}

void Supermarket::bottom10() const {
	//cria vetor com os 10 piores clientes e um map id->posicao no vetor e resto dos clientes
	vector< Client > bottom10 = allclients;
	vector <Client> restofclients;

	sort(bottom10.begin(), bottom10.end());
	restofclients = bottom10;
	bottom10.erase(bottom10.begin()+10, bottom10.end());
	restofclients.erase(restofclients.begin(), restofclients.begin() + 10);
	
	map <unsigned int, unsigned int> idbottom10;
	for (unsigned int i = 0; i < bottom10.size(); i++){
		idbottom10.insert(pair <unsigned int, unsigned int>(bottom10.at(i).getId(), i));
	}
	map <unsigned int, unsigned> idrestofclients;
	for (unsigned int i = 0; i < restofclients.size(); i++){
		idrestofclients.insert(pair <unsigned int, unsigned int>(restofclients.at(i).getId(), i));
	}
	
	//cria uma matriz com as compras dos 10 piores clientes
	vector< vector <bool> > matrixb10(10, vector<bool>(allproducts.size(), false));
	int idlineb10;
	map< unsigned int, unsigned int>::const_iterator lineitrb10;
	for (size_t i = 0; i < alltransactions.size(); i++){
		idlineb10 = alltransactions.at(i).getIdClient();

		lineitrb10 = idbottom10.find(idlineb10);//procura id

		if (lineitrb10 != idbottom10.end()){ //cliente nao pertence aos bottom10 ou foi removido
		vector <string > tmp = alltransactions.at(i).getProductsbought();
		for (size_t j = 0; j < tmp.size(); j++) //procura produtos comprados na transacao e mete a true no respectivo lugar (linha = cliente que comprou, coluna = produtos) 
		{
			map< string, unsigned int>::const_iterator columnitr;
			columnitr = productIdx.find(tmp.at(j));
			matrixb10.at(lineitrb10->second).at(columnitr->second) = true;
		}
		}
	}
	//cria um vetor de bool (true os produtos comuns)
	vector < bool > commonproducts;
	size_t counter=0;
	
	for (size_t i = 0; i < allproducts.size(); i++){
		for (counter; counter < 10; counter++){
			if (!matrixb10.at(counter).at(i)){
				commonproducts.push_back(false);
				break;
			}
		}
		if (matrixb10.at(9).at(i) && counter == 10)
			commonproducts.push_back(true);
		counter = 0;
	}

	//cria matriz com as compraz dos clientes nao pertencentes aos bottom 10
	//idlineb10 e lineitrb10 declarados anteriormente podemos reutilizar
	vector < vector <bool> > matrixrestofclients(restofclients.size(), vector <bool> (allproducts.size(), false));

	for (size_t i = 0; i<alltransactions.size(); i++){
		idlineb10 = alltransactions.at(i).getIdClient();
		lineitrb10 = idrestofclients.find(idlineb10);

		if (lineitrb10 != idrestofclients.end()){
			vector < string > tmp = alltransactions.at(i).getProductsbought();
			for (size_t j = 0; j < tmp.size(); j++){
				map < string, unsigned int>::const_iterator columnitr;
				columnitr = productIdx.find(tmp.at(j));
				matrixrestofclients.at(lineitrb10->second).at(columnitr->second) = true;
			}
		}
	}

	//cria matriz com os clientes interessantes
	vector < vector <bool> > matrixinterestingclients;
	map <unsigned int, unsigned int> maptointerestingclients;
	for (size_t i = 0; i < matrixrestofclients.size(); i++){
		if (compare_commonbottom10_client(commonproducts, matrixrestofclients.at(i))){
			matrixinterestingclients.push_back(matrixrestofclients.at(i));
			maptointerestingclients.insert(make_pair(restofclients.at(i).getId(), matrixinterestingclients.size() - 1));
		}
	}

	//cria histograma com produto/compras por clientes interessantes
	vector < int > histogram (allproducts.size(),0);

	for (size_t i = 0; i < allproducts.size(); i++){
		if (commonproducts.at(i))
			continue;
		for (size_t j = 0; j < matrixinterestingclients.size(); j++){
			if (matrixinterestingclients.at(j).at(i))
				histogram.at(i) += 1;
		}	
	}

	//descobre elemento para promoçao
	int positionofmax;
	string producttopromote;
	vector < int >::const_iterator histogramitr = max_element(histogram.begin(), histogram.end());
	positionofmax = histogramitr - histogram.begin();
	producttopromote = allproducts.at(positionofmax).getName();
	system("cls");
	cout << TAB_BIG << TAB_BIG << TAB_BIG << "Campanha Bottom10" << endl;
	cout << endl;
	cout << "O nosso software aconselha-o a criar uma campanha de promocao para o produto: " << endl << producttopromote << endl << endl;
	system("PAUSE");
	return;
}

//save and operator <<
void Supermarket::save() const{
	if (modified_clients){
		ofstream clientssave;
		clientssave.open(clientsFile);
		clientssave << allclients.size() << endl;
		for (size_t i = 0; i < allclients.size(); i++)
			allclients.at(i).save(clientssave);
		clientssave.flush();
		clientssave.close();
	}
	if (modified_Transactions){
		ofstream transactionsssave;
		transactionsssave.open(transactionsFile);
		transactionsssave << alltransactions.size() << endl;
		for (size_t i = 0; i < alltransactions.size(); i++)
			alltransactions.at(i).save(transactionsssave);
		transactionsssave.flush();
		transactionsssave.close();
	}
	return;
}

ostream& operator<<(ostream& out, const Supermarket & super){
	cout << TAB << "Numero de clientes: " << super.allclients.size() << endl;
	cout << TAB << "Numero de produtos disponiveis para venda: " << super.allproducts.size() << endl;
	cout << TAB << "Numero de transacoes efetudas ate ao momento: " << super.alltransactions.size() << endl << endl;
	system("PAUSE");
	return out;
}


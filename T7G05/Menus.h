#pragma once

#include <iostream>
#include <fstream>
#include <string>


#include "defs.h"
#include "Functions.h"
#include "Supermarket.h"

using namespace std;

void Client_management_menu(Supermarket &supermercado);
void Transactions_management_menu(Supermarket &supermercado);
void Information_menu(Supermarket &supermercado);
void Recommendations_menu(Supermarket &supermercado);
void Home_menu(Supermarket &supermercado);

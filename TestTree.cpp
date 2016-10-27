#include "stdafx.h"
#include <iostream>
#include <list>
#include <stack>
#include <random>
#include <ctime>

using namespace std;

struct node {
	char mov[9] = { "-" };
	node *padre = nullptr;
	node *hijo[9] = {nullptr};
	int costo;
};

node *auxiliar = new node;
list <node*> cola;
stack <node*> pila;

int vacios(node* aux);
void llenarArbol(node* root);
void printgato(node* aux);
void busqueda_amplitud(char jugada[9]);
void busqueda_profundidad(char jugada[9]);
void busqueda_profundidad_it(char jugada[9], int lvl);
void busqueda_costo(char jugada[9]);
int costo(node* aux, int posicion, char simbolo);


int main()
{
	srand(time(NULL));
	int opcion, nivel;
	char cArray[9];
	
	for (int x = 0; x < 9; x++)
	{
		auxiliar->mov[x] = '-'; //inicializacion de las combinaciones en vacio
	}

	llenarArbol(auxiliar);

	while (1) {
		system("cls");
		cout << "Seleccione una de las opciones: " << endl;
		/*cout << "0. Hijo 1" << endl;
		cout << "1. Hijo 2" << endl;
		cout << "2. Hijo 3" << endl;
		cout << "3. Hijo 4" << endl;
		cout << "4. Hijo 5" << endl;
		cout << "5. Hijo 6" << endl;
		cout << "6. Hijo 7" << endl;
		cout << "7. Hijo 8" << endl;
		cout << "8. Hijo 9" << endl;
		cout << "9. Padre" << endl;*/
		cout << "1. Busqueda por amplitud" << endl;
		cout << "2. Busqueda por profundidad" << endl;
		cout << "3. Busqueda por profundidad Iterativa" << endl;
		cout << "4. Busqueda por Costo uniforme" << endl;

		cout << "Seleccione: ";
		cin >> opcion;

		switch (opcion)
		{
		/*case 0:
			printgato(auxiliar->hijo[opcion]);
			cout << endl;
			system("pause");
			break;
		case 1:
			printgato(auxiliar->hijo[opcion]);
			cout << endl;
			system("pause");
			break;
		case 2:
			printgato(auxiliar->hijo[opcion]);
			cout << endl;
			system("pause");
			break;
		case 3:
			printgato(auxiliar->hijo[opcion]);
			cout << endl;
			system("pause");
			break;
		case 4:
			printgato(auxiliar->hijo[opcion]);
			cout << endl;
			system("pause");
			break;
		case 5:
			printgato(auxiliar->hijo[opcion]);
			cout << endl;
			system("pause");
			break;
		case 6:
			printgato(auxiliar->hijo[opcion]);
			cout << endl;
			system("pause");
			break;
		case 7:
			printgato(auxiliar->hijo[opcion]);
			cout << endl;
			system("pause");
			break;
		case 8:
			printgato(auxiliar->hijo[opcion]);
			cout << endl;
			system("pause");
			break;
		case 9:
			printgato(auxiliar->padre);
			auxiliar = auxiliar->padre;
			cout << endl;
			system("pause");
			break;*/
		case 1:
			cout << "Introduce la jugada a buscar: ";
			cin >> cArray;
			cola.push_back(auxiliar);
			busqueda_amplitud(cArray);
			break;
		case 2:
			cout << "Introduce la jugada a buscar: ";
			cin >> cArray;
			pila.push(auxiliar);
			busqueda_profundidad(cArray);
			break;
		case 3:
			cout << "Introduce la jugada a buscar: ";
			cin >> cArray;
			cout << "Introduce el nivel: ";
			cin >> nivel; 
			pila.push(auxiliar);
			busqueda_profundidad_it(cArray, nivel);
			break;
		case 4:
			cout << "Introduce la jugada a buscar: ";
			cin >> cArray;
			auxiliar->costo = 0;
			cola.push_back(auxiliar);
			busqueda_costo(cArray);
		default:
			break;
		}
	}
		return 0;
	}


void llenarArbol(node* root) {
		for (int i = 0; i < vacios(root); i++) { //numero de hijos vacios
			int auxiliar = vacios(root);
			node *aux = new node;
			int contador = 0, wins=0;
			char simbolo, simbaux;

			if (auxiliar % 2 == 0) {
				simbolo = 'O';
			}
			else {
				simbolo = 'X';
			}

			for (int x = 0; x < 9; x++) // llena la matriz
			{
				if (contador == i && root->mov[x] == '-') { // mueve la X de posicion 
					aux->mov[x] = simbolo;
					simbaux = x;
				}

				else {
					aux->mov[x] = root->mov[x];
				}

				if (root->mov[x] == '-') {
					contador++;
				}
			}
		
			aux->costo = costo(aux, simbaux, simbolo);
		
			aux->padre = root;
			root->hijo[i] = aux;

			llenarArbol(aux); // recursividad para llenar el arbol
		}
	}

int vacios(node* aux2) { // funcion para revisar los espacios vacios en los punteros
	int cont = 0;
	for (int x = 0; x < 9; x++) {
		if (aux2->mov[x] == '-')
			cont++;
	}
	return cont;
	}

void printgato(node* aux) {

	for (int x = 0; x < 9; x++) {
		cout << aux->mov[x];
			if (x == 2 || x == 5) {
				cout << endl;
			}
	}
		cout << "\nCosto: " << aux->costo<< endl << endl;
	
}

void busqueda_amplitud(char jugada[9]) {
	node *buscado = new node;
	buscado = cola.front();
	cola.pop_front();

	int nodoContador = 0;

	printgato(buscado);
	cout << endl << endl;

	for (int x = 0; x < 9; x++) {

		if (buscado->mov[x] == jugada[x]) {
			nodoContador++;
		}
	}

	if (nodoContador == 9) {
		cout << "Nodo encontrado" << endl;
		system("pause");
		return;
	}
	else
	{
		for (int x = 0; x < 9; x++) {
			if (buscado->hijo[x] != NULL) {
				cola.push_back(buscado->hijo[x]);
			}
		}
			busqueda_amplitud(jugada);


	}
}

void busqueda_profundidad(char jugada[9])
{
	node *buscado = new node;
	int nodoContador = 0;
	buscado = pila.top();
	pila.pop();

	printgato(buscado);
	cout << endl << endl;

	for (int x = 0; x < 9; x++) {

		if (buscado->mov[x] == jugada[x]) {
			nodoContador++;
		}
	}

	if (nodoContador == 9) {
		cout << "Nodo encontrado" << endl;
		system("pause");
		pila.empty();
		return;
	}
	else
	{
		for (int x = 8; x >= 0; x--) {
			if (buscado->hijo[x] != NULL) {
				pila.push(buscado->hijo[x]);
			}
		}
	}
	
	busqueda_profundidad(jugada);

	
	
}

void busqueda_profundidad_it(char jugada[9], int lvl)
{
	node* buscado = new node;
	int nodoContador = 0;
	int vaciosContador = 0;
	bool des;

	if (pila.empty()) {   // Aumenta el nivel de la busqueda
		cout << "No se encontro el nodo buscado" << endl;
		cout << "Quieres aumentar el nivel de busqueda +1?";
		cin >> des;
		if (des) {
			pila.push(auxiliar);
			busqueda_profundidad_it(jugada, (lvl + 1));
		}
	}

	buscado = pila.top();
	pila.pop();

	printgato(buscado);
	cout << endl << endl;

	for (int x = 0; x < 9; x++) {

		if (buscado->mov[x] == jugada[x]) {
			nodoContador++;
		}
	}

	for (int x = 0; x < 9; x++) {
		if (buscado->hijo[x] == NULL) {
			vaciosContador++;
		}
	}

	if (nodoContador == 9) {
		cout << "Nodo encontrado" << endl;
		system("pause");
		main();
	}
	else if (vaciosContador == lvl) {
		busqueda_profundidad_it(jugada, lvl);
	}
	else
	{
		for (int x = 8; x >= 0; x--) {
			if (buscado->hijo[x] != NULL) {
				pila.push(buscado->hijo[x]);
			}
		}
	}
	
	busqueda_profundidad_it(jugada,lvl);

}

void busqueda_costo(char jugada[9])
{
	node *buscado = new node;

	cola.sort([](const node * a, const node * b) 
				{ return a->costo > b->costo; });

	buscado = cola.front();
	cola.pop_front();

	int nodoContador = 0;

	printgato(buscado);

	for (int x = 0; x < 9; x++) {

		if (buscado->mov[x] == jugada[x]) {
			nodoContador++;
		}
	}

	if (nodoContador == 9) {
		cout << "Nodo encontrado" << endl;
		printgato(buscado);
		
		while (buscado->padre != nullptr) {
			printgato(buscado->padre);
			buscado = buscado->padre;
		}

		system("pause");
		return;
	}
	else
	{
		for (int x = 0; x < 9; x++) {
			if (buscado->hijo[x] != NULL) {
				cola.push_back(buscado->hijo[x]);
				//buscado->hijo[x]->costo += buscado->costo;
			}
		}
		busqueda_costo(jugada);
	}
}

int costo(node * aux,int posicion, char simbolo)
{
	int total = 0;
	switch (posicion) {
	case 0:
		if ((aux->mov[1] == simbolo || aux->mov[1] == '-') && (aux->mov[2] == simbolo || aux->mov[2] == '-')) { total++; }
		if ((aux->mov[3] == simbolo || aux->mov[3] == '-') && (aux->mov[6] == simbolo || aux->mov[6] == '-')) { total++; }
		if ((aux->mov[4] == simbolo || aux->mov[4] == '-') && (aux->mov[8] == simbolo || aux->mov[8] == '-')) { total++; }
		break;
	case 1:
		if ((aux->mov[0] == simbolo || aux->mov[0] == '-') && (aux->mov[2] == simbolo || aux->mov[2] == '-')) { total++; }
		if ((aux->mov[4] == simbolo || aux->mov[4] == '-') && (aux->mov[7] == simbolo || aux->mov[7] == '-')) { total++; }
		break;
	case 2:
		if ((aux->mov[0] == simbolo || aux->mov[0] == '-') && (aux->mov[1] == simbolo || aux->mov[1] == '-')) { total++; }
		if ((aux->mov[5] == simbolo || aux->mov[5] == '-') && (aux->mov[8] == simbolo || aux->mov[8] == '-')) { total++; }
		if ((aux->mov[4] == simbolo || aux->mov[4] == '-') && (aux->mov[6] == simbolo || aux->mov[6] == '-')) { total++; }
		break;
	case 3:
		if ((aux->mov[0] == simbolo || aux->mov[0] == '-') && (aux->mov[8] == simbolo || aux->mov[8] == '-')) { total++; }
		if ((aux->mov[4] == simbolo || aux->mov[4] == '-') && (aux->mov[5] == simbolo || aux->mov[5] == '-')) { total++; }
		break;
	case 4:
		if ((aux->mov[0] == simbolo || aux->mov[0] == '-') && (aux->mov[8] == simbolo || aux->mov[8] == '-')) { total++; }
		if ((aux->mov[1] == simbolo || aux->mov[1] == '-') && (aux->mov[7] == simbolo || aux->mov[7] == '-')) { total++; }
		if ((aux->mov[2] == simbolo || aux->mov[2] == '-') && (aux->mov[6] == simbolo || aux->mov[6] == '-')) { total++; }
		if ((aux->mov[3] == simbolo || aux->mov[3] == '-') && (aux->mov[5] == simbolo || aux->mov[5] == '-')) { total++; }
		break;
	case 5:
		if ((aux->mov[2] == simbolo || aux->mov[2] == '-') && (aux->mov[8] == simbolo || aux->mov[8] == '-')) { total++; }
		if ((aux->mov[4] == simbolo || aux->mov[4] == '-') && (aux->mov[3] == simbolo || aux->mov[3] == '-')) { total++; }
		break;
	case 6:
		if ((aux->mov[0] == simbolo || aux->mov[0] == '-') && (aux->mov[3] == simbolo || aux->mov[3] == '-')) { total++; }
		if ((aux->mov[7] == simbolo || aux->mov[7] == '-') && (aux->mov[8] == simbolo || aux->mov[8] == '-')) { total++; }
		if ((aux->mov[4] == simbolo || aux->mov[4] == '-') && (aux->mov[2] == simbolo || aux->mov[2] == '-')) { total++; }
		break;
	case 7:
		if ((aux->mov[6] == simbolo || aux->mov[6] == '-') && (aux->mov[8] == simbolo || aux->mov[8] == '-')) { total++; }
		if ((aux->mov[4] == simbolo || aux->mov[4] == '-') && (aux->mov[1] == simbolo || aux->mov[1] == '-')) { total++; }
		break;
	case 8:
		if ((aux->mov[5] == simbolo || aux->mov[5] == '-') && (aux->mov[2] == simbolo || aux->mov[2] == '-')) { total++; }
		if ((aux->mov[7] == simbolo || aux->mov[7] == '-') && (aux->mov[6] == simbolo || aux->mov[6] == '-')) { total++; }
		if ((aux->mov[4] == simbolo || aux->mov[4] == '-') && (aux->mov[0] == simbolo || aux->mov[0] == '-')) { total++; }
		break;
	}
	return total;
}

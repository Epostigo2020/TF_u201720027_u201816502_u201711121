#pragma once
#include "Arbol.h"

class Columna
{
	string nombre;
	vector<string*>* listaC;
	
public:
	Columna(string nombre) {
		this->nombre = nombre;
		listaC = new vector<string*>();
	}
	void agregar(string* texto) {
		listaC->push_back(texto);
	}
	string atValor(int indice) {
		return *listaC->at(indice);
	}
	string* at(int indice) {
		return listaC->at(indice);
	}
	void Clear() {
		listaC->clear();
	}
	string get_nombre() { return nombre; }
	int size() {
		return listaC->size();
	}
};


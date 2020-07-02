#pragma once
#include "Columna.h"

class Fila
{
	vector<string*>* vec;
	
public:
	Fila() {
		vec = new vector<string*>();
	}
	~Fila() {
		vec->clear();
	}
	void agregar(string* texto) {
		vec->push_back(texto);
	}
	string atValor(int indice) {
		return *vec->at(indice);
	}
	string* at(int indice) {
		return vec->at(indice);
	}
	void Clear() {
		vec->clear();
	}
	int size() {
		return vec->size();
	}
};






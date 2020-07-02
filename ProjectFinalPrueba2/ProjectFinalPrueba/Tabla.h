#pragma once
#include "Fila.h"
vector<string*>* nombresC(string palabra) {
	string nom = "";
	vector<string*>* vec = new vector<string*>();
	for (int i = 0; i < palabra.size(); i++) {
		if (palabra.at(i) != ',') {
			nom += palabra.at(i);
		}
		else {
			string* nuevo = new string;
			*nuevo = nom;
			vec->push_back(nuevo);
			nom = "";
		}
	}
	string* nuevo = new string;
	*nuevo = nom;
	vec->push_back(nuevo);
	nom = "";
	return vec;
}

class Tabla
{
	string nombreT;
	vector<Fila*>* vecF;
	vector<Columna*>* vecC;
	ifstream leer;
	ofstream escribir;
	bool nombresColum;
public:
	Tabla(string nombre) {
		nombresColum = false;
		this->nombreT = nombre;
		vecC = new vector<Columna*>();
		vecF = new vector<Fila*>();
	}
	~Tabla() {
		Clear();
	}
	void agregarNombresColumna(vector<string*>* nomC) {
		
		for (int i = 0; i < nomC->size(); i++) {
			string nom = *(nomC->at(i));
			Columna* nuevo = new Columna(nom);

			vecC->push_back(nuevo);
		}
		nombresColum = true;
	}
	
	void agregarF(vector<string*>* vector) {
		if (nombresColum == true) {
			Fila* filita = new Fila();

			for (int i = 0; i < vector->size(); i++) {

				filita->agregar(vector->at(i));

				vecC->at(i)->agregar(vector->at(i));

			}
			vecF->push_back(filita);
		}
	}
	void mostrar() {
		if (nombresColum == true) {
			for (int i = 0; i < vecC->size(); i++) {
				cout << setw(15) << vecC->at(i)->get_nombre() << " | ";
			}
			cout << endl;
			for (int i = 0; i < 18 * vecC->size(); i++) {
				cout << "_";
			}
			cout << endl;

			for (int f = 0; f < vecF->size(); f++) {
				for (int c = 0; c < vecF->at(0)->size(); c++) {
					cout << setw(15) << vecF->at(f)->atValor(c) << " | ";
				}
				cout << endl;
			}
		}
	}
	void guardarTabla() {
		if (nombresColum == true) {
			escribir.open(nombreT, ios::out | ios::app);
			if (escribir.is_open()) {
				for (int i = 0; i < vecC->size() - 1; i++) {
					escribir << vecC->at(i)->get_nombre() << ",";
				}
				escribir << vecC->at(vecC->size() - 1)->get_nombre() << endl;

				for (int f = 0; f < vecF->size(); f++) {
					for (int c = 0; c < vecF->at(0)->size() - 1; c++) {
						escribir << vecF->at(f)->atValor(c) << ",";
					}
					escribir << vecF->at(f)->atValor(vecF->at(0)->size() - 1) << endl;
				}
				cout << "Se exporto la tabla a un archivo correctamente " << endl;
			}
		}
	}
	void mostrarColumna(string nombreColum) {
		Columna* seleccion = nullptr;
		bool encontro = false;
		for (int i = 0; i < vecC->size() && encontro == false; i++) {
			if (vecC->at(i)->get_nombre() == nombreColum) {
				seleccion = vecC->at(i);
				encontro = true;
			}
		}

		if (seleccion != nullptr && encontro == true) {
			cout << seleccion->get_nombre() << endl;
			cout << "________________" << endl;
			for (int i = 0; i < seleccion->size(); i++) {
				cout << seleccion->atValor(i) << endl;
			}
		}
		else {
			cout << "No se encontro la columna" << endl;
		}

	}
	void leerArchivo() {
		string palabra;
		
		leer.open(nombreT, ios::out | ios::in);
		if (leer.is_open()) {
			Clear();
			getline(leer, palabra);

			vector<string*>* vec = nombresC(palabra);
			agregarNombresColumna(vec);
			
			while (!leer.eof()) {
				getline(leer, palabra);
				if (palabra.size() > 0) {
					vector<string*>* vect = nombresC(palabra);

					agregarF(vect);
				}
			}
			leer.close();
			cout << "El archivo se cargo correctamente " << endl;
		}
		else {
			cout << "El archivo no existe " << endl;
		}
	}
	void insercionRegistros() {
		if (nombresColum == true) {

			escribir.open(nombreT, ios::out | ios::app);
			string txt;
			if (escribir.is_open()) {
				vector<string> vecP;
				for (int i = 0; i < sizeC(); i++) {
					cout << "Escribe " << atC(i)->get_nombre() << " : "; cin >> txt;
					vecP.push_back(txt);
				}
				system("pause");
				if (vecP.size() == sizeC()) {

					for (int i = 0; i < vecP.size() - 1; i++) {
						escribir << vecP.at(i) << ",";
					}
					escribir << vecP.at(vecP.size() - 1) << endl;
					cout << "Se inserto correctamente :D " << endl;
					escribir.close();
					
					leerArchivo();
				}
				
			}
		}
		else {
			cout << "No se ha cargado ningun archivo";
		}
	}

	void Clear() {
		vecF->clear();
		vecC->clear();
		nombresColum = false;
	}
	int size() {
		return vecF->size();
	}
	Fila* atF(int indice) {
		return vecF->at(indice);
	}
	Columna* atC(int indice) {
		return vecC->at(indice);
	}
	Columna* findC(string nombre) {
		for (int i = 0; i < vecF->size(); i++) {
			if (vecC->at(i)->get_nombre() == nombre) {
				return vecC->at(i);
			}
		}
	}
	bool esVacio() { return !nombresColum; }
	int findIC(string nombre) {
		for (int i = 0; i < vecF->size(); i++) {
			if (vecC->at(i)->get_nombre() == nombre) {
				return i;
			}
		}
		return -1;
	}

	int sizeC() {
		return vecC->size();
	}

};


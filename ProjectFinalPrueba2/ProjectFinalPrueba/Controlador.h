#pragma once
#include "Tabla.h"

class Controlador
{
	Tabla* tablita;
	vector<Tabla*>* listaT;
	ifstream leer;
	ofstream escribir;
	Arbol<Fila*, string, nullptr>* arbolito;
	vector<Fila*>* vecAux;
	int columnaIndexada;

public:
	Controlador() {
		listaT = new vector<Tabla*>();
		tablita = nullptr;
		arbolito = nullptr;
		columnaIndexada = -1;
		vecAux = nullptr;
	}
	void crearTabla(string nombreTxt) {
		tablita = new Tabla(nombreTxt);
		listaT->push_back(tablita);
	}
	void generarTabla() {
		string nomT;
		int op;
		cout << "(1) Cargar un archivo/ (2) Crear Tabla / Otro numero para salir: "; cin >> op;
		if (op == 1) {
			cout << "Escriba el nombre del archivo a cargar: "; cin >> nomT;
			Tabla* nuevo = new Tabla(nomT);
			nuevo->leerArchivo();
			if (nuevo->esVacio() == false) {
				tablita = nuevo;
				apuntarNombreTabla(nomT);
			}
			else {
				cout << "El archivo no existe" << endl;
				tablita = nullptr;
			}
		}
		if (op == 2) {
			int num;
			cout << "Ingrese el nombre de la tabla: "; cin >> nomT;

			cout << "Elija el formato que desee: (1) .txt / (Otro numero) .csv : "; cin >> num;
			if (num == 1) {
				nomT += ".txt";
			}
			else {
				nomT += ".csv";
			}
			Tabla* nuevo = new Tabla(nomT);
			cout << "Cuantas columnas desea: "; cin >> num;

			vector<string> vecCol;
			for (int i = 0; i < num; i++) {
				string nom;
				cout << "Columna #" << i + 1 << ": "; cin >> nom;
				vecCol.push_back(nom);
			}
			apuntarNombreTabla(nomT);
			string nombresito = nomT;
			escribir.open(nombresito, ios::out | ios::app);
			for (int i = 0; i < num - 1; i++) {
				escribir << vecCol.at(i) << ",";
			}
			escribir << vecCol.at(num - 1) << endl;
			escribir.close();
			cout << "Se agrego la tabla correctamente " << endl;
		}
	}
	void seleccionarTabla() {
		leer.open("Controlar.txt", ios::out | ios::in);
		vector<string> vec;
		string nombresT;
		int cont = 0;
		int op;

		if (leer.is_open()) {
			arbolito = nullptr;
			while (!leer.eof()) {
				getline(leer, nombresT);
				if (nombresT != " " && nombresT != "") {
					cout << "(" << cont << ") " << nombresT << endl;
					vec.push_back(nombresT);
					cont++;
				}
			}
		}
		leer.close();
		cout << endl;
		cout << "Elija la tabla que desee: "; cin >> op;
		nombresT = vec.at(op);
		tablita = new Tabla(nombresT);
		tablita->leerArchivo();
		cout << endl;

		if (tablita->esVacio() == true) {
			tablita = nullptr;
			cout << "No se pudo seleccionar";
		}
		else {
			tablita->mostrar();
		}
	}
	void apuntarNombreTabla(string nom) {
		escribir.open("Controlar.txt", ios::out | ios::app);
		if (escribir.is_open()) {
			escribir << nom << endl;
		}
		escribir.close();
	}

	void mostrarTabla() {
		tablita->mostrar();
	}
	void leerArchivo() {
		tablita->leerArchivo();
	}

	void insercionRegistros() {
		if (tablita != nullptr) {
			tablita->insercionRegistros();
		}
		else {
			cout << "Falta seleccionar una tabla" << endl;
		}

	}

	void indexar() {
		if (tablita != nullptr) {
			if (tablita->esVacio() == false) {
				string palabra;
				cout << "Escriba la columna que desea indexar: "; cin >> palabra;
				columnaIndexada = tablita->findIC(palabra);
				if (columnaIndexada != -1) {
					auto k1 = [](Fila* a, int i) {
						return a->atValor(i); };

					arbolito = new Arbol<Fila*, string, nullptr>(k1, columnaIndexada);
					for (int i = 0; i < tablita->size(); i++) {
						arbolito->add(tablita->atF(i));
					}

					auto print = [](Fila* a) {
						if (a == nullptr) return;

						for (int i = 0; i < a->size(); i++) {
							cout << setw(15) << a->atValor(i) << " | ";
						}
						cout << endl;
					};

					arbolito->inOrder(print);
					cout << "Se ha indexado correctamente";
				}
				else {
					cout << "No existe esa columa " << endl;
				}
			}
		}
		else {
			cout << "Falta seleccionar tabla" << endl;
		}
	}
	void indexarFiltro() {
		string palabra;
		cout << "Escriba la columna que desea aplicar el filtro: "; cin >> palabra;
		columnaIndexada = tablita->findIC(palabra);
		if (columnaIndexada != -1) {
			if (arbolito != nullptr) {
				vecAux = arbolito->retornarTodo();
				if (vecAux != nullptr) {
					auto k1 = [](Fila* a, int i) {
						return a->atValor(i); };

					arbolito = new Arbol<Fila*, string, nullptr>(k1, columnaIndexada);
					for (int i = 0; i < vecAux->size(); i++) {
						arbolito->add(vecAux->at(i));
					}
				}
				else {
					cout << "La tabla esta vacia " << endl;
				}
			}
			else {
				auto k1 = [](Fila* a, int i) {
					return a->atValor(i); };

				arbolito = new Arbol<Fila*, string, nullptr>(k1, columnaIndexada);
				for (int i = 0; i < tablita->size(); i++) {
					arbolito->add(tablita->atF(i));
				}
			}
		}
		else {
			cout << "No existe esa columa " << endl;
		}
	}
 
	void seleccionDatosColuma() {
		if (tablita != nullptr) {
			string nom;

			cout << "Escriba el nombre de la columna que desea visualizar: "; cin >> nom;
			tablita->mostrarColumna(nom);
		}
		else {
			cout << "No se ha seleccionado una tabla" << endl;
		}
		
	}

	void filtradoDatos() {
		if (arbolito != nullptr) {
			int op;
			cout << "(1) Mayor que" << endl;
			cout << "(2) Menor que" << endl;
			cout << "(3) Igual a " << endl;
			cout << "(4) Inicia con " << endl;
			cout << "(5) Finaliza con " << endl;
			cout << "(6) Esta contenido en " << endl;
			cout << "(7) No esta contenido en " << endl;
			cout << "Elija su opcion: "; cin >> op;
			if (op == 1) {
				indexarFiltro();

				string busqueda;
				vector<Fila*>* vectorcito = nullptr;
				cout << "Buscar Mayor que: "; cin >> busqueda;
				vectorcito = arbolito->mayorQue(busqueda);
				if (vectorcito != nullptr) {
					auto k1 = [](Fila* a, int i) {
						return a->atValor(i); };

					arbolito = new Arbol<Fila*, string, nullptr>(k1, columnaIndexada);
					for (int i = 0; i < vectorcito->size(); i++) {
						arbolito->add(vectorcito->at(i));
					}
					auto print = [](Fila* a) {
						if (a == nullptr) return;

						for (int i = 0; i < a->size(); i++) {
							cout << setw(15) << a->atValor(i) << " | ";
						}
						cout << endl;
					};

					arbolito->inOrder(print);
				}
			}
			if (op == 2) {
				indexarFiltro();

				string busqueda;
				vector<Fila*>* vectorcito = nullptr;
				cout << "Buscar Menor que: "; cin >> busqueda;
				vectorcito = arbolito->menorQue(busqueda);
				if (vectorcito != nullptr) {
					auto k1 = [](Fila* a, int i) {
						return a->atValor(i); };

					arbolito = new Arbol<Fila*, string, nullptr>(k1, columnaIndexada);
					for (int i = 0; i < vectorcito->size(); i++) {
						arbolito->add(vectorcito->at(i));
					}
					auto print = [](Fila* a) {
						if (a == nullptr) return;

						for (int i = 0; i < a->size(); i++) {
							cout << setw(15) << a->atValor(i) << " | ";
						}
						cout << endl;
					};

					arbolito->inOrder(print);
				}
			}
			if (op == 3) {
				indexarFiltro();

				string busqueda;
				vector<Fila*>* vectorcito = nullptr;
				cout << "Buscar Igual a: "; cin >> busqueda;
				vectorcito = arbolito->findElementos(busqueda);

				if (vectorcito != nullptr) {
					auto k1 = [](Fila* a, int i) {
						return a->atValor(i); };

					arbolito = new Arbol<Fila*, string, nullptr>(k1, columnaIndexada);
					for (int i = 0; i < vectorcito->size(); i++) {
						arbolito->add(vectorcito->at(i));
					}
					auto print = [](Fila* a) {
						if (a == nullptr) return;

						for (int i = 0; i < a->size(); i++) {
							cout << setw(15) << a->atValor(i) << " | ";
						}
						cout << endl;
					};

					arbolito->inOrder(print);
				}
				else {
					cout << "No se encontro, no se modifico nada" << endl;
				}

			}
			if (op == 4) {
				indexarFiltro();

				string busqueda;
				vector<Fila*>* vectorcito = nullptr;
				cout << "Inicia con: "; cin >> busqueda;
				auto k = [](string pal, string a) {
					int n = a.size();
					string aux = "";
					for (int i = 0; i < n; i++) {
						aux += pal.at(i);
					}
					if (aux == a) {
						return true;
					}
					else {
						return false;
					}
				};

				vectorcito = arbolito->encontrarFiltro(busqueda, k);

				if (vectorcito != nullptr) {
					auto k1 = [](Fila* a, int i) {
						return a->atValor(i); };

					arbolito = new Arbol<Fila*, string, nullptr>(k1, columnaIndexada);
					for (int i = 0; i < vectorcito->size(); i++) {
						arbolito->add(vectorcito->at(i));
					}
					auto print = [](Fila* a) {
						if (a == nullptr) return;

						for (int i = 0; i < a->size(); i++) {
							cout << setw(15) << a->atValor(i) << " | ";
						}
						cout << endl;
					};

					arbolito->inOrder(print);
				}
				else {
					cout << "No se encontro, no se modifico nada" << endl;
				}
			}
			if (op == 5) {
				indexarFiltro();

				string busqueda;
				vector<Fila*>* vectorcito = nullptr;
				cout << "Inicia con: "; cin >> busqueda;
				auto k = [](string pal, string a) {
					int n = a.size();
					string aux = "";
					for (int i = pal.size() - n; i < pal.size(); i++) {
						aux += pal.at(i);
					}
					if (aux == a) {
						return true;
					}
					else {
						return false;
					}
				};

				vectorcito = arbolito->encontrarFiltro(busqueda, k);

				if (vectorcito != nullptr) {
					auto k1 = [](Fila* a, int i) {
						return a->atValor(i); };

					arbolito = new Arbol<Fila*, string, nullptr>(k1, columnaIndexada);
					for (int i = 0; i < vectorcito->size(); i++) {
						arbolito->add(vectorcito->at(i));
					}
					auto print = [](Fila* a) {
						if (a == nullptr) return;

						for (int i = 0; i < a->size(); i++) {
							cout << setw(15) << a->atValor(i) << " | ";
						}
						cout << endl;
					};

					arbolito->inOrder(print);
				}
				else {
					cout << "No se encontro, no se modifico nada" << endl;
				}
			}
			if (op == 6) {
				indexarFiltro();

				string busqueda;
				vector<Fila*>* vectorcito = nullptr;
				cout << "Esta contenido con: "; cin >> busqueda;
				auto k = [](string pal, string a) {
					int n = a.size();
					if (n > 2) {
						char* p1 = new char[pal.size()];
						char* p2 = new char[a.size()];
						char* p;
						for (int i = 0; i < pal.size(); i++) {
							p1[i] = pal.at(i);
						}
						for (int i = 0; i < a.size(); i++) {
							p2[i] = a.at(i);
						}
						p = strstr(p1, p2);
						if (p) {
							return true;
						}
						else {
							return false;
						}
					}
					else if (n == 1) {
						char c = a.at(0);
						for (int i = 0; i < pal.size(); i++) {
							if (c == pal.at(i)) {
								return true;
							}
						}
						return false;
					}
					else if (n == 2) {
						char* p2 = new char[a.size()];

						for (int i = 0; i < a.size(); i++) {
							p2[i] = a.at(i);
						}
						for (int i = 1; i < pal.size(); i++) {
							if (pal.at(i) == p2[1] && pal.at(i - 1) == p2[0]) {
								return true;
							}
						}
						return false;
					}
					else {
						return false;
					}
				};

				vectorcito = arbolito->encontrarFiltro(busqueda, k);

				if (vectorcito != nullptr) {
					auto k1 = [](Fila* a, int i) {
						return a->atValor(i); };

					arbolito = new Arbol<Fila*, string, nullptr>(k1, columnaIndexada);
					for (int i = 0; i < vectorcito->size(); i++) {
						arbolito->add(vectorcito->at(i));
					}
					auto print = [](Fila* a) {
						if (a == nullptr) return;

						for (int i = 0; i < a->size(); i++) {
							cout << setw(15) << a->atValor(i) << " | ";
						}
						cout << endl;
					};

					arbolito->inOrder(print);
				}
				else {
					cout << "No se encontro, no se modifico nada" << endl;
				}
			}
			if (op == 7) {
				indexarFiltro();

				string busqueda;
				vector<Fila*>* vectorcito = nullptr;
				cout << "No esta contenido con: "; cin >> busqueda;
				auto k = [](string pal, string a) {
					int n = a.size();
					if (n > 2) {
						char* p1 = new char[pal.size()];
						char* p2 = new char[a.size()];
						char* p;
						for (int i = 0; i < pal.size(); i++) {
							p1[i] = pal.at(i);
						}
						for (int i = 0; i < a.size(); i++) {
							p2[i] = a.at(i);
						}
						p = strstr(p1, p2);
						if (p) {
							return false;
						}
						else {
							return true;
						}
					}
					else if (n == 1) {
						char c = a.at(0);
						for (int i = 0; i < pal.size(); i++) {
							if (c == pal.at(i)) {
								return false;
							}
						}
						return true;
					}
					else if (n == 2) {
						char* p2 = new char[a.size()];

						for (int i = 0; i < a.size(); i++) {
							p2[i] = a.at(i);
						}
						for (int i = 1; i < pal.size(); i++) {
							if (pal.at(i) == p2[1] && pal.at(i - 1) == p2[0]) {
								return false;
							}
						}
						return true;
					}
					else {
						return false;
					}
				};

				vectorcito = arbolito->encontrarFiltro(busqueda, k);

				if (vectorcito != nullptr) {
					auto k1 = [](Fila* a, int i) {
						return a->atValor(i); };

					arbolito = new Arbol<Fila*, string, nullptr>(k1, columnaIndexada);
					for (int i = 0; i < vectorcito->size(); i++) {
						arbolito->add(vectorcito->at(i));
					}
					auto print = [](Fila* a) {
						if (a == nullptr) return;

						for (int i = 0; i < a->size(); i++) {
							cout << setw(15) << a->atValor(i) << " | ";
						}
						cout << endl;
					};

					arbolito->inOrder(print);
				}
				else {
					cout << "No se encontro, no se modifico nada" << endl;
				}
			}
		}
		else {
			cout << "No se ha indexado ninguna columna" << endl;
		}
	}
	void ordenamientoDatosPorColumna() {
		if (arbolito != nullptr) {
			indexarFiltro();
			auto print = [](Fila* a) {
				if (a == nullptr) return;

				for (int i = 0; i < a->size(); i++) {
					cout << setw(15) << a->atValor(i) << " | ";
				}
				cout << endl;
			};
			arbolito->inOrder(print);
		}
		else {
			cout << "No se ha indexado ninguna columna" << endl;
		}
	}
	void exportacionDatos() {
		if (arbolito != nullptr) {
			string nombre;
			int op;
			cout << "Escriba el nombre del archivo a generar: "; cin >> nombre;
			cout << "Escoga (1) .txt / (2) .csv : "; cin >> op;
			if (op == 1) {
				nombre += ".txt";
			}
			if (op == 2) {
				nombre += ".csv";
			}
			vecAux = arbolito->retornarTodo();
			escribir.open(nombre, ios::out | ios::app);
			if (escribir.is_open()) {
				for (int i = 0; i < tablita->sizeC() - 1; i++) {
					escribir << tablita->atC(i)->get_nombre() << ",";
				}
				escribir << tablita->atC(tablita->sizeC() - 1)->get_nombre() << endl;


				for (int f = 0; f < vecAux->size(); f++) {
					for (int c = 0; c < vecAux->at(0)->size() - 1; c++) {
						escribir << vecAux->at(f)->atValor(c) << ",";
					}
					escribir << vecAux->at(f)->atValor(vecAux->at(0)->size() - 1) << endl;
				}
			}
			escribir.close();
			apuntarNombreTabla(nombre);
			cout << "Se exporto correctamente" << endl;
			
			
		}
		else {
			cout << "No se ha indexado ninguna columna" << endl;
		}
	}
	int sizeF() {
		tablita->size();
	}
	int sizeC() {
		tablita->sizeC();
	}
	void clear() {
		tablita->Clear();
		tablita = nullptr;
	}
	Columna* atC(int indice) {
		return tablita->atC(indice);
	}
	Columna* find(string nombre) {
		return tablita->findC(nombre);
	}
};


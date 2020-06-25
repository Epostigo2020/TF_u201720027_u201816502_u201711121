#include "Controlador.h"


int main() {
	int op;
	Controlador* control = new Controlador();
	string arc;
	while (true) {
		system("cls");
		cout << "(1) Crear Tabla" << endl;
		cout << "(2) Seleccionar Tabla " << endl;
		cout << "(3) Insercion de Registros " << endl;
		cout << "(4) Seleccion de Columna" << endl;
		cout << "----------------------------------" << endl;
		cout << "(5) Indexado de Datos por Columna" << endl;
		cout << "(6) Filtrado de Datos por Columna" << endl;
		cout << "(7) Ordenamiento de Datos por Columna" << endl;
		cout << "(8) Exportación de Datos a Archivos" << endl;
		cin >> op;
		if (op == 1) {
			control->generarTabla();
			system("pause");
		}
		if (op == 2) {
			if (control != nullptr) {
				system("cls");
				control->seleccionarTabla();
				system("pause");
			}
		}
		if (op == 3) {
			if (control != nullptr) {
				system("cls");
				control->insercionRegistros();
				system("pause");
			}
			else {
				cout << "No se ha cargado ningun archivo" << endl;
				system("pause");
			}
			
		}
		if (op == 4) {
			system("cls");
			control->seleccionDatosColuma();
			system("pause");
		}
		if (op == 5) {
			control->indexar();
			system("pause");
		}
		if (op == 6) {
			system("cls");
			control->filtradoDatos();
			system("pause");
		}
		if (op == 7) {
			system("cls");
			control->ordenamientoDatosPorColumna();
			system("pause");
		}
		if (op == 8) {
			system("cls");
			control->exportacionDatos();
			system("pause");
		}
	}
	system("pause");
}

/*
string nomC;
			cout << "Escribe el nombre de la columa: "; cin >> nomC;
			Columna* seleccion = control->find(nomC);
			cout << seleccion->get_nombre() << endl;

			for (int i = 0; i < seleccion->size(); i++) {
				cout << seleccion->atValor(i) << endl;
			}
			system("pause");
*/
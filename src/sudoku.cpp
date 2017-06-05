#include <iostream>
#include "sudoku.h"

using namespace std;

void sudoku_print(Tablero t) {
	cout << "-------------------";
	cout << endl;
	for (int i = 0; i < 9; i++) {
		cout << "|";
		for (int j = 0; j < 9; j++) {
			if (t[i][j] == 0) {
				cout << " ";
			} else {
				cout << t[i][j];
			}
			cout << "|";
		}
		cout << endl;
		if (i == 8) {
			cout << "+-+-+-+-+-+-+-+-+-+";
		} else {
			cout << "-------------------";
		}
		cout << endl;
	}
}

bool sudoku_esCeldaVacia(Tablero t, int f, int c) {
	return t[f][c] == 0;
}
void sudoku_vaciarTablero(Tablero t) {
	// COMPLETAR
}

int sudoku_nroDeCeldasVacias(Tablero t) {
	// COMPLETAR
	return -1;
}

int sudoku_primerCeldaVaciaFila(Tablero t) {
	// COMPLETAR
	return -1;
}

int sudoku_primerCeldaVaciaColumna(Tablero t) {

	/* itera por todas las filas. luego por todas las columnas.
	 * cuando encuentra la celda, debería dejar de iterar y devolver
	 * */

	int res = -1; // -1 significa que no fue hallada

	// Itera en orden por todas las filas y columnas.
	for (int f = 0; f < 9 && res == -1; f++) {
		for (int c = 0; f < 9 && res == -1; f++) {

			if (sudoku_esCeldaVacia(t, f, c)) {
				// Hallamos la primer celda vacía.
				res = c; // Ahora que res != -1, deja de iterar.
			}
		}
	}

	return res;
}

int sudoku_valorEnCelda(Tablero t, int f, int c) {
	// COMPLETAR
	return -1;
}

void sudoku_llenarCelda(Tablero t, int f, int c, int v) {
	// COMPLETAR
}

void sudoku_vaciarCelda(Tablero t, int f, int c) {
	// COMPLETAR
}

bool sudoku_esTableroValido(Tablero t) {
	/*
	 * Tablero es un typedef para Tablero[9][9], Por lo tanto, las dimensiones
	 * son validas. Resta verificar que para todos los casilleros, vale que el
	 * entero que contienen esta en rango.
	 * */

	bool res = true;

	for (int f = 0; f < 9; f++) {
		for (int c = 0; c < 9; c++) {
			// Si no esta en rango la celda:
			if (! (0 <= t[f][c] && t[f][c] <= 9)) {
				res = false; // Y nada la va a volver a setear a true
			}
		}
	}


	return res;
}

bool sudoku_esTableroParcialmenteResuelto(Tablero t) {
	// COMPLETAR
	return false;
}

bool sudoku_esTableroTotalmenteResuelto(Tablero t) {
	// COMPLETAR
	return false;
}

bool sudoku_esSubTablero(Tablero t0, Tablero t1) {
	bool result = true;
	int f = 0;
	//Empieza a recorrer el tablero t0 celda por celda
	while (f < 9 && result){				//Significa que va a salir del ciclo cuando encuentre una celda que indica 
		int c = 0;							//que t0 no es subtablero de t1. Repito eso para el ciclo de la columna.
		while (c < 9 && result){
			if (!sudoku_esCeldaVacia(t0, f, c) && t0[f][c] != t1[f][c]){
				result = false;
			} 
			c++;
		}
		f++;
	}
	return result;
}

bool sudoku_resolver(Tablero t) {
	// COMPLETAR

	bool res;
	int count = 0; // Cuenta, va a ser ignorada.
	res = sudoku_resolver(t, count);

	return res;
}

bool sudoku_resolver(Tablero t, int& count) {
	// COMPLETAR
	return false;
}


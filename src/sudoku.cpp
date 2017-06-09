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
	for (int iFila = 0; iFila < 9; iFila++) {
		for (int iColumna = 0; iColumna < 9; iColumna++) {
			t[iFila][iColumna] = 0;
		}
	}
}

int sudoku_nroDeCeldasVacias(Tablero t) {
	int f = 0;
	int celdasVacias = 0;
	while (f < 9) {
		int c = 0;
		while (c < 9) {
			if (t[f][c] == 0) {
				celdasVacias++;
			}
			c++;
		}
		f++;
	}
	return celdasVacias;
}

int sudoku_primerCeldaVaciaFila(Tablero t) {
	int res = -1;
	int f = 0;
	//va iterando por todas las celdas en sentido horizontal//
	while (f < 9) {
		int c = 0;
		while (c < 9) {
			if (sudoku_esCeldaVacia(t, f, c)) {
				//encontré la primera celda//
				res = f;
			}
			c = c + 1;
		}
		f = f + 1;
	}
	//si no hay celda vacía, el resultado es -1.
	return res;
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
	int result = 0; //no hace falta inicializar, pero si lo hago es mejor, no?
	result = t[f][c]; //se podrían escribir ésta y la linea anterior en una sola? ej: int result = t[f][c];
	return result; //FIXME el archivo original tennía "return result-1;" lo cambié por mi código, no le veo ningún sentido al original
}

void sudoku_llenarCelda(Tablero t, int f, int c, int v) {
	t[f][c] = v;
}

void sudoku_vaciarCelda(Tablero t, int f, int c) {
	t[f][c] = 0;
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
			if (!(0 <= t[f][c] && t[f][c] <= 9)) {
				res = false; // Y nada la va a volver a setear a true
			}
		}
	}

	return res;
}

bool sudoku_esTableroParcialmenteResuelto(Tablero t) {

	return filasOk(t) && columnasOk(t) && regionesOk(t);
}

bool filasOk(Tablero t) {
	bool res = true;
	int f = 0;
	while (f < 9) {
		int c = 0;
		while (c < 8) {
			int k = c + 1;
			while (k < 9) {
				if ((t[f][c] = !0) && (t[f][c] == t[f][k])) {
					res = false;
				}
				k++;
			}
			c++;
		}
		f++;
	}
	return res;
}

bool columnasOk(Tablero t) {
	bool res = true;
	int c = 0;
	while (c < 9) {
		int f = 0;
		while (f < 8) {
			int k = f + 1;
			while (k < 9) {
				if ((t[f][c] = !0) && (t[f][c] == t[k][c])) {
					res = false;
				}
				k++;
			}
			f++;
		}
		c++;
	}
	return res;
}

int cantidadEnRegion(Tablero t, int x, int y, int valor) {
	int f = 0;
	int count = 0;
	if (t[(3 * x) + f][(3 * y) + c] == 0) {
		count = 1;
	} else {
		while (f < 3) {
			int c = 0;
			while (c < 3) {
				if (t[(3 * x) + f][(3 * y) + c] == valor) {
					count++;
				}
				c++;
			}
			f++;
		}
	}
	return count;
}

bool regionValida(Tablero t, int x, int y) {
	bool result = true;
	int f = 0;
	while (f < 3) {
		int c = 0;
		while (c < 3) {
			if (cantidadEnRegion(t, x, y, t[(3 * x) + f][(3 * y) + c]) != 1) {
				result = false;
			}
			c++;
		}
		f++;
	}
	return result;
}

bool regionesOk(Tablero t) {
	int x = 0;
	bool result = true;
	while (x < 3) {
		int y = 0;
		while (y < 3) {
			if (regionValida(t, x, y) == false) {
				result = false;
			}
			y++;
		}
		x++;
	}
	return result;
}

bool sudoku_esTableroTotalmenteResuelto(Tablero t) {
	// Se desprende fácil de la especificación
	return sudoku_esTableroParcialmenteResuelto(t) && sudoku_nroDeCeldasVacias(
			t) == 0;
}

bool sudoku_esSubTablero(Tablero t0, Tablero t1) {
	bool result = true;
	int f = 0;
	//Empieza a recorrer el tablero t0 celda por celda
	while (f < 9 && result) { //Significa que va a salir del ciclo cuando encuentre una celda que indica
		int c = 0; //que t0 no es subtablero de t1. Repito eso para el ciclo de la columna.
		while (c < 9 && result) {
			if (!sudoku_esCeldaVacia(t0, f, c) && t0[f][c] != t1[f][c]) {
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


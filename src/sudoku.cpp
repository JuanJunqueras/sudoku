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

	/**
	 * Primero, se deben obtener las coordenadas de todas las celdas vacias
	 * del tablero para saber donde modificar el tablero.
	 * */
	vector<int> celdasVaciasFilas;
	vector<int> celdasVaciasColumnas;

	int proximaCeldaVaciaFila = sudoku_primerCeldaVaciaFila();
	int proximaCeldaVaciaColumna = sudoku_primerCeldaVaciaColumna();
	/* Por especificacion, si no hay una proxima celda vacía, tanto
	 * sudoku_primerCeldaVaciaFila como sudoku_primerCeldaVaciaColumna
	 * deberían devolver -1. De este modo, si las funciones son correctas
	 * respecto de su especificacion, Debería parar cuando se acaban las
	 * celdas vacías para agregar a la lista.
	 *  */
	while (proximaCeldaVacia != -1) {

		// Por la guarda, sabemos que existe una proxima celda vacia.
		celdasVaciasFilas.push_back(proximaCeldaVaciaFila);
		celdasVaciasColumnas.push_back(proximaCeldaVaciaColumna);

		// Ponemos un 1.
		sudoku_llenarCelda(t, proximaCeldaVaciaFila, proximaCeldaVaciaColumna,
				1);

		// Obtenemos las coordenadas de la proxima celda vacia.
		int proximaCeldaVaciaFila = sudoku_primerCeldaVaciaFila();
		int proximaCeldaVaciaColumna = sudoku_primerCeldaVaciaColumna();
	}

	/* Ahora se deben probar todas las posibles combinaciones de numeros en
	 * las casillas vacias hasta hallar un resultado valido.
	 * */
	while (! sudoku_esTableroTotalmenteResuelto(t)) {


		// Incrementa los casilleros para obtener la proxima combinacion.
		for (int i = 0; i < (int) celdasVaciasFilas.size(); i++) {

			// Obtiene las coordenadas para la i-esima celda vacia.
			int f = celdasVaciasFilas[i];
			int c = celdasVaciasColumnas[i];
			// Obtiene el valor en la i-esima fila
			int v = sudoku_valorEnCelda(t, f, c);

			if (v < 9) {
				// Incrementamos el valor en la celda. La especificacion dice que
				// Debe estar vacia para llenarla.
				sudoku_vaciarCelda(t, f, c);
				sudoku_llenarCelda(t, f, c, v + 1);

				// No debemos tocar ninguna otra celda. Saco de rango el indice
				// para salir del loop.
				i = (int) celdasVaciasFilas.size();
			} else {
				// Si el valor ya esta en el maximo (v == 9), en vez de
				// incrementarlo voy a querer devolverlo a 1.
				sudoku_vaciarCelda(t, f, c);
				sudoku_llenarCelda(t, f, c, 1);
				// Ahora, en vez de cortar el loop, dejo que avance a la proxima.
			}

		}


	}

	// El tablero debería estar resuelto.

	return false;
}


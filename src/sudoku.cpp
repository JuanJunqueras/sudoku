#include <iostream>
#include <vector>
#include "sudoku.h"

using namespace std;

void sudoku_print(Tablero t) {
	// Lo cambiamos porque este nos parece mas legible
	for (int f = 0; f < 9; f++) {

		for (int c = 0; c < 9; ++c) {

			cout << " " << t[f][c];

			// Imprime columna luego del elemento 2 y 5.
			if (c == 2 || c == 5) {
				cout << " |";
			}
		}

		cout << endl;

		// Imprime los separadores luego de la fila 2 y 5:
		if (f == 2 || f == 5) {
			cout << "-------+-------+-------" << endl;
		}
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

    // Avanza fila por fila buscando una celda vacia.
	while (f < 9 && res == -1) {
		int c = 0;
		while (c < 9 && res == -1) {
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
	 * la columna.
	 * */

	int res = -1; // -1 significa que no fue hallada

    // Itera fila por fila buscando el primer elemento vacio
	for (int f = 0; f < 9 && res == -1; f++) {
		for (int c = 0; c < 9 && res == -1; c++) {

			if (sudoku_esCeldaVacia(t, f, c)) {
				// Hallamos la primer celda vacía.
				res = c; // Ahora que res != -1, deja de iterar.
			}
		}
	}

	return res;
}

int sudoku_valorEnCelda(Tablero t, int f, int c) {
    return t[f][c];
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
    // Se desprende de la especificacion.
	return sudoku_esTableroValido(t) && filasOk(t) && columnasOk(t)
			&& regionesOk(t);
}

bool filasOk(Tablero t) {
	bool res = true;

    /* Por cada fila, se asegura que para cada elemento distinto a cero en ella, no se vuelva a repetir a su derecha.
     */

	for (int f = 0; f < 9; ++f) {
		for (int c = 0; c < 8; ++c) {

			// No debe volver a aparecer a la derecha c.
			for (int k = c + 1; k < 9; k++) {

				if ((t[f][c] != 0) && (t[f][c] == t[f][k])) {
					res = false;
				}

			}
		}
	}

	return res;
}

bool columnasOk(Tablero t) {
	bool res = true;

    /* Para cada columna, se asegura que para cada elemento distinto a cero en ella, no se repite por debajo.
     * */

	for (int c = 0; c < 9; c++) {
		for (int f = 0; f < 8; f++) {

			if (t[f][c] != 0) {
				// Si el casillero es distinto de 0, para toda celda inferior,
				// su valor es distinto.
				for (int fPrima = f + 1; fPrima < 9; fPrima++) {
					res &= t[f][c] != t[fPrima][c];
				}
			}
		}
	}

	return res;
}

bool laRegionNoTieneRepetidas(Tablero t, int f, int c) {

    /* Devuelve true si la region que empieza en (f, c) no contiene elementos distintos a 0 que se repitan.
     * f y c deben ser 0, 3, o 6.
     */
    // f y c son las esquinas superiores izquierdas del tablero
	bool result = true;

	for (int k = 1; k <= 9; k++) {

        // Contamos cuantas veces se repite el valor "k".
		int count = 0;

		// Contamos las apariciones de k en la region.
		for (int fOffset = 0; fOffset < 3; fOffset++) {
			for (int cOffset = 0; cOffset < 3; cOffset++) {

				if (t[f + fOffset][c + cOffset] == k) {
					count++;
				}
			}
		}

		result &= count < 2;

	}

	return result;

}

bool regionesOk(Tablero t) {

	bool result = true;

    // Se identifican las regiones por dos indices entre 0 y 2 inclusive.
	for (int xRegion = 0; xRegion < 3; ++xRegion) {
		for (int yRegion = 0; yRegion < 3; ++yRegion) {

			// La esquina donde comienza la region en el tablero. (sup-izq)
			int f = xRegion * 3;
			int c = yRegion * 3;

            // Verificamos que no haya repetidas en ninguna de las 9 regiones
			result &= laRegionNoTieneRepetidas(t, f, c);

		}
	}

	return result;
}

bool sudoku_esTableroTotalmenteResuelto(Tablero t) {
	// Se desprende fácil de la especificación
	return sudoku_esTableroParcialmenteResuelto(t)
			&& sudoku_nroDeCeldasVacias(t) == 0;
}

bool sudoku_esSubTablero(Tablero t0, Tablero t1) {
	bool result = true;
	int f = 0;
	while (f < 9 && result) {
		int c = 0;
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
    // Wrapeamos sudoku_resolver(Tablero r, int& count) para no tener codigo duplicado.
	bool res;
	int count = 0; // Cuenta, va a ser ignorada.
	res = sudoku_resolver(t, count);
	return res;
}

bool sudoku_resolver(Tablero t, int& count) {
	bool pudeResolver = false;

	if (sudoku_esTableroTotalmenteResuelto(t)) {
		// Caso base de la recursion.
		pudeResolver = true;
	} else if (sudoku_esTableroParcialmenteResuelto(t)){
		/* Coordenadas de la primer celda vacia.
		 *
		 * Sabemos que f != -1 y c != -1 porque esta parcialmente resuelto,
		 * pero no totalmente, por lo tanto debe haber alguna celda vacia.
		 */
		int f = sudoku_primerCeldaVaciaFila(t);
		int c = sudoku_primerCeldaVaciaColumna(t);

		for (int v = 1; (v < 10) && (! pudeResolver); ++v) { // 1 a 9 inclusive.
            t[f][c] = v;
			count++;

			// Busca por ese camino por recursion.
			pudeResolver = sudoku_resolver(t, count);
		}

		// Si no pudo resolver en ninguno de los 9 valores.
		if (! pudeResolver) {
			sudoku_vaciarCelda(t, f, c); // deja la celda como estaba.
			count++;
		}
	}

	/* Hay un tercer caso: El tablero no es parcialmente resuelto. No hay nada
	 * que hacer. Se devuelve false y punto.
	 */

	return pudeResolver;
}


#include <iostream>
#include <vector>
#include "sudoku.h"

using namespace std;

void sudoku_print(Tablero t) {
	for (int f = 0; f < 9; f++) {

		for (int c = 0; c < 9; ++c) {

			cout << " " << t[f][c];

			// Imprime columna
			if (c == 2 || c == 5) {
				cout << " |";
			}
		}

		cout << endl;

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
	//va iterando por todas las celdas en sentido horizontal//
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
	 * */

	int res = -1; // -1 significa que no fue hallada

	// Itera en orden por todas las filas y columnas.
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

	return sudoku_esTableroValido(t) && filasOk(t) && columnasOk(t)
			&& regionesOk(t);
}

bool filasOk(Tablero t) {
	bool res = true;

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

	bool result = true;

	for (int k = 1; k <= 9; k++) {

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

	for (int xRegion = 0; xRegion < 3; ++xRegion) {
		for (int yRegion = 0; yRegion < 3; ++yRegion) {

			// La esquina donde comienza la region en el tablero. (sup-izq)
			int f = xRegion * 3;
			int c = yRegion * 3;

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

vector<pair<int, int> > companeras(int f, int c) {

	vector<pair<int, int> > listaCompaneras;

	// Todas las compañeras de columna
	for (int iFila = 0; iFila < 9; iFila++) {
		if (iFila != f) {
			pair<int, int> coord(iFila, c);
			listaCompaneras.push_back(coord);
		}
	}

	// Todas las compañeras de fila
	for (int iColumna = 0; iColumna < 9; ++iColumna) {
		if (iColumna != c) {
			pair<int, int> coord(f, iColumna);
			listaCompaneras.push_back(coord);
		}
	}

	// Las compañeras de region (que no estan aun en la lista)
	// Esquina sup izda de la region:
	int fRegion = f / 3;
	int cRegion = c / 3;
	// Con el metodo de offsets (o defases) logramos las 9 coords de la region.
	for (int fOffset = 0; fOffset < 3; ++fOffset) {
		for (int cOffset = 0; cOffset < 3; ++cOffset) {

			// Una coord dentro de la region
			int iFila = fRegion + fOffset;
			int iColumna = cRegion + cOffset;

			// Si no pertenecen a la misma fila o columna, las añado al set.
			if (iFila != f && iColumna != c) {
				pair<int, int> coord(iFila, iColumna);
				listaCompaneras.push_back(coord);
			}
		}
	}

	return listaCompaneras;
}

vector<int> candidatas(Tablero t, int f, int c) {

	vector<int> respuesta;
	respuesta.clear();

	if (sudoku_esCeldaVacia(t, f, c)) { // Si no es celda vacia, no hay candidatas.

		// Determina si un numero es candidato valido o no.
		// Hay un lugar para el 0 que esta por comodidad.
		bool esCandidata[10] = { false, true, true, true, true, true, true,
				true, true, true };

		vector<pair<int, int> > listaCompaneras = companeras(f, c);

		// Remueve de las candidatas todas las que ya ocupó alguna compañera.
		for (int i = 0; i < (int) listaCompaneras.size(); ++i) {

			// Coord de la compañera.
			int iFila = listaCompaneras[i].first;
			int iColumna = listaCompaneras[i].second;
			int v = t[iFila][iColumna];
			esCandidata[v] = false; // Ya no es mas candidata.

			/* Si no hubiese un indice extra para el 0, deberiamos restar 1, poner
			 * un if para ignorar las celdas vacias, etc.
			 */
		}

		// Ahora devuelvo los que si son candidatos.

		for (int i = 1; i < 10; ++i) {
			if (esCandidata[i]) {
				respuesta.push_back(i);
			}
		}
	}

	return respuesta;
}

void sudoku_copiarTablero(Tablero t0, Tablero t1, int& count) {

	for (int f = 0; f < 9; ++f) {
		for (int c = 0; c < 9; ++c) {
			count++;
			t1[f][c] = t0[f][c];
		}
	}
}

#define ix(f, c) (f * 8 + c)
bool sudoku_resolver(Tablero t, int& count) {
	bool pudeResolver = false;

	if (sudoku_esTableroTotalmenteResuelto(t)) {
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
			sudoku_llenarCelda(t, f, c, v);
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


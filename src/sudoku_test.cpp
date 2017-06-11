#include "../lib/gtest/gtest.h"
#include "sudoku.h"

TEST(sudoku_esCeldaVaciaTEST, celdaVacia) {
	Tablero t;
	sudoku_vaciarTablero(t);
	bool rv = sudoku_esCeldaVacia(t, 0, 0);
	ASSERT_EQ(true, rv);
}

TEST(sudoku_esCeldaVaciaTEST, celdaNoVacia) {
	Tablero t;
	sudoku_vaciarTablero(t);
	sudoku_llenarCelda(t, 0, 0, 1);
	bool rv = sudoku_esCeldaVacia(t, 0, 0);
	ASSERT_EQ(false, rv);
}

TEST(sudoku_nroDeCeldasVaciasTEST, cantCeldasVaciasEnTableroVacio) {
	Tablero t;
	sudoku_vaciarTablero(t);
	int rv = sudoku_nroDeCeldasVacias(t);
	ASSERT_EQ(81, rv);
}

TEST(sudoku_nroDeCeldasVaciasTEST, cantCeldasVaciasEnTableroNoVacio) {
	Tablero t;
	sudoku_vaciarTablero(t);
	sudoku_llenarCelda(t, 0, 0, 1);
	int rv = sudoku_nroDeCeldasVacias(t);
	ASSERT_EQ(80, rv);
}

TEST(sudoku_primerCeldaVaciaAmbosTEST, primerCeldaVaciaEnTableroVacio) {
	Tablero t;
	sudoku_vaciarTablero(t);
	int f = sudoku_primerCeldaVaciaFila(t);
	int c = sudoku_primerCeldaVaciaColumna(t);
	ASSERT_EQ(0, f);
	ASSERT_EQ(0, c);
}

TEST(sudoku_primerCeldaVaciaAmbosTEST, primerCeldaVaciaEnTableroNoVacio) {
	Tablero t;
	sudoku_vaciarTablero(t);
	sudoku_llenarCelda(t, 0, 0, 1);
	int f = sudoku_primerCeldaVaciaFila(t);
	int c = sudoku_primerCeldaVaciaColumna(t);
	ASSERT_EQ(0, f);
	ASSERT_EQ(1, c);
}

TEST(sudoku_primerCeldaVaciaAmbosTEST, primerCeldaVaciaEnTableroNoVacioFilaCompleta) {
	Tablero t;
	sudoku_vaciarTablero(t);
	for (int i = 0; i < 9; i++) {
		sudoku_llenarCelda(t, 0, i, i + 1);
	}
	int f = sudoku_primerCeldaVaciaFila(t);
	int c = sudoku_primerCeldaVaciaColumna(t);
	ASSERT_EQ(1, f);
	ASSERT_EQ(0, c);
}

TEST(sudoku_primerCeldaVaciaColumnaTEST, primerCeldaVaciaEnTableroVacio) {
	Tablero t;
	sudoku_vaciarTablero(t);
	int c = sudoku_primerCeldaVaciaColumna(t);
	ASSERT_EQ(0, c);
}

TEST(sudoku_primerCeldaVaciaColumnaTEST, primerCeldaVaciaEnTableroNoVacio) {
	Tablero t;
	sudoku_vaciarTablero(t);
	sudoku_llenarCelda(t, 0, 0, 1);
	int c = sudoku_primerCeldaVaciaColumna(t);
	ASSERT_EQ(1, c);
}

TEST(sudoku_primerCeldaVaciaColumnaTEST, primerCeldaVaciaEnTableroNoVacioFilaCompleta) {
	Tablero t;
	sudoku_vaciarTablero(t);
	for (int i = 0; i < 9; i++) {
		sudoku_llenarCelda(t, 0, i, i + 1);
	}
	int c = sudoku_primerCeldaVaciaColumna(t);
	ASSERT_EQ(0, c);
}

TEST(sudoku_valorEnCeldaTEST, llenarCeldaVacia) {
	Tablero t;
	sudoku_vaciarTablero(t);
	sudoku_llenarCelda(t, 0, 0, 5);
	int rv = sudoku_valorEnCelda(t, 0, 0);
	ASSERT_EQ(5, rv);
}

TEST(sudoku_valorEnCeldaTEST, llenarCeldaNoVacia) {
	Tablero t;
	sudoku_vaciarTablero(t);
	sudoku_llenarCelda(t, 4, 4, 5);
	sudoku_vaciarCelda(t, 4, 4);
	sudoku_llenarCelda(t, 4, 4, 7);
	int rv = sudoku_valorEnCelda(t, 4, 4);
	ASSERT_EQ(7, rv);
}

TEST(filasOkTest, tableroVacio) {
	Tablero t;
	sudoku_vaciarTablero(t);
	ASSERT_TRUE(filasOk(t));
}

TEST(filasOkTest, tableroLleno) {
	Tablero t;
	sudoku_vaciarTablero(t);

	for (int f = 0; f < 9; ++f) {
		for (int c = 0; c < 9; ++c) {
			t[f][c] = c;
		}
	}
	ASSERT_TRUE(filasOk(t));
}

TEST(filasOkTest, lasFilasNoEstanOk) {
	Tablero t;
	sudoku_vaciarTablero(t);
	t[5][0] = 2;
	t[5][5] = 2;
	ASSERT_FALSE(filasOk(t));
}

TEST(columnasOkTest, tableroVacio) {
	Tablero t;
	sudoku_vaciarTablero(t);
	ASSERT_TRUE(columnasOk(t));
}

TEST(columnasOkTest, tableroLleno) {
	Tablero t;
	sudoku_vaciarTablero(t);

	for (int f = 0; f < 9; ++f) {
		for (int c = 0; c < 9; ++c) {
			t[f][c] = f;
		}
	}
	ASSERT_TRUE(columnasOk(t));
}

TEST(columnasOkTest, lasColumnasNoEstanOk) {
	Tablero t;
	sudoku_vaciarTablero(t);
	t[0][4] = 2;
	t[5][4] = 2;
	ASSERT_FALSE(columnasOk(t));
}

TEST(laRegionNoTieneRepetidasTest, regionVacia) {
	Tablero t;
	sudoku_vaciarTablero(t);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			int f = i * 3;
			int c = i * 3;
			ASSERT_TRUE(laRegionNoTieneRepetidas(t, f, c));
		}
	}
}

TEST(laRegionNoTieneRepetidasTest, regionRellenada) {
	Tablero t;
	sudoku_vaciarTablero(t);

	t[0][0] = 1;
	t[0][1] = 2;
	t[0][2] = 3;
	t[1][0] = 4;
	t[1][1] = 5;
	t[1][2] = 6;

	ASSERT_TRUE(laRegionNoTieneRepetidas(t, 0, 0));
}

TEST(laRegionNoTieneRepetidasTest, regionConRepetidas) {
	Tablero t;
	sudoku_vaciarTablero(t);

	t[0][0] = 1;
	t[0][1] = 1;
	t[0][2] = 1;
	t[1][0] = 1;
	t[1][1] = 1;
	t[1][2] = 1;

	ASSERT_FALSE(laRegionNoTieneRepetidas(t, 0, 0));
}

TEST(regionesOkTest, tableroVacio) {
	Tablero t;
	sudoku_vaciarTablero(t);
	ASSERT_TRUE(regionesOk(t));
}

TEST(regionesOkTest, tableroParcialmenteCompleto) {
	Tablero t = { { 0, 9, 4, 0, 0, 0, 1, 3, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 7, 6, 0, 0, 2 }, { 0, 8, 0, 0, 1, 0, 0, 0, 0 }, { 0,
					3, 2, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 2, 0, 0, 0, 6, 0 }, {
					0, 0, 0, 0, 5, 0, 4, 0, 0 }, { 0, 0, 0, 0, 0, 8, 0, 0, 7 },
			{ 0, 0, 6, 3, 0, 4, 0, 0, 8 } };
	ASSERT_TRUE(regionesOk(t));
}

TEST(regionesOkTest, hayUnaRegionQueEstaMal) {
	Tablero t;
	sudoku_vaciarTablero(t);
	sudoku_llenarCelda(t, 5, 5, 1);
	sudoku_llenarCelda(t, 4, 4, 1);
	ASSERT_FALSE(regionesOk(t));
}

TEST(sudoku_esTableroParcialmenteResueltoTest, tableroVacio) {
	Tablero t;
	sudoku_vaciarTablero(t);
	ASSERT_TRUE(sudoku_esTableroParcialmenteResuelto(t));
}

TEST(sudoku_esTableroParcialmenteResueltoTest, tableroResuelto) {
	Tablero t = { { 0, 9, 4, 0, 0, 0, 1, 3, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 7, 6, 0, 0, 2 }, { 0, 8, 0, 0, 1, 0, 0, 0, 0 }, { 0,
					3, 2, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 2, 0, 0, 0, 6, 0 }, {
					0, 0, 0, 0, 5, 0, 4, 0, 0 }, { 0, 0, 0, 0, 0, 8, 0, 0, 7 },
			{ 0, 0, 6, 3, 0, 4, 0, 0, 8 } };
	//sudoku_print(t);

	ASSERT_TRUE(sudoku_esTableroParcialmenteResuelto(t));
}

TEST(SudokuIntegracionTest, resolverTableroVacio) {
	Tablero t;
	sudoku_vaciarTablero(t);
	bool resolver_rv = sudoku_resolver(t);
	ASSERT_EQ(true, resolver_rv);
	bool totalmente_resuelto_rv = sudoku_esTableroTotalmenteResuelto(t);
	ASSERT_EQ(true, totalmente_resuelto_rv);
}

TEST(SudokuIntegracionTest, tableroSinCeldasVacias) {
	Tablero t;
	sudoku_vaciarTablero(t);
	bool resolver_rv = sudoku_resolver(t);
	ASSERT_EQ(true, resolver_rv);
	int celdas_vacias_rv = sudoku_nroDeCeldasVacias(t);
	ASSERT_EQ(0, celdas_vacias_rv);
	int primer_celda_vacia_fila_rv = sudoku_primerCeldaVaciaFila(t);
	int primer_celda_vacia_columna_rv = sudoku_primerCeldaVaciaColumna(t);
	ASSERT_EQ(-1, primer_celda_vacia_fila_rv);
	ASSERT_EQ(-1, primer_celda_vacia_columna_rv);
}

TEST(SudokuIntegracionTest, vaciarCelda) {
	Tablero t;
	sudoku_vaciarTablero(t);
	bool esCeldaVacia0 = sudoku_esCeldaVacia(t, 0, 0);
	ASSERT_EQ(true, esCeldaVacia0);
	sudoku_llenarCelda(t, 0, 0, 1);
	bool esCeldaVacia1 = sudoku_esCeldaVacia(t, 0, 0);
	ASSERT_EQ(false, esCeldaVacia1);
	sudoku_vaciarCelda(t, 0, 0);
	bool esCeldaVacia2 = sudoku_esCeldaVacia(t, 0, 0);
	ASSERT_EQ(true, esCeldaVacia2);
}

TEST(SudokuIntegracionTest, tableroNoTotalmenteResuelto) {
	Tablero t;
	sudoku_vaciarTablero(t);
	bool tablero_valido = sudoku_esTableroValido(t);
	ASSERT_EQ(true, tablero_valido);
	bool tablero_parc_resuelto = sudoku_esTableroParcialmenteResuelto(t);
	ASSERT_EQ(true, tablero_parc_resuelto);
	bool tablero_tot_resuelto = sudoku_esTableroTotalmenteResuelto(t);
	ASSERT_EQ(false, tablero_tot_resuelto);
}

TEST(SudokuIntegracionTest, tableroInvalido) {
	Tablero t;
	sudoku_vaciarTablero(t);
	t[0][0] = 10;
	bool tablero_valido = sudoku_esTableroValido(t);
	ASSERT_EQ(false, tablero_valido);
	bool tablero_parc_resuelto = sudoku_esTableroParcialmenteResuelto(t);
	ASSERT_EQ(false, tablero_parc_resuelto);
	bool tablero_tot_resuelto = sudoku_esTableroTotalmenteResuelto(t);
	ASSERT_EQ(false, tablero_tot_resuelto);
}

TEST(SudokuIntegracionTest, esSubTablero) {
	Tablero t0;
	Tablero t1;
	sudoku_vaciarTablero(t0);
	sudoku_vaciarTablero(t1);
	bool esSubTablero0 = sudoku_esSubTablero(t0, t1);
	ASSERT_EQ(true, esSubTablero0);
	sudoku_llenarCelda(t0, 0, 0, 1);
	bool esSubTablero1 = sudoku_esSubTablero(t0, t1);
	ASSERT_EQ(false, esSubTablero1);
	bool esSubTablero2 = sudoku_esSubTablero(t1, t0);
	ASSERT_EQ(true, esSubTablero2);
}

TEST(SudokuIntegracionTest, printSudokuVacio) {
	Tablero t;
	sudoku_vaciarTablero(t);
	sudoku_llenarCelda(t, 0, 0, 1);
	sudoku_print(t);
}

TEST(SudokuIntegracionTest, cantOperaciones) {
	Tablero t;
	sudoku_vaciarTablero(t);
	int nroOperaciones = 0;
	bool resolver0 = sudoku_resolver(t, nroOperaciones);
	ASSERT_EQ(true, resolver0);
	ASSERT_LT(0, nroOperaciones);
	nroOperaciones = 0;
	bool resolver1 = sudoku_resolver(t, nroOperaciones);
	ASSERT_EQ(true, resolver1);
	ASSERT_EQ(0, nroOperaciones);
}

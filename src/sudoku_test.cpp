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

TEST(sudoku_esTableroTotalmenteResueltoTest, TableroMalResuelto) {
	Tablero t = { { 1, 4, 5, 3, 2, 7, 6, 9, 8, },
			{ 8, 3, 9, 6, 5, 4, 1, 2, 7, }, { 6, 7, 7, 7, 1, 8, 5, 4, 3, }, { 4,
					9, 6, 1, 8, 5, 3, 7, 2, }, { 2, 1, 8, 4, 7, 3, 9, 5, 6, }, {
					7, 5, 3, 2, 9, 6, 4, 8, 1, },
			{ 3, 6, 7, 5, 4, 2, 8, 1, 9, }, { 9, 8, 4, 7, 6, 1, 2, 3, 5, }, { 5,
					2, 1, 8, 3, 9, 7, 6, 4, } };
	ASSERT_FALSE(sudoku_esTableroTotalmenteResuelto(t));
}

TEST(sudoku_esTableroTotalmenteResueltoTest, tableroIrresuelto) {
	Tablero t = { { 1, 4, 5, 3, 2, 7, 6, 9, 8, },
			{ 8, 3, 9, 6, 5, 4, 1, 2, 7, }, { 6, 7, 2, 9, 1, 8, 5, 4, 3, }, { 4,
					9, 6, 1, 8, 5, 3, 7, 2, }, { 2, 1, 8, 4, 7, 3, 9, 5, 6, }, {
					7, 5, 3, 2, 9, 6, 4, 8, 1, },
			{ 3, 6, 7, 5, 4, 2, 8, 1, 9, }, { 9, 8, 4, 7, 6, 1, 2, 3, 5, }, { 5,
					2, 1, 8, 3, 9, 7, 6, 4, } };

	sudoku_vaciarCelda(t, 5, 4);
	sudoku_vaciarCelda(t, 2, 3);
	sudoku_vaciarCelda(t, 4, 4);
	sudoku_vaciarCelda(t, 5, 5);
	ASSERT_FALSE(sudoku_esTableroTotalmenteResuelto(t));
}

TEST(sudoku_esTableroTotalmenteResueltoTest, tableroTotalmenteResuelto) {
	Tablero t = { { 1, 4, 5, 3, 2, 7, 6, 9, 8, },
			{ 8, 3, 9, 6, 5, 4, 1, 2, 7, }, { 6, 7, 2, 9, 1, 8, 5, 4, 3, }, { 4,
					9, 6, 1, 8, 5, 3, 7, 2, }, { 2, 1, 8, 4, 7, 3, 9, 5, 6, }, {
					7, 5, 3, 2, 9, 6, 4, 8, 1, },
			{ 3, 6, 7, 5, 4, 2, 8, 1, 9, }, { 9, 8, 4, 7, 6, 1, 2, 3, 5, }, { 5,
					2, 1, 8, 3, 9, 7, 6, 4, } };
	ASSERT_TRUE(sudoku_esTableroTotalmenteResuelto(t));
}

TEST(sudoku_resolverTest, tableroYaResuelto) {
	Tablero t = { { 1, 4, 5, 3, 2, 7, 6, 9, 8, },
			{ 8, 3, 9, 6, 5, 4, 1, 2, 7, }, { 6, 7, 2, 9, 1, 8, 5, 4, 3, }, { 4,
					9, 6, 1, 8, 5, 3, 7, 2, }, { 2, 1, 8, 4, 7, 3, 9, 5, 6, }, {
					7, 5, 3, 2, 9, 6, 4, 8, 1, },
			{ 3, 6, 7, 5, 4, 2, 8, 1, 9, }, { 9, 8, 4, 7, 6, 1, 2, 3, 5, }, { 5,
					2, 1, 8, 3, 9, 7, 6, 4, } };
	Tablero t0 = { { 1, 4, 5, 3, 2, 7, 6, 9, 8, },
			{ 8, 3, 9, 6, 5, 4, 1, 2, 7, }, { 6, 7, 2, 9, 1, 8, 5, 4, 3, }, { 4,
					9, 6, 1, 8, 5, 3, 7, 2, }, { 2, 1, 8, 4, 7, 3, 9, 5, 6, }, {
					7, 5, 3, 2, 9, 6, 4, 8, 1, },
			{ 3, 6, 7, 5, 4, 2, 8, 1, 9, }, { 9, 8, 4, 7, 6, 1, 2, 3, 5, }, { 5,
					2, 1, 8, 3, 9, 7, 6, 4, } };

	int count = 0;
	bool fueResuelto = sudoku_resolver(t, count);

	ASSERT_TRUE(fueResuelto); // // Fue resuelto
	ASSERT_GE(count, 0); // los pasos son no negativos.
	// Son iguales
	for (int f = 0; f < 9; ++f) {
		for (int c = 0; c < 9; ++c) {
			ASSERT_EQ(t[f][c], t0[f][c]);
		}
	}
}

TEST(sudoku_resolverTest, soloFaltaUno) {
	Tablero t = { { 1, 4, 5, 3, 2, 7, 6, 9, 8, },
			{ 8, 3, 9, 6, 5, 4, 1, 2, 7, }, { 6, 7, 2, 9, 1, 8, 5, 4, 3, }, { 4,
					9, 6, 1, 0, 5, 3, 7, 2, }, { 2, 1, 8, 4, 7, 3, 9, 5, 6, }, {
					7, 5, 3, 2, 9, 6, 4, 8, 1, },
			{ 3, 6, 7, 5, 4, 2, 8, 1, 9, }, { 9, 8, 4, 7, 6, 1, 2, 3, 5, }, { 5,
					2, 1, 8, 3, 9, 7, 6, 4, } };
	Tablero rta = { { 1, 4, 5, 3, 2, 7, 6, 9, 8, },
			{ 8, 3, 9, 6, 5, 4, 1, 2, 7, }, { 6, 7, 2, 9, 1, 8, 5, 4, 3, }, { 4,
					9, 6, 1, 8, 5, 3, 7, 2, }, { 2, 1, 8, 4, 7, 3, 9, 5, 6, }, {
					7, 5, 3, 2, 9, 6, 4, 8, 1, },
			{ 3, 6, 7, 5, 4, 2, 8, 1, 9, }, { 9, 8, 4, 7, 6, 1, 2, 3, 5, }, { 5,
					2, 1, 8, 3, 9, 7, 6, 4, } };

	int count = 0;
	bool fueResuelto = sudoku_resolver(t, count);

	ASSERT_TRUE(fueResuelto); // // Fue resuelto
	ASSERT_GE(count, 0); // los pasos son no negativos.
	// Son iguales
	for (int f = 0; f < 9; ++f) {
		for (int c = 0; c < 9; ++c) {
			ASSERT_EQ(t[f][c], rta[f][c]);
		}
	}
}

TEST(sudoku_resolverTest, faltanDos) {
	Tablero t = { { 1, 4, 5, 3, 2, 7, 6, 9, 8, },
			{ 8, 3, 9, 6, 5, 4, 1, 2, 7, }, { 6, 7, 2, 9, 1, 8, 5, 4, 3, }, { 4,
					9, 6, 1, 0, 5, 0, 7, 2, }, { 2, 1, 8, 4, 7, 3, 9, 5, 6, }, {
					7, 5, 3, 2, 9, 6, 4, 8, 1, },
			{ 3, 6, 7, 5, 4, 2, 8, 1, 9, }, { 9, 8, 4, 7, 6, 1, 2, 3, 5, }, { 5,
					2, 1, 8, 3, 9, 7, 6, 4, } };
	Tablero rta = { { 1, 4, 5, 3, 2, 7, 6, 9, 8, },
			{ 8, 3, 9, 6, 5, 4, 1, 2, 7, }, { 6, 7, 2, 9, 1, 8, 5, 4, 3, }, { 4,
					9, 6, 1, 8, 5, 3, 7, 2, }, { 2, 1, 8, 4, 7, 3, 9, 5, 6, }, {
					7, 5, 3, 2, 9, 6, 4, 8, 1, },
			{ 3, 6, 7, 5, 4, 2, 8, 1, 9, }, { 9, 8, 4, 7, 6, 1, 2, 3, 5, }, { 5,
					2, 1, 8, 3, 9, 7, 6, 4, } };

	int count = 0;
	bool fueResuelto = sudoku_resolver(t, count);

	ASSERT_TRUE(fueResuelto); // // Fue resuelto
	ASSERT_GE(count, 0); // los pasos son no negativos.
	// Son iguales
	for (int f = 0; f < 9; ++f) {
		for (int c = 0; c < 9; ++c) {
			ASSERT_EQ(t[f][c], rta[f][c]);
		}
	}
}

TEST(sudoku_resolverTest, tableroFacil) {
	Tablero t = { { 1, 4, 5, 3, 2, 7, 6, 9, 8, },
			{ 8, 3, 9, 6, 5, 4, 1, 2, 7, }, { 6, 7, 2, 9, 1, 8, 5, 4, 3, }, { 4,
					9, 6, 1, 0, 0, 0, 7, 2, }, { 2, 1, 8, 4, 7, 3, 9, 5, 6, }, {
					7, 5, 3, 0, 0, 0, 4, 8, 1, },
			{ 3, 6, 7, 5, 4, 2, 8, 1, 9, }, { 9, 8, 4, 7, 6, 1, 2, 3, 5, }, { 5,
					2, 1, 8, 3, 9, 7, 6, 4, } };
	Tablero t0 = { { 1, 4, 5, 3, 2, 7, 6, 9, 8, },
			{ 8, 3, 9, 6, 5, 4, 1, 2, 7, }, { 6, 7, 2, 9, 1, 8, 5, 4, 3, }, { 4,
					9, 6, 1, 8, 5, 3, 7, 2, }, { 2, 1, 8, 4, 7, 3, 9, 5, 6, }, {
					7, 5, 3, 2, 9, 6, 4, 8, 1, },
			{ 3, 6, 7, 5, 4, 2, 8, 1, 9, }, { 9, 8, 4, 7, 6, 1, 2, 3, 5, }, { 5,
					2, 1, 8, 3, 9, 7, 6, 4, } };

	int count = 0;
	bool fueResuelto = sudoku_resolver(t, count);

	ASSERT_TRUE(sudoku_esTableroTotalmenteResuelto(t));
	ASSERT_TRUE(fueResuelto); // // Fue resuelto
	ASSERT_GE(count, 0); // los pasos son no negativos.

	// Son iguales
	for (int f = 0; f < 9; ++f) {
		for (int c = 0; c < 9; ++c) {
			ASSERT_EQ(t[f][c], t0[f][c]);
		}
	}
}

TEST(sudoku_resolverTest, tableroSinSolucion) {
	Tablero t;
	sudoku_vaciarTablero(t);
	t[0][0] = 1;
	t[1][1] = 1;

	Tablero t0;
	sudoku_vaciarTablero(t0);
	t0[0][0] = 1;
	t0[1][1] = 1;

	ASSERT_FALSE(sudoku_resolver(t));
	for (int f = 0; f < 9; f++) {
		for (int c = 0; c < 9; c++) {
			ASSERT_EQ(t[f][c], t0[f][c]);
		}
	}
}

/*
TEST(sudoku_resolverTest, unTablero) {

	Tablero t = { { 0, 0, 0, 5, 2, 0, 0, 0, 0 }, { 0, 9, 0, 0, 0, 3, 0, 0, 4 },
			{ 0, 0, 0, 0, 0, 0, 7, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 4, 0 }, { 0,
					8, 0, 0, 4, 5, 3, 0, 0 }, { 6, 0, 0, 0, 1, 0, 0, 0, 8 }, {
					7, 0, 2, 0, 0, 0, 0, 0, 0 }, { 0, 0, 8, 0, 0, 0, 0, 3, 2 },
			{ 0, 4, 0, 0, 8, 0, 0, 1, 0 } };

	int count = 0;
	ASSERT_TRUE(sudoku_resolver(t));
	ASSERT_TRUE(sudoku_esTableroTotalmenteResuelto(t));
	ASSERT_GT(count, 0);
} */

/*
 TEST(sudoku_resolverTest, tableroDificil1) {
 Tablero t = { { 6, 0, 2, 0, 5, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 4, 0, 3, 0 },
 { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 4, 3, 0, 0, 0, 8, 0, 0, 0 }, { 0,
 1, 0, 0, 0, 0, 2, 0, 0 }, { 0, 0, 0, 0, 0, 0, 7, 0, 0 }, {
 5, 0, 0, 2, 7, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 8, 1 },
 { 0, 0, 0, 6, 0, 0, 0, 0, 0 } };

 int count = 0;
 ASSERT_FALSE(sudoku_esTableroTotalmenteResuelto(t));
 ASSERT_TRUE(sudoku_resolver(t));
 ASSERT_TRUE(sudoku_esTableroTotalmenteResuelto(t));
 ASSERT_GT(count, 0);

 }
 TEST(sudoku_resolverTest, tableroDificil2) {
 Tablero t = { { 4, 5, 0, 0, 0, 0, 0, 3, 0 }, { 0, 0, 0, 8, 0, 1, 0, 0, 0 },
 { 0, 9, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 5, 0, 0, 9, 0 }, { 2,
 0, 0, 7, 0, 0, 0, 0, 0 }, { 8, 0, 0, 0, 0, 0, 0, 0, 0 }, {
 0, 1, 0, 0, 4, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 7, 0, 2 },
 { 0, 0, 0, 6, 0, 0, 8, 0, 0 } };

 int count = 0;
 ASSERT_FALSE(sudoku_esTableroTotalmenteResuelto(t));
 ASSERT_TRUE(sudoku_resolver(t));
 ASSERT_TRUE(sudoku_esTableroTotalmenteResuelto(t));
 ASSERT_GT(count, 0);

 }
 TEST(sudoku_resolverTest, tableroDificil3) {
 Tablero t = { { 1, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 6, 0, 0, 0, 0, 0, 3 },
 { 0, 8, 0, 0, 0, 0, 4, 0, 1 }, { 0, 0, 0, 6, 7, 8, 5, 0, 4 }, { 0,
 0, 0, 9, 0, 0, 0, 0, 0 }, { 0, 0, 0, 5, 0, 0, 7, 6, 0 }, {
 0, 0, 2, 0, 0, 0, 0, 0, 0 }, { 5, 9, 0, 8, 1, 4, 0, 0, 0 },
 { 0, 0, 0, 3, 0, 0, 9, 0, 0 } };

 int count = 0;
 ASSERT_FALSE(sudoku_esTableroTotalmenteResuelto(t));
 ASSERT_TRUE(sudoku_resolver(t));
 ASSERT_TRUE(sudoku_esTableroTotalmenteResuelto(t));
 ASSERT_GT(count, 0);

 }
 TEST(sudoku_resolverTest, tableroDificil4) {
 Tablero t = { { 8, 0, 0, 0, 0, 0, 3, 0, 2 }, { 6, 0, 0, 0, 3, 5, 0, 0, 0 },
 { 0, 0, 9, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 2, 6, 0, 9 }, { 0,
 0, 0, 0, 7, 0, 0, 0, 1 }, { 0, 5, 0, 0, 0, 0, 0, 3, 0 }, {
 0, 0, 0, 9, 0, 8, 2, 0, 6 }, { 0, 2, 0, 7, 5, 0, 0, 0, 0 },
 { 0, 0, 0, 0, 0, 3, 1, 0, 0 } };

 int count = 0;
 ASSERT_FALSE(sudoku_esTableroTotalmenteResuelto(t));
 ASSERT_TRUE(sudoku_resolver(t));
 ASSERT_TRUE(sudoku_esTableroTotalmenteResuelto(t));
 ASSERT_GT(count, 0);

 }
 TEST(sudoku_resolverTest, tableroDificil5) {
 Tablero t = { { 0, 4, 7, 0, 8, 0, 0, 0, 1 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
 { 0, 0, 0, 6, 0, 0, 7, 0, 0 }, { 6, 0, 0, 0, 0, 3, 5, 7, 0 }, { 0,
 0, 0, 0, 0, 5, 0, 0, 0 }, { 0, 1, 0, 0, 6, 0, 0, 0, 0 }, {
 2, 8, 0, 0, 4, 0, 0, 0, 0 }, { 0, 9, 0, 1, 0, 0, 0, 4, 0 },
 { 0, 0, 0, 0, 2, 0, 6, 9, 0 } };

 int count = 0;
 ASSERT_FALSE(sudoku_esTableroTotalmenteResuelto(t));
 ASSERT_TRUE(sudoku_resolver(t));
 ASSERT_TRUE(sudoku_esTableroTotalmenteResuelto(t));
 ASSERT_GT(count, 0);

 }

 TEST(sudoku_resolverTest, tableroDificil6) {
 Tablero t = { { 0, 0, 0, 8, 0, 0, 0, 0, 9 }, { 0, 8, 7, 3, 0, 0, 0, 4, 0 },
 { 6, 0, 0, 7, 0, 0, 0, 0, 0 }, { 0, 0, 8, 5, 0, 0, 9, 7, 0 }, { 0,
 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 4, 3, 0, 0, 7, 5, 0, 0 }, {
 0, 0, 0, 0, 0, 3, 0, 0, 0 }, { 0, 3, 0, 0, 0, 1, 4, 5, 0 },
 { 4, 0, 0, 0, 0, 2, 0, 0, 1 } };

 int count = 0;
 ASSERT_FALSE(sudoku_esTableroTotalmenteResuelto(t));
 ASSERT_TRUE(sudoku_resolver(t));
 ASSERT_TRUE(sudoku_esTableroTotalmenteResuelto(t));
 ASSERT_GT(count, 0);

 }

 TEST(sudoku_resolverTest, tableroDificil7) {
 Tablero t = { { 0, 0, 0, 0, 0, 0, 8, 0, 1 }, { 7, 0, 0, 2, 0, 0, 0, 0, 0 },
 { 0, 0, 0, 5, 0, 6, 0, 0, 0 }, { 0, 0, 0, 7, 0, 0, 0, 5, 0 }, { 0,
 1, 0, 0, 0, 0, 3, 0, 0 }, { 0, 8, 0, 0, 0, 0, 0, 0, 0 }, {
 5, 0, 0, 0, 0, 0, 0, 2, 0 }, { 0, 4, 0, 0, 8, 0, 0, 0, 0 },
 { 6, 0, 0, 0, 3, 0, 0, 0, 0 } };

 int count = 0;
 ASSERT_FALSE(sudoku_esTableroTotalmenteResuelto(t));
 ASSERT_TRUE(sudoku_resolver(t));
 ASSERT_TRUE(sudoku_esTableroTotalmenteResuelto(t));
 ASSERT_GT(count, 0);

 }*/

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

#ifndef FIGURA_H
#define FIGURA_H
#include "InfoJoc.h"
//Tauler
const int MAX_COL = 11;
const int MAX_FILES = 21;

//Figura
const int MAX_FILA = 8;
const int MAX_COLUMNA = 8;
const int MAX_GIR = 3;

class Figura
{

public:

	Figura() { m_tipus = NO_FIGURA; m_color = NO_COLOR; m_posicioFila = 0; m_posicioColumna = 0;  m_gir = 0; m_files = 0; m_columnes = 0; }
	void inicialitzaFigura(const TipusFigura& forma, int gir, int fila, int columna);

	void setTipus(const TipusFigura& tipus) { m_tipus = tipus; }
	TipusFigura getTipus() const { return m_tipus; }
	ColorFigura getColor() const { return m_color; }
	void setPosicioFila(const int fila) { m_posicioFila = fila; }
	int getPosicioFila() const { return m_posicioFila; }
	void setPosocioColumna(const int columna) { m_posicioColumna = columna; }
	int getPosicioColumna() const { return m_posicioColumna; }
	int getGir() const { return m_gir; }
	int getFiles() const { return m_files; }
	int getColumnes() const { return m_columnes; }
	void getFormaActual(int figuraJoc[MAX_FILA][MAX_COLUMNA]) const;
	

	void girHorari(); //Modifica m_forma i m_gir++
	void girAntiHorari(); //Modifica m_forma i m_gir--
	void desplacament(int dirX) { m_posicioColumna += dirX; }
	void baixa() { m_posicioFila++; }
	void puja() { m_posicioFila--; }

	void dibuixaFigura(int x, int y, int n, int s);


private:
	TipusFigura m_tipus;
	ColorFigura m_color;
	int m_posicioFila;
	int m_posicioColumna;
	int m_gir;
	int m_files;
	int m_columnes;
	int m_formaActual[MAX_FILA][MAX_COLUMNA];
	
	void novaForma();

};

#endif
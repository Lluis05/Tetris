#ifndef JOC_H
#define JOC_H
#include "Tauler.h"
#include "Figura.h"
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

typedef enum
{
	GIR_HORARI = 0,
	GIR_ANTI_HORARI
} DireccioGir;

class Joc
{
public:
	Joc() {}
	void inicialitza(const string& nomFitxer);
	bool giraFigura(DireccioGir direccio);
	bool mouFigura(int dirX);
	int baixaFigura();
	void escriuTauler(const string& nomFitxer);
	int baixaInstantani();
	bool novaFiguraAleatori();
	void novaFigura(InfoFigura figura);
	void actualitzaSombra();
	void dibuixaSombra();
	void dibuixaJoc();


private:
    Tauler m_tauler;
    Figura m_figura;
	Figura m_sombra;
	Figura m_figuraSeguent[MAX_FIGURES_SEGUENTS];
};

#endif
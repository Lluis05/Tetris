#ifndef TAULER_H
#define TAULER_H
#include "Figura.h"

class Tauler
{
public:
    Tauler();
    void inicialitza(ColorFigura tauler[MAX_FILES][MAX_COL]);
    void getTauler(ColorFigura tauler[MAX_FILES][MAX_COL]);
    void posaFigura(const Figura& figura);
    int colocaFigura(const Figura& figura);
    bool colisioFigura(const Figura& figura); 
    int getFilesOcupades(int i);
    void dibuixaTauler();
    
private:
    ColorFigura m_tauler[MAX_FILES + 1][MAX_COL + 2];
    int m_ocupades[MAX_FILES];
    void baixarFila(int fila); //baixar fila i omplir amb NO_COLOR les de dalt
};

#endif
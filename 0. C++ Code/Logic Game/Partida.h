#ifndef PARTIDA_H
#define PARTIDA_H

#include<list>
#include "Joc.h"
#include <stdio.h>
#include <string>
#include "InfoJoc.h"
#include "LlistaFigura.h"
#include "LlistaMoviment.h"
#include <ctime>

using namespace std;

const int DRETA = 1;
const int ESQUERRA = -1;
const int PUNTS_FILES[5] = {10,100,150,175,200};
const int CANVI_NIVELL = 500;
const double VEL_INICIAL = 1.0;
const double INCREMENT_VEL = 0.75;

typedef enum
{
    MODE_NORMAL = 0,
    MODE_TEST
} ModeJoc; 


class Partida 
{
public:    
    Partida() { m_mode = MODE_NORMAL; m_temps = 0.0; m_puntuacio = 0; m_nivellActual = 1; m_velocitat = VEL_INICIAL; m_acabaJoc = false; m_contador = 0; srand(time(0)); m_joc.novaFiguraAleatori(); }
    Partida(ModeJoc mode);
    void inicialitza(const ModeJoc mode, const string& fitxerInicial , const string& fitxerFigures, const string& fitxerMoviments);
    void actualitza(double deltaTime);
    ModeJoc getMode() const { return m_mode; }
    int getPuntuacio() const { return m_puntuacio; }

private:
    double m_temps;
    Joc m_joc;
    int m_puntuacio;
    int m_nivellActual;
    ModeJoc m_mode;
    double m_velocitat;
    bool m_acabaJoc;
    int m_contador;

    LlistaFigura m_figures;
    LlistaMoviment m_moviments;

    void actualitzaNormal(double deltaTime);
    void actualitzaTest(double deltTime);
    void actualitzaPuntuacio(int nFiles);
    void inicialitzaFigures(const string& nomFitxer);
    void inicialitzaMoviments(const string& nomFitxer);
    void mostraPuntuacioASuperar();

    int m_pASuperar;
    string m_nomJugador;
    list<int> m_puntuacions;

};

#endif 

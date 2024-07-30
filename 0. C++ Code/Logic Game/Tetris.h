#ifndef TETRIS
#define TETRIS
#include "Partida.h"
#include <list>
using namespace std;

typedef struct
{
    int puntuacio;
    string jugador;
} Puntuacio;


class Tetris
{
public:
    void carregaPuntuacions(const string& nomFitxer);
    int juga(Screen& pantalla, ModeJoc mode, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments);
    void mostraPuntuacions(const string& nomFitxer);
    void actualitzaPuntuacions(const string& nomJugador, int puntuacio);
    void guardaPuntuacions(const string& nomFitxer);

private:
    Partida m_partida;
    list<Puntuacio> m_puntuacio;

};
#endif
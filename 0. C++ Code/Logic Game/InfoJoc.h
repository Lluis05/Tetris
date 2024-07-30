#ifndef INFO_JOC_H
#define INFO_JOC_H
#include "GraphicManager.h"

typedef enum
{
    TECLA_ESQUERRA,
    TECLA_DRETA,
    TECLA_AMUNT,
    TECLA_ABAIX,
    TECLA_ESPAI,
    TECLA_ESCAPE,
    NO_TECLA
} TipusTecla;

const int N_TIPUS_FIGURES = 7;

typedef enum
{
    COLOR_NEGRE = 0,
    COLOR_GROC,
    COLOR_BLAUCEL,
    COLOR_MAGENTA,
    COLOR_TARONJA,
    COLOR_BLAUFOSC,
    COLOR_VERMELL,
    COLOR_VERD,
    NO_COLOR
} ColorFigura;

typedef enum
{
    NO_FIGURA = 0,
    FIGURA_O,
    FIGURA_I,
    FIGURA_T,
    FIGURA_L,
    FIGURA_J,
    FIGURA_Z,
    FIGURA_S
} TipusFigura;

// Tamany de la pantalla gràfica
const int SCREEN_SIZE_X = 800;
const int SCREEN_SIZE_Y = 700;

// Mida dels quadrats que formen el tauler
const int MIDA_QUADRAT = 26;

// Tamany del tauler
const int N_FILES_TAULER = 21;
const int N_COL_TAULER = 11;

// Posició del tauler a la pantalla
const int POS_X_TAULER = 400;
const int POS_Y_TAULER = 75;

//Posicio del missatge de puntuacio a la pantalla
const int POS_X_PUNTUACIO = 100;
const int POS_Y_PUNTUACIO = 50;

//Posicio del missatge de nivell a la pantalla
const int POS_X_NIVELL = 130;
const int POS_Y_NIVELL = 90;

//Posicio del missatge de canvis 
const int POS_X_CANVIS = 50;
const int POS_Y_CANVIS = 150;

//Posicio del missatge final
const int POS_X_FINAL = 425;
const int POS_Y_FINAL = 200;

// Posicio del missatge de puntuacio a superar a la pantalla
const int POS_X_PUNTUACIOASUPERAR = 420;
const int POS_Y_PUNTUACIOASUPERAR = 25;

//Posicio del missatge figura seguent
const int POS_X_MISSATGE_FIGURA_SEGUENT = 80;
const int POS_Y_MISSATGE_FIGURA_SEGUENT = 220;

const int MAX_FIGURES_SEGUENTS = 3;

//Posicio del figura seguent
const int POS_X_FIGURA_SEGUENT = 150;
const int POS_Y_FIGURA_SEGUENT = 330;

typedef struct
{
    TipusFigura tipus;
    int gir;
    int fila;
    int columna;
} InfoFigura;

typedef enum
{
    MOVIMENT_ESQUERRA = 0,
    MOVIMENT_DRETA = 1,
    MOVIMENT_GIR_HORARI = 2,
    MOVIMENT_GIR_ANTI_HORARI = 3,
    MOVIMENT_BAIXA = 4,
    MOVIMENT_BAIXA_FINAL = 5,
} TipusMoviment;

#endif

//
//  main.cpp
//
//  Copyright � 2018 Compiled Creations Limited. All rights reserved.
//

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined  (_WIN64)

#include <iostream>
#include <cstdlib>
//Definicio necesaria per poder incloure la llibreria i que trobi el main
#define SDL_MAIN_HANDLED
#include <windows.h>
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#include <conio.h>      /* getch */ 

#elif __APPLE__
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <SDL2/SDL.h>
#pragma clang diagnostic pop

#endif
//incloure musica
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#include "./Partida.h"
#include "./InfoJoc.h"
#include "Tetris.h"

void Menu()
{
    cout << endl;
    cout << "Copyright \u00A9 2024 Marti Bertrans & Lluis Sarries" << endl;
    cout << endl;
    cout << "==================================================================" << endl;
    cout << "_|_|_|_|_| _|_|_|_|  _|_|_|_|_|  _|_|_|    _|_|_|_|_|   _|_|_|_|  " << endl;
    cout << "    _|     _|           _|       _|    _|      _|       _|        " << endl;
    cout << "    _|     _|_|_|       _|       _|_|_|        _|       _|_|_|    " << endl;
    cout << "    _|     _|           _|       _|    _|      _|             _|  " << endl;
    cout << "    _|     _|_|_|_|     _|       _|    _|  _|_|_|_|_|   _|_|_|    " << endl;
    cout << "==================================================================" << endl;
    cout << endl;
    cout << "1. Jugar en mode normal" << endl;
    cout << "2. Jugar en mode test" << endl;
    cout << "3. Llistat de puntuacions" << endl;
    cout << "4. Sortir" << endl;
    cout << endl;
}

int main(int argc, const char* argv[])
{
    //Instruccions necesaries per poder incloure la llibreria i que trobi el main
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);


    Tetris tetris;
    tetris.carregaPuntuacions("./data/Games/puntuacions.txt");
    Partida joc;
    //Inicialitza un objecte de la classe Screen que s'utilitza per gestionar la finestra grafica
    Screen pantalla(SCREEN_SIZE_X, SCREEN_SIZE_Y);


    bool sortir = false;
    char op;
 
    int punts;

    do
    {
        string nomJugador, partida, figures, moviments;
        Menu();
        op = _getch();

        switch (op)
        {
        case '1':
            PlaySound(TEXT("./data/Audio/pokemon.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
            punts = tetris.juga(pantalla, MODE_NORMAL, "", "", "");
            PlaySound(0, 0, 0);
            Sleep(500);
            cout << "Introdueix el teu nom: ";
            cin >> nomJugador;
            tetris.actualitzaPuntuacions(nomJugador, punts);
            system("CLS");
            break;
        case '2':
            cout << "Fitxer estat inicial tauler: ";
            cin >> partida;
            partida = "./data/Games/" + partida;
            cout << "Fitxer sequencia figures: ";
            cin >> figures;
            figures = "./data/Games/" + figures;
            cout << "Fitxer sequencia moviments: ";
            cin >> moviments;
            moviments = "./data/Games/" + moviments;
            punts = tetris.juga(pantalla, MODE_TEST, partida, figures, moviments);
            system("CLS");
            break;
        case '3':
            tetris.mostraPuntuacions("./data/Games/puntuacions.txt");
            break;
        case '4':
            sortir = true;
            break;
        default:
            cout << "Opcio incorrecta. Escull una opcio entre el numero 1 i el 4." << endl;
            cout << endl;
            break;
        }
    } while (!sortir);
    tetris.guardaPuntuacions("./data/Games/puntuacions.txt");

    //Instruccio necesaria per alliberar els recursos de la llibreria
    SDL_Quit();
    return 0;
}

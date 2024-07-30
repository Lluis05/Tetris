#include "Tetris.h"
#include <fstream>
#include <iostream>
#include "GraphicManager.h"
#include <cstdlib>
using namespace std;

int Tetris::juga(Screen& pantalla, ModeJoc mode, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments)
{
	pantalla.show();

	Partida p(mode);
	p.inicialitza(mode, fitxerInicial, fitxerFigures, fitxerMoviments);

	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;

	do
	{
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();
		deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());
		// Captura tots els events de ratolí i teclat de l'ultim cicle
		pantalla.processEvents();

		p.actualitza(deltaTime);

		// Actualitza la pantalla
		pantalla.update();

	} while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE));
	int punts = p.getPuntuacio();

	return punts;
}

void Tetris::carregaPuntuacions(const string& nomFitxer)
{
	ifstream fitxer;
	fitxer.open(nomFitxer);
	if (fitxer.is_open())
	{
		Puntuacio p;
		fitxer >> p.jugador >> p.puntuacio;
		while (!fitxer.eof())
		{
			m_puntuacio.push_back(p);
			fitxer >> p.jugador >> p.puntuacio;
		}
		fitxer.close();
	}
}
void Tetris::mostraPuntuacions(const string& nomFitxer)
{
	list<Puntuacio>::iterator actual = m_puntuacio.begin();
	int posicio = 1;

	system("CLS");

	cout << endl;
	cout << "============================" << endl;
	cout << "	PUNTUACIONS" << endl;
	cout << "============================" << endl;
	while (actual != m_puntuacio.end())
	{
		cout << posicio << ". " << actual->jugador << " => " << actual->puntuacio << endl;
		posicio++;
		actual++;
	}


}

void Tetris::actualitzaPuntuacions(const string& nomJugador, int puntuacio)
{
	list<Puntuacio>::iterator actual = m_puntuacio.begin();
	bool trobat = false;
	int contador = 0;
	while (!trobat && (actual != m_puntuacio.end()))
	{
		if (actual->puntuacio < puntuacio)
			trobat = true;
		else
		{
			actual++;
			contador++;
		}
	}

	if (contador < 10)
	{
		Puntuacio p;
		p.jugador = nomJugador;
		p.puntuacio = puntuacio;
		m_puntuacio.insert(actual, p);

		if (m_puntuacio.size() > 10)
			m_puntuacio.pop_back();
	}
}

void Tetris::guardaPuntuacions(const string& nomFitxer)
{
	list<Puntuacio>::iterator actual = m_puntuacio.begin();
	ofstream fitxer;
	fitxer.open(nomFitxer);
	if (fitxer.is_open())
	{
		while (actual != m_puntuacio.end())
		{
			fitxer << actual->jugador << " " << actual->puntuacio << endl;
			actual++;
		}
	}

	fitxer.close();
}
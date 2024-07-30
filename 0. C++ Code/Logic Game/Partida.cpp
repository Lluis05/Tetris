#include "Partida.h"
#include "InfoJoc.h"
#include "GraphicManager.h"
#include <fstream>
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

Partida::Partida(ModeJoc mode)
{
    m_mode = mode;
    m_temps = 0.0; 
    m_puntuacio = 0; 
    m_nivellActual = 1; 
    m_velocitat = VEL_INICIAL; 
    m_acabaJoc = false; 
    m_contador = 0;
    srand(time(0));
    if (mode == MODE_NORMAL)
        m_joc.novaFiguraAleatori();
}
void Partida::inicialitza(ModeJoc mode, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments)
{

    if (mode == MODE_NORMAL)
    {
        m_acabaJoc = m_joc.novaFiguraAleatori();
    }
    else
    {
        m_joc.inicialitza(fitxerInicial);
        inicialitzaFigures(fitxerFigures);
        inicialitzaMoviments(fitxerMoviments);
    }
}

void Partida::inicialitzaFigures(const string& nomFitxer)
{
    ifstream fitxer;
    fitxer.open(nomFitxer);
    if (fitxer.is_open())
    {
        InfoFigura figura;
        int tipus;
        fitxer >> tipus >> figura.fila >> figura.columna >> figura.gir;
        figura.tipus = TipusFigura(tipus);
        while (!fitxer.eof())
        {
            m_figures.afegeix(figura);
            fitxer >> tipus >> figura.fila >> figura.columna >> figura.gir;
            figura.tipus = TipusFigura(tipus);
        }
        fitxer.close();
    }
}

void Partida::inicialitzaMoviments(const string& nomFitxer)
{
    ifstream fitxer;
    fitxer.open(nomFitxer);
    if (fitxer.is_open())
    {
        int tipus;
        fitxer >> tipus;
        while (!fitxer.eof())
        {
            m_moviments.afegeix(TipusMoviment(tipus));
            fitxer >> tipus;
        }
        fitxer.close();
    }
}

void Partida::mostraPuntuacioASuperar()
{
    ifstream fitxer;
    fitxer.open("./data/Games/puntuacions.txt");
    Partida partida;
    if (fitxer.is_open())
    {
        fitxer >> m_nomJugador >> m_pASuperar;
        while (!fitxer.eof())
        {
            m_puntuacions.push_back(m_pASuperar);
            fitxer >> m_nomJugador >> m_pASuperar;
        }
    }
    fitxer.close();

    list<int>::reverse_iterator it = m_puntuacions.rbegin();
    while (it != m_puntuacions.rend() && *it <= m_puntuacio)
    {
        it++;
    }
    if (it != m_puntuacions.rend())
        m_pASuperar = *it;
    else
        m_pASuperar = m_puntuacio;
}

void Partida::actualitza(double deltaTime)
{
    if (!m_acabaJoc)
    {
        if (m_mode == MODE_NORMAL)
            actualitzaNormal(deltaTime);
        else
            actualitzaTest(deltaTime);
    }

    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 400, 0, false);
	m_joc.dibuixaJoc();
    if (m_mode == MODE_NORMAL)
    {
        string msgFiguraSeguent = "Figures Seguents: ";
        string msgPuntuacioASuperar = "Puntuacio a superar: " + to_string(m_pASuperar);
        string msgCanvis = "Canvis realitzats: " + to_string(m_contador) + "/3";
        GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT, POS_X_MISSATGE_FIGURA_SEGUENT + 25, POS_Y_MISSATGE_FIGURA_SEGUENT + 45, false);
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_CANVIS, POS_Y_CANVIS, 0.7, msgCanvis);
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_MISSATGE_FIGURA_SEGUENT, POS_Y_MISSATGE_FIGURA_SEGUENT, 0.7, msgFiguraSeguent);
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_PUNTUACIOASUPERAR, POS_Y_PUNTUACIOASUPERAR, 0.7, msgPuntuacioASuperar);

        m_joc.dibuixaSombra();
    }
    string msgPuntuacio = "Puntuacio: " + to_string(m_puntuacio);
    string msgNivellActual = "Nivell: " + to_string(m_nivellActual);
   
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_NIVELL, POS_Y_NIVELL, 0.7, msgNivellActual);
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_PUNTUACIO, POS_Y_PUNTUACIO, 0.7, msgPuntuacio);
    
    
    if (m_acabaJoc)
    {
        GraphicManager::getInstance()->drawSprite(GRAFIC_GAME_OVER, POS_X_FINAL, POS_Y_FINAL, false);
        PlaySound(0, 0, 0);
    }

}


void Partida::actualitzaNormal(double deltaTime)
{
    mostraPuntuacioASuperar();
    int nFiles;

    if (Keyboard_GetKeyTrg(KEYBOARD_RIGHT))
        m_joc.mouFigura(DRETA);

    if (Keyboard_GetKeyTrg(KEYBOARD_LEFT))
        m_joc.mouFigura(ESQUERRA);

    if (Keyboard_GetKeyTrg(KEYBOARD_UP))
        m_joc.giraFigura(GIR_HORARI);

    if (Keyboard_GetKeyTrg(KEYBOARD_DOWN))
        m_joc.giraFigura(GIR_ANTI_HORARI);

    if (Keyboard_GetKeyTrg(KEYBOARD_C))
    {
        nFiles = m_joc.baixaFigura();
        if (nFiles != -1)
        {
            actualitzaPuntuacio(nFiles);
            mostraPuntuacioASuperar();
            m_acabaJoc = m_joc.novaFiguraAleatori();
        }
        m_temps = 0.0;
    }

    //canviar de figura X cops
    if (m_contador < 3)
    {
        if (Keyboard_GetKeyTrg(KEYBOARD_X))
        {
            m_contador++;
            m_acabaJoc = m_joc.novaFiguraAleatori();
            m_joc.actualitzaSombra();
            m_temps = 0.0;
        }
    }
    

    if (Keyboard_GetKeyTrg(KEYBOARD_SPACE))
    {
        nFiles = m_joc.baixaInstantani();
        if (nFiles != -1)
        {
            actualitzaPuntuacio(nFiles);
            mostraPuntuacioASuperar(); 
        }
        m_acabaJoc = m_joc.novaFiguraAleatori();
        m_temps = 0.0;
    }

    else
    {
        m_joc.actualitzaSombra();
        m_temps += deltaTime;
        if (m_temps > m_velocitat)
        {
            nFiles = m_joc.baixaFigura();
            if (nFiles != -1) //La figura a col·lisionat
            {
                actualitzaPuntuacio(nFiles);
                mostraPuntuacioASuperar();
                m_acabaJoc = m_joc.novaFiguraAleatori();
            }
            m_temps = 0.0;
        }
    }
}

void Partida::actualitzaTest(double deltaTime)
{
    m_temps += deltaTime;
    if (m_temps > m_velocitat)
    {
        m_temps = 0.0;
        TipusMoviment moviment;
        if (m_moviments.esBuida())
        {
            m_acabaJoc = true;
        }
        else
        {
            moviment = m_moviments.getPrimer();
            m_moviments.borrar();
            int nFiles;
            switch (moviment)
            {
            case MOVIMENT_DRETA:
                m_joc.mouFigura(DRETA);
                break;
            case MOVIMENT_ESQUERRA:
                m_joc.mouFigura(ESQUERRA);
                break;
            case MOVIMENT_GIR_HORARI:
                m_joc.giraFigura(GIR_HORARI);
                break;
            case MOVIMENT_GIR_ANTI_HORARI:
                m_joc.giraFigura(GIR_ANTI_HORARI);
                break;
            case MOVIMENT_BAIXA_FINAL:
                nFiles = m_joc.baixaInstantani ();
                actualitzaPuntuacio(nFiles);
                if (!m_figures.esBuida())
                {
                    InfoFigura figura = m_figures.getPrimer();
                    m_figures.borrar();
                    m_joc.novaFigura(figura);
                }
                else
                    m_acabaJoc = true;
                break;
            case MOVIMENT_BAIXA:
                nFiles = m_joc.baixaFigura();
                if (nFiles != -1)
                {
                    actualitzaPuntuacio(nFiles);
                    if (!m_figures.esBuida())
                    {
                        InfoFigura figura = m_figures.getPrimer();
                        m_figures.borrar();
                        m_joc.novaFigura(figura);
                    }
                    else
                        m_acabaJoc = true;
                }
                break;
            }
        }

    }
}

void Partida::actualitzaPuntuacio(int nFiles)
{
    m_puntuacio += PUNTS_FILES[nFiles];

    if (m_puntuacio > (m_nivellActual * CANVI_NIVELL))
    {
        m_nivellActual += 1;
        m_velocitat *= INCREMENT_VEL;
    }
    if (nFiles == 4 && m_contador >= 0)
    {
        m_contador--;
    }
    	
}

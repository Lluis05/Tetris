#include "Tauler.h"
#include <iostream>
using namespace std;

int Tauler::getFilesOcupades(int i)
{
    return m_ocupades[i];
}

Tauler::Tauler()
{
    
    for(int i = 0; i < MAX_FILES + 1; i++)
    {
        for (int j = 0; j < MAX_COL + 2; j++)
        {
            m_tauler[i][j] = COLOR_NEGRE;
        }
        m_tauler[i][0] = NO_COLOR;
        m_tauler[i][MAX_COL + 1] = NO_COLOR;
    }
    for (int i = 0; i < MAX_COL + 2; i++) //Fer una fila NO_COLOR per sota per detectar borde
    {
        m_tauler[MAX_FILES][i] = NO_COLOR;
    }
    

    for (int i = 0; i < MAX_FILES; i++)
        m_ocupades[i] = 0;
}

void Tauler::inicialitza(ColorFigura tauler[MAX_FILES][MAX_COL])
{
    for (int i = 0; i < MAX_FILES; i++)
        m_ocupades[i] = 0;
    for(int i = 0; i < MAX_FILES; i++)
        for(int j = 0; j < MAX_COL; j++)
        {
            m_tauler[i][j + 1] = tauler[i][j];
            if (tauler[i][j] != COLOR_NEGRE)
                m_ocupades[i]++;
        }
}

void Tauler::baixarFila(int fila)
{
    if (fila > 0) //comprova que sigui major que 0 pq sino acaba el joc
    {
        for (int i = fila; i > 0; i--)
        {
            for (int j = 0; j < MAX_COL; j++)
            {
                m_tauler[i][j + 1] = m_tauler[i - 1][j + 1];
            }
            m_ocupades[i] = m_ocupades[i - 1];
        }
    }
    for (int j = 0; j < MAX_COL; j++)
        m_tauler[0][j + 1] = COLOR_NEGRE;
    m_ocupades[0] = 0;
}

void Tauler::posaFigura(const Figura& figura)
{
    int figuraJoc[MAX_FILA][MAX_COLUMNA];

    ColorFigura color = figura.getColor();
    figura.getFormaActual(figuraJoc);

    int fila = figura.getPosicioFila() - 1;
    for (int i = 0; i < figura.getFiles(); i++)
    {
        int col = figura.getPosicioColumna();
        for (int j = 0; j < figura.getColumnes(); j++)
        {
            if ((figuraJoc[i][j] > 0))
            {
                m_tauler[fila][col] = color;
            } 
            col++;
        }
        fila++;     
    }                   
}

int Tauler::colocaFigura(const Figura& figura)
{
    int figuraJoc[MAX_FILA][MAX_COLUMNA];
    int numFiles = 0;

    ColorFigura color = figura.getColor();
    figura.getFormaActual(figuraJoc);
    int fila = figura.getPosicioFila() - 1;
    for (int i = 0; i < figura.getFiles(); i++)
    {
        int col = figura.getPosicioColumna();
        for (int j = 0; j < figura.getColumnes(); j++)
        {
            if (figuraJoc[i][j] > 0)
            {
                m_tauler[fila][col] = color;
                m_ocupades[fila]++;
                if (m_ocupades[fila] == MAX_COL)
                {
                    numFiles++;
                    baixarFila(fila);
                }
            }
            col++;
        }
        fila++;
    }
    return numFiles;
}


bool Tauler::colisioFigura(const Figura& figura)
{
    bool colisio = false;
    int figuraJoc[MAX_FILA][MAX_COLUMNA];
    figura.getFormaActual(figuraJoc);
    int fila = figura.getPosicioFila() - 1;
    int i = 0;
    while ((!colisio) && (i < figura.getFiles()))
    {
        int j = 0;
        int col = figura.getPosicioColumna();
        while ((!colisio) && (j < figura.getColumnes()))
        {
            if (figuraJoc[i][j] * m_tauler[fila][col] != 0)
            {
                colisio = true;
            }
            j++;
            col++;
            
        }
        i++;
        fila++;
    }
    return colisio;
}
void Tauler::getTauler(ColorFigura tauler[MAX_FILES][MAX_COL])
{
    for(int i = 0; i < MAX_FILES; i++)
        for(int j = 0; j < MAX_COL; j++)
            tauler[i][j] = m_tauler[i][j + 1];
}

void Tauler::dibuixaTauler()
{
    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER, false);

    for (int i = 0; i < MAX_FILES; i++)
    {
        for (int j = 0; j < MAX_COL; j++)
        {
            if (m_tauler[i][j + 1] != 0)
            {
                switch (m_tauler[i][j+1])
                {
                case COLOR_GROC:
                    GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_GROC, POS_X_TAULER + ((j + 1) * MIDA_QUADRAT), POS_Y_TAULER + (i * MIDA_QUADRAT), false);
                    break;
                case COLOR_BLAUCEL:
                    GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_BLAUCEL, POS_X_TAULER + ((j + 1) * MIDA_QUADRAT), POS_Y_TAULER + (i * MIDA_QUADRAT), false);
                    break;
                case COLOR_MAGENTA:
                    GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_MAGENTA, POS_X_TAULER + ((j + 1) * MIDA_QUADRAT), POS_Y_TAULER + (i * MIDA_QUADRAT), false);
                    break;
                case COLOR_TARONJA:
                    GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_TARONJA, POS_X_TAULER + ((j + 1) * MIDA_QUADRAT), POS_Y_TAULER + (i * MIDA_QUADRAT), false);
                    break;
                case COLOR_BLAUFOSC:
                    GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_BLAUFOSC, POS_X_TAULER + ((j + 1) * MIDA_QUADRAT), POS_Y_TAULER + (i * MIDA_QUADRAT), false);
                    break;
                case COLOR_VERMELL:
                    GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_VERMELL, POS_X_TAULER + ((j + 1) * MIDA_QUADRAT), POS_Y_TAULER + (i * MIDA_QUADRAT), false);
                    break;
                case COLOR_VERD:
                    GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_VERD, POS_X_TAULER + ((j + 1) * MIDA_QUADRAT), POS_Y_TAULER + (i * MIDA_QUADRAT), false);
                    break;
                }
            }
        }
    }
}
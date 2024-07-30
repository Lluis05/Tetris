#include "Joc.h"
#include <fstream>
#include <iostream>
#include "Partida.h"
using namespace std;

void Joc::inicialitza(const string& nomFitxer)
{
    ifstream fitxer;
    fitxer.open(nomFitxer);
    if (fitxer.is_open())
    {

        int tipus, fila, columna, gir;
        fitxer >> tipus >> fila >> columna >> gir;
        m_figura.inicialitzaFigura(TipusFigura(tipus), gir, fila, columna);

        int color;
        ColorFigura tauler[MAX_FILES][MAX_COL];
        
        for(int i = 0; i < MAX_FILES; i++)
        {
            for(int j = 0; j < MAX_COL; j++)
            {
                fitxer >> color;
                tauler[i][j] = ColorFigura(color);
            }

        }
        m_tauler.inicialitza(tauler);
        fitxer.close();
    }  
}


bool Joc::giraFigura(DireccioGir direccio)
{
    bool girafigura = true;

    switch (direccio)
    {
        case GIR_HORARI:
            m_figura.girHorari();
            if (m_tauler.colisioFigura(m_figura))
            {
                girafigura = false;
                m_figura.girAntiHorari();
            }
            break;

        case GIR_ANTI_HORARI:
            m_figura.girAntiHorari();
            if (m_tauler.colisioFigura(m_figura))
            {
                girafigura = false;
                m_figura.girHorari();
            }
            break;
    }

    actualitzaSombra();

    return girafigura;
}

bool Joc::mouFigura(int dirX)
{
    m_figura.desplacament(dirX);
    bool mouFigura = m_tauler.colisioFigura(m_figura);
    if (mouFigura)
    {
        m_figura.desplacament(-dirX);
    }

    actualitzaSombra();

    return !mouFigura;
}

int Joc::baixaFigura()
{
    int nFiles = -1;
    actualitzaSombra();
    m_figura.baixa();
    if (m_tauler.colisioFigura(m_figura))
    {
        m_figura.puja();
        nFiles = 0;
        nFiles = m_tauler.colocaFigura(m_figura);
    }

    

    return nFiles;

}

bool Joc::novaFiguraAleatori()
{
    srand(rand() ^ time(NULL));
    TipusFigura tipus;
    m_figura.inicialitzaFigura(m_figuraSeguent[0].getTipus(), 0, 1, 5);

    for (int i = 0; i < MAX_FIGURES_SEGUENTS; i++)
    {
        if (m_figuraSeguent[i].getTipus() == NO_FIGURA)
        {
            tipus = TipusFigura((rand() % N_TIPUS_FIGURES) + 1);
            m_figuraSeguent[i].inicialitzaFigura(tipus, 0, 0, 0);
        }
        else
            m_figuraSeguent[i].inicialitzaFigura(m_figuraSeguent[i + 1].getTipus(), 0, 0, 0);
    }

    tipus = TipusFigura((rand() % N_TIPUS_FIGURES) + 1);
    m_figuraSeguent[MAX_FIGURES_SEGUENTS - 1].inicialitzaFigura(tipus, 0, 0, 0);

    bool colisiona = m_tauler.colisioFigura(m_figura);
    return colisiona;
}

void Joc::novaFigura(InfoFigura figura)
{
    m_figura.inicialitzaFigura(figura.tipus, figura.gir, figura.fila, figura.columna);
}


void Joc::escriuTauler(const string& nomFitxer)
{
    ofstream fitxer;
    fitxer.open(nomFitxer);

    if(fitxer.is_open())
    {
        if (m_figura.getTipus() != NO_FIGURA)
            m_tauler.posaFigura(m_figura);
            
        ColorFigura tauler[MAX_FILES][MAX_COL];
        m_tauler.getTauler(tauler);
        
        for (int i = 0; i < MAX_FILES; i++)
        {
            for (int j = 0; j < MAX_COL; j++)
            {
                fitxer << int(tauler[i][j]) << " ";
            }
        }
        fitxer.close();
    }
}

int Joc::baixaInstantani()
{
    int nFiles;
    do
    {
        nFiles = baixaFigura();
    } while (nFiles == -1);
    return nFiles;
}

void Joc::actualitzaSombra()
{
    m_sombra = m_figura;
    bool colisiona = m_tauler.colisioFigura(m_sombra);
    while (!colisiona)
    {
        m_sombra.baixa();
        colisiona = m_tauler.colisioFigura(m_sombra);
    }
    m_sombra.puja();
}

void Joc::dibuixaSombra()
{
    m_sombra.dibuixaFigura(POS_X_TAULER, POS_Y_TAULER, 0, 1);
    m_figura.dibuixaFigura(POS_X_TAULER, POS_Y_TAULER, 0, 0);
}

void Joc::dibuixaJoc()
{
    Partida p;
    m_tauler.dibuixaTauler();
    m_figura.dibuixaFigura(POS_X_TAULER, POS_Y_TAULER, 0, 0);

    for (int i = 0; i < MAX_FIGURES_SEGUENTS; i++)
        m_figuraSeguent[i].dibuixaFigura(POS_X_FIGURA_SEGUENT, POS_Y_FIGURA_SEGUENT, i, 0);
}

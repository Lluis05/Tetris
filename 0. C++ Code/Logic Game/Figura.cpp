#include "Figura.h"

void Figura::getFormaActual(int figuraJoc[MAX_FILA][MAX_COLUMNA]) const
{
	for (int i = 0; i < m_files; i++)
            for (int j = 0; j < m_columnes; j++)
				figuraJoc[i][j] = m_formaActual[i][j];
}

void Figura::novaForma()
{
	for (int i = 0; i < m_files; i++)
		for (int j = 0; j < m_columnes; j++)
			m_formaActual[i][j] = 0;
}

void Figura::inicialitzaFigura(const TipusFigura& tipus, int gir, int fila, int columna)
{
	m_tipus = tipus;
	m_posicioFila = fila;
	m_posicioColumna = columna;
	m_gir = gir;

	switch (m_tipus)
	{
	case FIGURA_O:
		m_files = 2;
		m_columnes = 2;
		novaForma();
		m_formaActual[0][0] = 1;
		m_formaActual[0][1] = 1;
		m_formaActual[1][0] = 1;
		m_formaActual[1][1] = 1;
		m_color = COLOR_GROC;
		break;
	case FIGURA_I:
		m_files = 4;
		m_columnes = 4;
		novaForma();
		m_formaActual[1][0] = 2;
		m_formaActual[1][1] = 2;
		m_formaActual[1][2] = 2;
		m_formaActual[1][3] = 2;
		m_color = COLOR_BLAUCEL;
		break;
	case FIGURA_T:
		m_files = 3;
		m_columnes = 3;
		novaForma();
		m_formaActual[0][1] = 3;
		m_formaActual[1][0] = 3;
		m_formaActual[1][1] = 3;
		m_formaActual[1][2] = 3;
		m_color = COLOR_MAGENTA;
		break;
	case FIGURA_L:
		m_files = 3;
		m_columnes = 3;
		novaForma();
		m_formaActual[0][2] = 4;
		m_formaActual[1][0] = 4;
		m_formaActual[1][1] = 4;
		m_formaActual[1][2] = 4;
		m_color = COLOR_TARONJA;
		break;
	case FIGURA_J:
		m_files = 3;
		m_columnes = 3;
		novaForma();
		m_formaActual[0][0] = 5;
		m_formaActual[1][0] = 5;
		m_formaActual[1][1] = 5;
		m_formaActual[1][2] = 5;
		m_color = COLOR_BLAUFOSC;
		break;
	case FIGURA_Z:
		m_files = 3;
		m_columnes = 3;
		novaForma();
		m_formaActual[0][0] = 6;
		m_formaActual[0][1] = 6;
		m_formaActual[1][1] = 6;
		m_formaActual[1][2] = 6;
		m_color = COLOR_VERMELL;
		break;
	case FIGURA_S:
		m_files = 3;
		m_columnes = 3;
		novaForma();
		m_formaActual[0][1] = 7;
		m_formaActual[0][2] = 7;
		m_formaActual[1][0] = 7;
		m_formaActual[1][1] = 7;
		m_color = COLOR_VERD;
		break;
	}

	for (int j = 0; j < gir; j++)
		girHorari();
}

void Figura::girHorari()
{
	int matriuTransposada[MAX_FILA][MAX_COLUMNA];

	for (int i = 0; i < m_files; i++)
	{
		for (int j = 0; j < m_columnes; j++)
		{
			matriuTransposada[j][i] = m_formaActual[i][j];
		}
	}

	//Invertir columnes matriu 

	for (int i = 0; i < m_files; i++)
	{
		for (int j = 0; j < m_columnes; j++)
		{
			m_formaActual[i][m_columnes - 1 - j] = matriuTransposada[i][j];
		}
	}

	if (m_gir < MAX_GIR)
		m_gir++;
	else
		m_gir = 0; 
}


//Canviar
void Figura::girAntiHorari()
{
	int matriuTransposada[MAX_FILA][MAX_COLUMNA];
	
	
	for (int i = 0; i < m_files; i++)
	{
		for (int j = 0; j < m_columnes; j++)
		{
			matriuTransposada[j][i] = m_formaActual[i][j];
		}
	}
    //Invertir columnes matriu 

	for (int i = 0; i < m_files; i++)
	{
		for (int j = 0; j < m_columnes; j++)
		{
			m_formaActual[m_files - 1 - i][j] = matriuTransposada[i][j];
		}
	}
	
	

	if (m_gir > 0)
		m_gir--;
	else
		m_gir = MAX_GIR;
}

void Figura::dibuixaFigura(int x, int y, int n, int s)
{
	for (int i = 0; i < m_files; i++)
	{
		for (int j = 0; j < m_columnes; j++)
		{
			if (m_formaActual[i][j] != 0)
			{
				if (s == 1)
				{
					GraphicManager::getInstance()->drawSprite(GRAFIC_SOMBRA, x + ((m_posicioColumna + j) * MIDA_QUADRAT), y + ((m_posicioFila - 1 + i) * MIDA_QUADRAT), false);
				}
				else
				{
					switch (m_tipus)
					{
					case FIGURA_O:
						GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_GROC, x + ((m_posicioColumna + j) * MIDA_QUADRAT), y + (n * 100) + ((m_posicioFila - 1 + i) * MIDA_QUADRAT), false);
						break;
					case FIGURA_I:
						GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_BLAUCEL, x + ((m_posicioColumna + j) * MIDA_QUADRAT), y + (n * 100) + ((m_posicioFila - 1 + i) * MIDA_QUADRAT), false);
						break;
					case FIGURA_T:
						GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_MAGENTA, x + ((m_posicioColumna + j) * MIDA_QUADRAT), y + (n * 100) + ((m_posicioFila - 1 + i) * MIDA_QUADRAT), false);
						break;
					case FIGURA_L:
						GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_TARONJA, x + ((m_posicioColumna + j) * MIDA_QUADRAT), y + (n * 100) + ((m_posicioFila - 1 + i) * MIDA_QUADRAT), false);
						break;
					case FIGURA_J:
						GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_BLAUFOSC, x + ((m_posicioColumna + j) * MIDA_QUADRAT), y + (n * 100) + ((m_posicioFila - 1 + i) * MIDA_QUADRAT), false);
						break;
					case FIGURA_Z:
						GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_VERMELL, x + ((m_posicioColumna + j) * MIDA_QUADRAT), y + (n * 100) + ((m_posicioFila - 1 + i) * MIDA_QUADRAT), false);
						break;
					case FIGURA_S:
						GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_VERD, x + ((m_posicioColumna + j) * MIDA_QUADRAT), y + (n * 100) + ((m_posicioFila - 1 + i) * MIDA_QUADRAT), false);
						break;
					}
				}
			}
		}
	}
}

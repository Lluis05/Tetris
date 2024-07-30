#include "LlistaFigura.h"

LlistaFigura::~LlistaFigura()
{
	while (m_primer != nullptr)
		borrar();
}

LlistaFigura::LlistaFigura(const LlistaFigura& l)
{
	m_primer = nullptr;
	m_ultim = nullptr;
	NodeFigura* aux = l.m_primer;
	NodeFigura* aux_nova = m_primer;
	while (aux != nullptr)
	{
		aux_nova = afegeix(aux->getValor());
		aux = aux->getNext();
	}

}

LlistaFigura& LlistaFigura::operator=(const LlistaFigura& l)
{
	if (this != &l)
	{
		while (m_primer != nullptr)
			borrar();
		NodeFigura* aux = l.m_primer;
		NodeFigura* aux_nova = m_primer;
		while (aux != nullptr)
		{
			aux_nova = afegeix(aux->getValor());
			aux = aux->getNext();
		}
	}
	return *this;
}

NodeFigura* LlistaFigura::afegeix(const InfoFigura& valor)
{
	NodeFigura* aux = new NodeFigura;
	if (aux != nullptr)
	{
		aux->setValor(valor);
		aux->setNext(nullptr);
		if (m_primer == nullptr)
		{
			m_primer = aux;
		}
		else
		{
			m_ultim->setNext(aux);
		}
		m_ultim = aux;
	}

	return aux;
}

void LlistaFigura::borrar()
{
	NodeFigura* aux;
	if (m_primer == m_ultim)
	{
		delete m_primer;
		m_primer = nullptr;
		m_ultim = nullptr;
	}
	else
	{
		aux = m_primer->getNext();
		delete m_primer;
		m_primer = aux;
	}
}

int LlistaFigura::getNElements() const
{
	int nElements = 0;
	NodeFigura* aux = m_primer;
	while (aux != NULL)
	{
		nElements++;
		aux = aux->getNext();
	}

	return nElements;
}
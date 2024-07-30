#include "LlistaMoviment.h"

LlistaMoviment::~LlistaMoviment()
{
	while (m_primer != nullptr)
		borrar();
}

LlistaMoviment::LlistaMoviment(const LlistaMoviment& l)
{
	m_primer = nullptr;
	m_ultim = nullptr;
	NodeMoviment* aux = l.m_primer;
	NodeMoviment* aux_nova = m_primer;
	while (aux != nullptr)
	{
		aux_nova = afegeix(aux->getValor());
		aux = aux->getNext();
	}

}

NodeMoviment* LlistaMoviment::afegeix(const TipusMoviment& valor)
{
	NodeMoviment* aux = new NodeMoviment;
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

void LlistaMoviment::borrar()
{
	NodeMoviment* aux;
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

int LlistaMoviment::getNElements() const
{
	int nElements = 0;
	NodeMoviment* aux = m_primer;
	while (aux != NULL)
	{
		nElements++;
		aux = aux->getNext();
	}

	return nElements;
}

LlistaMoviment& LlistaMoviment::operator=(const LlistaMoviment& l)
{
	if (this != &l)
	{
		while (m_primer != nullptr)
			borrar();
		NodeMoviment* aux = l.m_primer;
		NodeMoviment* aux_nova = m_primer;
		while (aux != nullptr)
		{
			aux_nova = afegeix(aux->getValor());
			aux = aux->getNext();
		}
	}
	return *this;
}
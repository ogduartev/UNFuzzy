#ifndef CAPA_H
#define CAPA_H

#include "nodo.h"

	typedef Arreglo<nodo> ListaNodos;

class capa
{
	public:
		capa();
		virtual ~capa();

		ListaNodos* nodos()
		{
			return &Nodos;
		}
	protected:


	ListaNodos Nodos;
};

#endif // CAPA_H

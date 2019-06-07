#include "Universo.h"

Universo::~Universo()
{
	limpiarListaVariables();
	delete Variables;
}

Difusor* Universo::difusor(int num)
{
	return difusor(Variables->dato(num));
}

Variable* Universo::variable(int num)
{
	return Variables->dato(num);
}

void Universo::limpiarListaVariables()
{
	int i,numVar;
	numVar=numeroVariables();
	for(i=0;i<numVar;i++)
	{
		eliminarVariable(0);
	}
}

void Universo::entradaReal(float *ent)
{
	int i;
	for(i=0;i<numeroVariables();i++)
	{
		entradaReal(i,*(ent+i));
	}
}

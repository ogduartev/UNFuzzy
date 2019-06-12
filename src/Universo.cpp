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

Variable* Universo::variable(int num) const
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

void Universo::operator=(const Universo& other)
{
  limpiarListaVariables();
  for(int i=0;i<other.numeroVariables();i++)
	{
		Variable *Var;
		Var=new Variable();
		*Var=*(other.variable(i));
		adicionarVariable(Var);
	}
}


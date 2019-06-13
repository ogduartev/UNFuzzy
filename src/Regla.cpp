#include "Regla.h"

void Regla::adicionarEntrada()
{
	int* nuevoAntecedente=new int[NumeroEntradas+1];
	float* nuevoModificadores=new float[NumeroEntradas+1];
	for(int i=0;i<NumeroEntradas;i++)
	{
		nuevoAntecedente[i]=Antecedente[i];
		nuevoModificadores[i]=Modificadores[i];
	}
	nuevoAntecedente[NumeroEntradas]=0;
	nuevoModificadores[NumeroEntradas]=1.0;

	NumeroEntradas++;

	delete Antecedente;
	delete Modificadores;
	Antecedente=nuevoAntecedente;
	Modificadores=nuevoModificadores;
}

void Regla::adicionarSalida()
{
	int* nuevoConsecuente=new int[NumeroSalidas+1];
	for(int i=0;i<NumeroSalidas;i++)
	{
		nuevoConsecuente[i]=Consecuente[i];
	}
	nuevoConsecuente[NumeroSalidas]=0;
	NumeroSalidas++;
	delete Consecuente;
	Consecuente=nuevoConsecuente;
}

void  Regla::eliminarEntrada(int NumVar)
{
	for(int i=0;i<NumeroEntradas-1;i++)
	{
		Antecedente[i]=Antecedente[i+1];
		Modificadores[i]=Modificadores[i+1];
	}
	NumeroEntradas--;
}

void  Regla::eliminarSalida(int NumVar)
{
	for(int i=0;i<NumeroSalidas-1;i++)
	{
		Consecuente[i]=Consecuente[i+1];
	}
	NumeroSalidas--;
}


#include "nodo.h"

nodo::nodo(int numEntradas,int numSalidas)
{
	SLD.crearMinimoSLD(numEntradas,numSalidas);
	for(int i=0;i<numEntradas;i++)
	{
		pin* P1=new pin();
		Entradas.Add(P1);
	}

	for(int i=0;i<numEntradas;i++)
	{
		pin* P2=new pin();
		Salidas.Add(P2);
	}
}

nodo::~nodo()
{
	//dtor
}

void nodo::calcularNodo()
{
	actualizarEntradas();
	double entra[Entradas.GetItemsInContainer()];
	double sale [Salidas .GetItemsInContainer()];
	for(int i=0;i<Entradas.GetItemsInContainer();i++)
	{
		entra[i]=Entradas.dato(i)->valor();
	}
	calcular(entra,sale);
	for(int i=0;i<Salidas.GetItemsInContainer();i++)
	{
		Salidas.dato(i)->valor(sale[i]);
	}
}

void nodo::actualizarEntradas()
{
	for(int i=0;i<Entradas.GetItemsInContainer();i++)
	{
		pin* pinPtr= Entradas.dato(i)->contacto();
		if(pinPtr)
		{
			Entradas.dato(i)->valor(pinPtr->valor());
		}
	}
}

void nodo::calcular(double* entra, double* sale)
{
	SLD.calcular(entra,sale);
}

void nodo::ajustarPinesAsld()
{
	for(int i=Entradas.GetItemsInContainer();i<SLD.entradas->numeroVariables();i++)
	{
		pin* P=new pin();
		Entradas.Add(P);
	}
	for(int i=Salidas.GetItemsInContainer();i<SLD.salidas->numeroVariables();i++)
	{
		pin* P=new pin();
		Salidas.Add(P);
	}
	while(Entradas.GetItemsInContainer()>SLD.entradas->numeroVariables())
	{
		Entradas.Destroy(Entradas.GetItemsInContainer()-1);
	}
	while(Salidas.GetItemsInContainer()>SLD.salidas->numeroVariables())
	{
		Salidas.Destroy(Salidas.GetItemsInContainer()-1);
	}
}

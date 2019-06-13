#include "DialogoFuncionRed.h"

DialogoFuncionRed::DialogoFuncionRed(red *r,wxWindow *parent)
:DialogoFuncion::DialogoFuncion(parent)
{
	Red=r;
	iniciar();
	//ctor
}

DialogoFuncionRed::~DialogoFuncionRed()
{
	//dtor
}

int DialogoFuncionRed::numeroEntradas()
{
	return Red->numeroEntradas();
}

int DialogoFuncionRed::numeroSalidas()
{
	return Red->numeroSalidas();
}

wxString DialogoFuncionRed::nombreEntrada(int i)
{
	wxString str=Red->variableEntrada(i)->nombreVariable();
	return str;
}

wxString DialogoFuncionRed::nombreSalida (int i)
{
	wxString str=Red->variableSalida(i)->nombreVariable();
	return str;
}

float DialogoFuncionRed::rangoMinimoEntrada(int i)
{
	return Red->variableEntrada(i)->rangoMinimo();
}

float DialogoFuncionRed::rangoMaximoEntrada(int i)
{
	return Red->variableEntrada(i)->rangoMaximo();
}

float DialogoFuncionRed::rangoMinimoSalida(int i)
{
	return Red->variableSalida(i)->rangoMinimo();
}

float DialogoFuncionRed::rangoMaximoSalida(int i)
{
	return Red->variableSalida(i)->rangoMaximo();
}


void DialogoFuncionRed::pintarFuncion(bool flagFondo, bool flagCurva, int numEntra,int numSale)
{
	wxClientDC dc(this);
	wxRect canvas=canvasFuncion->GetRect();
	Grafica = new Graficador(&dc,canvas);

	float mnx, mxx, mny, mxy;
	mnx=rangoMinimoEntrada(numEntra);
	mxx=rangoMaximoEntrada(numEntra);
	mny=rangoMinimoSalida(numSale);
	mxy=rangoMaximoSalida(numSale);
	wxString nomEntra=nombreEntrada(numEntra);
	wxString nomSale =nombreSalida (numSale);

	if(flagFondo)
	{
		Grafica->pintarFondoFuncion(mnx,mxx,mny,mxy,nomEntra,nomSale);
	}
	if(!flagCurva){return;}

	float entra[numeroEntradas()];
	for(int i=0;i<numeroEntradas();i++)
	{
		entra[i]=valoresEntradas[i]->GetValue();
	}

	Grafica->pintarCurvaFuncionES(Red, numEntra,numSale,entra,colorData.GetColour());

}

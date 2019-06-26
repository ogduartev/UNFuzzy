#include "DialogoFuncionSld.h"

DialogoFuncionSld::DialogoFuncionSld(SistemaLogicaDifusa *sld,wxWindow *parent)
:DialogoFuncion::DialogoFuncion(parent)
{
	SLD=sld;
	iniciar();
}

DialogoFuncionSld::~DialogoFuncionSld()
{
	//dtor
}

int DialogoFuncionSld::numeroEntradas()
{
	return SLD->entradas->numeroVariables();
}

int DialogoFuncionSld::numeroSalidas()
{
	return SLD->salidas->numeroVariables();
}

wxString DialogoFuncionSld::nombreEntrada(int i)
{
	wxString str=SLD->entradas->variable(i)->nombreVariable();
	return str;
}

wxString DialogoFuncionSld::nombreSalida (int i)
{
	wxString str=SLD->salidas->variable(i)->nombreVariable();
	return str;
}

double DialogoFuncionSld::rangoMinimoEntrada(int i)
{
	return SLD->entradas->variable(i)->rangoMinimo();
}

double DialogoFuncionSld::rangoMaximoEntrada(int i)
{
	return SLD->entradas->variable(i)->rangoMaximo();
}

double DialogoFuncionSld::rangoMinimoSalida(int i)
{
	return SLD->salidas->variable(i)->rangoMinimo();
}

double DialogoFuncionSld::rangoMaximoSalida(int i)
{
	return SLD->salidas->variable(i)->rangoMaximo();
}


void DialogoFuncionSld::pintarFuncion(bool flagFondo, bool flagCurva, int numEntra,int numSale)
{
	wxClientDC dc(this);
	wxRect canvas=canvasFuncion->GetRect();
	Grafica = new Graficador(&dc,canvas);

	double mnx, mxx, mny, mxy;
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

	double entra[numeroEntradas()];
	for(int i=0;i<numeroEntradas();i++)
	{
		entra[i]=valoresEntradas[i]->GetValue();
	}

	Grafica->pintarCurvaFuncionES(SLD, numEntra,numSale,entra,colorData.GetColour());

}

#include "DialogoCalculoRed.h"

DialogoCalculoRed::DialogoCalculoRed(red* R, wxWindow* parent)
:DialogoCalculo::DialogoCalculo(parent)
{
	Red=R;
	iniciar();
}

DialogoCalculoRed::~DialogoCalculoRed()
{
	//dtor
}

int DialogoCalculoRed::numeroEntradas()
{
	return Red->numeroEntradas();
}

int DialogoCalculoRed::numeroSalidas()
{
	return Red->numeroSalidas();
}

wxString DialogoCalculoRed::nombreEntrada(int i)
{
	return Red->variableEntrada(i)->nombreVariable();
}

wxString DialogoCalculoRed::nombreSalida (int i)
{
	return Red->variableSalida(i)->nombreVariable();
}

double DialogoCalculoRed::rangoMinimoEntrada(int i)
{
	return Red->variableEntrada(i)->rangoMinimo();
}

double DialogoCalculoRed::rangoMaximoEntrada(int i)
{
	return Red->variableEntrada(i)->rangoMaximo();
}

void DialogoCalculoRed::calcular(double* entra, double* sale)
{
	Red->calcular(entra,sale);
}

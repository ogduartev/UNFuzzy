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

float DialogoCalculoRed::rangoMinimoEntrada(int i)
{
	return Red->variableEntrada(i)->rangoMinimo();
}

float DialogoCalculoRed::rangoMaximoEntrada(int i)
{
	return Red->variableEntrada(i)->rangoMaximo();
}

void DialogoCalculoRed::calcular(float* entra, float* sale)
{
	Red->calcular(entra,sale);
}

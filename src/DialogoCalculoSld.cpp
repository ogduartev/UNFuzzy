#include "DialogoCalculoSld.h"

DialogoCalculoSld::DialogoCalculoSld(SistemaLogicaDifusa* sld,wxWindow* parent)
:DialogoCalculo::DialogoCalculo(parent)
{
	SLD=sld;
	iniciar();
}

DialogoCalculoSld::~DialogoCalculoSld()
{
}

int DialogoCalculoSld::numeroEntradas()
{
	return SLD->entradas->numeroVariables();
}

int DialogoCalculoSld::numeroSalidas()
{
	return SLD->salidas->numeroVariables();
}

wxString DialogoCalculoSld::nombreEntrada(int i)
{
	return SLD->entradas->variable(i)->nombreVariable();
}

wxString DialogoCalculoSld::nombreSalida (int i)
{
	return SLD->salidas->variable(i)->nombreVariable();
}

double DialogoCalculoSld::rangoMinimoEntrada(int i)
{
	return SLD->entradas->variable(i)->rangoMinimo();
}

double DialogoCalculoSld::rangoMaximoEntrada(int i)
{
	return SLD->entradas->variable(i)->rangoMaximo();
}

void DialogoCalculoSld::calcular(double* entra, double* sale)
{
	SLD->calcular(entra,sale);
}


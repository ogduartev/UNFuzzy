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
	return variableEntrada(i)->nombreVariable();
}

wxString DialogoCalculoRed::nombreSalida (int i)
{
	return variableSalida(i)->nombreVariable();
}

float DialogoCalculoRed::rangoMinimoEntrada(int i)
{
	return variableEntrada(i)->rangoMinimo();
}

float DialogoCalculoRed::rangoMaximoEntrada(int i)
{
	return variableEntrada(i)->rangoMaximo();
}

void DialogoCalculoRed::calcular(float* entra, float* sale)
{
	Red->calcular(entra,sale);
}

Variable* DialogoCalculoRed::variableEntrada(int i)
{
	int cnt=0;
	int numCapa=0;
	for(int numNodo=0;numNodo < Red->capas()->dato(numCapa)->nodos()->GetItemsInContainer();numNodo++)
	{
		for(int numPin=0; numPin < Red->capas()->dato(numCapa)->nodos()->dato(numNodo)->entradas()->GetItemsInContainer(); numPin++)
		{
			if(cnt==i)
			{
				return Red->capas()->dato(numCapa)->nodos()->dato(numNodo)->sld()->entradas->variable(numPin);
			}
			cnt++;
		}
	}
	return NULL;
}

Variable* DialogoCalculoRed::variableSalida(int i)
{
	int cnt=0;
	int numCapa=Red->capas()->GetItemsInContainer()-1;
	for(int numNodo=0;numNodo < Red->capas()->dato(numCapa)->nodos()->GetItemsInContainer();numNodo++)
	{
		for(int numPin=0; numPin < Red->capas()->dato(numCapa)->nodos()->dato(numNodo)->sld()->salidas->numeroVariables(); numPin++)
		{
			if(cnt==i)
			{
				return Red->capas()->dato(numCapa)->nodos()->dato(numNodo)->sld()->salidas->variable(numPin);
			}
			cnt++;
		}
	}
	return NULL;
}

#ifndef VARIABLE_H
#define VARIABLE_H

#include<string.h>
#include <wx/wx.h>

#include <iostream>
#include <string>
using namespace std;

#include "Arreglo.h"
#include "Difusor.h"

class Variable
{
public:
	Variable(int num=10);
	~Variable();
	Difusor* difusorEntrada() const
	{
		return DifusorEntrada;
	}
	void difusorEntrada(Difusor *dif)
	{
		delete DifusorEntrada;
		DifusorEntrada=dif;
	}
	string nombreVariable()
	{
		return NombreVariable;
	}
	void nombreVariable(string s)
	{
		NombreVariable=s;
	}
	void adicionarConjuntos(ConjuntoDifuso* cd)
	{
		Conjuntos->Add(cd);
	}
	void eliminarConjuntos(int cd)
	{
		Conjuntos->Destroy(cd);
	}
	void limpiarListaConjuntos();
	int numeroConjuntos()
	{
		return Conjuntos->GetItemsInContainer();
	}
	void numeroIntervalos(int num)
	{
		NumeroIntervalos=num;
		Intervalo=(rangoMaximo()-rangoMinimo())/(NumeroIntervalos);
	}
	int numeroIntervalos()
	{
		return NumeroIntervalos;
	}
	float intervalo()
	{
		return Intervalo;
	}
	void insertarConjuntos(ConjuntoDifuso* cd,int num)
	{
		Conjuntos->AddAt(cd,num);
	}

	ConjuntoDifuso* conjunto(int conj) const;
	float pertenencia(ConjuntoDifuso*, float);
	float pertenencia(int, float);
	float pertenenciaDifusor(float);
	float rangoMinimo(){return RangoMinimo;}
	void rangoMinimo(float rm){RangoMinimo=rm;}
	float rangoMaximo(){return RangoMaximo;}
	void rangoMaximo(float rm){RangoMaximo=rm;}
	void autodefinirConjuntosRectos(int num);
	void autodefinirConjuntosCurvos(int num);
	void autodefinirConjuntosRectosCortos(int num);
	void autodefinirConjuntosCurvosCortos(int num);
	void ajustar(float minimo, float maximo);
	BOOL operator==(const Variable& other)
	{
		return ( (NombreVariable == other.NombreVariable)&
		( RangoMinimo == other.RangoMinimo)&
		( RangoMaximo == other.RangoMaximo)&
		( DifusorEntrada == other.DifusorEntrada)&
		( Conjuntos == other.Conjuntos) );
	}
	void operator=(const Variable& other);
protected:
	typedef Arreglo<ConjuntoDifuso> ListaConjuntos;

	ListaConjuntos *Conjuntos;
	Difusor *DifusorEntrada;

	float RangoMinimo;
	float RangoMaximo;
	int NumeroIntervalos;
	float Intervalo;
	string NombreVariable;
};

#endif // VARIABLE_H

#ifndef VARIABLE_H
#define VARIABLE_H

#include<string.h>

#include "Arreglo.h"
#include "Difusor.h"

class Variable
{
public:
	Variable(int num=10)
	{
		Conjuntos = new ListaConjuntos(num);
		DifusorEntrada= new DifusorSinglenton(0.5,0.01);
		NombreVariable=0;
	  char str[40];sprintf(str,"Sin nombre");
	  nombreVariable(str);
	  rangoMinimo(-1.0);
	  rangoMaximo(1.0);
	  autodefinirConjuntosRectos(num);
	}
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
	char* nombreVariable()
	{
		return NombreVariable;
	}
	char* nombreVariable(const char* s)
	{
		delete[] NombreVariable;
		NombreVariable=new char[strlen(s)+1];
		strcpy(NombreVariable,s);
		return NombreVariable;
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
	void ajustar(float minimo, float maximo);
	BOOL operator==(const Variable& other)
	{
		return ( strcmp( NombreVariable,other.NombreVariable)&
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
	char *NombreVariable;
};

#endif // VARIABLE_H

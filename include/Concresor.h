#ifndef CONCRESOR_H
#define CONCRESOR_H

#include "MaquinaInferencia.h"

/*////////////////////////////////////////////
class Concresor
La clase abstracta Concresor tiene por propósito encapsular la operación
de Concreción empleada para cada Variable Lingüistica de Salida;
fundamentalmente consta de un indentificador de cuál es la Variable de Salida
sobre la que debe operar, y un algoritmo de concreción;
;los Concresores emplean intensivamente las funciones de la Máquina de
Inferencia, pues es ésta la que genera los Conjuntos Difusos que deben
concretarse; la mayoría de algoritmos de concreción efectúan la Unión o
la Intersección de los Conjuntos Difusos producidos por el Motor de Inferencia ,
esta operación la lleva a cabo una Norma denominada Conjunción.
De esta clase se derivan varias clases concretas, cada una con un algoritmo
de concreción diferente.

atributos:
	char *Nombre;  				Etiqueta para distinguir el tipo de Concresor(ej. Altura)
	char *CodigoC;					Texto necesario para generar Código C
	char *CodigoCPP;				Texto necesario para generar Código C++
	MaquinaInferencia *Motor;	Apuntador a la MŽŽaquina de Inferencia
	int NumeroVariable;        Identificador de la Variable de Salida sobre la que opera
	Norma *Conjuncion;			Norma para efectuar Unión o Intersección
	int Identificador;			parámetro necesario para leer archivos de disco

procedimientos:
	int numeroVariable()                Consultor de NumeroVariable
	void numeroVariable(int numVar)		Modificador de NumeroVariable
	MaquinaInferencia *motor()				Consultor de Motor
	void motor(MaquinaInferencia *maq)	Modificador de Motor
	float defecto()							calcula la función defecto de la Implicación de Motor
	char *nombre()								Consultor de Nombre
	Norma *conjuncion()						Consultor de Conjuncion
	void conjuncion(Norma *nor)			Modificador de Conjuncion
	int identificador()                 Consultor de Identificador

Las funciones virtual=0 deben ser redefinidas por los hijos

	virtual float salidaConcreta(float *ent)=0;
			efectúa el algoritmo de Concreción cuando las entradas Concretas
			al Sistema de Lógica Difusa están almacenadas en el vector ent;
			Esta función encapsula todo el comportamiento del Sistema de
			Lógica Difusa
	virtual char* codigoC()=0;
			genera Código C
	virtual char* codigoCPP()=0;
			genera Código C++
	BOOL operator==(const Concresor& other)
   		operador definido para poder crear listas de Concresores
//////////////////////////////////////////////*/

class Concresor
{
public:
	Concresor(MaquinaInferencia *maq, int numVar, Norma *nor)
	{
		Motor=maq;
		NumeroVariable=numVar;
		Conjuncion=nor;
		Nombre=new char[30];
		CodigoC=new char[1000];
		CodigoCPP=new char[1000];
	}
	~Concresor()
	{
		Conjuncion=NULL;
		delete[] Nombre;
		delete[] CodigoC;
		delete[] CodigoCPP;
	}
	int numeroVariable()
	{
		return NumeroVariable;
	}
	void numeroVariable(int numVar)
	{
		NumeroVariable=numVar;
	}
	MaquinaInferencia *motor()
	{
		return Motor;
	}
	void motor(MaquinaInferencia *maq)
	{
		Motor=maq;
	}
	float defecto()
	{
		return Motor->implicacion()->defecto();
	}
	char *nombre()
	{
		return Nombre;
	}
	Norma *conjuncion()
	{
		return Conjuncion;
	}
	void conjuncion(Norma *nor)
	{
		Conjuncion=nor;
	}
	int identificador()
	{
		return Identificador;
	}
	virtual float salidaConcreta(float *ent)=0;
	virtual char* codigoC()=0;
	virtual char* codigoCPP()=0;
	BOOL operator==(const Concresor& other)
	{
		return ( strcmp( Nombre,other.Nombre)&
		( Motor == other.Motor)&
		( NumeroVariable == other.NumeroVariable)&
		( Conjuncion == other.Conjuncion) );
	}
protected:
	char *Nombre;
	char *CodigoC;
	char *CodigoCPP;
	MaquinaInferencia *Motor;
	int NumeroVariable;
	Norma *Conjuncion;
	int Identificador;
};

/*////////////////////////////////////////////////
class PrimerMaximo:public Concresor
		Nombre = Primer Máximo
		Identificador = 0

///////////////////////////////////////////////////*/

class PrimerMaximo:public Concresor
{
public:
	PrimerMaximo(MaquinaInferencia *maq, int numVar, Norma *nor):Concresor(maq,numVar,nor)
	{
		strcpy(Nombre,IDS_CONCRESOR_TIPO_0);
		Identificador=0;
	}
	~PrimerMaximo(){}
	float salidaConcreta(float *ent);
	char* codigoC();
	char* codigoCPP();
protected:
};

/*////////////////////////////////////////////////
class UltimoMaximo:public Concresor
		Nombre = Ultimo Máximo
		Identificador = 1

///////////////////////////////////////////////////*/

class UltimoMaximo:public Concresor
{
public:
	UltimoMaximo(MaquinaInferencia *maq, int numVar, Norma *nor):Concresor(maq,numVar,nor)
	{
		strcpy(Nombre,IDS_CONCRESOR_TIPO_1);
		Identificador=1;
	}
	~UltimoMaximo(){}
	float salidaConcreta(float *ent);
	char* codigoC();
	char* codigoCPP();
protected:
};

/*////////////////////////////////////////////////
class MediaDeMaximos:public Concresor
		Nombre = Media De Maximos
		Identificador = 2

///////////////////////////////////////////////////*/

class MediaDeMaximos:public Concresor
{
public:
	MediaDeMaximos(MaquinaInferencia *maq, int numVar, Norma *nor):Concresor(maq,numVar,nor)
	{
		strcpy(Nombre,IDS_CONCRESOR_TIPO_2);
		Identificador=2;
	}
	~MediaDeMaximos(){}
	float salidaConcreta(float *ent);
	char* codigoC();
	char* codigoCPP();
protected:
};

/*////////////////////////////////////////////////
class CentroDeGravedad:public Concresor
		Nombre = Centro De Gravedad
		Identificador = 3

///////////////////////////////////////////////////*/

class CentroDeGravedad:public Concresor
{
public:
	CentroDeGravedad(MaquinaInferencia *maq, int numVar, Norma *nor):Concresor(maq,numVar,nor)
	{
		strcpy(Nombre,IDS_CONCRESOR_TIPO_3);
		Identificador=3;
	}
	~CentroDeGravedad(){}
	float salidaConcreta(float *ent);
	char* codigoC();
	char* codigoCPP();
protected:
};

/*////////////////////////////////////////////////
class Altura:public Concresor
		Nombre Altura
		Identificador = 4

///////////////////////////////////////////////////*/

class Altura:public Concresor
{
public:
	Altura(MaquinaInferencia *maq, int numVar, Norma *nor):Concresor(maq,numVar,nor)
	{
		strcpy(Nombre,IDS_CONCRESOR_TIPO_4);
		Identificador=4;
	}
	~Altura(){}
	float salidaConcreta(float *ent);
	char* codigoC();
	char* codigoCPP();
protected:
};

#endif // CONCRESOR_H

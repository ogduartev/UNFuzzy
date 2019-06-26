#include "BloqueConcrecion.h"


void BloqueConcrecion::limpiarListaConcresores()
{
	int i,numConc;
	numConc=Motor->numeroSalidas()+1;
	for(i=0;i<numConc;i++)
	{
		eliminarConcresor(0);
	}
}

void BloqueConcrecion::insertarConcresor(Concresor* conc,int num)
{
	Concresores->AddAt(conc,num);
	int i;
	for(i=0;i<Concresores->GetItemsInContainer();i++)
	{
		concresor(i)->numeroVariable(i);
	}
}

Concresor* BloqueConcrecion::concresor(int numSal)
{
	return Concresores->dato(numSal);
}

double BloqueConcrecion::salidaConcreta(int numSal,double *ent)
{
	double sale=0.0;
	Concresor *conc;
	conc=concresor(numSal);
	if(conc)
	{
		sale=conc->salidaConcreta(ent);
	}
	return sale;
}

void BloqueConcrecion::salidaConcreta(double *ent,double *sal)
{
	int numSal;
	numSal=Concresores->GetItemsInContainer();
	int i;
	for(i=0;i<numSal;i++)
	{
		sal[i]=salidaConcreta(i,ent);
	}
}

void BloqueConcrecion::motor(MaquinaInferencia *maq)
{
	int i;
	int j;
	Motor=maq;
	j=maq->salidas()->numeroVariables();
	for(i=0;i<j;i++)
	{
		concresor(i)->motor(maq);
	}
}

void BloqueConcrecion::conjuncion(Norma *nor)
{
	Conjuncion=nor;
	int i;
	int j;
	j=Motor->salidas()->numeroVariables();
	for(i=0;i<j;i++)
	{
		concresor(i)->conjuncion(Conjuncion);
	}
}

void BloqueConcrecion::autodefinirBloqueConcrecion(MaquinaInferencia *maq,Norma *conjuncion)
{
	Conjuncion=conjuncion;
	Motor=maq;
	Concresor *conc;
	delete Concresores;
	int numSal;
	numSal=Motor->numeroSalidas()+1;
	Concresores=new ListaConcresores(numSal);
	int i;
	int j;
	j=Motor->salidas()->numeroVariables();
	for(i=0;i<j;i++)
	{
		conc=new CentroDeGravedad(Motor,i,conjuncion);
		adicionarConcresor(conc);
	}
}

double BloqueConcrecion::pertenenciaConjuncion(int numSalida,double sal)
{
  double con;
	con=concresor(numSalida)->defecto();
	for(int k=0;k<Motor->numeroReglas();k++)
	{
		double temp;
		temp=Motor->pertenenciaComposicion(numSalida,k,sal);
		con=conjuncion()->opera(con,temp);
	}
  return con;
}

void BloqueConcrecion::adicionarSalida()
{
	Concresor *conc;
 	conc=new CentroDeGravedad(Motor,Concresores->GetItemsInContainer(),Conjuncion);
	adicionarConcresor(conc);
}

void BloqueConcrecion::eliminarSalida(int NumVar)
{
	Concresores->Destroy(NumVar);
}

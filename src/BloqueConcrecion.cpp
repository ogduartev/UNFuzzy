#include "BloqueConcrecion.h"


void BloqueConcrecion::limpiarListaConcresores()
{
	int i,numConc;
	numConc=Motor->numeroSalidas();
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

void BloqueConcrecion::salidaConcreta(float *ent,float *sal)
{
	int numSal;
	numSal=Motor->numeroSalidas();
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
	int i;
	int j;
	j=Motor->salidas()->numeroVariables();
	for(i=0;i<j;i++)
	{
		concresor(i)->conjuncion(nor);
	}
}

void BloqueConcrecion::autodefinirBloqueConcrecion(MaquinaInferencia *maq,Norma *conjuncion)
{
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

float BloqueConcrecion::pertenenciaConjuncion(int numSalida,float sal)
{
  float con;
	con=concresor(numSalida)->defecto();
	for(int k=0;k<Motor->numeroReglas();k++)
	{
		float temp;
		temp=Motor->pertenenciaComposicion(numSalida,k,sal);
		con=conjuncion()->opera(con,temp);
	}
  return con;
}

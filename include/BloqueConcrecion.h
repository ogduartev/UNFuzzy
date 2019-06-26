#ifndef BLOQUECONCRECION_H
#define BLOQUECONCRECION_H

#include "Concresor.h"

class BloqueConcrecion
{
public:
	BloqueConcrecion(MaquinaInferencia *maq)
	{
		Motor=maq;
		int numSal;
		numSal=Motor->numeroSalidas();
		Concresores=new ListaConcresores(numSal);
	}
	~BloqueConcrecion()
	{
//		limpiarListaConcresores();
		delete Concresores;
	}
	void adicionarConcresor(Concresor* conc)
	{
		Concresores->Add(conc);
	}
	int numeroConcresores()
	{
		return Motor->salidas()->numeroVariables();
	}
	void insertarConcresor(Concresor* conc,int num);
	void eliminarConcresor(int conc)
	{
		Concresores->Destroy(conc);
	}
	Norma *conjuncion()
	{
		return Conjuncion;
	}
	void conjuncion(Norma *nor);
	void limpiarListaConcresores();
	void motor(MaquinaInferencia* maq);
	MaquinaInferencia *motor()
	{
		return Motor;
	}
	Concresor *concresor(int numSal);
	double salidaConcreta(int numSal,double *ent);
	void salidaConcreta(double *ent,double *sal);
	void autodefinirBloqueConcrecion(MaquinaInferencia* maq,Norma *conjuncion);
	double pertenenciaConjuncion(int numSalida,double sal);
	void adicionarSalida();
	void eliminarSalida(int NumVar);

//protected:
	typedef Arreglo<Concresor> ListaConcresores;

	ListaConcresores *Concresores;
	MaquinaInferencia *Motor;

	Norma* Conjuncion;

};

#endif // BLOQUECONCRECION_H

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
		numSal=Motor->numeroSalidas()+1;
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
		return concresor(0)->conjuncion();
	}
	void conjuncion(Norma *nor);
	void limpiarListaConcresores();
	void motor(MaquinaInferencia* maq);
	MaquinaInferencia *motor()
	{
		return Motor;
	}
	Concresor *concresor(int numSal);
	float salidaConcreta(int numSal,float *ent)
	{
		Concresor *conc;
		conc=concresor(numSal);
		return conc->salidaConcreta(ent);
	}
	void salidaConcreta(float *ent,float *sal);
	void autodefinirBloqueConcrecion(MaquinaInferencia* maq,Norma *conjuncion);
	float pertenenciaConjuncion(int numSalida,float sal);

protected:
	typedef Arreglo<Concresor> ListaConcresores;

	ListaConcresores *Concresores;
	MaquinaInferencia *Motor;
};

#endif // BLOQUECONCRECION_H

#ifndef MAQUINAINFERENCIA_H
#define MAQUINAINFERENCIA_H

//#include "Arreglo.h"
#include "Universo.h"
#include "Norma.h"
#include "Implicacion.h"
#include "Regla.h"

class MaquinaInferencia
{
public:
	MaquinaInferencia(Universo *ent,Universo *sal);
	MaquinaInferencia(Universo *ent,Universo *sal,int numReg);
	~MaquinaInferencia();
	Implicacion* implicacion()
	{
		return Implicaciones;
	}
	void implicacion(Implicacion *imp)
	{
		delete Implicaciones;
		Implicaciones=imp;
	}
	Norma *and_()
	{
		return And;
	}
	void and_(Norma *nor)
	{
		delete And;
		And=nor;
	}
	Norma *minComposicion()
	{
		return MinComposicion;
	}
	void minComposicion(Norma *nor)
	{
		delete MinComposicion;
		MinComposicion=nor;
	}
	Norma *maxComposicion()
	{
		return MaxComposicion;
	}
	void maxComposicion(Norma *nor)
	{
		delete MaxComposicion;
		MaxComposicion=nor;
	}

	Regla *regla(int numRegla);
	void conjuntoEntrada(int numRegla, int numVar, int numCon)
	{
		regla(numRegla)->conjuntoEntrada(numVar,numCon);
	}
	ConjuntoDifuso *conjuntoEntrada(int numRegla, int numVar)
	{
		return Entradas->conjuntoEnVariable(numVar,regla(numRegla)->conjuntoEntrada(numVar));
	}
	int numConjuntoEntrada(int numRegla, int numVar)
	{
		return regla(numRegla)->conjuntoEntrada(numVar);
	}
	void modificador(int numRegla, int numVar, double modif)
	{
		regla(numRegla)->modificador(numVar,modif);
	}
	double modificador(int numRegla, int numVar)
	{
		return regla(numRegla)->modificador(numVar);
	}
	void conjuntoSalida(int numRegla, int numVar, int numCon)
	{
		regla(numRegla)->conjuntoSalida(numVar,numCon);
	}
	ConjuntoDifuso *conjuntoSalida(int numRegla, int numVar)
	{
		return Salidas->conjuntoEnVariable(numVar,regla(numRegla)->conjuntoSalida(numVar));
	}
	int numConjuntoSalida(int numRegla, int numVar)
	{
		return regla(numRegla)->conjuntoSalida(numVar);
	}
	Universo *entradas()
	{
		return Entradas;
	}
	Universo *salidas()
	{
		return Salidas;
	}
	int numeroReglas()
	{
		return NumeroReglas;
	}
	void numeroEntradas(int numEnt)
	{
		NumeroEntradas=numEnt;
	}
	int numeroEntradas()
	{
		return NumeroEntradas;
	}
	int numeroSalidas()
	{
		return NumeroSalidas;
	}
	void numeroSalidas(int numSal)
	{
		NumeroSalidas=numSal;
	}
	void limpiarMaquinaInferencia();
	void adicionarRegla(Regla *reg)
	{
		BaseReglas->Add(reg);
		NumeroReglas++;
	}
	void eliminarRegla(int num)
	{
		BaseReglas->Destroy(num);
		NumeroReglas--;
	}
	void adicionarEntrada();
	void adicionarSalida();
	void eliminarEntrada(int NumVar);
	void eliminarSalida(int NumVar);
	void actualizarEntradas(double *ent);
	double pertenenciaDifusores(double *ent);
	double pertenenciaImplicacion(int numSal,int numRegla, double *ent,double sal);
	double pertenenciaConsecuente(int numSal,int numRegla,double sal);
	double pertenenciaAntecedente(int numRegla,double *ent);
	double pertenenciaComposicion(int numVar, int numRegla,double sal);
	int activarRegla(int numregla);
	void desocuparBaseReglas();
	void limpiaAntesUniversoFijo();
	void limpiaAntesUniversoVariable();
	void EntrenaUniversoFijo(double *antecedente, double *consecuente);
	void EntrenaUniversoVariable(double *antecedente, double *consecuente);
	void llenarRegla(Regla *rg,double *antec, double *consec);
	int compararAntec(Regla *rg1, Regla *rg2);

	void llenarEntradasBase();
	void llenarModificadoresBase();
	void llenarSalidasBaseCreciente();
	void llenarSalidasBaseDecreciente();
	void llenarSalidaCreciente(int NumVar);
	void llenarSalidaDecreciente(int NumVar);
	void llenarSalidaConstante(int NumVar,int NumCon);
	void etiquetaEliminada(bool flagEntrada,int NumVar,int NumCon);

protected:
	typedef Arreglo<Regla> ListaReglas;

	ListaReglas *BaseReglas;
	Universo *Entradas;
	Universo *Salidas;

	Implicacion *Implicaciones;
	Norma *And;
	Norma *MinComposicion;
	Norma *MaxComposicion;

	int NumeroReglas;
	int NumeroEntradas;
	int NumeroSalidas;
};

#endif // MAQUINAINFERENCIA_H

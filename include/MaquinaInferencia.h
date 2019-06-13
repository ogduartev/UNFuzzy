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
	Norma *composicion()
	{
		return Composicion;
	}
	void composicion(Norma *nor)
	{
		delete Composicion;
		Composicion=nor;
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
	void modificador(int numRegla, int numVar, float modif)
	{
		regla(numRegla)->modificador(numVar,modif);
	}
	float modificador(int numRegla, int numVar)
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
	void actualizarEntradas(float *ent);
	float pertenenciaDifusores(float *ent);
	float pertenenciaImplicacion(int numSal,int numRegla, float *ent,float sal);
	float pertenenciaConsecuente(int numSal,int numRegla,float sal);
	float pertenenciaAntecedente(int numRegla,float *ent);
	float pertenenciaComposicion(int numVar, int numRegla,float sal);
	int activarRegla(int numregla);
	void desocuparBaseReglas();
	void limpiaAntesUniversoFijo();
	void limpiaAntesUniversoVariable();
	void EntrenaUniversoFijo(float *antecedente, float *consecuente);
	void EntrenaUniversoVariable(float *antecedente, float *consecuente);
	void llenarRegla(Regla *rg,float *antec, float *consec);
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
	Norma *Composicion;
	Norma *And;

	int NumeroReglas;
	int NumeroEntradas;
	int NumeroSalidas;
};

#endif // MAQUINAINFERENCIA_H

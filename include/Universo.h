#ifndef UNIVERSO_H
#define UNIVERSO_H

#include "Variable.h"

class Universo
{
public:
	Universo(int num=10)
	{
		Variables=new ListaVariables(num);
	}
	~Universo();
	void adicionarVariable(Variable *var)
	{
		Variables->Add(var);
	}
	void eliminarVariable(int var)
	{
		Variables->Destroy(var);
	}
	int numeroVariables() const
	{
		return Variables->GetItemsInContainer();
	}
	Variable *variable(int numVar) const;
	void limpiarListaVariables();
	Difusor *difusor(int num);
	double intervaloDifusor(int numVar)
	{
		Difusor *dif;
		dif=difusor(numVar);
		return dif->intervalo();
	}
	void numeroPuntosDifusor(int numVar,int numPuntos)
	{
		Difusor *dif;
		dif=difusor(numVar);
		dif->numeroPuntos(numPuntos);
	}
	int numeroPuntosDifusor(int numVar)
	{
		Difusor *dif;
		dif=difusor(numVar);
		return dif->numeroPuntos();
	}
	double pertenenciaDifusor(int numVar, double x)
	{
		Variable *var;
		var=variable(numVar);
		return pertenenciaDifusor(var,x);
	}
	 string nombreVariable(int numVar)
	{
		Variable *var;
		var=variable(numVar);
		return nombreVariable(var);
	}
	void nombreVariable(string nom,int numVar)
	{
		Variable *var;
		var=variable(numVar);
		nombreVariable(nom,var);
	}
	void entradaReal(int numVar, double x)
	{
		Difusor *dif;
		dif=difusor(numVar);
		entradaReal(dif,x);
	}
	void entradaReal(double *ent);
	int numeroConjuntosEnVariable(int numVar)
	{
		Variable *var;
		var=variable(numVar);
		return numeroConjuntosEnVariable (var);
	}
	int numeroIntervalosEnVariable(int numVar)
	{
		Variable *var;
		var=variable(numVar);
		return numeroIntervalosEnVariable (var);
	}
	void numeroIntervalosEnVariable(int numVar,int intervalos)
	{
		Variable *var;
		var=variable(numVar);
		var->numeroIntervalos(intervalos);
	}
	double intervaloEnVariable(int numVar)
	{
		Variable *var;
		var=variable(numVar);
		return intervaloEnVariable (var);
	}
	ConjuntoDifuso *conjuntoEnVariable(int numVar, int numCon)
	{
		Variable *var;
		var=variable(numVar);
		return var->conjunto(numCon);
	}
	double rangoMinimoVariable(int numVar)
	{
		Variable *var;
		var=variable(numVar);
		return rangoMinimoVariable(var);
	}
	void rangoMinimoVariable(double rm,int numVar)
	{
		Variable *var;
		var=variable(numVar);
		rangoMinimoVariable(rm,var);
	}
	double rangoMaximoVariable(int numVar)
	{
		Variable *var;
		var=variable(numVar);
		return rangoMaximoVariable(var);
	}
	void rangoMaximoVariable(double rm,int numVar)
	{
		Variable *var;
		var=variable(numVar);
		rangoMaximoVariable(rm,var);
	}
	double minimoEnConjunto(int numVar, int numCon)
	{
		ConjuntoDifuso *cd;
		cd=conjuntoEnVariable(numVar, numCon);
		return minimoEnConjunto(cd);
	}
	double maximoEnConjunto(int numVar, int numCon)
	{
		ConjuntoDifuso *cd;
		cd=conjuntoEnVariable(numVar, numCon);
		return maximoEnConjunto(cd);
	}
	double minimoEnDifusor(int numVar)
	{
		Difusor *dif;
		dif=difusor(numVar);
		return minimoEnDifusor(dif);
	}
	double maximoEnDifusor(int numVar)
	{
		Difusor *dif;
		dif=difusor(numVar);
		return maximoEnDifusor(dif);
	}
	double pertenenciaVariable(int numVar, int numCon, double x)
	{
		ConjuntoDifuso *cd;
		cd=conjuntoEnVariable(numVar, numCon);
		return pertenenciaVariable(cd,x);
	}
	double centroEnDifusor(int numVar)
	{
		double x;
		x=difusor(numVar)->centro();;
		return x;
	}

	void operator=(const Universo& other);

protected:
	typedef Arreglo<Variable> ListaVariables;

	ListaVariables *Variables;

private:
	Difusor *difusor(Variable *var)
	{
		return var->difusorEntrada();
	}
	double pertenenciaDifusor(Variable *var, double x)
	{
		return var->pertenenciaDifusor(x);
	}
	string nombreVariable(Variable *var)
	{
		return var->nombreVariable();
	}
	void nombreVariable(string nom,Variable *var)
	{
		var->nombreVariable(nom);
	}
	void entradaReal(Difusor *dif, double x)
	{
		dif->entrada(x);
	}
	void entradaReal(Variable *var,double x)
	{
		Difusor *dif;
		dif=var->difusorEntrada();
		dif->entrada(x);
	}
	int numeroConjuntosEnVariable(Variable *var)
	{
		return var->numeroConjuntos();
	}
	int numeroIntervalosEnVariable(Variable *var)
	{
		return var->numeroIntervalos();
	}
	double intervaloEnVariable(Variable *var)
	{
		return var->intervalo();
	}
	ConjuntoDifuso *conjuntoEnVariable(Variable *var, int numCon)
	{
		return var->conjunto(numCon);
	}
	double rangoMinimoVariable(Variable *var)
	{
		return var->rangoMinimo();
	}
	void rangoMinimoVariable(double rm,Variable *var)
	{
		var->rangoMinimo(rm);
	}
	double rangoMaximoVariable(Variable *var)
	{
		return var->rangoMaximo();
	}
	void rangoMaximoVariable(double rm,Variable *var)
	{
		var->rangoMaximo(rm);
	}
	double minimoEnConjunto(Variable *var, int numCon)
	{
		ConjuntoDifuso *cd;
		cd=conjuntoEnVariable(var, numCon);
		return minimoEnConjunto(cd);
	}
	double minimoEnConjunto(ConjuntoDifuso *cd)
	{
		return cd->minimo();
	}
	double maximoEnConjunto(Variable *var, int numCon)
	{
		ConjuntoDifuso *cd;
		cd=conjuntoEnVariable(var, numCon);
		return maximoEnConjunto(cd);
	}
	double maximoEnConjunto(ConjuntoDifuso *cd)
	{
		return cd->maximo();
	}
	double minimoEnDifusor(Variable *var)
	{
		Difusor *dif;
		dif=difusor(var);
		return minimoEnDifusor(dif);
	}
	double minimoEnDifusor(Difusor *dif)
	{
		return dif->minimo();
	}
	double maximoEnDifusor(Variable *var)
	{
		Difusor *dif;
		dif=difusor(var);
		return maximoEnDifusor(dif);
	}
	double maximoEnDifusor(Difusor *dif)
	{
		return dif->maximo();
	}
	double pertenenciaVariable(Variable *var, int numCon, double x)
	{
		ConjuntoDifuso *cd;
		cd=conjuntoEnVariable(var, numCon);
		return pertenenciaVariable(cd,x);
	}
	double pertenenciaVariable(ConjuntoDifuso *cd,double x)
	{
		return cd->pertenencia(x);
	}
};

#endif // UNIVERSO_H

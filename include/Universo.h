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
	float intervaloDifusor(int numVar)
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
	float pertenenciaDifusor(int numVar, float x)
	{
		Variable *var;
		var=variable(numVar);
		return pertenenciaDifusor(var,x);
	}
	char *nombreVariable(int numVar)
	{
		Variable *var;
		var=variable(numVar);
		return nombreVariable(var);
	}
	void nombreVariable(char *nom,int numVar)
	{
		Variable *var;
		var=variable(numVar);
		nombreVariable(nom,var);
	}
	void entradaReal(int numVar, float x)
	{
		Difusor *dif;
		dif=difusor(numVar);
		entradaReal(dif,x);
	}
	void entradaReal(float *ent);
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
	float intervaloEnVariable(int numVar)
	{
		Variable *var;
		var=variable(numVar);
		return intervaloEnVariable (var);
	}
	ConjuntoDifuso *conjuntoEnVariable(int numVar, int numCon)
	{
		Variable *var;
		var=variable(numVar);
		return conjuntoEnVariable(var,numCon);
	}
	float rangoMinimoVariable(int numVar)
	{
		Variable *var;
		var=variable(numVar);
		return rangoMinimoVariable(var);
	}
	void rangoMinimoVariable(float rm,int numVar)
	{
		Variable *var;
		var=variable(numVar);
		rangoMinimoVariable(rm,var);
	}
	float rangoMaximoVariable(int numVar)
	{
		Variable *var;
		var=variable(numVar);
		return rangoMaximoVariable(var);
	}
	void rangoMaximoVariable(float rm,int numVar)
	{
		Variable *var;
		var=variable(numVar);
		rangoMaximoVariable(rm,var);
	}
	float minimoEnConjunto(int numVar, int numCon)
	{
		ConjuntoDifuso *cd;
		cd=conjuntoEnVariable(numVar, numCon);
		return minimoEnConjunto(cd);
	}
	float maximoEnConjunto(int numVar, int numCon)
	{
		ConjuntoDifuso *cd;
		cd=conjuntoEnVariable(numVar, numCon);
		return maximoEnConjunto(cd);
	}
	float minimoEnDifusor(int numVar)
	{
		Difusor *dif;
		dif=difusor(numVar);
		return minimoEnDifusor(dif);
	}
	float maximoEnDifusor(int numVar)
	{
		Difusor *dif;
		dif=difusor(numVar);
		return maximoEnDifusor(dif);
	}
	float pertenenciaVariable(int numVar, int numCon, float x)
	{
		ConjuntoDifuso *cd;
		cd=conjuntoEnVariable(numVar, numCon);
		return pertenenciaVariable(cd,x);
	}
	float centroEnDifusor(int numVar)
	{
		float x;
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
	float pertenenciaDifusor(Variable *var, float x)
	{
		return var->pertenenciaDifusor(x);
	}
	char *nombreVariable(Variable *var)
	{
		return var->nombreVariable();
	}
	void nombreVariable(char *nom,Variable *var)
	{
		var->nombreVariable(nom);
	}
	void entradaReal(Difusor *dif, float x)
	{
		dif->entrada(x);
	}
	void entradaReal(Variable *var,float x)
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
	float intervaloEnVariable(Variable *var)
	{
		return var->intervalo();
	}
	ConjuntoDifuso *conjuntoEnVariable(Variable *var, int numCon)
	{
		return var->conjunto(numCon);
	}
	float rangoMinimoVariable(Variable *var)
	{
		return var->rangoMinimo();
	}
	void rangoMinimoVariable(float rm,Variable *var)
	{
		var->rangoMinimo(rm);
	}
	float rangoMaximoVariable(Variable *var)
	{
		return var->rangoMaximo();
	}
	void rangoMaximoVariable(float rm,Variable *var)
	{
		var->rangoMaximo(rm);
	}
	float minimoEnConjunto(Variable *var, int numCon)
	{
		ConjuntoDifuso *cd;
		cd=conjuntoEnVariable(var, numCon);
		return minimoEnConjunto(cd);
	}
	float minimoEnConjunto(ConjuntoDifuso *cd)
	{
		return cd->minimo();
	}
	float maximoEnConjunto(Variable *var, int numCon)
	{
		ConjuntoDifuso *cd;
		cd=conjuntoEnVariable(var, numCon);
		return maximoEnConjunto(cd);
	}
	float maximoEnConjunto(ConjuntoDifuso *cd)
	{
		return cd->maximo();
	}
	float minimoEnDifusor(Variable *var)
	{
		Difusor *dif;
		dif=difusor(var);
		return minimoEnDifusor(dif);
	}
	float minimoEnDifusor(Difusor *dif)
	{
		return dif->minimo();
	}
	float maximoEnDifusor(Variable *var)
	{
		Difusor *dif;
		dif=difusor(var);
		return maximoEnDifusor(dif);
	}
	float maximoEnDifusor(Difusor *dif)
	{
		return dif->maximo();
	}
	float pertenenciaVariable(Variable *var, int numCon, float x)
	{
		ConjuntoDifuso *cd;
		cd=conjuntoEnVariable(var, numCon);
		return pertenenciaVariable(cd,x);
	}
	float pertenenciaVariable(ConjuntoDifuso *cd,float x)
	{
		return cd->pertenencia(x);
	}
};

#endif // UNIVERSO_H

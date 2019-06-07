#include "Variable.h"

Variable::~Variable()
{
	limpiarListaConjuntos();
	delete Conjuntos;
	delete DifusorEntrada;
	delete[] NombreVariable;
}

ConjuntoDifuso* Variable::conjunto(int conj)
{
	return Conjuntos->dato(conj);
}


void Variable::limpiarListaConjuntos()
{
	int i,numCon;
	numCon=Conjuntos->GetItemsInContainer();
	for(i=0;i<numCon;i++)
	{
		eliminarConjuntos(0);
	}
}

float Variable::pertenencia(int i, float x)
{
	return pertenencia(this->conjunto(i), x);
}

float Variable::pertenencia(ConjuntoDifuso* cd, float x)
{
	float ux;
	ux=cd->pertenencia(x);
	return ux;
}

float Variable::pertenenciaDifusor(float x)
{
	float ux;
	ux=DifusorEntrada->pertenencia(x);
	return ux;
}

void Variable::autodefinirConjuntosRectos(int num)
{
	limpiarListaConjuntos();
	ConjuntoDifuso *cd;
	float dx;
			// esta variable ayuda a calcular los soportes
			//de cada ConjuntoDifuso

	dx=(rangoMaximo()-rangoMinimo())/(num+1);
	numeroIntervalos((num+1)*5);
			// Se asume que entre más ConjuntosDifusos,
			//se requiere un Intervalo de Evaluación más pequeño
	int i;
	char cad1[20];
	char cad2[10];

			// El primer Conjunto es L, el último es Gamma
			// y los demás son Triángulo
	strcpy(cad1,IDS_VARIABLE_ETIQUETA1);
	cd=new ConjuntoL(cad1, rangoMinimo(), rangoMinimo()+dx, rangoMinimo()+2*dx);
	adicionarConjuntos(cd);
	for (i=1;i<(num-1);i++){
		strcpy(cad1,IDS_VARIABLE_ETIQUETA);
		sprintf(cad2,"%d",i+1);
		strcat(cad1,cad2);
		cd=new ConjuntoTriangulo(cad1, rangoMinimo()+i*dx, rangoMinimo()+(i+1)*dx, rangoMinimo()+(i+2)*dx);
		adicionarConjuntos(cd);
	}
	strcpy(cad1,IDS_VARIABLE_ETIQUETA);
	sprintf(cad2,"%d",i+1);
	strcat(cad1,cad2);
	cd=new ConjuntoGamma(cad1, rangoMaximo()-2*dx, rangoMaximo()-dx, rangoMaximo());
	adicionarConjuntos(cd);
}

void Variable::autodefinirConjuntosCurvos(int num)
{
	limpiarListaConjuntos();
	ConjuntoDifuso *cd;
	float dx;
			// esta variable ayuda a calcular los soportes
			//de cada ConjuntoDifuso

	dx=(rangoMaximo()-rangoMinimo())/(num+1);
	numeroIntervalos((num+1)*5);
			// Se asume que entre más ConjuntosDifusos,
			//se requiere un Intervalo de Evaluación más pequeño
	int i;
	char cad1[20];
	char cad2[10];

			// El primer Conjunto es Z, el último es s
			// y los demás son Campana
	strcpy(cad1,IDS_VARIABLE_ETIQUETA1);
	cd=new ConjuntoZ(cad1, rangoMinimo(), rangoMinimo()+dx, rangoMinimo()+2*dx);
	adicionarConjuntos(cd);
	for (i=1;i<(num-1);i++){
		strcpy(cad1,IDS_VARIABLE_ETIQUETA);
		sprintf(cad2,"%d",i+1);
		strcat(cad1,cad2);
		cd=new ConjuntoCampana(cad1, rangoMinimo()+i*dx, rangoMinimo()+(i+1)*dx, rangoMinimo()+(i+2)*dx);
		adicionarConjuntos(cd);
	}
	strcpy(cad1,IDS_VARIABLE_ETIQUETA);
	sprintf(cad2,"%d",i+1);
	strcat(cad1,cad2);
	cd=new ConjuntoS(cad1, rangoMaximo()-2*dx, rangoMaximo()-dx, rangoMaximo());
	adicionarConjuntos(cd);
}

void Variable::ajustar(float minimo, float maximo)
{
	if(maximo<=minimo){return;}
	float minimoAntes=rangoMinimo();
	float maximoAntes=rangoMaximo();
	if(minimo!=minimoAntes||maximo!=maximoAntes)
	{
		float x,mn,mx;
		ConjuntoDifuso *cd1;
		Difusor *dif1;
		int i;
		for(i=0;i<numeroConjuntos();i++)
		{
			cd1=conjunto(i);
			x=cd1->minimo();
			mn=minimo+(x-minimoAntes)*(maximo-minimo)/(maximoAntes-minimoAntes);
			x=cd1->maximo();
			mx=minimo+(x-minimoAntes)*(maximo-minimo)/(maximoAntes-minimoAntes);
			cd1->ajustar(mn,mx);
		}
		dif1=difusorEntrada();
		x=dif1->minimo();
		mn=minimo+(x-minimoAntes)*(maximo-minimo)/(maximoAntes-minimoAntes);
		x=dif1->maximo();
		mx=minimo+(x-minimoAntes)*(maximo-minimo)/(maximoAntes-minimoAntes);
		dif1->ajustar(mn,mx);
		cd1=NULL;
		dif1=NULL;
	}
	rangoMinimo(minimo);
	rangoMaximo(maximo);
}

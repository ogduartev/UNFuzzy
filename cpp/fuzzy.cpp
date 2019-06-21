#ifndef __FUZZY_CPP
#define __FUZZY_CPP
#endif


#ifndef __FUZZY_H
#include"fuzzy.h"
#endif


void ConjuntoL::nuevoPuntoClave(int punto, float x)
{
	switch(punto)
	{
		case 0: primerCorte(x);break;
		case 1: maximo(x);break;
		default:break;
	}
}

void ConjuntoTriangulo::nuevoPuntoClave(int punto, float x)
{
	switch(punto)
	{
		case 0: minimo(x);break;
		case 1: primerCorte(x);break;
		case 2: maximo(x);break;
		default:break;
	}
}

void ConjuntoPi::nuevoPuntoClave(int punto, float x)
{
	switch(punto)
	{
		case 0: minimo(x);break;
		case 1: primerCorte(x);break;
		case 2: segundoCorte(x);break;
		case 3: maximo(x);break;
		default:break;
	}
}

void ConjuntoGamma::nuevoPuntoClave(int punto, float x)
{
	switch(punto)
	{
		case 0: minimo(x);break;
		case 1: primerCorte(x);break;
		default:break;
	}
}

void ConjuntoZ::nuevoPuntoClave(int punto, float x)
{
	switch(punto)
	{
		case 0: primerCorte(x);break;
		case 1: maximo(x);break;
		default:break;
	}
}

void ConjuntoCampana::nuevoPuntoClave(int punto, float x)
{
	switch(punto)
	{
		case 0: minimo(x);break;
		case 1: primerCorte(x);break;
		case 2: maximo(x);break;
		default:break;
	}
}

void ConjuntoPiCampana::nuevoPuntoClave(int punto, float x)
{
	switch(punto)
	{
		case 0: minimo(x);break;
		case 1: primerCorte(x);break;
		case 2: segundoCorte(x);break;
		case 3: maximo(x);break;
		default:break;
	}
}

void ConjuntoS::nuevoPuntoClave(int punto, float x)
{
	switch(punto)
	{
		case 0: minimo(x);break;
		case 1: primerCorte(x);break;
		default:break;
	}
}

void ConjuntoSinglenton::nuevoPuntoClave(int punto, float x)
{
	switch(punto)
	{
		case 0: minimo(x);break;
		case 1: maximo(x);break;
		default:break;
	}
}

Variable::~Variable()
{
	limpiarListaConjuntos();
	delete Conjuntos;
	delete DifusorEntrada;
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

Universo::~Universo()
{
	limpiarListaVariables();
	delete Variables;
}

Difusor* Universo::difusor(int num)
{
	return difusor(Variables->dato(num));
}

Variable* Universo::variable(int num)
{
	return Variables->dato(num);
}

void Universo::limpiarListaVariables()
{
	int i,numVar;
	numVar=numeroVariables();
	for(i=0;i<numVar;i++)
	{
		eliminarVariable(0);
	}
}

void Universo::entradaReal(float *ent)
{
	int i;
	for(i=0;i<numeroVariables();i++)
	{
		entradaReal(i,*(ent+i));
	}
}

MaquinaInferencia::MaquinaInferencia(Universo *ent,Universo *sal,int numReg)
{
	Entradas=ent;
	Salidas=sal;
	NumeroEntradas=Entradas->numeroVariables();
	NumeroSalidas=Salidas->numeroVariables();
	NumeroReglas=numReg;
	BaseReglas=new ListaReglas(NumeroReglas);
	Regla *rg;
	int i;
	for(i=0;i<NumeroReglas;i++)
	{
		rg=new Regla(NumeroEntradas,NumeroSalidas);
		BaseReglas->Add(rg);
	}
	Implicaciones=new ImplicacionMinimo();
	Composicion=new Minimo();
	And=new Minimo();
}

MaquinaInferencia::~MaquinaInferencia()
{
	delete Implicaciones;
	delete Composicion;
	delete BaseReglas;
	delete And;
}

Regla *MaquinaInferencia::regla(int numRegla)
{
	return BaseReglas->dato(numRegla);
}


void MaquinaInferencia::limpiarMaquinaInferencia()
{
	int i,j;
	for(i=0;i<numeroReglas();i++)
	{
		for(j=0;j<numeroEntradas();j++)
		{
			modificador(i,j,1.0);
		}
	}
	for(j=0;j<NumeroReglas;j++)
	{
		for(i=0;i<NumeroSalidas;i++)
		{
			conjuntoSalida(j,i,0);
		}
	}

}

void MaquinaInferencia::actualizarEntradas(float *ent)
{
	Entradas->entradaReal(ent);
}

float MaquinaInferencia::pertenenciaDifusores(float *ent)
{
	float uxd;
	int j;
	j=0;
	uxd=Entradas->pertenenciaDifusor(j,ent[j]);
	for(j=1;j<NumeroEntradas;j++)
	{
		uxd=And->opera(uxd,Entradas->pertenenciaDifusor(j,ent[j]));
	}
	return uxd;
}

float MaquinaInferencia::pertenenciaImplicacion(int numSal,int numRegla, float *ent,float sal)
{
	float uxa,uxb;
	uxa=pertenenciaAntecedente(numRegla,ent);
	uxb=pertenenciaConsecuente(numSal,numRegla,sal);
	return Implicaciones->implica(uxa,uxb);
}

float MaquinaInferencia::pertenenciaConsecuente(int numSal,int numRegla,float sal)
{
	float uxc;
	int conj;
	conj=numConjuntoSalida(numRegla,numSal);
	uxc=Salidas->pertenenciaVariable(numSal,conj,sal);
	return uxc;
}

float MaquinaInferencia::pertenenciaAntecedente(int numRegla,float *ent)
{
	float ux;
	float uxa;
	int conj;
	int j;
	j=0;
	conj=numConjuntoEntrada(numRegla,0);
	ux=Entradas->pertenenciaVariable(j,conj,ent[j]);
	if(modificador(numRegla,0)>0.0)
	{
		uxa=pow(ux,modificador(numRegla,0));
	}else
	{
		uxa=1;
	}
	for (j=1;j<NumeroEntradas;j++)
	{
		conj=numConjuntoEntrada(numRegla,j);
		ux=Entradas->pertenenciaVariable(j,conj,ent[j]);
		if(modificador(numRegla,j)!=0)
		{
			ux=pow(ux,modificador(numRegla,0));
		}else
		{
			ux=1;
		}
		uxa=And->opera(uxa,ux);
	}
	return uxa;
}

float MaquinaInferencia::pertenenciaComposicion(int numVar, int numRegla,float sal)
{
	float ux;
	float uxa;
	float uxab;
	float comp=0;
	float *x;
	x=new float[NumeroEntradas];
	int *inter;
	inter= new int[NumeroEntradas];
	if(!activarRegla(numRegla))
	{
		comp=Implicaciones->defecto();
	}
	else{
		int casos=1;
		int i;
		for (i=0;i<NumeroEntradas;i++)
		{
			casos=casos*Entradas->numeroPuntosDifusor(i);
			inter[i]=1;
		}
		for(i=0;i<casos;i++)
		{
			int k;
			for (k=0;k<NumeroEntradas;k++)
			{
				x[k]=Entradas->minimoEnDifusor(k)+Entradas->intervaloDifusor(k)*inter[k];
				inter[k]=inter[k]+1;
				if(inter[k]>=Entradas->numeroPuntosDifusor(k))
				{
					inter[k]=1;
				}
			}
			uxab=pertenenciaImplicacion(numVar,numRegla,x,sal);
			uxa=pertenenciaDifusores(x);
			ux=Composicion->opera(uxa,uxab);
			if(ux>comp)
			{
				comp=ux;
			}
		}
	}
	delete[] x;
	delete[] inter;
	return comp;
}

int MaquinaInferencia::activarRegla(int numRegla)
{
	int i;
	for(i=0;i<NumeroEntradas;i++)
	{
		float bmn,bmx,cmn,cmx;
		int numCon;
		numCon=numConjuntoEntrada(numRegla,i);
		bmn=Entradas->minimoEnConjunto(i,numCon);
		bmx=Entradas->maximoEnConjunto(i,numCon);
		cmn=Entradas->minimoEnDifusor(i);
		cmx=Entradas->maximoEnDifusor(i);
		if(bmn>cmx||bmx<cmn)
			return 0;
	}
	return 1;
}

void MaquinaInferencia::desocuparBaseReglas()
{
	int i,num;
	 num=numeroReglas();
	for(i=1;i<num;i++)
	{
		  eliminarRegla(0);
	}
	 for(i=0;i<numeroEntradas();i++)
	 {
		  conjuntoEntrada(0,i,0);
	 }
	 for(i=0;i<numeroEntradas();i++)
	 {
		  modificador(0,i,0);
	 }
	 for(i=0;i<numeroSalidas();i++)
	 {
		  conjuntoSalida(0,i,0);
	 }
	 NumeroReglas=1;
}

void MaquinaInferencia::EntrenaUniversoFijo(float *antecedente, float *consecuente)
{
	Regla *ReglaTemporal;
	ReglaTemporal=new Regla(NumeroEntradas,NumeroSalidas);
	llenarRegla(ReglaTemporal,antecedente,consecuente);
	int preexistencia=0;
	int i;
	for(i=0;i<numeroReglas();i++)
	{
		if(compararAntec(ReglaTemporal,regla(i)))
		{
			if(ReglaTemporal->certeza()>regla(i)->certeza())
			{
				adicionarRegla(ReglaTemporal);
				eliminarRegla(i);
			}
			preexistencia=1;
			i=numeroReglas()+1;
		}
	}
	if(preexistencia==0)
	{
		adicionarRegla(ReglaTemporal);
	}
}

void MaquinaInferencia::llenarRegla(Regla *ReglaTemporal, float *antec, float *consec)
{
	int i;
	float certeza=1.0;
	for(i=0;i<NumeroEntradas;i++)
	{
		if(antec[i]>Entradas->rangoMaximoVariable(i))
		{
			antec[i]=Entradas->rangoMaximoVariable(i);
		}
		if(antec[i]<Entradas->rangoMinimoVariable(i))
		{
			antec[i]=Entradas->rangoMinimoVariable(i);
		}
		float maxPerAnte=0;
		int j;
		for(j=0;j<Entradas->numeroConjuntosEnVariable(i);j++)
		{
			float Per;
			Per=Entradas->pertenenciaVariable(i,j,antec[i]);
			if(maxPerAnte<Per)
			{
				maxPerAnte=Per;
				ReglaTemporal->conjuntoEntrada(i,j);
			}
		}
		certeza=certeza*maxPerAnte;
		ReglaTemporal->modificador(i,1.0);
	}
	for(i=0;i<NumeroSalidas;i++)
	{
		if(consec[i]>Salidas->rangoMaximoVariable(i))
		{
			consec[i]=Salidas->rangoMaximoVariable(i);
		}
		if(consec[i]<Salidas->rangoMinimoVariable(i))
		{
			consec[i]=Salidas->rangoMinimoVariable(i);
		}
		float maxPerCons=0;
		int j;
		for(j=0;j<Salidas->numeroConjuntosEnVariable(i);j++)
		{
			float Per;
			Per=Salidas->pertenenciaVariable(i,j,consec[i]);
			if(maxPerCons<Per)
			{
				maxPerCons=Per;
				ReglaTemporal->conjuntoSalida(i,j);
			}
		}
		certeza=certeza*maxPerCons;
	}
	ReglaTemporal->certeza(certeza);
}


int MaquinaInferencia::compararAntec(Regla *rg1, Regla *rg2)
{
	int resultado=1;
	int i;
	for(i=0;i<NumeroEntradas;i++)
	{
		if(rg1->conjuntoEntrada(i)!=rg2->conjuntoEntrada(i))
		{
			resultado=0;
		}
	}
	return resultado;
}

void MaquinaInferencia::EntrenaUniversoVariable(float *antecedente, float *consecuente)
{
	ConjuntoDifuso* conj;
	int i;
	for(i=0;i<NumeroEntradas;i++)
	{
		int tipoConjunto;
		tipoConjunto=Entradas->variable(i)->conjunto(0)->identificador();
		int numeroPuntos;
		numeroPuntos=Entradas->variable(i)->conjunto(0)->numeroPuntosClaves();
		float *puntos;
		puntos=new float[numeroPuntos];
		Entradas->variable(i)->conjunto(0)->puntosClaves(puntos);
		switch(tipoConjunto)
		{
			case 0 : conj=new ConjuntoL(puntos[0],puntos[1],puntos[2]);
						break;
			case 1 : conj=new ConjuntoTriangulo(puntos[0],puntos[1],puntos[2]);
						break;
			case 2 : conj=new ConjuntoPi(puntos[0],puntos[1],puntos[2],puntos[3]);
						break;
			case 3 : conj=new ConjuntoGamma(puntos[0],puntos[1],puntos[2]);
						break;
			case 4 : conj=new ConjuntoZ(puntos[0],puntos[1],puntos[2]);
						break;
			case 5 : conj=new ConjuntoCampana(puntos[0],puntos[1],puntos[2]);
						break;
			case 6 : conj=new ConjuntoS(puntos[0],puntos[1],puntos[2]);
						break;
			case 7 : conj=new ConjuntoPiCampana(puntos[0],puntos[1],puntos[2],puntos[3]);
						break;
			case 8 : conj=new ConjuntoSinglenton(puntos[0],puntos[1]);
						break;
			default:break;
		}
		float delta;
		delta=*(antecedente+i)-conj->centroAltura();
		int j;
		for(j=0;j<numeroPuntos;j++)
		{
			conj->nuevoPuntoClave(j,puntos[j]+delta);
		}
		Entradas->variable(i)->adicionarConjuntos(conj);
	}

	for(i=0;i<NumeroSalidas;i++)
	{
		int tipoConjunto;
		tipoConjunto=Salidas->variable(i)->conjunto(0)->identificador();
		int numeroPuntos;
		numeroPuntos=Salidas->variable(i)->conjunto(0)->numeroPuntosClaves();
		float *puntos;
		puntos=new float[numeroPuntos];
		Salidas->variable(i)->conjunto(0)->puntosClaves(puntos);
		switch(tipoConjunto)
		{
			case 0 : conj=new ConjuntoL(puntos[0],puntos[1],puntos[2]);
						break;
			case 1 : conj=new ConjuntoTriangulo(puntos[0],puntos[1],puntos[2]);
						break;
			case 2 : conj=new ConjuntoPi(puntos[0],puntos[1],puntos[2],puntos[3]);
						break;
			case 3 : conj=new ConjuntoGamma(puntos[0],puntos[1],puntos[2]);
						break;
			case 4 : conj=new ConjuntoZ(puntos[0],puntos[1],puntos[2]);
						break;
			case 5 : conj=new ConjuntoCampana(puntos[0],puntos[1],puntos[2]);
						break;
			case 6 : conj=new ConjuntoS(puntos[0],puntos[1],puntos[2]);
						break;
			case 7 : conj=new ConjuntoPiCampana(puntos[0],puntos[1],puntos[2],puntos[3]);
						break;
			case 8 : conj=new ConjuntoSinglenton(puntos[0],puntos[1]);
						break;
			default:break;
		}
		float delta;
		delta=*(consecuente+i)-conj->centroAltura();
		int j;
		for(j=0;j<numeroPuntos;j++)
		{
			conj->nuevoPuntoClave(j,puntos[j]+delta);
		}
		Salidas->variable(i)->adicionarConjuntos(conj);
	}
	Regla *rg;
	rg=new Regla(NumeroEntradas,NumeroSalidas);
	for(i=0;i<NumeroEntradas;i++)
	{
		rg->conjuntoEntrada(i,Entradas->variable(i)->numeroConjuntos()-1);
		rg->modificador(i,1.0);
	}
	for(i=0;i<NumeroSalidas;i++)
	{
		rg->conjuntoSalida(i,Salidas->variable(i)->numeroConjuntos()-1);
	}
	rg->certeza(1.0);
	adicionarRegla(rg);
}


float PrimerMaximo::salidaConcreta(float *ent)
{
	float con;
	float concreto=0;
	float y;
	float ymax;
	ymax=Motor->salidas()->rangoMinimoVariable(NumeroVariable);
	Motor->actualizarEntradas(ent);
	int i;
	for(i=0;i<(Motor->salidas()->numeroIntervalosEnVariable(NumeroVariable)+1);i++)
	{
		con=defecto();
		y=Motor->salidas()->rangoMinimoVariable(NumeroVariable)+i*Motor->salidas()->intervaloEnVariable(NumeroVariable);
		int j;
		for(j=0;j<Motor->numeroReglas();j++)
		{
			float temp;
			temp=Motor->pertenenciaComposicion(NumeroVariable,j,y);
			con=Conjuncion->opera(con,temp);
		}
		if(concreto<con)
		{
			concreto=con;
			ymax=y;
		}
	}
	return ymax;
}


float UltimoMaximo::salidaConcreta(float *ent)
{
	float con;
	float concreto=0;
	float y;
	float ymax;
	ymax=Motor->salidas()->rangoMinimoVariable(NumeroVariable);
	Motor->actualizarEntradas(ent);
	int i;
	for(i=0;i<(Motor->salidas()->numeroIntervalosEnVariable(NumeroVariable)+1);i++)
	{
		con=defecto();
		y=Motor->salidas()->rangoMinimoVariable(NumeroVariable)+i*Motor->salidas()->intervaloEnVariable(NumeroVariable);
		int j;
		for(j=0;j<Motor->numeroReglas();j++)
		{
			float temp;
			temp=Motor->pertenenciaComposicion(NumeroVariable,j,y);
			con=Conjuncion->opera(con,temp);
		}
		if(concreto<=con)
		{
			concreto=con;
			ymax=y;
		}
	}
	return ymax;
}


float MediaDeMaximos::salidaConcreta(float *ent)
{
	float con;
	float concreto1=0;
	float concreto2=0;
	float y;
	float ymax;
	float ymax1,ymax2;
	ymax=Motor->salidas()->rangoMinimoVariable(NumeroVariable);
	ymax1=ymax;
	ymax2=ymax;
	Motor->actualizarEntradas(ent);
	int i;
	for(i=0;i<(Motor->salidas()->numeroIntervalosEnVariable(NumeroVariable)+1);i++)
	{
		con=defecto();
		y=Motor->salidas()->rangoMinimoVariable(NumeroVariable)+i*Motor->salidas()->intervaloEnVariable(NumeroVariable);
		int j;
		for(j=0;j<Motor->numeroReglas();j++)
		{
			float temp;
			temp=Motor->pertenenciaComposicion(NumeroVariable,j,y);
			con=Conjuncion->opera(con,temp);
		}
		if(concreto1<con)
		{
			concreto1=con;
			ymax1=y;
		}
		if(concreto2<=con)
		{
			concreto2=con;
			ymax2=y;
		}
	}
	ymax=(ymax1+ymax2)/2;
	return ymax;
}


float CentroDeGravedad::salidaConcreta(float *ent)
{
	float con;
	float y;
	float y1=0;
	float y2=0;
	float ymax;
	Motor->actualizarEntradas(ent);
	int i;
	for(i=0;i<(Motor->salidas()->numeroIntervalosEnVariable(NumeroVariable)+1);i++)
	{
		con=defecto();
		y=Motor->salidas()->rangoMinimoVariable(NumeroVariable)+i*Motor->salidas()->intervaloEnVariable(NumeroVariable);
		int j;
		for(j=0;j<Motor->numeroReglas();j++)
		{
			float temp;
			temp=Motor->pertenenciaComposicion(NumeroVariable,j,y);
			con=Conjuncion->opera(con,temp);
		}
		y1=y1+y*con;
		y2=y2+con;
	}
	if(fabs(y2)<0.000001)
		y2=100000.0;
	if(fabs(y1)<0.000001)
		y1=0.0;
	ymax=y1/y2;
	return ymax;
}

float Altura::salidaConcreta(float *ent)
{
	float ymax;
	float y;
	 float y1,y2;
	Motor->actualizarEntradas(ent);
	int j;
    y1=0;
    y2=0;
	for(j=0;j<Motor->numeroReglas();j++)
	{
		if(Motor->activarRegla(j))
		{
			float temp;
			y=Motor->conjuntoSalida(j,NumeroVariable)->centroAltura();
			temp=Motor->pertenenciaComposicion(NumeroVariable,j,y);
			y1=y1+temp*y;
			y2=y2+temp;
		}
	}
	if(fabs(y2)<0.000001)
		y2=100000.0;
	if(fabs(y1)<0.000001)
		y1=0.0;
	ymax=y1/y2;
	return ymax;
}


void BloqueConcrecion::limpiarListaConcresores()
{
	int i,numConc;
	numConc=Motor->numeroSalidas();
	for(i=0;i<numConc;i++)
	{
		eliminarConcresor(0);
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

/////////////////////////

void nodo::calcularNodo()
{
	actualizarEntradas();
	float entra[Entradas.GetItemsInContainer()];
	float sale [Salidas .GetItemsInContainer()];
	for(int i=0;i<Entradas.GetItemsInContainer();i++)
	{
		entra[i]=Entradas.dato(i)->valor();
	}
	calcular(entra,sale);
	for(int i=0;i<Salidas.GetItemsInContainer();i++)
	{
		Salidas.dato(i)->valor(sale[i]);
	}
}

void nodo::actualizarEntradas()
{
	for(int i=0;i<Entradas.GetItemsInContainer();i++)
	{
		pin* pinPtr= Entradas.dato(i)->contacto();
		if(pinPtr)
		{
			Entradas.dato(i)->valor(pinPtr->valor());
		}
	}
}

void nodo::calcular(float* entra, float* sale)
{
	SLD->calcular(entra,sale);
}

void nodo::ajustarPinesAsld()
{
	for(int i=Entradas.GetItemsInContainer();i<SLD->entradas->numeroVariables();i++)
	{
		pin* P=new pin();
		Entradas.Add(P);
	}
	for(int i=Salidas.GetItemsInContainer();i<SLD->salidas->numeroVariables();i++)
	{
		pin* P=new pin();
		Salidas.Add(P);
	}
	while(Entradas.GetItemsInContainer()>SLD->entradas->numeroVariables())
	{
		Entradas.Destroy(Entradas.GetItemsInContainer()-1);
	}
	while(Salidas.GetItemsInContainer()>SLD->salidas->numeroVariables())
	{
		Salidas.Destroy(Salidas.GetItemsInContainer()-1);
	}
}

////////////////////////////

bool red::conectar(int capa1, int nodo1, int pin1,int capa2, int nodo2, int pin2)
{
	if(capa1<0)                            {return false;}
	if(capa1!=(capa2-1))                   {return false;}
	if(!buscarPinSalida(capa1,nodo1,pin1)) {return false;}
	if(!buscarPinEntrada(capa2,nodo2,pin2)){return false;}
	pin* ptr1;
	pin* ptr2;
	ptr1=Capas.dato(capa1)->nodos()->dato(nodo1)->salidas() ->dato(pin1);
	ptr2=Capas.dato(capa2)->nodos()->dato(nodo2)->entradas()->dato(pin2);
	ptr2->contacto(ptr1);
}

bool red::buscarCapa(int numCapa)
{
	if(numCapa>=Capas.GetItemsInContainer()){return false;}
	return true;
}

bool red::buscarNodo(int numCapa, int numNodo)
{
	if(numCapa>=Capas.GetItemsInContainer())                                                   {return false;}
	if(numNodo>=Capas.dato(numCapa)->nodos()->GetItemsInContainer())                           {return false;}
	return true;
}

bool red::buscarPinEntrada(int numCapa, int numNodo, int numPin)
{
	if(numCapa>=Capas.GetItemsInContainer())                                                   {return false;}
	if(numNodo>=Capas.dato(numCapa)->nodos()->GetItemsInContainer())                           {return false;}
	if(numPin >=Capas.dato(numCapa)->nodos()->dato(numNodo)->entradas()->GetItemsInContainer()){return false;}
	return true;
}

bool red::buscarPinSalida(int numCapa, int numNodo, int numPin)
{
	if(numCapa>=Capas.GetItemsInContainer())                                                   {return false;}
	if(numNodo>=Capas.dato(numCapa)->nodos()->GetItemsInContainer())                           {return false;}
	if(numPin >=Capas.dato(numCapa)->nodos()->dato(numNodo)->salidas()->GetItemsInContainer()){return false;}
	return true;
}

float red::valorPinEntrada(int numCapa, int numNodo, int numPin)
{
	float V=0.0;
	if(!buscarPinEntrada(numCapa,numNodo,numPin))
	{
		return V;
	}
	V=Capas.dato(numCapa)->nodos()->dato(numNodo)->entradas()->dato(numPin)->valor();
}

float red::valorPinSalida(int numCapa, int numNodo, int numPin)
{
	float V=0.0;
	if(!buscarPinSalida(numCapa,numNodo,numPin))
	{
		return V;
	}
	V=Capas.dato(numCapa)->nodos()->dato(numNodo)->salidas()->dato(numPin)->valor();
}

void red::calcularRed()
{
	for(int numCapa=0;numCapa<Capas.GetItemsInContainer();numCapa++)
	{
		for(int numNodo=0;numNodo<Capas.dato(numCapa)->nodos()->GetItemsInContainer();numNodo++)
		{
		  Capas.dato(numCapa)->nodos()->dato(numNodo)->calcularNodo();
		}
	}
}

void red::valorEntrada(int numNodo, int numPin, float Valor)
{
  if(!buscarPinEntrada(0,numNodo,numPin))
	{
		return;
	}
	Capas.dato(0)->nodos()->dato(numNodo)->entradas()->dato(numPin)->valor(Valor);
}

nodo* red::ptrNodo(int numCapa, int numNodo)
{
	if(!buscarNodo(numCapa,numNodo))
	{
		return NULL;
	}
	return Capas.dato(numCapa)->nodos()->dato(numNodo);
}

pin* red::ptrPinEntrada(int numCapa, int numNodo, int numPin)
{
	if(!buscarPinEntrada(numCapa,numNodo,numPin)) {return NULL;}
	pin* Pin=capas()->dato(numCapa)->nodos()->dato(numNodo)->entradas()->dato(numPin);
	return Pin;
}

pin* red::ptrPinSalida(int numCapa, int numNodo, int numPin)
{
	if(!buscarPinSalida(numCapa,numNodo,numPin)) {return NULL;}
	pin* Pin=capas()->dato(numCapa)->nodos()->dato(numNodo)->salidas()->dato(numPin);
	return Pin;
}

void red::desconectarSalida(int numCapa, int numNodo, int numPin)
{
	pin* PinSalida=ptrPinSalida(numCapa, numNodo, numPin);
	if(!PinSalida){return;}
	for(int i=0;i<capas()->GetItemsInContainer();i++)
	{
		for(int j=0;j<capas()->dato(i)->nodos()->GetItemsInContainer();j++)
		{
			for(int k=0;k<capas()->dato(i)->nodos()->dato(j)->entradas()->GetItemsInContainer();k++)
			{
			  pin* PinEntrada=ptrPinEntrada(i, j, k);
			  if(PinEntrada->contacto() == PinSalida)
				{
					PinEntrada->contacto(NULL);
				}
			}
		}
	}
}

void red::desconectarEntradasNodo(int numCapa, int numNodo)
{
	nodo* Nodo=ptrNodo(numCapa, numNodo);
	if(!Nodo){return;}
	for(int i=0;i<Nodo->entradas()->GetItemsInContainer();i++)
	{
		Nodo->entradas()->dato(i)->contacto(NULL);
	}
}

void red::desconectarSalidasNodo(int numCapa, int numNodo)
{
	nodo* Nodo=ptrNodo(numCapa, numNodo);
	if(!Nodo){return;}
	for(int i=0;i<Nodo->salidas()->GetItemsInContainer();i++)
	{
		desconectarSalida(numCapa, numNodo, i);
	}
}

void red::eliminarNodo(int numCapa, int numNodo)
{
	if(!buscarNodo(numCapa, numNodo)){return;}
	desconectarEntradasNodo(numCapa, numNodo);
	desconectarSalidasNodo(numCapa, numNodo);
	capas()->dato(numCapa)->nodos()->Destroy(numNodo);
}

void red::eliminarCapa(int numCapa)
{
	if(!buscarCapa(numCapa)){return;}
	while(capas()->dato(numCapa)->nodos()->GetItemsInContainer() > 0)
	{
		eliminarNodo(numCapa, 0);
	}
	capas()->Destroy(numCapa);
}

void red::eliminarCapas()
{
	while(capas()->GetItemsInContainer() > 0)
	{
		eliminarCapa(0);
	}
}

void red::adicionarCapa()
{
	capa* C=new capa();
	Capas.Add(C);
}

void red::adicionarNodo(int numCapa)
{
	if(!buscarCapa(numCapa)){return;}
	nodo* N=new nodo();
	capas()->dato(numCapa)->nodos()->Add(N);
}

bool red::buscarPinEntrada(pin* Pin, int *numCapa, int *numNodo, int *numPin)
{
	if(!Pin){return false;}
	for(int i=0;i<capas()->GetItemsInContainer();i++)
	{
		for(int j=0;j<capas()->dato(i)->nodos()->GetItemsInContainer();j++)
		{
			for(int k=0;k<capas()->dato(i)->nodos()->dato(j)->entradas()->GetItemsInContainer();k++)
			{
			  pin* PinEntrada=ptrPinEntrada(i, j, k);
			  if(PinEntrada == Pin)
				{
					*numCapa=i;
					*numNodo=j;
					*numPin=k;
					return true;
				}
			}
		}
	}
	return false;
}

bool red::buscarPinSalida(pin* Pin, int *numCapa, int *numNodo, int *numPin)
{
	if(!Pin){return false;}
	for(int i=0;i<capas()->GetItemsInContainer();i++)
	{
		for(int j=0;j<capas()->dato(i)->nodos()->GetItemsInContainer();j++)
		{
			for(int k=0;k<capas()->dato(i)->nodos()->dato(j)->entradas()->GetItemsInContainer();k++)
			{
			  pin* PinEntrada=ptrPinSalida(i, j, k);
			  if(PinEntrada == Pin)
				{
					*numCapa=i;
					*numNodo=j;
					*numPin=k;
					return true;
				}
			}
		}
	}
	return false;
}


int red::numeroEntradas()
{
	int num=0;
	int numCapa=0;
	for(int numNodo=0;numNodo < capas()->dato(numCapa)->nodos()->GetItemsInContainer();numNodo++)
	{
		num+=capas()->dato(numCapa)->nodos()->dato(numNodo)->entradas()->GetItemsInContainer();
	}
	return num;
}

int red::numeroSalidas()
{
	int num=0;
	int numCapa=capas()->GetItemsInContainer()-1;
	for(int numNodo=0;numNodo < capas()->dato(numCapa)->nodos()->GetItemsInContainer();numNodo++)
	{
		num+=capas()->dato(numCapa)->nodos()->dato(numNodo)->salidas()->GetItemsInContainer();
	}
	return num;
}

void red::asignarEntradas(float* entra)
{
	int cnt=0;
	int numCapa=0;
	for(int numNodo=0;numNodo < capas()->dato(numCapa)->nodos()->GetItemsInContainer();numNodo++)
	{
		for(int numPin=0; numPin < capas()->dato(numCapa)->nodos()->dato(numNodo)->entradas()->GetItemsInContainer(); numPin++)
		{
			valorEntrada(numNodo, numPin, entra[cnt]);
			cnt++;
		}
	}
}

void red::leerSalidas(float* sale)
{
	int cnt=0;
	int numCapa=capas()->GetItemsInContainer()-1;
	for(int numNodo=0;numNodo < capas()->dato(numCapa)->nodos()->GetItemsInContainer();numNodo++)
	{
		for(int numPin=0; numPin < capas()->dato(numCapa)->nodos()->dato(numNodo)->entradas()->GetItemsInContainer(); numPin++)
		{
			sale[cnt]=valorPinSalida(numCapa, numNodo,numPin);
			cnt++;
		}
	}
}

void red::calcular(float* entra, float* sale)
{
	asignarEntradas(entra);
	calcularRed();
	leerSalidas(sale);
}



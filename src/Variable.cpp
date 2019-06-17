#include "Variable.h"

Variable::Variable(int num)
{
	Conjuntos = new ListaConjuntos(num);
	DifusorEntrada= new DifusorSinglenton(0.5,0.01);
	NombreVariable=0;
  char str[40];sprintf(str,"--");
  nombreVariable(str);
  numeroIntervalos(20);
  rangoMinimo(-1.0);
  rangoMaximo(1.0);
  autodefinirConjuntosRectos(num);
}

Variable::~Variable()
{
	limpiarListaConjuntos();
	delete Conjuntos;
	delete DifusorEntrada;
	delete[] NombreVariable;
}

ConjuntoDifuso* Variable::conjunto(int conj) const
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
	char cad1[200];

			// El primer Conjunto es L, el último es Gamma
			// y los demás son Triángulo
	wxString n=_("Set ");
	n << (1);
	sprintf(cad1,n.c_str());
	cd=new ConjuntoL(cad1, rangoMinimo(), rangoMinimo()+dx, rangoMinimo()+2*dx);
	adicionarConjuntos(cd);
	for (i=1;i<(num-1);i++)
	{
		n=_("Set ");
		n << (i+1);
		sprintf(cad1,n.c_str());
		cd=new ConjuntoTriangulo(cad1, rangoMinimo()+i*dx, rangoMinimo()+(i+1)*dx, rangoMinimo()+(i+2)*dx);
		adicionarConjuntos(cd);
	}
	n=_("Set ");
	n << (num);
	sprintf(cad1,n.c_str());
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
	char cad1[200];

			// El primer Conjunto es Z, el último es s
			// y los demás son Campana
	wxString n=_("Set ");
	n << (1);
	sprintf(cad1,n.c_str());
	cd=new ConjuntoZ(cad1, rangoMinimo(), rangoMinimo()+dx, rangoMinimo()+2*dx);
	adicionarConjuntos(cd);
	for (i=1;i<(num-1);i++)
	{
		n =_("Set ");
		n << (i+1);
		sprintf(cad1,n.c_str());
		cd=new ConjuntoCampana(cad1, rangoMinimo()+i*dx, rangoMinimo()+(i+1)*dx, rangoMinimo()+(i+2)*dx);
		adicionarConjuntos(cd);
	}
	n =_("Set ");
	n << (num);
	sprintf(cad1,n.c_str());
	cd=new ConjuntoS(cad1, rangoMaximo()-2*dx, rangoMaximo()-dx, rangoMaximo());
	adicionarConjuntos(cd);
}


void Variable::autodefinirConjuntosRectosCortos(int num)
{
	if(num<2){return;}
	limpiarListaConjuntos();
	ConjuntoDifuso *cd;
	float dx;
			// esta variable ayuda a calcular los soportes
			//de cada ConjuntoDifuso

	dx=(rangoMaximo()-rangoMinimo())/(num-1);
	numeroIntervalos((num+1)*5);
			// Se asume que entre más ConjuntosDifusos,
			//se requiere un Intervalo de Evaluación más pequeño
	int i;
	char cad1[200];

			// El primer Conjunto es L, el último es Gamma
			// y los demás son Triángulo
	wxString n=_("Set ");
	n << (1);
	sprintf(cad1,n.c_str());
	cd=new ConjuntoL(cad1, rangoMinimo(), rangoMinimo(), rangoMinimo()+dx);
	adicionarConjuntos(cd);
	for (i=1;i<(num-1);i++)
	{
		n=_("Set ");
		n << (i+1);
		sprintf(cad1,n.c_str());
		cd=new ConjuntoTriangulo(cad1, rangoMinimo()+(i-1)*dx, rangoMinimo()+(i)*dx, rangoMinimo()+(i+1)*dx);
		adicionarConjuntos(cd);
	}
	n=_("Set ");
	n << (num);
	sprintf(cad1,n.c_str());
	cd=new ConjuntoGamma(cad1, rangoMaximo()-dx, rangoMaximo(), rangoMaximo());
	adicionarConjuntos(cd);
}

void Variable::autodefinirConjuntosCurvosCortos(int num)
{
	if(num<2){return;}
	limpiarListaConjuntos();
	ConjuntoDifuso *cd;
	float dx;
			// esta variable ayuda a calcular los soportes
			//de cada ConjuntoDifuso

	dx=(rangoMaximo()-rangoMinimo())/(num-1);
	numeroIntervalos((num+1)*5);
			// Se asume que entre más ConjuntosDifusos,
			//se requiere un Intervalo de Evaluación más pequeño
	int i;
	char cad1[200];
	wxString n=_("Set ");
	n << (1);
	sprintf(cad1,n.c_str());

			// El primer Conjunto es Z, el último es s
			// y los demás son Campana
	cd=new ConjuntoZ(cad1, rangoMinimo(), rangoMinimo(), rangoMinimo()+dx);
	adicionarConjuntos(cd);
	for (i=1;i<(num-1);i++)
	{
		n =_("Set ");
		n << (i+1);
		sprintf(cad1,n.c_str());
		cd=new ConjuntoCampana(cad1, rangoMinimo()+(i-1)*dx, rangoMinimo()+(i)*dx, rangoMinimo()+(i+1)*dx);
		adicionarConjuntos(cd);
	}
	n =_("Set ");
	n << (num);
	sprintf(cad1,n.c_str());
	cd=new ConjuntoS(cad1, rangoMaximo()-dx, rangoMaximo(), rangoMaximo());
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

void Variable::operator=(const Variable& other)
{
	strcpy(NombreVariable,other.NombreVariable);
	ajustar(other.RangoMinimo,other.RangoMaximo);
	RangoMinimo = other.RangoMinimo;
	RangoMaximo = other.RangoMaximo;
	numeroIntervalos(other.NumeroIntervalos);

//////CONJUNTOS

  while(numeroConjuntos()>0)
	{
		eliminarConjuntos(0);
	}
	for(int i=0;i<other.Conjuntos->GetItemsInContainer();i++)
	{
		ConjuntoDifuso* otherCd;
		otherCd=other.conjunto(i);
		float puntos[10];
		otherCd->puntosClaves(puntos);
		int identificador=otherCd->identificador();

		ConjuntoDifuso *cd;
		switch(identificador)
		{
			case 0 :	cd=new ConjuntoL         (otherCd->nombre(),RangoMinimo,puntos[0],puntos[1]);break;
			case 1 :  cd=new ConjuntoTriangulo (otherCd->nombre(),puntos[0],puntos[1],puntos[2]);break;
			case 2 :  cd=new ConjuntoPi        (otherCd->nombre(),puntos[0],puntos[1],puntos[2],puntos[3]);break;
			case 3 :  cd=new ConjuntoGamma     (otherCd->nombre(),puntos[0],puntos[1],RangoMaximo);break;
			case 4 :  cd=new ConjuntoZ         (otherCd->nombre(),RangoMinimo,puntos[0],puntos[1]);break;
			case 5 :  cd=new ConjuntoCampana   (otherCd->nombre(),puntos[0],puntos[1],puntos[2]);break;
			case 6 :  cd=new ConjuntoPiCampana (otherCd->nombre(),puntos[0],puntos[1],puntos[2],puntos[3]);break;
			case 7 :  cd=new ConjuntoS         (otherCd->nombre(),puntos[0],puntos[1],RangoMaximo);break;
			case 8 :  cd=new ConjuntoSinglenton(otherCd->nombre(),0.5*(puntos[0]+puntos[1]),(puntos[1]-puntos[0]));break;
			default : cd=new ConjuntoTriangulo (otherCd->nombre(),RangoMinimo,puntos[0],puntos[1]);break;
		}
		adicionarConjuntos(cd);

	}

////////// DIFUSOR
	float puntos[10];
	Difusor* otherDif;
	otherDif=other.difusorEntrada();
	int identificador=otherDif->identificador();
	float centro=otherDif->centro();
	otherDif->puntosClaves(puntos);

	Difusor *dif;
	switch(identificador)
	{
		case 1 :  dif=new DifusorTriangulo (centro,puntos[1]-puntos[0],puntos[2]-puntos[1]);break;
		case 2 :  dif=new DifusorPi        (centro,centro-puntos[0],centro-puntos[1],puntos[2]-centro,puntos[3]-centro);break;
		case 5 :  dif=new DifusorCampana   (centro,puntos[1]-puntos[0],puntos[2]-puntos[1]);break;
		case 6 :  dif=new DifusorPiCampana (centro,centro-puntos[0],centro-puntos[1],puntos[2]-centro,puntos[3]-centro);break;
		case 8 :  dif=new DifusorSinglenton(0.5*(puntos[0]+puntos[1]),(puntos[1]-puntos[0]));break;
		default : dif=new DifusorSinglenton(0.5*(puntos[0]+puntos[1]),(puntos[1]-puntos[0]));break;
	}
	dif->numeroPuntos(otherDif->numeroPuntos());
	difusorEntrada(dif);
}

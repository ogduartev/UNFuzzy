#include "MaquinaInferencia.h"

/*Este constructor crea un Conjunto Completo de Reglas*/
MaquinaInferencia::MaquinaInferencia(Universo *ent,Universo *sal)
{
	NumeroEntradas=ent->numeroVariables();
	NumeroSalidas =sal->numeroVariables();
	NumeroReglas=1;
/*El conjunto completo de reglas es el producto del número de Valores Linguisticos de cada Variable de Entrada*/
	int i;
	for(i=0;i<NumeroEntradas;i++)
	{
		NumeroReglas=NumeroReglas*Entradas->numeroConjuntosEnVariable(i);
	}
	MaquinaInferencia(ent,sal,NumeroReglas);
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

void MaquinaInferencia::adicionarEntrada()
{
	for(int i=0;i<numeroReglas();i++)
	{
		regla(i)->adicionarEntrada();
	}
	NumeroEntradas++;
}

void MaquinaInferencia::adicionarSalida()
{
	for(int i=0;i<numeroReglas();i++)
	{
		regla(i)->adicionarSalida();
	}
	NumeroSalidas++;
}

void MaquinaInferencia::eliminarEntrada(int NumVar)
{
	for(int i=0;i<numeroReglas();i++)
	{
		regla(i)->eliminarEntrada(NumVar);
	}
	NumeroEntradas--;
}

void MaquinaInferencia::eliminarSalida(int NumVar)
{
	for(int i=0;i<numeroReglas();i++)
	{
		regla(i)->eliminarSalida(NumVar);
	}
	NumeroSalidas--;
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
		char cad[200];
		wxString n=_("Set ");
		n << Entradas->variable(i)->numeroConjuntos();
		sprintf(cad,n.c_str());
		switch(tipoConjunto)
		{
			case 0 : conj=new ConjuntoL(cad,puntos[0],puntos[1],puntos[2]);
						break;
			case 1 : conj=new ConjuntoTriangulo(cad,puntos[0],puntos[1],puntos[2]);
						break;
			case 2 : conj=new ConjuntoPi(cad,puntos[0],puntos[1],puntos[2],puntos[3]);
						break;
			case 3 : conj=new ConjuntoGamma(cad,puntos[0],puntos[1],puntos[2]);
						break;
			case 4 : conj=new ConjuntoZ(cad,puntos[0],puntos[1],puntos[2]);
						break;
			case 5 : conj=new ConjuntoCampana(cad,puntos[0],puntos[1],puntos[2]);
						break;
			case 6 : conj=new ConjuntoS(cad,puntos[0],puntos[1],puntos[2]);
						break;
			case 7 : conj=new ConjuntoPiCampana(cad,puntos[0],puntos[1],puntos[2],puntos[3]);
						break;
			case 8 : conj=new ConjuntoSinglenton(cad,puntos[0],puntos[1]);
						break;
			case 9 :// conj=new ConjuntoPorPuntos(cad,,,); //min,max,float *dt, int puntos
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
		char cad[200];
		wxString n=_("Set ");
		n << (Salidas->variable(i)->numeroConjuntos());
		sprintf(cad,n.c_str());
		switch(tipoConjunto)
		{
			case 0 : conj=new ConjuntoL(cad,puntos[0],puntos[1],puntos[2]);
						break;
			case 1 : conj=new ConjuntoTriangulo(cad,puntos[0],puntos[1],puntos[2]);
						break;
			case 2 : conj=new ConjuntoPi(cad,puntos[0],puntos[1],puntos[2],puntos[3]);
						break;
			case 3 : conj=new ConjuntoGamma(cad,puntos[0],puntos[1],puntos[2]);
						break;
			case 4 : conj=new ConjuntoZ(cad,puntos[0],puntos[1],puntos[2]);
						break;
			case 5 : conj=new ConjuntoCampana(cad,puntos[0],puntos[1],puntos[2]);
						break;
			case 6 : conj=new ConjuntoS(cad,puntos[0],puntos[1],puntos[2]);
						break;
			case 7 : conj=new ConjuntoPiCampana(cad,puntos[0],puntos[1],puntos[2],puntos[3]);
						break;
			case 8 : conj=new ConjuntoSinglenton(cad,puntos[0],puntos[1]);
						break;
			case 9 :// conj=new ConjuntoPorPuntos(cad,,,); //min,max,float *dt, int puntos
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

void MaquinaInferencia::llenarEntradasBase()
{
   	int i,numReg;
	numReg=BaseReglas->GetItemsInContainer();
	for(i=0;i<numReg;i++)
	{
		eliminarRegla(0);
	}
/*El conjunto completo de reglas es el producto del número de Valores Linguisticos de cada Variable de Entrada*/
	NumeroReglas=1;
	for(i=0;i<NumeroEntradas;i++)
	{
		NumeroReglas=NumeroReglas*Entradas->numeroConjuntosEnVariable(i);
	}
	Regla *rg;
	int error=0;
	for(i=0;i<NumeroReglas;i++)
	{
		try{
			rg=new Regla(NumeroEntradas,NumeroSalidas);
		}catch(...)
		{
			error=1;
		}
		if(error==0)
		{
			BaseReglas->Add(rg);
		}
	}
/*fija los antecedentes en 0*/
	int j;
	for(i=0;i<numeroReglas();i++)
	{
		for(j=0;j<numeroEntradas();j++)
		{
			conjuntoEntrada(i,j,0);
		}
	}
/*maximo[] guarda el numero de Valores Linguisticos de cada Variable de entrada*/
/*conteo[] se incrementa para poder llenar una tabla como la siguiente:
    Supóngase 3 Variables de entrada, con 2,3 y 2 Valores Linguisticos respectivamente

        0   0   0
        0   0   1
        0   1   0
        0   1   1
		  0   2   0
        0   2   1
        1   0   0
        1   0   1
        1   1   0
        1   1   1
        1   2   0
        1   2   1

*/

	int *maximo;
	int *conteo;
	maximo=new int[NumeroEntradas];
	conteo=new int[NumeroEntradas];
	int k;
	int cambios;
/*la variable cambios determina si debe incrementarse conteo[]*/
	for(i=0;i<NumeroEntradas;i++)
	{
		conteo[i]=-1;
		maximo[i]=Entradas->numeroConjuntosEnVariable(i);
        /*aquí se llena maximo[] y se presetea conteo[]*/
	}
	for (i=NumeroEntradas-1;i>=0;i--)
	{
		for(j=0;j<NumeroReglas;j++)
		{
			cambios=1;
			for(k=i+1;k<NumeroEntradas;k++)
			{
				if(numConjuntoEntrada(j,k)!=0)
				{
					cambios=0;
				}
			}
			if(cambios==1)
			{
                /*si cambios==1 debe incrementarse conteo[]*/
				conteo[i]=conteo[i]+1;
				if(conteo[i]==maximo[i])
				{
					conteo[i]=0;
				}
			}
			conjuntoEntrada(j,i,conteo[i]);
            /*aquí se asigna el antecedente*/
		}
	}
	delete[] maximo;
	delete[] conteo;



}

void MaquinaInferencia::llenarModificadoresBase()
{
	int i,j;
	for(i=0;i<numeroReglas();i++)
	{
		for(j=0;j<numeroEntradas();j++)
		{
			modificador(i,j,1.0);
		}
	}
}

void MaquinaInferencia::llenarSalidasBaseCreciente()
{
/*la tendencia creciente se maneja con el parametro ŽfactorŽ, que
utiliza el número de los conjuntos de antecedente en relación al nùmero
máximo de Valores Linguisticos*/
	int i,j,numConj;
	float NumeroConj=1;
	for(i=0;i<NumeroEntradas;i++)
	{
		NumeroConj=NumeroConj+Entradas->numeroConjuntosEnVariable(i);
	}
	for(j=0;j<NumeroReglas;j++)
	{
		float factor=1;
		for(i=0;i<NumeroEntradas;i++)
		{
			factor=factor+numConjuntoEntrada(j,i);
		}
		factor=factor/NumeroConj;
		for(i=0;i<NumeroSalidas;i++)
		{
			numConj=(int)(factor*Salidas->numeroConjuntosEnVariable(i));
			conjuntoSalida(j,i,numConj);
		}
	}
}

void MaquinaInferencia::llenarSalidasBaseDecreciente()
{
/*El algoritmo es similar al de base Creciente*/
	int i,j,numConj;
	float NumeroConj=1;
	for(i=0;i<NumeroEntradas;i++)
	{
		NumeroConj=NumeroConj+Entradas->numeroConjuntosEnVariable(i);
	}
	for(j=0;j<NumeroReglas;j++)
	{
		float factor=1;
		for(i=0;i<NumeroEntradas;i++)
		{
			factor=factor+numConjuntoEntrada(j,i);
		}
		factor=factor/NumeroConj;
		for(i=0;i<NumeroSalidas;i++)
		{
			numConj=(int)(factor*Salidas->numeroConjuntosEnVariable(i));
			numConj=Salidas->numeroConjuntosEnVariable(i)-numConj;
            /*ésta es la diferencia entre las tendencias creciente y decreciente*/
			conjuntoSalida(j,i,numConj);
		}
	}
}

void MaquinaInferencia::llenarSalidaCreciente(int NumVar)
{
	int i,j,numConj;
	float NumeroConj=1;
	for(i=0;i<NumeroEntradas;i++)
	{
		NumeroConj=NumeroConj+Entradas->numeroConjuntosEnVariable(i);
	}
	for(j=0;j<NumeroReglas;j++)
	{
		float factor=1;
		for(i=0;i<NumeroEntradas;i++)
		{
			factor=factor+numConjuntoEntrada(j,i);
		}
		factor=factor/NumeroConj;
		i=NumVar;
		numConj=(int)(factor*Salidas->numeroConjuntosEnVariable(i));
		conjuntoSalida(j,i,numConj);
	}
}

void MaquinaInferencia::llenarSalidaDecreciente(int NumVar)
{
	int i,j,numConj;
	float NumeroConj=1;
	for(i=0;i<NumeroEntradas;i++)
	{
		NumeroConj=NumeroConj+Entradas->numeroConjuntosEnVariable(i);
	}
	for(j=0;j<NumeroReglas;j++)
	{
		float factor=1;
		for(i=0;i<NumeroEntradas;i++)
		{
			factor=factor+numConjuntoEntrada(j,i);
		}
		factor=factor/NumeroConj;
		i=NumVar;
		numConj=(int)(factor*Salidas->numeroConjuntosEnVariable(i));
		numConj=Salidas->numeroConjuntosEnVariable(i)-1-numConj;
		conjuntoSalida(j,i,numConj);
	}
}

void MaquinaInferencia::llenarSalidaConstante(int NumVar,int NumCon)
{
	int j;
	for(j=0;j<NumeroReglas;j++)
	{
		conjuntoSalida(j,NumVar,NumCon);
	}
}

void MaquinaInferencia::etiquetaEliminada(bool flagEntrada,int NumVar,int NumCon)
{
	if(flagEntrada)
	{
		for(int j=0;j<NumeroReglas;j++)
		{
			int et=numConjuntoEntrada(j,NumVar);
			if(et == NumCon)
			{
			  conjuntoEntrada(j,NumVar,0);
			}
			if(et > NumCon)
			{
			  conjuntoEntrada(j,NumVar,et-1);
			}
		}
	}else
	{
		for(int j=0;j<NumeroReglas;j++)
		{
			int et=numConjuntoSalida(j,NumVar);
			if(et == NumCon)
			{
			  conjuntoSalida(j,NumVar,0);
			}
			if(et > NumCon)
			{
			  conjuntoSalida(j,NumVar,et-1);
			}
		}
	}
}

void MaquinaInferencia::limpiaAntesUniversoFijo()
{
	desocuparBaseReglas();
	eliminarRegla(0);
}

void MaquinaInferencia::limpiaAntesUniversoVariable()
{
	limpiaAntesUniversoFijo();
	int i;
	for(i=0;i<numeroEntradas();i++)
	{
		int numConj;
		int j;
		numConj=entradas()->variable(i)->numeroConjuntos();
		for(j=1;j<numConj;j++)
		{
			entradas()->variable(i)->eliminarConjuntos(1);
		}
		entradas()->variable(i)->conjunto(0)->nombre(_("Set base"));
	}
	for(i=0;i<numeroSalidas();i++)
	{
		int numConj;
		int j;
		numConj=salidas()->variable(i)->numeroConjuntos();
		for(j=1;j<numConj;j++)
		{
			salidas()->variable(i)->eliminarConjuntos(1);
		}
		salidas()->variable(i)->conjunto(0)->nombre(_("Set base"));
	}

}

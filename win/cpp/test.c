// Código C del Sistema de Lógica Difusa

// Generado automáticamente por UNFUZZY V 3.0
// Autor: Oscar Duarte (ogduartev@unal.edu.co)
// Universidad Nacional de Colombia
// Descargo de responsabilidad: 
// El código generado se usa bajo responsabilidad del usuario.
// En ninguna forma genera responsabilidad para el autor de UNFUZZY
// ni para la Universidad Nacional de Colombia.
// 
// para compilar el archivo xxx.c:
//   g++ xxx.c

#include <stdio.h>
#include <string.h>
#include <math.h>

#define NUMEROREGLAS                 27
#define NUMEROVARIABLESENTRADA       3
#define NUMEROVARIABLESSALIDA        2
#define NUMEROTOTALCONJUNTOSENTRADA  9

struct conjunto{
	char nombre[40];
	float minimo;
	float maximo;
};

struct variable{
	char nombre[40];
	float minimo;
	float maximo;
	int intervalos;
	float intervalo;
	int numeroConjuntos;
};

struct difusor{
	float minimo;
	float maximo;
	float centro;
	float var1;
	float var2;
	float var3;
	float var4;
	int puntos;
	float intervalo;
};

struct variable VariablesEntrada[NUMEROVARIABLESENTRADA];
struct variable VariablesSalida[NUMEROVARIABLESSALIDA];
struct conjunto Entradas[NUMEROTOTALCONJUNTOSENTRADA];
struct difusor Difusores[NUMEROTOTALCONJUNTOSENTRADA];
int Reglas[NUMEROREGLAS][NUMEROVARIABLESENTRADA+NUMEROVARIABLESSALIDA];
float Modificadores[NUMEROREGLAS][NUMEROVARIABLESENTRADA];
float CentrosAltura[NUMEROREGLAS][NUMEROVARIABLESSALIDA];
void llenarDatos();
void llenarVariablesEntrada();
void llenarVariablesSalida();
void llenarEntradas();
void llenarDifusores();
void llenarReglas();
void llenarModificadores();
void llenarCentrosAltura();
void calcular(float *ent,float *sal);
float salidaConcreta(int NumeroSalida, float *entra);
float salidaConcreta0(float *entra);
float salidaConcreta1(float *entra);

float pertenenciaComposicion(int numVar, int numRegla, float sal);
float pertenenciaDifusores(float *ent);
float pertenenciaImplicacion(int numSal, int numRegla,float *ent, float sal);
float pertenenciaConsecuente(int numSal, int numRegla, float sal);
float pertenenciaAntecedente(int numRegla, float *ent);
int activarRegla(int numRegla);
float pertenenciaDifusor(int numVar, float x);
float pertenenciaVariableEntrada(int numVar,int numConj, float x);
float pertenenciaVariableSalida(int numVar,int numConj, float x);

int indiceEntradas(int numRegla,int numVar);
void actualizarEntradas(float *ent);
float Implicacion(float x,float y);
float Composicion(float x,float y);
float Conjuncion(float x,float y);
float And(float x,float y);

int main()
{
    float entra[NUMEROVARIABLESENTRADA];
    float sale[NUMEROVARIABLESSALIDA];
    char q='s';
    llenarDatos();
    while(q=='s')
    {
        int i;
        for(i=0;i<NUMEROVARIABLESENTRADA;i++)
        {
            float e;
            printf("%s : ",VariablesEntrada[i].nombre);
            scanf("%f",&e);
            entra[i]=e;
        }
        calcular(entra,sale);
        for(i=0;i<NUMEROVARIABLESSALIDA;i++)
        {
            printf("%s : ",VariablesSalida[i].nombre);
            printf("%f : \n",sale[i]);
        }

        fflush(stdin);
        scanf("%c",&q);
    }
}
void llenarDatos()
{
    llenarVariablesEntrada();
    llenarVariablesSalida();
    llenarEntradas();
    llenarDifusores();
    llenarReglas();
    llenarModificadores();
    llenarCentrosAltura();
}
void calcular(float *entra, float *sale)
{
    int i;
    for(i=0;i<NUMEROVARIABLESSALIDA;i++)
    {
        sale[i]=salidaConcreta(i,entra);
    }
}
void actualizarEntradas(float *ent)
{
    float dx;
    int i;
    for(i=0;i<NUMEROVARIABLESENTRADA;i++)
    {
        dx=ent[i]-Difusores[i].centro;
        Difusores[i].centro=Difusores[i].centro+dx;
        Difusores[i].minimo=Difusores[i].minimo+dx;
        Difusores[i].maximo=Difusores[i].maximo+dx;
        Difusores[i].var1=Difusores[i].var1+dx;
        Difusores[i].var2=Difusores[i].var2+dx;
        Difusores[i].var3=Difusores[i].var3+dx;
        Difusores[i].var4=Difusores[i].var4+dx;
    }
}
int indiceEntradas(int numVar,int numConj)
{
    int contador=0;
    int i;
    for(i=0;i<numVar;i++)
    {
        contador=contador+VariablesEntrada[i].numeroConjuntos;
    }
    contador=contador+numConj;
    return contador;
}
float pertenenciaComposicion(int numVar,int numRegla, float sal)
{
    float ux;
    float uxa;
    float uxab;
    float comp=0;
    float x[NUMEROVARIABLESENTRADA];
    int inter[NUMEROVARIABLESENTRADA];
    if(!activarRegla(numRegla))
    {
        comp=Implicacion(0,0);
    }
    else{
        int casos=1;
        int i;
        for(i=0;i<NUMEROVARIABLESENTRADA;i++)
        {
            casos=casos*Difusores[i].puntos;
            inter[i]=1;
        }
        for(i=0;i<NUMEROVARIABLESENTRADA;i++)
        {
            int k;
            for(k=0;k<NUMEROVARIABLESENTRADA;k++)
            {
                x[k]=Difusores[k].minimo+Difusores[k].intervalo*inter[k];
                inter[k]=inter[k]+1;
                if(inter[k]>=Difusores[k].puntos)
                {
                    inter[k]=1;
                }
            }
            uxab=pertenenciaImplicacion(numVar,numRegla,x,sal);
            uxa=pertenenciaDifusores(x);
            ux=Composicion(uxa,uxab);
            if(ux>comp)
            {
                comp=ux;
            }
        }
    }
    return comp;
}
float pertenenciaDifusores(float *ent)
{
    float uxd;
    int j=0;
    uxd=pertenenciaDifusor(j,ent[j]);
    for(j=0;j<NUMEROVARIABLESENTRADA;j++)
    {
    uxd=And(uxd,pertenenciaDifusor(j,ent[j]));
    }
    return uxd;
}
float pertenenciaImplicacion(int numSal,int numRegla,float *ent,float sal)
{
    float uxa,uxb;
    uxa=pertenenciaAntecedente(numRegla,ent);
    uxb=pertenenciaConsecuente(numSal,numRegla,sal);
    return Implicacion(uxa,uxb);
}
float pertenenciaConsecuente(int numSal,int numRegla,float sal)
{
    float uxc;
    int conj;
    conj=Reglas[numRegla][NUMEROVARIABLESENTRADA+numSal];
    uxc=pertenenciaVariableSalida(numSal,conj,sal);
    return uxc;
}
float pertenenciaAntecedente(int numRegla,float *ent)
{
    float ux;
    float uxa;
    int conj;
    int j=0;
    conj=Reglas[numRegla][0];
    ux=pertenenciaVariableEntrada(j,conj,ent[j]);
    if(Modificadores[numRegla][0]>0.0)
    {
        uxa=pow(ux,Modificadores[numRegla][0]);
    }else
    {
        uxa=1;
    }
    for(j=1;j<NUMEROVARIABLESENTRADA;j++)
    {
        conj=Reglas[numRegla][j];
        ux=pertenenciaVariableEntrada(j,conj,ent[j]);
        if(Modificadores[numRegla][j]>0.0)
        {
            ux=pow(ux,Modificadores[numRegla][j]);
        }else
        {
            ux=1;
        }
        uxa=And(uxa,ux);
    }
    return uxa;
}
int activarRegla(int numRegla)
{
    int i;
    for(i=0;i<NUMEROVARIABLESENTRADA;i++)
    {
        float bmn,bmx,cmn,cmx;
        int numCon;
        int indice;
        numCon=Reglas[numRegla][i];
        indice=indiceEntradas(i,numCon);
        bmn=Entradas[indice].minimo;
        bmx=Entradas[indice].maximo;
        cmn=Difusores[i].minimo;
        cmx=Difusores[i].maximo;
        if(bmn>cmx||bmx<cmn)
            return 0;
    }
    return 1;
}
float salidaConcreta(int NumeroSalida,float *ent)
{
    float respuesta;
    switch(NumeroSalida)
    {
        case 0 : respuesta=salidaConcreta0(ent);break;
        case 1 : respuesta=salidaConcreta1(ent);break;
        default:respuesta=0;break;
    }
    return respuesta;
}
float salidaConcreta0(float *ent)
{
    int NumeroSalida=0;
    float con=0.000000;
    float y;
    float y1=0;
    float y2=0;
    float ymax;
    int i;
    int j;
    ymax=VariablesSalida[NumeroSalida].minimo;
    actualizarEntradas(ent);
    for(i=0;i<(VariablesSalida[NumeroSalida].intervalos+1);i++)
    {
        float con=0.000000;
        y=VariablesSalida[NumeroSalida].minimo+i*VariablesSalida[NumeroSalida].intervalo;
        for(j=0;j<NUMEROREGLAS;j++)
        {
            float temp;
            temp=pertenenciaComposicion(NumeroSalida,j,y);
            con=Conjuncion(con,temp);
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

float salidaConcreta1(float *ent)
{
    int NumeroSalida=1;
    float con=0.000000;
    float y;
    float y1=0;
    float y2=0;
    float ymax;
    int i;
    int j;
    ymax=VariablesSalida[NumeroSalida].minimo;
    actualizarEntradas(ent);
    for(i=0;i<(VariablesSalida[NumeroSalida].intervalos+1);i++)
    {
        float con=0.000000;
        y=VariablesSalida[NumeroSalida].minimo+i*VariablesSalida[NumeroSalida].intervalo;
        for(j=0;j<NUMEROREGLAS;j++)
        {
            float temp;
            temp=pertenenciaComposicion(NumeroSalida,j,y);
            con=Conjuncion(con,temp);
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

void llenarVariablesEntrada()
{
    strcpy(VariablesEntrada[0].nombre,"Entrada 1");
    VariablesEntrada[0].minimo=-1.000000;
    VariablesEntrada[0].maximo=1.000000;
    VariablesEntrada[0].intervalos=20;
    VariablesEntrada[0].intervalo=0.100000;
    VariablesEntrada[0].numeroConjuntos=3;
    strcpy(VariablesEntrada[1].nombre,"Entrada 2");
    VariablesEntrada[1].minimo=-1.000000;
    VariablesEntrada[1].maximo=1.000000;
    VariablesEntrada[1].intervalos=20;
    VariablesEntrada[1].intervalo=0.100000;
    VariablesEntrada[1].numeroConjuntos=3;
    strcpy(VariablesEntrada[2].nombre,"Entrada 3");
    VariablesEntrada[2].minimo=-1.000000;
    VariablesEntrada[2].maximo=1.000000;
    VariablesEntrada[2].intervalos=20;
    VariablesEntrada[2].intervalo=0.100000;
    VariablesEntrada[2].numeroConjuntos=3;
}

void llenarVariablesSalida()
{
    strcpy(VariablesSalida[0].nombre,"Salida 1");
    VariablesSalida[0].minimo=-1.000000;
    VariablesSalida[0].maximo=1.000000;
    VariablesSalida[0].intervalos=20;
    VariablesSalida[0].intervalo=0.100000;
    VariablesSalida[0].numeroConjuntos=3;
    strcpy(VariablesSalida[1].nombre,"Salida 2");
    VariablesSalida[1].minimo=-1.000000;
    VariablesSalida[1].maximo=1.000000;
    VariablesSalida[1].intervalos=20;
    VariablesSalida[1].intervalo=0.100000;
    VariablesSalida[1].numeroConjuntos=3;
}
void llenarEntradas()
{
    Entradas[0].minimo=-1.000000;
    Entradas[0].maximo=0.000000;
    Entradas[1].minimo=-0.500000;
    Entradas[1].maximo=0.500000;
    Entradas[2].minimo=0.000000;
    Entradas[2].maximo=1.000000;
    Entradas[3].minimo=-1.000000;
    Entradas[3].maximo=0.000000;
    Entradas[4].minimo=-0.500000;
    Entradas[4].maximo=0.500000;
    Entradas[5].minimo=0.000000;
    Entradas[5].maximo=1.000000;
    Entradas[6].minimo=-1.000000;
    Entradas[6].maximo=0.000000;
    Entradas[7].minimo=-0.500000;
    Entradas[7].maximo=0.500000;
    Entradas[8].minimo=0.000000;
    Entradas[8].maximo=1.000000;
}
void llenarDifusores()
{
    Difusores[0].minimo=-0.005000;
    Difusores[0].maximo=0.005000;
    Difusores[0].centro=0.000000;
    Difusores[0].puntos=1;
    Difusores[0].intervalo=0.000000;
    Difusores[0].var1=-0.005000;
    Difusores[0].var2=0.005000;
    Difusores[0].var3=0.000000;
    Difusores[0].var4=0.000000;
    Difusores[1].minimo=-0.005000;
    Difusores[1].maximo=0.005000;
    Difusores[1].centro=0.000000;
    Difusores[1].puntos=1;
    Difusores[1].intervalo=0.000000;
    Difusores[1].var1=-0.005000;
    Difusores[1].var2=0.005000;
    Difusores[1].var3=0.000000;
    Difusores[1].var4=0.000000;
    Difusores[2].minimo=-0.005000;
    Difusores[2].maximo=0.005000;
    Difusores[2].centro=0.000000;
    Difusores[2].puntos=1;
    Difusores[2].intervalo=0.000000;
    Difusores[2].var1=-0.005000;
    Difusores[2].var2=0.005000;
    Difusores[2].var3=0.000000;
    Difusores[2].var4=0.000000;
}
void llenarReglas()
{
Reglas[0][0]=0;
Reglas[0][1]=0;
Reglas[0][2]=0;
Reglas[0][3]=0;
Reglas[0][4]=0;

Reglas[1][0]=0;
Reglas[1][1]=0;
Reglas[1][2]=1;
Reglas[1][3]=0;
Reglas[1][4]=0;

Reglas[2][0]=0;
Reglas[2][1]=0;
Reglas[2][2]=2;
Reglas[2][3]=0;
Reglas[2][4]=0;

Reglas[3][0]=0;
Reglas[3][1]=1;
Reglas[3][2]=0;
Reglas[3][3]=0;
Reglas[3][4]=0;

Reglas[4][0]=0;
Reglas[4][1]=1;
Reglas[4][2]=1;
Reglas[4][3]=0;
Reglas[4][4]=0;

Reglas[5][0]=0;
Reglas[5][1]=1;
Reglas[5][2]=2;
Reglas[5][3]=1;
Reglas[5][4]=1;

Reglas[6][0]=0;
Reglas[6][1]=2;
Reglas[6][2]=0;
Reglas[6][3]=0;
Reglas[6][4]=0;

Reglas[7][0]=0;
Reglas[7][1]=2;
Reglas[7][2]=1;
Reglas[7][3]=1;
Reglas[7][4]=1;

Reglas[8][0]=0;
Reglas[8][1]=2;
Reglas[8][2]=2;
Reglas[8][3]=1;
Reglas[8][4]=1;

Reglas[9][0]=1;
Reglas[9][1]=0;
Reglas[9][2]=0;
Reglas[9][3]=0;
Reglas[9][4]=0;

Reglas[10][0]=1;
Reglas[10][1]=0;
Reglas[10][2]=1;
Reglas[10][3]=0;
Reglas[10][4]=0;

Reglas[11][0]=1;
Reglas[11][1]=0;
Reglas[11][2]=2;
Reglas[11][3]=1;
Reglas[11][4]=1;

Reglas[12][0]=1;
Reglas[12][1]=1;
Reglas[12][2]=0;
Reglas[12][3]=0;
Reglas[12][4]=0;

Reglas[13][0]=1;
Reglas[13][1]=1;
Reglas[13][2]=1;
Reglas[13][3]=1;
Reglas[13][4]=1;

Reglas[14][0]=1;
Reglas[14][1]=1;
Reglas[14][2]=2;
Reglas[14][3]=1;
Reglas[14][4]=1;

Reglas[15][0]=1;
Reglas[15][1]=2;
Reglas[15][2]=0;
Reglas[15][3]=1;
Reglas[15][4]=1;

Reglas[16][0]=1;
Reglas[16][1]=2;
Reglas[16][2]=1;
Reglas[16][3]=1;
Reglas[16][4]=1;

Reglas[17][0]=1;
Reglas[17][1]=2;
Reglas[17][2]=2;
Reglas[17][3]=1;
Reglas[17][4]=1;

Reglas[18][0]=2;
Reglas[18][1]=0;
Reglas[18][2]=0;
Reglas[18][3]=0;
Reglas[18][4]=0;

Reglas[19][0]=2;
Reglas[19][1]=0;
Reglas[19][2]=1;
Reglas[19][3]=1;
Reglas[19][4]=1;

Reglas[20][0]=2;
Reglas[20][1]=0;
Reglas[20][2]=2;
Reglas[20][3]=1;
Reglas[20][4]=1;

Reglas[21][0]=2;
Reglas[21][1]=1;
Reglas[21][2]=0;
Reglas[21][3]=1;
Reglas[21][4]=1;

Reglas[22][0]=2;
Reglas[22][1]=1;
Reglas[22][2]=1;
Reglas[22][3]=1;
Reglas[22][4]=1;

Reglas[23][0]=2;
Reglas[23][1]=1;
Reglas[23][2]=2;
Reglas[23][3]=1;
Reglas[23][4]=1;

Reglas[24][0]=2;
Reglas[24][1]=2;
Reglas[24][2]=0;
Reglas[24][3]=1;
Reglas[24][4]=1;

Reglas[25][0]=2;
Reglas[25][1]=2;
Reglas[25][2]=1;
Reglas[25][3]=1;
Reglas[25][4]=1;

Reglas[26][0]=2;
Reglas[26][1]=2;
Reglas[26][2]=2;
Reglas[26][3]=2;
Reglas[26][4]=2;

}

void llenarModificadores()
{
Modificadores[0][0]=1.000000;
Modificadores[0][1]=1.000000;
Modificadores[0][2]=1.000000;

Modificadores[1][0]=1.000000;
Modificadores[1][1]=1.000000;
Modificadores[1][2]=1.000000;

Modificadores[2][0]=1.000000;
Modificadores[2][1]=1.000000;
Modificadores[2][2]=1.000000;

Modificadores[3][0]=1.000000;
Modificadores[3][1]=1.000000;
Modificadores[3][2]=1.000000;

Modificadores[4][0]=1.000000;
Modificadores[4][1]=1.000000;
Modificadores[4][2]=1.000000;

Modificadores[5][0]=1.000000;
Modificadores[5][1]=1.000000;
Modificadores[5][2]=1.000000;

Modificadores[6][0]=1.000000;
Modificadores[6][1]=1.000000;
Modificadores[6][2]=1.000000;

Modificadores[7][0]=1.000000;
Modificadores[7][1]=1.000000;
Modificadores[7][2]=1.000000;

Modificadores[8][0]=1.000000;
Modificadores[8][1]=1.000000;
Modificadores[8][2]=1.000000;

Modificadores[9][0]=1.000000;
Modificadores[9][1]=1.000000;
Modificadores[9][2]=1.000000;

Modificadores[10][0]=1.000000;
Modificadores[10][1]=1.000000;
Modificadores[10][2]=1.000000;

Modificadores[11][0]=1.000000;
Modificadores[11][1]=1.000000;
Modificadores[11][2]=1.000000;

Modificadores[12][0]=1.000000;
Modificadores[12][1]=1.000000;
Modificadores[12][2]=1.000000;

Modificadores[13][0]=1.000000;
Modificadores[13][1]=1.000000;
Modificadores[13][2]=1.000000;

Modificadores[14][0]=1.000000;
Modificadores[14][1]=1.000000;
Modificadores[14][2]=1.000000;

Modificadores[15][0]=1.000000;
Modificadores[15][1]=1.000000;
Modificadores[15][2]=1.000000;

Modificadores[16][0]=1.000000;
Modificadores[16][1]=1.000000;
Modificadores[16][2]=1.000000;

Modificadores[17][0]=1.000000;
Modificadores[17][1]=1.000000;
Modificadores[17][2]=1.000000;

Modificadores[18][0]=1.000000;
Modificadores[18][1]=1.000000;
Modificadores[18][2]=1.000000;

Modificadores[19][0]=1.000000;
Modificadores[19][1]=1.000000;
Modificadores[19][2]=1.000000;

Modificadores[20][0]=1.000000;
Modificadores[20][1]=1.000000;
Modificadores[20][2]=1.000000;

Modificadores[21][0]=1.000000;
Modificadores[21][1]=1.000000;
Modificadores[21][2]=1.000000;

Modificadores[22][0]=1.000000;
Modificadores[22][1]=1.000000;
Modificadores[22][2]=1.000000;

Modificadores[23][0]=1.000000;
Modificadores[23][1]=1.000000;
Modificadores[23][2]=1.000000;

Modificadores[24][0]=1.000000;
Modificadores[24][1]=1.000000;
Modificadores[24][2]=1.000000;

Modificadores[25][0]=1.000000;
Modificadores[25][1]=1.000000;
Modificadores[25][2]=1.000000;

Modificadores[26][0]=1.000000;
Modificadores[26][1]=1.000000;
Modificadores[26][2]=1.000000;

}
void llenarCentrosAltura()
{
CentrosAltura[0][0]=-0.750000;
CentrosAltura[0][1]=-0.750000;

CentrosAltura[1][0]=-0.750000;
CentrosAltura[1][1]=-0.750000;

CentrosAltura[2][0]=-0.750000;
CentrosAltura[2][1]=-0.750000;

CentrosAltura[3][0]=-0.750000;
CentrosAltura[3][1]=-0.750000;

CentrosAltura[4][0]=-0.750000;
CentrosAltura[4][1]=-0.750000;

CentrosAltura[5][0]=0.000000;
CentrosAltura[5][1]=0.000000;

CentrosAltura[6][0]=-0.750000;
CentrosAltura[6][1]=-0.750000;

CentrosAltura[7][0]=0.000000;
CentrosAltura[7][1]=0.000000;

CentrosAltura[8][0]=0.000000;
CentrosAltura[8][1]=0.000000;

CentrosAltura[9][0]=-0.750000;
CentrosAltura[9][1]=-0.750000;

CentrosAltura[10][0]=-0.750000;
CentrosAltura[10][1]=-0.750000;

CentrosAltura[11][0]=0.000000;
CentrosAltura[11][1]=0.000000;

CentrosAltura[12][0]=-0.750000;
CentrosAltura[12][1]=-0.750000;

CentrosAltura[13][0]=0.000000;
CentrosAltura[13][1]=0.000000;

CentrosAltura[14][0]=0.000000;
CentrosAltura[14][1]=0.000000;

CentrosAltura[15][0]=0.000000;
CentrosAltura[15][1]=0.000000;

CentrosAltura[16][0]=0.000000;
CentrosAltura[16][1]=0.000000;

CentrosAltura[17][0]=0.000000;
CentrosAltura[17][1]=0.000000;

CentrosAltura[18][0]=-0.750000;
CentrosAltura[18][1]=-0.750000;

CentrosAltura[19][0]=0.000000;
CentrosAltura[19][1]=0.000000;

CentrosAltura[20][0]=0.000000;
CentrosAltura[20][1]=0.000000;

CentrosAltura[21][0]=0.000000;
CentrosAltura[21][1]=0.000000;

CentrosAltura[22][0]=0.000000;
CentrosAltura[22][1]=0.000000;

CentrosAltura[23][0]=0.000000;
CentrosAltura[23][1]=0.000000;

CentrosAltura[24][0]=0.000000;
CentrosAltura[24][1]=0.000000;

CentrosAltura[25][0]=0.000000;
CentrosAltura[25][1]=0.000000;

CentrosAltura[26][0]=0.750000;
CentrosAltura[26][1]=0.750000;

}

float pertenenciaDifusor(int numVar, float x)
{
    float ux=0;
    switch(numVar)
    {
        case 0:
            if(x<Difusores[0].var1)
            	ux=0;
            if(x<Difusores[0].var2&&x>=Difusores[0].var1)
            	ux=1;
            if(x>=Difusores[0].var2)
            	ux=0;
            break;
        case 1:
            if(x<Difusores[1].var1)
            	ux=0;
            if(x<Difusores[1].var2&&x>=Difusores[1].var1)
            	ux=1;
            if(x>=Difusores[1].var2)
            	ux=0;
            break;
        case 2:
            if(x<Difusores[2].var1)
            	ux=0;
            if(x<Difusores[2].var2&&x>=Difusores[2].var1)
            	ux=1;
            if(x>=Difusores[2].var2)
            	ux=0;
            break;
        default:break;
    }
    return ux;
}
float pertenenciaVariableEntrada(int numVar,int numConj, float x)
{
    float ux=0;
    switch(numVar)
    {
        case 0:
            switch(numConj)
            {
            case 0:
                        if(x<(-1.000000))
                            ux=1;
                        if(x<(-0.500000)&&x>=(-1.000000))
                            ux=1;
                        if(x<(0.000000)&&x>=(-0.500000))
                            ux=((0.000000)-x)/((0.000000)-(-0.500000));
                        if(x>=(0.000000))
                            ux=0;
                        if(ux<0.0001)
                            ux=0;
                break;
            case 1:
                        if(x<(-0.500000))
                            ux=0;
                        if(x<(0.000000)&&x>=(-0.500000))
                            ux=(x-(-0.500000))/((0.000000)-(-0.500000));
                        if(x<(0.500000)&&x>=(0.000000))
                            ux=((0.500000)-x)/((0.500000)-(0.000000));
                        if(x>=(0.500000))
                            ux=0;
                        if(ux<0.0001)
                            ux=0;

                break;
            case 2:
                        if(x<(0.000000))
                            ux=0;
                        if(x<(0.500000)&&x>=(0.000000))
                            ux=(x-(0.000000))/((0.500000)-(0.000000));
                        if(x>=(0.500000))
                            ux=1;
                        if(ux<0.0001)
                            ux=0;
                break;
            default:break;
            }break;
        case 1:
            switch(numConj)
            {
            case 0:
                        if(x<(-1.000000))
                            ux=1;
                        if(x<(-0.500000)&&x>=(-1.000000))
                            ux=1;
                        if(x<(0.000000)&&x>=(-0.500000))
                            ux=((0.000000)-x)/((0.000000)-(-0.500000));
                        if(x>=(0.000000))
                            ux=0;
                        if(ux<0.0001)
                            ux=0;
                break;
            case 1:
                        if(x<(-0.500000))
                            ux=0;
                        if(x<(0.000000)&&x>=(-0.500000))
                            ux=(x-(-0.500000))/((0.000000)-(-0.500000));
                        if(x<(0.500000)&&x>=(0.000000))
                            ux=((0.500000)-x)/((0.500000)-(0.000000));
                        if(x>=(0.500000))
                            ux=0;
                        if(ux<0.0001)
                            ux=0;

                break;
            case 2:
                        if(x<(0.000000))
                            ux=0;
                        if(x<(0.500000)&&x>=(0.000000))
                            ux=(x-(0.000000))/((0.500000)-(0.000000));
                        if(x>=(0.500000))
                            ux=1;
                        if(ux<0.0001)
                            ux=0;
                break;
            default:break;
            }break;
        case 2:
            switch(numConj)
            {
            case 0:
                        if(x<(-1.000000))
                            ux=1;
                        if(x<(-0.500000)&&x>=(-1.000000))
                            ux=1;
                        if(x<(0.000000)&&x>=(-0.500000))
                            ux=((0.000000)-x)/((0.000000)-(-0.500000));
                        if(x>=(0.000000))
                            ux=0;
                        if(ux<0.0001)
                            ux=0;
                break;
            case 1:
                        if(x<(-0.500000))
                            ux=0;
                        if(x<(0.000000)&&x>=(-0.500000))
                            ux=(x-(-0.500000))/((0.000000)-(-0.500000));
                        if(x<(0.500000)&&x>=(0.000000))
                            ux=((0.500000)-x)/((0.500000)-(0.000000));
                        if(x>=(0.500000))
                            ux=0;
                        if(ux<0.0001)
                            ux=0;

                break;
            case 2:
                        if(x<(0.000000))
                            ux=0;
                        if(x<(0.500000)&&x>=(0.000000))
                            ux=(x-(0.000000))/((0.500000)-(0.000000));
                        if(x>=(0.500000))
                            ux=1;
                        if(ux<0.0001)
                            ux=0;
                break;
            default:break;
            }break;
        default:break;
    }
    return ux;
}
float pertenenciaVariableSalida(int numVar,int numConj, float x)
{
    float ux=0;
    switch(numVar)
    {
        case 0:
            switch(numConj)
            {
            case 0:
                        if(x<(-1.000000))
                            ux=1;
                        if(x<(-0.500000)&&x>=(-1.000000))
                            ux=1;
                        if(x<(0.000000)&&x>=(-0.500000))
                            ux=((0.000000)-x)/((0.000000)-(-0.500000));
                        if(x>=(0.000000))
                            ux=0;
                        if(ux<0.0001)
                            ux=0;
                break;
            case 1:
                        if(x<(-0.500000))
                            ux=0;
                        if(x<(0.000000)&&x>=(-0.500000))
                            ux=(x-(-0.500000))/((0.000000)-(-0.500000));
                        if(x<(0.500000)&&x>=(0.000000))
                            ux=((0.500000)-x)/((0.500000)-(0.000000));
                        if(x>=(0.500000))
                            ux=0;
                        if(ux<0.0001)
                            ux=0;

                break;
            case 2:
                        if(x<(0.000000))
                            ux=0;
                        if(x<(0.500000)&&x>=(0.000000))
                            ux=(x-(0.000000))/((0.500000)-(0.000000));
                        if(x>=(0.500000))
                            ux=1;
                        if(ux<0.0001)
                            ux=0;
                break;
            default:break;
            }break;
        case 1:
            switch(numConj)
            {
            case 0:
                        if(x<(-1.000000))
                            ux=1;
                        if(x<(-0.500000)&&x>=(-1.000000))
                            ux=1;
                        if(x<(0.000000)&&x>=(-0.500000))
                            ux=((0.000000)-x)/((0.000000)-(-0.500000));
                        if(x>=(0.000000))
                            ux=0;
                        if(ux<0.0001)
                            ux=0;
                break;
            case 1:
                        if(x<(-0.500000))
                            ux=0;
                        if(x<(0.000000)&&x>=(-0.500000))
                            ux=(x-(-0.500000))/((0.000000)-(-0.500000));
                        if(x<(0.500000)&&x>=(0.000000))
                            ux=((0.500000)-x)/((0.500000)-(0.000000));
                        if(x>=(0.500000))
                            ux=0;
                        if(ux<0.0001)
                            ux=0;

                break;
            case 2:
                        if(x<(0.000000))
                            ux=0;
                        if(x<(0.500000)&&x>=(0.000000))
                            ux=(x-(0.000000))/((0.500000)-(0.000000));
                        if(x>=(0.500000))
                            ux=1;
                        if(ux<0.0001)
                            ux=0;
                break;
            default:break;
            }break;
        default:break;
    }
    return ux;
}
float Implicacion(float x,float y)
{
    float rel;
    if(x<y)
    {
    	rel=x;
    }else
    {
    	rel=y;
    }
    return rel;
}

float Composicion(float x,float y)
{
    float z;
    if(x<y)
    {
    	z=x;
    }else
    {
    	z=y;
    }
    return z;
}

float Conjuncion(float x,float y)
{
    float z;
    if(x>y)
    {
    	z=x;
    }else
    {
    	z=y;
    }
    return z;
}

float And(float x,float y)
{
    float z;
    if(x<y)
    {
    	z=x;
    }else
    {
    	z=y;
    }
    return z;
}


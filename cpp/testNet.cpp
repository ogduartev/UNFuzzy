// Código C++ del Sistema de Lógica Difusa

// Generado automáticamente por UNFUZZY V 3.0
// Autor: Oscar Duarte (ogduartev@unal.edu.co)
// Universidad Nacional de Colombia
// Descargo de responsabilidad: 
// El código generado se usa bajo responsabilidad del usuario.
// En ninguna forma genera responsabilidad para el autor de UNFUZZY
// ni para la Universidad Nacional de Colombia.
// 
// para compilar el archivo xxx.cpp:
//   g++ xxx.cpp fuzzy.cpp

#ifndef __IOSTREAM_H
#include <iostream>
#endif

using namespace std;
	
#ifndef __FUZZY_H
#include "fuzzy.h"
#endif

class SLD_1_1:public SistemaLogicaDifusa
{
public:
    SLD_1_1();
    ~SLD_1_1();
protected:
};

SLD_1_1::SLD_1_1()
{
    ConjuntoDifuso *cd;
    Difusor *dif;
    Variable *var;
    Norma *And;
    Norma *Composicion;
    Norma *Conjuncion;
    Implicacion *Implica;
    Concresor *conc;

    entradas=new Universo(2);
    salidas=new Universo(1);
    var=new Variable(3);
    var->rangoMinimo(-1.000000);
    var->rangoMaximo(1.000000);
    cd=new ConjuntoL(-1.000000,-1.000000,0.000000);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoTriangulo(-1.000000,0.000000,1.000000);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoGamma(0.000000,1.000000,1.000000);
    var->adicionarConjuntos(cd);
    dif=new DifusorSinglenton(0.200000,0.010000);
    dif->numeroPuntos(1);
    var->difusorEntrada(dif);
    var->nombreVariable("Entrada 1");
    var->numeroIntervalos(20);
    entradas->adicionarVariable(var);
    var=new Variable(3);
    var->rangoMinimo(-1.000000);
    var->rangoMaximo(1.000000);
    cd=new ConjuntoL(-1.000000,-1.000000,0.000000);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoTriangulo(-1.000000,0.000000,1.000000);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoGamma(0.000000,1.000000,1.000000);
    var->adicionarConjuntos(cd);
    dif=new DifusorSinglenton(0.200000,0.010000);
    dif->numeroPuntos(1);
    var->difusorEntrada(dif);
    var->nombreVariable("Entrada 2");
    var->numeroIntervalos(20);
    entradas->adicionarVariable(var);
    var=new Variable(3);
    var->rangoMinimo(-1.000000);
    var->rangoMaximo(1.000000);
    cd=new ConjuntoL(-1.000000,-1.000000,0.000000);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoTriangulo(-1.000000,0.000000,1.000000);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoGamma(0.000000,1.000000,1.000000);
    var->adicionarConjuntos(cd);
    var->nombreVariable("Salida 1");
    var->numeroIntervalos(20);
    salidas->adicionarVariable(var);
    motor=new MaquinaInferencia(entradas,salidas,9);
    And=new Minimo();
    Composicion=new Minimo();
    Implica=new ImplicacionMinimo();
    motor->and_(And);
    motor->composicion(Composicion);
    motor->implicacion(Implica);
    motor->conjuntoEntrada(0,0,0);
    motor->conjuntoEntrada(0,1,0);
    motor->conjuntoSalida(0,0,0);
    motor->conjuntoEntrada(1,0,0);
    motor->conjuntoEntrada(1,1,1);
    motor->conjuntoSalida(1,0,0);
    motor->conjuntoEntrada(2,0,0);
    motor->conjuntoEntrada(2,1,2);
    motor->conjuntoSalida(2,0,1);
    motor->conjuntoEntrada(3,0,1);
    motor->conjuntoEntrada(3,1,0);
    motor->conjuntoSalida(3,0,0);
    motor->conjuntoEntrada(4,0,1);
    motor->conjuntoEntrada(4,1,1);
    motor->conjuntoSalida(4,0,1);
    motor->conjuntoEntrada(5,0,1);
    motor->conjuntoEntrada(5,1,2);
    motor->conjuntoSalida(5,0,1);
    motor->conjuntoEntrada(6,0,2);
    motor->conjuntoEntrada(6,1,0);
    motor->conjuntoSalida(6,0,1);
    motor->conjuntoEntrada(7,0,2);
    motor->conjuntoEntrada(7,1,1);
    motor->conjuntoSalida(7,0,1);
    motor->conjuntoEntrada(8,0,2);
    motor->conjuntoEntrada(8,1,2);
    motor->conjuntoSalida(8,0,2);
    motor->modificador(0,0,1.000000);
    motor->modificador(0,1,1.000000);
    motor->modificador(1,0,1.000000);
    motor->modificador(1,1,1.000000);
    motor->modificador(2,0,1.000000);
    motor->modificador(2,1,1.000000);
    motor->modificador(3,0,1.000000);
    motor->modificador(3,1,1.000000);
    motor->modificador(4,0,1.000000);
    motor->modificador(4,1,1.000000);
    motor->modificador(5,0,1.000000);
    motor->modificador(5,1,1.000000);
    motor->modificador(6,0,1.000000);
    motor->modificador(6,1,1.000000);
    motor->modificador(7,0,1.000000);
    motor->modificador(7,1,1.000000);
    motor->modificador(8,0,1.000000);
    motor->modificador(8,1,1.000000);
    concreto=new BloqueConcrecion(motor);
    Conjuncion=new Maximo();
    conc=new CentroDeGravedad(motor,0,Conjuncion);
    concreto->adicionarConcresor(conc);
    concreto->motor(motor);
    concreto->conjuncion(Conjuncion);
}

SLD_1_1::~SLD_1_1()
{
}

class SLD_1_2:public SistemaLogicaDifusa
{
public:
    SLD_1_2();
    ~SLD_1_2();
protected:
};

SLD_1_2::SLD_1_2()
{
    ConjuntoDifuso *cd;
    Difusor *dif;
    Variable *var;
    Norma *And;
    Norma *Composicion;
    Norma *Conjuncion;
    Implicacion *Implica;
    Concresor *conc;

    entradas=new Universo(2);
    salidas=new Universo(1);
    var=new Variable(3);
    var->rangoMinimo(-1.000000);
    var->rangoMaximo(1.000000);
    cd=new ConjuntoL(-1.000000,-1.000000,0.000000);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoTriangulo(-1.000000,0.000000,1.000000);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoGamma(0.000000,1.000000,1.000000);
    var->adicionarConjuntos(cd);
    dif=new DifusorSinglenton(-0.200000,0.010000);
    dif->numeroPuntos(1);
    var->difusorEntrada(dif);
    var->nombreVariable("Entrada 1");
    var->numeroIntervalos(20);
    entradas->adicionarVariable(var);
    var=new Variable(3);
    var->rangoMinimo(-1.000000);
    var->rangoMaximo(1.000000);
    cd=new ConjuntoL(-1.000000,-1.000000,0.000000);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoTriangulo(-1.000000,0.000000,1.000000);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoGamma(0.000000,1.000000,1.000000);
    var->adicionarConjuntos(cd);
    dif=new DifusorSinglenton(-0.200000,0.010000);
    dif->numeroPuntos(1);
    var->difusorEntrada(dif);
    var->nombreVariable("Entrada 2");
    var->numeroIntervalos(20);
    entradas->adicionarVariable(var);
    var=new Variable(3);
    var->rangoMinimo(-1.000000);
    var->rangoMaximo(1.000000);
    cd=new ConjuntoL(-1.000000,-1.000000,0.000000);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoTriangulo(-1.000000,0.000000,1.000000);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoGamma(0.000000,1.000000,1.000000);
    var->adicionarConjuntos(cd);
    var->nombreVariable("Salida 1");
    var->numeroIntervalos(20);
    salidas->adicionarVariable(var);
    motor=new MaquinaInferencia(entradas,salidas,9);
    And=new Minimo();
    Composicion=new Minimo();
    Implica=new ImplicacionMinimo();
    motor->and_(And);
    motor->composicion(Composicion);
    motor->implicacion(Implica);
    motor->conjuntoEntrada(0,0,0);
    motor->conjuntoEntrada(0,1,0);
    motor->conjuntoSalida(0,0,0);
    motor->conjuntoEntrada(1,0,0);
    motor->conjuntoEntrada(1,1,1);
    motor->conjuntoSalida(1,0,0);
    motor->conjuntoEntrada(2,0,0);
    motor->conjuntoEntrada(2,1,2);
    motor->conjuntoSalida(2,0,1);
    motor->conjuntoEntrada(3,0,1);
    motor->conjuntoEntrada(3,1,0);
    motor->conjuntoSalida(3,0,0);
    motor->conjuntoEntrada(4,0,1);
    motor->conjuntoEntrada(4,1,1);
    motor->conjuntoSalida(4,0,1);
    motor->conjuntoEntrada(5,0,1);
    motor->conjuntoEntrada(5,1,2);
    motor->conjuntoSalida(5,0,1);
    motor->conjuntoEntrada(6,0,2);
    motor->conjuntoEntrada(6,1,0);
    motor->conjuntoSalida(6,0,1);
    motor->conjuntoEntrada(7,0,2);
    motor->conjuntoEntrada(7,1,1);
    motor->conjuntoSalida(7,0,1);
    motor->conjuntoEntrada(8,0,2);
    motor->conjuntoEntrada(8,1,2);
    motor->conjuntoSalida(8,0,2);
    motor->modificador(0,0,1.000000);
    motor->modificador(0,1,1.000000);
    motor->modificador(1,0,1.000000);
    motor->modificador(1,1,1.000000);
    motor->modificador(2,0,1.000000);
    motor->modificador(2,1,1.000000);
    motor->modificador(3,0,1.000000);
    motor->modificador(3,1,1.000000);
    motor->modificador(4,0,1.000000);
    motor->modificador(4,1,1.000000);
    motor->modificador(5,0,1.000000);
    motor->modificador(5,1,1.000000);
    motor->modificador(6,0,1.000000);
    motor->modificador(6,1,1.000000);
    motor->modificador(7,0,1.000000);
    motor->modificador(7,1,1.000000);
    motor->modificador(8,0,1.000000);
    motor->modificador(8,1,1.000000);
    concreto=new BloqueConcrecion(motor);
    Conjuncion=new Maximo();
    conc=new CentroDeGravedad(motor,0,Conjuncion);
    concreto->adicionarConcresor(conc);
    concreto->motor(motor);
    concreto->conjuncion(Conjuncion);
}

SLD_1_2::~SLD_1_2()
{
}

class SLD_2_1:public SistemaLogicaDifusa
{
public:
    SLD_2_1();
    ~SLD_2_1();
protected:
};

SLD_2_1::SLD_2_1()
{
    ConjuntoDifuso *cd;
    Difusor *dif;
    Variable *var;
    Norma *And;
    Norma *Composicion;
    Norma *Conjuncion;
    Implicacion *Implica;
    Concresor *conc;

    entradas=new Universo(2);
    salidas=new Universo(1);
    var=new Variable(3);
    var->rangoMinimo(-1.000000);
    var->rangoMaximo(1.000000);
    cd=new ConjuntoL(-1.000000,-1.000000,0.000000);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoTriangulo(-1.000000,0.000000,1.000000);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoGamma(0.000000,1.000000,1.000000);
    var->adicionarConjuntos(cd);
    dif=new DifusorSinglenton(0.028319,0.010000);
    dif->numeroPuntos(1);
    var->difusorEntrada(dif);
    var->nombreVariable("Entrada 1");
    var->numeroIntervalos(20);
    entradas->adicionarVariable(var);
    var=new Variable(3);
    var->rangoMinimo(-1.000000);
    var->rangoMaximo(1.000000);
    cd=new ConjuntoL(-1.000000,-1.000000,0.000000);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoTriangulo(-1.000000,0.000000,1.000000);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoGamma(0.000000,1.000000,1.000000);
    var->adicionarConjuntos(cd);
    dif=new DifusorSinglenton(-0.030688,0.010000);
    dif->numeroPuntos(1);
    var->difusorEntrada(dif);
    var->nombreVariable("Entrada 2");
    var->numeroIntervalos(20);
    entradas->adicionarVariable(var);
    var=new Variable(3);
    var->rangoMinimo(-1.000000);
    var->rangoMaximo(1.000000);
    cd=new ConjuntoL(-1.000000,-1.000000,0.000000);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoTriangulo(-1.000000,0.000000,1.000000);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoGamma(0.000000,1.000000,1.000000);
    var->adicionarConjuntos(cd);
    var->nombreVariable("Salida 1");
    var->numeroIntervalos(20);
    salidas->adicionarVariable(var);
    motor=new MaquinaInferencia(entradas,salidas,9);
    And=new Minimo();
    Composicion=new Minimo();
    Implica=new ImplicacionMinimo();
    motor->and_(And);
    motor->composicion(Composicion);
    motor->implicacion(Implica);
    motor->conjuntoEntrada(0,0,0);
    motor->conjuntoEntrada(0,1,0);
    motor->conjuntoSalida(0,0,0);
    motor->conjuntoEntrada(1,0,0);
    motor->conjuntoEntrada(1,1,1);
    motor->conjuntoSalida(1,0,0);
    motor->conjuntoEntrada(2,0,0);
    motor->conjuntoEntrada(2,1,2);
    motor->conjuntoSalida(2,0,1);
    motor->conjuntoEntrada(3,0,1);
    motor->conjuntoEntrada(3,1,0);
    motor->conjuntoSalida(3,0,0);
    motor->conjuntoEntrada(4,0,1);
    motor->conjuntoEntrada(4,1,1);
    motor->conjuntoSalida(4,0,1);
    motor->conjuntoEntrada(5,0,1);
    motor->conjuntoEntrada(5,1,2);
    motor->conjuntoSalida(5,0,1);
    motor->conjuntoEntrada(6,0,2);
    motor->conjuntoEntrada(6,1,0);
    motor->conjuntoSalida(6,0,1);
    motor->conjuntoEntrada(7,0,2);
    motor->conjuntoEntrada(7,1,1);
    motor->conjuntoSalida(7,0,1);
    motor->conjuntoEntrada(8,0,2);
    motor->conjuntoEntrada(8,1,2);
    motor->conjuntoSalida(8,0,2);
    motor->modificador(0,0,1.000000);
    motor->modificador(0,1,1.000000);
    motor->modificador(1,0,1.000000);
    motor->modificador(1,1,1.000000);
    motor->modificador(2,0,1.000000);
    motor->modificador(2,1,1.000000);
    motor->modificador(3,0,1.000000);
    motor->modificador(3,1,1.000000);
    motor->modificador(4,0,1.000000);
    motor->modificador(4,1,1.000000);
    motor->modificador(5,0,1.000000);
    motor->modificador(5,1,1.000000);
    motor->modificador(6,0,1.000000);
    motor->modificador(6,1,1.000000);
    motor->modificador(7,0,1.000000);
    motor->modificador(7,1,1.000000);
    motor->modificador(8,0,1.000000);
    motor->modificador(8,1,1.000000);
    concreto=new BloqueConcrecion(motor);
    Conjuncion=new Maximo();
    conc=new CentroDeGravedad(motor,0,Conjuncion);
    concreto->adicionarConcresor(conc);
    concreto->motor(motor);
    concreto->conjuncion(Conjuncion);
}

SLD_2_1::~SLD_2_1()
{
}

class miRed:public red
{
public:
    miRed();
    ~miRed();
protected:
};

miRed::miRed()
{
  capa* Capa_1;
  Capa_1= new capa();

    nodo* Nodo_1_1;
    SLD_1_1* miSLD_1_1;
    Nodo_1_1= new nodo();
    miSLD_1_1= new SLD_1_1();
    Nodo_1_1->sld(miSLD_1_1);
    Nodo_1_1->ajustarPinesAsld();
    Capa_1->nodos()->Add(Nodo_1_1);

    nodo* Nodo_1_2;
    SLD_1_2* miSLD_1_2;
    Nodo_1_2= new nodo();
    miSLD_1_2= new SLD_1_2();
    Nodo_1_2->sld(miSLD_1_2);
    Nodo_1_2->ajustarPinesAsld();
    Capa_1->nodos()->Add(Nodo_1_2);
  capas()->Add(Capa_1);

  capa* Capa_2;
  Capa_2= new capa();

    nodo* Nodo_2_1;
    SLD_2_1* miSLD_2_1;
    Nodo_2_1= new nodo();
    miSLD_2_1= new SLD_2_1();
    Nodo_2_1->sld(miSLD_2_1);
    Nodo_2_1->ajustarPinesAsld();
    Capa_2->nodos()->Add(Nodo_2_1);
  capas()->Add(Capa_2);

  conectar(0,0,0,1,0,0);
  conectar(0,1,0,1,0,1);
}

miRed::~miRed()
{
}

int main()
{
    float *entra;
    float *sale;
    miRed *Red;
    int NumeroEntradas;
    int NumeroSalidas;
    Red=new miRed();
    NumeroEntradas=Red->numeroEntradas();
    NumeroSalidas=Red->numeroSalidas();
    entra=new float[NumeroEntradas];
    sale=new float[NumeroSalidas];
    int i;
    char q='s';
    while(q=='s')
    {
        for(i=0;i<NumeroEntradas;i++)
        {
            cout << "Entrada " << (i+1) << " : ";
            cin >> entra[i];
        }
        Red->calcular(entra,sale);
        for(i=0;i<NumeroSalidas;i++)
        {
            cout << "Salida " << (i+1) << " : ";
            cout << sale[i] << "\n";
        }
        cout << "Desea otro cálculo ?(s/n)";
        cin >> q;
    }
    delete[] entra;
    delete[] sale;
    return 0;
}


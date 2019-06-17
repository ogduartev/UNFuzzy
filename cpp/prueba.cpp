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

class miSLD:public SistemaLogicaDifusa
{
public:
    miSLD();
    ~miSLD();
protected:
};

miSLD::miSLD()
{
    ConjuntoDifuso *cd;
    Difusor *dif;
    Variable *var;
    Norma *And;
    Norma *Composicion;
    Norma *Conjuncion;
    Implicacion *Implica;
    Concresor *conc;

    entradas=new Universo(1);
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
    dif=new DifusorSinglenton(0.000000,0.010000);
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
    var->nombreVariable("Salida 1");
    var->numeroIntervalos(20);
    salidas->adicionarVariable(var);
    motor=new MaquinaInferencia(entradas,salidas,3);
    And=new Minimo();
    Composicion=new Minimo();
    Implica=new ImplicacionMinimo();
    motor->and_(And);
    motor->composicion(Composicion);
    motor->implicacion(Implica);
    motor->conjuntoEntrada(0,0,0);
    motor->conjuntoSalida(0,0,0);
    motor->conjuntoEntrada(1,0,1);
    motor->conjuntoSalida(1,0,1);
    motor->conjuntoEntrada(2,0,2);
    motor->conjuntoSalida(2,0,2);
    motor->modificador(0,0,1.000000);
    motor->modificador(1,0,1.000000);
    motor->modificador(2,0,1.000000);
    concreto=new BloqueConcrecion(motor);
    Conjuncion=new Maximo();
    conc=new CentroDeGravedad(motor,0,Conjuncion);
    concreto->adicionarConcresor(conc);
    concreto->motor(motor);
    concreto->conjuncion(Conjuncion);
}

miSLD::~miSLD()
{
}

int main()
{
    float *entra;
    float *sale;
    miSLD *sistema;
    int NumeroEntradas;
    int NumeroSalidas;
    sistema=new miSLD();
    NumeroEntradas=sistema->numeroEntradas();
    NumeroSalidas=sistema->numeroSalidas();
    entra=new float[NumeroEntradas];
    sale=new float[NumeroSalidas];
    int i;
    char q='s';
    while(q=='s')
    {
        for(i=0;i<NumeroEntradas;i++)
        {
            cout << sistema->nombreVariableEntrada(i) << " : ";
            cin >> entra[i];
        }
        sistema->calcular(entra,sale);
        for(i=0;i<NumeroSalidas;i++)
        {
            cout << sistema->nombreVariableSalida(i) << " : ";
            cout << sale[i] << "\n";
        }
        cout << "Desea otro cálculo ?(s/n)";
        cin >> q;
    }
    delete[] entra;
    delete[] sale;
    return 0;
}


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

#include <iostream>
#include <iostream>
#include <string>
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

    entradas=new Universo(2);
    salidas=new Universo(1);
    var=new Variable(5);
    var->rangoMinimo(-1);
    var->rangoMaximo(1);
    cd=new ConjuntoL(-1,-0.666667,-0.333333);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoTriangulo(-0.666667,-0.333333,0);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoTriangulo(-0.333333,0,0.333333);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoTriangulo(0,0.333333,0.666667);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoGamma(0.333333,0.666667,1);
    var->adicionarConjuntos(cd);
    dif=new DifusorSinglenton(1,0.01);
    dif->numeroPuntos(1);
    var->difusorEntrada(dif);
    var->nombreVariable("Ángulo");
    var->numeroIntervalos(30);
    entradas->adicionarVariable(var);
    var=new Variable(3);
    var->rangoMinimo(-1);
    var->rangoMaximo(1);
    cd=new ConjuntoL(-1,-0.5,0);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoTriangulo(-0.5,0,0.5);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoGamma(0,0.5,1);
    var->adicionarConjuntos(cd);
    dif=new DifusorSinglenton(0,0.01);
    dif->numeroPuntos(1);
    var->difusorEntrada(dif);
    var->nombreVariable("Delta Ángulo");
    var->numeroIntervalos(20);
    entradas->adicionarVariable(var);
    var=new Variable(5);
    var->rangoMinimo(-1);
    var->rangoMaximo(1);
    cd=new ConjuntoL(-1,-0.666667,-0.333333);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoTriangulo(-0.666667,-0.333333,0);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoTriangulo(-0.333333,0,0.333333);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoTriangulo(0,0.333333,0.666667);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoGamma(0.333333,0.666667,1);
    var->adicionarConjuntos(cd);
    var->nombreVariable("Control");
    var->numeroIntervalos(30);
    salidas->adicionarVariable(var);
    motor=new MaquinaInferencia(entradas,salidas,15);
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
    motor->conjuntoSalida(3,0,1);
    motor->conjuntoEntrada(4,0,1);
    motor->conjuntoEntrada(4,1,1);
    motor->conjuntoSalida(4,0,1);
    motor->conjuntoEntrada(5,0,1);
    motor->conjuntoEntrada(5,1,2);
    motor->conjuntoSalida(5,0,2);
    motor->conjuntoEntrada(6,0,2);
    motor->conjuntoEntrada(6,1,0);
    motor->conjuntoSalida(6,0,2);
    motor->conjuntoEntrada(7,0,2);
    motor->conjuntoEntrada(7,1,1);
    motor->conjuntoSalida(7,0,2);
    motor->conjuntoEntrada(8,0,2);
    motor->conjuntoEntrada(8,1,2);
    motor->conjuntoSalida(8,0,2);
    motor->conjuntoEntrada(9,0,3);
    motor->conjuntoEntrada(9,1,0);
    motor->conjuntoSalida(9,0,2);
    motor->conjuntoEntrada(10,0,3);
    motor->conjuntoEntrada(10,1,1);
    motor->conjuntoSalida(10,0,3);
    motor->conjuntoEntrada(11,0,3);
    motor->conjuntoEntrada(11,1,2);
    motor->conjuntoSalida(11,0,3);
    motor->conjuntoEntrada(12,0,4);
    motor->conjuntoEntrada(12,1,0);
    motor->conjuntoSalida(12,0,3);
    motor->conjuntoEntrada(13,0,4);
    motor->conjuntoEntrada(13,1,1);
    motor->conjuntoSalida(13,0,4);
    motor->conjuntoEntrada(14,0,4);
    motor->conjuntoEntrada(14,1,2);
    motor->conjuntoSalida(14,0,4);
    motor->modificador(0,0,1);
    motor->modificador(0,1,1);
    motor->modificador(1,0,1);
    motor->modificador(1,1,1);
    motor->modificador(2,0,1);
    motor->modificador(2,1,1);
    motor->modificador(3,0,1);
    motor->modificador(3,1,1);
    motor->modificador(4,0,1);
    motor->modificador(4,1,1);
    motor->modificador(5,0,1);
    motor->modificador(5,1,1);
    motor->modificador(6,0,1);
    motor->modificador(6,1,1);
    motor->modificador(7,0,1);
    motor->modificador(7,1,1);
    motor->modificador(8,0,1);
    motor->modificador(8,1,1);
    motor->modificador(9,0,1);
    motor->modificador(9,1,1);
    motor->modificador(10,0,1);
    motor->modificador(10,1,1);
    motor->modificador(11,0,1);
    motor->modificador(11,1,1);
    motor->modificador(12,0,1);
    motor->modificador(12,1,1);
    motor->modificador(13,0,1);
    motor->modificador(13,1,1);
    motor->modificador(14,0,1);
    motor->modificador(14,1,1);
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
    double *entra;
    double *sale;
    miSLD *sistema;
    int NumeroEntradas;
    int NumeroSalidas;
    sistema=new miSLD();
    NumeroEntradas=sistema->numeroEntradas();
    NumeroSalidas=sistema->numeroSalidas();
    entra=new double[NumeroEntradas];
    sale=new double[NumeroSalidas];
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


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

    entradas=new Universo(3);
    salidas=new Universo(2);
    var=new Variable(3);
    var->rangoMinimo(-1.000000);
    var->rangoMaximo(1.000000);
    cd=new ConjuntoL(-1.000000,-0.500000,0.000000);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoTriangulo(-0.500000,0.000000,0.500000);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoGamma(0.000000,0.500000,1.000000);
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
    cd=new ConjuntoL(-1.000000,-0.500000,0.000000);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoTriangulo(-0.500000,0.000000,0.500000);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoGamma(0.000000,0.500000,1.000000);
    var->adicionarConjuntos(cd);
    dif=new DifusorSinglenton(0.000000,0.010000);
    dif->numeroPuntos(1);
    var->difusorEntrada(dif);
    var->nombreVariable("Entrada 2");
    var->numeroIntervalos(20);
    entradas->adicionarVariable(var);
    var=new Variable(3);
    var->rangoMinimo(-1.000000);
    var->rangoMaximo(1.000000);
    cd=new ConjuntoL(-1.000000,-0.500000,0.000000);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoTriangulo(-0.500000,0.000000,0.500000);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoGamma(0.000000,0.500000,1.000000);
    var->adicionarConjuntos(cd);
    dif=new DifusorSinglenton(0.000000,0.010000);
    dif->numeroPuntos(1);
    var->difusorEntrada(dif);
    var->nombreVariable("Entrada 3");
    var->numeroIntervalos(20);
    entradas->adicionarVariable(var);
    var=new Variable(3);
    var->rangoMinimo(-1.000000);
    var->rangoMaximo(1.000000);
    cd=new ConjuntoL(-1.000000,-0.500000,0.000000);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoTriangulo(-0.500000,0.000000,0.500000);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoGamma(0.000000,0.500000,1.000000);
    var->adicionarConjuntos(cd);
    var->nombreVariable("Salida 1");
    var->numeroIntervalos(20);
    salidas->adicionarVariable(var);
    var=new Variable(3);
    var->rangoMinimo(-1.000000);
    var->rangoMaximo(1.000000);
    cd=new ConjuntoL(-1.000000,-0.500000,0.000000);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoTriangulo(-0.500000,0.000000,0.500000);
    var->adicionarConjuntos(cd);
    cd=new ConjuntoGamma(0.000000,0.500000,1.000000);
    var->adicionarConjuntos(cd);
    var->nombreVariable("Salida 2");
    var->numeroIntervalos(20);
    salidas->adicionarVariable(var);
    motor=new MaquinaInferencia(entradas,salidas,27);
    And=new Minimo();
    Composicion=new Minimo();
    Implica=new ImplicacionMinimo();
    motor->and_(And);
    motor->composicion(Composicion);
    motor->implicacion(Implica);
    motor->conjuntoEntrada(0,0,0);
    motor->conjuntoEntrada(0,1,0);
    motor->conjuntoEntrada(0,2,0);
    motor->conjuntoSalida(0,0,0);
    motor->conjuntoSalida(0,1,0);
    motor->conjuntoEntrada(1,0,0);
    motor->conjuntoEntrada(1,1,0);
    motor->conjuntoEntrada(1,2,1);
    motor->conjuntoSalida(1,0,0);
    motor->conjuntoSalida(1,1,0);
    motor->conjuntoEntrada(2,0,0);
    motor->conjuntoEntrada(2,1,0);
    motor->conjuntoEntrada(2,2,2);
    motor->conjuntoSalida(2,0,0);
    motor->conjuntoSalida(2,1,0);
    motor->conjuntoEntrada(3,0,0);
    motor->conjuntoEntrada(3,1,1);
    motor->conjuntoEntrada(3,2,0);
    motor->conjuntoSalida(3,0,0);
    motor->conjuntoSalida(3,1,0);
    motor->conjuntoEntrada(4,0,0);
    motor->conjuntoEntrada(4,1,1);
    motor->conjuntoEntrada(4,2,1);
    motor->conjuntoSalida(4,0,0);
    motor->conjuntoSalida(4,1,0);
    motor->conjuntoEntrada(5,0,0);
    motor->conjuntoEntrada(5,1,1);
    motor->conjuntoEntrada(5,2,2);
    motor->conjuntoSalida(5,0,1);
    motor->conjuntoSalida(5,1,1);
    motor->conjuntoEntrada(6,0,0);
    motor->conjuntoEntrada(6,1,2);
    motor->conjuntoEntrada(6,2,0);
    motor->conjuntoSalida(6,0,0);
    motor->conjuntoSalida(6,1,0);
    motor->conjuntoEntrada(7,0,0);
    motor->conjuntoEntrada(7,1,2);
    motor->conjuntoEntrada(7,2,1);
    motor->conjuntoSalida(7,0,1);
    motor->conjuntoSalida(7,1,1);
    motor->conjuntoEntrada(8,0,0);
    motor->conjuntoEntrada(8,1,2);
    motor->conjuntoEntrada(8,2,2);
    motor->conjuntoSalida(8,0,1);
    motor->conjuntoSalida(8,1,1);
    motor->conjuntoEntrada(9,0,1);
    motor->conjuntoEntrada(9,1,0);
    motor->conjuntoEntrada(9,2,0);
    motor->conjuntoSalida(9,0,0);
    motor->conjuntoSalida(9,1,0);
    motor->conjuntoEntrada(10,0,1);
    motor->conjuntoEntrada(10,1,0);
    motor->conjuntoEntrada(10,2,1);
    motor->conjuntoSalida(10,0,0);
    motor->conjuntoSalida(10,1,0);
    motor->conjuntoEntrada(11,0,1);
    motor->conjuntoEntrada(11,1,0);
    motor->conjuntoEntrada(11,2,2);
    motor->conjuntoSalida(11,0,1);
    motor->conjuntoSalida(11,1,1);
    motor->conjuntoEntrada(12,0,1);
    motor->conjuntoEntrada(12,1,1);
    motor->conjuntoEntrada(12,2,0);
    motor->conjuntoSalida(12,0,0);
    motor->conjuntoSalida(12,1,0);
    motor->conjuntoEntrada(13,0,1);
    motor->conjuntoEntrada(13,1,1);
    motor->conjuntoEntrada(13,2,1);
    motor->conjuntoSalida(13,0,1);
    motor->conjuntoSalida(13,1,1);
    motor->conjuntoEntrada(14,0,1);
    motor->conjuntoEntrada(14,1,1);
    motor->conjuntoEntrada(14,2,2);
    motor->conjuntoSalida(14,0,1);
    motor->conjuntoSalida(14,1,1);
    motor->conjuntoEntrada(15,0,1);
    motor->conjuntoEntrada(15,1,2);
    motor->conjuntoEntrada(15,2,0);
    motor->conjuntoSalida(15,0,1);
    motor->conjuntoSalida(15,1,1);
    motor->conjuntoEntrada(16,0,1);
    motor->conjuntoEntrada(16,1,2);
    motor->conjuntoEntrada(16,2,1);
    motor->conjuntoSalida(16,0,1);
    motor->conjuntoSalida(16,1,1);
    motor->conjuntoEntrada(17,0,1);
    motor->conjuntoEntrada(17,1,2);
    motor->conjuntoEntrada(17,2,2);
    motor->conjuntoSalida(17,0,1);
    motor->conjuntoSalida(17,1,1);
    motor->conjuntoEntrada(18,0,2);
    motor->conjuntoEntrada(18,1,0);
    motor->conjuntoEntrada(18,2,0);
    motor->conjuntoSalida(18,0,0);
    motor->conjuntoSalida(18,1,0);
    motor->conjuntoEntrada(19,0,2);
    motor->conjuntoEntrada(19,1,0);
    motor->conjuntoEntrada(19,2,1);
    motor->conjuntoSalida(19,0,1);
    motor->conjuntoSalida(19,1,1);
    motor->conjuntoEntrada(20,0,2);
    motor->conjuntoEntrada(20,1,0);
    motor->conjuntoEntrada(20,2,2);
    motor->conjuntoSalida(20,0,1);
    motor->conjuntoSalida(20,1,1);
    motor->conjuntoEntrada(21,0,2);
    motor->conjuntoEntrada(21,1,1);
    motor->conjuntoEntrada(21,2,0);
    motor->conjuntoSalida(21,0,1);
    motor->conjuntoSalida(21,1,1);
    motor->conjuntoEntrada(22,0,2);
    motor->conjuntoEntrada(22,1,1);
    motor->conjuntoEntrada(22,2,1);
    motor->conjuntoSalida(22,0,1);
    motor->conjuntoSalida(22,1,1);
    motor->conjuntoEntrada(23,0,2);
    motor->conjuntoEntrada(23,1,1);
    motor->conjuntoEntrada(23,2,2);
    motor->conjuntoSalida(23,0,1);
    motor->conjuntoSalida(23,1,1);
    motor->conjuntoEntrada(24,0,2);
    motor->conjuntoEntrada(24,1,2);
    motor->conjuntoEntrada(24,2,0);
    motor->conjuntoSalida(24,0,1);
    motor->conjuntoSalida(24,1,1);
    motor->conjuntoEntrada(25,0,2);
    motor->conjuntoEntrada(25,1,2);
    motor->conjuntoEntrada(25,2,1);
    motor->conjuntoSalida(25,0,1);
    motor->conjuntoSalida(25,1,1);
    motor->conjuntoEntrada(26,0,2);
    motor->conjuntoEntrada(26,1,2);
    motor->conjuntoEntrada(26,2,2);
    motor->conjuntoSalida(26,0,2);
    motor->conjuntoSalida(26,1,2);
    motor->modificador(0,0,1.000000);
    motor->modificador(0,1,1.000000);
    motor->modificador(0,2,1.000000);
    motor->modificador(1,0,1.000000);
    motor->modificador(1,1,1.000000);
    motor->modificador(1,2,1.000000);
    motor->modificador(2,0,1.000000);
    motor->modificador(2,1,1.000000);
    motor->modificador(2,2,1.000000);
    motor->modificador(3,0,1.000000);
    motor->modificador(3,1,1.000000);
    motor->modificador(3,2,1.000000);
    motor->modificador(4,0,1.000000);
    motor->modificador(4,1,1.000000);
    motor->modificador(4,2,1.000000);
    motor->modificador(5,0,1.000000);
    motor->modificador(5,1,1.000000);
    motor->modificador(5,2,1.000000);
    motor->modificador(6,0,1.000000);
    motor->modificador(6,1,1.000000);
    motor->modificador(6,2,1.000000);
    motor->modificador(7,0,1.000000);
    motor->modificador(7,1,1.000000);
    motor->modificador(7,2,1.000000);
    motor->modificador(8,0,1.000000);
    motor->modificador(8,1,1.000000);
    motor->modificador(8,2,1.000000);
    motor->modificador(9,0,1.000000);
    motor->modificador(9,1,1.000000);
    motor->modificador(9,2,1.000000);
    motor->modificador(10,0,1.000000);
    motor->modificador(10,1,1.000000);
    motor->modificador(10,2,1.000000);
    motor->modificador(11,0,1.000000);
    motor->modificador(11,1,1.000000);
    motor->modificador(11,2,1.000000);
    motor->modificador(12,0,1.000000);
    motor->modificador(12,1,1.000000);
    motor->modificador(12,2,1.000000);
    motor->modificador(13,0,1.000000);
    motor->modificador(13,1,1.000000);
    motor->modificador(13,2,1.000000);
    motor->modificador(14,0,1.000000);
    motor->modificador(14,1,1.000000);
    motor->modificador(14,2,1.000000);
    motor->modificador(15,0,1.000000);
    motor->modificador(15,1,1.000000);
    motor->modificador(15,2,1.000000);
    motor->modificador(16,0,1.000000);
    motor->modificador(16,1,1.000000);
    motor->modificador(16,2,1.000000);
    motor->modificador(17,0,1.000000);
    motor->modificador(17,1,1.000000);
    motor->modificador(17,2,1.000000);
    motor->modificador(18,0,1.000000);
    motor->modificador(18,1,1.000000);
    motor->modificador(18,2,1.000000);
    motor->modificador(19,0,1.000000);
    motor->modificador(19,1,1.000000);
    motor->modificador(19,2,1.000000);
    motor->modificador(20,0,1.000000);
    motor->modificador(20,1,1.000000);
    motor->modificador(20,2,1.000000);
    motor->modificador(21,0,1.000000);
    motor->modificador(21,1,1.000000);
    motor->modificador(21,2,1.000000);
    motor->modificador(22,0,1.000000);
    motor->modificador(22,1,1.000000);
    motor->modificador(22,2,1.000000);
    motor->modificador(23,0,1.000000);
    motor->modificador(23,1,1.000000);
    motor->modificador(23,2,1.000000);
    motor->modificador(24,0,1.000000);
    motor->modificador(24,1,1.000000);
    motor->modificador(24,2,1.000000);
    motor->modificador(25,0,1.000000);
    motor->modificador(25,1,1.000000);
    motor->modificador(25,2,1.000000);
    motor->modificador(26,0,1.000000);
    motor->modificador(26,1,1.000000);
    motor->modificador(26,2,1.000000);
    concreto=new BloqueConcrecion(motor);
    Conjuncion=new Maximo();
    conc=new CentroDeGravedad(motor,0,Conjuncion);
    concreto->adicionarConcresor(conc);
    conc=new CentroDeGravedad(motor,1,Conjuncion);
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


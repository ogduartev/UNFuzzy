#ifndef CONJUNTODIFUSO_H
#define CONJUNTODIFUSO_H

#include <cstdio>

#ifndef __IDIOMAS_H
#include "Idiomas.h"
#endif

typedef int BOOL;

/*/////////////////////////////////////////////////////
class ConjuntoDifuso

    Tiene por propósito encapsular la definición de cada
    Valor Lingüístico; fundamentalmente es una Etiqueta,
    y un Conjunto Difuso definido por su función de pertenencia
    y su Soporte.
atributos:
	char* Nombre;           Etiqueta del Valor Linguistico (Ej, BAJO)
	char* Tipo;             Identificador de tipo (Ej. "Tipo L" ) ver hijos
	char* CodigoC;          Texto necesario para generar Código C
	char* CodigoCPP;        Texto necesario para generar Código C++
	float Minimo;           límite inferior del Soporte
	float Maximo;           límite superior del Soporte
	int NumeroPuntosClaves; Número de puntos que se pueden editar gráficamente (ver DialogVariableEntrada)
	int Identificador;      identificador de Tipo, necesario para crear el hijo adecuado al leer un archivo

procedimientos
	char* nombre()          consultor de Nombre
	char* nombre(char* s)   modificador de Nombre
	char* tipo()            consultor de Tipo
	void minimo(float min)  modificador de Minimo
	float minimo()          consultor de Minimo
	void maximo(float max)  modificador de Maximo
	float maximo()          consultor de Maximo
	int identificador()     consultor de Identificador
	int numeroPuntosClaves()  consultor de NumeroPuntosClaves

Las funciones virtual=0 deben ser redefinidas por los hijos

	virtual void puntosClaves(float *puntos)=0;
                        en el arreglo puntos retorna los valores de los puntos editables gráficamente (ver DialogVariableEntrada)
	virtual void nuevoPuntoClave(int punto, float x)=0;
                        reasigna el valor de un punto que ha sido editado gráficamente (ver DialogVariableEntrada)
	virtual float pertenencia(float x)=0;
                        calcula la función de pertenencia para x
	virtual void recibirDatos(TWindow *parent,float mn,float mx)=0;
                        muestra un cuador de dialogo para editar el ConjuntoDifuso no graficamente
	virtual void ajustar(float nuevoMinimo, float nuevoMaximo)=0;
                        redefine el ConjuntoDifuso cuando cambia el Universo de Discurso de la Variable a la cual pertenece
    virtual float centroAltura()=0;
                        devuelve el centro del ConjuntoDifuso, definido para calcular la Concrecion de Altura
	virtual char* codigoC()=0;
                        entrega el texto necesario para generar Codigo C (ver DialogGenerarCodigo)
	virtual char* codigoCPP()=0;
                        entrega el texto necesario para generar Codigo C++ (ver DialogGenerarCodigo)

	BOOL operator==(const ConjuntoDifuso& other)  Definido para poder crear listas de ConjuntoDifuso

//////////////////////////////////////////////*/

class ConjuntoDifuso
{
public:
	ConjuntoDifuso()
	{
		Nombre = 0;
		Tipo=0;
	  CodigoC=0;
	  CodigoCPP=0;
	}
	virtual ~ConjuntoDifuso()
	{
		delete[] Nombre;
		delete[] Tipo;
		delete[] CodigoC;
		delete[] CodigoCPP;
	}
	char* nombre() const
	{
		return Nombre;
	}
	char* nombre(const char* s)
	{
		delete[] Nombre;
		Nombre=new char[strlen(s)+1];
		strcpy(Nombre,s);
		return Nombre;
	}
	char* tipo()
	{
		return Tipo;
	}
	void minimo(float min)
	{
		Minimo=min;
	}
	float minimo()
	{
		return Minimo;
	}
	void maximo(float max)
	{
		Maximo=max;
	}
	float maximo()
	{
		return Maximo;
	}
	int identificador()
	{
		return Identificador;
	}
	int numeroPuntosClaves()
	{
		return NumeroPuntosClaves;
	}
	float verificarPuntoClave(int i,float x);
	virtual void puntosClaves(float *puntos)=0;
	virtual void nuevoPuntoClave(int punto, float x)=0;
	virtual float pertenencia(float x)=0;
	virtual void ajustar(float nuevoMinimo, float nuevoMaximo)=0;
	virtual float centroAltura()=0;
	virtual char* codigoC()=0;
	virtual char* codigoCPP()=0;
	BOOL operator==(const ConjuntoDifuso& other)
	{
		return ( strcmp( Nombre,other.Nombre)&
		( Minimo == other.Minimo)&
		( Maximo == other.Maximo) );
	}
	///// FALTA VALIDAR
	/*
	void operator=(const ConjuntoDifuso& other)
	{
		strcpy( Nombre    ,  other.Nombre);
		strcpy( Tipo      ,  other.Tipo);
		strcpy( CodigoC   ,  other.CodigoC);
		strcpy( CodigoCPP ,  other.CodigoCPP);
		Minimo             = other.Minimo;
		Maximo             = other.Maximo;
		NumeroPuntosClaves = other.NumeroPuntosClaves;
		Identificador      = other.Identificador;
	}*/
protected:
	char* Nombre;
	char* Tipo;
	char* CodigoC;
	char* CodigoCPP;
	float Minimo;
	float Maximo;
	int NumeroPuntosClaves;
	int Identificador;
};

/*////////////////////////////////////////
class ConjuntoL

    El soporte de un Conjunto Tipo L va desde Minimo hasta Maximo;
    su función de pertenencia son tres tramos de línea recta:
    desde Minimo hasta PrimerCorte vale 1.0
    desde PrimerCorte hasta Maximo es una recta que va de 1.0 a 0.0
    para valores mayores a Maximo  vale 0.0

    Tipo :               "Tipo L"
    Identificador :      0
    NumeroPuntosClaves : 2
    centroAltura:        En la mitad de la recta de valor 1.0
atributos:
    float PrimerCorte       parámetro de la función de pertenencia

////////////////////////////////////////*/

class ConjuntoL: public ConjuntoDifuso
{
public:
	ConjuntoL(const char* s, float min, float pcor, float max)
	{
		Nombre=new char[strlen(s)+1];
		strcpy(Nombre,s);
		Tipo=new char[20];
		strcpy(Tipo,IDS_CONJUNTOS_TIPO_0);
		Minimo=min;
		PrimerCorte=pcor;
		Maximo=max;
		NumeroPuntosClaves=2;
		CodigoC=new char[2000];
		CodigoCPP=new char[2000];
		Identificador=0;
	}
	~ConjuntoL()
	{
	}
	float pertenencia(float);
	void ajustar(float nuevoMinimo,float nuevoMaximo)
	{
		float a,b,c;
		a=nuevoMinimo;
		b=nuevoMinimo+(primerCorte()-minimo())*(nuevoMaximo-nuevoMinimo)/(maximo()-minimo());
		c=nuevoMaximo;
		minimo(a);
		primerCorte(b);
		maximo(c);
	}
	void puntosClaves(float *puntos)
	{
		puntos[0]=primerCorte();
		puntos[1]=maximo();
	}
	void nuevoPuntoClave(int punto, float x);
	float centroAltura()
  {
    float cen;
    cen=(minimo()+primerCorte())/2.0;
    return cen;
  }
	char* codigoC();
	char* codigoCPP();
protected:
	float PrimerCorte;
	void primerCorte(float pcor)
	{
		PrimerCorte=pcor;
	}
	float primerCorte()
	{
		return PrimerCorte;
	}
};


/*////////////////////////////////////////
class ConjuntoTriangulo

    El soporte de un Conjunto Tipo Triangulo va desde Minimo hasta Maximo;
    su función de pertenencia son cuatro tramos de línea recta:
	 para valores menores a Minimo  vale 0.0
    desde Minimo hasta PrimerCorte es una recta que va de 0.0 a 1.0
    desde PrimerCorte hasta  Maximo es una recta que va de 1.0 a 0.0
    para valores mayores a Maximo  vale 0.0

    Tipo :               "Triángulo"
    Identificador :      1
    NumeroPuntosClaves : 3
    centroAltura:        En el pico del Triangulo
atributos:
    float PrimerCorte       parámetro de la función de pertenencia

////////////////////////////////////////*/


class ConjuntoTriangulo: public ConjuntoDifuso
{
public:
	ConjuntoTriangulo(const char* s, float min_, float pcor, float max_)
	{
		Nombre=new char[strlen(s)+1];
		strcpy(Nombre,s);
		Tipo=new char[20];
		strcpy(Tipo,IDS_CONJUNTOS_TIPO_1);
		Minimo=min_;
		PrimerCorte=pcor;
		Maximo=max_;
		NumeroPuntosClaves=3;
		CodigoC=new char[2000];
		CodigoCPP=new char[2000];
		Identificador=1;
	}
	~ConjuntoTriangulo()
	{
	}
	float pertenencia(float);
//	void recibirDatos(TWindow *parent, float mn, float mx);
	void ajustar(float nuevoMinimo,float nuevoMaximo)
	{
		float a,b,c;
		a=nuevoMinimo;
		b=nuevoMinimo+(primerCorte()-minimo())*(nuevoMaximo-nuevoMinimo)/(maximo()-minimo());
		c=nuevoMaximo;
		minimo(a);
		primerCorte(b);
		maximo(c);
	}
	void puntosClaves(float *puntos)
	{
		puntos[0]=minimo();
		puntos[1]=primerCorte();
		puntos[2]=maximo();
	}
	void nuevoPuntoClave(int punto, float x);
    float centroAltura()
    {
        return primerCorte();
    }
	char* codigoC();
	char* codigoCPP();
protected:
	float PrimerCorte;
	void primerCorte(float pcor)
	{
		PrimerCorte=pcor;
	}
	float primerCorte()
	{
		return PrimerCorte;
	}
};

/*////////////////////////////////////////
class ConjuntoPi

    El soporte de un Conjunto Tipo Pi va desde Minimo hasta Maximo;
    su función de pertenencia son cinco tramos de línea recta:
    para valores menores a Minimo  vale 0.0
    desde Minimo hasta PrimerCorte es una recta que va de 0.0 a 1.0
    desde PrimerCorte hasta SegundoCorte vale 1.0
    desde SegundoCorte hasta  Maximo es una recta que va de 1.0 a 0.0
    para valores mayores a Maximo  vale 0.0

    Tipo :               "Tipo Pi"
    Identificador :      2
    NumeroPuntosClaves : 4
    centroAltura:        En la mitad de la recta de valor 1.0
atributos:
    float PrimerCorte       parámetro de la función de pertenencia
    float SegundoCorte       parámetro de la función de pertenencia

////////////////////////////////////////*/


class ConjuntoPi: public ConjuntoDifuso
{
public:
	ConjuntoPi(const char* s, float min, float pcor, float scor, float max)
	{
		Nombre=new char[strlen(s)+1];
		strcpy(Nombre,s);
		Tipo=new char[20];
		strcpy(Tipo,IDS_CONJUNTOS_TIPO_2);
		Minimo=min;
		PrimerCorte=pcor;
		SegundoCorte=scor;
		Maximo=max;
		NumeroPuntosClaves=4;
		CodigoC=new char[2000];
		CodigoCPP=new char[2000];
		Identificador=2;
	}
	~ConjuntoPi()
	{
	}
	float pertenencia(float x);
//	void recibirDatos(TWindow *parent, float mn, float mx);
	void ajustar(float nuevoMinimo,float nuevoMaximo)
	{
		float a,b,c,d;
		a=nuevoMinimo;
		b=nuevoMinimo+(primerCorte()-minimo())*(nuevoMaximo-nuevoMinimo)/(maximo()-minimo());
		c=nuevoMinimo+(segundoCorte()-minimo())*(nuevoMaximo-nuevoMinimo)/(maximo()-minimo());
		d=nuevoMaximo;
		minimo(a);
		primerCorte(b);
      segundoCorte(c);
		maximo(d);
	}
	void puntosClaves(float *puntos)
	{
		puntos[0]=minimo();
		puntos[1]=primerCorte();
		puntos[2]=segundoCorte();
		puntos[3]=maximo();
	}
	void nuevoPuntoClave(int punto, float x);
    float centroAltura()
    {
        float cen;
        cen=(primerCorte()+segundoCorte())/2.0;
        return cen;
    }
	char* codigoC();
	char* codigoCPP();
protected:
	float PrimerCorte;
	float SegundoCorte;
	void primerCorte(float pcor)
	{
		PrimerCorte=pcor;
	}
	float primerCorte()
	{
		return PrimerCorte;
	}
	void segundoCorte(float scor)
	{
		SegundoCorte=scor;
	}
	float segundoCorte()
	{
		return SegundoCorte;
	}
};

/*////////////////////////////////////////
class ConjuntoGamma

    El soporte de un Conjunto Tipo Gamma va desde Minimo hasta Maximo;
    su función de pertenencia son tres tramos de línea recta:
    desde Minimo hasta PrimerCorte vale 0.0
    desde PrimerCorte hasta Maximo es una recta que va de 0.0 a 1.0
    para valores mayores a Maximo  vale 1.0

    Tipo :               "Tipo Gamma"
	 Identificador :      3
    NumeroPuntosClaves : 2
    centroAltura:        En la mitad de la recta de valor 1.0
atributos:
    float PrimerCorte       parámetro de la función de pertenencia

////////////////////////////////////////*/


class ConjuntoGamma: public ConjuntoDifuso
{
public:
	ConjuntoGamma(const char* s, float min, float pcor,  float max)
	{
		Nombre=new char[strlen(s)+1];
		strcpy(Nombre,s);
		Tipo=new char[20];
		strcpy(Tipo,IDS_CONJUNTOS_TIPO_3);
		Minimo=min;
		PrimerCorte=pcor;
		Maximo=max;
		NumeroPuntosClaves=2;
		CodigoC=new char[2000];
		CodigoCPP=new char[2000];
		Identificador=3;
	}
	~ConjuntoGamma()
	{
	}
	float pertenencia(float);
//	void recibirDatos(TWindow *parent, float mn, float mx);
	void ajustar(float nuevoMinimo,float nuevoMaximo)
	{
		float a,b,c;
		a=nuevoMinimo;
		b=nuevoMinimo+(primerCorte()-minimo())*(nuevoMaximo-nuevoMinimo)/(maximo()-minimo());
		c=nuevoMaximo;
		minimo(a);
		primerCorte(b);
		maximo(c);
	}
	void puntosClaves(float *puntos)
	{
		puntos[0]=minimo();
		puntos[1]=primerCorte();
	}
	void nuevoPuntoClave(int punto, float x);
    float centroAltura()
    {
        float cen;
        cen=(primerCorte()+maximo())/2.0;
        return cen;
    }
	char* codigoC();
	char* codigoCPP();
protected:
	float PrimerCorte;
	void primerCorte(float pcor)
	{
		PrimerCorte=pcor;
	}
	float primerCorte()
	{
		return PrimerCorte;
	}
};

/*////////////////////////////////////////
class ConjuntoZ

    El soporte de un Conjunto Tipo Z va desde Minimo hasta Maximo;
    su función de pertenencia son tres tramos de línea :
    desde Minimo hasta PrimerCorte vale 1.0
    desde PrimerCorte hasta Maximo es una curva en S que va de 1.0 a 0.0
    para valores mayores a Maximo  vale 0.0

    las curvas en S se calculan en dos tramos: hasta la mitad
    de la curva, y despues de la mitad

    Tipo :               "Tipo Z"
    Identificador :      4
    NumeroPuntosClaves : 2
    centroAltura:        En la mitad de la recta de valor 1.0
atributos:
    float PrimerCorte       parámetro de la función de pertenencia

////////////////////////////////////////*/


class ConjuntoZ: public ConjuntoDifuso
{
public:
	ConjuntoZ(const char* s, float min, float pcor, float max)
	{
		Nombre=new char[strlen(s)+1];
		strcpy(Nombre,s);
		Tipo=new char[20];
		strcpy(Tipo,IDS_CONJUNTOS_TIPO_4);
		Minimo=min;
		PrimerCorte=pcor;
		Maximo=max;
		NumeroPuntosClaves=2;
		CodigoC=new char[2000];
		CodigoCPP=new char[2000];
		Identificador=4;
	}
	~ConjuntoZ()
	{
	}
	float pertenencia(float);
//	void recibirDatos(TWindow *parent, float mn, float mx);
	void ajustar(float nuevoMinimo,float nuevoMaximo)
	{
		float a,b,c;
		a=nuevoMinimo;
		b=nuevoMinimo+(primerCorte()-minimo())*(nuevoMaximo-nuevoMinimo)/(maximo()-minimo());
		c=nuevoMaximo;
		minimo(a);
		primerCorte(b);
		maximo(c);
	}
	void puntosClaves(float *puntos)
	{
		puntos[0]=primerCorte();
		puntos[1]=maximo();
	}
	void nuevoPuntoClave(int punto, float x);
    float centroAltura()
    {
        float cen;
        cen=(minimo()+primerCorte())/2.0;
        return cen;
    }
	char* codigoC();
	char* codigoCPP();
protected:
	float PrimerCorte;
	void primerCorte(float pcor)
	{
		PrimerCorte=pcor;
	}
	float primerCorte()
	{
		return PrimerCorte;
	}
};

/*////////////////////////////////////////
class ConjuntoCampana

    El soporte de un Conjunto Tipo Campana va desde Minimo hasta Maximo;
    su función de pertenencia son cuatro tramos de línea :
    para valores menores a Minimo  vale 0.0
    desde Minimo hasta PrimerCorte es una curva en S que va de 0.0 a 1.0
    desde PrimerCorte hasta  Maximo es una curva en S que va de 1.0 a 0.0
    para valores mayores a Maximo  vale 0.0

    las curvas en S se calculan en dos tramos: hasta la mitad
    de la curva, y despues de la mitad

    Tipo :               "Campana"
    Identificador :      5
    NumeroPuntosClaves : 3
    centroAltura:        En el pico de la campana
atributos:
    float PrimerCorte       parámetro de la función de pertenencia

////////////////////////////////////////*/


class ConjuntoCampana: public ConjuntoDifuso
{
public:
	ConjuntoCampana(const char* s, float min, float pcor, float max)
	{
		Nombre=new char[strlen(s)+1];
		strcpy(Nombre,s);
		Tipo=new char[20];
		strcpy(Tipo,IDS_CONJUNTOS_TIPO_5);
		Minimo=min;
		PrimerCorte=pcor;
		Maximo=max;
		NumeroPuntosClaves=3;
		CodigoC=new char[2000];
		CodigoCPP=new char[2000];
		Identificador=5;
	}
	~ConjuntoCampana()
	{
	}
	float pertenencia(float);
//	void recibirDatos(TWindow *parent, float mn, float mx);
	void ajustar(float nuevoMinimo,float nuevoMaximo)
	{
		float a,b,c;
		a=nuevoMinimo;
		b=nuevoMinimo+(primerCorte()-minimo())*(nuevoMaximo-nuevoMinimo)/(maximo()-minimo());
		c=nuevoMaximo;
		minimo(a);
		primerCorte(b);
		maximo(c);
	}
	void puntosClaves(float *puntos)
	{
		puntos[0]=minimo();
		puntos[1]=primerCorte();
		puntos[2]=maximo();
	}
	void nuevoPuntoClave(int punto, float x);
    float centroAltura()
    {
        return primerCorte();
    }
	char* codigoC();
	char* codigoCPP();
protected:
	float PrimerCorte;
	void primerCorte(float pcor)
	{
		PrimerCorte=pcor;
	}
	float primerCorte()
	{
		return PrimerCorte;
	}
};

/*////////////////////////////////////////
class ConjuntoPiCampana

    El soporte de un Conjunto Tipo Pi-Campana va desde Minimo hasta Maximo;
    su función de pertenencia son cinco tramos de línea :
    para valores menores a Minimo  vale 0.0
    desde Minimo hasta PrimerCorte es una curva en S que va de 0.0 a 1.0
    desde PrimerCorte hasta SegundoCorte es una recta que vale 1.0
    desde SegundoCorte hasta  Maximo es una curva en S que va de 1.0 a 0.0
    para valores mayores a Maximo  vale 0.0

    las curvas en S se calculan en dos tramos: hasta la mitad
    de la curva, y despues de la mitad

    Tipo :               "PiCampana"
    Identificador :      6
    NumeroPuntosClaves : 4
    centroAltura:        En la mitad de la recta de valor 1.0
atributos:
    float PrimerCorte       parámetro de la función de pertenencia
    float SegundoCorte       parámetro de la función de pertenencia

////////////////////////////////////////*/


class ConjuntoPiCampana: public ConjuntoDifuso
{
public:
	ConjuntoPiCampana(const char* s, float min, float pcor, float scor, float max)
	{
		Nombre=new char[strlen(s)+1];
		strcpy(Nombre,s);
		Tipo=new char[20];
		strcpy(Tipo,IDS_CONJUNTOS_TIPO_6);
		Minimo=min;
		PrimerCorte=pcor;
		SegundoCorte=scor;
		Maximo=max;
		NumeroPuntosClaves=4;
		CodigoC=new char[2000];
		CodigoCPP=new char[2000];
		Identificador=6;
	}
	~ConjuntoPiCampana()
	{
	}
	float pertenencia(float);
//	void recibirDatos(TWindow *parent, float mn, float mx);
	void ajustar(float nuevoMinimo,float nuevoMaximo)
	{
		float a,b,c,d;
		a=nuevoMinimo;
		b=nuevoMinimo+(primerCorte()-minimo())*(nuevoMaximo-nuevoMinimo)/(maximo()-minimo());
		c=nuevoMinimo+(segundoCorte()-minimo())*(nuevoMaximo-nuevoMinimo)/(maximo()-minimo());
		d=nuevoMaximo;
		minimo(a);
		primerCorte(b);
		segundoCorte(c);
		maximo(d);
	}
	void puntosClaves(float *puntos)
	{
		puntos[0]=minimo();
		puntos[1]=primerCorte();
		puntos[2]=segundoCorte();
		puntos[3]=maximo();
	}
	void nuevoPuntoClave(int punto, float x);
    float centroAltura()
    {
        float cen;
        cen=(minimo()+primerCorte()+segundoCorte())/2.0;
        return cen;
    }
	char* codigoC();
	char* codigoCPP();
protected:
	float PrimerCorte;
	float SegundoCorte;
	void primerCorte(float pcor)
	{
		PrimerCorte=pcor;
	}
	float primerCorte()
	{
		return PrimerCorte;
	}
	void segundoCorte(float scor)
	{
		SegundoCorte=scor;
	}
	float segundoCorte()
	{
		return SegundoCorte;
	}
};

/*////////////////////////////////////////
class ConjuntoS

    El soporte de un Conjunto Tipo S va desde Minimo hasta Maximo;
    su función de pertenencia son tres tramos de línea :
    desde Minimo hasta PrimerCorte vale 0.0
    desde PrimerCorte hasta Maximo es una curva en S que va de 0.0 a 1.0
    para valores mayores a Maximo  vale 1.0

    las curvas en S se calculan en dos tramos: hasta la mitad
    de la curva, y despues de la mitad

    Tipo :               "Tipo S"
    Identificador :      7
    NumeroPuntosClaves : 2
    centroAltura:        En la mitad de la recta de valor 1.0
atributos:
    float PrimerCorte       parámetro de la función de pertenencia

////////////////////////////////////////*/


class ConjuntoS: public ConjuntoDifuso
{
public:
	ConjuntoS(const char* s, float min, float pcor, float max)
	{
		Nombre=new char[strlen(s)+1];
		strcpy(Nombre,s);
		Tipo=new char[20];
		strcpy(Tipo,IDS_CONJUNTOS_TIPO_7);
		Minimo=min;
		PrimerCorte=pcor;
		Maximo=max;
		NumeroPuntosClaves=2;
		CodigoC=new char[2000];
		CodigoCPP=new char[2000];
		Identificador=7;
	}
	~ConjuntoS()
	{
	}
	float pertenencia(float);
//	void recibirDatos(TWindow *parent, float mn, float mx);
	void ajustar(float nuevoMinimo,float nuevoMaximo)
	{
		float a,b,c;
		a=nuevoMinimo;
		b=nuevoMinimo+(primerCorte()-minimo())*(nuevoMaximo-nuevoMinimo)/(maximo()-minimo());
		c=nuevoMaximo;
		minimo(a);
		primerCorte(b);
		maximo(c);
	}
	void puntosClaves(float *puntos)
	{
		puntos[0]=minimo();
		puntos[1]=primerCorte();
	}
	void nuevoPuntoClave(int punto, float x);
    float centroAltura()
    {
        float cen;
        cen=(primerCorte()+maximo())/2.0;
        return cen;
    }
	char* codigoC();
	char* codigoCPP();
protected:
	float PrimerCorte;
	void primerCorte(float pcor)
	{
		PrimerCorte=pcor;
	}
	float primerCorte()
	{
		return PrimerCorte;
	}
};


/*////////////////////////////////////////
class ConjuntoSinglenton

    El soporte de un Conjunto Tipo S va desde Minimo hasta Maximo;
    su función de pertenencia es un rectangulo de ancho Delta,
    con centro en Pico

	 Tipo :               "Singlenton"
	 Identificador :      8
	 NumeroPuntosClaves : 2
	 centroAltura:        En la mitad de la recta de valor 1.0
atributos:
	 float Delta       parámetro de la función de pertenencia
	 float Pico       parámetro de la función de pertenencia

////////////////////////////////////////*/


class ConjuntoSinglenton: public ConjuntoDifuso
{
public:
	ConjuntoSinglenton(const char* s, float pi, float de)
	{
		Nombre=new char[strlen(s)+1];
		strcpy(Nombre,s);
		Tipo=new char[20];
		strcpy(Tipo,IDS_CONJUNTOS_TIPO_8);
		Pico=pi;
		Delta=de;
		Minimo=Pico-Delta/2;
		Maximo=Pico+Delta/2;
		NumeroPuntosClaves=2;
		CodigoC=new char[2000];
		CodigoCPP=new char[2000];
		Identificador=8;
	}
	~ConjuntoSinglenton()
	{
	}
	float pico(){return Pico;}
	float delta(){return Delta;}
	float pertenencia(float);
//	void recibirDatos(TWindow *parent, float mn, float mx);
	void ajustar(float nuevoMinimo,float nuevoMaximo)
	{
		float a,b;
		a=nuevoMinimo;
		b=nuevoMaximo;
		minimo(a);
		maximo(b);
		Pico=(a+b)/2;
      Delta=b-a;
	}
	void puntosClaves(float *puntos)
	{
		puntos[0]=minimo();
		puntos[1]=maximo();
	}
	void nuevoPuntoClave(int punto, float x);
	 float centroAltura()
	 {
		  return Pico;
	 }
	char* codigoC();
	char* codigoCPP();
protected:
	float Delta;
	float Pico;
};


#endif // CONJUNTODIFUSO_H

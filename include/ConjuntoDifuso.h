#ifndef CONJUNTODIFUSO_H
#define CONJUNTODIFUSO_H

#include <cstdio>
#include <iostream>
#include <string>
#include <wx/wx.h>

using namespace std;


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
	double Minimo;           límite inferior del Soporte
	double Maximo;           límite superior del Soporte
	int NumeroPuntosClaves; Número de puntos que se pueden editar gráficamente (ver DialogVariableEntrada)
	int Identificador;      identificador de Tipo, necesario para crear el hijo adecuado al leer un archivo

procedimientos
	char* nombre()          consultor de Nombre
	char* nombre(char* s)   modificador de Nombre
	char* tipo()            consultor de Tipo
	void minimo(double min)  modificador de Minimo
	double minimo()          consultor de Minimo
	void maximo(double max)  modificador de Maximo
	double maximo()          consultor de Maximo
	int identificador()     consultor de Identificador
	int numeroPuntosClaves()  consultor de NumeroPuntosClaves

Las funciones virtual=0 deben ser redefinidas por los hijos

	virtual void puntosClaves(double *puntos)=0;
                        en el arreglo puntos retorna los valores de los puntos editables gráficamente (ver DialogVariableEntrada)
	virtual void nuevoPuntoClave(int punto, double x)=0;
                        reasigna el valor de un punto que ha sido editado gráficamente (ver DialogVariableEntrada)
	virtual double pertenencia(double x)=0;
                        calcula la función de pertenencia para x
	virtual void recibirDatos(TWindow *parent,double mn,double mx)=0;
                        muestra un cuador de dialogo para editar el ConjuntoDifuso no graficamente
	virtual void ajustar(double nuevoMinimo, double nuevoMaximo)=0;
                        redefine el ConjuntoDifuso cuando cambia el Universo de Discurso de la Variable a la cual pertenece
    virtual double centroAltura()=0;
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
	}
	virtual ~ConjuntoDifuso()
	{
	}
	string nombre() const
	{
		return Nombre;
	}
	void nombre(string s)
	{
		Nombre=s;
	}
	string tipo()
	{
		return tipo(Identificador);
	}
	static string tipo(int caso);
	void minimo(double min)
	{
		Minimo=min;
	}
	double minimo()
	{
		return Minimo;
	}
	void maximo(double max)
	{
		Maximo=max;
	}
	double maximo()
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
	double verificarPuntoClave(int i,double x);
	virtual void puntosClaves(double *puntos)=0;
	virtual void nuevoPuntoClave(int punto, double x)=0;
	virtual double pertenencia(double x)=0;
	virtual void ajustar(double nuevoMinimo, double nuevoMaximo)=0;
	virtual double centroAltura()=0;
	virtual string codigoC()=0;
	virtual string codigoCPP()=0;
	BOOL operator==(const ConjuntoDifuso& other)
	{
		return ( ( Nombre == other.Nombre)&
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
	string Nombre;
	double Minimo;
	double Maximo;
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
    double PrimerCorte       parámetro de la función de pertenencia

////////////////////////////////////////*/

class ConjuntoL: public ConjuntoDifuso
{
public:
	ConjuntoL(string s, double min, double pcor, double max)
	{
		Nombre=s;
		Minimo=min;
		PrimerCorte=pcor;
		Maximo=max;
		NumeroPuntosClaves=2;
		Identificador=0;
	}
	~ConjuntoL()
	{
	}
	double pertenencia(double);
	void ajustar(double nuevoMinimo,double nuevoMaximo)
	{
		double a,b,c;
		a=nuevoMinimo;
		b=nuevoMinimo+(primerCorte()-minimo())*(nuevoMaximo-nuevoMinimo)/(maximo()-minimo());
		c=nuevoMaximo;
		minimo(a);
		primerCorte(b);
		maximo(c);
	}
	void puntosClaves(double *puntos)
	{
		puntos[0]=primerCorte();
		puntos[1]=maximo();
	}
	void nuevoPuntoClave(int punto, double x);
	double centroAltura()
  {
    double cen;
    cen=(minimo()+primerCorte())/2.0;
    return cen;
  }
	string codigoC();
	string codigoCPP();
protected:
	double PrimerCorte;
	void primerCorte(double pcor)
	{
		PrimerCorte=pcor;
	}
	double primerCorte()
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
    double PrimerCorte       parámetro de la función de pertenencia

////////////////////////////////////////*/


class ConjuntoTriangulo: public ConjuntoDifuso
{
public:
	ConjuntoTriangulo(string s, double min_, double pcor, double max_)
	{
		Nombre=s;
		Minimo=min_;
		PrimerCorte=pcor;
		Maximo=max_;
		NumeroPuntosClaves=3;
		Identificador=1;
	}
	~ConjuntoTriangulo()
	{
	}
	double pertenencia(double);
//	void recibirDatos(TWindow *parent, double mn, double mx);
	void ajustar(double nuevoMinimo,double nuevoMaximo)
	{
		double a,b,c;
		a=nuevoMinimo;
		b=nuevoMinimo+(primerCorte()-minimo())*(nuevoMaximo-nuevoMinimo)/(maximo()-minimo());
		c=nuevoMaximo;
		minimo(a);
		primerCorte(b);
		maximo(c);
	}
	void puntosClaves(double *puntos)
	{
		puntos[0]=minimo();
		puntos[1]=primerCorte();
		puntos[2]=maximo();
	}
	void nuevoPuntoClave(int punto, double x);
    double centroAltura()
    {
        return primerCorte();
    }
	string codigoC();
	string codigoCPP();
protected:
	double PrimerCorte;
	void primerCorte(double pcor)
	{
		PrimerCorte=pcor;
	}
	double primerCorte()
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
    double PrimerCorte       parámetro de la función de pertenencia
    double SegundoCorte       parámetro de la función de pertenencia

////////////////////////////////////////*/


class ConjuntoPi: public ConjuntoDifuso
{
public:
	ConjuntoPi(string s, double min, double pcor, double scor, double max)
	{
		Nombre=s;
		Minimo=min;
		PrimerCorte=pcor;
		SegundoCorte=scor;
		Maximo=max;
		NumeroPuntosClaves=4;
		Identificador=2;
	}
	~ConjuntoPi()
	{
	}
	double pertenencia(double x);
//	void recibirDatos(TWindow *parent, double mn, double mx);
	void ajustar(double nuevoMinimo,double nuevoMaximo)
	{
		double a,b,c,d;
		a=nuevoMinimo;
		b=nuevoMinimo+(primerCorte()-minimo())*(nuevoMaximo-nuevoMinimo)/(maximo()-minimo());
		c=nuevoMinimo+(segundoCorte()-minimo())*(nuevoMaximo-nuevoMinimo)/(maximo()-minimo());
		d=nuevoMaximo;
		minimo(a);
		primerCorte(b);
      segundoCorte(c);
		maximo(d);
	}
	void puntosClaves(double *puntos)
	{
		puntos[0]=minimo();
		puntos[1]=primerCorte();
		puntos[2]=segundoCorte();
		puntos[3]=maximo();
	}
	void nuevoPuntoClave(int punto, double x);
    double centroAltura()
    {
        double cen;
        cen=(primerCorte()+segundoCorte())/2.0;
        return cen;
    }
	string codigoC();
	string codigoCPP();
protected:
	double PrimerCorte;
	double SegundoCorte;
	void primerCorte(double pcor)
	{
		PrimerCorte=pcor;
	}
	double primerCorte()
	{
		return PrimerCorte;
	}
	void segundoCorte(double scor)
	{
		SegundoCorte=scor;
	}
	double segundoCorte()
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
    double PrimerCorte       parámetro de la función de pertenencia

////////////////////////////////////////*/


class ConjuntoGamma: public ConjuntoDifuso
{
public:
	ConjuntoGamma(string s, double min, double pcor,  double max)
	{
		Nombre=s;
		Minimo=min;
		PrimerCorte=pcor;
		Maximo=max;
		NumeroPuntosClaves=2;
		Identificador=3;
	}
	~ConjuntoGamma()
	{
	}
	double pertenencia(double);
//	void recibirDatos(TWindow *parent, double mn, double mx);
	void ajustar(double nuevoMinimo,double nuevoMaximo)
	{
		double a,b,c;
		a=nuevoMinimo;
		b=nuevoMinimo+(primerCorte()-minimo())*(nuevoMaximo-nuevoMinimo)/(maximo()-minimo());
		c=nuevoMaximo;
		minimo(a);
		primerCorte(b);
		maximo(c);
	}
	void puntosClaves(double *puntos)
	{
		puntos[0]=minimo();
		puntos[1]=primerCorte();
	}
	void nuevoPuntoClave(int punto, double x);
    double centroAltura()
    {
        double cen;
        cen=(primerCorte()+maximo())/2.0;
        return cen;
    }
	string codigoC();
	string codigoCPP();
protected:
	double PrimerCorte;
	void primerCorte(double pcor)
	{
		PrimerCorte=pcor;
	}
	double primerCorte()
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
    double PrimerCorte       parámetro de la función de pertenencia

////////////////////////////////////////*/


class ConjuntoZ: public ConjuntoDifuso
{
public:
	ConjuntoZ(string s, double min, double pcor, double max)
	{
		Nombre=s;
		Minimo=min;
		PrimerCorte=pcor;
		Maximo=max;
		NumeroPuntosClaves=2;
		Identificador=4;
	}
	~ConjuntoZ()
	{
	}
	double pertenencia(double);
//	void recibirDatos(TWindow *parent, double mn, double mx);
	void ajustar(double nuevoMinimo,double nuevoMaximo)
	{
		double a,b,c;
		a=nuevoMinimo;
		b=nuevoMinimo+(primerCorte()-minimo())*(nuevoMaximo-nuevoMinimo)/(maximo()-minimo());
		c=nuevoMaximo;
		minimo(a);
		primerCorte(b);
		maximo(c);
	}
	void puntosClaves(double *puntos)
	{
		puntos[0]=primerCorte();
		puntos[1]=maximo();
	}
	void nuevoPuntoClave(int punto, double x);
    double centroAltura()
    {
        double cen;
        cen=(minimo()+primerCorte())/2.0;
        return cen;
    }
	string codigoC();
	string codigoCPP();
protected:
	double PrimerCorte;
	void primerCorte(double pcor)
	{
		PrimerCorte=pcor;
	}
	double primerCorte()
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
    double PrimerCorte       parámetro de la función de pertenencia

////////////////////////////////////////*/


class ConjuntoCampana: public ConjuntoDifuso
{
public:
	ConjuntoCampana(string s, double min, double pcor, double max)
	{
		Nombre=s;
		Minimo=min;
		PrimerCorte=pcor;
		Maximo=max;
		NumeroPuntosClaves=3;
		Identificador=5;
	}
	~ConjuntoCampana()
	{
	}
	double pertenencia(double);
//	void recibirDatos(TWindow *parent, double mn, double mx);
	void ajustar(double nuevoMinimo,double nuevoMaximo)
	{
		double a,b,c;
		a=nuevoMinimo;
		b=nuevoMinimo+(primerCorte()-minimo())*(nuevoMaximo-nuevoMinimo)/(maximo()-minimo());
		c=nuevoMaximo;
		minimo(a);
		primerCorte(b);
		maximo(c);
	}
	void puntosClaves(double *puntos)
	{
		puntos[0]=minimo();
		puntos[1]=primerCorte();
		puntos[2]=maximo();
	}
	void nuevoPuntoClave(int punto, double x);
    double centroAltura()
    {
        return primerCorte();
    }
	string codigoC();
	string codigoCPP();
protected:
	double PrimerCorte;
	void primerCorte(double pcor)
	{
		PrimerCorte=pcor;
	}
	double primerCorte()
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
    double PrimerCorte       parámetro de la función de pertenencia
    double SegundoCorte       parámetro de la función de pertenencia

////////////////////////////////////////*/


class ConjuntoPiCampana: public ConjuntoDifuso
{
public:
	ConjuntoPiCampana(string s, double min, double pcor, double scor, double max)
	{
		Nombre=s;
		Minimo=min;
		PrimerCorte=pcor;
		SegundoCorte=scor;
		Maximo=max;
		NumeroPuntosClaves=4;
		Identificador=6;
	}
	~ConjuntoPiCampana()
	{
	}
	double pertenencia(double);
//	void recibirDatos(TWindow *parent, double mn, double mx);
	void ajustar(double nuevoMinimo,double nuevoMaximo)
	{
		double a,b,c,d;
		a=nuevoMinimo;
		b=nuevoMinimo+(primerCorte()-minimo())*(nuevoMaximo-nuevoMinimo)/(maximo()-minimo());
		c=nuevoMinimo+(segundoCorte()-minimo())*(nuevoMaximo-nuevoMinimo)/(maximo()-minimo());
		d=nuevoMaximo;
		minimo(a);
		primerCorte(b);
		segundoCorte(c);
		maximo(d);
	}
	void puntosClaves(double *puntos)
	{
		puntos[0]=minimo();
		puntos[1]=primerCorte();
		puntos[2]=segundoCorte();
		puntos[3]=maximo();
	}
	void nuevoPuntoClave(int punto, double x);
    double centroAltura()
    {
        double cen;
        cen=(minimo()+primerCorte()+segundoCorte())/2.0;
        return cen;
    }
	string codigoC();
	string codigoCPP();
protected:
	double PrimerCorte;
	double SegundoCorte;
	void primerCorte(double pcor)
	{
		PrimerCorte=pcor;
	}
	double primerCorte()
	{
		return PrimerCorte;
	}
	void segundoCorte(double scor)
	{
		SegundoCorte=scor;
	}
	double segundoCorte()
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
    double PrimerCorte       parámetro de la función de pertenencia

////////////////////////////////////////*/


class ConjuntoS: public ConjuntoDifuso
{
public:
	ConjuntoS(string s, double min, double pcor, double max)
	{
		Nombre=s;
		Minimo=min;
		PrimerCorte=pcor;
		Maximo=max;
		NumeroPuntosClaves=2;
		Identificador=7;
	}
	~ConjuntoS()
	{
	}
	double pertenencia(double);
//	void recibirDatos(TWindow *parent, double mn, double mx);
	void ajustar(double nuevoMinimo,double nuevoMaximo)
	{
		double a,b,c;
		a=nuevoMinimo;
		b=nuevoMinimo+(primerCorte()-minimo())*(nuevoMaximo-nuevoMinimo)/(maximo()-minimo());
		c=nuevoMaximo;
		minimo(a);
		primerCorte(b);
		maximo(c);
	}
	void puntosClaves(double *puntos)
	{
		puntos[0]=minimo();
		puntos[1]=primerCorte();
	}
	void nuevoPuntoClave(int punto, double x);
    double centroAltura()
    {
        double cen;
        cen=(primerCorte()+maximo())/2.0;
        return cen;
    }
	string codigoC();
	string codigoCPP();
protected:
	double PrimerCorte;
	void primerCorte(double pcor)
	{
		PrimerCorte=pcor;
	}
	double primerCorte()
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
	 double Delta       parámetro de la función de pertenencia
	 double Pico       parámetro de la función de pertenencia

////////////////////////////////////////*/


class ConjuntoSinglenton: public ConjuntoDifuso
{
public:
	ConjuntoSinglenton(string s, double pi, double de)
	{
		Nombre=s;
		Pico=pi;
		Delta=de;
		Minimo=Pico-Delta/2;
		Maximo=Pico+Delta/2;
		NumeroPuntosClaves=2;
		Identificador=8;
	}
	~ConjuntoSinglenton()
	{
	}
	double pico(){return Pico;}
	double delta(){return Delta;}
	double pertenencia(double);
//	void recibirDatos(TWindow *parent, double mn, double mx);
	void ajustar(double nuevoMinimo,double nuevoMaximo)
	{
		double a,b;
		a=nuevoMinimo;
		b=nuevoMaximo;
		minimo(a);
		maximo(b);
		Pico=(a+b)/2;
      Delta=b-a;
	}
	void puntosClaves(double *puntos)
	{
		puntos[0]=minimo();
		puntos[1]=maximo();
	}
	void nuevoPuntoClave(int punto, double x);
	 double centroAltura()
	 {
		  return Pico;
	 }
	string codigoC();
	string codigoCPP();
protected:
	double Delta;
	double Pico;
};


#endif // CONJUNTODIFUSO_H

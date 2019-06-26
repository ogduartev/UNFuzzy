#ifndef IMPLICACION_H
#define IMPLICACION_H

#include <iostream>
#include <string>
#include <wx/wx.h>
using namespace std;

#include <math.h>

/*///////////////////////////////////////
class Implicacion
atributos
	char *Tipo;                 Identificador de tipo (Ej. "Minimo" ) ver hijos	char *CodigoC;
	char *CodigoC;            Texto necesario para generar Código C
	char *CodigoCPP;            Texto necesario para generar Código C++
	int Identificador;          identificador de Tipo, necesario para crear el hijo adecuado al leer un archivo

procedimientos:
	char* tipo()                  consultor de Tipo
	int identificador()           consultor de Identificador

Las funciones virtual=0 deben ser redefinidas por los hijos

	virtual double defecto()=0;
                    determina si la Implicacion es ImplicacionT_Norma ó ImplicacionIf_Then
	virtual double implica(double, double)=0;
                    efectúa la operación matemática
	virtual char* codigoC()=0;
                        entrega el texto necesario para generar Codigo C (ver DialogGenerarCodigo)
	virtual char* codigoCPP()=0;
                        entrega el texto necesario para generar Codigo C++ (ver DialogGenerarCodigo)
//////////////////////////////////////////*/


class Implicacion
{
public:
	Implicacion()
	{
	}
	virtual ~Implicacion()
	{
	}
	virtual double implica(double,double)=0;
	virtual double defecto()=0;
	virtual string codigoC()=0;
	virtual string codigoCPP()=0;
	string tipo()
	{
		return tipo(Identificador);
	}
	static string tipo(int caso);
	int identificador()
	{
		return Identificador;
	}

protected:
	int Identificador;
};

/*/////////////////////////////////////////
class ImplicacionT_Norma:public Implicacion

esta clase sólo redefine la funcion defecto(), devolviendo 0.0
///////////////////////////////////////////*/

class ImplicacionT_Norma:public Implicacion
{
public:
	ImplicacionT_Norma(){}
	~ImplicacionT_Norma(){}
	double defecto()
	{
		return 0;
	}
	string codigoC()=0;
	string codigoCPP()=0;
	virtual double implica(double x, double y)=0;
protected:
};


/*/////////////////////////////////////////
class ImplicacionIf_Then:public Implicacion

esta clase sólo redefine la funcion defecto(), devolviendo 1.0
///////////////////////////////////////////*/

class ImplicacionIf_Then:public Implicacion
{
public:
	ImplicacionIf_Then(){}
	~ImplicacionIf_Then(){}
	double defecto()
	{
		return 1;
	}
	virtual double implica(double x, double y)=0;
	string codigoC()=0;
	string codigoCPP()=0;
protected:
};


/*//////////////////////////////////////////
class ImplicacionProducto:public ImplicacionT_Norma

    implicacion del producto

    Identificador=0

////////////////////////////////////////////*/


class ImplicacionProducto:public ImplicacionT_Norma
{
public:
	ImplicacionProducto()
	{
		Identificador=0;
	}
	~ImplicacionProducto(){}
	string codigoC()
	{
		wxString CodigoC="";
		CodigoC << ("    	rel=x*y;");
		return std::string(CodigoC.mb_str());
	}
	string codigoCPP()
	{
		wxString CodigoCPP="";
		CodigoCPP=("ImplicacionProducto();");
		return std::string(CodigoCPP.mb_str());
	}
	double implica(double x, double y)
	{
		double z;
		z=x*y;
		return z;
	}
protected:
};

/*//////////////////////////////////////////
class ImplicacionMinimo:public ImplicacionT_Norma

    implicacion del minimo

    Identificador=1

////////////////////////////////////////////*/

class ImplicacionMinimo:public ImplicacionT_Norma
{
public:
	ImplicacionMinimo()
	{
		Identificador=1;
	}
	~ImplicacionMinimo(){}
	string codigoC()
	{
		wxString CodigoC="";
		CodigoC << ("    if(x<y)\r\n");
		CodigoC << ("    {\r\n");
		CodigoC << ("    	rel=x;\r\n");
		CodigoC << ("    }else\r\n");
		CodigoC << ("    {\r\n");
		CodigoC << ("    	rel=y;\r\n");
		CodigoC << ("    }");
		return std::string(CodigoC.mb_str());
	}
	string codigoCPP()
	{
		wxString CodigoCPP="";
		CodigoCPP=("ImplicacionMinimo();");
		return std::string(CodigoCPP.mb_str());
	}
	double implica(double x, double y)
	{
		double z;
		if(x<y)
			z=x;
		else
			z=y;
		return z;
	}
protected:
};

/*//////////////////////////////////////////
class ImplicacionKleenDienes:public ImplicacionIf_Then

    implicacion de Kleene-Dienes

    Identificador=2

////////////////////////////////////////////*/

class ImplicacionKleenDienes:public ImplicacionIf_Then
{
public:
	ImplicacionKleenDienes()
	{
		Identificador=2;
	}
	~ImplicacionKleenDienes(){}
	string codigoC()
	{
		wxString CodigoC="";
		CodigoC << ("    x=1-x;\r\n");
		CodigoC << ("    if(x>y)\r\n");
		CodigoC << ("    	rel=x;\r\n");
		CodigoC << ("    else\r\n");
		CodigoC << ("    	rel=y;");
		return std::string(CodigoC.mb_str());
	}
	string codigoCPP()
	{
		wxString CodigoCPP="";
		CodigoCPP=("ImplicacionKleenDienes();");
		return std::string(CodigoCPP.mb_str());
	}
	double implica(double x, double y)
	{
		double rel;
		x=1-x;
		if(x>y)
			rel=x;
		else
			rel=y;
		return(rel);
	}
protected:
};


/*//////////////////////////////////////////
class ImplicacionLukasiewicz:public ImplicacionIf_Then

    implicacion de Lukasiewicz

    Identificador=3

////////////////////////////////////////////*/

class ImplicacionLukasiewicz:public ImplicacionIf_Then
{
public:
	ImplicacionLukasiewicz()
	{
		Identificador=3;
	}
	~ImplicacionLukasiewicz(){}
	string codigoC()
	{
		wxString CodigoC="";
		CodigoC << ("    if(x<y)\r\n");
		CodigoC << ("    	rel=x;\r\n");
		CodigoC << ("    else\r\n");
		CodigoC << ("    	rel=y;\r\n");
		CodigoC << ("    x=1-x;\r\n");
		CodigoC << ("    if(rel<x)\r\n");
		CodigoC << ("    	rel=x;");
		return std::string(CodigoC.mb_str());
	}
	string codigoCPP()
	{
		wxString CodigoCPP="";
		CodigoCPP=("ImplicacionLukasiewicz();");
		return std::string(CodigoCPP.mb_str());
	}
	double implica(double x, double y)
	{
		double rel;
		rel=1-x+y;
		if(rel>1)
			rel=1;
		return(rel);
	}
protected:
};


/*//////////////////////////////////////////
class ImplicacionZadeh:public ImplicacionIf_Then

    implicacion de Zadeh

    Identificador=4

////////////////////////////////////////////*/

class ImplicacionZadeh:public ImplicacionIf_Then
{
public:
	ImplicacionZadeh()
	{
		Identificador=4;
	}
	~ImplicacionZadeh(){}
	string codigoC()
	{
		wxString CodigoC="";
		CodigoC << ("    if(x<y)\r\n");
		CodigoC << ("    	rel=x;\r\n");
		CodigoC << ("    else\r\n");
		CodigoC << ("    	rel=y;\r\n");
		CodigoC << ("    x=1-x;\r\n");
		CodigoC << ("    if(rel<x)\r\n");
		CodigoC << ("    	rel=x;");
		return std::string(CodigoC.mb_str());
	}
	string codigoCPP()
	{
		wxString CodigoCPP="";
		CodigoCPP=("ImplicacionZadeh();");
		return std::string(CodigoCPP.mb_str());
	}
	double implica(double x, double y)
	{
		double rel;
		if(x<y)
			rel=x;
		else
			rel=y;
		x=1-x;
		if(rel<x)
			rel=x;
		return(rel);
	}
protected:
};


/*//////////////////////////////////////////
class ImplicacionEstocastica:public ImplicacionIf_Then

    implicacion estocástica

    Identificador=5

////////////////////////////////////////////*/

class ImplicacionEstocastica:public ImplicacionIf_Then
{
public:
	ImplicacionEstocastica()
	{
		Identificador=5;
	}
	~ImplicacionEstocastica(){}
	string codigoC()
	{
		wxString CodigoC="";
		CodigoC << ("    rel=x*y;\r\n");
		CodigoC << ("    x=1-x;\r\n");
		CodigoC << ("    if(rel<x)\r\n");
		CodigoC << ("    	rel=x;");
		return std::string(CodigoC.mb_str());
	}
	string codigoCPP()
	{
		wxString CodigoCPP="";
		CodigoCPP=("ImplicacionEstocastica();");
		return std::string(CodigoCPP.mb_str());
	}
	double implica(double x, double y)
	{
		double rel;
		rel=x*y;
		x=1-x;
		if(rel<x)
			rel=x;
		return(rel);
	}
protected:
};


/*//////////////////////////////////////////
class ImplicacionGoguen:public ImplicacionIf_Then

    implicacion de Goguen

    Identificador=6

////////////////////////////////////////////*/

class ImplicacionGoguen:public ImplicacionIf_Then
{
public:
	ImplicacionGoguen()
	{
		Identificador=6;
	}
	~ImplicacionGoguen(){}
	string codigoC()
	{
		wxString CodigoC="";
		CodigoC << ("    if(x>0.00001)\r\n");
		CodigoC << ("    	rel=y/x;\r\n");
		CodigoC << ("    else\r\n");
		CodigoC << ("    	rel=1000;\r\n");
		CodigoC << ("    if(rel>1)\r\n");
		CodigoC << ("    	rel=1;");
		return std::string(CodigoC.mb_str());
	}
	string codigoCPP()
	{
		wxString CodigoCPP="";
		CodigoCPP=("ImplicacionGoguen();");
		return std::string(CodigoCPP.mb_str());
	}
	double implica(double x, double y)
	{
		double rel;
		if(x>0.00001)
			rel=y/x;
		else
			rel=1000;
		if(rel>1)
			rel=1;
		return(rel);
	}
protected:
};


/*//////////////////////////////////////////
class ImplicacionGodel:public ImplicacionIf_Then

    implicacion de Godel

    Identificador=7

////////////////////////////////////////////*/

class ImplicacionGodel:public ImplicacionIf_Then
{
public:
	ImplicacionGodel()
	{
		Identificador=7;
	}
	~ImplicacionGodel(){}
	string codigoC()
	{
		wxString CodigoC="";
		CodigoC << ("    if(x<=y)\r\n");
		CodigoC << ("    	rel=1;\r\n");
		CodigoC << ("    else\r\n");
		CodigoC << ("    	rel=y;");
		return std::string(CodigoC.mb_str());
	}
	string codigoCPP()
	{
		wxString CodigoCPP="";
		CodigoCPP=("ImplicacionGodel();");
		return std::string(CodigoCPP.mb_str());
	}
	double implica(double x, double y)
	{
		double rel;
		if(x<=y)
			rel=1;
		else
			rel=y;
		return(rel);
	}
protected:
};


/*//////////////////////////////////////////
class ImplicacionAguda:public ImplicacionIf_Then

    implicacion Aguda

    Identificador=8

////////////////////////////////////////////*/

class ImplicacionAguda:public ImplicacionIf_Then
{
public:
	ImplicacionAguda()
	{
		Identificador=8;
	}
	~ImplicacionAguda(){}
	string codigoC()
	{
		wxString CodigoC="";
		CodigoC << ("    if(x<=y)\r\n");
		CodigoC << ("    	rel=1;\r\n");
		CodigoC << ("    else\r\n");
		CodigoC << ("    	rel=0;");
		return std::string(CodigoC.mb_str());
	}
	string codigoCPP()
	{
		wxString CodigoCPP="";
		CodigoCPP=("ImplicacionAguda();");
		return std::string(CodigoCPP.mb_str());
	}
	double implica(double x, double y)
	{
		double rel;
		if(x<=y)
			rel=1;
		else
			rel=0;
		return(rel);
	}
protected:
};




#endif // IMPLICACION_H

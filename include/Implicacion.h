#ifndef IMPLICACION_H
#define IMPLICACION_H

#include <wx/wx.h>
#include <math.h>
#include <Idiomas.h>

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

	virtual float defecto()=0;
                    determina si la Implicacion es ImplicacionT_Norma ó ImplicacionIf_Then
	virtual float implica(float, float)=0;
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
		Tipo=new char[20];
		strcpy(Tipo,IDS_IMPLICA_TIPO);
		CodigoC=0;
		CodigoCPP=0;
	}
	virtual ~Implicacion()
	{
		delete[] Tipo;
		delete[] CodigoC;
		delete[] CodigoCPP;
	}
	virtual float implica(float,float)=0;
	virtual float defecto()=0;
	virtual char *codigoC()=0;
	virtual char *codigoCPP()=0;
	char *tipo()
	{
		return Tipo;
	}
	int identificador()
	{
		return Identificador;
	}

protected:
	char *Tipo;
	char *CodigoC;
	char *CodigoCPP;
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
	float defecto()
	{
		return 0;
	}
	virtual char *codigoC()=0;
	virtual char *codigoCPP()=0;
	virtual float implica(float x, float y)=0;
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
	float defecto()
	{
		return 1;
	}
	virtual float implica(float x, float y)=0;
	virtual char *codigoC()=0;
	virtual char *codigoCPP()=0;
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
		strcpy(Tipo,IDS_IMPLICA_TN_TIPO_0);
		CodigoC=new char[200];
		CodigoCPP=new char[200];
		Identificador=0;
	}
	~ImplicacionProducto(){}
	char *codigoC()
	{
		delete[] CodigoC;
		CodigoC=new char[200];
		strcpy(CodigoC,"");
		strcat(CodigoC,"    	rel=x*y;");
		return CodigoC;
	}
	char *codigoCPP()
	{
		delete[] CodigoCPP;
		CodigoCPP=new char[200];
		strcpy(CodigoCPP,"");
		strcat(CodigoCPP,"ImplicacionProducto();");
		return CodigoCPP;
	}
	float implica(float x, float y)
	{
		float z;
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
		strcpy(Tipo,IDS_IMPLICA_TN_TIPO_1);
		CodigoC=new char[200];
		CodigoCPP=new char[200];
		Identificador=1;
	}
	~ImplicacionMinimo(){}
	char *codigoC()
	{
		delete[] CodigoC;
		CodigoC=new char[200];
		strcpy(CodigoC,"");
		strcat(CodigoC,"    if(x<y)\r\n");
		strcat(CodigoC,"    {\r\n");
		strcat(CodigoC,"    	rel=x;\r\n");
		strcat(CodigoC,"    }else\r\n");
		strcat(CodigoC,"    {\r\n");
		strcat(CodigoC,"    	rel=y;\r\n");
		strcat(CodigoC,"    }");
		return CodigoC;
	}
	char *codigoCPP()
	{
		delete[] CodigoCPP;
		CodigoCPP=new char[200];
		strcpy(CodigoCPP,"");
		strcat(CodigoCPP,"ImplicacionMinimo();");
		return CodigoCPP;
	}
	float implica(float x, float y)
	{
		float z;
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
		strcpy(Tipo,IDS_IMPLICA_IF_TIPO_2);
		CodigoC=new char[200];
		CodigoCPP=new char[200];
		Identificador=2;
	}
	~ImplicacionKleenDienes(){}
	char *codigoC()
	{
		delete[] CodigoC;
		CodigoC=new char[200];
		strcpy(CodigoC,"");
		strcat(CodigoC,"    x=1-x;\r\n");
		strcat(CodigoC,"    if(x>y)\r\n");
		strcat(CodigoC,"    	rel=x;\r\n");
		strcat(CodigoC,"    else\r\n");
		strcat(CodigoC,"    	rel=y;");
		return CodigoC;
	}
	char *codigoCPP()
	{
		delete[] CodigoCPP;
		CodigoCPP=new char[200];
		strcpy(CodigoCPP,"");
		strcat(CodigoCPP,"ImplicacionKleenDienes();");
		return CodigoCPP;
	}
	float implica(float x, float y)
	{
		float rel;
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
		strcpy(Tipo,IDS_IMPLICA_IF_TIPO_3);
		CodigoC=new char[200];
		CodigoCPP=new char[200];
		Identificador=3;
	}
	~ImplicacionLukasiewicz(){}
	char *codigoC()
	{
		delete[] CodigoC;
		CodigoC=new char[200];
		strcpy(CodigoC,"");
		strcat(CodigoC,"    if(x<y)\r\n");
		strcat(CodigoC,"    	rel=x;\r\n");
		strcat(CodigoC,"    else\r\n");
		strcat(CodigoC,"    	rel=y;\r\n");
		strcat(CodigoC,"    x=1-x;\r\n");
		strcat(CodigoC,"    if(rel<x)\r\n");
		strcat(CodigoC,"    	rel=x;");
		return CodigoC;
	}
	char *codigoCPP()
	{
		delete[] CodigoCPP;
		CodigoCPP=new char[200];
		strcpy(CodigoCPP,"");
		strcat(CodigoCPP,"ImplicacionLukasiewicz();");
		return CodigoCPP;
	}
	float implica(float x, float y)
	{
		float rel;
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
		strcpy(Tipo,IDS_IMPLICA_IF_TIPO_4);
		CodigoC=new char[200];
		CodigoCPP=new char[200];
		Identificador=4;
	}
	~ImplicacionZadeh(){}
	char *codigoC()
	{
		delete[] CodigoC;
		CodigoC=new char[200];
		strcpy(CodigoC,"");
		strcat(CodigoC,"    if(x<y)\r\n");
		strcat(CodigoC,"    	rel=x;\r\n");
		strcat(CodigoC,"    else\r\n");
		strcat(CodigoC,"    	rel=y;\r\n");
		strcat(CodigoC,"    x=1-x;\r\n");
		strcat(CodigoC,"    if(rel<x)\r\n");
		strcat(CodigoC,"    	rel=x;");
		return CodigoC;
	}
	char *codigoCPP()
	{
		delete[] CodigoCPP;
		CodigoCPP=new char[200];
		strcpy(CodigoCPP,"");
		strcat(CodigoCPP,"ImplicacionZadeh();");
		return CodigoCPP;
	}
	float implica(float x, float y)
	{
		float rel;
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
		strcpy(Tipo,IDS_IMPLICA_IF_TIPO_5);
		CodigoC=new char[200];
		CodigoCPP=new char[200];
		Identificador=5;
	}
	~ImplicacionEstocastica(){}
	char *codigoC()
	{
		delete[] CodigoC;
		CodigoC=new char[200];
		strcpy(CodigoC,"");
		strcat(CodigoC,"    rel=x*y;\r\n");
		strcat(CodigoC,"    x=1-x;\r\n");
		strcat(CodigoC,"    if(rel<x)\r\n");
		strcat(CodigoC,"    	rel=x;");
		return CodigoC;
	}
	char *codigoCPP()
	{
		delete[] CodigoCPP;
		CodigoCPP=new char[200];
		strcpy(CodigoCPP,"");
		strcat(CodigoCPP,"ImplicacionEstocastica();");
		return CodigoCPP;
	}
	float implica(float x, float y)
	{
		float rel;
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
		strcpy(Tipo,IDS_IMPLICA_IF_TIPO_6);
		CodigoC=new char[200];
		CodigoCPP=new char[200];
		Identificador=6;
	}
	~ImplicacionGoguen(){}
	char *codigoC()
	{
		delete[] CodigoC;
		CodigoC=new char[200];
		strcpy(CodigoC,"");
		strcat(CodigoC,"    if(x>0.00001)\r\n");
		strcat(CodigoC,"    	rel=y/x;\r\n");
		strcat(CodigoC,"    else\r\n");
		strcat(CodigoC,"    	rel=1000;\r\n");
		strcat(CodigoC,"    if(rel>1)\r\n");
		strcat(CodigoC,"    	rel=1;");
		return CodigoC;
	}
	char *codigoCPP()
	{
		delete[] CodigoCPP;
		CodigoCPP=new char[200];
		strcpy(CodigoCPP,"");
		strcat(CodigoCPP,"ImplicacionGoguen();");
		return CodigoCPP;
	}
	float implica(float x, float y)
	{
		float rel;
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
		strcpy(Tipo,IDS_IMPLICA_IF_TIPO_7);
		CodigoC=new char[200];
		CodigoCPP=new char[200];
		Identificador=7;
	}
	~ImplicacionGodel(){}
	char *codigoC()
	{
		delete[] CodigoC;
		CodigoC=new char[200];
		strcpy(CodigoC,"");
		strcat(CodigoC,"    if(x<=y)\r\n");
		strcat(CodigoC,"    	rel=1;\r\n");
		strcat(CodigoC,"    else\r\n");
		strcat(CodigoC,"    	rel=y;");
		return CodigoC;
	}
	char *codigoCPP()
	{
		delete[] CodigoCPP;
		CodigoCPP=new char[200];
		strcpy(CodigoCPP,"");
		strcat(CodigoCPP,"ImplicacionGodel();");
		return CodigoCPP;
	}
	float implica(float x, float y)
	{
		float rel;
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
		strcpy(Tipo,IDS_IMPLICA_IF_TIPO_8);
		CodigoC=new char[200];
		CodigoCPP=new char[200];
		Identificador=8;
	}
	~ImplicacionAguda(){}
	char *codigoC()
	{
		delete[] CodigoC;
		CodigoC=new char[200];
		strcpy(CodigoC,"");
		strcat(CodigoC,"    if(x<=y)\r\n");
		strcat(CodigoC,"    	rel=1;\r\n");
		strcat(CodigoC,"    else\r\n");
		strcat(CodigoC,"    	rel=0;");
		return CodigoC;
	}
	char *codigoCPP()
	{
		delete[] CodigoCPP;
		CodigoCPP=new char[200];
		strcpy(CodigoCPP,"");
		strcat(CodigoCPP,"ImplicacionAguda();");
		return CodigoCPP;
	}
	float implica(float x, float y)
	{
		float rel;
		if(x<=y)
			rel=1;
		else
			rel=0;
		return(rel);
	}
protected:
};




#endif // IMPLICACION_H

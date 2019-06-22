#ifndef NORMA_H
#define NORMA_H

#include <iostream>
#include <string>
#include <wx/wx.h>
using namespace std;

#include <math.h>

/*///////////////////////////////////////
class Norma
atributos
	char *Tipo;                 Identificador de tipo (Ej. "Maximo" ) ver hijos	char *CodigoC;
	char *CodigoCPP;            Texto necesario para generar Código C++
	int Identificador;          identificador de Tipo, necesario para crear el hijo adecuado al leer un archivo

procedimientos:
	char* tipo()                  consultor de Tipo
	int identificador()           consultor de Identificador

Las funciones virtual=0 deben ser redefinidas por los hijos

	virtual char* codigoC()=0;
                        entrega el texto necesario para generar Codigo C (ver DialogGenerarCodigo)
	virtual char* codigoCPP()=0;
								entrega el texto necesario para generar Codigo C++ (ver DialogGenerarCodigo)
	virtual float ToSNorm()=0;
                    determina si la Norma es T_Norma ó S_Norma
	virtual float opera(float, float)=0;
                    efectúa la operación matemática
	virtual float parametro()=0;
                    algunas Normas tienen un parámetro; este es el consultor
//////////////////////////////////////////*/

class Norma
{
public:
	Norma()
	{
	}
	virtual ~Norma()
	{
	}
	string tipo()
	{
		return tipo(Identificador);
	}
	static string tipo(int caso);
	int identificador()
	{
		return Identificador;
	}
	virtual string codigoC()=0;
	virtual string codigoCPP()=0;
	virtual float ToSNorm()=0;
	virtual float opera(float, float)=0;
	virtual float parametro()=0;
protected:
	int Identificador;
};

/*/////////////////////////////////////////
class T_Norma:public Norma

esta clase sólo redefine la funcion ToSNorm(), devolviendo 1.0
///////////////////////////////////////////*/

class T_Norma:public Norma
{
public:
	T_Norma(){}
	~T_Norma(){}
	float ToSNorm()
	{
		return 1.0;
	}
	virtual string codigoC()=0;
	virtual string codigoCPP()=0;
	virtual float opera(float, float)=0;
protected:
};

/*/////////////////////////////////////////
class S_Norma:public Norma

esta clase sólo redefine la funcion ToSNorm(), devolviendo 0.0
///////////////////////////////////////////*/

class S_Norma:public Norma
{
public:
	S_Norma(){}
	~S_Norma(){}
	float ToSNorm()
	{
		return 0.0;
	}
	virtual string codigoC()=0;
	virtual string codigoCPP()=0;
	virtual float opera(float, float)=0;
protected:
};

//////////////////// T_Norma

/*//////////////////////////////////////////
class Producto:public T_Norma

    norma del producto

	 Identificador=0

////////////////////////////////////////////*/

class Producto:public T_Norma
{
public:
	Producto()
	{
		Identificador=0;
	}
	~Producto(){}
	float parametro()
	{
		return 0;
	}
	string codigoC()
	{
		wxString CodigoC="";
		CodigoC << ("    z=x*y;");
		return std::string(CodigoC.mb_str());
	}
	string codigoCPP()
	{
		wxString CodigoCPP="";
		CodigoCPP << ("Producto();");
		return std::string(CodigoCPP.mb_str());
	}
	float opera(float x, float y)
	{
		float z;
		z=x*y;
		return z;
	}
protected:
};

/*//////////////////////////////////////////
class Minimo:public T_Norma

    Norma del mínimo

    Identificador=1

////////////////////////////////////////////*/

class Minimo:public T_Norma
{
public:
	Minimo()
	{
		Identificador=1;
	}
	~Minimo(){}
	float parametro()
	{
		return 0;
	}
	string codigoC()
	{
		wxString CodigoC="";
		CodigoC << ("    if(x<y)\n");
		CodigoC << ("    {\n");
		CodigoC << ("    	z=x;\n");
		CodigoC << ("    }else\n");
		CodigoC << ("    {\n");
		CodigoC << ("    	z=y;\n");
		CodigoC << ("    }");
		return std::string(CodigoC.mb_str());
	}
	string codigoCPP()
	{
		wxString CodigoCPP="";
		CodigoCPP << ("Minimo();");
		return std::string(CodigoCPP.mb_str());
	}
	float opera(float x, float y)
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
protected:
};


/*//////////////////////////////////////////
class ProductoAcotado:public T_Norma

    norma del producto acotado

    Identificador=2

////////////////////////////////////////////*/

class ProductoAcotado:public T_Norma
{
public:
	ProductoAcotado()
	{
		Identificador=2;
	}
	~ProductoAcotado(){}
	float parametro()
	{
		return 0;
	}
	string codigoC()
	{
		wxString CodigoC="";
		CodigoC << ("    z=x+y-1;\n");
		CodigoC << ("    if(z<0)\n");
		CodigoC << ("    {\n");
		CodigoC << ("    	z=0;\n");
		CodigoC << ("    }");
		return std::string(CodigoC.mb_str());
	}
	string codigoCPP()
	{
		wxString CodigoCPP="";
		CodigoCPP << ("ProductoAcotado();");
		return std::string(CodigoCPP.mb_str());
	}
	float opera(float x, float y)
	{
		float z;
		z=x+y-1;
		if(z<0)
		{
			z=0;
		}
		return z;
	}
protected:
};


/*//////////////////////////////////////////
class ProductoDrastico:public T_Norma

    norma del producto drástico

    Identificador=3

////////////////////////////////////////////*/

class ProductoDrastico:public T_Norma
{
public:
	ProductoDrastico()
	{
		Identificador=3;
	}
	~ProductoDrastico(){}
	float parametro()
	{
		return 0;
	}
	string codigoC()
	{
		wxString CodigoC="";
		CodigoC << ("    if(y==1)\n");
		CodigoC << ("    {\n");
		CodigoC << ("    	z=x;\n");
		CodigoC << ("    }\n");
		CodigoC << ("    if(x==1)\n");
		CodigoC << ("    {\n");
		CodigoC << ("    	z=y;\n");
		CodigoC << ("    }\n");
		CodigoC << ("    if(x<1&&y<1)\n");
		CodigoC << ("    {\n");
		CodigoC << ("    	z=0;\n");
		CodigoC << ("    }");
		return std::string(CodigoC.mb_str());
	}
	string codigoCPP()
	{
		wxString CodigoCPP="";
		CodigoCPP << ("ProductoDrastico();");
		return std::string(CodigoCPP.mb_str());
	}
	float opera(float x, float y)
	{
		float z;
		if(y==1)
		{
			z=x;
		}
		if(x==1)
		{
			z=y;
		}
		if(x<1&&y<1)
		{
			z=0;
		}
		return z;
	}
protected:
};


/*//////////////////////////////////////////
class FamiliaTp:public T_Norma

	 familia Tp

    Identificador=4

////////////////////////////////////////////*/

class FamiliaTp:public T_Norma
{
public:
	FamiliaTp(float parametro=1.0)
	{
		p=parametro;
		Identificador=4;
	}
	float parametro()
	{
		return p;
	}
	string codigoC()
	{
		wxString CodigoC="";
		CodigoC << ("    float p=") << p << (";\n");
		CodigoC << ("    z=pow(1-x,p)+pow(1-y,p)-pow(1-x,p)*pow(1-y,p);\n");
		CodigoC << ("    z=1-pow(z,(1/p));");
		return std::string(CodigoC.mb_str());
	}
	string codigoCPP()
	{
		wxString CodigoCPP="";
		CodigoCPP << ("FamiliaTp(") << p << (");");
		return std::string(CodigoCPP.mb_str());
	}
	~FamiliaTp(){}
	float opera(float x, float y)
	{
		float z;
		z=pow(1-x,p)+pow(1-y,p)-pow(1-x,p)*pow(1-y,p);
		z=1-pow(z,(1/p));
		return z;
	}
protected:
	float p;
};


/*//////////////////////////////////////////
class FamiliaHp:public T_Norma

    familia Hamacher

    Identificador=5

////////////////////////////////////////////*/

class FamiliaHp:public T_Norma
{
public:
	FamiliaHp(float parametro=1.0)
	{
		p=parametro;
		Identificador=5;
	}
	~FamiliaHp(){}
	float parametro()
	{
		return p;
	}
	string codigoC()
	{
		wxString CodigoC="";
		CodigoC << ("    float p=") << p << (";\n");
		CodigoC << ("    z=p-(1-p)*(x+y-x*y);\n");
		CodigoC << ("    z=x*y/z;");
		return std::string(CodigoC.mb_str());
	}
	string codigoCPP()
	{
		wxString CodigoCPP="";
		CodigoCPP << ("FamiliaHp(") << p << (");");
		return std::string(CodigoCPP.mb_str());
	}
	float opera(float x, float y)
	{
		float z;
		z=p-(1-p)*(x+y-x*y);
		z=x*y/z;
		return z;
	}
protected:
	float p;
};



/*//////////////////////////////////////////
class FamiliaFp:public T_Norma

	 familia Frank

    Identificador=7

////////////////////////////////////////////*/

class FamiliaFp:public T_Norma
{
public:
	FamiliaFp(float parametro=2.0)
	{
		p=parametro;
		Identificador=7;
	}
	float parametro()
	{
		return p;
	}
	string codigoC()
	{
		wxString CodigoC="";
		CodigoC << ("    float p=") << p << (";\n");
		CodigoC << ("    z=1+(pow(p,x)-1)*(pow(p,y)-1)/(p-1);\n");
		CodigoC << ("    z=log(z)/log(p);");
		return std::string(CodigoC.mb_str());
	}
	string codigoCPP()
	{
		wxString CodigoCPP="";
		CodigoCPP << ("FamiliaFp(") << p << (");");
		return std::string(CodigoCPP.mb_str());
	}
	~FamiliaFp(){}
	float opera(float x, float y)
	{
		float z;
		z=1+(pow(p,x)-1)*(pow(p,y)-1)/(p-1);
		z=log(z)/log(p);
		return z;
	}
protected:
	float p;
};


/*//////////////////////////////////////////
class FamiliaYp:public T_Norma

    Familia Yager

    Identificador=8

////////////////////////////////////////////*/

class FamiliaYp:public T_Norma
{
public:
	FamiliaYp(float parametro=1.0)
	{
		p=parametro;
		Identificador=8;
	}
	~FamiliaYp(){}
	float parametro()
	{
		return p;
	}
	string codigoC()
	{
		wxString CodigoC="";
		CodigoC << ("    float p=") << p << (";\n");
		CodigoC << ("    z=pow(1-x,p)+pow(1-y,p);\n");
		CodigoC << ("    z=pow(z,(1/p));\n");
		CodigoC << ("    if(z>1)\n");
		CodigoC << ("    {\n");
		CodigoC << ("    	z=1;\n");
		CodigoC << ("    }\n");
		CodigoC << ("    z=1-z;");
		return std::string(CodigoC.mb_str());
	}
	string codigoCPP()
	{
		wxString CodigoCPP="";
		CodigoCPP << ("FamiliaYp(") << p << (");");
		return std::string(CodigoCPP.mb_str());
	}
	float opera(float x, float y)
	{
		float z;
		z=pow(1-x,p)+pow(1-y,p);
		z=pow(z,(1/p));
		if(z>1)
		{
			z=1;
		}
		z=1-z;
		return z;
	}
protected:
	float p;
};


/*//////////////////////////////////////////
class FamiliaAp:public T_Norma

    familia Dubois-Prade

    Identificador=9

////////////////////////////////////////////*/

class FamiliaAp:public T_Norma
{
public:
	FamiliaAp(float parametro=1.0)
	{
		p=parametro;
		Identificador=9;
	}
	~FamiliaAp(){}
	float parametro()
	{
		return p;
	}
	string codigoC()
	{
		wxString CodigoC="";
		CodigoC << ("    float p=") << p << (";\n");
		CodigoC << ("    z=x;\n");
		CodigoC << ("    if(y>z)\n");
		CodigoC << ("    {\n");
		CodigoC << ("    	z=y;\n");
		CodigoC << ("    }\n");
		CodigoC << ("    if(p>z)\n");
		CodigoC << ("    {\n");
		CodigoC << ("    	z=p;\n");
		CodigoC << ("    }\n");
		CodigoC << ("    z=x*y/z;");
		return std::string(CodigoC.mb_str());
	}
	string codigoCPP()
	{
		wxString CodigoCPP="";
		CodigoCPP << ("FamiliaAp(") << p << (");");
		return std::string(CodigoCPP.mb_str());
	}
	float opera(float x, float y)
	{
		float z;
		z=x;
		if(y>z)
		{
			z=y;
		}
		if(p>z)
		{
			z=p;
		}
		z=x*y/z;
		return z;
	}
protected:
	float p;
};



///////////////// S-Normas


/*//////////////////////////////////////////
class Maximo:public S_Norma

    norma del máximo

    Identificador=10

////////////////////////////////////////////*/

class Maximo:public S_Norma
{
public:
	Maximo()
	{
		Identificador=10;
	}
	~Maximo(){}
	float parametro()
	{
		return 0;
	}
	string codigoC()
	{
		wxString CodigoC="";
		CodigoC << ("    if(x>y)\n");
		CodigoC << ("    {\n");
		CodigoC << ("    	z=x;\n");
		CodigoC << ("    }else\n");
		CodigoC << ("    {\n");
		CodigoC << ("    	z=y;\n");
		CodigoC << ("    }");
		return std::string(CodigoC.mb_str());
	}
	string codigoCPP()
	{
		wxString CodigoCPP="";
		CodigoCPP << ("Maximo();");
		return std::string(CodigoCPP.mb_str());
	}
	float opera(float x, float y)
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
protected:
};


/*//////////////////////////////////////////
class SumaAcotada:public S_Norma

    norma de la suma acotada

    Identificador=11

////////////////////////////////////////////*/

class SumaAcotada:public S_Norma
{
public:
	SumaAcotada()
	{
		Identificador=11;
	}
	~SumaAcotada(){}
	float parametro()
	{
		return 0;
	}
	string codigoC()
	{
		wxString CodigoC="";
		CodigoC << ("    z=x+y;\n");
		CodigoC << ("    if(z>1)\n");
		CodigoC << ("    {\n");
		CodigoC << ("    	z=1;\n");
		CodigoC << ("    }");
		return std::string(CodigoC.mb_str());
	}
	string codigoCPP()
	{
		wxString CodigoCPP="";
		CodigoCPP << ("SumaAcotada();");
		return std::string(CodigoCPP.mb_str());
	}
	float opera(float x, float y)
	{
		float z;
		z=x+y;
		if(z>1)
		{
			z=1;
		}
		return z;
	}
protected:
};


/*//////////////////////////////////////////
class SumaDrastica:public S_Norma

	 norma de la suma drástica

    Identificador=12

////////////////////////////////////////////*/

class SumaDrastica:public S_Norma
{
public:
	SumaDrastica()
	{
		Identificador=12;
	}
	~SumaDrastica(){}
	float parametro()
	{
		return 0;
	}
	string codigoC()
	{
		wxString CodigoC="";
		CodigoC << ("    if(y==0)\n");
		CodigoC << ("    {\n");
		CodigoC << ("    	z=x;\n");
		CodigoC << ("    }\n");
		CodigoC << ("    if(x==0)\n");
		CodigoC << ("    {\n");
		CodigoC << ("    	z=y;\n");
		CodigoC << ("    }\n");
		CodigoC << ("    if(x>0&&y>0)\n");
		CodigoC << ("    {\n");
		CodigoC << ("    	z=1;\n");
		CodigoC << ("    }");
		return std::string(CodigoC.mb_str());
	}
	string codigoCPP()
	{
		wxString CodigoCPP="";
		CodigoCPP << ("SumaDrastica();");
		return std::string(CodigoCPP.mb_str());
	}
	float opera(float x, float y)
	{
		float z;
		if(y==0)
		{
			z=x;
		}
		if(x==0)
		{
			z=y;
		}
		if(x>0&&y>0)
		{
			z=1;
		}
		return z;
	}
protected:
};

/*//////////////////////////////////////////
class FamiliaSp:public S_Norma

	 familia Sugeno

	 Identificador=6

////////////////////////////////////////////*/

class FamiliaSp:public S_Norma
{
public:
	FamiliaSp(float parametro=1.0)
	{
		p=parametro;
		Identificador=6;
	}
	~FamiliaSp(){}
	float parametro()
	{
		return p;
	}
	string codigoC()
	{
		wxString CodigoC="";
		CodigoC << ("    float p=") << p << (";\n");
		CodigoC << ("    z=x+y+p*x*y;\n");
		CodigoC << ("    if(z>1)\n");
		CodigoC << ("    {\n");
		CodigoC << ("    	z=1;\n");
		CodigoC << ("    }");
		return std::string(CodigoC.mb_str());
	}
	string codigoCPP()
	{
		wxString CodigoCPP="";
		CodigoCPP << ("FamiliaSp(") << p << (");");
		return std::string(CodigoCPP.mb_str());
	}
	float opera(float x, float y)
	{
		float z;
		z=x+y+p*x*y;
		if(z>1)
		{
			z=1;
		}
		return z;
	}
protected:
	float p;
};


#endif // NORMA_H

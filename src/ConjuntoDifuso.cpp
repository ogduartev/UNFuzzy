#include "ConjuntoDifuso.h"

/*//////////////////////////////////////////////
En las siguientes funciones se calculan las
funciones de pertenencia  de las clases derivadas de
ConjuntoDifuso .

Las funciones de pertenencia son tramos de líneas
rectas o de curvas en forma de S según el Clase.

Una curva en S desde a hasta b que cambie de 0 a 1 se
calcula de la siguiente forma

entra a y (a+b)/2
                              2
        f(x)= 2*((x-a)/(b-a))

entra (a+b)/2 y b
                                2
        f(x)= 1- 2*((x-b)/(b-a))


//////////////////////////////////////////////*/

float ConjuntoDifuso::verificarPuntoClave(int i,float x)
{
	float xVer=x;
	float puntos[10];
	puntosClaves(puntos);
	if(i>0)
	{
		if(xVer < puntos[i-1])
		{
			xVer=puntos[i-1];
		}
	}
	if(i<(numeroPuntosClaves()-2))
	{
		if(xVer > puntos[i+1])
		{
			xVer=puntos[i+1];
		}
	}
	return xVer;
}


inline float ConjuntoL::pertenencia(float x)
{
	float ux;
	if(x<minimo())
		ux=1;
	if(x<primerCorte()&&x>=minimo())
		ux=1;
	if(x<maximo()&&x>=primerCorte())
		ux=(maximo()-x)/(maximo()-primerCorte());
	if(x>=maximo())
		ux=0;
	if(ux<0.0001)
		ux=0;
	return ux ;
}


inline float ConjuntoTriangulo::pertenencia(float x)
{
	float ux;
	if(x<minimo())
		ux=0;
	if(x<primerCorte()&&x>=minimo())
		ux=(x-minimo())/(primerCorte()-minimo());
	if(x<maximo()&&x>=primerCorte())
		ux=(maximo()-x)/(maximo()-primerCorte());
	if(x>=maximo())
		ux=0;
	if(ux<0.0001)
		ux=0;
	return ux ;
}


inline float ConjuntoPi::pertenencia(float x)
{
	float ux;
	if(x<minimo())
		ux=0;
	if(x<primerCorte()&&x>=minimo())
		ux=(x-minimo())/(primerCorte()-minimo());
	if(x<segundoCorte()&&x>=primerCorte())
		ux=1;
	if(x<maximo()&&x>=segundoCorte())
		ux=(maximo()-x)/(maximo()-segundoCorte());
	if(x>=maximo())
		ux=0;
	if(ux<0.0001)
		ux=0;
	return ux ;
}


inline float ConjuntoGamma::pertenencia(float x)
{
	float ux;
	if(x<minimo())
		ux=0;
	if(x<primerCorte()&&x>=minimo())
		ux=(x-minimo())/(primerCorte()-minimo());
	if(x<maximo()&&x>=primerCorte())
		ux=1;
	if(x>=maximo())
		ux=1;
	if(ux<0.0001)
		ux=0;
	return ux ;
}

inline float ConjuntoZ::pertenencia(float x)
{
	float ux;
	if(x<minimo())
		ux=1;
	if(x<primerCorte())
		ux=1;
	if(x<(primerCorte()+maximo())/2&&x>=primerCorte())
		{
			ux=(x-primerCorte())/(maximo()-primerCorte());
			ux=1-2*ux*ux;
		}
	if(x<maximo()&&x>=(primerCorte()+maximo())/2)
		{
			ux=(x-maximo())/(maximo()-primerCorte());
			ux=2*ux*ux;
		}
	if(x>=maximo())
		ux=0;
	if(ux<0.0001)
		ux=0;
	return ux ;
}

inline float ConjuntoCampana::pertenencia(float x)
{
	float ux;
	if(x<minimo())
		ux=0;
	if(x<(primerCorte()+minimo())/2&&x>=minimo())
		{
			ux=(x-minimo())/(primerCorte()-minimo());
			ux=2*ux*ux;
		}
	if(x<primerCorte()&&x>=(primerCorte()+minimo())/2)
		{
			ux=(x-primerCorte())/(primerCorte()-minimo());
			ux=1-2*ux*ux;
		}
	if(x<(primerCorte()+maximo())/2&&x>=primerCorte())
		{
			ux=(x-primerCorte())/(maximo()-primerCorte());
			ux=1-2*ux*ux;
		}
	if(x<maximo()&&x>=(primerCorte()+maximo())/2)
		{
			ux=(x-maximo())/(maximo()-primerCorte());
			ux=2*ux*ux;
		}
	if(x>=maximo())
		ux=0;
	if(ux<0.0001)
		ux=0;
	return ux ;
}


inline float ConjuntoS::pertenencia(float x)
{
	float ux;
	if(x<minimo())
		ux=0;
	if(x<(primerCorte()+minimo())/2&&x>=minimo())
		{
			ux=(x-minimo())/(primerCorte()-minimo());
			ux=2*ux*ux;
		}
	if(x<primerCorte()&&x>=(primerCorte()+minimo())/2)
		{
			ux=(x-primerCorte())/(primerCorte()-minimo());
			ux=1-2*ux*ux;
		}
	if(x>=primerCorte())
		ux=1;
	if(ux<0.0001)
		ux=0;
	return ux ;
}

inline float ConjuntoPiCampana::pertenencia(float x)
{
	float ux;
	if(x<minimo())
		ux=0;
	if(x<(primerCorte()+minimo())/2&&x>=minimo())
		{
			ux=(x-minimo())/(primerCorte()-minimo());
			ux=2*ux*ux;
		}
	if(x<primerCorte()&&x>=(primerCorte()+minimo())/2)
		{
			ux=(x-primerCorte())/(primerCorte()-minimo());
			ux=1-2*ux*ux;
		}
	if(x<segundoCorte()&&x>=primerCorte())
		ux=1;
	if(x<(segundoCorte()+maximo())/2&&x>=segundoCorte())
		{
			ux=(x-segundoCorte())/(maximo()-segundoCorte());
			ux=1-2*ux*ux;
		}
	if(x<maximo()&&x>=(segundoCorte()+maximo())/2)
		{
			ux=(x-maximo())/(maximo()-segundoCorte());
			ux=2*ux*ux;
		}
	if(x>=maximo())
		ux=0;
	if(ux<0.0001)
		ux=0;
	return ux ;
}


inline float ConjuntoSinglenton::pertenencia(float x)
{
	float ux;
	if(x<minimo())
		ux=0;
	if(x<maximo()&&x>=minimo())
		ux=1;
	if(x>=maximo())
		ux=0;
	if(ux<0.0001)
		ux=0;
	return ux ;
}

void ConjuntoL::nuevoPuntoClave(int punto, float x)
{
	switch(punto)
	{
		case 0: primerCorte(x);break;
		case 1: maximo(x);break;
		default:break;
	}
}

void ConjuntoTriangulo::nuevoPuntoClave(int punto, float x)
{
	switch(punto)
	{
		case 0: minimo(x);break;
		case 1: primerCorte(x);break;
		case 2: maximo(x);break;
		default:break;
	}
}

void ConjuntoPi::nuevoPuntoClave(int punto, float x)
{
	switch(punto)
	{
		case 0: minimo(x);break;
		case 1: primerCorte(x);break;
		case 2: segundoCorte(x);break;
		case 3: maximo(x);break;
		default:break;
	}
}

void ConjuntoGamma::nuevoPuntoClave(int punto, float x)
{
	switch(punto)
	{
		case 0: minimo(x);break;
		case 1: primerCorte(x);break;
		default:break;
	}
}

void ConjuntoZ::nuevoPuntoClave(int punto, float x)
{
	switch(punto)
	{
		case 0: primerCorte(x);break;
		case 1: maximo(x);break;
		default:break;
	}
}

void ConjuntoCampana::nuevoPuntoClave(int punto, float x)
{
	switch(punto)
	{
		case 0: minimo(x);break;
		case 1: primerCorte(x);break;
		case 2: maximo(x);break;
		default:break;
	}
}

void ConjuntoPiCampana::nuevoPuntoClave(int punto, float x)
{
	switch(punto)
	{
		case 0: minimo(x);break;
		case 1: primerCorte(x);break;
		case 2: segundoCorte(x);break;
		case 3: maximo(x);break;
		default:break;
	}
}

void ConjuntoS::nuevoPuntoClave(int punto, float x)
{
	switch(punto)
	{
		case 0: minimo(x);break;
		case 1: primerCorte(x);break;
		default:break;
	}
}

void ConjuntoSinglenton::nuevoPuntoClave(int punto, float x)
{
	switch(punto)
	{
		case 0: minimo(x);break;
		case 1: maximo(x);break;
		default:break;
	}
}

////////////////////////////////////////////////////////
//    CODIGO C
///////////////////////////////////////////////


char* ConjuntoL::codigoC()
{
	char cad[1000];
	delete[] CodigoC;
	CodigoC=new char[5000];
	strcpy(CodigoC,"");
	sprintf(   cad,"                        if(x<(%f))\r\n",minimo());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                            ux=1;\r\n");
	sprintf(   cad,"                        if(x<(%f)&&x>=(%f))\r\n",primerCorte(),minimo());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                            ux=1;\r\n");
	sprintf(   cad,"                        if(x<(%f)&&x>=(%f))\r\n",maximo(),primerCorte());
	strcat(CodigoC,cad);
	sprintf(   cad,"                            ux=((%f)-x)/((%f)-(%f));\r\n",maximo(),maximo(),primerCorte());
	strcat(CodigoC,cad);
	sprintf(   cad,"                        if(x>=(%f))\r\n",maximo());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                            ux=0;\r\n");
	strcat(CodigoC,"                        if(ux<0.0001)\r\n");
	strcat(CodigoC,"                            ux=0;");
	return CodigoC;
}

char* ConjuntoL::codigoCPP()
{
	char cad[1000];
	delete[] CodigoCPP;
	CodigoCPP=new char[5000];
	strcpy(CodigoCPP,"");
	sprintf(   cad,"    cd=new ConjuntoL(%f,%f,%f);",minimo(),primerCorte(),maximo());
	strcat(CodigoCPP,cad);
	return CodigoCPP;
}

char* ConjuntoTriangulo::codigoC()
{
	char cad[1000];
	delete[] CodigoC;
	CodigoC=new char[5000];
	strcpy(CodigoC,"");
	sprintf(   cad,"                        if(x<(%f))\r\n",minimo());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                            ux=0;\r\n");
	sprintf(   cad,"                        if(x<(%f)&&x>=(%f))\r\n",primerCorte(),minimo());
	strcat(CodigoC,cad);
	sprintf(   cad,"                            ux=(x-(%f))/((%f)-(%f));\r\n",minimo(),primerCorte(),minimo());
	strcat(CodigoC,cad);
	sprintf(   cad,"                        if(x<(%f)&&x>=(%f))\r\n",maximo(),primerCorte());
	strcat(CodigoC,cad);
	sprintf(   cad,"                            ux=((%f)-x)/((%f)-(%f));\r\n",maximo(),maximo(),primerCorte());
	strcat(CodigoC,cad);
	sprintf(   cad,"                        if(x>=(%f))\r\n",maximo());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                            ux=0;\r\n");
	strcat(CodigoC,"                        if(ux<0.0001)\r\n");
	strcat(CodigoC,"                            ux=0;\r\n");
	return CodigoC;
}

char* ConjuntoTriangulo::codigoCPP()
{
	char cad[1000];
	delete[] CodigoCPP;
	CodigoCPP=new char[5000];
	strcpy(CodigoCPP,"");
	sprintf(   cad,"    cd=new ConjuntoTriangulo(%f,%f,%f);",minimo(),primerCorte(),maximo());
	strcat(CodigoCPP,cad);
	return CodigoCPP;
}

char* ConjuntoPi::codigoC()
{
	char cad[1000];
	delete[] CodigoC;
	CodigoC=new char[5000];
	strcpy(CodigoC,"");
	sprintf(   cad,"                        if(x<(%f))\r\n",minimo());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                            ux=0;\r\n");
	sprintf(   cad,"                        if(x<(%f)&&x>=(%f))\r\n",primerCorte(),minimo());
	strcat(CodigoC,cad);
	sprintf(   cad,"                            ux=(x-(%f))/((%f)-(%f));\r\n",minimo(),primerCorte(),minimo());
	strcat(CodigoC,cad);
	sprintf(   cad,"                        if(x<(%f)&&x>=(%f))\r\n",primerCorte(),segundoCorte());
	strcat(CodigoC,cad);
	sprintf(   cad,"                            ux=1;\r\n");
	strcat(CodigoC,cad);
	sprintf(   cad,"                        if(x<(%f)&&x>=(%f))\r\n",maximo(),segundoCorte());
	strcat(CodigoC,cad);
	sprintf(   cad,"                            ux=((%f)-x)/((%f)-(%f));\r\n",maximo(),maximo(),segundoCorte());
	strcat(CodigoC,cad);
	sprintf(   cad,"                        if(x>=(%f))\r\n",maximo());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                            ux=0;\r\n");
	strcat(CodigoC,"                        if(ux<0.0001)\r\n");
	strcat(CodigoC,"                            ux=0;");
	return CodigoC;
}

char* ConjuntoPi::codigoCPP()
{
	char cad[1000];
	delete[] CodigoCPP;
	CodigoCPP=new char[5000];
	strcpy(CodigoCPP,"");
	sprintf(   cad,"    cd=new ConjuntoPi(%f,%f,%f,%f);",minimo(),primerCorte(),segundoCorte(),maximo());
	strcat(CodigoCPP,cad);
	return CodigoCPP;
}

char* ConjuntoGamma::codigoC()
{
	char cad[1000];
	delete[] CodigoC;
	CodigoC=new char[5000];
	strcpy(CodigoC,"");
	sprintf(   cad,"                        if(x<(%f))\r\n",minimo());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                            ux=0;\r\n");
	sprintf(   cad,"                        if(x<(%f)&&x>=(%f))\r\n",primerCorte(),minimo());
	strcat(CodigoC,cad);
	sprintf(   cad,"                            ux=(x-(%f))/((%f)-(%f));\r\n",minimo(),primerCorte(),minimo());
	strcat(CodigoC,cad);
	sprintf(   cad,"                        if(x>=(%f))\r\n",primerCorte());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                            ux=1;\r\n");
	strcat(CodigoC,"                        if(ux<0.0001)\r\n");
	strcat(CodigoC,"                            ux=0;");
	return CodigoC;
}

char* ConjuntoGamma::codigoCPP()
{
	char cad[1000];
	delete[] CodigoCPP;
	CodigoCPP=new char[5000];
	strcpy(CodigoCPP,"");
	sprintf(   cad,"    cd=new ConjuntoGamma(%f,%f,%f);",minimo(),primerCorte(),maximo());
	strcat(CodigoCPP,cad);
	return CodigoCPP;
}

char* ConjuntoZ::codigoC()
{
	char cad[1000];
	delete[] CodigoC;
	CodigoC=new char[5000];
	strcpy(CodigoC,"");
	sprintf(   cad,"                        if(x<(%f))\r\n",minimo());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                            ux=1;\r\n");
	sprintf(   cad,"                        if(x<(%f))\r\n",primerCorte());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                            ux=1;\r\n");
	sprintf(   cad,"                        if(x<(%f)&&x>=(%f))\r\n",(primerCorte()+maximo())/2,primerCorte());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                            {\r\n");
	sprintf(   cad,"                                ux=(x-(%f))/((%f)-(%f));\r\n",primerCorte(),maximo(),primerCorte());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                                ux=1-2*ux*ux;\r\n");
	strcat(CodigoC,"                            }\r\n");
	sprintf(   cad,"                        if(x<(%f)&&x>=(%f))\r\n",maximo(),(primerCorte()+maximo())/2);
	strcat(CodigoC,cad);
	strcat(CodigoC,"                            {\r\n");
	sprintf(   cad,"                                ux=(x-(%f))/((%f)-(%f));\r\n",maximo(),maximo(),primerCorte());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                                ux=2*ux*ux;\r\n");
	strcat(CodigoC,"                            }\r\n");
	sprintf(   cad,"                        if(x>=(%f))\r\n",maximo());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                            ux=0;\r\n");
	strcat(CodigoC,"                        if(ux<0.0001)\r\n");
	strcat(CodigoC,"                            ux=0;");
	return CodigoC;
}

char* ConjuntoZ::codigoCPP()
{
	char cad[1000];
	delete[] CodigoCPP;
	CodigoCPP=new char[5000];
	strcpy(CodigoCPP,"");
	sprintf(   cad,"    cd=new ConjuntoZ(%f,%f,%f);",minimo(),primerCorte(),maximo());
	strcat(CodigoCPP,cad);
	return CodigoCPP;
}

char* ConjuntoCampana::codigoC()
{
	char cad[1000];
	delete[] CodigoC;
	CodigoC=new char[5000];
	strcpy(CodigoC,"");
	sprintf(   cad,"                        if(x<(%f))\r\n",minimo());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                            ux=0;\r\n");
	sprintf(   cad,"                        if(x<(%f)&&x>=(%f))\r\n",(primerCorte()+minimo())/2,minimo());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                            {\r\n");
	sprintf(   cad,"                                ux=(x-(%f))/((%f)-(%f));\r\n",minimo(),primerCorte(),minimo());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                                ux=2*ux*ux;\r\n");
	strcat(CodigoC,"                            }\r\n");
	sprintf(   cad,"                        if(x<(%f)&&x>=(%f))\r\n",primerCorte(),(primerCorte()+minimo())/2);
	strcat(CodigoC,cad);
	strcat(CodigoC,"                            {\r\n");
	sprintf(   cad,"                                ux=(x-(%f))/((%f)-(%f));\r\n",primerCorte(),primerCorte(),minimo());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                                ux=1-2*ux*ux;\r\n");
	strcat(CodigoC,"                            }\r\n");
	sprintf(   cad,"                        if(x<(%f)&&x>=(%f))\r\n",(primerCorte()+maximo())/2,primerCorte());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                            {\r\n");
	sprintf(   cad,"                                ux=(x-(%f))/((%f)-(%f));\r\n",primerCorte(),maximo(),primerCorte());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                                ux=1-2*ux*ux;\r\n");
	strcat(CodigoC,"                            }\r\n");
	sprintf(   cad,"                        if(x<(%f)&&x>=(%f))\r\n",maximo(),(primerCorte()+maximo())/2);
	strcat(CodigoC,cad);
	strcat(CodigoC,"                            {\r\n");
	sprintf(   cad,"                                ux=(x-(%f))/((%f)-(%f));\r\n",maximo(),maximo(),primerCorte());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                                ux=2*ux*ux;\r\n");
	strcat(CodigoC,"                            }\r\n");
	sprintf(   cad,"                        if(x>=(%f))\r\n",maximo());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                            ux=0;\r\n");
	strcat(CodigoC,"                        if(ux<0.0001)\r\n");
	strcat(CodigoC,"                            ux=0;");
	return CodigoC;
}

char* ConjuntoCampana::codigoCPP()
{
	char cad[1000];
	delete[] CodigoCPP;
	CodigoCPP=new char[5000];
	strcpy(CodigoCPP,"");
	sprintf(   cad,"    cd=new ConjuntoCampana(%f,%f,%f);",minimo(),primerCorte(),maximo());
	strcat(CodigoCPP,cad);
	return CodigoCPP;
}

char* ConjuntoS::codigoC()
{
	char cad[1000];
	delete[] CodigoC;
	CodigoC=new char[5000];
	strcpy(CodigoC,"");
	sprintf(   cad,"                        if(x<(%f))\r\n",minimo());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                            ux=0;\r\n");
	sprintf(   cad,"                        if(x<(%f)&&x>=(%f))\r\n",(primerCorte()+minimo())/2,minimo());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                            {\r\n");
	sprintf(   cad,"                                ux=(x-(%f))/((%f)-(%f));\r\n",minimo(),primerCorte(),minimo());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                                ux=2*ux*ux;\r\n");
	strcat(CodigoC,"                            }\r\n");
	sprintf(   cad,"                        if(x<(%f)&&x>=(%f))\r\n",primerCorte(),(primerCorte()+minimo())/2);
	strcat(CodigoC,cad);
	strcat(CodigoC,"                            {\r\n");
	sprintf(   cad,"                                ux=(x-(%f))/((%f)-(%f));\r\n",primerCorte(),primerCorte(),minimo());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                                ux=1-2*ux*ux;\r\n");
	strcat(CodigoC,"                            }\r\n");
	sprintf(   cad,"                        if(x>=(%f))\r\n",primerCorte());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                            ux=1;\r\n");
	strcat(CodigoC,"                        if(ux<0.0001)\r\n");
	strcat(CodigoC,"                            ux=0;");
	return CodigoC;
}

char* ConjuntoS::codigoCPP()
{
	char cad[1000];
	delete[] CodigoCPP;
	CodigoCPP=new char[5000];
	strcpy(CodigoCPP,"");
	sprintf(   cad,"    cd=new ConjuntoS(%f,%f,%f);",minimo(),primerCorte(),maximo());
	strcat(CodigoCPP,cad);
	return CodigoCPP;
}

char* ConjuntoPiCampana::codigoC()
{
	char cad[1000];
	delete[] CodigoC;
	CodigoC=new char[5000];
	strcpy(CodigoC,"");
	sprintf(   cad,"                        if(x<(%f))\r\n",minimo());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                            ux=0;\r\n");
	sprintf(   cad,"                        if(x<(%f)&&x>=(%f))\r\n",(primerCorte()+minimo())/2,minimo());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                            {\r\n");
	sprintf(   cad,"                                ux=(x-(%f))/((%f)-(%f));\r\n",minimo(),primerCorte(),minimo());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                                ux=2*ux*ux;\r\n");
	strcat(CodigoC,"                            }\r\n");
	sprintf(   cad,"                        if(x<(%f)&&x>=(%f))\r\n",primerCorte(),(primerCorte()+minimo())/2);
	strcat(CodigoC,cad);
	strcat(CodigoC,"                            {\r\n");
	sprintf(   cad,"                                ux=(x-(%f))/((%f)-(%f));\r\n",primerCorte(),primerCorte(),minimo());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                                ux=1-2*ux*ux;\r\n");
	strcat(CodigoC,"                            }\r\n");
	sprintf(   cad,"                        if(x<(%f)&&x>=(%f))\r\n",segundoCorte(),primerCorte());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                            ux=1;\r\n");
	sprintf(   cad,"                        if(x<(%f)&&x>=(%f))\r\n",(segundoCorte()+maximo())/2,segundoCorte());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                            {\r\n");
	sprintf(   cad,"                                ux=(x-(%f))/((%f)-(%f));\r\n",segundoCorte(),maximo(),segundoCorte());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                                ux=1-2*ux*ux;\r\n");
	strcat(CodigoC,"                            }\r\n");
	sprintf(   cad,"                        if(x<(%f)&&x>=(%f))\r\n",maximo(),(segundoCorte()+maximo())/2);
	strcat(CodigoC,cad);
	strcat(CodigoC,"                            {\r\n");
	sprintf(   cad,"                                ux=(x-(%f))/((%f)-(%f));\r\n",maximo(),maximo(),segundoCorte());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                                ux=2*ux*ux;\r\n");
	strcat(CodigoC,"                            }\r\n");
	sprintf(   cad,"                        if(x>=(%f))\r\n",maximo());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                            ux=0;\r\n");
	strcat(CodigoC,"                        if(ux<0.0001)\r\n");
	strcat(CodigoC,"                            ux=0;");
	return CodigoC;
}

char* ConjuntoPiCampana::codigoCPP()
{
	char cad[1000];
	delete[] CodigoCPP;
	CodigoCPP=new char[5000];
	strcpy(CodigoCPP,"");
	sprintf(   cad,"    cd=new ConjuntoPiCampana(%f,%f,%f,%f);",minimo(),primerCorte(),segundoCorte(),maximo());
	strcat(CodigoCPP,cad);
	return CodigoCPP;
}

char* ConjuntoSinglenton::codigoC()
{
	char cad[1000];
	delete[] CodigoC;
	CodigoC=new char[5000];
	strcpy(CodigoC,"");
	sprintf(   cad,"                        if(x<(%f))\r\n",minimo());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                            ux=0;\r\n");
	sprintf(   cad,"                        if(x<(%f)&&x>=(%f))\r\n",maximo(),minimo());
	strcat(CodigoC,cad);
	sprintf(   cad,"                            ux=1;\r\n");
	strcat(CodigoC,cad);
	sprintf(   cad,"                        if(x>=(%f))\r\n",maximo());
	strcat(CodigoC,cad);
	strcat(CodigoC,"                            ux=0;\r\n");
	strcat(CodigoC,"                        if(ux<0.0001)\r\n");
	strcat(CodigoC,"                            ux=0;");
	return CodigoC;
}

char* ConjuntoSinglenton::codigoCPP()
{
	char cad[1000];
	delete[] CodigoCPP;
	CodigoCPP=new char[5000];
	strcpy(CodigoCPP,"");
	sprintf(   cad,"    cd=new ConjuntoSinglenton(%f,%f);",pico(),delta());
	strcat(CodigoCPP,cad);
	return CodigoCPP;
}

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
string ConjuntoDifuso::tipo(int caso)
{
	wxString str;
	switch(caso)
	{
		case 0: str= _("Type L");break;
		case 1: str= _("Triangle");break;
		case 2: str= _("Type PI");break;
		case 3: str= _("Type Gamma");break;
		case 4: str= _("Type Z");break;
		case 5: str= _("Bell");break;
		case 6: str= _("PI-Bell");break;
		case 7: str= _("Type S");break;
		case 8: str= _("Singleton");break;
		default: str= "";break;
	}
	return string(str.mb_str());
}


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


string ConjuntoL::codigoC()
{
	wxString CodigoC="";
	CodigoC << "                        if(x<(" << minimo() << "))\n" ;
	CodigoC << "                            ux=1;\n";
	CodigoC << "                        if(x<(" << primerCorte() << ")&&x>=(" << minimo() << "))\n";
	CodigoC << "                            ux=1;\n";
	CodigoC << "                        if(x<(" << maximo() << ")&&x>=(" << primerCorte() << "))\n";
	CodigoC << "                            ux=((" << maximo() << ")-x)/((" << maximo() << ")-(" << primerCorte() << "));\n";
	CodigoC << "                        if(x>=(" << maximo() << "))\n";
	CodigoC << "                            ux=0;\n";
	CodigoC << "                        if(ux<0.0001)\n";
	CodigoC << "                            ux=0;";
	return std::string(CodigoC.mb_str());
}

string ConjuntoL::codigoCPP()
{
	wxString CodigoCPP;
	CodigoCPP=("    cd=new ConjuntoL(");
	CodigoCPP << minimo() << (",")  << primerCorte() << (",") << maximo() << (");");
	return std::string(CodigoCPP.mb_str());
}

string ConjuntoTriangulo::codigoC()
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

string ConjuntoTriangulo::codigoCPP()
{
	wxString CodigoCPP;
	CodigoCPP=("    cd=new ConjuntoTriangulo(");
	CodigoCPP << minimo() << (",")  << primerCorte() << (",") << maximo() << (");");
	return std::string(CodigoCPP.mb_str());
}

string ConjuntoPi::codigoC()
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

string ConjuntoPi::codigoCPP()
{
	wxString CodigoCPP="";
	CodigoCPP=("    cd=new ConjuntoPi(");
	CodigoCPP << minimo() << (",")  << primerCorte() << (",") << segundoCorte() << (",") << maximo() << (");");
	return std::string(CodigoCPP.mb_str());
}

string ConjuntoGamma::codigoC()
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

string ConjuntoGamma::codigoCPP()
{
	wxString CodigoCPP="";
	CodigoCPP=("    cd=new ConjuntoGamma(");
	CodigoCPP << minimo() << (",")  << primerCorte() << (",") << maximo() << (");");
	return std::string(CodigoCPP.mb_str());
}

string ConjuntoZ::codigoC()
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

string ConjuntoZ::codigoCPP()
{
	wxString CodigoCPP="";
	CodigoCPP=("    cd=new ConjuntoZ(");
	CodigoCPP << minimo() << (",")  << primerCorte() << (",") << maximo() << (");");
	return std::string(CodigoCPP.mb_str());
}

string ConjuntoCampana::codigoC()
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

string ConjuntoCampana::codigoCPP()
{
	wxString CodigoCPP="";
	CodigoCPP=("    cd=new ConjuntoCampana(");
	CodigoCPP << minimo() << (",")  << primerCorte() << (",") << maximo() << (");");
	return std::string(CodigoCPP.mb_str());
}

string ConjuntoS::codigoC()
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

string ConjuntoS::codigoCPP()
{
	wxString CodigoCPP="";
	CodigoCPP=("    cd=new ConjuntoS(");
	CodigoCPP << minimo() << (",")  << primerCorte() << (",") << maximo() << (");");
	return std::string(CodigoCPP.mb_str());
}

string ConjuntoPiCampana::codigoC()
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

string ConjuntoPiCampana::codigoCPP()
{
	wxString CodigoCPP="";
	CodigoCPP=("    cd=new ConjuntoPiCampana(");
	CodigoCPP << minimo() << (",")  << primerCorte() << (",") << segundoCorte() << (",") << maximo() << (");");
	return std::string(CodigoCPP.mb_str());
}

string ConjuntoSinglenton::codigoC()
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

string ConjuntoSinglenton::codigoCPP()
{
	wxString CodigoCPP="";
	CodigoCPP=("    cd=new ConjuntoSinglenton(");
	CodigoCPP << pico() << (",") << delta() << (");");
	return std::string(CodigoCPP.mb_str());
}

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


double ConjuntoDifuso::verificarPuntoClave(int i,double x)
{
	double xVer=x;
	double puntos[10];
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


inline double ConjuntoL::pertenencia(double x)
{
	double ux;
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


inline double ConjuntoTriangulo::pertenencia(double x)
{
	double ux;
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

inline double ConjuntoPi::pertenencia(double x)
{
	double ux;
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


inline double ConjuntoGamma::pertenencia(double x)
{
	double ux;
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

inline double ConjuntoZ::pertenencia(double x)
{
	double ux;
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

inline double ConjuntoCampana::pertenencia(double x)
{
	double ux;
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


inline double ConjuntoS::pertenencia(double x)
{
	double ux;
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

inline double ConjuntoPiCampana::pertenencia(double x)
{
	double ux;
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


inline double ConjuntoSinglenton::pertenencia(double x)
{
	double ux;
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

void ConjuntoL::nuevoPuntoClave(int punto, double x)
{
	switch(punto)
	{
		case 0: primerCorte(x);break;
		case 1: maximo(x);break;
		default:break;
	}
}

void ConjuntoTriangulo::nuevoPuntoClave(int punto, double x)
{
	switch(punto)
	{
		case 0: minimo(x);break;
		case 1: primerCorte(x);break;
		case 2: maximo(x);break;
		default:break;
	}
}

void ConjuntoPi::nuevoPuntoClave(int punto, double x)
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

void ConjuntoGamma::nuevoPuntoClave(int punto, double x)
{
	switch(punto)
	{
		case 0: minimo(x);break;
		case 1: primerCorte(x);break;
		default:break;
	}
}

void ConjuntoZ::nuevoPuntoClave(int punto, double x)
{
	switch(punto)
	{
		case 0: primerCorte(x);break;
		case 1: maximo(x);break;
		default:break;
	}
}

void ConjuntoCampana::nuevoPuntoClave(int punto, double x)
{
	switch(punto)
	{
		case 0: minimo(x);break;
		case 1: primerCorte(x);break;
		case 2: maximo(x);break;
		default:break;
	}
}

void ConjuntoPiCampana::nuevoPuntoClave(int punto, double x)
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

void ConjuntoS::nuevoPuntoClave(int punto, double x)
{
	switch(punto)
	{
		case 0: minimo(x);break;
		case 1: primerCorte(x);break;
		default:break;
	}
}

void ConjuntoSinglenton::nuevoPuntoClave(int punto, double x)
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
	wxString CodigoC="";
	CodigoC << ("                        if(x<(") << minimo() << ("))\n");
	CodigoC << ("                            ux=0;\n");
	CodigoC << ("                        if(x<(") << primerCorte() << (")&&x>=(") << minimo() << ("))\n");
	CodigoC << ("                            ux=(x-(") << minimo() << ("))/((") << primerCorte() << (")-(") << minimo() << ("));\n");
	CodigoC << ("                        if(x<(") << maximo() << (")&&x>=(") << primerCorte() << ("))\n");
	CodigoC << ("                            ux=((") << maximo() << (")-x)/((") << maximo() << (")-(") << primerCorte() << ("));\n");
	CodigoC << ("                        if(x>=(") << maximo() << ("))\n");
	CodigoC << ("                            ux=0;\n");
	CodigoC << ("                        if(ux<0.0001)\n");
	CodigoC << ("                            ux=0;\n");
	return std::string(CodigoC.mb_str());
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
	wxString CodigoC="";
	CodigoC << ("                        if(x<(") << minimo() << ("))\n");
	CodigoC << ("                            ux=0;\n");
	CodigoC << ("                        if(x<(") << primerCorte() << (")&&x>=(") << minimo() << ("))\n");
	CodigoC << ("                            ux=(x-(") << minimo() << ("))/((") << primerCorte() << (")-(") << minimo() << ("));\n");
	CodigoC << ("                        if(x<(") << segundoCorte() << (")&&x>=(") << primerCorte() << ("))\n");
	CodigoC << ("                            ux=1;\n");
	CodigoC << ("                        if(x<(") << maximo() << (")&&x>=(") << segundoCorte() << ("))\n");
	CodigoC << ("                            ux=((") << maximo() << (")-x)/((") << maximo() << (")-(") << segundoCorte() << ("));\n");
	CodigoC << ("                        if(x>=(") << maximo() << ("))\n");
	CodigoC << ("                            ux=0;\n");
	CodigoC << ("                        if(ux<0.0001)\n");
	CodigoC << ("                            ux=0;");
	return std::string(CodigoC.mb_str());
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
	wxString CodigoC="";
	CodigoC << ("                        if(x<(") << minimo() << ("))\n");
	CodigoC << ("                            ux=0;\n");
	CodigoC << ("                        if(x<(") << primerCorte() << (")&&x>=(") << minimo() << ("))\n");
	CodigoC << ("                            ux=(x-(") << minimo() << ("))/((") << primerCorte() << (")-(") << minimo() << ("));\n");
	CodigoC << ("                        if(x>=(") << primerCorte() << ("))\n");
	CodigoC << ("                            ux=1;\r\n");
	CodigoC << ("                        if(ux<0.0001)\r\n");
	CodigoC << ("                            ux=0;");
	return std::string(CodigoC.mb_str());
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
	wxString CodigoC="";
	CodigoC << ("                        if(x<(") << minimo() << ("))\n");
	CodigoC << ("                            ux=1;\n");
	CodigoC << ("                        if(x<(") << primerCorte() << ("))\n");
	CodigoC << ("                            ux=1;\n");
	CodigoC << ("                        if(x<(") << (primerCorte()+maximo())/2 << (")&&x>=(") << primerCorte() << ("))\n");
	CodigoC << ("                            {\n");
	CodigoC << ("                                ux=(x-(") << primerCorte() << ("))/((") << maximo() << (")-(") << primerCorte() << ("));\n");
	CodigoC << ("                                ux=1-2*ux*ux;\n");
	CodigoC << ("                            }\n");
	CodigoC << ("                        if(x<(") << maximo() << (")&&x>=(") << (primerCorte()+maximo())/2 << ("))\n");
	CodigoC << ("                            {\n");
	CodigoC << ("                                ux=(x-(") << maximo() << ("))/((") << maximo() << (")-(") << primerCorte() << ("));\n");
	CodigoC << ("                                ux=2*ux*ux;\n");
	CodigoC << ("                            }\n");
	CodigoC << ("                        if(x>=(") << maximo() << ("))\n");
	CodigoC << ("                            ux=0;\n");
	CodigoC << ("                        if(ux<0.0001)\n");
	CodigoC << ("                            ux=0;");
	return std::string(CodigoC.mb_str());
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
	wxString CodigoC="";
	CodigoC << ("                        if(x<(") << minimo() << ("))\n");
	CodigoC << ("                            ux=0;\n");
	CodigoC << ("                        if(x<(") << (primerCorte()+minimo())/2 << (")&&x>=(") << minimo() << ("))\n");
	CodigoC << ("                            {\n");
	CodigoC << ("                                ux=(x-(") << minimo() << ("))/((") << primerCorte() << (")-(") << minimo() << ("));\n");
	CodigoC << ("                                ux=2*ux*ux;\n");
	CodigoC << ("                            }\n");
	CodigoC << ("                        if(x<(") << primerCorte() << (")&&x>=(") << (primerCorte()+minimo())/2 << ("))\n");
	CodigoC << ("                            {\n");
	CodigoC << ("                                ux=(x-(") << primerCorte() << ("))/((") << primerCorte() << (")-(") << minimo() << ("));\n");
	CodigoC << ("                                ux=1-2*ux*ux;\n");
	CodigoC << ("                            }\n");
	CodigoC << ("                        if(x<(") << (primerCorte()+maximo())/2 << (")&&x>=(") << primerCorte() << ("))\n");
	CodigoC << ("                            {\n");
	CodigoC << ("                                ux=(x-(") << primerCorte() << ("))/((") << maximo() << (")-(") << primerCorte() << ("));\n");
	CodigoC << ("                                ux=1-2*ux*ux;\n");
	CodigoC << ("                            }\n");
	CodigoC << ("                        if(x<(") << maximo() << (")&&x>=(") << (primerCorte()+maximo())/2 << ("))\n");
	CodigoC << ("                            {\n");
	CodigoC << ("                                ux=(x-(") << maximo() << ("))/((") << maximo() << (")-(") << primerCorte() << ("));\n");
	CodigoC << ("                                ux=2*ux*ux;\n");
	CodigoC << ("                            }\n");
	CodigoC << ("                        if(x>=(") << maximo() << ("))\n");
	CodigoC << ("                            ux=0;\n");
	CodigoC << ("                        if(ux<0.0001)\n");
	CodigoC << ("                            ux=0;");
	return std::string(CodigoC.mb_str());
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
	wxString CodigoC="";
	CodigoC << ("                        if(x<(") << minimo() << ("))\n");
	CodigoC << ("                            ux=0;\n");
	CodigoC << ("                        if(x<(") << (primerCorte()+minimo())/2 << (")&&x>=(") << minimo() << ("))\r\n");
	CodigoC << ("                            {\n");
	CodigoC << ("                                ux=(x-(") << minimo() << ("))/((") << primerCorte() << (")-(") << minimo() << ("));\n");
	CodigoC << ("                                ux=2*ux*ux;\n");
	CodigoC << ("                            }\n");
	CodigoC << ("                        if(x<(") << primerCorte() << (")&&x>=(") << (primerCorte()+minimo())/2 << ("))\n");
	CodigoC << ("                            {\n");
	CodigoC << ("                                ux=(x-(") << primerCorte() << ("))/((") << primerCorte() << (")-(") << minimo() << ("));\n");
	CodigoC << ("                                ux=1-2*ux*ux;\n");
	CodigoC << ("                            }\n");
	CodigoC << ("                        if(x>=(") << primerCorte() << ("))\n");
	CodigoC << ("                            ux=1;\n");
	CodigoC << ("                        if(ux<0.0001)\n");
	CodigoC << ("                            ux=0;");
	return std::string(CodigoC.mb_str());
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
	wxString CodigoC="";
	CodigoC << ("                        if(x<(") << minimo() << ("))\n");
	CodigoC << ("                            ux=0;\n");
	CodigoC << ("                        if(x<(") << (primerCorte()+minimo())/2 << (")&&x>=(") << minimo() << ("))\n");
	CodigoC << ("                            {\n");
	CodigoC << ("                                ux=(x-(") << minimo() << ("))/((") << primerCorte() << (")-(") << minimo() << ("));\n");
	CodigoC << ("                                ux=2*ux*ux;\n");
	CodigoC << ("                            }\n");
	CodigoC << ("                        if(x<(") << primerCorte() << (")&&x>=(") << (primerCorte()+minimo())/2 << ("))\n");
	CodigoC << ("                            {\n");
	CodigoC << ("                                ux=(x-(") << primerCorte() << ("))/((") << primerCorte() << (")-(") << minimo() << ("));\n");
	CodigoC << ("                                ux=1-2*ux*ux;\n");
	CodigoC << ("                            }\n");
	CodigoC << ("                        if(x<(") << segundoCorte() << (")&&x>=(") << primerCorte() << ("))\n");
	CodigoC << ("                            ux=1;\n");
	CodigoC << ("                        if(x<(") << (segundoCorte()+maximo())/2 << (")&&x>=(") << segundoCorte() << ("))\n");
	CodigoC << ("                            {\n");
	CodigoC << ("                                ux=(x-(") << segundoCorte() << ("))/((") << maximo() << (")-(") << segundoCorte() << ("));\n");
	CodigoC << ("                                ux=1-2*ux*ux;\n");
	CodigoC << ("                            }\n");
	CodigoC << ("                        if(x<(") << maximo() << (")&&x>=(") << (segundoCorte()+maximo())/2 << ("))\n");
	CodigoC << ("                            {\n");
	CodigoC << ("                                ux=(x-(") << maximo() << ("))/((") << maximo() << (")-(") << segundoCorte() << ("));\n");
	CodigoC << ("                                ux=2*ux*ux;\n");
	CodigoC << ("                            }\n");
	CodigoC << ("                        if(x>=(") << maximo() << ("))\n");
	CodigoC << ("                            ux=0;\n");
	CodigoC << ("                        if(ux<0.0001)\n");
	CodigoC << ("                            ux=0;");
	return std::string(CodigoC.mb_str());
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
	wxString CodigoC="";
	CodigoC << ("                        if(x<(") << minimo() << ("))\n");
	CodigoC << ("                            ux=0;\n");
	CodigoC << ("                        if(x<(") << maximo() << (")&&x>=(") << minimo() << ("))\n");
	CodigoC << ("                            ux=1;\n");
	CodigoC << ("                        if(x>=(") << maximo() << ("))\n");
	CodigoC << ("                            ux=0;\n");
	CodigoC << ("                        if(ux<0.0001)\n");
	CodigoC << ("                            ux=0;");
	return std::string(CodigoC.mb_str());
}

string ConjuntoSinglenton::codigoCPP()
{
	wxString CodigoCPP="";
	CodigoCPP=("    cd=new ConjuntoSinglenton(");
	CodigoCPP << pico() << (",") << delta() << (");");
	return std::string(CodigoCPP.mb_str());
}

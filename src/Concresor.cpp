#include "Concresor.h"

string Concresor::nombre(int caso)
{
	wxString str;
	switch(caso)
	{
		case 0 : str=_("First of maximums"); break;
		case 1 : str=_("Last of maximums"); break;
		case 2 : str=_("Medio of maximums"); break;
		case 3 : str=_("Center of gravity"); break;
		case 4 : str=_("Height"); break;
		default : str=""; break;
	}
	return string(str.mb_str());
}

float PrimerMaximo::salidaConcreta(float *ent)
{
	float con;
	float concreto=0;
	float y;
	float ymax;
	ymax=Motor->salidas()->rangoMinimoVariable(NumeroVariable);
	Motor->actualizarEntradas(ent);
	int i;
	for(i=0;i<(Motor->salidas()->numeroIntervalosEnVariable(NumeroVariable)+1);i++)
	{
		con=defecto();
		y=Motor->salidas()->rangoMinimoVariable(NumeroVariable)+i*Motor->salidas()->intervaloEnVariable(NumeroVariable);
		int j;
		for(j=0;j<Motor->numeroReglas();j++)
		{
			float temp;
			temp=Motor->pertenenciaComposicion(NumeroVariable,j,y);
			con=Conjuncion->opera(con,temp);
		}
		if(concreto<con)
		{
			concreto=con;
			ymax=y;
		}
	}
	return ymax;
}


float UltimoMaximo::salidaConcreta(float *ent)
{
	float con;
	float concreto=0;
	float y;
	float ymax;
	ymax=Motor->salidas()->rangoMinimoVariable(NumeroVariable);
	Motor->actualizarEntradas(ent);
	int i;
	for(i=0;i<(Motor->salidas()->numeroIntervalosEnVariable(NumeroVariable)+1);i++)
	{
		con=defecto();
		y=Motor->salidas()->rangoMinimoVariable(NumeroVariable)+i*Motor->salidas()->intervaloEnVariable(NumeroVariable);
		int j;
		for(j=0;j<Motor->numeroReglas();j++)
		{
			float temp;
			temp=Motor->pertenenciaComposicion(NumeroVariable,j,y);
			con=Conjuncion->opera(con,temp);
		}
		if(concreto<=con)
		{
			concreto=con;
			ymax=y;
		}
	}
	return ymax;
}


float MediaDeMaximos::salidaConcreta(float *ent)
{
	float con;
	float concreto1=0;
	float concreto2=0;
	float y;
	float ymax;
	float ymax1,ymax2;
	ymax=Motor->salidas()->rangoMinimoVariable(NumeroVariable);
	ymax1=ymax;
	ymax2=ymax;
	Motor->actualizarEntradas(ent);
	int i;
	for(i=0;i<(Motor->salidas()->numeroIntervalosEnVariable(NumeroVariable)+1);i++)
	{
		con=defecto();
		y=Motor->salidas()->rangoMinimoVariable(NumeroVariable)+i*Motor->salidas()->intervaloEnVariable(NumeroVariable);
		int j;
		for(j=0;j<Motor->numeroReglas();j++)
		{
			float temp;
			temp=Motor->pertenenciaComposicion(NumeroVariable,j,y);
			con=Conjuncion->opera(con,temp);
		}
		if(concreto1<con)
		{
			concreto1=con;
			ymax1=y;
		}
		if(concreto2<=con)
		{
			concreto2=con;
			ymax2=y;
		}
	}
	ymax=(ymax1+ymax2)/2;
	return ymax;
}


float CentroDeGravedad::salidaConcreta(float *ent)
{
	float con;
	float y;
	float y1=0;
	float y2=0;
	float ymax;
	Motor->actualizarEntradas(ent);
	int i;
	for(i=0;i<(Motor->salidas()->numeroIntervalosEnVariable(NumeroVariable)+1);i++)
	{
		con=defecto();
		y=Motor->salidas()->rangoMinimoVariable(NumeroVariable)+i*Motor->salidas()->intervaloEnVariable(NumeroVariable);
		int j;
		for(j=0;j<Motor->numeroReglas();j++)
		{
			float temp;
			temp=Motor->pertenenciaComposicion(NumeroVariable,j,y);
			con=Conjuncion->opera(con,temp);
		}
		y1=y1+y*con;
		y2=y2+con;
	}
	if(fabs(y2)<0.000001)
		y2=100000.0;
	if(fabs(y1)<0.000001)
		y1=0.0;
	ymax=y1/y2;
	return ymax;
}

float Altura::salidaConcreta(float *ent)
{
	float ymax;
	float y;
	 float y1,y2;
	Motor->actualizarEntradas(ent);
	int j;
    y1=0;
    y2=0;
	for(j=0;j<Motor->numeroReglas();j++)
	{
		if(Motor->activarRegla(j))
		{
			float temp;
			y=Motor->conjuntoSalida(j,NumeroVariable)->centroAltura();
			temp=Motor->pertenenciaComposicion(NumeroVariable,j,y);
			y1=y1+temp*y;
			y2=y2+temp;
		}
	}
	if(fabs(y2)<0.000001)
		y2=100000.0;
	if(fabs(y1)<0.000001)
		y1=0.0;
	ymax=y1/y2;
	return ymax;
}

//////////////////////////

string PrimerMaximo::codigoC()
{
	wxString CodigoC="";
	CodigoC << ("float salidaConcreta") << NumeroVariable << ("(float *ent)\n");
	CodigoC << ("{\n");
	CodigoC << ("    int NumeroSalida=") << NumeroVariable << (";\n");
	CodigoC << ("    float con=") << defecto() << (";\n");
	CodigoC << ("    float concreto=0;\n");
	CodigoC << ("    float y;\n");
	CodigoC << ("    float ymax;\n");
	CodigoC << ("    int i;\n");
	CodigoC << ("    int j;\n");
	CodigoC << ("    ymax=VariablesSalida[NumeroSalida].minimo;\n");
	CodigoC << ("    actualizarEntradas(ent);\n");
	CodigoC << ("    for(i=0;i<(VariablesSalida[NumeroSalida].intervalos+1);i++)\n");
	CodigoC << ("    {\n");
	CodigoC << ("        float con=") << defecto() << (";\n");
	CodigoC << ("        y=VariablesSalida[NumeroSalida].minimo+i*VariablesSalida[NumeroSalida].intervalo;\n");
	CodigoC << ("        for(j=0;j<NUMEROREGLAS;j++)\n");
	CodigoC << ("        {\n");
	CodigoC << ("            float temp;\n");
	CodigoC << ("            temp=pertenenciaComposicion(NumeroSalida,j,y);\n");
	CodigoC << ("            con=Conjuncion(con,temp);\n");
	CodigoC << ("        }\n");
	CodigoC << ("        if(concreto<con)\n");
	CodigoC << ("        {\n");
	CodigoC << ("            concreto=con;\n");
	CodigoC << ("            ymax=y;\n");
	CodigoC << ("        }\n");
	CodigoC << ("    }\n");
	CodigoC << ("    return ymax;\n");
	CodigoC << ("}\n");
	return std::string(CodigoC.mb_str());
}

string PrimerMaximo::codigoCPP()
{
	wxString CodigoCPP="";
	CodigoCPP << ("    conc=new PrimerMaximo(motor,") << NumeroVariable << (",Conjuncion);");
	return std::string(CodigoCPP.mb_str());
}

string UltimoMaximo::codigoC()
{
	wxString CodigoC="";
	CodigoC << ("float salidaConcreta") << NumeroVariable << ("(float *ent)\n");
	CodigoC << ("{\n");
	CodigoC << ("    int NumeroSalida=") << NumeroVariable << (";\n");
	CodigoC << ("    float con=") << defecto() << (";\n");
	CodigoC << ("    float concreto=0;\n");
	CodigoC << ("    float y;\n");
	CodigoC << ("    float ymax;\n");
	CodigoC << ("    int i;\n");
	CodigoC << ("    int j;\n");
	CodigoC << ("    ymax=VariablesSalida[NumeroSalida].minimo;\n");
	CodigoC << ("    actualizarEntradas(ent);\n");
	CodigoC << ("    for(i=0;i<(VariablesSalida[NumeroSalida].intervalos+1);i++)\n");
	CodigoC << ("    {\n");
	CodigoC << ("        float con=") << defecto() << (";\n");
	CodigoC << ("        y=VariablesSalida[NumeroSalida].minimo+i*VariablesSalida[NumeroSalida].intervalo;\n");
	CodigoC << ("        for(j=0;j<NUMEROREGLAS;j++)\n");
	CodigoC << ("        {\n");
	CodigoC << ("            float temp;\n");
	CodigoC << ("            temp=pertenenciaComposicion(NumeroSalida,j,y);\n");
	CodigoC << ("            con=Conjuncion(con,temp);\n");
	CodigoC << ("        }\n");
	CodigoC << ("        if(concreto<=con)\n");
	CodigoC << ("        {\n");
	CodigoC << ("            concreto=con;\n");
	CodigoC << ("            ymax=y;\n");
	CodigoC << ("        }\n");
	CodigoC << ("    }\n");
	CodigoC << ("    return ymax;\n");
	CodigoC << ("}\n");
	return std::string(CodigoC.mb_str());
}

string UltimoMaximo::codigoCPP()
{
	wxString CodigoCPP="";
	CodigoCPP << ("    conc=new UltimoMaximo(motor,") << NumeroVariable << (",Conjuncion);");
	return std::string(CodigoCPP.mb_str());
}

string MediaDeMaximos::codigoC()
{
	wxString CodigoC="";
	CodigoC << ("float salidaConcreta") << NumeroVariable << ("(float *ent)\n");
	CodigoC << ("{\n");
	CodigoC << ("    int NumeroSalida=") << NumeroVariable << (";\n");
	CodigoC << ("    float con=") << defecto() << (";\n");
	CodigoC << ("    float concreto1=0;\n");
	CodigoC << ("    float concreto2=0;\n");
	CodigoC << ("    float y;\n");
	CodigoC << ("    float ymax;\n");
	CodigoC << ("    float ymax1,ymax2;\n");
	CodigoC << ("    int i;\n");
	CodigoC << ("    int j;\n");
	CodigoC << ("    ymax=VariablesSalida[NumeroSalida].minimo;\n");
	CodigoC << ("    ymax1=ymax;\n");
	CodigoC << ("    ymax2=ymax;\n");
	CodigoC << ("    actualizarEntradas(ent);\n");
	CodigoC << ("    for(i=0;i<(VariablesSalida[NumeroSalida].intervalos+1);i++)\n");
	CodigoC << ("    {\n");
	CodigoC << ("        float con=") << defecto() << (";\n");
	CodigoC << ("        y=VariablesSalida[NumeroSalida].minimo+i*VariablesSalida[NumeroSalida].intervalo;\n");
	CodigoC << ("        for(j=0;j<NUMEROREGLAS;j++)\n");
	CodigoC << ("        {\n");
	CodigoC << ("            float temp;\n");
	CodigoC << ("            temp=pertenenciaComposicion(NumeroSalida,j,y);\n");
	CodigoC << ("            con=Conjuncion(con,temp);\n");
	CodigoC << ("        }\n");
	CodigoC << ("        if(concreto<con)\n");
	CodigoC << ("        {\n");
	CodigoC << ("            concreto=con;\n");
	CodigoC << ("            ymax1=y;\n");
	CodigoC << ("        }\n");
	CodigoC << ("        if(concreto<=con)\n");
	CodigoC << ("        {\n");
	CodigoC << ("            concreto=con;\n");
	CodigoC << ("            ymax2=y;\n");
	CodigoC << ("        }\n");
	CodigoC << ("    }\n");
	CodigoC << ("    ymax=(ymax1+ymax2)/2;\n");
	CodigoC << ("    return ymax;\n");
	CodigoC << ("}\n");
	return std::string(CodigoC.mb_str());
}

string MediaDeMaximos::codigoCPP()
{
	wxString CodigoCPP="";
	CodigoCPP << ("    conc=new MediaDeMaximos(motor,") << NumeroVariable << (",Conjuncion);");
	return std::string(CodigoCPP.mb_str());
}

string CentroDeGravedad::codigoC()
{
	wxString CodigoC="";
	CodigoC << ("float salidaConcreta") << NumeroVariable << ("(float *ent)\n");
	CodigoC << ("{\n");
	CodigoC << ("    int NumeroSalida=") << NumeroVariable << (";\n");
	CodigoC << ("    float con=") << defecto() << (";\n");
	CodigoC << ("    float y;\n");
	CodigoC << ("    float y1=0;\n");
	CodigoC << ("    float y2=0;\n");
	CodigoC << ("    float ymax;\n");
	CodigoC << ("    int i;\n");
	CodigoC << ("    int j;\n");
	CodigoC << ("    ymax=VariablesSalida[NumeroSalida].minimo;\n");
	CodigoC << ("    actualizarEntradas(ent);\n");
	CodigoC << ("    for(i=0;i<(VariablesSalida[NumeroSalida].intervalos+1);i++)\n");
	CodigoC << ("    {\n");
	CodigoC << ("        float con=") << defecto() << (";\n");
	CodigoC << ("        y=VariablesSalida[NumeroSalida].minimo+i*VariablesSalida[NumeroSalida].intervalo;\n");
	CodigoC << ("        for(j=0;j<NUMEROREGLAS;j++)\n");
	CodigoC << ("        {\n");
	CodigoC << ("            float temp;\n");
	CodigoC << ("            temp=pertenenciaComposicion(NumeroSalida,j,y);\n");
	CodigoC << ("            con=Conjuncion(con,temp);\n");
	CodigoC << ("        }\n");
	CodigoC << ("        y1=y1+y*con;\n");
	CodigoC << ("        y2=y2+con;\n");
	CodigoC << ("    }\n");
	CodigoC << ("    if(fabs(y2)<0.000001)\n");
	CodigoC << ("        y2=100000.0;\n");
	CodigoC << ("    if(fabs(y1)<0.000001)\n");
	CodigoC << ("        y1=0.0;\n");
	CodigoC << ("    ymax=y1/y2;\n");
	CodigoC << ("    return ymax;\n");
	CodigoC << ("}\n");
	return std::string(CodigoC.mb_str());
}

string CentroDeGravedad::codigoCPP()
{
	wxString CodigoCPP="";
	CodigoCPP << ("    conc=new CentroDeGravedad(motor,") << NumeroVariable << (",Conjuncion);");
	return std::string(CodigoCPP.mb_str());
}

string Altura::codigoC()
{
	wxString CodigoC="";
	CodigoC << ("float salidaConcreta") << NumeroVariable << ("(float *ent)\n");
	CodigoC << ("{\n");
	CodigoC << ("    int NumeroSalida=") << NumeroVariable << (";\n");
	CodigoC << ("    float y;\n");
	CodigoC << ("    float y1=0;\n");
	CodigoC << ("    float y2=0;\n");
	CodigoC << ("    float ymax;\n");
	CodigoC << ("    int j;\n");
	CodigoC << ("    ymax=VariablesSalida[NumeroSalida].minimo;\n");
	CodigoC << ("    actualizarEntradas(ent);\n");
	CodigoC << ("    for(j=0;j<NUMEROREGLAS;j++)\n");
	CodigoC << ("    {\n");
	CodigoC << ("        if(activarRegla(j))\n");
	CodigoC << ("        {\n");
	CodigoC << ("            float temp;\n");
	CodigoC << ("            y=CentrosAltura[j][NumeroSalida];\n");
	CodigoC << ("            temp=pertenenciaComposicion(NumeroSalida,j,y);\n");
	CodigoC << ("            y1=y1+y*temp;\n");
	CodigoC << ("            y2=y2+temp;\n");
	CodigoC << ("        }\n");
	CodigoC << ("    }\n");
	CodigoC << ("    if(fabs(y2)<0.000001)\n");
	CodigoC << ("        y2=100000.0;\n");
	CodigoC << ("    if(fabs(y1)<0.000001)\n");
	CodigoC << ("        y1=0.0;\n");
	CodigoC << ("    ymax=y1/y2;\n");
	CodigoC << ("    return ymax;\n");
	CodigoC << ("}\n");
	return std::string(CodigoC.mb_str());
}

string Altura::codigoCPP()
{
	wxString CodigoCPP="";
	CodigoCPP << ("    conc=new Altura(motor,") << NumeroVariable << (",Conjuncion);");
	return std::string(CodigoCPP.mb_str());
}


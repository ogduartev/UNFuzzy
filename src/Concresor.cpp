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
	char cad[100];
	delete[] CodigoC;
	CodigoC=new char [5000];
	strcpy(CodigoC,"");
	sprintf(cad,"float salidaConcreta%u(float *ent)\r\n",NumeroVariable);
	strcat(CodigoC,cad);
	strcat(CodigoC,"{\r\n");
	sprintf(cad,"    int NumeroSalida=%u;\r\n",NumeroVariable);
	strcat(CodigoC,cad);
	sprintf(cad,"    float con=%f;\r\n",defecto());
	strcat(CodigoC,cad);
	strcat(CodigoC,"    float concreto=0;\r\n");
	strcat(CodigoC,"    float y;\r\n");
	strcat(CodigoC,"    float ymax;\r\n");
	strcat(CodigoC,"    int i;\r\n");
	strcat(CodigoC,"    int j;\r\n");
	strcat(CodigoC,"    ymax=VariablesSalida[NumeroSalida].minimo;\r\n");
	strcat(CodigoC,"    actualizarEntradas(ent);\r\n");
	strcat(CodigoC,"    for(i=0;i<(VariablesSalida[NumeroSalida].intervalos+1);i++)\r\n");
	strcat(CodigoC,"    {\r\n");
	sprintf(cad,"        float con=%f;\r\n",defecto());
	strcat(CodigoC,cad);
	strcat(CodigoC,"        y=VariablesSalida[NumeroSalida].minimo+i*VariablesSalida[NumeroSalida].intervalo;\r\n");
	strcat(CodigoC,"        for(j=0;j<NUMEROREGLAS;j++)\r\n");
	strcat(CodigoC,"        {\r\n");
	strcat(CodigoC,"            float temp;\r\n");
	strcat(CodigoC,"            temp=pertenenciaComposicion(NumeroSalida,j,y);\r\n");
	strcat(CodigoC,"            con=Conjuncion(con,temp);\r\n");
	strcat(CodigoC,"        }\r\n");
	strcat(CodigoC,"        if(concreto<con)\r\n");
	strcat(CodigoC,"        {\r\n");
	strcat(CodigoC,"            concreto=con;\r\n");
	strcat(CodigoC,"            ymax=y;\r\n");
	strcat(CodigoC,"        }\r\n");
	strcat(CodigoC,"    }\r\n");
	strcat(CodigoC,"    return ymax;\r\n");
	strcat(CodigoC,"}\r\n");
	return CodigoC;
}

string PrimerMaximo::codigoCPP()
{
	char* CodigoCPP;
	CodigoCPP=new char [1000];
	strcpy(CodigoCPP,"");
	sprintf(CodigoCPP,"    conc=new PrimerMaximo(motor,%d,Conjuncion);",NumeroVariable);
	return CodigoCPP;
}

string UltimoMaximo::codigoC()
{
	char cad[100];
	delete[] CodigoC;
	CodigoC=new char [5000];
	strcpy(CodigoC,"");
	sprintf(cad,"float salidaConcreta%u(float *ent)\r\n",NumeroVariable);
	strcat(CodigoC,cad);
	strcat(CodigoC,"{\r\n");
	sprintf(cad,"    int NumeroSalida=%u;\r\n",NumeroVariable);
	strcat(CodigoC,cad);
	sprintf(cad,"    float con=%f;\r\n",defecto());
	strcat(CodigoC,cad);
	strcat(CodigoC,"    float concreto=0;\r\n");
	strcat(CodigoC,"    float y;\r\n");
	strcat(CodigoC,"    float ymax;\r\n");
	strcat(CodigoC,"    int i;\r\n");
	strcat(CodigoC,"    int j;\r\n");
	strcat(CodigoC,"    ymax=VariablesSalida[NumeroSalida].minimo;\r\n");
	strcat(CodigoC,"    actualizarEntradas(ent);\r\n");
	strcat(CodigoC,"    for(i=0;i<(VariablesSalida[NumeroSalida].intervalos+1);i++)\r\n");
	strcat(CodigoC,"    {\r\n");
	sprintf(cad,"        float con=%f;\r\n",defecto());
	strcat(CodigoC,cad);
	strcat(CodigoC,"        y=VariablesSalida[NumeroSalida].minimo+i*VariablesSalida[NumeroSalida].intervalo;\r\n");
	strcat(CodigoC,"        for(j=0;j<NUMEROREGLAS;j++)\r\n");
	strcat(CodigoC,"        {\r\n");
	strcat(CodigoC,"            float temp;\r\n");
	strcat(CodigoC,"            temp=pertenenciaComposicion(NumeroSalida,j,y);\r\n");
	strcat(CodigoC,"            con=Conjuncion(con,temp);\r\n");
	strcat(CodigoC,"        }\r\n");
	strcat(CodigoC,"        if(concreto<=con)\r\n");
	strcat(CodigoC,"        {\r\n");
	strcat(CodigoC,"            concreto=con;\r\n");
	strcat(CodigoC,"            ymax=y;\r\n");
	strcat(CodigoC,"        }\r\n");
	strcat(CodigoC,"    }\r\n");
	strcat(CodigoC,"    return ymax;\r\n");
	strcat(CodigoC,"}\r\n");
	return CodigoC;
}

string UltimoMaximo::codigoCPP()
{
	char* CodigoCPP;
	CodigoCPP=new char [1000];
	strcpy(CodigoCPP,"");
	sprintf(CodigoCPP,"    conc=new UltimoMaximo(motor,%d,Conjuncion);",NumeroVariable);
	return CodigoCPP;
}

string MediaDeMaximos::codigoC()
{
	char cad[100];
	delete[] CodigoC;
	CodigoC=new char [5000];
	strcpy(CodigoC,"");
	sprintf(cad,"float salidaConcreta%u(float *ent)\r\n",NumeroVariable);
	strcat(CodigoC,cad);
	strcat(CodigoC,"{\r\n");
	sprintf(cad,"    int NumeroSalida=%u;\r\n",NumeroVariable);
	strcat(CodigoC,cad);
	sprintf(cad,"    float con=%f;\r\n",defecto());
	strcat(CodigoC,cad);
	strcat(CodigoC,"    float concreto1=0;\r\n");
	strcat(CodigoC,"    float concreto2=0;\r\n");
	strcat(CodigoC,"    float y;\r\n");
	strcat(CodigoC,"    float ymax;\r\n");
	strcat(CodigoC,"    float ymax1,ymax2;\r\n");
	strcat(CodigoC,"    int i;\r\n");
	strcat(CodigoC,"    int j;\r\n");
	strcat(CodigoC,"    ymax=VariablesSalida[NumeroSalida].minimo;\r\n");
	strcat(CodigoC,"    ymax1=ymax;\r\n");
	strcat(CodigoC,"    ymax2=ymax;\r\n");
	strcat(CodigoC,"    actualizarEntradas(ent);\r\n");
	strcat(CodigoC,"    for(i=0;i<(VariablesSalida[NumeroSalida].intervalos+1);i++)\r\n");
	strcat(CodigoC,"    {\r\n");
	sprintf(cad,"        float con=%f;\r\n",defecto());
	strcat(CodigoC,cad);
	strcat(CodigoC,"        y=VariablesSalida[NumeroSalida].minimo+i*VariablesSalida[NumeroSalida].intervalo;\r\n");
	strcat(CodigoC,"        for(j=0;j<NUMEROREGLAS;j++)\r\n");
	strcat(CodigoC,"        {\r\n");
	strcat(CodigoC,"            float temp;\r\n");
	strcat(CodigoC,"            temp=pertenenciaComposicion(NumeroSalida,j,y);\r\n");
	strcat(CodigoC,"            con=Conjuncion(con,temp);\r\n");
	strcat(CodigoC,"        }\r\n");
	strcat(CodigoC,"        if(concreto<con)\r\n");
	strcat(CodigoC,"        {\r\n");
	strcat(CodigoC,"            concreto=con;\r\n");
	strcat(CodigoC,"            ymax1=y;\r\n");
	strcat(CodigoC,"        }\r\n");
	strcat(CodigoC,"        if(concreto<=con)\r\n");
	strcat(CodigoC,"        {\r\n");
	strcat(CodigoC,"            concreto=con;\r\n");
	strcat(CodigoC,"            ymax2=y;\r\n");
	strcat(CodigoC,"        }\r\n");
	strcat(CodigoC,"    }\r\n");
	strcat(CodigoC,"    ymax=(ymax1+ymax2)/2;\r\n");
	strcat(CodigoC,"    return ymax;\r\n");
	strcat(CodigoC,"}\r\n");
	return CodigoC;
}

string MediaDeMaximos::codigoCPP()
{
	char* CodigoCPP;
	CodigoCPP=new char [1000];
	strcpy(CodigoCPP,"");
	sprintf(CodigoCPP,"    conc=new MediaDeMaximos(motor,%d,Conjuncion);",NumeroVariable);
	return CodigoCPP;
}

string CentroDeGravedad::codigoC()
{
	char cad[100];
	delete[] CodigoC;
	CodigoC=new char [5000];
	strcpy(CodigoC,"");
	sprintf(cad,"float salidaConcreta%u(float *ent)\r\n",NumeroVariable);
	strcat(CodigoC,cad);
	strcat(CodigoC,"{\r\n");
	sprintf(cad,"    int NumeroSalida=%u;\r\n",NumeroVariable);
	strcat(CodigoC,cad);
	sprintf(cad,"    float con=%f;\r\n",defecto());
	strcat(CodigoC,cad);
	strcat(CodigoC,"    float y;\r\n");
	strcat(CodigoC,"    float y1=0;\r\n");
	strcat(CodigoC,"    float y2=0;\r\n");
	strcat(CodigoC,"    float ymax;\r\n");
	strcat(CodigoC,"    int i;\r\n");
	strcat(CodigoC,"    int j;\r\n");
	strcat(CodigoC,"    ymax=VariablesSalida[NumeroSalida].minimo;\r\n");
	strcat(CodigoC,"    actualizarEntradas(ent);\r\n");
	strcat(CodigoC,"    for(i=0;i<(VariablesSalida[NumeroSalida].intervalos+1);i++)\r\n");
	strcat(CodigoC,"    {\r\n");
	sprintf(cad,"        float con=%f;\r\n",defecto());
	strcat(CodigoC,cad);
	strcat(CodigoC,"        y=VariablesSalida[NumeroSalida].minimo+i*VariablesSalida[NumeroSalida].intervalo;\r\n");
	strcat(CodigoC,"        for(j=0;j<NUMEROREGLAS;j++)\r\n");
	strcat(CodigoC,"        {\r\n");
	strcat(CodigoC,"            float temp;\r\n");
	strcat(CodigoC,"            temp=pertenenciaComposicion(NumeroSalida,j,y);\r\n");
	strcat(CodigoC,"            con=Conjuncion(con,temp);\r\n");
	strcat(CodigoC,"        }\r\n");
	strcat(CodigoC,"        y1=y1+y*con;\r\n");
	strcat(CodigoC,"        y2=y2+con;\r\n");
	strcat(CodigoC,"    }\r\n");
	strcat(CodigoC,"    if(fabs(y2)<0.000001)\r\n");
	strcat(CodigoC,"        y2=100000.0;\r\n");
	strcat(CodigoC,"    if(fabs(y1)<0.000001)\r\n");
	strcat(CodigoC,"        y1=0.0;\r\n");
	strcat(CodigoC,"    ymax=y1/y2;\r\n");
	strcat(CodigoC,"    return ymax;\r\n");
	strcat(CodigoC,"}\r\n");
	return CodigoC;
}

string CentroDeGravedad::codigoCPP()
{
	char* CodigoCPP;
	CodigoCPP=new char [1000];
	strcpy(CodigoCPP,"");
	sprintf(CodigoCPP,"    conc=new CentroDeGravedad(motor,%d,Conjuncion);",NumeroVariable);
	return CodigoCPP;
}

string Altura::codigoC()
{
	char cad[100];
	delete[] CodigoC;
	CodigoC=new char [5000];
	strcpy(CodigoC,"");
	sprintf(cad,"float salidaConcreta%u(float *ent)\r\n",NumeroVariable);
	strcat(CodigoC,cad);
	strcat(CodigoC,"{\r\n");
	sprintf(cad,"    int NumeroSalida=%u;\r\n",NumeroVariable);
	strcat(CodigoC,cad);
	strcat(CodigoC,"    float y;\r\n");
	strcat(CodigoC,"    float y1=0;\r\n");
	strcat(CodigoC,"    float y2=0;\r\n");
	strcat(CodigoC,"    float ymax;\r\n");
	strcat(CodigoC,"    int j;\r\n");
	strcat(CodigoC,"    ymax=VariablesSalida[NumeroSalida].minimo;\r\n");
	strcat(CodigoC,"    actualizarEntradas(ent);\r\n");
	strcat(CodigoC,"    for(j=0;j<NUMEROREGLAS;j++)\r\n");
	strcat(CodigoC,"    {\r\n");
	strcat(CodigoC,"        if(activarRegla(j))\r\n");
	strcat(CodigoC,"        {\r\n");
	strcat(CodigoC,"            float temp;\r\n");
	strcat(CodigoC,"            y=CentrosAltura[j][NumeroSalida];\r\n");
	strcat(CodigoC,"            temp=pertenenciaComposicion(NumeroSalida,j,y);\r\n");
	strcat(CodigoC,"            y1=y1+y*temp;\r\n");
	strcat(CodigoC,"            y2=y2+temp;\r\n");
	strcat(CodigoC,"        }\r\n");
	strcat(CodigoC,"    }\r\n");
	strcat(CodigoC,"    if(fabs(y2)<0.000001)\r\n");
	strcat(CodigoC,"        y2=100000.0;\r\n");
	strcat(CodigoC,"    if(fabs(y1)<0.000001)\r\n");
	strcat(CodigoC,"        y1=0.0;\r\n");
	strcat(CodigoC,"    ymax=y1/y2;\r\n");
	strcat(CodigoC,"    return ymax;\r\n");
	strcat(CodigoC,"}\r\n");
	return CodigoC;
}

string Altura::codigoCPP()
{
	char* CodigoCPP;
	CodigoCPP=new char [1000];
	strcpy(CodigoCPP,"");
	sprintf(CodigoCPP,"    conc=new Altura(motor,%d,Conjuncion);",NumeroVariable);
	return CodigoCPP;
}


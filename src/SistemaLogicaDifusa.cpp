#include "SistemaLogicaDifusa.h"

void SistemaLogicaDifusa::crearMinimoSLD(int numEnt,int numSal)
{
	nombre=_("Sin nombre");
	descripcion="";

	if(entradas){delete entradas;}
	if(salidas){delete salidas;}
	if(motor){delete motor;}
	if(concreto){delete concreto;}

  entradas=new Universo();
  for(int i=0;i<numEnt;i++)
	{
	  Variable *V;
	  V=new Variable();
	  char str[40];sprintf(str,"Entrada %d",i+1);
	  V->nombreVariable(str);
	  V->rangoMinimo(-1.0);
	  V->rangoMaximo(1.0);
	  V->autodefinirConjuntosRectosCortos(3);
	  entradas->adicionarVariable(V);
	}

  salidas=new Universo();
  for(int i=0;i<numSal;i++)
	{
	  Variable *V;
	  V=new Variable();
	  char str[40];sprintf(str,"Salida %d",i+1);
	  V->nombreVariable(str);
	  V->rangoMinimo(-1.0);
	  V->rangoMaximo(1.0);
	  V->autodefinirConjuntosRectosCortos(3);
	  salidas->adicionarVariable(V);
	}

  motor=new MaquinaInferencia(entradas,salidas,9);
  motor->llenarEntradasBase();
  motor->llenarSalidasBaseCreciente();

  Norma       *Conjuncion  = new Maximo();
  concreto=new BloqueConcrecion(motor);
  concreto->autodefinirBloqueConcrecion(motor,Conjuncion);

  float *entra=new float[numeroEntradas()];
  float *sale =new float[numeroSalidas()];
  for(int i=0;i<numeroEntradas();i++)
	{
		entra[i]=0.5*(entradas->variable(i)->rangoMinimo() + entradas->variable(i)->rangoMaximo());
	}
  calcular(entra,sale);
}

void SistemaLogicaDifusa::crearArchivoTabla(wxString nombreArchivo)
{
	wxTextFile tablaFile(nombreArchivo);
	tablaFile.Clear();
	wxString linea="";

/////////////////////////

	int numLineas=0;
	int numEntradas;
	int numSalidas;
	int *contadorIntervalos;
	int *numIntervalos;
	float *minimoEntradas;
	float *intervalosEntradas;
	float *entra;
	float *sale;
	numEntradas=concreto->motor()->entradas()->numeroVariables();
	numSalidas =concreto->motor()->salidas()->numeroVariables();
	contadorIntervalos=new int[numEntradas];
	numIntervalos=new int[numEntradas];
	minimoEntradas=new float[numEntradas];
	intervalosEntradas=new float[numEntradas];
	entra=new float[numEntradas];
	sale =new float[numSalidas];

	int i;

	for(i=0;i<numEntradas;i++)
	{
		linea << nombreVariableEntrada(i) << _("\t");
	}
	for(i=0;i<numSalidas;i++)
	{
		linea << nombreVariableSalida(i) << _("\t");
	}
	tablaFile.AddLine(linea);

	long maxLineas=1;
	for(i=0;i<numEntradas;i++)
	{
		contadorIntervalos[i]=0;
		numIntervalos[i]=concreto->motor()->entradas()->numeroIntervalosEnVariable(i);
		minimoEntradas[i]=concreto->motor()->entradas()->rangoMinimoVariable(i);
		intervalosEntradas[i]=concreto->motor()->entradas()->intervaloEnVariable(i);
		maxLineas=maxLineas*(numIntervalos[i]+1);
	}
	maxLineas++;
	int bandera=1;
	int aviso=0;
	int conteoLineas=1;
	wxString mensaje=_("Lineas");
	wxProgressDialog progreso(_("Avance"), mensaje , maxLineas);
	while(bandera!=0)
	{
		conteoLineas++;
		mensaje =_("Lineas: ");
		mensaje << conteoLineas << _("/") << maxLineas;
		progreso.Update(conteoLineas,mensaje);
		for(i=numEntradas-1;i>=0;i--)
		{
			entra[i]=minimoEntradas[i]+intervalosEntradas[i]*contadorIntervalos[i];
			if(i==numEntradas-1)
			{
				contadorIntervalos[i]=contadorIntervalos[i]+1;
				if(contadorIntervalos[i]>numIntervalos[i])
				{
					contadorIntervalos[i]=0;
					aviso=1;
				}
			}else
			{
				if(aviso==1)
				{
					aviso=0;
					contadorIntervalos[i]=contadorIntervalos[i]+1;
					if(contadorIntervalos[i]>numIntervalos[i])
					{
						contadorIntervalos[i]=0;
						aviso=1;
					}
				}
			}
		}
		concreto->salidaConcreta(entra,sale);
		linea ="";
		for(i=0;i<numEntradas;i++)
		{
			linea << entra[i] << _("\t");
		}
		for(i=0;i<numSalidas;i++)
		{
			linea << sale[i] << _("\t");
		}
		tablaFile.AddLine(linea);

		numLineas=numLineas+1;

		bandera=0;

		for(i=0;i<numEntradas;i++)
		{
			if(contadorIntervalos[i]==0)
			{
				bandera=bandera+0;
			}else
			{
					bandera=bandera+1;
			}
		}
	}


/////////////////////////

	if(tablaFile.Write())
	{
		wxMessageBox(_("Se ha creado el archivo"),_("Información"));
	}else
	{
		wxMessageBox(_("No se pudo abrir el archivo"),_("¡Atención!"));
	}

}

void SistemaLogicaDifusa::generarCodigo(wxString nombreArchivo,wxString nombreClase)
{
	wxFileName fn(nombreArchivo);
	wxString ext=fn.GetExt().Lower();
	if(ext=="cpp")
	{
		wxString verificar="";
		verificar << fn.GetName() << "." << fn.GetExt();
		if(verificar == "fuzzy.cpp")
		{
			if(wxMessageBox(_("El archivo fuzzy.cpp es necesario para compilar ¿desea sobreescribirlo?"),_("Atención"),wxOK|wxCANCEL|wxCANCEL_DEFAULT)==wxID_OK)
			{
				generarCodigoCPP(nombreArchivo,nombreClase);
			}
		}else
		{
			generarCodigoCPP(nombreArchivo,nombreClase);
		}
	}else if(ext=="c")
	{
		generarCodigoC(nombreArchivo);
	}
}

void SistemaLogicaDifusa::generarCodigoCPP(wxString nombreArchivo,wxString nombreClase)
{
	wxTextFile codigoFile(nombreArchivo);
	codigoFile.Clear();

	generarCodigoCPPEncabezado(&codigoFile);
	generarCodigoCPPClase(&codigoFile, nombreClase);
	generarCodigoCPPMain(&codigoFile, nombreClase);

	if(codigoFile.Write())
	{
		wxMessageBox(_("Se ha creado el archivo"),_("Información"));
	}else
	{
		wxMessageBox(_("No se pudo abrir el archivo"),_("¡Atención!"));
	}
}

void SistemaLogicaDifusa::generarCodigoCPPEncabezado(wxTextFile* codigoFile)
{
	wxString Codigo="";
	char cad[2000];

	Codigo=_("// Código C++ del Sistema de Lógica Difusa\n");codigoFile->AddLine(Codigo);
	Codigo=_("// Generado automáticamente por UNFUZZY V 3.0");codigoFile->AddLine(Codigo);
	Codigo=_("// Autor: Oscar Duarte (ogduartev@unal.edu.co)");codigoFile->AddLine(Codigo);
	Codigo=_("// Universidad Nacional de Colombia");codigoFile->AddLine(Codigo);
	Codigo=_("// Descargo de responsabilidad: ");codigoFile->AddLine(Codigo);
	Codigo=_("// El código generado se usa bajo responsabilidad del usuario.");codigoFile->AddLine(Codigo);
	Codigo=_("// En ninguna forma genera responsabilidad para el autor de UNFUZZY");codigoFile->AddLine(Codigo);
	Codigo=_("// ni para la Universidad Nacional de Colombia.");codigoFile->AddLine(Codigo);
	Codigo=_("// ");codigoFile->AddLine(Codigo);
	Codigo=_("// para compilar el archivo xxx.cpp:");codigoFile->AddLine(Codigo);
	Codigo=_("//   g++ xxx.cpp fuzzy.cpp");codigoFile->AddLine(Codigo);
	Codigo=("");codigoFile->AddLine(Codigo);
	Codigo=("#ifndef __IOSTREAM_H");codigoFile->AddLine(Codigo);
	Codigo=("#include <iostream>");codigoFile->AddLine(Codigo);
	Codigo=("#endif");codigoFile->AddLine(Codigo);
	Codigo=("");codigoFile->AddLine(Codigo);
	Codigo=("using namespace std;");codigoFile->AddLine(Codigo);
	Codigo=("	");codigoFile->AddLine(Codigo);
	Codigo=("#ifndef __FUZZY_H");codigoFile->AddLine(Codigo);
	Codigo=("#include \"fuzzy.h\"");codigoFile->AddLine(Codigo);
	Codigo=("#endif\r\n");codigoFile->AddLine(Codigo);
}

void SistemaLogicaDifusa::generarCodigoCPPClase(wxTextFile* codigoFile,wxString nombreClase)
{
	wxString Codigo=("");
	char cad[2000];

	Codigo=("class ");
	Codigo << nombreClase << (":public SistemaLogicaDifusa");codigoFile->AddLine(Codigo);
	Codigo=("{");codigoFile->AddLine(Codigo);
	Codigo=("public:");codigoFile->AddLine(Codigo);
	Codigo=("    ");
	Codigo << nombreClase << ("();");codigoFile->AddLine(Codigo);
	Codigo=("    ~");
	Codigo << nombreClase << ("();");codigoFile->AddLine(Codigo);
	Codigo=("protected:");codigoFile->AddLine(Codigo);
	Codigo=("};\r\n");codigoFile->AddLine(Codigo);
	Codigo=nombreClase;
	Codigo << ("::") << nombreClase << ("()");codigoFile->AddLine(Codigo);
	Codigo=("{");codigoFile->AddLine(Codigo);
	Codigo=("    ConjuntoDifuso *cd;");codigoFile->AddLine(Codigo);
	Codigo=("    Difusor *dif;");codigoFile->AddLine(Codigo);
	Codigo=("    Variable *var;");codigoFile->AddLine(Codigo);
	Codigo=("    Norma *And;");codigoFile->AddLine(Codigo);
	Codigo=("    Norma *Composicion;");codigoFile->AddLine(Codigo);
	Codigo=("    Norma *Conjuncion;");codigoFile->AddLine(Codigo);
	Codigo=("    Implicacion *Implica;");codigoFile->AddLine(Codigo);
	Codigo=("    Concresor *conc;\r\n");codigoFile->AddLine(Codigo);
	Codigo=("    entradas=new Universo(");
	Codigo << concreto->motor()->entradas()->numeroVariables() << (");");codigoFile->AddLine(Codigo);
	Codigo=("    salidas=new Universo(");
	Codigo << concreto->motor()->salidas()->numeroVariables() << (");");codigoFile->AddLine(Codigo);
	int i;
	for(i=0;i<concreto->motor()->entradas()->numeroVariables();i++)
	{
		Codigo =("    var=new Variable(");
		Codigo << concreto->motor()->entradas()->numeroConjuntosEnVariable(i) << (");");codigoFile->AddLine(Codigo);
		Codigo=("    var->rangoMinimo(");
								Codigo << concreto->motor()->entradas()->rangoMinimoVariable(i) << (");");codigoFile->AddLine(Codigo);
		Codigo=("    var->rangoMaximo(");
		Codigo << concreto->motor()->entradas()->rangoMaximoVariable(i) << (");");codigoFile->AddLine(Codigo);
		int j;
		for(j=0;j<concreto->motor()->entradas()->numeroConjuntosEnVariable(i);j++)
		{
			strcpy(cad,concreto->motor()->entradas()->conjuntoEnVariable(i,j)->codigoCPP());
			Codigo=cad;codigoFile->AddLine(Codigo);
			Codigo=("    var->adicionarConjuntos(cd);");codigoFile->AddLine(Codigo);
		}
		strcpy(cad,concreto->motor()->entradas()->difusor(i)->codigo_CPP());
		Codigo=cad;codigoFile->AddLine(Codigo);
		Codigo=("    dif->numeroPuntos(");
		Codigo << concreto->motor()->entradas()->numeroPuntosDifusor(i) << (");");codigoFile->AddLine(Codigo);
		Codigo=("    var->difusorEntrada(dif);");codigoFile->AddLine(Codigo);
		Codigo=("    var->nombreVariable(\"");
		Codigo << concreto->motor()->entradas()->nombreVariable(i) <<("\");");codigoFile->AddLine(Codigo);
		Codigo =("    var->numeroIntervalos(");
		Codigo << concreto->motor()->entradas()->numeroIntervalosEnVariable(i) << (");");codigoFile->AddLine(Codigo);
		Codigo=("    entradas->adicionarVariable(var);");codigoFile->AddLine(Codigo);
	}
	//////////////////////////////////////
	for(i=0;i<concreto->motor()->salidas()->numeroVariables();i++)
	{
		sprintf(cad,"    var=new Variable(%d);",concreto->motor()->salidas()->numeroConjuntosEnVariable(i));
		Codigo=cad;codigoFile->AddLine(Codigo);
		sprintf(cad,"    var->rangoMinimo(%f);",concreto->motor()->salidas()->rangoMinimoVariable(i));
		Codigo=cad;codigoFile->AddLine(Codigo);
		sprintf(cad,"    var->rangoMaximo(%f);",concreto->motor()->salidas()->rangoMaximoVariable(i));
		Codigo=cad;codigoFile->AddLine(Codigo);
		int j;
		for(j=0;j<concreto->motor()->salidas()->numeroConjuntosEnVariable(i);j++)
		{
			strcpy(cad,concreto->motor()->salidas()->conjuntoEnVariable(i,j)->codigoCPP());
			Codigo=cad;codigoFile->AddLine(Codigo);
			Codigo=("    var->adicionarConjuntos(cd);");codigoFile->AddLine(Codigo);
		}
		Codigo=("    var->nombreVariable(\"");
		Codigo << concreto->motor()->salidas()->nombreVariable(i) <<("\");");codigoFile->AddLine(Codigo);
		sprintf(cad,"    var->numeroIntervalos(%d);",concreto->motor()->salidas()->numeroIntervalosEnVariable(i));
		Codigo=cad;codigoFile->AddLine(Codigo);
		Codigo=("    salidas->adicionarVariable(var);");codigoFile->AddLine(Codigo);
	}

	sprintf(cad,"    motor=new MaquinaInferencia(entradas,salidas,%d);",concreto->motor()->numeroReglas());
	Codigo=cad;codigoFile->AddLine(Codigo);
	Codigo=("    And=new ");
	strcpy(cad,concreto->motor()->and_()->codigoCPP());
	Codigo << cad;codigoFile->AddLine(Codigo);
	Codigo=("    Composicion=new ");
	strcpy(cad,concreto->motor()->composicion()->codigoCPP());
	Codigo << cad;codigoFile->AddLine(Codigo);
//////////////
	Codigo=("    Implica=new ");
	strcpy(cad,concreto->motor()->implicacion()->codigoCPP());
	Codigo << cad;codigoFile->AddLine(Codigo);
	Codigo=("    motor->and_(And);");codigoFile->AddLine(Codigo);
	Codigo=("    motor->composicion(Composicion);");codigoFile->AddLine(Codigo);
	Codigo=("    motor->implicacion(Implica);");codigoFile->AddLine(Codigo);
	for(i=0;i<concreto->motor()->numeroReglas();i++)
	{
		int j;
		for(j=0;j<concreto->motor()->entradas()->numeroVariables();j++)
		{
			sprintf(cad,"    motor->conjuntoEntrada(%d,%d,%d);",i,j,concreto->motor()->numConjuntoEntrada(i,j));
			Codigo=cad;codigoFile->AddLine(Codigo);
		}
		for(j=0;j<concreto->motor()->salidas()->numeroVariables();j++)
		{
			sprintf(cad,"    motor->conjuntoSalida(%d,%d,%d);",i,j,concreto->motor()->numConjuntoSalida(i,j));
			Codigo=cad;codigoFile->AddLine(Codigo);
		}
	}
	for(i=0;i<concreto->motor()->numeroReglas();i++)
	{
		int j;
		for(j=0;j<concreto->motor()->entradas()->numeroVariables();j++)
		{
			sprintf(cad,"    motor->modificador(%d,%d,%f);",i,j,concreto->motor()->modificador(i,j));
			Codigo=cad;codigoFile->AddLine(Codigo);
		}
	}
	Codigo=("    concreto=new BloqueConcrecion(motor);");codigoFile->AddLine(Codigo);
	Codigo=("    Conjuncion=new ");
	strcpy(cad,concreto->conjuncion()->codigoCPP());
	Codigo << cad;codigoFile->AddLine(Codigo);
	for(i=0;i<concreto->motor()->salidas()->numeroVariables();i++)
	{
		strcpy(cad,concreto->concresor(i)->codigoCPP());
		Codigo=cad;codigoFile->AddLine(Codigo);
		Codigo=("    concreto->adicionarConcresor(conc);");codigoFile->AddLine(Codigo);
	}
	Codigo=("    concreto->motor(motor);");codigoFile->AddLine(Codigo);
	Codigo=("    concreto->conjuncion(Conjuncion);");codigoFile->AddLine(Codigo);
	Codigo=("}\r\n");codigoFile->AddLine(Codigo);
	Codigo=nombreClase;
	Codigo << ("::~") << nombreClase << ("()");codigoFile->AddLine(Codigo);
	Codigo=("{");codigoFile->AddLine(Codigo);
	Codigo=("}\r\n");codigoFile->AddLine(Codigo);
}

void SistemaLogicaDifusa::generarCodigoCPPMain(wxTextFile* codigoFile,wxString nombreClase)
{
	wxString Codigo=("");
	char cad[2000];

	Codigo=("int main()");codigoFile->AddLine(Codigo);
	Codigo=("{");codigoFile->AddLine(Codigo);
	Codigo=("    float *entra;");codigoFile->AddLine(Codigo);
	Codigo=("    float *sale;");codigoFile->AddLine(Codigo);
	Codigo=("    ");
	Codigo << nombreClase << (" *sistema;");codigoFile->AddLine(Codigo);
	Codigo=("    int NumeroEntradas;");codigoFile->AddLine(Codigo);
	Codigo=("    int NumeroSalidas;");codigoFile->AddLine(Codigo);
	Codigo=("    sistema=new ");
	Codigo << nombreClase << ("();");codigoFile->AddLine(Codigo);
	Codigo=("    NumeroEntradas=sistema->numeroEntradas();");codigoFile->AddLine(Codigo);
	Codigo=("    NumeroSalidas=sistema->numeroSalidas();");codigoFile->AddLine(Codigo);
	Codigo=("    entra=new float[NumeroEntradas];");codigoFile->AddLine(Codigo);
	Codigo=("    sale=new float[NumeroSalidas];");codigoFile->AddLine(Codigo);
	Codigo=("    int i;");codigoFile->AddLine(Codigo);
	Codigo=("    char q='s';");codigoFile->AddLine(Codigo);
	Codigo=("    while(q=='s')");codigoFile->AddLine(Codigo);
	Codigo=("    {");codigoFile->AddLine(Codigo);
	Codigo=("        for(i=0;i<NumeroEntradas;i++)");codigoFile->AddLine(Codigo);
	Codigo=("        {");codigoFile->AddLine(Codigo);
	Codigo=("            cout << sistema->nombreVariableEntrada(i) << \" : \";");codigoFile->AddLine(Codigo);
	Codigo=("            cin >> entra[i];");codigoFile->AddLine(Codigo);
	Codigo=("        }");codigoFile->AddLine(Codigo);
	Codigo=("        sistema->calcular(entra,sale);");codigoFile->AddLine(Codigo);
	Codigo=("        for(i=0;i<NumeroSalidas;i++)");codigoFile->AddLine(Codigo);
	Codigo=("        {");codigoFile->AddLine(Codigo);
	Codigo=("            cout << sistema->nombreVariableSalida(i) << \" : \";");codigoFile->AddLine(Codigo);
	Codigo=("            cout << sale[i] << \"\\n\";");codigoFile->AddLine(Codigo);
	Codigo=("        }");codigoFile->AddLine(Codigo);
	Codigo=("        cout << \"");
	Codigo+=_("Desea otro cálculo ?(s/n)");
	Codigo+=("\";");codigoFile->AddLine(Codigo);
	Codigo=("        cin >> q;");codigoFile->AddLine(Codigo);
	Codigo=("    }");codigoFile->AddLine(Codigo);
	Codigo=("    delete[] entra;");codigoFile->AddLine(Codigo);
	Codigo=("    delete[] sale;");codigoFile->AddLine(Codigo);
	Codigo=("    return 0;");codigoFile->AddLine(Codigo);
	Codigo=("}\r\n");codigoFile->AddLine(Codigo);
}

void SistemaLogicaDifusa::generarCodigoC(wxString nombreArchivo)
{
	wxTextFile codigoFile(nombreArchivo);
	codigoFile.Clear();

	wxString Codigo=("");
	char cad[2000];

	Codigo=("// Código C del Sistema de Lógica Difusa\n");codigoFile.AddLine(Codigo);
	Codigo=("// Generado automáticamente por UNFUZZY V 3.0");codigoFile.AddLine(Codigo);
	Codigo=("// Autor: Oscar Duarte (ogduartev@unal.edu.co)");codigoFile.AddLine(Codigo);
	Codigo=("// Universidad Nacional de Colombia");codigoFile.AddLine(Codigo);
	Codigo=("// Descargo de responsabilidad: ");codigoFile.AddLine(Codigo);
	Codigo=("// El código generado se usa bajo responsabilidad del usuario.");codigoFile.AddLine(Codigo);
	Codigo=("// En ninguna forma genera responsabilidad para el autor de UNFUZZY");codigoFile.AddLine(Codigo);
	Codigo=("// ni para la Universidad Nacional de Colombia.");codigoFile.AddLine(Codigo);
	Codigo=("// ");codigoFile.AddLine(Codigo);
	Codigo=("// para compilar el archivo xxx.c:");codigoFile.AddLine(Codigo);
	Codigo=("//   g++ xxx.c");codigoFile.AddLine(Codigo);
	Codigo=("");codigoFile.AddLine(Codigo);
	Codigo="#include <stdio.h>";codigoFile.AddLine(Codigo);
	Codigo="#include <string.h>";codigoFile.AddLine(Codigo);
	Codigo="#include <math.h>\r\n";codigoFile.AddLine(Codigo);
	sprintf(cad,"#define NUMEROREGLAS                 %d",concreto->motor()->numeroReglas());
	Codigo=cad;codigoFile.AddLine(Codigo);
	sprintf(cad,"#define NUMEROVARIABLESENTRADA       %d",concreto->motor()->entradas()->numeroVariables());
	Codigo=cad;codigoFile.AddLine(Codigo);
	sprintf(cad,"#define NUMEROVARIABLESSALIDA        %d",concreto->motor()->salidas()->numeroVariables());
	Codigo=cad;codigoFile.AddLine(Codigo);
	int numConjTotales=0;
	int i;
	for(i=0;i<concreto->motor()->entradas()->numeroVariables();i++)
	{
		numConjTotales=numConjTotales+concreto->motor()->entradas()->numeroConjuntosEnVariable(i);
	}
	sprintf(cad,"#define NUMEROTOTALCONJUNTOSENTRADA  %d\r\n",numConjTotales);
	Codigo=cad;codigoFile.AddLine(Codigo);
	Codigo="struct conjunto{";codigoFile.AddLine(Codigo);
	Codigo="	char nombre[40];";codigoFile.AddLine(Codigo);
	Codigo="	float minimo;";codigoFile.AddLine(Codigo);
	Codigo="	float maximo;";codigoFile.AddLine(Codigo);
	Codigo="};\r\n";codigoFile.AddLine(Codigo);
	Codigo="struct variable{";codigoFile.AddLine(Codigo);
	Codigo="	char nombre[40];";codigoFile.AddLine(Codigo);
	Codigo="	float minimo;";codigoFile.AddLine(Codigo);
	Codigo="	float maximo;";codigoFile.AddLine(Codigo);
	Codigo="	int intervalos;";codigoFile.AddLine(Codigo);
	Codigo="	float intervalo;";codigoFile.AddLine(Codigo);
	Codigo="	int numeroConjuntos;";codigoFile.AddLine(Codigo);
	Codigo="};\r\n";codigoFile.AddLine(Codigo);
	Codigo="struct difusor{";codigoFile.AddLine(Codigo);
	Codigo="	float minimo;";codigoFile.AddLine(Codigo);
	Codigo="	float maximo;";codigoFile.AddLine(Codigo);
	Codigo="	float centro;";codigoFile.AddLine(Codigo);
	Codigo="	float var1;";codigoFile.AddLine(Codigo);
	Codigo="	float var2;";codigoFile.AddLine(Codigo);
	Codigo="	float var3;";codigoFile.AddLine(Codigo);
	Codigo="	float var4;";codigoFile.AddLine(Codigo);
	Codigo="	int puntos;";codigoFile.AddLine(Codigo);
	Codigo="	float intervalo;";codigoFile.AddLine(Codigo);
	Codigo="};\r\n";codigoFile.AddLine(Codigo);
	Codigo="struct variable VariablesEntrada[NUMEROVARIABLESENTRADA];";codigoFile.AddLine(Codigo);
	Codigo="struct variable VariablesSalida[NUMEROVARIABLESSALIDA];";codigoFile.AddLine(Codigo);
	Codigo="struct conjunto Entradas[NUMEROTOTALCONJUNTOSENTRADA];";codigoFile.AddLine(Codigo);
	Codigo="struct difusor Difusores[NUMEROTOTALCONJUNTOSENTRADA];";codigoFile.AddLine(Codigo);
	Codigo="int Reglas[NUMEROREGLAS][NUMEROVARIABLESENTRADA+NUMEROVARIABLESSALIDA];";codigoFile.AddLine(Codigo);
	Codigo="float Modificadores[NUMEROREGLAS][NUMEROVARIABLESENTRADA];";codigoFile.AddLine(Codigo);
	Codigo="float CentrosAltura[NUMEROREGLAS][NUMEROVARIABLESSALIDA];";codigoFile.AddLine(Codigo);
	Codigo="void llenarDatos();";codigoFile.AddLine(Codigo);
	Codigo="void llenarVariablesEntrada();";codigoFile.AddLine(Codigo);
	Codigo="void llenarVariablesSalida();";codigoFile.AddLine(Codigo);
	Codigo="void llenarEntradas();";codigoFile.AddLine(Codigo);
	Codigo="void llenarDifusores();";codigoFile.AddLine(Codigo);
	Codigo="void llenarReglas();";codigoFile.AddLine(Codigo);
	Codigo="void llenarModificadores();";codigoFile.AddLine(Codigo);
	Codigo="void llenarCentrosAltura();";codigoFile.AddLine(Codigo);
	Codigo="void calcular(float *ent,float *sal);";codigoFile.AddLine(Codigo);
	Codigo="float salidaConcreta(int NumeroSalida, float *entra);";codigoFile.AddLine(Codigo);
	for(i=0;i<concreto->motor()->salidas()->numeroVariables();i++)
	{
		sprintf(cad,"float salidaConcreta%d(float *entra);",i);
		Codigo=cad;codigoFile.AddLine(Codigo);
	}
	Codigo="";codigoFile.AddLine(Codigo);
	Codigo="float pertenenciaComposicion(int numVar, int numRegla, float sal);";codigoFile.AddLine(Codigo);
	Codigo="float pertenenciaDifusores(float *ent);";codigoFile.AddLine(Codigo);
	Codigo="float pertenenciaImplicacion(int numSal, int numRegla,float *ent, float sal);";codigoFile.AddLine(Codigo);
	Codigo="float pertenenciaConsecuente(int numSal, int numRegla, float sal);";codigoFile.AddLine(Codigo);
	Codigo="float pertenenciaAntecedente(int numRegla, float *ent);";codigoFile.AddLine(Codigo);
	Codigo="int activarRegla(int numRegla);";codigoFile.AddLine(Codigo);
	Codigo="float pertenenciaDifusor(int numVar, float x);";codigoFile.AddLine(Codigo);
	Codigo="float pertenenciaVariableEntrada(int numVar,int numConj, float x);";codigoFile.AddLine(Codigo);
	Codigo="float pertenenciaVariableSalida(int numVar,int numConj, float x);\r\n";codigoFile.AddLine(Codigo);
	Codigo="int indiceEntradas(int numRegla,int numVar);";codigoFile.AddLine(Codigo);
	Codigo="void actualizarEntradas(float *ent);";codigoFile.AddLine(Codigo);
	Codigo="float Implicacion(float x,float y);";codigoFile.AddLine(Codigo);
	Codigo="float Composicion(float x,float y);";codigoFile.AddLine(Codigo);
	Codigo="float Conjuncion(float x,float y);";codigoFile.AddLine(Codigo);
	Codigo="float And(float x,float y);";codigoFile.AddLine(Codigo);
	Codigo="";codigoFile.AddLine(Codigo);
	Codigo="int main()";codigoFile.AddLine(Codigo);
	Codigo="{";codigoFile.AddLine(Codigo);
	Codigo="    float entra[NUMEROVARIABLESENTRADA];";codigoFile.AddLine(Codigo);
	Codigo="    float sale[NUMEROVARIABLESSALIDA];";codigoFile.AddLine(Codigo);
	Codigo="    char q='s';";codigoFile.AddLine(Codigo);
	Codigo="    llenarDatos();";codigoFile.AddLine(Codigo);
	Codigo="    while(q=='s')";codigoFile.AddLine(Codigo);
	Codigo="    {";codigoFile.AddLine(Codigo);
	Codigo="        int i;";codigoFile.AddLine(Codigo);
	Codigo="        for(i=0;i<NUMEROVARIABLESENTRADA;i++)";codigoFile.AddLine(Codigo);
	Codigo="        {";codigoFile.AddLine(Codigo);
	Codigo="            float e;";codigoFile.AddLine(Codigo);
	Codigo="            printf(\"%s : \",VariablesEntrada[i].nombre);";codigoFile.AddLine(Codigo);
	Codigo="            scanf(\"%f\",&e);";codigoFile.AddLine(Codigo);
	Codigo="            entra[i]=e;";codigoFile.AddLine(Codigo);
	Codigo="        }";codigoFile.AddLine(Codigo);
	Codigo="        calcular(entra,sale);";codigoFile.AddLine(Codigo);
	Codigo="        for(i=0;i<NUMEROVARIABLESSALIDA;i++)";codigoFile.AddLine(Codigo);
	Codigo="        {";codigoFile.AddLine(Codigo);
	Codigo="            printf(\"%s : \",VariablesSalida[i].nombre);";codigoFile.AddLine(Codigo);
	Codigo="            printf(\"%f : \\n\",sale[i]);";codigoFile.AddLine(Codigo);
	Codigo="        }";codigoFile.AddLine(Codigo);
	Codigo="        printf(\"";
	Codigo+=_("Desea otro cálculo ?(s/n)");
	Codigo+="\\n\");";codigoFile.AddLine(Codigo);
	Codigo="        fflush(stdin);";codigoFile.AddLine(Codigo);
	Codigo="        scanf(\" %c\",&q);";codigoFile.AddLine(Codigo);
	Codigo="    }";codigoFile.AddLine(Codigo);
	Codigo="}";codigoFile.AddLine(Codigo);
	Codigo="void llenarDatos()";codigoFile.AddLine(Codigo);
	Codigo="{";codigoFile.AddLine(Codigo);
	Codigo="    llenarVariablesEntrada();";codigoFile.AddLine(Codigo);
	Codigo="    llenarVariablesSalida();";codigoFile.AddLine(Codigo);
	Codigo="    llenarEntradas();";codigoFile.AddLine(Codigo);
	Codigo="    llenarDifusores();";codigoFile.AddLine(Codigo);
	Codigo="    llenarReglas();";codigoFile.AddLine(Codigo);
	Codigo="    llenarModificadores();";codigoFile.AddLine(Codigo);
	Codigo="    llenarCentrosAltura();";codigoFile.AddLine(Codigo);
	Codigo="}";codigoFile.AddLine(Codigo);
	Codigo="void calcular(float *entra, float *sale)";codigoFile.AddLine(Codigo);
	Codigo="{";codigoFile.AddLine(Codigo);
	Codigo="    int i;";codigoFile.AddLine(Codigo);
	Codigo="    for(i=0;i<NUMEROVARIABLESSALIDA;i++)";codigoFile.AddLine(Codigo);
	Codigo="    {";codigoFile.AddLine(Codigo);
	Codigo="        sale[i]=salidaConcreta(i,entra);";codigoFile.AddLine(Codigo);
	Codigo="    }";codigoFile.AddLine(Codigo);
	Codigo="}";codigoFile.AddLine(Codigo);
	Codigo="void actualizarEntradas(float *ent)";codigoFile.AddLine(Codigo);
	Codigo="{";codigoFile.AddLine(Codigo);
	Codigo="    float dx;";codigoFile.AddLine(Codigo);
	Codigo="    int i;";codigoFile.AddLine(Codigo);
	Codigo="    for(i=0;i<NUMEROVARIABLESENTRADA;i++)";codigoFile.AddLine(Codigo);
	Codigo="    {";codigoFile.AddLine(Codigo);
	Codigo="        dx=ent[i]-Difusores[i].centro;";codigoFile.AddLine(Codigo);
	Codigo="        Difusores[i].centro=Difusores[i].centro+dx;";codigoFile.AddLine(Codigo);
	Codigo="        Difusores[i].minimo=Difusores[i].minimo+dx;";codigoFile.AddLine(Codigo);
	Codigo="        Difusores[i].maximo=Difusores[i].maximo+dx;";codigoFile.AddLine(Codigo);
	Codigo="        Difusores[i].var1=Difusores[i].var1+dx;";codigoFile.AddLine(Codigo);
	Codigo="        Difusores[i].var2=Difusores[i].var2+dx;";codigoFile.AddLine(Codigo);
	Codigo="        Difusores[i].var3=Difusores[i].var3+dx;";codigoFile.AddLine(Codigo);
	Codigo="        Difusores[i].var4=Difusores[i].var4+dx;";codigoFile.AddLine(Codigo);
	Codigo="    }";codigoFile.AddLine(Codigo);
	Codigo="}";codigoFile.AddLine(Codigo);
	Codigo="int indiceEntradas(int numVar,int numConj)";codigoFile.AddLine(Codigo);
	Codigo="{";codigoFile.AddLine(Codigo);
	Codigo="    int contador=0;";codigoFile.AddLine(Codigo);
	Codigo="    int i;";codigoFile.AddLine(Codigo);
	Codigo="    for(i=0;i<numVar;i++)";codigoFile.AddLine(Codigo);
	Codigo="    {";codigoFile.AddLine(Codigo);
	Codigo="        contador=contador+VariablesEntrada[i].numeroConjuntos;";codigoFile.AddLine(Codigo);
	Codigo="    }";codigoFile.AddLine(Codigo);
	Codigo="    contador=contador+numConj;";codigoFile.AddLine(Codigo);
	Codigo="    return contador;";codigoFile.AddLine(Codigo);
	Codigo="}";codigoFile.AddLine(Codigo);
	Codigo="float pertenenciaComposicion(int numVar,int numRegla, float sal)";codigoFile.AddLine(Codigo);
	Codigo="{";codigoFile.AddLine(Codigo);
	Codigo="    float ux;";codigoFile.AddLine(Codigo);
	Codigo="    float uxa;";codigoFile.AddLine(Codigo);
	Codigo="    float uxab;";codigoFile.AddLine(Codigo);
	Codigo="    float comp=0;";codigoFile.AddLine(Codigo);
	Codigo="    float x[NUMEROVARIABLESENTRADA];";codigoFile.AddLine(Codigo);
	Codigo="    int inter[NUMEROVARIABLESENTRADA];";codigoFile.AddLine(Codigo);
	Codigo="    if(!activarRegla(numRegla))";codigoFile.AddLine(Codigo);
	Codigo="    {";codigoFile.AddLine(Codigo);
	Codigo="        comp=Implicacion(0,0);";codigoFile.AddLine(Codigo);
	Codigo="    }";codigoFile.AddLine(Codigo);
	Codigo="    else{";codigoFile.AddLine(Codigo);
	Codigo="        int casos=1;";codigoFile.AddLine(Codigo);
	Codigo="        int i;";codigoFile.AddLine(Codigo);
	Codigo="        for(i=0;i<NUMEROVARIABLESENTRADA;i++)";codigoFile.AddLine(Codigo);
	Codigo="        {";codigoFile.AddLine(Codigo);
	Codigo="            casos=casos*Difusores[i].puntos;";codigoFile.AddLine(Codigo);
	Codigo="            inter[i]=1;";codigoFile.AddLine(Codigo);
	Codigo="        }";codigoFile.AddLine(Codigo);
	Codigo="        for(i=0;i<NUMEROVARIABLESENTRADA;i++)";codigoFile.AddLine(Codigo);
	Codigo="        {";codigoFile.AddLine(Codigo);
	Codigo="            int k;";codigoFile.AddLine(Codigo);
	Codigo="            for(k=0;k<NUMEROVARIABLESENTRADA;k++)";codigoFile.AddLine(Codigo);
	Codigo="            {";codigoFile.AddLine(Codigo);
	Codigo="                x[k]=Difusores[k].minimo+Difusores[k].intervalo*inter[k];";codigoFile.AddLine(Codigo);
	Codigo="                inter[k]=inter[k]+1;";codigoFile.AddLine(Codigo);
	Codigo="                if(inter[k]>=Difusores[k].puntos)";codigoFile.AddLine(Codigo);
	Codigo="                {";codigoFile.AddLine(Codigo);
	Codigo="                    inter[k]=1;";codigoFile.AddLine(Codigo);
	Codigo="                }";codigoFile.AddLine(Codigo);
	Codigo="            }";codigoFile.AddLine(Codigo);
	Codigo="            uxab=pertenenciaImplicacion(numVar,numRegla,x,sal);";codigoFile.AddLine(Codigo);
	Codigo="            uxa=pertenenciaDifusores(x);";codigoFile.AddLine(Codigo);
	Codigo="            ux=Composicion(uxa,uxab);";codigoFile.AddLine(Codigo);
	Codigo="            if(ux>comp)";codigoFile.AddLine(Codigo);
	Codigo="            {";codigoFile.AddLine(Codigo);
	Codigo="                comp=ux;";codigoFile.AddLine(Codigo);
	Codigo="            }";codigoFile.AddLine(Codigo);
	Codigo="        }";codigoFile.AddLine(Codigo);
	Codigo="    }";codigoFile.AddLine(Codigo);
	Codigo="    return comp;";codigoFile.AddLine(Codigo);
	Codigo="}";codigoFile.AddLine(Codigo);
	Codigo="float pertenenciaDifusores(float *ent)";codigoFile.AddLine(Codigo);
	Codigo="{";codigoFile.AddLine(Codigo);
	Codigo="    float uxd;";codigoFile.AddLine(Codigo);
	Codigo="    int j=0;";codigoFile.AddLine(Codigo);
	Codigo="    uxd=pertenenciaDifusor(j,ent[j]);";codigoFile.AddLine(Codigo);
	Codigo="    for(j=0;j<NUMEROVARIABLESENTRADA;j++)";codigoFile.AddLine(Codigo);
	Codigo="    {";codigoFile.AddLine(Codigo);
	Codigo="    uxd=And(uxd,pertenenciaDifusor(j,ent[j]));";codigoFile.AddLine(Codigo);
	Codigo="    }";codigoFile.AddLine(Codigo);
	Codigo="    return uxd;";codigoFile.AddLine(Codigo);
	Codigo="}";codigoFile.AddLine(Codigo);
	Codigo="float pertenenciaImplicacion(int numSal,int numRegla,float *ent,float sal)";codigoFile.AddLine(Codigo);
	Codigo="{";codigoFile.AddLine(Codigo);
	Codigo="    float uxa,uxb;";codigoFile.AddLine(Codigo);
	Codigo="    uxa=pertenenciaAntecedente(numRegla,ent);";codigoFile.AddLine(Codigo);
	Codigo="    uxb=pertenenciaConsecuente(numSal,numRegla,sal);";codigoFile.AddLine(Codigo);
	Codigo="    return Implicacion(uxa,uxb);";codigoFile.AddLine(Codigo);
	Codigo="}";codigoFile.AddLine(Codigo);
	Codigo="float pertenenciaConsecuente(int numSal,int numRegla,float sal)";codigoFile.AddLine(Codigo);
	Codigo="{";codigoFile.AddLine(Codigo);
	Codigo="    float uxc;";codigoFile.AddLine(Codigo);
	Codigo="    int conj;";codigoFile.AddLine(Codigo);
	Codigo="    conj=Reglas[numRegla][NUMEROVARIABLESENTRADA+numSal];";codigoFile.AddLine(Codigo);
	Codigo="    uxc=pertenenciaVariableSalida(numSal,conj,sal);";codigoFile.AddLine(Codigo);
	Codigo="    return uxc;";codigoFile.AddLine(Codigo);
	Codigo="}";codigoFile.AddLine(Codigo);
	Codigo="float pertenenciaAntecedente(int numRegla,float *ent)";codigoFile.AddLine(Codigo);
	Codigo="{";codigoFile.AddLine(Codigo);
	Codigo="    float ux;";codigoFile.AddLine(Codigo);
	Codigo="    float uxa;";codigoFile.AddLine(Codigo);
	Codigo="    int conj;";codigoFile.AddLine(Codigo);
	Codigo="    int j=0;";codigoFile.AddLine(Codigo);
	Codigo="    conj=Reglas[numRegla][0];";codigoFile.AddLine(Codigo);
	Codigo="    ux=pertenenciaVariableEntrada(j,conj,ent[j]);";codigoFile.AddLine(Codigo);
	Codigo="    if(Modificadores[numRegla][0]>0.0)";codigoFile.AddLine(Codigo);
	Codigo="    {";codigoFile.AddLine(Codigo);
	Codigo="        uxa=pow(ux,Modificadores[numRegla][0]);";codigoFile.AddLine(Codigo);
	Codigo="    }else";codigoFile.AddLine(Codigo);
	Codigo="    {";codigoFile.AddLine(Codigo);
	Codigo="        uxa=1;";codigoFile.AddLine(Codigo);
	Codigo="    }";codigoFile.AddLine(Codigo);
	Codigo="    for(j=1;j<NUMEROVARIABLESENTRADA;j++)";codigoFile.AddLine(Codigo);
	Codigo="    {";codigoFile.AddLine(Codigo);
	Codigo="        conj=Reglas[numRegla][j];";codigoFile.AddLine(Codigo);
	Codigo="        ux=pertenenciaVariableEntrada(j,conj,ent[j]);";codigoFile.AddLine(Codigo);
	Codigo="        if(Modificadores[numRegla][j]>0.0)";codigoFile.AddLine(Codigo);
	Codigo="        {";codigoFile.AddLine(Codigo);
	Codigo="            ux=pow(ux,Modificadores[numRegla][j]);";codigoFile.AddLine(Codigo);
	Codigo="        }else";codigoFile.AddLine(Codigo);
	Codigo="        {";codigoFile.AddLine(Codigo);
	Codigo="            ux=1;";codigoFile.AddLine(Codigo);
	Codigo="        }";codigoFile.AddLine(Codigo);
	Codigo="        uxa=And(uxa,ux);";codigoFile.AddLine(Codigo);
	Codigo="    }";codigoFile.AddLine(Codigo);
	Codigo="    return uxa;";codigoFile.AddLine(Codigo);
	Codigo="}";codigoFile.AddLine(Codigo);
	Codigo="int activarRegla(int numRegla)";codigoFile.AddLine(Codigo);
	Codigo="{";codigoFile.AddLine(Codigo);
	Codigo="    int i;";codigoFile.AddLine(Codigo);
	Codigo="    for(i=0;i<NUMEROVARIABLESENTRADA;i++)";codigoFile.AddLine(Codigo);
	Codigo="    {";codigoFile.AddLine(Codigo);
	Codigo="        float bmn,bmx,cmn,cmx;";codigoFile.AddLine(Codigo);
	Codigo="        int numCon;";codigoFile.AddLine(Codigo);
	Codigo="        int indice;";codigoFile.AddLine(Codigo);
	Codigo="        numCon=Reglas[numRegla][i];";codigoFile.AddLine(Codigo);
	Codigo="        indice=indiceEntradas(i,numCon);";codigoFile.AddLine(Codigo);
	Codigo="        bmn=Entradas[indice].minimo;";codigoFile.AddLine(Codigo);
	Codigo="        bmx=Entradas[indice].maximo;";codigoFile.AddLine(Codigo);
	Codigo="        cmn=Difusores[i].minimo;";codigoFile.AddLine(Codigo);
	Codigo="        cmx=Difusores[i].maximo;";codigoFile.AddLine(Codigo);
	Codigo="        if(bmn>cmx||bmx<cmn)";codigoFile.AddLine(Codigo);
	Codigo="            return 0;";codigoFile.AddLine(Codigo);
	Codigo="    }";codigoFile.AddLine(Codigo);
	Codigo="    return 1;";codigoFile.AddLine(Codigo);
	Codigo="}";codigoFile.AddLine(Codigo);
	Codigo="float salidaConcreta(int NumeroSalida,float *ent)";codigoFile.AddLine(Codigo);
	Codigo="{";codigoFile.AddLine(Codigo);
	Codigo="    float respuesta;";codigoFile.AddLine(Codigo);
	Codigo="    switch(NumeroSalida)";codigoFile.AddLine(Codigo);
	Codigo="    {";codigoFile.AddLine(Codigo);
	for(i=0;i<concreto->motor()->salidas()->numeroVariables();i++)
	{
		sprintf(cad,"        case %u : respuesta=salidaConcreta%u(ent);break;",i,i);
		Codigo=cad;codigoFile.AddLine(Codigo);
	}
	Codigo="        default:respuesta=0;break;";codigoFile.AddLine(Codigo);
	Codigo="    }";codigoFile.AddLine(Codigo);
	Codigo="    return respuesta;";codigoFile.AddLine(Codigo);
	Codigo="}";codigoFile.AddLine(Codigo);

////////////////////////////////////////////////////
	int numEntradas;
	int numSalidas;
	int numReglas;
	numEntradas=concreto->motor()->entradas()->numeroVariables();
	numSalidas=concreto->motor()->salidas()->numeroVariables();
	numReglas=concreto->motor()->numeroReglas();
	for(i=0;i<numSalidas;i++)
	{
		strcpy(cad,concreto->concresor(i)->codigoC());
		Codigo=cad;codigoFile.AddLine(cad);
	}
	Codigo="void llenarVariablesEntrada()";codigoFile.AddLine(Codigo);
	Codigo="{";codigoFile.AddLine(Codigo);
	for(i=0;i<numEntradas;i++)
	{
		sprintf(cad,"    strcpy(VariablesEntrada[%d].nombre,\"%s\");",i,concreto->motor()->entradas()->nombreVariable(i));
		Codigo=cad;codigoFile.AddLine(cad);
		sprintf(cad,"    VariablesEntrada[%d].minimo=%f;",i,concreto->motor()->entradas()->rangoMinimoVariable(i));
		Codigo=cad;codigoFile.AddLine(cad);
		sprintf(cad,"    VariablesEntrada[%d].maximo=%f;",i,concreto->motor()->entradas()->rangoMaximoVariable(i));
		Codigo=cad;codigoFile.AddLine(cad);
		sprintf(cad,"    VariablesEntrada[%d].intervalos=%d;",i,concreto->motor()->entradas()->variable(i)->numeroIntervalos());
		Codigo=cad;codigoFile.AddLine(cad);
		sprintf(cad,"    VariablesEntrada[%d].intervalo=%f;",i,concreto->motor()->entradas()->variable(i)->intervalo());
		Codigo=cad;codigoFile.AddLine(cad);
		sprintf(cad,"    VariablesEntrada[%d].numeroConjuntos=%d;",i,concreto->motor()->entradas()->numeroConjuntosEnVariable(i));
		Codigo=cad;codigoFile.AddLine(cad);

	}
	Codigo="}\r\n";codigoFile.AddLine(Codigo);
	Codigo="void llenarVariablesSalida()";codigoFile.AddLine(Codigo);
	Codigo="{";codigoFile.AddLine(Codigo);
	for(i=0;i<numSalidas;i++)
	{
		sprintf(cad,"    strcpy(VariablesSalida[%d].nombre,\"%s\");",i,concreto->motor()->salidas()->nombreVariable(i));
		Codigo=cad;codigoFile.AddLine(cad);
		sprintf(cad,"    VariablesSalida[%d].minimo=%f;",i,concreto->motor()->salidas()->rangoMinimoVariable(i));
		Codigo=cad;codigoFile.AddLine(cad);
		sprintf(cad,"    VariablesSalida[%d].maximo=%f;",i,concreto->motor()->salidas()->rangoMaximoVariable(i));
		Codigo=cad;codigoFile.AddLine(cad);
		sprintf(cad,"    VariablesSalida[%d].intervalos=%d;",i,concreto->motor()->salidas()->variable(i)->numeroIntervalos());
		Codigo=cad;codigoFile.AddLine(cad);
		sprintf(cad,"    VariablesSalida[%d].intervalo=%f;",i,concreto->motor()->salidas()->variable(i)->intervalo());
		Codigo=cad;codigoFile.AddLine(cad);
		sprintf(cad,"    VariablesSalida[%d].numeroConjuntos=%d;",i,concreto->motor()->salidas()->numeroConjuntosEnVariable(i));
		Codigo=cad;codigoFile.AddLine(cad);

	}
	Codigo="}";codigoFile.AddLine(Codigo);
	Codigo="void llenarEntradas()";codigoFile.AddLine(Codigo);
	Codigo="{";codigoFile.AddLine(Codigo);
	int contador=0;
	for(i=0;i<numEntradas;i++)
	{
		int j,numConj;
		numConj=concreto->motor()->entradas()->numeroConjuntosEnVariable(i);
		for(j=0;j<numConj;j++)
		{
			sprintf(cad,"    Entradas[%d].minimo=%f;",contador,concreto->motor()->entradas()->minimoEnConjunto(i,j));
			Codigo=cad;codigoFile.AddLine(cad);
			sprintf(cad,"    Entradas[%d].maximo=%f;",contador,concreto->motor()->entradas()->maximoEnConjunto(i,j));
			Codigo=cad;codigoFile.AddLine(cad);
			contador=contador+1;
			 		}
	}
	Codigo="}";codigoFile.AddLine(Codigo);
 	Codigo="void llenarDifusores()";codigoFile.AddLine(Codigo);
	Codigo="{";codigoFile.AddLine(Codigo);
	for(i=0;i<numEntradas;i++)
	{
		sprintf(cad,"    Difusores[%d].minimo=%f;",i,concreto->motor()->entradas()->minimoEnDifusor(i));
		Codigo=cad;codigoFile.AddLine(cad);
		sprintf(cad,"    Difusores[%d].maximo=%f;",i,concreto->motor()->entradas()->maximoEnDifusor(i));
		Codigo=cad;codigoFile.AddLine(cad);
		sprintf(cad,"    Difusores[%d].centro=%f;",i,concreto->motor()->entradas()->centroEnDifusor(i));
		Codigo=cad;codigoFile.AddLine(cad);
		sprintf(cad,"    Difusores[%d].puntos=%d;",i,concreto->motor()->entradas()->numeroPuntosDifusor(i));
		Codigo=cad;codigoFile.AddLine(cad);
		sprintf(cad,"    Difusores[%d].intervalo=%f;",i,concreto->motor()->entradas()->intervaloDifusor(i));
		Codigo=cad;codigoFile.AddLine(cad);
		sprintf(cad,"    Difusores[%d].var1=%f;",i,concreto->motor()->entradas()->difusor(i)->var1());
		Codigo=cad;codigoFile.AddLine(cad);
		sprintf(cad,"    Difusores[%d].var2=%f;",i,concreto->motor()->entradas()->difusor(i)->var2());
		Codigo=cad;codigoFile.AddLine(cad);
		sprintf(cad,"    Difusores[%d].var3=%f;",i,concreto->motor()->entradas()->difusor(i)->var3());
		Codigo=cad;codigoFile.AddLine(cad);
		sprintf(cad,"    Difusores[%d].var4=%f;",i,concreto->motor()->entradas()->difusor(i)->var4());
		Codigo=cad;codigoFile.AddLine(cad);
	}
	Codigo="}";codigoFile.AddLine(Codigo);
	Codigo="void llenarReglas()";codigoFile.AddLine(Codigo);
	Codigo="{";codigoFile.AddLine(Codigo);
	for(i=0;i<numReglas;i++)
	{
		Codigo="    ";
		int j;
		for(j=0;j<numEntradas;j++)
		{
			sprintf(cad,"Reglas[%d][%d]=%d;",i,j,concreto->motor()->numConjuntoEntrada(i,j));
			Codigo=cad;codigoFile.AddLine(cad);
			 		}
		for(j=0;j<numSalidas;j++)
		{
			sprintf(cad,"Reglas[%d][%d]=%d;",i,numEntradas+j,concreto->motor()->numConjuntoSalida(i,j));
			Codigo=cad;codigoFile.AddLine(cad);
		}
		Codigo="";codigoFile.AddLine(Codigo);
	}
	Codigo="}\r\n";codigoFile.AddLine(Codigo);
	Codigo="void llenarModificadores()";codigoFile.AddLine(Codigo);
	Codigo="{";codigoFile.AddLine(Codigo);
	for(i=0;i<numReglas;i++)
	{
		Codigo="    ";
		int j;
		for(j=0;j<numEntradas;j++)
		{
			sprintf(cad,"Modificadores[%d][%d]=%f;",i,j,concreto->motor()->modificador(i,j));
			Codigo=cad;codigoFile.AddLine(cad);
		}
		Codigo="";codigoFile.AddLine(Codigo);
	}
	Codigo="}";codigoFile.AddLine(Codigo);
	Codigo="void llenarCentrosAltura()";codigoFile.AddLine(Codigo);
	Codigo="{";codigoFile.AddLine(Codigo);
	for(i=0;i<numReglas;i++)
	{
		Codigo="    ";
		int j;
		for(j=0;j<numSalidas;j++)
		{
			sprintf(cad,"CentrosAltura[%d][%d]=%f;",i,j,concreto->motor()->conjuntoSalida(i,j)->centroAltura());
			Codigo=cad;codigoFile.AddLine(cad);
		}
		Codigo="";codigoFile.AddLine(Codigo);
	}
	Codigo="}\r\n";codigoFile.AddLine(Codigo);
	Codigo="float pertenenciaDifusor(int numVar, float x)";codigoFile.AddLine(Codigo);
	Codigo="{";codigoFile.AddLine(Codigo);
	Codigo="    float ux=0;";codigoFile.AddLine(Codigo);
	Codigo="    switch(numVar)";codigoFile.AddLine(Codigo);
	Codigo="    {";codigoFile.AddLine(Codigo);
	for(i=0;i<numEntradas;i++)
	{
		sprintf(cad,"        case %d:",i);
		Codigo=cad;codigoFile.AddLine(cad);
		strcpy(cad,concreto->motor()->entradas()->difusor(i)->codigo_C(i));
		Codigo=cad;codigoFile.AddLine(cad);
		sprintf(cad,"            break;");
		Codigo=cad;codigoFile.AddLine(cad);
 	}
	Codigo="        default:break;";codigoFile.AddLine(Codigo);
	Codigo="    }";codigoFile.AddLine(Codigo);
	Codigo="    return ux;";codigoFile.AddLine(Codigo);
	Codigo="}";codigoFile.AddLine(Codigo);
	Codigo="float pertenenciaVariableEntrada(int numVar,int numConj, float x)";codigoFile.AddLine(Codigo);
	Codigo="{";codigoFile.AddLine(Codigo);
	Codigo="    float ux=0;";codigoFile.AddLine(Codigo);
	Codigo="    switch(numVar)";codigoFile.AddLine(Codigo);
	Codigo="    {";codigoFile.AddLine(Codigo);
	for(i=0;i<numEntradas;i++)
	{
		sprintf(cad,"        case %d:",i);
		Codigo=cad;codigoFile.AddLine(cad);
		Codigo="            switch(numConj)";codigoFile.AddLine(Codigo);
		Codigo="            {";codigoFile.AddLine(Codigo);
		int j;
		for(j=0;j<concreto->motor()->entradas()->numeroConjuntosEnVariable(i);j++)
		{
			sprintf(cad,"            case %d:",j);
			Codigo=cad;codigoFile.AddLine(cad);
			strcpy(cad,concreto->motor()->entradas()->conjuntoEnVariable(i,j)->codigoC());
			Codigo=cad;codigoFile.AddLine(cad);
			Codigo="                break;";codigoFile.AddLine(Codigo);
		}
		Codigo="            default:break;";codigoFile.AddLine(Codigo);
		Codigo="            }break;";codigoFile.AddLine(Codigo);
	}
	Codigo="        default:break;";codigoFile.AddLine(Codigo);
	Codigo="    }";codigoFile.AddLine(Codigo);
	Codigo="    return ux;";codigoFile.AddLine(Codigo);
	Codigo="}";codigoFile.AddLine(Codigo);
	Codigo="float pertenenciaVariableSalida(int numVar,int numConj, float x)";codigoFile.AddLine(Codigo);
	Codigo="{";codigoFile.AddLine(Codigo);
	Codigo="    float ux=0;";codigoFile.AddLine(Codigo);
	Codigo="    switch(numVar)";codigoFile.AddLine(Codigo);
	Codigo="    {";codigoFile.AddLine(Codigo);
	for(i=0;i<numSalidas;i++)
	{
		sprintf(cad,"        case %d:",i);
		Codigo=cad;codigoFile.AddLine(cad);
		Codigo="            switch(numConj)";codigoFile.AddLine(Codigo);
		Codigo="            {";codigoFile.AddLine(Codigo);
		int j;
		for(j=0;j<concreto->motor()->salidas()->numeroConjuntosEnVariable(i);j++)
		{
			sprintf(cad,"            case %d:",j);
			Codigo=cad;codigoFile.AddLine(cad);
			strcpy(cad,concreto->motor()->salidas()->conjuntoEnVariable(i,j)->codigoC());
			Codigo=cad;codigoFile.AddLine(cad);
			Codigo="                break;";codigoFile.AddLine(Codigo);
		}
		Codigo="            default:break;";codigoFile.AddLine(Codigo);
		Codigo="            }break;";codigoFile.AddLine(Codigo);
	}
	Codigo="        default:break;";codigoFile.AddLine(Codigo);
	Codigo="    }";codigoFile.AddLine(Codigo);
	Codigo="    return ux;";codigoFile.AddLine(Codigo);
	Codigo="}";codigoFile.AddLine(Codigo);
	Codigo="float Implicacion(float x,float y)";codigoFile.AddLine(Codigo);
	Codigo="{";codigoFile.AddLine(Codigo);
	Codigo="    float rel;";codigoFile.AddLine(Codigo);
	strcpy(cad,concreto->motor()->implicacion()->codigoC());
	Codigo=cad;codigoFile.AddLine(cad);
	Codigo="    return rel;";codigoFile.AddLine(Codigo);
	Codigo="}\r\n";codigoFile.AddLine(Codigo);
	Codigo="float Composicion(float x,float y)";codigoFile.AddLine(Codigo);
	Codigo="{";codigoFile.AddLine(Codigo);
	Codigo="    float z;";codigoFile.AddLine(Codigo);
	strcpy(cad,concreto->motor()->composicion()->codigoC());
	Codigo=cad;codigoFile.AddLine(cad);
	Codigo="    return z;";codigoFile.AddLine(Codigo);
	Codigo="}\r\n";codigoFile.AddLine(Codigo);
	Codigo="float Conjuncion(float x,float y)";codigoFile.AddLine(Codigo);
	Codigo="{";codigoFile.AddLine(Codigo);
	Codigo="    float z;";codigoFile.AddLine(Codigo);
	strcpy(cad,concreto->conjuncion()->codigoC());
	Codigo=cad;codigoFile.AddLine(cad);
	Codigo="    return z;";codigoFile.AddLine(Codigo);
	Codigo="}\r\n";codigoFile.AddLine(Codigo);
	Codigo="float And(float x,float y)";codigoFile.AddLine(Codigo);
	Codigo="{";codigoFile.AddLine(Codigo);
	Codigo="    float z;";codigoFile.AddLine(Codigo);
	strcpy(cad,concreto->motor()->and_()->codigoC());
	Codigo=cad;codigoFile.AddLine(cad);
	Codigo="    return z;";codigoFile.AddLine(Codigo);
	Codigo="}\r\n";codigoFile.AddLine(Codigo);

	if(codigoFile.Write())
	{
		wxMessageBox(_("Se ha creado el archivo"),("Información"));
	}else
	{
		wxMessageBox(_("No se pudo abrir el archivo"),("¡Atención!"));
	}
}


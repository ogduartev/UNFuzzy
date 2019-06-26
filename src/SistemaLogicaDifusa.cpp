#include "SistemaLogicaDifusa.h"

void SistemaLogicaDifusa::crearMinimoSLD(int numEnt,int numSal)
{
	nombre=_("Without name");
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
	  wxString n=_("Input ");
	  n << (i+1);
	  char str[40];sprintf(str,n.c_str());
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
	  wxString n=_("Output ");
	  n << (i+1);
	  char str[40];sprintf(str,n.c_str());
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

  double *entra=new double[numeroEntradas()];
  double *sale =new double[numeroSalidas()];
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
	double *minimoEntradas;
	double *intervalosEntradas;
	double *entra;
	double *sale;
	numEntradas=concreto->motor()->entradas()->numeroVariables();
	numSalidas =concreto->motor()->salidas()->numeroVariables();
	contadorIntervalos=new int[numEntradas];
	numIntervalos=new int[numEntradas];
	minimoEntradas=new double[numEntradas];
	intervalosEntradas=new double[numEntradas];
	entra=new double[numEntradas];
	sale =new double[numSalidas];

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
	wxString mensaje=_("Rows");
	wxProgressDialog progreso(_("Progress"), mensaje , maxLineas);
	while(bandera!=0)
	{
		conteoLineas++;
		mensaje =_("Rows: ");
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
		wxMessageBox(_("The file has been created"),_("Information"));
	}else
	{
		wxMessageBox(_("The file could not be opened"),_("¡Warning!"));
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
			if(wxMessageBox(_("The file fuzzy.cpp is neccesary in compilation ¿do you want to overwrite it?"),_("Warning"),wxOK|wxCANCEL|wxCANCEL_DEFAULT)==wxID_OK)
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
		wxMessageBox(_("The file has been created"),_("Information"));
	}else
	{
		wxMessageBox(_("The file could not be opened"),_("¡Warning!"));
	}
}

void SistemaLogicaDifusa::generarCodigoCPPEncabezado(wxTextFile* codigoFile)
{
	wxString Codigo="";

	Codigo=_("// C++ code for the Fuzzy Logic System\n");codigoFile->AddLine(Codigo);
	Codigo=_("// Automatically generated by UNFUZZY V 3.0");codigoFile->AddLine(Codigo);
	Codigo=_("// Author: Oscar Duarte (ogduartev@unal.edu.co)");codigoFile->AddLine(Codigo);
	Codigo=_("// Universidad Nacional de Colombia");codigoFile->AddLine(Codigo);
	Codigo=_("// Disclaimer: ");codigoFile->AddLine(Codigo);
	Codigo=_("// The code generated is udes under the responsability of the user.");codigoFile->AddLine(Codigo);
	Codigo=_("// It does not causes direct or indirect responsability neither for the author of UNFUZZY");codigoFile->AddLine(Codigo);
	Codigo=_("// nor for Universidad Nacional de Colombia.");codigoFile->AddLine(Codigo);
	Codigo=_("// ");codigoFile->AddLine(Codigo);
	Codigo=_("// in order to compile xxx.cpp:");codigoFile->AddLine(Codigo);
	Codigo=_("//   g++ xxx.cpp fuzzy.cpp");codigoFile->AddLine(Codigo);
	Codigo=("");codigoFile->AddLine(Codigo);
	Codigo=("#include <iostream>");codigoFile->AddLine(Codigo);
	Codigo=("#include <iostream>");codigoFile->AddLine(Codigo);
	Codigo=("#include <string>");codigoFile->AddLine(Codigo);
	Codigo=("using namespace std;\n");codigoFile->AddLine(Codigo);
	Codigo=("");codigoFile->AddLine(Codigo);
	Codigo=("#ifndef __FUZZY_H");codigoFile->AddLine(Codigo);
	Codigo=("#include \"fuzzy.h\"");codigoFile->AddLine(Codigo);
	Codigo=("#endif\r\n");codigoFile->AddLine(Codigo);
}

void SistemaLogicaDifusa::generarCodigoCPPClase(wxTextFile* codigoFile,wxString nombreClase)
{
	wxString Codigo=("");

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
			Codigo=concreto->motor()->entradas()->conjuntoEnVariable(i,j)->codigoCPP();codigoFile->AddLine(Codigo);
			Codigo=("    var->adicionarConjuntos(cd);");codigoFile->AddLine(Codigo);
		}
		Codigo=concreto->motor()->entradas()->difusor(i)->codigo_CPP();codigoFile->AddLine(Codigo);
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
		Codigo=("    var=new Variable(");
		Codigo << concreto->motor()->salidas()->numeroConjuntosEnVariable(i) << (");");codigoFile->AddLine(Codigo);
		Codigo=("    var->rangoMinimo(");
		Codigo << concreto->motor()->salidas()->rangoMinimoVariable(i) << (");");codigoFile->AddLine(Codigo);
		Codigo=("    var->rangoMaximo(");
		Codigo << concreto->motor()->salidas()->rangoMaximoVariable(i) << (");");codigoFile->AddLine(Codigo);
		int j;
		for(j=0;j<concreto->motor()->salidas()->numeroConjuntosEnVariable(i);j++)
		{
			Codigo=concreto->motor()->salidas()->conjuntoEnVariable(i,j)->codigoCPP();codigoFile->AddLine(Codigo);
			Codigo=("    var->adicionarConjuntos(cd);");codigoFile->AddLine(Codigo);
		}
		Codigo=("    var->nombreVariable(\"");
		Codigo << concreto->motor()->salidas()->nombreVariable(i) <<("\");");codigoFile->AddLine(Codigo);
		Codigo =("    var->numeroIntervalos(");
		Codigo << concreto->motor()->salidas()->numeroIntervalosEnVariable(i) << (");");codigoFile->AddLine(Codigo);
		Codigo=("    salidas->adicionarVariable(var);");codigoFile->AddLine(Codigo);
	}

	Codigo=("    motor=new MaquinaInferencia(entradas,salidas,");
	Codigo << concreto->motor()->numeroReglas() << (");");codigoFile->AddLine(Codigo);
	Codigo=("    And=new ");
	Codigo << concreto->motor()->and_()->codigoCPP();codigoFile->AddLine(Codigo);
	Codigo=("    Composicion=new ");
	Codigo << concreto->motor()->composicion()->codigoCPP();codigoFile->AddLine(Codigo);
//////////////
	Codigo=("    Implica=new ");
	Codigo << concreto->motor()->implicacion()->codigoCPP();codigoFile->AddLine(Codigo);
	Codigo=("    motor->and_(And);");codigoFile->AddLine(Codigo);
	Codigo=("    motor->composicion(Composicion);");codigoFile->AddLine(Codigo);
	Codigo=("    motor->implicacion(Implica);");codigoFile->AddLine(Codigo);
	for(i=0;i<concreto->motor()->numeroReglas();i++)
	{
		int j;
		for(j=0;j<concreto->motor()->entradas()->numeroVariables();j++)
		{
			Codigo=("    motor->conjuntoEntrada(");
			Codigo << i << (",") << j << (",") << concreto->motor()->numConjuntoEntrada(i,j) << (");");codigoFile->AddLine(Codigo);
		}
		for(j=0;j<concreto->motor()->salidas()->numeroVariables();j++)
		{
			Codigo=("    motor->conjuntoSalida(");
			Codigo << i << (",") << j << (",") << concreto->motor()->numConjuntoSalida(i,j) << (");");codigoFile->AddLine(Codigo);
		}
	}
	for(i=0;i<concreto->motor()->numeroReglas();i++)
	{
		int j;
		for(j=0;j<concreto->motor()->entradas()->numeroVariables();j++)
		{
			Codigo=("    motor->modificador(");
			Codigo << i << (",") << j << (",") << concreto->motor()->modificador(i,j) << (");");codigoFile->AddLine(Codigo);
		}
	}
	Codigo=("    concreto=new BloqueConcrecion(motor);");codigoFile->AddLine(Codigo);
	Codigo=("    Conjuncion=new ");
	Codigo << concreto->conjuncion()->codigoCPP();codigoFile->AddLine(Codigo);
	for(i=0;i<concreto->motor()->salidas()->numeroVariables();i++)
	{
		Codigo=concreto->concresor(i)->codigoCPP();codigoFile->AddLine(Codigo);
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

	Codigo=("int main()");codigoFile->AddLine(Codigo);
	Codigo=("{");codigoFile->AddLine(Codigo);
	Codigo=("    double *entra;");codigoFile->AddLine(Codigo);
	Codigo=("    double *sale;");codigoFile->AddLine(Codigo);
	Codigo=("    ");
	Codigo << nombreClase << (" *sistema;");codigoFile->AddLine(Codigo);
	Codigo=("    int NumeroEntradas;");codigoFile->AddLine(Codigo);
	Codigo=("    int NumeroSalidas;");codigoFile->AddLine(Codigo);
	Codigo=("    sistema=new ");
	Codigo << nombreClase << ("();");codigoFile->AddLine(Codigo);
	Codigo=("    NumeroEntradas=sistema->numeroEntradas();");codigoFile->AddLine(Codigo);
	Codigo=("    NumeroSalidas=sistema->numeroSalidas();");codigoFile->AddLine(Codigo);
	Codigo=("    entra=new double[NumeroEntradas];");codigoFile->AddLine(Codigo);
	Codigo=("    sale=new double[NumeroSalidas];");codigoFile->AddLine(Codigo);
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
	Codigo+=_("Do you want another calculus? (s/n)");
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
	generarCodigoCEncabezado(&codigoFile);
	generarCodigoCDefs(&codigoFile);
	generarCodigoCMain(&codigoFile);
	generarCodigoCFunciones(&codigoFile);
	generarCodigoCSistema(&codigoFile);
}

void SistemaLogicaDifusa::generarCodigoCEncabezado(wxTextFile* codigoFile)
{
	wxString Codigo=("");

	Codigo=("// Código C del Sistema de Lógica Difusa\n");codigoFile->AddLine(Codigo);
	Codigo=("// Automatically generated by UNFUZZY V 3.0");codigoFile->AddLine(Codigo);
	Codigo=("// Author: Oscar Duarte (ogduartev@unal.edu.co)");codigoFile->AddLine(Codigo);
	Codigo=("// Universidad Nacional de Colombia");codigoFile->AddLine(Codigo);
	Codigo=("// Disclaimer: ");codigoFile->AddLine(Codigo);
	Codigo=("// The code generated is udes under the responsability of the user.");codigoFile->AddLine(Codigo);
	Codigo=("// It does not causes direct or indirect responsability neither for the author of UNFUZZY");codigoFile->AddLine(Codigo);
	Codigo=("// nor for Universidad Nacional de Colombia.");codigoFile->AddLine(Codigo);
	Codigo=("// ");codigoFile->AddLine(Codigo);
	Codigo=("// para compilar el archivo xxx.c:");codigoFile->AddLine(Codigo);
	Codigo=("//   g++ xxx.c");codigoFile->AddLine(Codigo);
	Codigo=("");codigoFile->AddLine(Codigo);
	Codigo="#include <stdio.h>";codigoFile->AddLine(Codigo);
	Codigo="#include <string.h>";codigoFile->AddLine(Codigo);
	Codigo="#include <math.h>";codigoFile->AddLine(Codigo);
	Codigo="#include <iostream>";codigoFile->AddLine(Codigo);
	Codigo="#include <string>";codigoFile->AddLine(Codigo);
	Codigo="using namespace std;\n";codigoFile->AddLine(Codigo);
}

void SistemaLogicaDifusa::generarCodigoCDefs(wxTextFile* codigoFile)
{
	wxString Codigo=("");

	Codigo=("#define NUMEROREGLAS                 ");
	Codigo << concreto->motor()->numeroReglas();codigoFile->AddLine(Codigo);
	Codigo=("#define NUMEROVARIABLESENTRADA       ");
	Codigo << concreto->motor()->entradas()->numeroVariables();codigoFile->AddLine(Codigo);
	Codigo=("#define NUMEROVARIABLESSALIDA        ");
	Codigo << concreto->motor()->salidas()->numeroVariables();codigoFile->AddLine(Codigo);
	int numConjTotales=0;
	int i;
	for(i=0;i<concreto->motor()->entradas()->numeroVariables();i++)
	{
		numConjTotales=numConjTotales+concreto->motor()->entradas()->numeroConjuntosEnVariable(i);
	}
	Codigo=("#define NUMEROTOTALCONJUNTOSENTRADA  ");
	Codigo<< numConjTotales << "\n";codigoFile->AddLine(Codigo);

	Codigo="struct conjunto{";codigoFile->AddLine(Codigo);
	Codigo="	string nombre;";codigoFile->AddLine(Codigo);
	Codigo="	double minimo;";codigoFile->AddLine(Codigo);
	Codigo="	double maximo;";codigoFile->AddLine(Codigo);
	Codigo="};\r\n";codigoFile->AddLine(Codigo);
	Codigo="struct variable{";codigoFile->AddLine(Codigo);
	Codigo="	string nombre;";codigoFile->AddLine(Codigo);
	Codigo="	double minimo;";codigoFile->AddLine(Codigo);
	Codigo="	double maximo;";codigoFile->AddLine(Codigo);
	Codigo="	int intervalos;";codigoFile->AddLine(Codigo);
	Codigo="	double intervalo;";codigoFile->AddLine(Codigo);
	Codigo="	int numeroConjuntos;";codigoFile->AddLine(Codigo);
	Codigo="};\r\n";codigoFile->AddLine(Codigo);
	Codigo="struct difusor{";codigoFile->AddLine(Codigo);
	Codigo="	double minimo;";codigoFile->AddLine(Codigo);
	Codigo="	double maximo;";codigoFile->AddLine(Codigo);
	Codigo="	double centro;";codigoFile->AddLine(Codigo);
	Codigo="	double var1;";codigoFile->AddLine(Codigo);
	Codigo="	double var2;";codigoFile->AddLine(Codigo);
	Codigo="	double var3;";codigoFile->AddLine(Codigo);
	Codigo="	double var4;";codigoFile->AddLine(Codigo);
	Codigo="	int puntos;";codigoFile->AddLine(Codigo);
	Codigo="	double intervalo;";codigoFile->AddLine(Codigo);
	Codigo="};\r\n";codigoFile->AddLine(Codigo);
	Codigo="struct variable VariablesEntrada[NUMEROVARIABLESENTRADA];";codigoFile->AddLine(Codigo);
	Codigo="struct variable VariablesSalida[NUMEROVARIABLESSALIDA];";codigoFile->AddLine(Codigo);
	Codigo="struct conjunto Entradas[NUMEROTOTALCONJUNTOSENTRADA];";codigoFile->AddLine(Codigo);
	Codigo="struct difusor Difusores[NUMEROTOTALCONJUNTOSENTRADA];";codigoFile->AddLine(Codigo);
	Codigo="int Reglas[NUMEROREGLAS][NUMEROVARIABLESENTRADA+NUMEROVARIABLESSALIDA];";codigoFile->AddLine(Codigo);
	Codigo="double Modificadores[NUMEROREGLAS][NUMEROVARIABLESENTRADA];";codigoFile->AddLine(Codigo);
	Codigo="double CentrosAltura[NUMEROREGLAS][NUMEROVARIABLESSALIDA];";codigoFile->AddLine(Codigo);
	Codigo="void llenarDatos();";codigoFile->AddLine(Codigo);
	Codigo="void llenarVariablesEntrada();";codigoFile->AddLine(Codigo);
	Codigo="void llenarVariablesSalida();";codigoFile->AddLine(Codigo);
	Codigo="void llenarEntradas();";codigoFile->AddLine(Codigo);
	Codigo="void llenarDifusores();";codigoFile->AddLine(Codigo);
	Codigo="void llenarReglas();";codigoFile->AddLine(Codigo);
	Codigo="void llenarModificadores();";codigoFile->AddLine(Codigo);
	Codigo="void llenarCentrosAltura();";codigoFile->AddLine(Codigo);
	Codigo="void calcular(double *ent,double *sal);";codigoFile->AddLine(Codigo);
	Codigo="double salidaConcreta(int NumeroSalida, double *entra);";codigoFile->AddLine(Codigo);
	for(i=0;i<concreto->motor()->salidas()->numeroVariables();i++)
	{
		Codigo=("double salidaConcreta");
		Codigo << i <<("(double *entra);");codigoFile->AddLine(Codigo);
	}
	Codigo="";codigoFile->AddLine(Codigo);
	Codigo="double pertenenciaComposicion(int numVar, int numRegla, double sal);";codigoFile->AddLine(Codigo);
	Codigo="double pertenenciaDifusores(double *ent);";codigoFile->AddLine(Codigo);
	Codigo="double pertenenciaImplicacion(int numSal, int numRegla,double *ent, double sal);";codigoFile->AddLine(Codigo);
	Codigo="double pertenenciaConsecuente(int numSal, int numRegla, double sal);";codigoFile->AddLine(Codigo);
	Codigo="double pertenenciaAntecedente(int numRegla, double *ent);";codigoFile->AddLine(Codigo);
	Codigo="int activarRegla(int numRegla);";codigoFile->AddLine(Codigo);
	Codigo="double pertenenciaDifusor(int numVar, double x);";codigoFile->AddLine(Codigo);
	Codigo="double pertenenciaVariableEntrada(int numVar,int numConj, double x);";codigoFile->AddLine(Codigo);
	Codigo="double pertenenciaVariableSalida(int numVar,int numConj, double x);\r\n";codigoFile->AddLine(Codigo);
	Codigo="int indiceEntradas(int numRegla,int numVar);";codigoFile->AddLine(Codigo);
	Codigo="void actualizarEntradas(double *ent);";codigoFile->AddLine(Codigo);
	Codigo="double Implicacion(double x,double y);";codigoFile->AddLine(Codigo);
	Codigo="double Composicion(double x,double y);";codigoFile->AddLine(Codigo);
	Codigo="double Conjuncion(double x,double y);";codigoFile->AddLine(Codigo);
	Codigo="double And(double x,double y);";codigoFile->AddLine(Codigo);
	Codigo="";codigoFile->AddLine(Codigo);
}

void SistemaLogicaDifusa::generarCodigoCMain(wxTextFile* codigoFile)
{
	wxString Codigo=("");

	Codigo="int main()";codigoFile->AddLine(Codigo);
	Codigo="{";codigoFile->AddLine(Codigo);
	Codigo="    double entra[NUMEROVARIABLESENTRADA];";codigoFile->AddLine(Codigo);
	Codigo="    double sale[NUMEROVARIABLESSALIDA];";codigoFile->AddLine(Codigo);
	Codigo="    char q='s';";codigoFile->AddLine(Codigo);
	Codigo="    llenarDatos();";codigoFile->AddLine(Codigo);
	Codigo="    while(q=='s')";codigoFile->AddLine(Codigo);
	Codigo="    {";codigoFile->AddLine(Codigo);
	Codigo="        int i;";codigoFile->AddLine(Codigo);
	Codigo="        for(i=0;i<NUMEROVARIABLESENTRADA;i++)";codigoFile->AddLine(Codigo);
	Codigo="        {";codigoFile->AddLine(Codigo);
	Codigo="            double e;";codigoFile->AddLine(Codigo);
	Codigo="            printf(\"%s : \",VariablesEntrada[i].nombre.c_str());";codigoFile->AddLine(Codigo);
	Codigo="            scanf(\"%lf\",&e);";codigoFile->AddLine(Codigo);
	Codigo="            entra[i]=e;";codigoFile->AddLine(Codigo);
	Codigo="        }";codigoFile->AddLine(Codigo);
	Codigo="        calcular(entra,sale);";codigoFile->AddLine(Codigo);
	Codigo="        for(i=0;i<NUMEROVARIABLESSALIDA;i++)";codigoFile->AddLine(Codigo);
	Codigo="        {";codigoFile->AddLine(Codigo);
	Codigo="            printf(\"%s : \",VariablesSalida[i].nombre.c_str());";codigoFile->AddLine(Codigo);
	Codigo="            printf(\"%lf : \\n\",sale[i]);";codigoFile->AddLine(Codigo);
	Codigo="        }";codigoFile->AddLine(Codigo);
	Codigo="        printf(\"";
	Codigo+=_("Do you want another calculus? (s/n)");
	Codigo+="\");";codigoFile->AddLine(Codigo);
	Codigo="        fflush(stdin);";codigoFile->AddLine(Codigo);
	Codigo="        scanf(\" %c\",&q);";codigoFile->AddLine(Codigo);
	Codigo="    }";codigoFile->AddLine(Codigo);
	Codigo="}";codigoFile->AddLine(Codigo);
}

void SistemaLogicaDifusa::generarCodigoCFunciones(wxTextFile* codigoFile)
{
	wxString Codigo=("");

	Codigo="void llenarDatos()";codigoFile->AddLine(Codigo);
	Codigo="{";codigoFile->AddLine(Codigo);
	Codigo="    llenarVariablesEntrada();";codigoFile->AddLine(Codigo);
	Codigo="    llenarVariablesSalida();";codigoFile->AddLine(Codigo);
	Codigo="    llenarEntradas();";codigoFile->AddLine(Codigo);
	Codigo="    llenarDifusores();";codigoFile->AddLine(Codigo);
	Codigo="    llenarReglas();";codigoFile->AddLine(Codigo);
	Codigo="    llenarModificadores();";codigoFile->AddLine(Codigo);
	Codigo="    llenarCentrosAltura();";codigoFile->AddLine(Codigo);
	Codigo="}";codigoFile->AddLine(Codigo);
	Codigo="void calcular(double *entra, double *sale)";codigoFile->AddLine(Codigo);
	Codigo="{";codigoFile->AddLine(Codigo);
	Codigo="    int i;";codigoFile->AddLine(Codigo);
	Codigo="    for(i=0;i<NUMEROVARIABLESSALIDA;i++)";codigoFile->AddLine(Codigo);
	Codigo="    {";codigoFile->AddLine(Codigo);
	Codigo="        sale[i]=salidaConcreta(i,entra);";codigoFile->AddLine(Codigo);
	Codigo="    }";codigoFile->AddLine(Codigo);
	Codigo="}";codigoFile->AddLine(Codigo);
	Codigo="void actualizarEntradas(double *ent)";codigoFile->AddLine(Codigo);
	Codigo="{";codigoFile->AddLine(Codigo);
	Codigo="    double dx;";codigoFile->AddLine(Codigo);
	Codigo="    int i;";codigoFile->AddLine(Codigo);
	Codigo="    for(i=0;i<NUMEROVARIABLESENTRADA;i++)";codigoFile->AddLine(Codigo);
	Codigo="    {";codigoFile->AddLine(Codigo);
	Codigo="        dx=ent[i]-Difusores[i].centro;";codigoFile->AddLine(Codigo);
	Codigo="        Difusores[i].centro=Difusores[i].centro+dx;";codigoFile->AddLine(Codigo);
	Codigo="        Difusores[i].minimo=Difusores[i].minimo+dx;";codigoFile->AddLine(Codigo);
	Codigo="        Difusores[i].maximo=Difusores[i].maximo+dx;";codigoFile->AddLine(Codigo);
	Codigo="        Difusores[i].var1=Difusores[i].var1+dx;";codigoFile->AddLine(Codigo);
	Codigo="        Difusores[i].var2=Difusores[i].var2+dx;";codigoFile->AddLine(Codigo);
	Codigo="        Difusores[i].var3=Difusores[i].var3+dx;";codigoFile->AddLine(Codigo);
	Codigo="        Difusores[i].var4=Difusores[i].var4+dx;";codigoFile->AddLine(Codigo);
	Codigo="    }";codigoFile->AddLine(Codigo);
	Codigo="}";codigoFile->AddLine(Codigo);
	Codigo="int indiceEntradas(int numVar,int numConj)";codigoFile->AddLine(Codigo);
	Codigo="{";codigoFile->AddLine(Codigo);
	Codigo="    int contador=0;";codigoFile->AddLine(Codigo);
	Codigo="    int i;";codigoFile->AddLine(Codigo);
	Codigo="    for(i=0;i<numVar;i++)";codigoFile->AddLine(Codigo);
	Codigo="    {";codigoFile->AddLine(Codigo);
	Codigo="        contador=contador+VariablesEntrada[i].numeroConjuntos;";codigoFile->AddLine(Codigo);
	Codigo="    }";codigoFile->AddLine(Codigo);
	Codigo="    contador=contador+numConj;";codigoFile->AddLine(Codigo);
	Codigo="    return contador;";codigoFile->AddLine(Codigo);
	Codigo="}";codigoFile->AddLine(Codigo);
	Codigo="double pertenenciaComposicion(int numVar,int numRegla, double sal)";codigoFile->AddLine(Codigo);
	Codigo="{";codigoFile->AddLine(Codigo);
	Codigo="    double ux;";codigoFile->AddLine(Codigo);
	Codigo="    double uxa;";codigoFile->AddLine(Codigo);
	Codigo="    double uxab;";codigoFile->AddLine(Codigo);
	Codigo="    double comp=0;";codigoFile->AddLine(Codigo);
	Codigo="    double x[NUMEROVARIABLESENTRADA];";codigoFile->AddLine(Codigo);
	Codigo="    int inter[NUMEROVARIABLESENTRADA];";codigoFile->AddLine(Codigo);
	Codigo="    if(!activarRegla(numRegla))";codigoFile->AddLine(Codigo);
	Codigo="    {";codigoFile->AddLine(Codigo);
	Codigo="        comp=Implicacion(0,0);";codigoFile->AddLine(Codigo);
	Codigo="    }";codigoFile->AddLine(Codigo);
	Codigo="    else{";codigoFile->AddLine(Codigo);
	Codigo="        int casos=1;";codigoFile->AddLine(Codigo);
	Codigo="        int i;";codigoFile->AddLine(Codigo);
	Codigo="        for(i=0;i<NUMEROVARIABLESENTRADA;i++)";codigoFile->AddLine(Codigo);
	Codigo="        {";codigoFile->AddLine(Codigo);
	Codigo="            casos=casos*Difusores[i].puntos;";codigoFile->AddLine(Codigo);
	Codigo="            inter[i]=1;";codigoFile->AddLine(Codigo);
	Codigo="        }";codigoFile->AddLine(Codigo);
	Codigo="        for(i=0;i<NUMEROVARIABLESENTRADA;i++)";codigoFile->AddLine(Codigo);
	Codigo="        {";codigoFile->AddLine(Codigo);
	Codigo="            int k;";codigoFile->AddLine(Codigo);
	Codigo="            for(k=0;k<NUMEROVARIABLESENTRADA;k++)";codigoFile->AddLine(Codigo);
	Codigo="            {";codigoFile->AddLine(Codigo);
	Codigo="                x[k]=Difusores[k].minimo+Difusores[k].intervalo*inter[k];";codigoFile->AddLine(Codigo);
	Codigo="                inter[k]=inter[k]+1;";codigoFile->AddLine(Codigo);
	Codigo="                if(inter[k]>=Difusores[k].puntos)";codigoFile->AddLine(Codigo);
	Codigo="                {";codigoFile->AddLine(Codigo);
	Codigo="                    inter[k]=1;";codigoFile->AddLine(Codigo);
	Codigo="                }";codigoFile->AddLine(Codigo);
	Codigo="            }";codigoFile->AddLine(Codigo);
	Codigo="            uxab=pertenenciaImplicacion(numVar,numRegla,x,sal);";codigoFile->AddLine(Codigo);
	Codigo="            uxa=pertenenciaDifusores(x);";codigoFile->AddLine(Codigo);
	Codigo="            ux=Composicion(uxa,uxab);";codigoFile->AddLine(Codigo);
	Codigo="            if(ux>comp)";codigoFile->AddLine(Codigo);
	Codigo="            {";codigoFile->AddLine(Codigo);
	Codigo="                comp=ux;";codigoFile->AddLine(Codigo);
	Codigo="            }";codigoFile->AddLine(Codigo);
	Codigo="        }";codigoFile->AddLine(Codigo);
	Codigo="    }";codigoFile->AddLine(Codigo);
	Codigo="    return comp;";codigoFile->AddLine(Codigo);
	Codigo="}";codigoFile->AddLine(Codigo);
	Codigo="double pertenenciaDifusores(double *ent)";codigoFile->AddLine(Codigo);
	Codigo="{";codigoFile->AddLine(Codigo);
	Codigo="    double uxd;";codigoFile->AddLine(Codigo);
	Codigo="    int j=0;";codigoFile->AddLine(Codigo);
	Codigo="    uxd=pertenenciaDifusor(j,ent[j]);";codigoFile->AddLine(Codigo);
	Codigo="    for(j=0;j<NUMEROVARIABLESENTRADA;j++)";codigoFile->AddLine(Codigo);
	Codigo="    {";codigoFile->AddLine(Codigo);
	Codigo="    uxd=And(uxd,pertenenciaDifusor(j,ent[j]));";codigoFile->AddLine(Codigo);
	Codigo="    }";codigoFile->AddLine(Codigo);
	Codigo="    return uxd;";codigoFile->AddLine(Codigo);
	Codigo="}";codigoFile->AddLine(Codigo);
	Codigo="double pertenenciaImplicacion(int numSal,int numRegla,double *ent,double sal)";codigoFile->AddLine(Codigo);
	Codigo="{";codigoFile->AddLine(Codigo);
	Codigo="    double uxa,uxb;";codigoFile->AddLine(Codigo);
	Codigo="    uxa=pertenenciaAntecedente(numRegla,ent);";codigoFile->AddLine(Codigo);
	Codigo="    uxb=pertenenciaConsecuente(numSal,numRegla,sal);";codigoFile->AddLine(Codigo);
	Codigo="    return Implicacion(uxa,uxb);";codigoFile->AddLine(Codigo);
	Codigo="}";codigoFile->AddLine(Codigo);
	Codigo="double pertenenciaConsecuente(int numSal,int numRegla,double sal)";codigoFile->AddLine(Codigo);
	Codigo="{";codigoFile->AddLine(Codigo);
	Codigo="    double uxc;";codigoFile->AddLine(Codigo);
	Codigo="    int conj;";codigoFile->AddLine(Codigo);
	Codigo="    conj=Reglas[numRegla][NUMEROVARIABLESENTRADA+numSal];";codigoFile->AddLine(Codigo);
	Codigo="    uxc=pertenenciaVariableSalida(numSal,conj,sal);";codigoFile->AddLine(Codigo);
	Codigo="    return uxc;";codigoFile->AddLine(Codigo);
	Codigo="}";codigoFile->AddLine(Codigo);
	Codigo="double pertenenciaAntecedente(int numRegla,double *ent)";codigoFile->AddLine(Codigo);
	Codigo="{";codigoFile->AddLine(Codigo);
	Codigo="    double ux;";codigoFile->AddLine(Codigo);
	Codigo="    double uxa;";codigoFile->AddLine(Codigo);
	Codigo="    int conj;";codigoFile->AddLine(Codigo);
	Codigo="    int j=0;";codigoFile->AddLine(Codigo);
	Codigo="    conj=Reglas[numRegla][0];";codigoFile->AddLine(Codigo);
	Codigo="    ux=pertenenciaVariableEntrada(j,conj,ent[j]);";codigoFile->AddLine(Codigo);
	Codigo="    if(Modificadores[numRegla][0]>0.0)";codigoFile->AddLine(Codigo);
	Codigo="    {";codigoFile->AddLine(Codigo);
	Codigo="        uxa=pow(ux,Modificadores[numRegla][0]);";codigoFile->AddLine(Codigo);
	Codigo="    }else";codigoFile->AddLine(Codigo);
	Codigo="    {";codigoFile->AddLine(Codigo);
	Codigo="        uxa=1;";codigoFile->AddLine(Codigo);
	Codigo="    }";codigoFile->AddLine(Codigo);
	Codigo="    for(j=1;j<NUMEROVARIABLESENTRADA;j++)";codigoFile->AddLine(Codigo);
	Codigo="    {";codigoFile->AddLine(Codigo);
	Codigo="        conj=Reglas[numRegla][j];";codigoFile->AddLine(Codigo);
	Codigo="        ux=pertenenciaVariableEntrada(j,conj,ent[j]);";codigoFile->AddLine(Codigo);
	Codigo="        if(Modificadores[numRegla][j]>0.0)";codigoFile->AddLine(Codigo);
	Codigo="        {";codigoFile->AddLine(Codigo);
	Codigo="            ux=pow(ux,Modificadores[numRegla][j]);";codigoFile->AddLine(Codigo);
	Codigo="        }else";codigoFile->AddLine(Codigo);
	Codigo="        {";codigoFile->AddLine(Codigo);
	Codigo="            ux=1;";codigoFile->AddLine(Codigo);
	Codigo="        }";codigoFile->AddLine(Codigo);
	Codigo="        uxa=And(uxa,ux);";codigoFile->AddLine(Codigo);
	Codigo="    }";codigoFile->AddLine(Codigo);
	Codigo="    return uxa;";codigoFile->AddLine(Codigo);
	Codigo="}";codigoFile->AddLine(Codigo);
	Codigo="int activarRegla(int numRegla)";codigoFile->AddLine(Codigo);
	Codigo="{";codigoFile->AddLine(Codigo);
	Codigo="    int i;";codigoFile->AddLine(Codigo);
	Codigo="    for(i=0;i<NUMEROVARIABLESENTRADA;i++)";codigoFile->AddLine(Codigo);
	Codigo="    {";codigoFile->AddLine(Codigo);
	Codigo="        double bmn,bmx,cmn,cmx;";codigoFile->AddLine(Codigo);
	Codigo="        int numCon;";codigoFile->AddLine(Codigo);
	Codigo="        int indice;";codigoFile->AddLine(Codigo);
	Codigo="        numCon=Reglas[numRegla][i];";codigoFile->AddLine(Codigo);
	Codigo="        indice=indiceEntradas(i,numCon);";codigoFile->AddLine(Codigo);
	Codigo="        bmn=Entradas[indice].minimo;";codigoFile->AddLine(Codigo);
	Codigo="        bmx=Entradas[indice].maximo;";codigoFile->AddLine(Codigo);
	Codigo="        cmn=Difusores[i].minimo;";codigoFile->AddLine(Codigo);
	Codigo="        cmx=Difusores[i].maximo;";codigoFile->AddLine(Codigo);
	Codigo="        if(bmn>cmx||bmx<cmn)";codigoFile->AddLine(Codigo);
	Codigo="            return 0;";codigoFile->AddLine(Codigo);
	Codigo="    }";codigoFile->AddLine(Codigo);
	Codigo="    return 1;";codigoFile->AddLine(Codigo);
	Codigo="}";codigoFile->AddLine(Codigo);
	Codigo="double salidaConcreta(int NumeroSalida,double *ent)";codigoFile->AddLine(Codigo);
	Codigo="{";codigoFile->AddLine(Codigo);
	Codigo="    double respuesta;";codigoFile->AddLine(Codigo);
	Codigo="    switch(NumeroSalida)";codigoFile->AddLine(Codigo);
	Codigo="    {";codigoFile->AddLine(Codigo);
	for(int i=0;i<concreto->motor()->salidas()->numeroVariables();i++)
	{
		Codigo=("        case ");
		Codigo << i << (" : respuesta=salidaConcreta") << i << ("(ent);break;");codigoFile->AddLine(Codigo);
	}
	Codigo="        default:respuesta=0;break;";codigoFile->AddLine(Codigo);
	Codigo="    }";codigoFile->AddLine(Codigo);
	Codigo="    return respuesta;";codigoFile->AddLine(Codigo);
	Codigo="}";codigoFile->AddLine(Codigo);
}

void SistemaLogicaDifusa::generarCodigoCSistema(wxTextFile* codigoFile)
{
	wxString Codigo=("");

	int numEntradas;
	int numSalidas;
	int numReglas;
	numEntradas=concreto->motor()->entradas()->numeroVariables();
	numSalidas=concreto->motor()->salidas()->numeroVariables();
	numReglas=concreto->motor()->numeroReglas();
	for(int i=0;i<numSalidas;i++)
	{
		Codigo=concreto->concresor(i)->codigoC();codigoFile->AddLine(Codigo);
	}
	Codigo="void llenarVariablesEntrada()";codigoFile->AddLine(Codigo);
	Codigo="{";codigoFile->AddLine(Codigo);
	for(int i=0;i<numEntradas;i++)
	{
		Codigo=("    VariablesEntrada[");
		Codigo << i << ("].nombre=\"")        << concreto->motor()->entradas()->nombreVariable(i) << ("\";");codigoFile->AddLine(Codigo);
		Codigo=("    VariablesEntrada[");
		Codigo << i << ("].minimo=")          << concreto->motor()->entradas()->rangoMinimoVariable(i) << (";");codigoFile->AddLine(Codigo);
		Codigo=("    VariablesEntrada[");
		Codigo << i << ("].maximo=")          << concreto->motor()->entradas()->rangoMaximoVariable(i) << (";");codigoFile->AddLine(Codigo);
		Codigo=("    VariablesEntrada[");
		Codigo << i << ("].intervalos=")      << concreto->motor()->entradas()->variable(i)->numeroIntervalos() << (";");codigoFile->AddLine(Codigo);
		Codigo=("    VariablesEntrada[");
		Codigo << i << ("].intervalo=")       << concreto->motor()->entradas()->variable(i)->intervalo() << (";");codigoFile->AddLine(Codigo);
		Codigo=("    VariablesEntrada[");
		Codigo << i << ("].numeroConjuntos=") << concreto->motor()->entradas()->numeroConjuntosEnVariable(i) << (";\n");codigoFile->AddLine(Codigo);
	}
	Codigo="}\r\n";codigoFile->AddLine(Codigo);
	Codigo="void llenarVariablesSalida()";codigoFile->AddLine(Codigo);
	Codigo="{";codigoFile->AddLine(Codigo);
	for(int i=0;i<numSalidas;i++)
	{
		Codigo=("    VariablesSalida[");
		Codigo << i << ("].nombre=\"")        << concreto->motor()->salidas()->nombreVariable(i) << ("\";");codigoFile->AddLine(Codigo);
		Codigo=("    VariablesSalida[");
		Codigo << i << ("].minimo=")          << concreto->motor()->salidas()->rangoMinimoVariable(i) << (";");codigoFile->AddLine(Codigo);
		Codigo=("    VariablesSalida[");
		Codigo << i << ("].maximo=")          << concreto->motor()->salidas()->rangoMaximoVariable(i) << (";");codigoFile->AddLine(Codigo);
		Codigo=("    VariablesSalida[");
		Codigo << i << ("].intervalos=")      << concreto->motor()->salidas()->variable(i)->numeroIntervalos() << (";");codigoFile->AddLine(Codigo);
		Codigo=("    VariablesSalida[");
		Codigo << i << ("].intervalo=")       << concreto->motor()->salidas()->variable(i)->intervalo() << (";");codigoFile->AddLine(Codigo);
		Codigo=("    VariablesSalida[");
		Codigo << i << ("].numeroConjuntos=") << concreto->motor()->salidas()->numeroConjuntosEnVariable(i) << (";\n");codigoFile->AddLine(Codigo);
	}
	Codigo="}";codigoFile->AddLine(Codigo);
	Codigo="void llenarEntradas()";codigoFile->AddLine(Codigo);
	Codigo="{";codigoFile->AddLine(Codigo);
	int contador=0;
	for(int i=0;i<numEntradas;i++)
	{
		int numConj;
		numConj=concreto->motor()->entradas()->numeroConjuntosEnVariable(i);
		for(int j=0;j<numConj;j++)
		{
			Codigo=("    Entradas[");
			Codigo << contador << ("].minimo=") << concreto->motor()->entradas()->minimoEnConjunto(i,j) << (";");codigoFile->AddLine(Codigo);
			Codigo=("    Entradas[");
			Codigo << contador << ("].maximo=") << concreto->motor()->entradas()->maximoEnConjunto(i,j) << (";\n");codigoFile->AddLine(Codigo);
			contador=contador+1;
		}
	}
	Codigo="}";codigoFile->AddLine(Codigo);
 	Codigo="void llenarDifusores()";codigoFile->AddLine(Codigo);
	Codigo="{";codigoFile->AddLine(Codigo);
	for(int i=0;i<numEntradas;i++)
	{
		Codigo=("    Difusores[");
		Codigo << i << ("].minimo=") << concreto->motor()->entradas()->minimoEnDifusor(i) << (";");codigoFile->AddLine(Codigo);
		Codigo=("    Difusores[");
		Codigo << i << ("].maximo=") << concreto->motor()->entradas()->maximoEnDifusor(i) << (";");codigoFile->AddLine(Codigo);
		Codigo=("    Difusores[");
		Codigo << i << ("].centro=") << concreto->motor()->entradas()->centroEnDifusor(i) << (";");codigoFile->AddLine(Codigo);
		Codigo=("    Difusores[");
		Codigo << i << ("].puntos=") << concreto->motor()->entradas()->numeroPuntosDifusor(i) << (";");codigoFile->AddLine(Codigo);
		Codigo=("    Difusores[");
		Codigo << i << ("].intervalo=") << concreto->motor()->entradas()->intervaloDifusor(i) << (";");codigoFile->AddLine(Codigo);
		Codigo=("    Difusores[");
		Codigo << i << ("].var1=") << concreto->motor()->entradas()->difusor(i)->var1() << (";");codigoFile->AddLine(Codigo);
		Codigo=("    Difusores[");
		Codigo << i << ("].var2=") << concreto->motor()->entradas()->difusor(i)->var2() << (";");codigoFile->AddLine(Codigo);
		Codigo=("    Difusores[");
		Codigo << i << ("].var3=") << concreto->motor()->entradas()->difusor(i)->var3() << (";");codigoFile->AddLine(Codigo);
		Codigo=("    Difusores[");
		Codigo << i << ("].var4=") << concreto->motor()->entradas()->difusor(i)->var4() << (";\n");codigoFile->AddLine(Codigo);
	}
	Codigo="}";codigoFile->AddLine(Codigo);
	Codigo="void llenarReglas()";codigoFile->AddLine(Codigo);
	Codigo="{";codigoFile->AddLine(Codigo);
	for(int i=0;i<numReglas;i++)
	{
		for(int j=0;j<numEntradas;j++)
		{
			Codigo=("    Reglas[");
			Codigo << i << ("][") << j << ("]=") << concreto->motor()->numConjuntoEntrada(i,j) << (";");codigoFile->AddLine(Codigo);
		}
		for(int j=0;j<numSalidas;j++)
		{
			Codigo=("    Reglas[");
			Codigo << i << ("][") << numEntradas+j << ("]=") << concreto->motor()->numConjuntoSalida(i,j) << (";");codigoFile->AddLine(Codigo);
		}
		Codigo="";codigoFile->AddLine(Codigo);
	}
	Codigo="}\r\n";codigoFile->AddLine(Codigo);
	Codigo="void llenarModificadores()";codigoFile->AddLine(Codigo);
	Codigo="{";codigoFile->AddLine(Codigo);
	for(int i=0;i<numReglas;i++)
	{
		for(int j=0;j<numEntradas;j++)
		{
			Codigo=("    Modificadores[");
			Codigo << i << ("][") << j << ("]=") << concreto->motor()->modificador(i,j) << (";");codigoFile->AddLine(Codigo);
		}
	}
	Codigo="}";codigoFile->AddLine(Codigo);
	Codigo="void llenarCentrosAltura()";codigoFile->AddLine(Codigo);
	Codigo="{";codigoFile->AddLine(Codigo);
	for(int i=0;i<numReglas;i++)
	{
		for(int j=0;j<numSalidas;j++)
		{
			Codigo=("    CentrosAltura[");
			Codigo << i << ("][") << j << ("]=") << concreto->motor()->conjuntoSalida(i,j)->centroAltura() << (";");codigoFile->AddLine(Codigo);
		}
	}
	Codigo="}\r\n";codigoFile->AddLine(Codigo);
	Codigo="double pertenenciaDifusor(int numVar, double x)";codigoFile->AddLine(Codigo);
	Codigo="{";codigoFile->AddLine(Codigo);
	Codigo="    double ux=0;";codigoFile->AddLine(Codigo);
	Codigo="    switch(numVar)";codigoFile->AddLine(Codigo);
	Codigo="    {";codigoFile->AddLine(Codigo);
	for(int i=0;i<numEntradas;i++)
	{
		Codigo=("        case ");
		Codigo << i << (":");codigoFile->AddLine(Codigo);
		Codigo=concreto->motor()->entradas()->difusor(i)->codigo_C(i);codigoFile->AddLine(Codigo);
		Codigo=("            break;");codigoFile->AddLine(Codigo);
 	}
	Codigo="        default:break;";codigoFile->AddLine(Codigo);
	Codigo="    }";codigoFile->AddLine(Codigo);
	Codigo="    return ux;";codigoFile->AddLine(Codigo);
	Codigo="}";codigoFile->AddLine(Codigo);
	Codigo="double pertenenciaVariableEntrada(int numVar,int numConj, double x)";codigoFile->AddLine(Codigo);
	Codigo="{";codigoFile->AddLine(Codigo);
	Codigo="    double ux=0;";codigoFile->AddLine(Codigo);
	Codigo="    switch(numVar)";codigoFile->AddLine(Codigo);
	Codigo="    {";codigoFile->AddLine(Codigo);
	for(int i=0;i<numEntradas;i++)
	{
		Codigo=("        case ");
		Codigo << i << (":");codigoFile->AddLine(Codigo);
		Codigo="            switch(numConj)";codigoFile->AddLine(Codigo);
		Codigo="            {";codigoFile->AddLine(Codigo);
		for(int j=0;j<concreto->motor()->entradas()->numeroConjuntosEnVariable(i);j++)
		{
			Codigo=("            case ");
			Codigo << j << (":");codigoFile->AddLine(Codigo);
			Codigo=concreto->motor()->entradas()->conjuntoEnVariable(i,j)->codigoC();codigoFile->AddLine(Codigo);
			Codigo="                break;";codigoFile->AddLine(Codigo);
		}
		Codigo="            default:break;";codigoFile->AddLine(Codigo);
		Codigo="            }break;";codigoFile->AddLine(Codigo);
	}
	Codigo="        default:break;";codigoFile->AddLine(Codigo);
	Codigo="    }";codigoFile->AddLine(Codigo);
	Codigo="    return ux;";codigoFile->AddLine(Codigo);
	Codigo="}";codigoFile->AddLine(Codigo);
	Codigo="double pertenenciaVariableSalida(int numVar,int numConj, double x)";codigoFile->AddLine(Codigo);
	Codigo="{";codigoFile->AddLine(Codigo);
	Codigo="    double ux=0;";codigoFile->AddLine(Codigo);
	Codigo="    switch(numVar)";codigoFile->AddLine(Codigo);
	Codigo="    {";codigoFile->AddLine(Codigo);
	for(int i=0;i<numSalidas;i++)
	{
		Codigo=("        case ");
		Codigo << i << (":");codigoFile->AddLine(Codigo);
		Codigo="            switch(numConj)";codigoFile->AddLine(Codigo);
		Codigo="            {";codigoFile->AddLine(Codigo);
		for(int j=0;j<concreto->motor()->salidas()->numeroConjuntosEnVariable(i);j++)
		{
			Codigo=("            case ");
			Codigo << j << (":");codigoFile->AddLine(Codigo);
			Codigo=concreto->motor()->salidas()->conjuntoEnVariable(i,j)->codigoC();codigoFile->AddLine(Codigo);
			Codigo="                break;";codigoFile->AddLine(Codigo);
		}
		Codigo="            default:break;";codigoFile->AddLine(Codigo);
		Codigo="            }break;";codigoFile->AddLine(Codigo);
	}
	Codigo="        default:break;";codigoFile->AddLine(Codigo);
	Codigo="    }";codigoFile->AddLine(Codigo);
	Codigo="    return ux;";codigoFile->AddLine(Codigo);
	Codigo="}";codigoFile->AddLine(Codigo);
	Codigo="double Implicacion(double x,double y)";codigoFile->AddLine(Codigo);
	Codigo="{";codigoFile->AddLine(Codigo);
	Codigo="    double rel;";codigoFile->AddLine(Codigo);
	Codigo=concreto->motor()->implicacion()->codigoC();codigoFile->AddLine(Codigo);
	Codigo="    return rel;";codigoFile->AddLine(Codigo);
	Codigo="}\r\n";codigoFile->AddLine(Codigo);
	Codigo="double Composicion(double x,double y)";codigoFile->AddLine(Codigo);
	Codigo="{";codigoFile->AddLine(Codigo);
	Codigo="    double z;";codigoFile->AddLine(Codigo);
	Codigo=concreto->motor()->composicion()->codigoC();codigoFile->AddLine(Codigo);
	Codigo="    return z;";codigoFile->AddLine(Codigo);
	Codigo="}\r\n";codigoFile->AddLine(Codigo);
	Codigo="double Conjuncion(double x,double y)";codigoFile->AddLine(Codigo);
	Codigo="{";codigoFile->AddLine(Codigo);
	Codigo="    double z;";codigoFile->AddLine(Codigo);
	Codigo=concreto->conjuncion()->codigoC();codigoFile->AddLine(Codigo);
	Codigo="    return z;";codigoFile->AddLine(Codigo);
	Codigo="}\r\n";codigoFile->AddLine(Codigo);
	Codigo="double And(double x,double y)";codigoFile->AddLine(Codigo);
	Codigo="{";codigoFile->AddLine(Codigo);
	Codigo="    double z;";codigoFile->AddLine(Codigo);
	Codigo=concreto->motor()->and_()->codigoC();codigoFile->AddLine(Codigo);
	Codigo="    return z;";codigoFile->AddLine(Codigo);
	Codigo="}\r\n";codigoFile->AddLine(Codigo);

	if(codigoFile->Write())
	{
		wxMessageBox(_("The file has been created"),("Information"));
	}else
	{
		wxMessageBox(_("The file could not be opened"),("¡Warning!"));
	}
}


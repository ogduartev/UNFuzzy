#include "red.h"

red::red()
{
	crearRedMinima();
	nombre=_("Sin nombre");
	descripcion="";
}

void red::crearRedMinima()
{
	eliminarCapas();
	capa* C1=new capa();
	capa* C2=new capa();

	nodo* N11=new nodo(2,1);
	nodo* N12=new nodo(2,1);
	nodo* N21=new nodo(2,1);

	Capas.Add(C1);
	Capas.Add(C2);

	C1->nodos()->Add(N11);
	C1->nodos()->Add(N12);
	C2->nodos()->Add(N21);

  conectar(0,0,0,1,0,0);
  conectar(0,1,0,1,0,1);

  valorEntrada(0,0,0.2);
  valorEntrada(0,1,0.2);
  valorEntrada(1,0,-0.2);
  valorEntrada(1,1,-0.2);

  calcularRed();
}

red::~red()
{
}

bool red::conectar(int capa1, int nodo1, int pin1,int capa2, int nodo2, int pin2)
{
	if(capa1<0)                            {return false;}
	if(capa1!=(capa2-1))                   {return false;}
	if(!buscarPinSalida(capa1,nodo1,pin1)) {return false;}
	if(!buscarPinEntrada(capa2,nodo2,pin2)){return false;}
	pin* ptr1;
	pin* ptr2;
	ptr1=Capas.dato(capa1)->nodos()->dato(nodo1)->salidas() ->dato(pin1);
	ptr2=Capas.dato(capa2)->nodos()->dato(nodo2)->entradas()->dato(pin2);
	ptr2->contacto(ptr1);
}

bool red::buscarCapa(int numCapa)
{
	if(numCapa>=Capas.GetItemsInContainer()){return false;}
	return true;
}

bool red::buscarNodo(int numCapa, int numNodo)
{
	if(numCapa>=Capas.GetItemsInContainer())                                                   {return false;}
	if(numNodo>=Capas.dato(numCapa)->nodos()->GetItemsInContainer())                           {return false;}
	return true;
}

bool red::buscarPinEntrada(int numCapa, int numNodo, int numPin)
{
	if(numCapa>=Capas.GetItemsInContainer())                                                   {return false;}
	if(numNodo>=Capas.dato(numCapa)->nodos()->GetItemsInContainer())                           {return false;}
	if(numPin >=Capas.dato(numCapa)->nodos()->dato(numNodo)->entradas()->GetItemsInContainer()){return false;}
	return true;
}

bool red::buscarPinSalida(int numCapa, int numNodo, int numPin)
{
	if(numCapa>=Capas.GetItemsInContainer())                                                   {return false;}
	if(numNodo>=Capas.dato(numCapa)->nodos()->GetItemsInContainer())                           {return false;}
	if(numPin >=Capas.dato(numCapa)->nodos()->dato(numNodo)->salidas()->GetItemsInContainer()){return false;}
	return true;
}

float red::valorPinEntrada(int numCapa, int numNodo, int numPin)
{
	float V=0.0;
	if(!buscarPinEntrada(numCapa,numNodo,numPin))
	{
		return V;
	}
	V=Capas.dato(numCapa)->nodos()->dato(numNodo)->entradas()->dato(numPin)->valor();
	return V;
}

float red::valorPinSalida(int numCapa, int numNodo, int numPin)
{
	float V=0.0;
	if(!buscarPinSalida(numCapa,numNodo,numPin))
	{
		return V;
	}
	V=Capas.dato(numCapa)->nodos()->dato(numNodo)->salidas()->dato(numPin)->valor();
	return V;
}

void red::calcularRed()
{
	for(int numCapa=0;numCapa<Capas.GetItemsInContainer();numCapa++)
	{
		for(int numNodo=0;numNodo<Capas.dato(numCapa)->nodos()->GetItemsInContainer();numNodo++)
		{
		  Capas.dato(numCapa)->nodos()->dato(numNodo)->calcularNodo();
		}
	}
}

void red::valorEntrada(int numNodo, int numPin, float Valor)
{
  if(!buscarPinEntrada(0,numNodo,numPin))
	{
		return;
	}
	Capas.dato(0)->nodos()->dato(numNodo)->entradas()->dato(numPin)->valor(Valor);
}

nodo* red::ptrNodo(int numCapa, int numNodo)
{
	if(!buscarNodo(numCapa,numNodo))
	{
		return NULL;
	}
	return Capas.dato(numCapa)->nodos()->dato(numNodo);
}

pin* red::ptrPinEntrada(int numCapa, int numNodo, int numPin)
{
	if(!buscarPinEntrada(numCapa,numNodo,numPin)) {return NULL;}
	pin* Pin=capas()->dato(numCapa)->nodos()->dato(numNodo)->entradas()->dato(numPin);
	return Pin;
}

pin* red::ptrPinSalida(int numCapa, int numNodo, int numPin)
{
	if(!buscarPinSalida(numCapa,numNodo,numPin)) {return NULL;}
	pin* Pin=capas()->dato(numCapa)->nodos()->dato(numNodo)->salidas()->dato(numPin);
	return Pin;
}

void red::desconectarSalida(int numCapa, int numNodo, int numPin)
{
	pin* PinSalida=ptrPinSalida(numCapa, numNodo, numPin);
	if(!PinSalida){return;}
	for(int i=0;i<capas()->GetItemsInContainer();i++)
	{
		for(int j=0;j<capas()->dato(i)->nodos()->GetItemsInContainer();j++)
		{
			for(int k=0;k<capas()->dato(i)->nodos()->dato(j)->entradas()->GetItemsInContainer();k++)
			{
			  pin* PinEntrada=ptrPinEntrada(i, j, k);
			  if(PinEntrada->contacto() == PinSalida)
				{
					PinEntrada->contacto(NULL);
				}
			}
		}
	}
}

void red::desconectarEntradasNodo(int numCapa, int numNodo)
{
	nodo* Nodo=ptrNodo(numCapa, numNodo);
	if(!Nodo){return;}
	for(int i=0;i<Nodo->entradas()->GetItemsInContainer();i++)
	{
		Nodo->entradas()->dato(i)->contacto(NULL);
	}
}

void red::desconectarSalidasNodo(int numCapa, int numNodo)
{
	nodo* Nodo=ptrNodo(numCapa, numNodo);
	if(!Nodo){return;}
	for(int i=0;i<Nodo->salidas()->GetItemsInContainer();i++)
	{
		desconectarSalida(numCapa, numNodo, i);
	}
}

void red::eliminarNodo(int numCapa, int numNodo)
{
	if(!buscarNodo(numCapa, numNodo)){return;}
	desconectarEntradasNodo(numCapa, numNodo);
	desconectarSalidasNodo(numCapa, numNodo);
	capas()->dato(numCapa)->nodos()->Destroy(numNodo);
}

void red::eliminarCapa(int numCapa)
{
	if(!buscarCapa(numCapa)){return;}
	while(capas()->dato(numCapa)->nodos()->GetItemsInContainer() > 0)
	{
		eliminarNodo(numCapa, 0);
	}
	capas()->Destroy(numCapa);
}

void red::eliminarCapas()
{
	while(capas()->GetItemsInContainer() > 0)
	{
		eliminarCapa(0);
	}
}

void red::adicionarCapa()
{
	capa* C=new capa();
	Capas.Add(C);
}

void red::adicionarNodo(int numCapa)
{
	if(!buscarCapa(numCapa)){return;}
	nodo* N=new nodo(1,1);
	capas()->dato(numCapa)->nodos()->Add(N);
}

bool red::buscarPinEntrada(pin* Pin, int *numCapa, int *numNodo, int *numPin)
{
	if(!Pin){return false;}
	for(int i=0;i<capas()->GetItemsInContainer();i++)
	{
		for(int j=0;j<capas()->dato(i)->nodos()->GetItemsInContainer();j++)
		{
			for(int k=0;k<capas()->dato(i)->nodos()->dato(j)->entradas()->GetItemsInContainer();k++)
			{
			  pin* PinEntrada=ptrPinEntrada(i, j, k);
			  if(PinEntrada == Pin)
				{
					*numCapa=i;
					*numNodo=j;
					*numPin=k;
					return true;
				}
			}
		}
	}
	return false;
}

bool red::buscarPinSalida(pin* Pin, int *numCapa, int *numNodo, int *numPin)
{
	if(!Pin){return false;}
	for(int i=0;i<capas()->GetItemsInContainer();i++)
	{
		for(int j=0;j<capas()->dato(i)->nodos()->GetItemsInContainer();j++)
		{
			for(int k=0;k<capas()->dato(i)->nodos()->dato(j)->entradas()->GetItemsInContainer();k++)
			{
			  pin* PinEntrada=ptrPinSalida(i, j, k);
			  if(PinEntrada == Pin)
				{
					*numCapa=i;
					*numNodo=j;
					*numPin=k;
					return true;
				}
			}
		}
	}
	return false;
}

int red::numeroEntradas()
{
	int num=0;
	int numCapa=0;
	for(int numNodo=0;numNodo < capas()->dato(numCapa)->nodos()->GetItemsInContainer();numNodo++)
	{
		num+=capas()->dato(numCapa)->nodos()->dato(numNodo)->sld()->entradas->numeroVariables();
	}
	return num;
}

int red::numeroSalidas()
{
	int num=0;
	int numCapa=capas()->GetItemsInContainer()-1;
	for(int numNodo=0;numNodo < capas()->dato(numCapa)->nodos()->GetItemsInContainer();numNodo++)
	{
		num+=capas()->dato(numCapa)->nodos()->dato(numNodo)->sld()->salidas->numeroVariables();
	}
	return num;
}

Variable* red::variableEntrada(int i)
{
	int cnt=0;
	int numCapa=0;
	for(int numNodo=0;numNodo < capas()->dato(numCapa)->nodos()->GetItemsInContainer();numNodo++)
	{
		for(int numPin=0; numPin < capas()->dato(numCapa)->nodos()->dato(numNodo)->entradas()->GetItemsInContainer(); numPin++)
		{
			if(cnt==i)
			{
				return capas()->dato(numCapa)->nodos()->dato(numNodo)->sld()->entradas->variable(numPin);
			}
			cnt++;
		}
	}
	return NULL;
}

Variable* red::variableSalida(int i)
{
	int cnt=0;
	int numCapa=capas()->GetItemsInContainer()-1;
	for(int numNodo=0;numNodo < capas()->dato(numCapa)->nodos()->GetItemsInContainer();numNodo++)
	{
		for(int numPin=0; numPin < capas()->dato(numCapa)->nodos()->dato(numNodo)->sld()->salidas->numeroVariables(); numPin++)
		{
			if(cnt==i)
			{
				return capas()->dato(numCapa)->nodos()->dato(numNodo)->sld()->salidas->variable(numPin);
			}
			cnt++;
		}
	}
	return NULL;
}

void red::asignarEntradas(float* entra)
{
	int cnt=0;
	int numCapa=0;
	for(int numNodo=0;numNodo < capas()->dato(numCapa)->nodos()->GetItemsInContainer();numNodo++)
	{
		for(int numPin=0; numPin < capas()->dato(numCapa)->nodos()->dato(numNodo)->entradas()->GetItemsInContainer(); numPin++)
		{
			valorEntrada(numNodo, numPin, entra[cnt]);
			cnt++;
		}
	}
}

void red::leerSalidas(float* sale)
{
	int cnt=0;
	int numCapa=capas()->GetItemsInContainer()-1;
	for(int numNodo=0;numNodo < capas()->dato(numCapa)->nodos()->GetItemsInContainer();numNodo++)
	{
		for(int numPin=0; numPin < capas()->dato(numCapa)->nodos()->dato(numNodo)->entradas()->GetItemsInContainer(); numPin++)
		{
			sale[cnt]=valorPinSalida(numCapa, numNodo,numPin);
			cnt++;
		}
	}
}

void red::calcular(float* entra, float* sale)
{
	asignarEntradas(entra);
	calcularRed();
	leerSalidas(sale);
}

void red::generarCodigo(wxString nombreArchivo,wxString nombreClase)
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
	}
}

void red::generarCodigoCPP(wxString nombreArchivo,wxString nombreClase)
{
	wxTextFile codigoFile(nombreArchivo);
	codigoFile.Clear();

	generarCodigoCPPEncabezado(&codigoFile);
	generarCodigoCPPsld       (&codigoFile);
	generarCodigoCPPClase     (&codigoFile, nombreClase);
	generarCodigoCPPMain      (&codigoFile, nombreClase);

	if(codigoFile.Write())
	{
		wxMessageBox(_("Se ha creado el archivo"),_("Información"));
	}else
	{
		wxMessageBox(_("No se pudo abrir el archivo"),_("¡Atención!"));
	}
}

void red::generarCodigoCPPEncabezado(wxTextFile* codigoFile)
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
	Codigo="";codigoFile->AddLine(Codigo);
	Codigo=("#ifndef __IOSTREAM_H");codigoFile->AddLine(Codigo);
	Codigo=("#include <iostream>");codigoFile->AddLine(Codigo);
	Codigo=("#endif");codigoFile->AddLine(Codigo);
	Codigo=("");codigoFile->AddLine(Codigo);
	Codigo=("using namespace std;");codigoFile->AddLine(Codigo);
	Codigo=("	");codigoFile->AddLine(Codigo);
	Codigo=("#ifndef __FUZZY_H");codigoFile->AddLine(Codigo);
	Codigo=("#include \"fuzzy.h\"");codigoFile->AddLine(Codigo);
	Codigo=("#endif\n");codigoFile->AddLine(Codigo);
}

void red::generarCodigoCPPsld(wxTextFile* codigoFile)
{
	for(int numCapa=0; numCapa < capas()->GetItemsInContainer(); numCapa++)
	{
		for(int numNodo=0; numNodo < capas()->dato(numCapa)->nodos()->GetItemsInContainer(); numNodo++)
		{
			wxString nombreClase = ("SLD_");
			nombreClase << (numCapa+1) << ("_") << (numNodo+1);

			nodo* Nodo=ptrNodo(numCapa, numNodo);
			Nodo->sld()->generarCodigoCPPClase(codigoFile, nombreClase);
		}
	}
}

void red::generarCodigoCPPClase(wxTextFile* codigoFile, wxString nombreClase)
{
	wxString Codigo=("");
	char cad[2000];

	Codigo=("class ");
	Codigo << nombreClase << (":public red");codigoFile->AddLine(Codigo);
	Codigo=("{");codigoFile->AddLine(Codigo);
	Codigo=("public:");codigoFile->AddLine(Codigo);
	Codigo=("    ");
	Codigo << nombreClase << ("();");codigoFile->AddLine(Codigo);
	Codigo=("    ~");
	Codigo << nombreClase << ("();");codigoFile->AddLine(Codigo);
	Codigo=("protected:");codigoFile->AddLine(Codigo);
	Codigo=("};\n");codigoFile->AddLine(Codigo);
	Codigo=nombreClase;
	Codigo << ("::") << nombreClase << ("()");codigoFile->AddLine(Codigo);
	Codigo=("{");codigoFile->AddLine(Codigo);
	for(int numCapa=0; numCapa < capas()->GetItemsInContainer(); numCapa++)
	{
		Codigo=("  capa* Capa_");
		Codigo << (numCapa+1) << (";"); codigoFile->AddLine(Codigo);
		Codigo=("  Capa_");
		Codigo << (numCapa+1) << ("= new capa();"); codigoFile->AddLine(Codigo);
		for(int numNodo=0; numNodo < capas()->dato(numCapa)->nodos()->GetItemsInContainer(); numNodo++)
		{
			wxString ext="_";
			ext << (numCapa+1) << ("_")<< (numNodo+1);
			Codigo=("\n    nodo* Nodo");
			Codigo << ext << (";"); codigoFile->AddLine(Codigo);
			Codigo=("    SLD");
			Codigo << ext << ("* miSLD") << ext << (";"); codigoFile->AddLine(Codigo);
			Codigo=("    Nodo");
			Codigo << ext << ("= new nodo();"); codigoFile->AddLine(Codigo);
			Codigo=("    miSLD");
			Codigo << ext << ("= new SLD") << ext << ("();"); codigoFile->AddLine(Codigo);
			Codigo=("    Nodo");
			Codigo << ext << ("->sld(miSLD") << ext << (");"); codigoFile->AddLine(Codigo);
			Codigo=("    Nodo");
			Codigo << ext << ("->ajustarPinesAsld();"); codigoFile->AddLine(Codigo);
			Codigo=("    Capa_");
			Codigo << (numCapa+1) << ("->nodos()->Add(Nodo") << ext << (");"); codigoFile->AddLine(Codigo);

		}
		Codigo=("  capas()->Add(Capa_");
		Codigo << (numCapa+1) << (");\n"); codigoFile->AddLine(Codigo);
	}

	for(int numCapa=0; numCapa < capas()->GetItemsInContainer(); numCapa++)
	{
		for(int numNodo=0; numNodo < capas()->dato(numCapa)->nodos()->GetItemsInContainer(); numNodo++)
		{
			nodo* Nodo=ptrNodo(numCapa, numNodo);
			for(int numPin=0;numPin < Nodo->entradas()->GetItemsInContainer();numPin++)
			{
				pin* PinEntra=NULL;
				PinEntra=Nodo->entradas()->dato(numPin);
				pin* PinSale=NULL;
				if(PinEntra)
				{
					PinSale=PinEntra->contacto();
					if(PinSale)
					{
						int capaEntra=-1;
						int nodoEntra=-1;
						int pinEntra=-1;
						int capaSale=-1;
						int nodoSale=-1;
						int pinSale=-1;

						buscarPinEntrada(PinEntra, &capaEntra, &nodoEntra, &pinEntra);
						buscarPinSalida (PinSale,  &capaSale,  &nodoSale,  &pinSale );

						Codigo=("  conectar(");
						Codigo << capaSale  << (",");
						Codigo << nodoSale  << (",");
						Codigo << pinSale   << (",");
						Codigo << capaEntra << (",");
						Codigo << nodoEntra << (",");
						Codigo << pinEntra  << (");");
						codigoFile->AddLine(Codigo);
					}
				}
			}
		}
	}

	Codigo=("}\n");codigoFile->AddLine(Codigo);
	Codigo=nombreClase;
	Codigo << ("::~") << nombreClase << ("()");codigoFile->AddLine(Codigo);
	Codigo=("{");codigoFile->AddLine(Codigo);
	Codigo=("}\n");codigoFile->AddLine(Codigo);
}

void red::generarCodigoCPPMain(wxTextFile* codigoFile,wxString nombreClase)
{
	wxString Codigo=("");
	char cad[2000];

	Codigo=("int main()");codigoFile->AddLine(Codigo);
	Codigo=("{");codigoFile->AddLine(Codigo);
	Codigo=("    float *entra;");codigoFile->AddLine(Codigo);
	Codigo=("    float *sale;");codigoFile->AddLine(Codigo);
	Codigo=("    ");
	Codigo << nombreClase << (" *Red;");codigoFile->AddLine(Codigo);
	Codigo=("    int NumeroEntradas;");codigoFile->AddLine(Codigo);
	Codigo=("    int NumeroSalidas;");codigoFile->AddLine(Codigo);
	Codigo=("    Red=new ");
	Codigo << nombreClase << ("();");codigoFile->AddLine(Codigo);
	Codigo=("    NumeroEntradas=Red->numeroEntradas();");codigoFile->AddLine(Codigo);
	Codigo=("    NumeroSalidas=Red->numeroSalidas();");codigoFile->AddLine(Codigo);
	Codigo=("    entra=new float[NumeroEntradas];");codigoFile->AddLine(Codigo);
	Codigo=("    sale=new float[NumeroSalidas];");codigoFile->AddLine(Codigo);
	Codigo=("    int i;");codigoFile->AddLine(Codigo);
	Codigo=("    char q='s';");codigoFile->AddLine(Codigo);
	Codigo=("    while(q=='s')");codigoFile->AddLine(Codigo);
	Codigo=("    {");codigoFile->AddLine(Codigo);
	Codigo=("        for(i=0;i<NumeroEntradas;i++)");codigoFile->AddLine(Codigo);
	Codigo=("        {");codigoFile->AddLine(Codigo);
	Codigo=("            cout << \"Entrada \" << (i+1) << \" : \";");codigoFile->AddLine(Codigo);
	Codigo=("            cin >> entra[i];");codigoFile->AddLine(Codigo);
	Codigo=("        }");codigoFile->AddLine(Codigo);
	Codigo=("        Red->calcular(entra,sale);");codigoFile->AddLine(Codigo);
	Codigo=("        for(i=0;i<NumeroSalidas;i++)");codigoFile->AddLine(Codigo);
	Codigo=("        {");codigoFile->AddLine(Codigo);
	Codigo=("            cout << \"Salida \" << (i+1) << \" : \";");codigoFile->AddLine(Codigo);
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
	Codigo=("}\n");codigoFile->AddLine(Codigo);
}


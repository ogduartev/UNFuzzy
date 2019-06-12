#include "archivadorRed.h"

archivadorRed::archivadorRed(red *r)
{
	Red=r;
	doc.SetFileEncoding("UTF-8");
}

archivadorRed::~archivadorRed()
{
	//dtor
}

void archivadorRed::guardar(wxString fileName)
{

	wxXmlNode* Node;
	Node=new wxXmlNode(NULL,wxXML_ELEMENT_NODE,_T("RED"));
	Node->AddAttribute(_T("Nombre")      , Red->nombre);
	Node->AddAttribute(_T("Descripción") , Red->descripcion);
	doc.SetRoot(Node);

	guardarEnlaces(Node);
	guardarCapas(Node);

	doc.Save(fileName);
}

void archivadorRed::guardarCapas(wxXmlNode* parent)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,_T("CAPAS"));
	for(int i = Red->capas()->GetItemsInContainer()-1; i >= 0 ; i--)
	{
		capa *Capa=Red->capas()->dato(i);
		guardarCapa(NodeA,Capa);
	}
}

void archivadorRed::guardarCapa(wxXmlNode* parent, capa* Capa)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,_T("CAPA"));

	for(int j=Capa->nodos()->GetItemsInContainer()-1; j>=0 ;j--)
	{
	  nodo *Nodo=Capa->nodos()->dato(j);
	  guardarNodo(NodeA,Nodo);
	}
}

void archivadorRed::guardarNodo(wxXmlNode* parent, nodo *Nodo)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,_T("NODO"));
	NodeA->AddAttribute(_T("Entradas")      , wxString::Format("%d",Nodo->sld()->entradas->numeroVariables()));
	NodeA->AddAttribute(_T("Salidas")       , wxString::Format("%d",Nodo->sld()->salidas->numeroVariables()));

	guardarSLD(NodeA, Nodo->sld());
}

void archivadorRed::guardarSLD(wxXmlNode* parent, SistemaLogicaDifusa *SLD)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,_T("SLD"));

	Archivador archSLD(SLD);
	archSLD.guardarSLD(NodeA);
}

void archivadorRed::guardarEnlaces (wxXmlNode* parent)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,_T("ENLACES"));

	for(int numCapa=0;numCapa < Red->capas()->GetItemsInContainer(); numCapa++)
	{
		for(int numNodo=0; numNodo < Red->capas()->dato(numCapa)->nodos()->GetItemsInContainer();numNodo++)
		{
			nodo *Nodo=Red->ptrNodo(numCapa,numNodo);
			for(int numPin=0; numPin < Nodo->entradas()->GetItemsInContainer();numPin++)
			{
				pin* PinEntra=NULL;
				PinEntra=Nodo->entradas()->dato(numPin);
				pin* PinSale=NULL;
				if(PinEntra)
				{
					PinSale=PinEntra->contacto();
					if(PinSale)
					{
						guardarEnlace(NodeA,PinEntra,PinSale);
					}
				}
			}
		}
	}
}

void archivadorRed::guardarEnlace  (wxXmlNode* parent,pin* PinEntra, pin* PinSale)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,_T("ENLACE"));
	int capaEntra=-1;
	int nodoEntra=-1;
	int pinEntra=-1;
	int capaSale=-1;
	int nodoSale=-1;
	int pinSale=-1;

	Red->buscarPinEntrada(PinEntra, &capaEntra, &nodoEntra, &pinEntra);
	Red->buscarPinSalida (PinSale,  &capaSale,  &nodoSale,  &pinSale );

	NodeA->AddAttribute(_T("CapaEntrada")      , wxString::Format("%d",capaEntra));
	NodeA->AddAttribute(_T("NodoEntrada")      , wxString::Format("%d",nodoEntra));
	NodeA->AddAttribute(_T("PinEntrada")       , wxString::Format("%d",pinEntra));
	NodeA->AddAttribute(_T("CapaSalida")       , wxString::Format("%d",capaSale));
	NodeA->AddAttribute(_T("NodoSalida")       , wxString::Format("%d",nodoSale));
	NodeA->AddAttribute(_T("PinSalida")        , wxString::Format("%d",pinSale));
}

void archivadorRed::leer(wxString fileName)
{
	doc.Load(fileName);
	if(!doc.IsOk())
	{
		wxMessageBox(_T("No se pudo cargar el archivo"),_T("¡Atención!"));
	}

	Red->eliminarCapas();

	wxXmlNode *Node=doc.GetRoot();
	Red->nombre=Node->GetAttribute(_T("Nombre"));
	Red->descripcion=Node->GetAttribute(_T("Descripción"));

	wxXmlNode *NodeA=Node->GetChildren();
	while(NodeA)
	{
		if(NodeA->GetName()==_T("CAPAS"))
		{
			leerCapas(NodeA);
		}if(NodeA->GetName()==_T("ENLACES"))
		{
			leerEnlaces(NodeA);
		}
		NodeA=NodeA->GetNext();
	}
}

void archivadorRed::leerCapas   (wxXmlNode* parent)
{
	wxXmlNode *NodeA=parent->GetChildren();
	while(NodeA)
	{
		if(NodeA->GetName()==_T("CAPA"))
		{
			capa *Capa;
			Capa=new capa();
			leerCapa(NodeA,Capa);
			Red->capas()->Add(Capa);
		}
		NodeA=NodeA->GetNext();
	}
}

void archivadorRed::leerCapa(wxXmlNode* parent, capa *Capa)
{
	wxXmlNode *NodeA=parent->GetChildren();
	while(NodeA)
	{
		if(NodeA->GetName()==_T("NODO"))
		{
			long numEnt,numSal;
			NodeA->GetAttribute(_T("Entradas")).ToLong(&numEnt);
			NodeA->GetAttribute(_T("Salidas")).ToLong(&numSal);
			nodo *Nodo;
			Nodo=new nodo((int)numEnt,(int)numSal);
			leerNodo(NodeA,Nodo);
			Capa->nodos()->Add(Nodo);
		}
		NodeA=NodeA->GetNext();
	}
}

void archivadorRed::leerNodo(wxXmlNode* parent, nodo *Nodo)
{
	wxXmlNode *NodeA=parent->GetChildren();

	if(NodeA->GetName()==_T("SLD"))
	{
		leerSLD(NodeA, Nodo->sld());
	}
}

void archivadorRed::leerSLD(wxXmlNode* parent, SistemaLogicaDifusa *SLD)
{
	Archivador archSLD(SLD);
	archSLD.leerSLD(parent);
}

void archivadorRed::leerEnlaces    (wxXmlNode* parent)
{
	wxXmlNode *NodeA=parent->GetChildren();
	while(NodeA)
	{
		if(NodeA->GetName()==_T("ENLACE"))
		{
			leerEnlace(NodeA);
		}
		NodeA=NodeA->GetNext();
	}
}

void archivadorRed::leerEnlace     (wxXmlNode* parent)
{
	long capaEntra=-1;
	long nodoEntra=-1;
	long pinEntra=-1;
	long capaSale=-1;
	long nodoSale=-1;
	long pinSale=-1;

	parent->GetAttribute(_T("CapaEntrada")).ToLong(&capaEntra);
	parent->GetAttribute(_T("NodoEntrada")).ToLong(&nodoEntra);
	parent->GetAttribute(_T("PinEntrada") ).ToLong(&pinEntra);
	parent->GetAttribute(_T("CapaSalida") ).ToLong(&capaSale);
	parent->GetAttribute(_T("NodoSalida") ).ToLong(&nodoSale);
	parent->GetAttribute(_T("PinSalida")  ).ToLong(&pinSale);

	if (capaEntra>=0 and nodoEntra>=0 and pinEntra>=0 and
			capaSale>=0  and nodoSale>=0  and pinSale>=0 )
	{
		pin* PinEntra=NULL;
		pin* PinSale=NULL;
		PinEntra=Red->ptrPinEntrada(capaEntra, nodoEntra, pinEntra);
		PinSale =Red->ptrPinSalida (capaSale,  nodoSale,  pinSale);
		if(PinEntra and PinSale)
		{
			PinEntra->contacto(PinSale);
		}
	}
}

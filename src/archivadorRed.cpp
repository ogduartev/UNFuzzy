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
	Node=new wxXmlNode(NULL,wxXML_ELEMENT_NODE,("NETWORK"));
	Node->AddAttribute(("Name")      , Red->nombre);
	Node->AddAttribute(("Description") , Red->descripcion);
	doc.SetRoot(Node);

	guardarEnlaces(Node);
	guardarCapas(Node);

	doc.Save(fileName);
}

void archivadorRed::guardarCapas(wxXmlNode* parent)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,("LAYERS"));
	for(int i = Red->capas()->GetItemsInContainer()-1; i >= 0 ; i--)
	{
		capa *Capa=Red->capas()->dato(i);
		guardarCapa(NodeA,Capa);
	}
}

void archivadorRed::guardarCapa(wxXmlNode* parent, capa* Capa)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,("LAYER"));

	for(int j=Capa->nodos()->GetItemsInContainer()-1; j>=0 ;j--)
	{
	  nodo *Nodo=Capa->nodos()->dato(j);
	  guardarNodo(NodeA,Nodo);
	}
}

void archivadorRed::guardarNodo(wxXmlNode* parent, nodo *Nodo)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,("NODE"));
	NodeA->AddAttribute(("Inputs")      , wxString::Format("%d",Nodo->sld()->entradas->numeroVariables()));
	NodeA->AddAttribute(("Outputs")     , wxString::Format("%d",Nodo->sld()->salidas->numeroVariables()));

	guardarSLD(NodeA, Nodo->sld());
}

void archivadorRed::guardarSLD(wxXmlNode* parent, SistemaLogicaDifusa *SLD)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,("FLS"));

	Archivador archSLD(SLD);
	archSLD.guardarSLD(NodeA);
}

void archivadorRed::guardarEnlaces (wxXmlNode* parent)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,("LINKS"));

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
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,("LINK"));
	int capaEntra=-1;
	int nodoEntra=-1;
	int pinEntra=-1;
	int capaSale=-1;
	int nodoSale=-1;
	int pinSale=-1;

	Red->buscarPinEntrada(PinEntra, &capaEntra, &nodoEntra, &pinEntra);
	Red->buscarPinSalida (PinSale,  &capaSale,  &nodoSale,  &pinSale );

	NodeA->AddAttribute(("InputLayer")     , wxString::Format("%d",capaEntra));
	NodeA->AddAttribute(("InputNode")      , wxString::Format("%d",nodoEntra));
	NodeA->AddAttribute(("InputTerminal")  , wxString::Format("%d",pinEntra));
	NodeA->AddAttribute(("OutputLayer")    , wxString::Format("%d",capaSale));
	NodeA->AddAttribute(("OutputNode")     , wxString::Format("%d",nodoSale));
	NodeA->AddAttribute(("OutputTerminal") , wxString::Format("%d",pinSale));
}

void archivadorRed::leer(wxString fileName)
{
	doc.Load(fileName);
	if(!doc.IsOk())
	{
		wxMessageBox(_("The file coud not be loaded"),_("¡Warning!"));
	}

	Red->eliminarCapas();

	wxXmlNode *Node=doc.GetRoot();
	Red->nombre=Node->GetAttribute(("Name"));
	Red->descripcion=Node->GetAttribute(("Description"));

	wxXmlNode *NodeA=Node->GetChildren();
	while(NodeA)
	{
		if(NodeA->GetName()==("LAYERS"))
		{
			leerCapas(NodeA);
		}if(NodeA->GetName()==("LINKS"))
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
		if(NodeA->GetName()==("LAYER"))
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
		if(NodeA->GetName()==("NODE"))
		{
			long numEnt,numSal;
			NodeA->GetAttribute(("Inputs")).ToLong(&numEnt);
			NodeA->GetAttribute(("Outputs")).ToLong(&numSal);
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

	if(NodeA->GetName()==("FLS"))
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
		if(NodeA->GetName()==("LINK"))
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

	parent->GetAttribute(("InputLayer"    )).ToLong(&capaEntra);
	parent->GetAttribute(("InputNode"     )).ToLong(&nodoEntra);
	parent->GetAttribute(("InputTerminal" )).ToLong(&pinEntra);
	parent->GetAttribute(("OutputLayer"   )).ToLong(&capaSale);
	parent->GetAttribute(("OutputNode"    )).ToLong(&nodoSale);
	parent->GetAttribute(("OutputTerminal")).ToLong(&pinSale);

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

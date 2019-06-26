#include "Archivador.h"

Archivador::Archivador(SistemaLogicaDifusa* sld)
{
	SLD=sld;
	doc.SetFileEncoding("UTF-8");
}

Archivador::~Archivador()
{
	//dtor
}

void Archivador::guardar(wxString fileName)
{

	wxXmlNode* Node;
	Node=new wxXmlNode(NULL,wxXML_ELEMENT_NODE,("FLS"));
	doc.SetRoot(Node);

	guardarSLD(Node);

	doc.Save(fileName);
}

void Archivador::guardarSLD(wxXmlNode* parent)
{
	parent->AddAttribute(("Name")      , SLD->nombre);
	parent->AddAttribute(("Description") , SLD->descripcion);

	guardarConcrecion(parent);
	guardarMaquina   (parent);
	guardarSalidas   (parent);
	guardarEntradas  (parent);
}

void Archivador::guardarEntradas(wxXmlNode* parent)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,("INPUTS"));
	for(int i = SLD->entradas->numeroVariables()-1; i >= 0 ; i--)
	{
		Variable *var=SLD->entradas->variable(i);
		guardarVariable(NodeA,var,true);
	}
}

void Archivador::guardarSalidas(wxXmlNode* parent)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,("OUTPUTS"));
	for(int i = SLD->salidas->numeroVariables()-1; i >= 0 ; i--)
	{
		Variable *var=SLD->salidas->variable(i);
		guardarVariable(NodeA,var,false);
	}
}

void Archivador::guardarVariable(wxXmlNode* parent, Variable *var, bool flagDifusor)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,("VARIABLE"));
	NodeA->AddAttribute(("Name")      , var->nombreVariable());
	NodeA->AddAttribute(("Minimum")      , wxString::Format(("%f"),var->rangoMinimo()));
	NodeA->AddAttribute(("Maximum")      , wxString::Format(("%f"),var->rangoMaximo()));
	NodeA->AddAttribute(("Intervals")  , wxString::Format(("%d"),var->numeroIntervalos()));

	for(int j=var->numeroConjuntos()-1; j>=0 ;j--)
	{
	  ConjuntoDifuso *cd=var->conjunto(j);
	  guardarConjunto(NodeA,cd);
	}

	if(flagDifusor)
	{
		Difusor *dif=var->difusorEntrada();
		guardarDifusor(NodeA, dif);
	}

}

void Archivador::guardarDifusor(wxXmlNode* parent, Difusor *dif)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,("FUZZYFIER"));
	NodeA->AddAttribute(("Type")        ,  wxString::Format(("%d"),dif->identificador()));
	NodeA->AddAttribute(("Points")      ,  wxString::Format(("%d"),dif->numeroPuntos()));
	NodeA->AddAttribute(("Center")      ,  wxString::Format(("%f"),dif->centro()));

	double puntos[dif->numeroPuntosClaves()];
	dif->puntosClaves(puntos);
	for(int i=dif->numeroPuntosClaves()-1;i>=0;i--)
	{
		wxXmlNode* NodeB;
		NodeB=new wxXmlNode(NodeA,wxXML_ELEMENT_NODE,("POINT"));
		NodeB->AddAttribute(("X")      , wxString::Format(("%f"),puntos[i]));
	}
}

void Archivador::guardarConjunto(wxXmlNode* parent, ConjuntoDifuso *cd)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,("LABEL"));
	NodeA->AddAttribute(("Name")      , cd->nombre());
	NodeA->AddAttribute(("Type")        ,  wxString::Format(("%d"),cd->identificador()));

	double puntos[cd->numeroPuntosClaves()];
	cd->puntosClaves(puntos);
	for(int i=cd->numeroPuntosClaves()-1;i>=0;i--)
	{
		wxXmlNode* NodeB;
		NodeB=new wxXmlNode(NodeA,wxXML_ELEMENT_NODE,("POINT"));
		NodeB->AddAttribute(("X")      , wxString::Format(("%f"),puntos[i]));
	}
}

void Archivador::guardarMaquina (wxXmlNode* parent)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,("ENGINE"));

	guardarBase(NodeA);
	guardarNorma(NodeA,SLD->motor->and_(),("AND"));
	guardarNorma(NodeA,SLD->motor->composicion(),("COMPOSITION"));
	guardarImplicacion(NodeA,SLD->motor->implicacion());
}

void Archivador::guardarBase    (wxXmlNode* parent)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,("BASE"));
	NodeA->AddAttribute(("Inputs")    , wxString::Format(("%d"),SLD->entradas->numeroVariables()));
	NodeA->AddAttribute(("Outputs")     , wxString::Format(("%d"),SLD->salidas->numeroVariables()));

	for(int i=SLD->motor->numeroReglas()-1;i>=0;i--)
	{
		Regla *regla=SLD->motor->regla(i);
		guardarRegla(NodeA,regla);
	}

}
void Archivador::guardarRegla   (wxXmlNode* parent, Regla *regla)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,("RULE"));
	NodeA->AddAttribute(("Certainty")      , wxString::Format(("%f"),regla->certeza()));

	for(int i=SLD->salidas->numeroVariables()-1;i>=0;i--)
	{
		guardarConsecuente(NodeA,regla,i);
	}
	for(int i=SLD->entradas->numeroVariables()-1;i>=0;i--)
	{
		guardarAntecedente(NodeA,regla,i);
	}
}

void Archivador::guardarAntecedente(wxXmlNode* parent, Regla *regla, int num)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,("ANTECEDENT"));
	NodeA->AddAttribute(("Variable")      , wxString::Format(("%d"),num));
	NodeA->AddAttribute(("Label")      , wxString::Format(("%d"),regla->conjuntoEntrada(num)));
	NodeA->AddAttribute(("Modifier")   , wxString::Format(("%f"),regla->modificador(num)));
}

void Archivador::guardarConsecuente(wxXmlNode* parent, Regla *regla, int num)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,("CONSEQUENT"));
	NodeA->AddAttribute(("Variable")      , wxString::Format(("%d"),num));
	NodeA->AddAttribute(("Label")      , wxString::Format(("%d"),regla->conjuntoSalida(num)));
}

void Archivador::guardarNorma   (wxXmlNode* parent, Norma *norma, wxString label)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,label);
	NodeA->AddAttribute(("Type")      , wxString::Format(("%d"),norma->identificador()));
	NodeA->AddAttribute(("Parameter")  , wxString::Format(("%f"),norma->parametro()));

}

void Archivador::guardarImplicacion(wxXmlNode* parent, Implicacion *imp)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,("IMPLICATION"));
	NodeA->AddAttribute(("Type")      , wxString::Format(("%d"),imp->identificador()));
}

void Archivador::guardarConcrecion (wxXmlNode* parent)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,("DEFUZZYFIERS"));

	guardarNorma(NodeA,SLD->concreto->conjuncion(),("CONJUNCTION"));
	for(int i=SLD->concreto->numeroConcresores()-1;i>=0;i--)
	{
		Concresor *conc=SLD->concreto->concresor(i);
		guardarConcresor(NodeA,conc,i);
	}
}

void Archivador::guardarConcresor  (wxXmlNode* parent, Concresor *conc, int numVar)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,("DEFUZZYFIER"));
	NodeA->AddAttribute(("Variable")  , wxString::Format(("%d"),numVar));
	NodeA->AddAttribute(("Type")      , wxString::Format(("%d"),conc->identificador()));
}

void Archivador::leer(wxString fileName)
{
	doc.Load(fileName);
	if(!doc.IsOk())
	{
		wxMessageBox(_("The file coud not be loaded"),_("¡Warning!"));
	}
	wxXmlNode *Node=doc.GetRoot();

	leerSLD(Node);
}

void Archivador::leerSLD   (wxXmlNode* parent)
{
	SLD->crearMinimoSLD(1,1);
	SLD->nombre=parent->GetAttribute(("Name"));
	SLD->descripcion=parent->GetAttribute(("Description"));

	wxXmlNode *NodeA=parent->GetChildren();
	while(NodeA)
	{
		if(NodeA->GetName()==("INPUTS"))
		{
			leerEntradas(NodeA);
		}else if(NodeA->GetName()==("OUTPUTS"))
		{
			leerSalidas(NodeA);
		}else if(NodeA->GetName()==("ENGINE"))
		{
			leerMaquina(NodeA);
		}else if(NodeA->GetName()==("DEFUZZYFIERS"))
		{
			leerConcrecion(NodeA);
		}
		NodeA=NodeA->GetNext();
	}
}

void Archivador::leerEntradas   (wxXmlNode* parent)
{
	wxXmlNode *NodeA=parent->GetChildren();
	int cnt=0;
	while(NodeA)
	{
		if(NodeA->GetName()==("VARIABLE"))
		{
			Variable *var;
			var=new Variable(2);
			leerVariable(NodeA,var,true);
			SLD->entradas->adicionarVariable(var);
			cnt++;
		}
		NodeA=NodeA->GetNext();
	}
	if(cnt>0)
	{
		SLD->entradas->eliminarVariable(0);
	}
}

void Archivador::leerSalidas   (wxXmlNode* parent)
{
	wxXmlNode *NodeA=parent->GetChildren();
	int cnt=0;
	while(NodeA)
	{
		if(NodeA->GetName()==("VARIABLE"))
		{
			Variable *var;
			var=new Variable(2);
			leerVariable(NodeA,var,true);
			SLD->salidas->adicionarVariable(var);
			cnt++;
		}
		NodeA=NodeA->GetNext();
	}
	if(cnt>0)
	{
		SLD->salidas->eliminarVariable(0);
	}
}

void Archivador::leerVariable      (wxXmlNode* parent, Variable *var, bool flagDifusor)
{
	wxString strS;
	double tmpD;
	long tmpL;

	strS=parent->GetAttribute(("Name"));
	var->nombreVariable(std::string(strS.mb_str()));
	parent->GetAttribute(("Minimum")).ToDouble(&tmpD);
	var->rangoMinimo((double)tmpD);
	parent->GetAttribute(("Maximum")).ToDouble(&tmpD);
	var->rangoMaximo((double)tmpD);
	parent->GetAttribute(("Intervals")).ToLong(&tmpL);
	var->numeroIntervalos((int)tmpL);

	wxXmlNode *NodeA=parent->GetChildren();
	int cnt=0;
	while(NodeA)
	{
		if(NodeA->GetName()==("LABEL"))
		{
			ConjuntoDifuso *cd;
			cd=leerConjunto(NodeA,var);
			var->adicionarConjuntos(cd);
			cnt++;
		}else if(NodeA->GetName()==("FUZZYFIER"))
		{
			Difusor *dif;
			dif=leerDifusor(NodeA,var);
			var->difusorEntrada(dif);
		}

		NodeA=NodeA->GetNext();
	}
	if(cnt>0)
	{
		var->eliminarConjuntos(0);
		var->eliminarConjuntos(0);
	}

}

Difusor* Archivador::leerDifusor      (wxXmlNode* parent, Variable *var)
{
	long tmpL;
	double tmpD;
	wxString strS;

	int identificador;
	int numeroPuntos;
	double centro;

	parent->GetAttribute(("Type")).ToLong(&tmpL);
	identificador = (int)tmpL;
	parent->GetAttribute(("Points")).ToLong(&tmpL);
	numeroPuntos = (int)tmpL;
	parent->GetAttribute(("Center")).ToDouble(&tmpD);
	centro = (double)tmpD;

	double puntos[10];
	wxXmlNode *NodeA=parent->GetChildren();
	int cnt=0;
	while(NodeA)
	{
		if(NodeA->GetName()==("POINT"))
		{
			NodeA->GetAttribute(("X")).ToDouble(&tmpD);
			puntos[cnt]=(double)tmpD;
			cnt++;
		}
		NodeA=NodeA->GetNext();
	}

	Difusor *dif;
	switch(identificador)
	{
		case 1 :  dif=new DifusorTriangulo (centro,puntos[1]-puntos[0],puntos[2]-puntos[1]);break;
		case 2 :  dif=new DifusorPi        (centro,centro-puntos[0],centro-puntos[1],puntos[2]-centro,puntos[3]-centro);break;
		case 5 :  dif=new DifusorCampana   (centro,puntos[1]-puntos[0],puntos[2]-puntos[1]);break;
		case 6 :  dif=new DifusorPiCampana (centro,centro-puntos[0],centro-puntos[1],puntos[2]-centro,puntos[3]-centro);break;
		case 8 :  dif=new DifusorSinglenton(0.5*(puntos[0]+puntos[1]),(puntos[1]-puntos[0]));break;
		default : dif=new DifusorSinglenton(0.5*(puntos[0]+puntos[1]),(puntos[1]-puntos[0]));break;
	}
	dif->numeroPuntos(numeroPuntos);

	return dif;
}

ConjuntoDifuso* Archivador::leerConjunto      (wxXmlNode* parent, Variable *var)
{
	long tmpL;
	double tmpD;
	wxString strS;

	wxString Nombre;
	int identificador;
	int numeroPuntosClave;
	double *puntosClave;
	double minimo;
	double maximo;

	Nombre=parent->GetAttribute(("Name"));
	parent->GetAttribute(("Type")).ToLong(&tmpL);
	identificador = (int)tmpL;
	minimo = var->rangoMinimo();
	maximo = var->rangoMaximo();

	double puntos[10];
	wxXmlNode *NodeA=parent->GetChildren();
	int cnt=0;
	while(NodeA)
	{
		if(NodeA->GetName()==("POINT"))
		{
			NodeA->GetAttribute(("X")).ToDouble(&tmpD);
			puntos[cnt]=(double)tmpD;
			cnt++;
		}
		NodeA=NodeA->GetNext();
	}

	ConjuntoDifuso *cd;
	switch(identificador)
	{
		case 0 :	cd=new ConjuntoL         (std::string(Nombre.mb_str()),minimo,puntos[0],puntos[1]);break;
		case 1 :  cd=new ConjuntoTriangulo (std::string(Nombre.mb_str()),puntos[0],puntos[1],puntos[2]);break;
		case 2 :  cd=new ConjuntoPi        (std::string(Nombre.mb_str()),puntos[0],puntos[1],puntos[2],puntos[3]);break;
		case 3 :  cd=new ConjuntoGamma     (std::string(Nombre.mb_str()),puntos[0],puntos[1],maximo);break;
		case 4 :  cd=new ConjuntoZ         (std::string(Nombre.mb_str()),minimo,puntos[0],puntos[1]);break;
		case 5 :  cd=new ConjuntoCampana   (std::string(Nombre.mb_str()),puntos[0],puntos[1],puntos[2]);break;
		case 6 :  cd=new ConjuntoPiCampana (std::string(Nombre.mb_str()),puntos[0],puntos[1],puntos[2],puntos[3]);break;
		case 7 :  cd=new ConjuntoS         (std::string(Nombre.mb_str()),puntos[0],puntos[1],maximo);break;
		case 8 :  cd=new ConjuntoSinglenton(std::string(Nombre.mb_str()),0.5*(puntos[0]+puntos[1]),(puntos[1]-puntos[0]));break;
		default : cd=new ConjuntoTriangulo (std::string(Nombre.mb_str()),minimo,puntos[0],puntos[1]);break;
	}
	return cd;
}

void Archivador::leerMaquina(wxXmlNode* parent)
{
	wxXmlNode *NodeA=parent->GetChildren();
	while(NodeA)
	{
		if(NodeA->GetName()==("BASE"))
		{
			leerBase(NodeA);
		}else if(NodeA->GetName()==("IMPLICATION"))
		{
			leerImplicacion(NodeA);
		}else if(NodeA->GetName()==("COMPOSITION"))
		{
			Norma* norma=leerNorma(NodeA);
			SLD->motor->composicion(norma);
		}else if(NodeA->GetName()==("AND"))
		{
			Norma* norma=leerNorma(NodeA);
			SLD->motor->and_(norma);
		}
		NodeA=NodeA->GetNext();
	}
}

void Archivador::leerBase(wxXmlNode* parent)
{
	long tmpL;

	int numEnt;
	int numSal;

	parent->GetAttribute(("Inputs")).ToLong(&tmpL);
	numEnt=(int)tmpL;
	parent->GetAttribute(("Outputs")).ToLong(&tmpL);
	numSal=(int)tmpL;

	SLD->motor->desocuparBaseReglas();
	SLD->motor->eliminarRegla(0);
	SLD->motor->numeroEntradas(numEnt);
	SLD->motor->numeroSalidas(numSal);

	wxXmlNode *NodeA=parent->GetChildren();
	while(NodeA)
	{
		if(NodeA->GetName()==("RULE"))
		{
			Regla* regla;
			regla=new Regla(numEnt,numSal);
			leerRegla(NodeA,regla);
			SLD->motor->adicionarRegla(regla);
		}
		NodeA=NodeA->GetNext();
	}
}

void Archivador::leerRegla(wxXmlNode* parent, Regla *regla)
{
	long tmpL;
	double tmpD;

	int numVar;
	int numEt;
	double mod;

	parent->GetAttribute(("Certainty")).ToDouble(&tmpD);
	regla->certeza((double)tmpD);

	wxXmlNode *NodeA=parent->GetChildren();
	while(NodeA)
	{
		if(NodeA->GetName()==("ANTECEDENT"))
		{
			NodeA->GetAttribute(("Variable")).ToLong(&tmpL);
			numVar=(int)tmpL;
			NodeA->GetAttribute(("Label")).ToLong(&tmpL);
			numEt =(int)tmpL;
			NodeA->GetAttribute(("Modifier")).ToDouble(&tmpD);
			mod   =(double)tmpD;
			regla->conjuntoEntrada(numVar,numEt);
			regla->modificador(numVar,mod);

		}else if(NodeA->GetName()==("CONSEQUENT"))
		{
			NodeA->GetAttribute(("Variable")).ToLong(&tmpL);
			numVar=(int)tmpL;
			NodeA->GetAttribute(("Label")).ToLong(&tmpL);
			numEt =(int)tmpL;
			regla->conjuntoSalida(numVar,numEt);
		}
		NodeA=NodeA->GetNext();
	}
}

Norma* Archivador::leerNorma(wxXmlNode* parent)
{
	long tmpL;
	double tmpD;

	int identificador;
	double parametro;

	parent->GetAttribute(("Type")).ToLong(&tmpL);
	identificador=(int)tmpL;
	parent->GetAttribute(("Parameter")).ToDouble(&tmpD);
	parametro=(double)tmpD;

	Norma* norma;
	switch(identificador)
	{
	  case 0  : norma = new Producto();break;
	  case 1  : norma = new Minimo();break;
	  case 2  : norma = new ProductoAcotado();break;
	  case 3  : norma = new ProductoDrastico();break;
	  case 4  : norma = new FamiliaTp(parametro);break;
	  case 5  : norma = new FamiliaHp(parametro);break;
	  case 6  : norma = new FamiliaSp(parametro);break; // S-norma
	  case 7  : norma = new FamiliaFp(parametro);break;
	  case 8  : norma = new FamiliaYp(parametro);break;
	  case 9  : norma = new FamiliaAp(parametro);break;
	  case 10 : norma = new Maximo();break;
	  case 11 : norma = new SumaAcotada();break;
	  case 12 : norma = new SumaDrastica();break;
	  default : norma = new Minimo();break;
	}
	return norma;
}

void Archivador::leerImplicacion(wxXmlNode* parent)
{
	long tmpL;

	int identificador;
	parent->GetAttribute(("Type")).ToLong(&tmpL);
	identificador=(int)tmpL;

	Implicacion *imp;
	switch(identificador)
	{
	  case 0 : imp=new ImplicacionProducto();break;
	  case 1 : imp=new ImplicacionMinimo();break;
	  case 2 : imp=new ImplicacionKleenDienes();break;
	  case 3 : imp=new ImplicacionLukasiewicz();break;
	  case 4 : imp=new ImplicacionZadeh();break;
	  case 5 : imp=new ImplicacionEstocastica();break;
	  case 6 : imp=new ImplicacionGoguen();break;
	  case 7 : imp=new ImplicacionGodel();break;
	  case 8 : imp=new ImplicacionAguda();break;
	  default: imp=new ImplicacionMinimo();break;
	}

	SLD->motor->implicacion(imp);
}

void Archivador::leerConcrecion(wxXmlNode* parent)
{
  delete SLD->concreto;
  SLD->concreto= new BloqueConcrecion(SLD->motor);

	wxXmlNode *NodeA=parent->GetChildren();
	while(NodeA)
	{
		if(NodeA->GetName()==("DEFUZZYFIER"))
		{
			leerConcresor(NodeA);
		}else if(NodeA->GetName()==("CONJUNCTION"))
		{
			Norma *norma=leerNorma(NodeA);
			SLD->concreto->conjuncion(norma);
		}
		NodeA=NodeA->GetNext();
	}
}

void Archivador::leerConcresor(wxXmlNode* parent)
{
	long tmpL;

	int identificador;
	int numVar;

	parent->GetAttribute(("Variable")).ToLong(&tmpL);
	numVar=(int)tmpL;
	parent->GetAttribute(("Type")).ToLong(&tmpL);
	identificador=(int)tmpL;

	Norma *conjuncion=new Maximo();

	Concresor* conc;
	switch(identificador)
	{
		case 0 : conc = new PrimerMaximo    (SLD->motor, numVar, conjuncion);break;
		case 1 : conc = new UltimoMaximo    (SLD->motor, numVar, conjuncion);break;
		case 2 : conc = new MediaDeMaximos  (SLD->motor, numVar, conjuncion);break;
		case 3 : conc = new CentroDeGravedad(SLD->motor, numVar, conjuncion);break;
		case 4 : conc = new Altura          (SLD->motor, numVar, conjuncion);break;
		default: conc = new CentroDeGravedad(SLD->motor, numVar, conjuncion);break;
	}
	SLD->concreto->insertarConcresor(conc,numVar);
}

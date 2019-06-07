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
	Node=new wxXmlNode(NULL,wxXML_ELEMENT_NODE,_T("SLD"));
	Node->AddAttribute(_T("Nombre")      , SLD->nombre);
	Node->AddAttribute(_T("Descripción") , SLD->descripcion);
	doc.SetRoot(Node);

	guardarConcrecion(Node);
	guardarMaquina(Node);
	guardarSalidas(Node);
	guardarEntradas(Node);

	doc.Save(fileName);
}

void Archivador::guardarEntradas(wxXmlNode* parent)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,_T("ENTRADAS"));
	for(int i = SLD->entradas->numeroVariables()-1; i >= 0 ; i--)
	{
		Variable *var=SLD->entradas->variable(i);
		guardarVariable(NodeA,var,true);
	}
}

void Archivador::guardarSalidas(wxXmlNode* parent)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,_T("SALIDAS"));
	for(int i = SLD->salidas->numeroVariables()-1; i >= 0 ; i--)
	{
		Variable *var=SLD->salidas->variable(i);
		guardarVariable(NodeA,var,false);
	}
}

void Archivador::guardarVariable(wxXmlNode* parent, Variable *var, bool flagDifusor)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,_T("VARIABLE"));
	NodeA->AddAttribute(_T("Nombre")      , var->nombreVariable());
	NodeA->AddAttribute(_T("Mínimo")      , wxString::Format(wxT("%f"),var->rangoMinimo()));
	NodeA->AddAttribute(_T("Máximo")      , wxString::Format(wxT("%f"),var->rangoMaximo()));
	NodeA->AddAttribute(_T("Intervalos")  , wxString::Format(wxT("%d"),var->numeroIntervalos()));

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
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,_T("DIFUSOR"));
	NodeA->AddAttribute(_T("Tipo")        ,  wxString::Format(wxT("%d"),dif->identificador()));
	NodeA->AddAttribute(_T("Puntos")      ,  wxString::Format(wxT("%d"),dif->numeroPuntos()));
	NodeA->AddAttribute(_T("Centro")      ,  wxString::Format(wxT("%f"),dif->centro()));

	float puntos[dif->numeroPuntosClaves()];
	dif->puntosClaves(puntos);
	for(int i=dif->numeroPuntosClaves()-1;i>=0;i--)
	{
		wxXmlNode* NodeB;
		NodeB=new wxXmlNode(NodeA,wxXML_ELEMENT_NODE,_T("PUNTO"));
		NodeB->AddAttribute(_T("X")      , wxString::Format(wxT("%f"),puntos[i]));
	}
}

void Archivador::guardarConjunto(wxXmlNode* parent, ConjuntoDifuso *cd)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,_T("ETIQUETA"));
	NodeA->AddAttribute(_T("Nombre")      , cd->nombre());
	NodeA->AddAttribute(_T("Tipo")        ,  wxString::Format(wxT("%d"),cd->identificador()));

	float puntos[cd->numeroPuntosClaves()];
	cd->puntosClaves(puntos);
	for(int i=cd->numeroPuntosClaves()-1;i>=0;i--)
	{
		wxXmlNode* NodeB;
		NodeB=new wxXmlNode(NodeA,wxXML_ELEMENT_NODE,_T("PUNTO"));
		NodeB->AddAttribute(_T("X")      , wxString::Format(wxT("%f"),puntos[i]));
	}
}

void Archivador::guardarMaquina (wxXmlNode* parent)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,_T("MOTOR"));

	guardarBase(NodeA);
	guardarNorma(NodeA,SLD->motor->and_(),_T("AND"));
	guardarNorma(NodeA,SLD->motor->composicion(),_T("COMPOSICIÓN"));
	guardarImplicacion(NodeA,SLD->motor->implicacion());
}

void Archivador::guardarBase    (wxXmlNode* parent)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,_T("BASE"));
	NodeA->AddAttribute(_T("Entradas")    , wxString::Format(wxT("%d"),SLD->entradas->numeroVariables()));
	NodeA->AddAttribute(_T("Salidas")     , wxString::Format(wxT("%d"),SLD->salidas->numeroVariables()));

	for(int i=SLD->motor->numeroReglas()-1;i>=0;i--)
	{
		Regla *regla=SLD->motor->regla(i);
		guardarRegla(NodeA,regla);
	}

}
void Archivador::guardarRegla   (wxXmlNode* parent, Regla *regla)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,_T("REGLA"));
	NodeA->AddAttribute(_T("Certeza")      , wxString::Format(wxT("%f"),regla->certeza()));

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
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,_T("ANTECEDENTE"));
	NodeA->AddAttribute(_T("Variable")      , wxString::Format(wxT("%d"),num));
	NodeA->AddAttribute(_T("Etiqueta")      , wxString::Format(wxT("%d"),regla->conjuntoEntrada(num)));
	NodeA->AddAttribute(_T("Modificador")   , wxString::Format(wxT("%f"),regla->modificador(num)));
}

void Archivador::guardarConsecuente(wxXmlNode* parent, Regla *regla, int num)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,_T("CONSECUENTE"));
	NodeA->AddAttribute(_T("Variable")      , wxString::Format(wxT("%d"),num));
	NodeA->AddAttribute(_T("Etiqueta")      , wxString::Format(wxT("%d"),regla->conjuntoSalida(num)));
}

void Archivador::guardarNorma   (wxXmlNode* parent, Norma *norma, wxString label)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,label);
	NodeA->AddAttribute(_T("Tipo")      , wxString::Format(wxT("%d"),norma->identificador()));
	NodeA->AddAttribute(_T("Parámetro")  , wxString::Format(wxT("%f"),norma->parametro()));

}

void Archivador::guardarImplicacion(wxXmlNode* parent, Implicacion *imp)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,_T("IMPLICACIÓN"));
	NodeA->AddAttribute(_T("Tipo")      , wxString::Format(wxT("%d"),imp->identificador()));
}

void Archivador::guardarConcrecion (wxXmlNode* parent)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,_T("CONCRECIÓN"));

	guardarNorma(NodeA,SLD->concreto->conjuncion(),_T("CONJUNCIÓN"));
	for(int i=SLD->concreto->numeroConcresores()-1;i>=0;i--)
	{
		Concresor *conc=SLD->concreto->concresor(i);
		guardarConcresor(NodeA,conc,i);
	}
}

void Archivador::guardarConcresor  (wxXmlNode* parent, Concresor *conc, int numVar)
{
	wxXmlNode* NodeA;
	NodeA=new wxXmlNode(parent,wxXML_ELEMENT_NODE,_T("CONCRESOR"));
	NodeA->AddAttribute(_T("Variable")  , wxString::Format(wxT("%d"),numVar));
	NodeA->AddAttribute(_T("Tipo")      , wxString::Format(wxT("%d"),conc->identificador()));
}

void Archivador::leer(wxString fileName)
{
	doc.Load(fileName);
	if(!doc.IsOk())
	{
		wxMessageBox(_T("No se pudo cargar el archivo"),_T("¡Atención!"));
	}

	SLD->crearMinimoSLD(1,1);

	wxXmlNode *Node=doc.GetRoot();
	SLD->nombre=Node->GetAttribute(_T("Nombre"));
	SLD->descripcion=Node->GetAttribute(_T("Descripción"));

	wxXmlNode *NodeA=Node->GetChildren();
	while(NodeA)
	{
		if(NodeA->GetName()==_T("ENTRADAS"))
		{
			leerEntradas(NodeA);
		}else if(NodeA->GetName()==_T("SALIDAS"))
		{
			leerSalidas(NodeA);
		}else if(NodeA->GetName()==_T("MOTOR"))
		{
			leerMaquina(NodeA);
		}else if(NodeA->GetName()==_T("CONCRECIÓN"))
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
		if(NodeA->GetName()==_T("VARIABLE"))
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
		if(NodeA->GetName()==_T("VARIABLE"))
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

	strS=parent->GetAttribute(_T("Nombre"));
	var->nombreVariable(strS.mb_str());
	parent->GetAttribute(_T("Mínimo")).ToDouble(&tmpD);
	var->rangoMinimo((float)tmpD);
	parent->GetAttribute(_T("Máximo")).ToDouble(&tmpD);
	var->rangoMaximo((float)tmpD);
	parent->GetAttribute(_T("Intervalos")).ToLong(&tmpL);
	var->numeroIntervalos((int)tmpL);

	wxXmlNode *NodeA=parent->GetChildren();
	int cnt=0;
	while(NodeA)
	{
		if(NodeA->GetName()==_T("ETIQUETA"))
		{
			ConjuntoDifuso *cd;
			cd=leerConjunto(NodeA,var);
			var->adicionarConjuntos(cd);
			cnt++;
		}else if(NodeA->GetName()==_T("DIFUSOR"))
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
	int numeroPuntosClave;
	float *puntosClave;
	float minimo;
	float maximo;
	float centro;

	parent->GetAttribute(_T("Tipo")).ToLong(&tmpL);
	identificador = (int)tmpL;
	parent->GetAttribute(_T("Puntos")).ToLong(&tmpL);
	numeroPuntos = (int)tmpL;
	parent->GetAttribute(_T("Centro")).ToDouble(&tmpD);
	centro = (float)tmpD;
	minimo = var->rangoMinimo();
	maximo = var->rangoMaximo();

	float puntos[10];
	wxXmlNode *NodeA=parent->GetChildren();
	int cnt=0;
	while(NodeA)
	{
		if(NodeA->GetName()==_T("PUNTO"))
		{
			NodeA->GetAttribute(_T("X")).ToDouble(&tmpD);
			puntos[cnt]=(float)tmpD;
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
	float *puntosClave;
	float minimo;
	float maximo;

	Nombre=parent->GetAttribute(_T("Nombre"));
	parent->GetAttribute(_T("Tipo")).ToLong(&tmpL);
	identificador = (int)tmpL;
	minimo = var->rangoMinimo();
	maximo = var->rangoMaximo();

	float puntos[10];
	wxXmlNode *NodeA=parent->GetChildren();
	int cnt=0;
	while(NodeA)
	{
		if(NodeA->GetName()==_T("PUNTO"))
		{
			NodeA->GetAttribute(_T("X")).ToDouble(&tmpD);
			puntos[cnt]=(float)tmpD;
			cnt++;
		}
		NodeA=NodeA->GetNext();
	}

	ConjuntoDifuso *cd;
	switch(identificador)
	{
		case 0 :	cd=new ConjuntoL         (Nombre.mb_str(),minimo,puntos[0],puntos[1]);break;
		case 1 :  cd=new ConjuntoTriangulo (Nombre.mb_str(),puntos[0],puntos[1],puntos[2]);break;
		case 2 :  cd=new ConjuntoPi        (Nombre.mb_str(),puntos[0],puntos[1],puntos[2],puntos[3]);break;
		case 3 :  cd=new ConjuntoGamma     (Nombre.mb_str(),puntos[0],puntos[1],maximo);break;
		case 4 :  cd=new ConjuntoZ         (Nombre.mb_str(),minimo,puntos[0],puntos[1]);break;
		case 5 :  cd=new ConjuntoCampana   (Nombre.mb_str(),puntos[0],puntos[1],puntos[2]);break;
		case 6 :  cd=new ConjuntoPiCampana (Nombre.mb_str(),puntos[0],puntos[1],puntos[2],puntos[3]);break;
		case 7 :  cd=new ConjuntoS         (Nombre.mb_str(),puntos[0],puntos[1],maximo);break;
		case 8 :  cd=new ConjuntoSinglenton(Nombre.mb_str(),0.5*(puntos[0]+puntos[1]),(puntos[1]-puntos[0]));break;
		default : cd=new ConjuntoTriangulo (Nombre.mb_str(),minimo,puntos[0],puntos[1]);break;
	}
	return cd;
}

void Archivador::leerMaquina(wxXmlNode* parent)
{
	wxXmlNode *NodeA=parent->GetChildren();
	while(NodeA)
	{
		if(NodeA->GetName()==_T("BASE"))
		{
			leerBase(NodeA);
		}else if(NodeA->GetName()==_T("IMPLICACIÓN"))
		{
			leerImplicacion(NodeA);
		}else if(NodeA->GetName()==_T("COMPOSICIÓN"))
		{
			Norma* norma=leerNorma(NodeA);
			SLD->motor->composicion(norma);
		}else if(NodeA->GetName()==_T("AND"))
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

	parent->GetAttribute(_T("Entradas")).ToLong(&tmpL);
	numEnt=(int)tmpL;
	parent->GetAttribute(_T("Salidas")).ToLong(&tmpL);
	numSal=(int)tmpL;

	SLD->motor->desocuparBaseReglas();
	SLD->motor->eliminarRegla(0);
	SLD->motor->numeroEntradas(numEnt);
	SLD->motor->numeroSalidas(numSal);

	wxXmlNode *NodeA=parent->GetChildren();
	while(NodeA)
	{
		if(NodeA->GetName()==_T("REGLA"))
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
	float mod;

	wxXmlNode *NodeA=parent->GetChildren();
	while(NodeA)
	{
		if(NodeA->GetName()==_T("ANTECEDENTE"))
		{
			NodeA->GetAttribute(_T("Variable")).ToLong(&tmpL);
			numVar=(int)tmpL;
			NodeA->GetAttribute(_T("Etiqueta")).ToLong(&tmpL);
			numEt =(int)tmpL;
			NodeA->GetAttribute(_T("Modificador")).ToDouble(&tmpD);
			mod   =(float)tmpD;
			regla->conjuntoEntrada(numVar,numEt);
			regla->modificador(numVar,mod);

		}else if(NodeA->GetName()==_T("CONSECUENTE"))
		{
			NodeA->GetAttribute(_T("Variable")).ToLong(&tmpL);
			numVar=(int)tmpL;
			NodeA->GetAttribute(_T("Etiqueta")).ToLong(&tmpL);
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
	float parametro;

	parent->GetAttribute(_T("Tipo")).ToLong(&tmpL);
	identificador=(int)tmpL;
	parent->GetAttribute(_T("Parámetro")).ToDouble(&tmpD);
	parametro=(float)tmpD;

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
	parent->GetAttribute(_T("Tipo")).ToLong(&tmpL);
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
		if(NodeA->GetName()==_T("CONCRESOR"))
		{
			leerConcresor(NodeA);
		}else if(NodeA->GetName()==_T("CONJUNCIÓN"))
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

	parent->GetAttribute(_T("Variable")).ToLong(&tmpL);
	numVar=(int)tmpL;
	parent->GetAttribute(_T("Tipo")).ToLong(&tmpL);
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

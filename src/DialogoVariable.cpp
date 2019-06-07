#include "DialogoVariable.h"

BEGIN_EVENT_TABLE(DialogoVariable, wxDialog)
    EVT_PAINT(DialogoVariable::OnPaint)
    EVT_CLOSE(DialogoVariable::OnClose)
    EVT_LEFT_DOWN(DialogoVariable::OnLeftDown)
    EVT_LEFT_UP(DialogoVariable::OnLeftUp)
    EVT_RIGHT_DOWN(DialogoVariable::OnRightClick)
    EVT_BUTTON(wxID_OK                      , DialogoVariable::OnOK)
    EVT_LISTBOX(DLG_VARIABLE_LISTAVAR       , DialogoVariable::cambiaVariable)
    EVT_LISTBOX(DLG_VARIABLE_LISTACON       , DialogoVariable::cambiaConjunto)
    EVT_BUTTON(DLG_VARIABLE_VAREDITAR       , DialogoVariable::OnEditarVar)
    EVT_BUTTON(DLG_VARIABLE_VARELIMINAR     , DialogoVariable::OnEliminarVar)
    EVT_BUTTON(DLG_VARIABLE_VARADICIONAR    , DialogoVariable::OnAdicionarVar)
    EVT_BUTTON(DLG_VARIABLE_VARAUTODEFINIR  , DialogoVariable::OnAutodefinirVar)
    EVT_BUTTON(DLG_VARIABLE_CONEDITAR       , DialogoVariable::OnEditarCon)
    EVT_BUTTON(DLG_VARIABLE_CONELIMINAR     , DialogoVariable::OnEliminarCon)
    EVT_BUTTON(DLG_VARIABLE_CONADICIONAR    , DialogoVariable::OnAdicionarCon)
    EVT_COMBOBOX(DLG_VARIABLE_CONTIPO       , DialogoVariable::OnTipoCon)
    EVT_COMBOBOX(DLG_VARIABLE_COMBODIFUSOR  , DialogoVariable::cambiaDifusor)
    EVT_COMBOBOX(DLG_VARIABLE_COMBOCONCRESOR, DialogoVariable::cambiaConcresor)
    EVT_SPINCTRL(DLG_VARIABLE_SPINDIFINTERVALOS,DialogoVariable::OnSpinIntervalos)
    EVT_SPINCTRLDOUBLE(DLG_VARIABLE_SPINDIFANCHO,DialogoVariable::OnSpinAncho)
END_EVENT_TABLE()

DialogoVariable::DialogoVariable(Universo *u, SistemaLogicaDifusa *sld, bool flagDif, wxWindow *parent)
:wxDialog(parent,wxID_ANY,wxString(wxT("Diseño de Universos de Entrada o Salida")))
{
	U=u;
	SLD=sld;
	Concreto=sld->concreto;

	flagDifusor=flagDif;

	flagArrastre=false;
	NumVar=0;
	NumCon=0;

  wxFlexGridSizer*  sizerTotal;
  wxFlexGridSizer*  sizerControles;
  wxFlexGridSizer*  sizerControlesVariable;
  wxFlexGridSizer*  sizerBotonesVariable;
  wxFlexGridSizer*  sizerControlesConjunto;
  wxFlexGridSizer*  sizerBotonesConjunto;
  wxFlexGridSizer*  sizerBotonesDifConc;
  wxFlexGridSizer*  sizerFlexiVariable;
  wxFlexGridSizer*  sizerImgVariable;
  wxFlexGridSizer*  sizerOKCancel;

  wxStaticBoxSizer* sizerStaticVariables;
  wxStaticBoxSizer* sizerStaticConjuntos;
  wxStaticBoxSizer* sizerStaticDifConc;


  sizerTotal             = new wxFlexGridSizer(1,4,0);
	sizerControles         = new wxFlexGridSizer(3,1,0);
	sizerControlesVariable = new wxFlexGridSizer(4,1,0);
	sizerBotonesVariable   = new wxFlexGridSizer(1,4,0);
	sizerControlesConjunto = new wxFlexGridSizer(4,1,0);
	sizerBotonesConjunto   = new wxFlexGridSizer(1,4,0);
	sizerBotonesDifConc    = new wxFlexGridSizer(2,3,0);
	sizerFlexiVariable     = new wxFlexGridSizer(1,2,0);
	sizerImgVariable       = new wxFlexGridSizer(2,2,0);
	sizerStaticVariables   = new wxStaticBoxSizer(wxVERTICAL,this,_T("Variables"));
	sizerStaticConjuntos   = new wxStaticBoxSizer(wxVERTICAL,this,_T("Conjuntos"));
  sizerOKCancel    = new wxFlexGridSizer(2,1,0);

	listaVariables    = new wxListBox(this,DLG_VARIABLE_LISTAVAR,wxDefaultPosition,wxSize(150,150));
	listaConjuntos    = new wxListBox(this,DLG_VARIABLE_LISTACON,wxDefaultPosition,wxSize(150,150));
  canvasVar         = new wxSizerItem(600,200);
  staticLabelVar    = new wxStaticText(this,wxID_ANY,_T("Variable Lingüística"));

  if(flagDifusor)
	{
	  canvasDif         = new wxSizerItem(300,200);

	  staticLabelDif      = new wxStaticText(this,wxID_ANY,_("Difusor"));
		comboTipoDifusor    = new wxComboBox(this,DLG_VARIABLE_COMBODIFUSOR);
	  spinDifIntervalos   = new wxSpinCtrl(this,DLG_VARIABLE_SPINDIFINTERVALOS, _T(""),wxDefaultPosition,wxSize(120,25));
	  spinDifAncho        = new wxSpinCtrlDouble(this,DLG_VARIABLE_SPINDIFANCHO,_T(""),wxDefaultPosition,wxSize(120,25));
		comboTipoConcresor  = NULL;
		sizerStaticDifConc  = new wxStaticBoxSizer(wxVERTICAL,this,_T("Difusor"));
		staticTipoDif       = new wxStaticText(this,wxID_ANY,_T("Tipo"));
		staticInterDif      = new wxStaticText(this,wxID_ANY,_T("Puntos de evaluación"));
		staticAnchoDif      = new wxStaticText(this,wxID_ANY,_T("Ancho"));

		sizerBotonesDifConc->Add(staticTipoDif        , 1, wxALIGN_RIGHT|wxALL, 1);
		sizerBotonesDifConc->Add(comboTipoDifusor     , 1, wxALIGN_LEFT |wxALL, 1);
		sizerBotonesDifConc->Add(staticInterDif       , 1, wxALIGN_RIGHT|wxALL, 1);
		sizerBotonesDifConc->Add(spinDifIntervalos    , 1, wxALIGN_LEFT |wxALL, 1);
		sizerBotonesDifConc->Add(staticAnchoDif       , 1, wxALIGN_RIGHT|wxALL, 1);
		sizerBotonesDifConc->Add(spinDifAncho         , 1, wxALIGN_LEFT |wxALL, 1);

		comboTipoDifusor->Append(_T(IDS_CONJUNTOS_TIPO_1));
		comboTipoDifusor->Append(_T(IDS_CONJUNTOS_TIPO_2));
		comboTipoDifusor->Append(_T(IDS_CONJUNTOS_TIPO_5));
		comboTipoDifusor->Append(_T(IDS_CONJUNTOS_TIPO_6));
		comboTipoDifusor->Append(_T(IDS_CONJUNTOS_TIPO_8));
	}else
	{
	  canvasDif         = new wxSizerItem(1,200);

	  staticLabelDif      = new wxStaticText(this,wxID_ANY,_(""));
		comboTipoDifusor    = NULL;
	  spinDifIntervalos   = NULL;
	  spinDifAncho        = NULL;
		staticTipoDif       = NULL;
		staticInterDif      = NULL;
		staticAnchoDif      = NULL;

		comboTipoConcresor  = new wxComboBox(this,DLG_VARIABLE_COMBOCONCRESOR);
		sizerStaticDifConc  = new wxStaticBoxSizer(wxVERTICAL,this,_T("Concresor"));
		sizerBotonesDifConc->Add(comboTipoConcresor     , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 1);

		comboTipoConcresor->Append(_T(IDS_CONCRESOR_TIPO_0));
		comboTipoConcresor->Append(_T(IDS_CONCRESOR_TIPO_1));
		comboTipoConcresor->Append(_T(IDS_CONCRESOR_TIPO_2));
		comboTipoConcresor->Append(_T(IDS_CONCRESOR_TIPO_3));
		comboTipoConcresor->Append(_T(IDS_CONCRESOR_TIPO_4));
	}

	buttonEditarVar      = new wxButton(this,DLG_VARIABLE_VAREDITAR      ,_T("Editar"));
	buttonEliminarVar    = new wxButton(this,DLG_VARIABLE_VARELIMINAR    ,_T("Eliminar"));
	buttonAdicionarVar   = new wxButton(this,DLG_VARIABLE_VARADICIONAR   ,_T("Adicionar"));
	buttonAutodefinirVar = new wxButton(this,DLG_VARIABLE_VARAUTODEFINIR ,_T("Autodefinir"));
	buttonEditarCon      = new wxButton(this,DLG_VARIABLE_CONEDITAR      ,_T("Etiqueta"));
	buttonEliminarCon    = new wxButton(this,DLG_VARIABLE_CONELIMINAR    ,_T("Eliminar"));
	buttonAdicionarCon   = new wxButton(this,DLG_VARIABLE_CONADICIONAR   ,_T("Adicionar"));
  buttonOK             = new wxButton(this,wxID_OK,_("OK"));
  buttonCancel         = new wxButton(this,wxID_CANCEL,_("Cancelar"));
	comboTipoCon         = new wxComboBox(this,DLG_VARIABLE_CONTIPO);

	comboTipoCon->Append(_T(IDS_CONJUNTOS_TIPO_0));
	comboTipoCon->Append(_T(IDS_CONJUNTOS_TIPO_1));
	comboTipoCon->Append(_T(IDS_CONJUNTOS_TIPO_2));
	comboTipoCon->Append(_T(IDS_CONJUNTOS_TIPO_3));
	comboTipoCon->Append(_T(IDS_CONJUNTOS_TIPO_4));
	comboTipoCon->Append(_T(IDS_CONJUNTOS_TIPO_5));
	comboTipoCon->Append(_T(IDS_CONJUNTOS_TIPO_6));
	comboTipoCon->Append(_T(IDS_CONJUNTOS_TIPO_7));
	comboTipoCon->Append(_T(IDS_CONJUNTOS_TIPO_8));

///////////////////
	sizerBotonesVariable->Add(buttonEditarVar     , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 1);
	sizerBotonesVariable->Add(buttonEliminarVar   , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 1);
	sizerBotonesVariable->Add(buttonAdicionarVar  , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 1);
	sizerBotonesVariable->Add(buttonAutodefinirVar, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 1);

	sizerBotonesConjunto->Add(buttonEditarCon     , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 1);
	sizerBotonesConjunto->Add(buttonEliminarCon   , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 1);
	sizerBotonesConjunto->Add(buttonAdicionarCon  , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 1);
	sizerBotonesConjunto->Add(comboTipoCon        , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 1);

	sizerControlesVariable->Add(listaVariables       , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerControlesVariable->Add(sizerBotonesVariable , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

	sizerControlesConjunto->Add(listaConjuntos       , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerControlesConjunto->Add(sizerBotonesConjunto , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

	sizerStaticVariables->Add(sizerControlesVariable , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 0);

	sizerStaticConjuntos->Add(sizerControlesConjunto , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 0);

	sizerStaticDifConc->Add(sizerBotonesDifConc , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 0);

	sizerControles->Add(sizerStaticVariables, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerControles->Add(sizerStaticConjuntos, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerControles->Add(sizerStaticDifConc  , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

  sizerImgVariable->Add(staticLabelVar);
  sizerImgVariable->Add(staticLabelDif);
  sizerImgVariable->Add(canvasVar);
  sizerImgVariable->Add(canvasDif);

  sizerFlexiVariable->Add(sizerImgVariable        , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

	sizerOKCancel->Add(buttonOK, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerOKCancel->Add(buttonCancel, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

  sizerTotal->Add(sizerControles          , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
  sizerTotal->Add(sizerFlexiVariable        , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 0);
	sizerTotal->Add(sizerOKCancel, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

  this->SetSizer(sizerTotal);
  this->Layout();
  sizerTotal->Fit(this);

	llenarDatos();
}

DialogoVariable::~DialogoVariable()
{
	U=NULL;
}

void DialogoVariable::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void DialogoVariable::OnOK(wxCommandEvent&   event)
{
	EndModal(wxID_OK);
}

void DialogoVariable::pintarVariable(int numVar,int conj)
{
	NumVar=numVar;
	NumCon=conj;
	if(U->numeroVariables()<=(NumVar)){return;}
	Variable *Var;
  Var=U->variable(NumVar);

	wxClientDC dc(this);
	wxRect canvas=canvasVar->GetRect();
	Graficador Grafica(&dc,canvas);
	Grafica.pintarVariable(Var,NumCon);
	Grafica.pintarTitle(Var->nombreVariable());

	numeroPuntosArrastre=Grafica.numeroPuntosArrastre;
	tamArrastre=Grafica.tamArrastre;
	for(int i=0;i<=numeroPuntosArrastre+1;i++)
	{
		puntosArrastre[i]=Grafica.puntosArrastre[i];
	}
	Var=NULL;
}


void DialogoVariable::pintarDifusor(int numVar,int conj)
{
	NumVar=numVar;
	NumCon=conj;
	if(U->numeroVariables()<=(NumVar)){return;}

	Variable *Var;
  Var=U->variable(NumVar);

	wxClientDC dc(this);
	wxRect canvas=canvasDif->GetRect();
	Graficador Grafica(&dc,canvas);
	Grafica.pintarDifusor(Var);
	Grafica.pintarTitle(wxString::Format("Difusor de %s",Var->nombreVariable()));

	Var=NULL;
}

void DialogoVariable::OnPaint(wxPaintEvent& event)
{
	pintarVariable(NumVar,NumCon);
	if(flagDifusor)
	{
		pintarDifusor(NumVar,NumCon);
	}
}

void DialogoVariable::OnLeftDown(wxMouseEvent& event)
{
	wxPoint tp(event.GetX(),event.GetY());
	puntoArrastrado=0;
	for(int i=1;i<=numeroPuntosArrastre+1;i++)
	{
		wxRect rect(puntosArrastre[i].x-tamArrastre,puntosArrastre[i].y-tamArrastre,tamArrastre*2,tamArrastre*2);
		if(rect.Contains(tp))
		{
			flagArrastre=true;
			puntoArrastrado=i;
			wxSetCursor(wxCursor(*wxCROSS_CURSOR));
		}
	}
}

void DialogoVariable::OnLeftUp(wxMouseEvent& event)
{
	wxSetCursor(wxCursor(*wxSTANDARD_CURSOR));
	if(!flagArrastre){return;}
	Variable *Var;
  Var=U->variable(NumVar);
	if(!Var){return;}
	if(puntoArrastrado!=0)
	{
		int X=event.GetX();
		int Xo,Xf;
		float xo,xf;
		Xo=puntosArrastre[0].x;
		Xf=puntosArrastre[numeroPuntosArrastre+1].x;
		xo=Var->rangoMinimo();
		xf=Var->rangoMaximo();

		ConjuntoDifuso *CD;
		CD=Var->conjunto(NumCon);

		float x;
		x=xo+(X-Xo)*(xf-xo)/(Xf-Xo);
		if(x<xo){x=xo;}
		if(x>xf){x=xf;}
		x=CD->verificarPuntoClave(puntoArrastrado-1,x);
		CD->nuevoPuntoClave(puntoArrastrado-1,x);
		CD=NULL;
		pintarVariable(NumVar,NumCon);
	}
	Var=NULL;
}

void DialogoVariable::cambiaVariable(wxCommandEvent&   event)
{
	NumVar=listaVariables->GetSelection();
	NumCon=0;
	llenarDatos();
}

void DialogoVariable::cambiaConjunto(wxCommandEvent&   event)
{
	NumCon=listaConjuntos->GetSelection();
	llenarDatos();
}

void DialogoVariable::llenarDatos()
{
	listaVariables->Clear();
	for(unsigned int i=0;i<U->numeroVariables();i++)
	{
		listaVariables->Append(U->nombreVariable(i));
	}
	listaVariables->SetSelection(NumVar);
//	staticNombreVar->SetLabel(U->nombreVariable(NumVar));

	listaConjuntos->Clear();
	for(unsigned int i=0;i<U->variable(NumVar)->numeroConjuntos();i++)
	{
		listaConjuntos->Append(U->variable(NumVar)->conjunto(i)->nombre());
	}
	listaConjuntos->SetSelection(NumCon);

  comboTipoCon->SetSelection(U->variable(NumVar)->conjunto(NumCon)->identificador());

  int tmp;
  if(flagDifusor)
	{
	  tmp=U->variable(NumVar)->difusorEntrada()->identificador();
	  switch(tmp)
	  {
	  	case 1 : comboTipoDifusor->SetSelection(0);break;
	  	case 2 : comboTipoDifusor->SetSelection(1);break;
	  	case 5 : comboTipoDifusor->SetSelection(2);break;
	  	case 6 : comboTipoDifusor->SetSelection(3);break;
	  	case 8 : comboTipoDifusor->SetSelection(4);break;
	  }

	  float mn,mx,dx;
	  float difMn,difMx;
	  mn=U->variable(NumVar)->rangoMinimo();
	  mx=U->variable(NumVar)->rangoMaximo();
	  dx=(mx-mn)/100.0;
	  difMn=U->variable(NumVar)->difusorEntrada()->minimo();
	  difMx=U->variable(NumVar)->difusorEntrada()->maximo();
	  spinDifAncho->SetRange(dx,mx-mn);
	  spinDifAncho->SetValue(difMx-difMn);
	  spinDifAncho->SetIncrement((double)dx);
	  spinDifAncho->SetDigits(2);

	  spinDifIntervalos->SetValue(U->variable(NumVar)->difusorEntrada()->numeroPuntos());

	}else
	{
	  tmp=Concreto->concresor(NumVar)->identificador();
  	comboTipoConcresor->SetSelection(tmp);
	}

	pintarVariable(NumVar,NumCon);
	if(flagDifusor)
	{
		float x=0.5*(U->variable(NumVar)->rangoMinimo() + U->variable(NumVar)->rangoMaximo() );
		U->variable(NumVar)->difusorEntrada()->entrada(x);
		pintarDifusor(NumVar,NumCon);
	}

}

void DialogoVariable::OnEditarVar      (wxCommandEvent&   event)
{
	DialogoEditarVariable *dial;
	dial=new  DialogoEditarVariable(U->variable(NumVar),this);
	if(dial->ShowModal() == wxID_OK)
	{
		const char* ascii_str = (const char*)dial->nombre.mb_str(wxConvUTF8);
		U->variable(NumVar)->nombreVariable(ascii_str);
		U->variable(NumVar)->ajustar(dial->min_,dial->max_);
		U->variable(NumVar)->numeroIntervalos(dial->intervalos);
	}
	delete dial;
	llenarDatos();
}

void DialogoVariable::OnEliminarVar    (wxCommandEvent&   event)
{
	if(U->numeroVariables()<2)
	{
	  wxMessageBox(_T("No puede eliminar todas las variables"),_T("Atención"));
	  return;
	}
	wxMessageDialog *dial;
	dial=new wxMessageDialog (this, _T("Esta acción implica eliminar todas las reglas ¿Desea eliminar la variable?"), _T("Confirmación"), wxOK|wxCANCEL|wxCENTRE);
	if(dial->ShowModal() == wxID_OK)
	{
		U->eliminarVariable(NumVar);

		delete SLD->motor;
		delete SLD->concreto;
	  Norma       *Conjuncion  = new Maximo();
		SLD->motor=new MaquinaInferencia(SLD->entradas,SLD->salidas,1);
	  SLD->concreto=new BloqueConcrecion(SLD->motor);
  	SLD->concreto->autodefinirBloqueConcrecion(SLD->motor,Conjuncion);

		NumVar=0;
	}
	delete dial;
	llenarDatos();

}

void DialogoVariable::OnAdicionarVar   (wxCommandEvent&   event)
{
	wxMessageDialog *dial1;
	dial1=new wxMessageDialog (this, _T("Esta acción implica eliminar todas las reglas ¿Desea adicionar una variable?"), _T("Confirmación"), wxOK|wxCANCEL|wxCENTRE);
	if(dial1->ShowModal() == wxID_CANCEL)
	{
		delete dial1;
		return;
	}
	DialogoEditarVariable *dial;
	Variable *Var;
	Var=new Variable();
	Var->autodefinirConjuntosRectos(3);
	dial=new  DialogoEditarVariable(Var,this);
	if(dial->ShowModal() == wxID_OK)
	{
		const char* ascii_str = (const char*)dial->nombre.mb_str(wxConvUTF8);
		Var->nombreVariable(ascii_str);
		Var->ajustar(dial->min_,dial->max_);
		Var->numeroIntervalos(dial->intervalos);
		U->adicionarVariable(Var);

		delete SLD->motor;
		delete SLD->concreto;
	  Norma       *Conjuncion  = new Maximo();
		SLD->motor=new MaquinaInferencia(SLD->entradas,SLD->salidas,1);
	  SLD->concreto=new BloqueConcrecion(SLD->motor);
  	SLD->concreto->autodefinirBloqueConcrecion(SLD->motor,Conjuncion);

	}
	delete dial;
	llenarDatos();
}

void DialogoVariable::OnAutodefinirVar (wxCommandEvent&   event)
{
	DialogoAutodefinirVariable *dial;
	dial=new  DialogoAutodefinirVariable(U->variable(NumVar),this);
	if(dial->ShowModal() == wxID_OK)
	{
		if(dial->flagRectos)
		{
			U->variable(NumVar)->autodefinirConjuntosRectos(dial->numConjuntos);
		}else
		{
			U->variable(NumVar)->autodefinirConjuntosCurvos(dial->numConjuntos);
		}
	}
	delete dial;
	llenarDatos();
}

void DialogoVariable::OnEditarCon      (wxCommandEvent&   event)
{
	wxTextEntryDialog *dial;
	ConjuntoDifuso *CD;
	CD=U->variable(NumVar)->conjunto(NumCon);
	wxString nombre;
	nombre=CD->nombre();
	dial=new  wxTextEntryDialog(this,_("Etiqueta"),_("Etiqueta del conjunto"),nombre);
	if(dial->ShowModal() == wxID_OK)
	{
		wxString nom=dial->GetValue();
		const char* ascii_str = (const char*)nom.mb_str(wxConvUTF8);
		CD->nombre(ascii_str);
	}
	delete dial;
	llenarDatos();
}

void DialogoVariable::OnEliminarCon    (wxCommandEvent&   event)
{
	if(U->variable(NumVar)->numeroConjuntos()<2)
	{
	  wxMessageBox(_T("No puede eliminar todos los conjuntos"),_T("Atención"));
	  return;
	}
	wxMessageDialog *dial;
	dial=new wxMessageDialog (this, _T("Esta acción afectará la base de reglas ¿Desea eliminar el conjunto?"), _T("Confirmación"), wxOK|wxCANCEL|wxCENTRE);
	if(dial->ShowModal() == wxID_OK)
	{
		U->variable(NumVar)->eliminarConjuntos(NumCon);
		SLD->motor->etiquetaEliminada(flagDifusor , NumVar, NumCon);

		NumCon=0;
	}
	delete dial;
	llenarDatos();
}

void DialogoVariable::OnAdicionarCon   (wxCommandEvent&   event)
{
	wxString nombre=_T("Sin etiqueta");

	wxTextEntryDialog* dial;
	dial=new  wxTextEntryDialog(this,_("Etiqueta"),_("Etiqueta del conjunto"),nombre);
	if(dial->ShowModal() == wxID_OK)
	{
		wxString nom=dial->GetValue();
		const char* ascii_str = (const char*)nom.mb_str(wxConvUTF8);
		float mn,mx;
		float x1,x2,x3;
		mn=U->variable(NumVar)->rangoMinimo();
		mx=U->variable(NumVar)->rangoMaximo();
		x1=mn + (mx-mn)*3/8;
		x2=mn + (mx-mn)*4/8;
		x3=mn + (mx-mn)*5/8;

		ConjuntoDifuso *CD;
		CD=new ConjuntoTriangulo(ascii_str,x1,x2,x3);
		U->variable(NumVar)->adicionarConjuntos(CD);
		NumCon=U->variable(NumVar)->numeroConjuntos()-1;
		llenarDatos();
	}
	delete dial;
}

void DialogoVariable::OnTipoCon        (wxCommandEvent&   event)
{
	int nuevoTipo=comboTipoCon->GetSelection();

	char nombre[100];
	strcpy(nombre,U->variable(NumVar)->conjunto(NumCon)->nombre());
	float mn,a,b,mx;
	mn=U->variable(NumVar)->rangoMinimo();
	a=U->variable(NumVar)->conjunto(NumCon)->minimo();
	b=U->variable(NumVar)->conjunto(NumCon)->maximo();
	mx=U->variable(NumVar)->rangoMaximo();

	ConjuntoDifuso *conj;
	switch (nuevoTipo)
	{
		case 0 : conj=new ConjuntoL(nombre,mn,a,b);
				break;
		case 1 : conj=new ConjuntoTriangulo(nombre,a,(a+b)/2,b);
				break;
		case 2 : conj=new ConjuntoPi(nombre,a,a+(b-a)/3,a+(b-a)*2/3,b);
				break;
		case 3 : conj=new ConjuntoGamma(nombre,a,b,mx);
				break;
		case 4 : conj=new ConjuntoZ(nombre,mn,a,b);
				break;
		case 5 : conj=new ConjuntoCampana(nombre,a,(a+b)/2,b);
				break;
		case 6 : conj=new ConjuntoPiCampana(nombre,a,a+(b-a)/3,a+(b-a)*2/3,b);
				break;
		case 7 : conj=new ConjuntoS(nombre,a,b,mx);
				break;
		case 8 : conj=new ConjuntoSinglenton(nombre,a,(mx-mn)/100); //pico,delta
				break;
		case 9 :// conj=new ConjuntoPorPuntos(nombre,,,); //min,max,float *dt, int puntos
				break;
		default:break;
	}
	U->variable(NumVar)->eliminarConjuntos(NumCon);
	U->variable(NumVar)->insertarConjuntos(conj,NumCon);
	llenarDatos();

}

void DialogoVariable::OnRightClick (wxMouseEvent& event)
{
	wxPoint tp(event.GetX(),event.GetY());
	puntoArrastrado=0;
	for(int i=1;i<=numeroPuntosArrastre+1;i++)
	{
		wxRect rect(puntosArrastre[i].x-tamArrastre,puntosArrastre[i].y-tamArrastre,tamArrastre*2,tamArrastre*2);
		if(rect.Contains(tp))
		{
			float arrastre[10];

			wxTextEntryDialog *dial;
			ConjuntoDifuso *CD;
			CD=U->variable(NumVar)->conjunto(NumCon);
			CD->puntosClaves(arrastre);

			wxString valor;
			valor << arrastre[i-1];

			dial=new  wxTextEntryDialog(this,_("Valor actual"),_("Valor del punto"),valor);
			if(dial->ShowModal() == wxID_OK)
			{
				puntoArrastrado=i;

				double x;
				wxString str;
				str=dial->GetValue();
				str.ToDouble(&x);

				if(x<U->variable(NumVar)->rangoMinimo()){x=U->variable(NumVar)->rangoMinimo();}
				if(x>U->variable(NumVar)->rangoMaximo()){x=U->variable(NumVar)->rangoMaximo();}
				x=CD->verificarPuntoClave(puntoArrastrado-1,(float)x);

				CD->nuevoPuntoClave(puntoArrastrado-1,(float)x);
				CD=NULL;
				llenarDatos();
			}
			delete dial;
		}
	}
}

void DialogoVariable::cambiaDifusor(wxCommandEvent&   event)
{
  if(!flagDifusor) return;

	float mn,mx,x,dx;
	mn=U->rangoMinimoVariable(NumVar);
	mx=U->rangoMaximoVariable(NumVar);
	x=(mn+mx)/2;
	dx=(mx-mn)/100;

  Difusor *dif;
  int tipo=comboTipoDifusor->GetSelection();
  switch(tipo)
  {
		case 0 :dif=new DifusorTriangulo(x,dx*20,dx*20);
				U->variable(NumVar)->difusorEntrada(dif);
				U->numeroPuntosDifusor(NumVar,3);
				break;
		case 1 :dif=new DifusorPi(x,dx*20,dx*10,dx*10,dx*20);
				U->variable(NumVar)->difusorEntrada(dif);
				U->numeroPuntosDifusor(NumVar,5);
				break;
		case 2 :dif=new DifusorCampana(x,dx*20,dx*20);
				U->variable(NumVar)->difusorEntrada(dif);
				U->numeroPuntosDifusor(NumVar,5);
				break;
		case 3 :dif=new DifusorPiCampana(x,dx*20,dx*10,dx*10,dx*20);
				U->variable(NumVar)->difusorEntrada(dif);
				U->numeroPuntosDifusor(NumVar,5);
				break;
  	default:
		case 4 :dif=new DifusorSinglenton(x,dx);
				U->variable(NumVar)->difusorEntrada(dif);
				U->numeroPuntosDifusor(NumVar,1);
				break;
  }
  llenarDatos();
}

void DialogoVariable::cambiaConcresor(wxCommandEvent&   event)
{
  if(flagDifusor) return;

  MaquinaInferencia *maq       =Concreto->motor();
  Norma             *conjuncion=Concreto->conjuncion();
  Concresor *conc;
  int tipo=comboTipoConcresor->GetSelection();
  switch(tipo)
  {
		case 0 :conc=new PrimerMaximo         (maq,NumVar,conjuncion);break;
		case 1 :conc=new UltimoMaximo         (maq,NumVar,conjuncion);break;
		case 2 :conc=new MediaDeMaximos       (maq,NumVar,conjuncion);break;
		case 3 :conc=new CentroDeGravedad     (maq,NumVar,conjuncion);break;
		case 4 :conc=new Altura               (maq,NumVar,conjuncion);break;
		default:conc=new CentroDeGravedad     (maq,NumVar,conjuncion);break;
  }
	Concreto->eliminarConcresor(NumVar);
	Concreto->insertarConcresor(conc,NumVar);
  llenarDatos();
}

void DialogoVariable::OnSpinIntervalos (wxSpinEvent&   event)
{
  if(!flagDifusor) return;

	int num=spinDifIntervalos->GetValue();
	U->variable(NumVar)->difusorEntrada()->numeroPuntos(num);
	pintarDifusor(NumVar,NumCon);
}

void DialogoVariable::OnSpinAncho      (wxSpinDoubleEvent&   event)
{
  if(!flagDifusor) return;

  float ancho=spinDifAncho->GetValue();
  float mn,mx;
  mn=U->variable(NumVar)->difusorEntrada()->centro() - ancho/2.0;
  mx=U->variable(NumVar)->difusorEntrada()->centro() + ancho/2.0;
  U->variable(NumVar)->difusorEntrada()->ajustar(mn,mx);
	pintarDifusor(NumVar,NumCon);
}

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
    EVT_BUTTON(DLG_VARIABLE_VARETIQUETAR    , DialogoVariable::OnEtiquetarVar)
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
:wxDialog(parent,wxID_ANY,wxString(_("Design of input or output universes")))
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
	sizerBotonesVariable   = new wxFlexGridSizer(1,5,0);
	sizerControlesConjunto = new wxFlexGridSizer(4,1,0);
	sizerBotonesConjunto   = new wxFlexGridSizer(1,4,0);
	sizerBotonesDifConc    = new wxFlexGridSizer(2,3,0);
	sizerFlexiVariable     = new wxFlexGridSizer(1,2,0);
	sizerImgVariable       = new wxFlexGridSizer(2,2,0);
	sizerStaticVariables   = new wxStaticBoxSizer(wxVERTICAL,this,_("Variables"));
	sizerStaticConjuntos   = new wxStaticBoxSizer(wxVERTICAL,this,_("Sets"));
  sizerOKCancel    = new wxFlexGridSizer(2,1,0);

	listaVariables    = new wxListBox(this,DLG_VARIABLE_LISTAVAR,wxDefaultPosition,wxSize(150,180));
	listaConjuntos    = new wxListBox(this,DLG_VARIABLE_LISTACON,wxDefaultPosition,wxSize(150,180));
  canvasVar         = new wxSizerItem(600,200);
  staticLabelVar    = new wxStaticText(this,wxID_ANY,_("Linguistic variable"));

  if(flagDifusor)
	{
	  canvasDif         = new wxSizerItem(300,200);

	  staticLabelDif      = new wxStaticText(this,wxID_ANY,_("Fuzzyfier"));
		comboTipoDifusor    = new wxComboBox(this,DLG_VARIABLE_COMBODIFUSOR);
	  spinDifIntervalos   = new wxSpinCtrl(this,DLG_VARIABLE_SPINDIFINTERVALOS, "",wxDefaultPosition,wxSize(120,25));
	  spinDifAncho        = new wxSpinCtrlDouble(this,DLG_VARIABLE_SPINDIFANCHO,"",wxDefaultPosition,wxSize(120,25));
		comboTipoConcresor  = NULL;
		sizerStaticDifConc  = new wxStaticBoxSizer(wxVERTICAL,this,_("Fuzzyfier"));
		staticTipoDif       = new wxStaticText(this,wxID_ANY,_("Type"));
		staticInterDif      = new wxStaticText(this,wxID_ANY,_("Evaluation points"));
		staticAnchoDif      = new wxStaticText(this,wxID_ANY,_("Width"));

		sizerBotonesDifConc->Add(staticTipoDif        , 1, wxALIGN_RIGHT|wxALL, 1);
		sizerBotonesDifConc->Add(comboTipoDifusor     , 1, wxALIGN_LEFT |wxALL, 1);
		sizerBotonesDifConc->Add(staticInterDif       , 1, wxALIGN_RIGHT|wxALL, 1);
		sizerBotonesDifConc->Add(spinDifIntervalos    , 1, wxALIGN_LEFT |wxALL, 1);
		sizerBotonesDifConc->Add(staticAnchoDif       , 1, wxALIGN_RIGHT|wxALL, 1);
		sizerBotonesDifConc->Add(spinDifAncho         , 1, wxALIGN_LEFT |wxALL, 1);

		comboTipoDifusor->Append(ConjuntoDifuso::tipo(1));
		comboTipoDifusor->Append(ConjuntoDifuso::tipo(2));
		comboTipoDifusor->Append(ConjuntoDifuso::tipo(5));
		comboTipoDifusor->Append(ConjuntoDifuso::tipo(6));
		comboTipoDifusor->Append(ConjuntoDifuso::tipo(8));
	}else
	{
	  canvasDif         = new wxSizerItem(1,200);

	  staticLabelDif      = new wxStaticText(this,wxID_ANY,"");
		comboTipoDifusor    = NULL;
	  spinDifIntervalos   = NULL;
	  spinDifAncho        = NULL;
		staticTipoDif       = NULL;
		staticInterDif      = NULL;
		staticAnchoDif      = NULL;

		comboTipoConcresor  = new wxComboBox(this,DLG_VARIABLE_COMBOCONCRESOR);
		sizerStaticDifConc  = new wxStaticBoxSizer(wxVERTICAL,this,_("Defuzzyfier"));
		sizerBotonesDifConc->Add(comboTipoConcresor     , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 1);

		for(int i=0;i<5;i++)
		{
			comboTipoConcresor->Append(Concresor::nombre(i));
		}
	}

	buttonEditarVar      = new wxButton(this,DLG_VARIABLE_VAREDITAR      ,_("Edit"));
	buttonEliminarVar    = new wxButton(this,DLG_VARIABLE_VARELIMINAR    ,_("Delete"));
	buttonAdicionarVar   = new wxButton(this,DLG_VARIABLE_VARADICIONAR   ,_("Add"));
	buttonAutodefinirVar = new wxButton(this,DLG_VARIABLE_VARAUTODEFINIR ,_("Selfdefinition"));
	buttonEtiquetarVar   = new wxButton(this,DLG_VARIABLE_VARETIQUETAR   ,_("Labeling"));
	buttonEditarCon      = new wxButton(this,DLG_VARIABLE_CONEDITAR      ,_("Label"));
	buttonEliminarCon    = new wxButton(this,DLG_VARIABLE_CONELIMINAR    ,_("Delete"));
	buttonAdicionarCon   = new wxButton(this,DLG_VARIABLE_CONADICIONAR   ,_("Add"));
  buttonOK             = new wxButton(this,wxID_OK,_("OK"));
  buttonCancel         = new wxButton(this,wxID_CANCEL,_("Cancel"));
	comboTipoCon         = new wxComboBox(this,DLG_VARIABLE_CONTIPO);

	for(int i=0;i<9;i++)
	{
		comboTipoCon->Append(ConjuntoDifuso::tipo(i));
	}

///////////////////
	sizerBotonesVariable->Add(buttonEditarVar     , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 1);
	sizerBotonesVariable->Add(buttonEliminarVar   , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 1);
	sizerBotonesVariable->Add(buttonAdicionarVar  , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 1);
	sizerBotonesVariable->Add(buttonAutodefinirVar, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 1);
	sizerBotonesVariable->Add(buttonEtiquetarVar  , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 1);

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
	for(int i=1;i<=numeroPuntosArrastre+0;i++)
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
		double xo,xf;
		Xo=puntosArrastre[0].x;
		Xf=puntosArrastre[numeroPuntosArrastre+1].x;
		xo=Var->rangoMinimo();
		xf=Var->rangoMaximo();

		ConjuntoDifuso *CD;
		CD=Var->conjunto(NumCon);

		double x;
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

	  double mn,mx,dx;
	  double difMn,difMx;
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
		double x=0.5*(U->variable(NumVar)->rangoMinimo() + U->variable(NumVar)->rangoMaximo() );
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
	wxMessageDialog *dial1;
	dial1=new wxMessageDialog (this, _("Do you want to delete the variable?"), _("Confirmation"), wxOK|wxCANCEL|wxCENTRE);
	if(dial1->ShowModal() == wxID_CANCEL)
	{
		delete dial1;
		return;
	}
	if(U->numeroVariables()<2)
	{
	  wxMessageBox(_("You cannot delete all the variables"),_("Warning"));
	  return;
	}
	wxMessageDialog *dial;
	U->eliminarVariable(NumVar);

	if(flagDifusor)
	{
		SLD->motor->eliminarEntrada(NumVar);
	}else
	{
		SLD->motor->eliminarSalida(NumVar);
		SLD->concreto->eliminarSalida(NumVar);
	}

	NumVar=0;
	llenarDatos();
}

void DialogoVariable::OnAdicionarVar   (wxCommandEvent&   event)
{
	DialogoEditarVariable *dial;
	Variable *Var;
	Var=new Variable();
	wxString name=_("Without name");
	Var->nombreVariable(std::string(name.mb_str()));
	Var->autodefinirConjuntosRectos(3);
	dial=new  DialogoEditarVariable(Var,this);
	if(dial->ShowModal() == wxID_OK)
	{
		const char* ascii_str = (const char*)dial->nombre.mb_str(wxConvUTF8);
		Var->nombreVariable(ascii_str);
		Var->ajustar(dial->min_,dial->max_);
		Var->numeroIntervalos(dial->intervalos);
		U->adicionarVariable(Var);

		if(flagDifusor)
		{
			SLD->motor->adicionarEntrada();
		}else
		{
			SLD->motor->adicionarSalida();
			SLD->concreto->adicionarSalida();
		}
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
	}
	delete dial;
	llenarDatos();
}

void DialogoVariable::OnEtiquetarVar (wxCommandEvent&   event)
{
	DialogoAsignarEtiquetas *dial;
	dial=new  DialogoAsignarEtiquetas(U->variable(NumVar),this);
	if(dial->ShowModal() == wxID_OK)
	{
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
	dial=new  wxTextEntryDialog(this,_("Label"),_("Set label"),nombre);
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
	  wxMessageBox(_("You cannot delete all the sets"),_("Warning"));
	  return;
	}
	wxMessageDialog *dial;
	dial=new wxMessageDialog (this, _("This action will affect the rule base ¿Do you want to delete the set?"), _("Confirmation"), wxOK|wxCANCEL|wxCENTRE);
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
	wxString nombre=_("Without label");

	wxTextEntryDialog* dial;
	dial=new  wxTextEntryDialog(this,_("Label"),_("Set label"),nombre);
	if(dial->ShowModal() == wxID_OK)
	{
		wxString nom=dial->GetValue();
		const char* ascii_str = (const char*)nom.mb_str(wxConvUTF8);
		double mn,mx;
		double x1,x2,x3;
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

	string nombre;
	nombre=U->variable(NumVar)->conjunto(NumCon)->nombre();
	double mn,a,b,mx;
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
		case 9 :// conj=new ConjuntoPorPuntos(nombre,,,); //min,max,double *dt, int puntos
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
			double arrastre[10];

			wxTextEntryDialog *dial;
			ConjuntoDifuso *CD;
			CD=U->variable(NumVar)->conjunto(NumCon);
			CD->puntosClaves(arrastre);

			wxString valor;
			valor << arrastre[i-1];

			dial=new  wxTextEntryDialog(this,_("Actual value"),_("Value of the point"),valor);
			if(dial->ShowModal() == wxID_OK)
			{
				puntoArrastrado=i;

				double x;
				wxString str;
				str=dial->GetValue();
				str.ToDouble(&x);

				if(x<U->variable(NumVar)->rangoMinimo()){x=U->variable(NumVar)->rangoMinimo();}
				if(x>U->variable(NumVar)->rangoMaximo()){x=U->variable(NumVar)->rangoMaximo();}
				x=CD->verificarPuntoClave(puntoArrastrado-1,(double)x);

				CD->nuevoPuntoClave(puntoArrastrado-1,(double)x);
				CD=NULL;
				llenarDatos();
			}
			delete dial;
			return;
		}
	}
	wxRect canvas;
	canvas=canvasVar->GetRect();
	if(canvas.Contains(tp))
	{
		copiarAlClipboard(1);
    wxMessageBox(_("Image has been copied to clipboard"));
	}
	canvas=canvasDif->GetRect();
	if(canvas.Contains(tp))
	{
		copiarAlClipboard(2);
    wxMessageBox(_("Image has been copied to clipboard"));
	}
}

void DialogoVariable::cambiaDifusor(wxCommandEvent&   event)
{
  if(!flagDifusor) return;

	double mn,mx,x,dx;
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

  double ancho=spinDifAncho->GetValue();
  double mn,mx;
  mn=U->variable(NumVar)->difusorEntrada()->centro() - ancho/2.0;
  mx=U->variable(NumVar)->difusorEntrada()->centro() + ancho/2.0;
  U->variable(NumVar)->difusorEntrada()->ajustar(mn,mx);
	pintarDifusor(NumVar,NumCon);
}

void DialogoVariable::copiarAlClipboard(int caso)
{
	wxRect canvas;
	switch(caso)
	{
	  case 1 : canvas=canvasVar->GetRect(); break;
	  case 2 : canvas=canvasDif->GetRect(); break;
	  default: return;
	}
	if (wxTheClipboard->Open())
	{
		wxTheClipboard->Clear();

		wxClientDC dcLocal(this);
		int x = canvas.GetTopLeft().x;
		int y = canvas.GetTopLeft().y;
		int w = canvas.GetWidth();
		int h = canvas.GetHeight();

		wxBitmap bitmap(w,h);
		wxMemoryDC memory;
		memory.SelectObject(bitmap);
		memory.Blit(0,0, w, h, &dcLocal, x, y);

		wxTheClipboard->SetData( new wxBitmapDataObject(bitmap) );
		wxTheClipboard->Close();
	}
}

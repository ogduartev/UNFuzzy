#include "DialogoMotor.h"

BEGIN_EVENT_TABLE(DialogoMotor, wxDialog)
    EVT_CLOSE(DialogoMotor::OnClose)
    EVT_COMBOBOX(DLG_MOTOR_IMPLICACION     , DialogoMotor::OnImplicacion)
    EVT_COMBOBOX(DLG_MOTOR_MINCOMPOSICION  , DialogoMotor::OnMinComposicion)
    EVT_COMBOBOX(DLG_MOTOR_MAXCOMPOSICION  , DialogoMotor::OnMaxComposicion)
    EVT_COMBOBOX(DLG_MOTOR_AND             , DialogoMotor::OnAnd)
    EVT_COMBOBOX(DLG_MOTOR_CONJUNCION      , DialogoMotor::OnConjuncion)
    EVT_BUTTON(wxID_OK   , DialogoMotor::OnOK)
END_EVENT_TABLE()

DialogoMotor::DialogoMotor(SistemaLogicaDifusa *SLD, wxWindow *parent)
:wxDialog(parent,wxID_ANY,wxString(_("Inference Engine Parameters")))
{
	Motor = SLD->motor;
	Concreto = SLD->concreto;

  wxFlexGridSizer* sizerTotal;
  wxFlexGridSizer* sizerControles;
  wxFlexGridSizer* sizerOKCancel;

  sizerTotal       = new wxFlexGridSizer(1,2,0);
  sizerControles   = new wxFlexGridSizer(3,4,0);
  sizerOKCancel    = new wxFlexGridSizer(2,1,0);

  staticImplicacion    = new wxStaticText(this,wxID_ANY,_("Implication"));
  staticMinComposicion = new wxStaticText(this,wxID_ANY,_("Composition-Min"));
  staticMaxComposicion = new wxStaticText(this,wxID_ANY,_("Composition-Max"));
  staticAnd            = new wxStaticText(this,wxID_ANY,_("And"));
  staticConjuncion     = new wxStaticText(this,wxID_ANY,_("Rule Aggregation"));
  wxStaticText *staticEmpty;
  staticEmpty          = new wxStaticText(this,wxID_ANY,"");
  comboImplicacion     = new wxComboBox(this,DLG_MOTOR_IMPLICACION   ,"",wxDefaultPosition,wxSize(150,25));
  comboMinComposicion  = new wxComboBox(this,DLG_MOTOR_MINCOMPOSICION,"",wxDefaultPosition,wxSize(150,25));
  comboMaxComposicion  = new wxComboBox(this,DLG_MOTOR_MAXCOMPOSICION,"",wxDefaultPosition,wxSize(150,25));
  comboAnd             = new wxComboBox(this,DLG_MOTOR_AND           ,"",wxDefaultPosition,wxSize(150,25));
  comboConjuncion      = new wxComboBox(this,DLG_MOTOR_CONJUNCION    ,"",wxDefaultPosition,wxSize(150,25));

  llenarCombos();
  seleccionarCombos();

  buttonOK         = new wxButton(this,wxID_OK,_("OK"));
  buttonCancel     = new wxButton(this,wxID_CANCEL,_("Cancel"));

	sizerControles->Add(staticImplicacion, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerControles->Add(staticMinComposicion, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerControles->Add(staticMaxComposicion, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerControles->Add(comboImplicacion, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerControles->Add(comboMinComposicion, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerControles->Add(comboMaxComposicion, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerControles->Add(staticAnd        , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerControles->Add(staticConjuncion , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerControles->Add(staticEmpty , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerControles->Add(comboAnd        , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerControles->Add(comboConjuncion , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

	sizerOKCancel->Add(buttonOK, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerOKCancel->Add(buttonCancel, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

  sizerTotal->Add(sizerControles   , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
  sizerTotal->Add(sizerOKCancel    , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

  this->SetSizer(sizerTotal);
  this->Layout();
  sizerTotal->Fit(this);

}

DialogoMotor::~DialogoMotor()
{
	//dtor
}

void DialogoMotor::OnClose       (wxCloseEvent&   event)
{
	if(verificar())
	{
		EndModal(wxID_OK);
	}
}

void DialogoMotor::OnOK(wxCommandEvent&   event)
{
	if(verificar())
	{
		EndModal(wxID_OK);
	}
}

void DialogoMotor::llenarCombos()
{
	for(int i=0;i<9;i++)
	{
		comboImplicacion->Append(Implicacion::tipo(i));
	}

	comboMinComposicion->Append(Norma::tipo(1));
	comboMinComposicion->Append(Norma::tipo(0));
	comboMinComposicion->Append(Norma::tipo(2));
	comboMinComposicion->Append(Norma::tipo(3));
	comboMinComposicion->Append(Norma::tipo(4));
	comboMinComposicion->Append(Norma::tipo(7));
	comboMinComposicion->Append(Norma::tipo(8));
	comboMinComposicion->Append(Norma::tipo(9));

	comboMaxComposicion->Append(Norma::tipo(10));
	comboMaxComposicion->Append(Norma::tipo(11));
	comboMaxComposicion->Append(Norma::tipo(12));
	comboMaxComposicion->Append(Norma::tipo(6));

	comboAnd->Append(Norma::tipo(1));
	comboAnd->Append(Norma::tipo(0));
	comboAnd->Append(Norma::tipo(2));
	comboAnd->Append(Norma::tipo(3));
	comboAnd->Append(Norma::tipo(4));
	comboAnd->Append(Norma::tipo(5));
	comboAnd->Append(Norma::tipo(6));
	comboAnd->Append(Norma::tipo(8));
	comboAnd->Append(Norma::tipo(9));

	comboConjuncion->Append(Norma::tipo(10));
	comboConjuncion->Append(Norma::tipo(11));
	comboConjuncion->Append(Norma::tipo(12));
	comboConjuncion->Append(Norma::tipo(6));
	comboConjuncion->Append("----------");
	comboConjuncion->Append(Norma::tipo(1));
	comboConjuncion->Append(Norma::tipo(0));
	comboConjuncion->Append(Norma::tipo(2));
	comboConjuncion->Append(Norma::tipo(3));
	comboConjuncion->Append(Norma::tipo(4));
	comboConjuncion->Append(Norma::tipo(5));
	comboConjuncion->Append(Norma::tipo(7));
	comboConjuncion->Append(Norma::tipo(8));
	comboConjuncion->Append(Norma::tipo(9));
}

void DialogoMotor::seleccionarCombos()
{
	int tipo,sel;

	tipo=Motor->implicacion()->identificador();
	sel=tipo;
	comboImplicacion->SetSelection(sel);

	tipo=Motor->minComposicion()->identificador();
	switch(tipo)
	{
		case 0 : sel = 1; break;
		case 1 : sel = 0; break;
		case 2 : sel = 2; break;
		case 3 : sel = 3; break;
		case 4 : sel = 4; break;
		case 5 : sel = 5; break;
		case 7 : sel = 7; break;
		case 8 : sel = 8; break;
		case 9 : sel = 9; break;
	}
	comboMinComposicion->SetSelection(sel);

	tipo=Motor->maxComposicion()->identificador();
	switch(tipo)
	{
		case 10 : sel = 0; break;
		case 11 : sel = 1; break;
		case 12 : sel = 2; break;
		case 6  : sel = 3; break;
	}
	comboMaxComposicion->SetSelection(sel);

	tipo=Motor->and_()->identificador();
	switch(tipo)
	{
		case 0 : sel = 1; break;
		case 1 : sel = 0; break;
		case 2 : sel = 2; break;
		case 3 : sel = 3; break;
		case 4 : sel = 4; break;
		case 5 : sel = 5; break;
		case 7 : sel = 7; break;
		case 8 : sel = 8; break;
		case 9 : sel = 9; break;
	}
	comboAnd->SetSelection(sel);

	tipo=Concreto->conjuncion()->identificador();
	switch(tipo)
	{
		case 0 : sel = 6; break;
		case 1 : sel = 5; break;
		case 2 : sel = 7; break;
		case 3 : sel = 8; break;
		case 4 : sel = 9; break;
		case 5 : sel = 10; break;
		case 6 : sel = 3; break;
		case 7 : sel = 11; break;
		case 8 : sel = 12; break;
		case 9 : sel = 9; break;
		case 10: sel = 0; break;
		case 11: sel = 1; break;
		case 12: sel = 2; break;
	}
	comboConjuncion->SetSelection(sel);
}

void DialogoMotor::OnImplicacion(wxCommandEvent& event)
{
	nuevaImplicacion();
}

void DialogoMotor::OnMinComposicion(wxCommandEvent& event)
{
	nuevaMinComposicion();
}

void DialogoMotor::OnMaxComposicion(wxCommandEvent& event)
{
	nuevaMaxComposicion();
}

void DialogoMotor::OnAnd(wxCommandEvent& event)
{
	nuevaAnd();
}

void DialogoMotor::OnConjuncion(wxCommandEvent& event)
{
	nuevaConjuncion();
}

void DialogoMotor::nuevaImplicacion()
{
	Implicacion *imp;
	int caso;
	caso=comboImplicacion->GetSelection();
	switch(caso)
	{
		case 0:imp=new ImplicacionProducto();
				break;
		case 1:imp=new ImplicacionMinimo();
				break;
		case 2:imp=new ImplicacionKleenDienes();
				break;
		case 3:imp=new ImplicacionLukasiewicz();
				break;
		case 4:imp=new ImplicacionZadeh();
				break;
		case 5:imp=new ImplicacionEstocastica();
				break;
		case 6:imp=new ImplicacionGoguen();
				break;
		case 7:imp=new ImplicacionGodel();
				break;
		case 8:imp=new ImplicacionAguda();
				break;
		default:break;
	}
	Motor->implicacion(imp);
  /*FALTA VERIFICACION*/
}

void DialogoMotor::nuevaMinComposicion()
{
	int caso;
	caso=comboMinComposicion->GetSelection();
	Norma* nor=nuevaTNorma(caso);
	if(nor)
	{
		Motor->minComposicion(nor);
	}
}

void DialogoMotor::nuevaMaxComposicion()
{
	int caso;
	caso=comboMaxComposicion->GetSelection();
	Norma* nor=nuevaSNorma(caso);
	if(nor)
	{
		Motor->maxComposicion(nor);
	}
}

void DialogoMotor::nuevaAnd()
{
	int caso;
	caso=comboAnd->GetSelection();
	Norma* nor=nuevaTNorma(caso);
	if(nor)
	{
		Motor->and_(nor);
	}
}

void DialogoMotor::nuevaConjuncion()
{
	Norma *nor;
	int caso;
	caso=comboConjuncion->GetSelection();
	if(caso==4)
	{
    seleccionarCombos();
		return;
	}
	if(caso<4)
	{
		nor=nuevaSNorma(caso);
	}else
	{
		nor=nuevaTNorma(caso-5);
	}
	if(nor)
	{
		delete Concreto->conjuncion();
		Concreto->conjuncion(nor);
	}
}

Norma* DialogoMotor::nuevaSNorma(int caso)
{
	Norma *nor=NULL;
	double par;
	switch(caso)
	{
			case 0:nor=new Maximo();
					break;
			case 1:nor=new SumaAcotada();
					break;
			case 2:nor=new SumaDrastica();
					break;
			case 3:
					par=1.0;
					getParametro(&par,0.0,10.0);
					nor=new FamiliaSp(par);
					break;
	}
	return nor;
}

Norma* DialogoMotor::nuevaTNorma(int caso)
{
	Norma *nor=NULL;
	double par;
	switch(caso)
	{
		case 0:nor=new Minimo();
				break;
		case 1:nor=new Producto();
				break;
		case 2:nor=new ProductoAcotado();
				break;
		case 3:nor=new ProductoDrastico();
				break;
		case 4:
				par=1.0;
				getParametro(&par,0.0,10.0);
				nor=new FamiliaTp(par);
				break;
		case 5:
				par=1.0;
				getParametro(&par,0.0,10.0);
				nor=new FamiliaHp(par);
				break;
		case 6:
				par=2.0;
				getParametro(&par,1.0,10.0);
				nor=new FamiliaFp(par);
				break;
		case 7:
				par=1.0;
				getParametro(&par,0.0,10.0);
				nor=new FamiliaYp(par);
				break;
		case 8:
				par=1.0;
				getParametro(&par,0.0,1.0);
				nor=new FamiliaAp(par);
				break;
		default:break;
	}
	return nor;
}

void DialogoMotor::getParametro(double *par,double minimo,double maximo)
{
	double tmp=(double)(*par);
	wxTextValidator Validator(wxFILTER_NUMERIC);
	wxString msg,val;
	val << *par;
	msg << _("Enter the family parameter, between ") << minimo << _(" and ") << maximo;
	wxTextEntryDialog dlg(this,msg,_("Parameter of the Norm familiy"),val);
	if(dlg.ShowModal()==wxID_OK)
	{
	  dlg.GetValue().ToDouble(&tmp);
	  *par=(double)tmp;
	}
	if(*par < minimo){*par=minimo;}
	if(*par > maximo){*par=maximo;}
	msg = "";
	msg << _("The parameter applied will be ") << *par;
	wxMessageBox(msg,_("Information"));
}

bool DialogoMotor::verificar()
{
	bool flag=true;
	double a,b;
	a=Motor->implicacion()->defecto();
	b=Concreto->conjuncion()->ToSNorm();
	if(a!=b)
	{
		flag=false;
		wxString str1,str2;
		if(a==0.0)
		{
			str1 = _("The selected implication requires a Conjunction type 'Union'. You have selected one of type 'Intersection'");
			str2 = _("¡Warning!");
		}else
		{
			str1 = _("The selected implication requires a Conjunction type 'Intersection'. You have selected one of type 'Union'");
			str2 = _("¡Warning!");
		}
		str1 << "\n" <<_("Do you want to keep this choice?");
		if(wxMessageDialog(this, str1, str2, wxYES_NO|wxNO_DEFAULT).ShowModal() == wxID_YES)
		{
			flag=true;
		}
	}
	return flag;
}

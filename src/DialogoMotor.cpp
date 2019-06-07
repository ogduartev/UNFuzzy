#include "DialogoMotor.h"

BEGIN_EVENT_TABLE(DialogoMotor, wxDialog)
    EVT_CLOSE(DialogoMotor::OnClose)
    EVT_COMBOBOX(DLG_MOTOR_IMPLICACION  , DialogoMotor::OnImplicacion)
    EVT_COMBOBOX(DLG_MOTOR_COMPOSICION  , DialogoMotor::OnComposicion)
    EVT_COMBOBOX(DLG_MOTOR_AND          , DialogoMotor::OnAnd)
    EVT_COMBOBOX(DLG_MOTOR_CONJUNCION   , DialogoMotor::OnConjuncion)
    EVT_BUTTON(wxID_OK   , DialogoMotor::OnOK)
END_EVENT_TABLE()

DialogoMotor::DialogoMotor(SistemaLogicaDifusa *SLD, wxWindow *parent)
:wxDialog(parent,wxID_ANY,wxString(wxT("Parametros del motor de inferencia")))
{
	Motor = SLD->motor;
	Concreto = SLD->concreto;

  wxFlexGridSizer* sizerTotal;
  wxFlexGridSizer* sizerControles;
  wxFlexGridSizer* sizerOKCancel;

  sizerTotal       = new wxFlexGridSizer(1,2,0);
  sizerControles   = new wxFlexGridSizer(2,4,0);
  sizerOKCancel    = new wxFlexGridSizer(2,1,0);

  staticImplicacion = new wxStaticText(this,wxID_ANY,_T("Implicación"));
  staticComposicion = new wxStaticText(this,wxID_ANY,_T("Composición"));
  staticAnd         = new wxStaticText(this,wxID_ANY,_T("And"));
  staticConjuncion  = new wxStaticText(this,wxID_ANY,_T("Conjunción"));
  comboImplicacion  = new wxComboBox(this,DLG_MOTOR_IMPLICACION,_T(""),wxDefaultPosition,wxSize(150,25));
  comboComposicion  = new wxComboBox(this,DLG_MOTOR_COMPOSICION,_T(""),wxDefaultPosition,wxSize(150,25));
  comboAnd          = new wxComboBox(this,DLG_MOTOR_AND        ,_T(""),wxDefaultPosition,wxSize(150,25));
  comboConjuncion   = new wxComboBox(this,DLG_MOTOR_CONJUNCION ,_T(""),wxDefaultPosition,wxSize(150,25));

  llenarCombos();
  seleccionarCombos();

  buttonOK         = new wxButton(this,wxID_OK,_("OK"));
  buttonCancel     = new wxButton(this,wxID_CANCEL,_("Cancelar"));

	sizerControles->Add(staticImplicacion, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerControles->Add(staticComposicion, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerControles->Add(comboImplicacion, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerControles->Add(comboComposicion, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerControles->Add(staticAnd        , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerControles->Add(staticConjuncion , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
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
	comboImplicacion->Append(_T(IDS_IMPLICA_TN_TIPO_1));
	comboImplicacion->Append(_T(IDS_IMPLICA_TN_TIPO_0));
	comboImplicacion->Append(_T(IDS_IMPLICA_IF_TIPO_2));
	comboImplicacion->Append(_T(IDS_IMPLICA_IF_TIPO_3));
	comboImplicacion->Append(_T(IDS_IMPLICA_IF_TIPO_4));
	comboImplicacion->Append(_T(IDS_IMPLICA_IF_TIPO_5));
	comboImplicacion->Append(_T(IDS_IMPLICA_IF_TIPO_6));
	comboImplicacion->Append(_T(IDS_IMPLICA_IF_TIPO_7));
	comboImplicacion->Append(_T(IDS_IMPLICA_IF_TIPO_8));

	comboComposicion->Append(_T(IDS_T_NORMA_TIPO_1));
	comboComposicion->Append(_T(IDS_T_NORMA_TIPO_0));
	comboComposicion->Append(_T(IDS_T_NORMA_TIPO_2));
	comboComposicion->Append(_T(IDS_T_NORMA_TIPO_3));
	comboComposicion->Append(_T(IDS_T_NORMA_TIPO_4));
	comboComposicion->Append(_T(IDS_T_NORMA_TIPO_5));
//	comboComposicion->Append(_T(IDS_T_NORMA_TIPO_6));
	comboComposicion->Append(_T(IDS_T_NORMA_TIPO_7));
	comboComposicion->Append(_T(IDS_T_NORMA_TIPO_8));
	comboComposicion->Append(_T(IDS_T_NORMA_TIPO_9));

	comboAnd->Append(_T(IDS_T_NORMA_TIPO_1));
	comboAnd->Append(_T(IDS_T_NORMA_TIPO_0));
	comboAnd->Append(_T(IDS_T_NORMA_TIPO_2));
	comboAnd->Append(_T(IDS_T_NORMA_TIPO_3));
	comboAnd->Append(_T(IDS_T_NORMA_TIPO_4));
	comboAnd->Append(_T(IDS_T_NORMA_TIPO_5));
//	comboAnd->Append(_T(IDS_T_NORMA_TIPO_6));
	comboAnd->Append(_T(IDS_T_NORMA_TIPO_7));
	comboAnd->Append(_T(IDS_T_NORMA_TIPO_8));
	comboAnd->Append(_T(IDS_T_NORMA_TIPO_9));

	comboConjuncion->Append(_T(IDS_S_NORMA_TIPO_10));
	comboConjuncion->Append(_T(IDS_S_NORMA_TIPO_11));
	comboConjuncion->Append(_T(IDS_S_NORMA_TIPO_12));
	comboConjuncion->Append(_T(IDS_S_NORMA_TIPO_6));
	comboConjuncion->Append(_T("----------"));
	comboConjuncion->Append(_T(IDS_T_NORMA_TIPO_1));
	comboConjuncion->Append(_T(IDS_T_NORMA_TIPO_0));
	comboConjuncion->Append(_T(IDS_T_NORMA_TIPO_2));
	comboConjuncion->Append(_T(IDS_T_NORMA_TIPO_3));
	comboConjuncion->Append(_T(IDS_T_NORMA_TIPO_4));
	comboConjuncion->Append(_T(IDS_T_NORMA_TIPO_5));
//	comboConjuncion->Append(_T(IDS_T_NORMA_TIPO_6));
	comboConjuncion->Append(_T(IDS_T_NORMA_TIPO_7));
	comboConjuncion->Append(_T(IDS_T_NORMA_TIPO_8));
	comboConjuncion->Append(_T(IDS_T_NORMA_TIPO_9));
}

void DialogoMotor::seleccionarCombos()
{
	int tipo,sel;

	tipo=Motor->implicacion()->identificador();
	switch(tipo)
	{
		case 0 : sel = 1; break;
		case 1 : sel = 0; break;
		case 2 : sel = 2; break;
		case 3 : sel = 3; break;
		case 4 : sel = 4; break;
		case 5 : sel = 5; break;
		case 6 : sel = 6; break;
		case 7 : sel = 7; break;
		case 8 : sel = 8; break;
	}
	comboImplicacion->SetSelection(sel);

	tipo=Motor->composicion()->identificador();
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
	comboComposicion->SetSelection(sel);

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

void DialogoMotor::OnComposicion(wxCommandEvent& event)
{
	nuevaComposicion();
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
		case 0:imp=new ImplicacionMinimo();
				break;
		case 1:imp=new ImplicacionProducto();
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

void DialogoMotor::nuevaComposicion()
{
	int caso;
	caso=comboComposicion->GetSelection();
	Norma* nor=nuevaTNorma(caso);
	if(nor)
	{
		Motor->composicion(nor);
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
	if(caso==4){return;}
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
	float par;
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
}

Norma* DialogoMotor::nuevaTNorma(int caso)
{
	Norma *nor=NULL;
	float par;
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

void DialogoMotor::getParametro(float *par,float minimo,float maximo)
{
	double tmp=(double)(*par);
	wxTextValidator Validator(wxFILTER_NUMERIC);
	wxString msg,val;
	val << *par;
	msg << _T("Ingrese el parámetro de la familia, entre ") << minimo << _T(" y ") << maximo;
	wxTextEntryDialog dlg(this,msg,_T("Parámetro de la familia de norma"),val);
	if(dlg.ShowModal()==wxID_OK)
	{
	  dlg.GetValue().ToDouble(&tmp);
	  *par=(float)tmp;
	}
	if(*par < minimo){*par=minimo;}
	if(*par > maximo){*par=maximo;}
	msg = "";
	msg << _T("El parámetro aplicado será ") << *par;
	wxMessageBox(msg,_T("Información"));
}

bool DialogoMotor::verificar()
{
	bool flag=true;
	float a,b;
	a=Motor->implicacion()->defecto();
	b=Concreto->conjuncion()->ToSNorm();
	if(a!=b)
	{
		flag=false;
		wxString str1,str2;
		if(a==0.0)
		{
			str1 = _T("La Implicación seleccionada requiere una Conjunción del tipo 'Unión'. La que usted ha seleccionado es del tipo 'Intersección'");
			str2 = _T(IDS_DIALOG_OPCION_IMPLICA2);
		}else
		{
			str1 = _T("La Implicación seleccionada requiere una Conjunción del tipo 'Intersección'. La que usted ha seleccionado es del tipo 'Unión'");
			str2 = _T(IDS_DIALOG_OPCION_IMPLICA4);
		}
		str1 << _T("\n¿Desea mantener esa elección?");
		if(wxMessageDialog(this, str1, str2, wxYES_NO|wxNO_DEFAULT).ShowModal() == wxID_YES)
		{
			flag=true;
		}
	}
	return flag;
}

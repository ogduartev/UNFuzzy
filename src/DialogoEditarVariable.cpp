#include "DialogoEditarVariable.h"

BEGIN_EVENT_TABLE(DialogoEditarVariable, wxDialog)
    EVT_CLOSE(DialogoEditarVariable::OnClose)
    EVT_BUTTON(wxID_OK   , DialogoEditarVariable::OnOK)
END_EVENT_TABLE()

DialogoEditarVariable::DialogoEditarVariable(Variable *var,wxWindow* parent)
:wxDialog(parent,wxID_ANY,wxString(_("Variable design")))
{
	Var=var;

  wxFlexGridSizer*  sizerTotal;
  wxFlexGridSizer*  sizerControles;
  wxFlexGridSizer*  sizerOKCancel;

  sizerTotal       = new wxFlexGridSizer(1,4,0);
  sizerControles   = new wxFlexGridSizer(2,4,0);
  sizerOKCancel    = new wxFlexGridSizer(2,1,0);

  staticNombre     = new wxStaticText(this,wxID_ANY, _("Variable name"));
  staticMinimo     = new wxStaticText(this,wxID_ANY, _("Minimum value"));
  staticMaximo     = new wxStaticText(this,wxID_ANY, _("Maximum value"));
  staticIntervalos = new wxStaticText(this,wxID_ANY, _("Number of evaluation intervals"));
  textNombre       = new wxTextCtrl(this,DLG_EDITVAR_NOMBRE    ,"",wxDefaultPosition,wxSize(150,20));
  textMinimo       = new wxTextCtrl(this,DLG_EDITVAR_MINIMO    ,"",wxDefaultPosition,wxSize(100,20));
  textMaximo       = new wxTextCtrl(this,DLG_EDITVAR_MAXIMO    ,"",wxDefaultPosition,wxSize(100,20));
  spinIntervalos   = new wxSpinCtrl(this,DLG_EDITVAR_INTERVALOS,"",wxDefaultPosition,wxSize(100,20),0x4000|wxALIGN_RIGHT,5,200,30);
  buttonOK         = new wxButton(this,wxID_OK,_("OK"));
  buttonCancel     = new wxButton(this,wxID_CANCEL,_("Cancel"));

	sizerControles->Add(staticNombre    , 1, wxALIGN_RIGHT|wxALL, 5);
	sizerControles->Add(textNombre      , 1, wxALIGN_LEFT|wxALL, 5);
	sizerControles->Add(staticMinimo    , 1, wxALIGN_RIGHT|wxALL, 5);
	sizerControles->Add(textMinimo      , 1, wxALIGN_LEFT|wxALL, 5);
	sizerControles->Add(staticMaximo    , 1, wxALIGN_RIGHT|wxALL, 5);
	sizerControles->Add(textMaximo      , 1, wxALIGN_LEFT|wxALL, 5);
	sizerControles->Add(staticIntervalos, 1, wxALIGN_RIGHT|wxALL, 5);
	sizerControles->Add(spinIntervalos  , 1, wxALIGN_LEFT|wxALL, 5);

	sizerOKCancel->Add(buttonOK, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerOKCancel->Add(buttonCancel, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

	sizerTotal->Add(sizerControles, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerTotal->Add(sizerOKCancel, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

  this->SetSizer(sizerTotal);
  this->Layout();
  sizerTotal->Fit(this);

  llenarDatos();
}

DialogoEditarVariable::~DialogoEditarVariable()
{
	//dtor
}

void DialogoEditarVariable::OnClose(wxCloseEvent&   event)
{
}

void DialogoEditarVariable::OnOK(wxCommandEvent&   event)
{
	nombre=textNombre->GetValue();
	wxString str;
	str=textMinimo->GetValue();
	min_=atof(str.c_str());
	str=textMaximo->GetValue();
	max_=atof(str.c_str());
	if(min_ >= max_)
	{
	  min_=Var->rangoMinimo();
	  max_=Var->rangoMaximo();
	}
	intervalos=spinIntervalos->GetValue();
	EndModal(wxID_OK);
}

void DialogoEditarVariable::llenarDatos()
{
	textNombre->SetValue(Var->nombreVariable());
	wxString str="";
	str << Var->rangoMinimo();
	textMinimo->SetValue(str);
	str="";
	str << Var->rangoMaximo();
	textMaximo->SetValue(str);
	spinIntervalos->SetValue(Var->numeroIntervalos());
}

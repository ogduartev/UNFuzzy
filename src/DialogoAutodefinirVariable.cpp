#include "DialogoAutodefinirVariable.h"

BEGIN_EVENT_TABLE(DialogoAutodefinirVariable, wxDialog)
    EVT_CLOSE(DialogoAutodefinirVariable::OnClose)
    EVT_BUTTON(wxID_OK   , DialogoAutodefinirVariable::OnOK)
END_EVENT_TABLE()

DialogoAutodefinirVariable::DialogoAutodefinirVariable(Variable *var,wxWindow* parent)
:wxDialog(parent,wxID_ANY,wxString(_T("Definición rápida de la variable")))
{
	Var=var;

  wxFlexGridSizer*  sizerTotal;
  wxFlexGridSizer*  sizerControles;
  wxFlexGridSizer*  sizerOKCancel;

  sizerTotal       = new wxFlexGridSizer(1,4,0);
  sizerControles   = new wxFlexGridSizer(2,1,0);
  sizerOKCancel    = new wxFlexGridSizer(2,1,0);

 	wxArrayString formas;
	formas.Add(_("Conjuntos rectos"));
	formas.Add(_("Conjuntos curvos"));

  staticNumero     = new wxStaticText(this,wxID_ANY, _T("Número de conjuntos"));
  spinNumero       = new wxSpinCtrl(this,DLG_AUTOVAR_NUMERO,_(""),wxDefaultPosition,wxSize(100,20),0x4000|wxALIGN_RIGHT,1,15,3);
  radioForma       = new wxRadioBox(this,DLG_AUTOVAR_FORMA,_("Forma de los conjuntos"),wxDefaultPosition,wxDefaultSize,formas);
  buttonOK         = new wxButton(this,wxID_OK,_("OK"));
  buttonCancel     = new wxButton(this,wxID_CANCEL,_("Cancelar"));

	sizerControles->Add(staticNumero, 1, wxALIGN_RIGHT|wxALL, 5);
	sizerControles->Add(spinNumero  , 1, wxALIGN_LEFT|wxALL, 5);

	sizerOKCancel->Add(buttonOK, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerOKCancel->Add(buttonCancel, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

	sizerTotal->Add(radioForma    , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerTotal->Add(sizerControles, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerTotal->Add(sizerOKCancel , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

  this->SetSizer(sizerTotal);
  this->Layout();
  sizerTotal->Fit(this);
}

DialogoAutodefinirVariable::~DialogoAutodefinirVariable()
{
	//dtor
}

void DialogoAutodefinirVariable::OnClose(wxCloseEvent&   event)
{
}

void DialogoAutodefinirVariable::OnOK(wxCommandEvent&   event)
{
	int sel=radioForma->GetSelection();
	if(sel==0)
	{
		flagRectos=true;
	}else
	{
		flagRectos=false;
	}
	numConjuntos=spinNumero->GetValue();
	EndModal(wxID_OK);
}

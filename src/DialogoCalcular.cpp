#include "DialogoCalcular.h"

BEGIN_EVENT_TABLE(DialogoCalcular, wxDialog)
    EVT_CLOSE(DialogoCalcular::OnClose)
    EVT_BUTTON(DLG_CALCULAR_CALCULAR      , DialogoCalcular::OnCalcular)
    EVT_BUTTON(wxID_OK   , DialogoCalcular::OnOK)
END_EVENT_TABLE()

DialogoCalcular::DialogoCalcular(SistemaLogicaDifusa *sld, wxWindow *parent)
:wxDialog(parent,wxID_ANY,wxString(_("Calculate")))
{
	SLD=sld;
	int numEntradas=SLD->numeroEntradas();
	int numSalidas=SLD->numeroSalidas();

  wxFlexGridSizer* sizerTotal;
  wxFlexGridSizer* sizerControles;
  wxFlexGridSizer* sizerEntradas;
  wxFlexGridSizer* sizerSalidas;
  wxFlexGridSizer* sizerOKCancel;

  sizerTotal      = new wxFlexGridSizer(1,2,0);
  sizerControles  = new wxFlexGridSizer(3,1,0);
	sizerEntradas   = new wxFlexGridSizer(2,numEntradas,0);
	sizerSalidas    = new wxFlexGridSizer(1,numSalidas,0);
  sizerOKCancel    = new wxFlexGridSizer(2,1,0);

	buttonCalcular = new wxButton(this, DLG_CALCULAR_CALCULAR      , _("=>")      , wxDefaultPosition, wxSize(35,35), 0);
  buttonOK         = new wxButton(this,wxID_OK,_("OK"));
  buttonCancel     = new wxButton(this,wxID_CANCEL,_("Cancel"));

	float entra[numEntradas];
	float sale[numEntradas];
	for(int i=0;i<numEntradas;i++)
	{
	  wxStaticText *st=new wxStaticText(this,wxID_ANY,SLD->nombreVariableEntrada(i));
	  NombresEntradas.Add(st);
	  sizerEntradas->Add(st, 0, wxALL, 0);
	  wxTextCtrl *ct=new wxTextCtrl(this,wxID_ANY);
	  ValoresEntradas.Add(ct);
	  wxString str;
	  str << SLD->variableEntrada(i)->difusorEntrada()->centro();
	  entra[i]=SLD->variableEntrada(i)->difusorEntrada()->centro();
	  ct->SetValue(str);
	  sizerEntradas->Add(ct, 0, wxALL, 0);
	}

	SLD->calcular(entra,sale);
	for(int i=0;i<numSalidas;i++)
	{
		wxString str=SLD->nombreVariableSalida(i);
		str << ": ";// << sale[i];
	  wxStaticText *st=new wxStaticText(this,wxID_ANY,str,wxDefaultPosition,wxSize(150,25));
	  NombresSalidas.Add(st);
	  sizerSalidas->Add(st, 0, wxALL, 0);
	}

	sizerOKCancel->Add(buttonOK, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerOKCancel->Add(buttonCancel, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

  sizerControles->Add(sizerEntradas      , 1, wxALIGN_CENTRE_HORIZONTAL|wxALIGN_CENTRE_VERTICAL|wxALL, 5);
  sizerControles->Add(buttonCalcular     , 1, wxALIGN_CENTRE_HORIZONTAL|wxALIGN_CENTRE_VERTICAL|wxALL, 20);
  sizerControles->Add(sizerSalidas       , 1, wxALIGN_CENTRE_HORIZONTAL|wxALIGN_CENTRE_VERTICAL|wxALL, 5);

  sizerTotal->Add(sizerControles    , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
  sizerTotal->Add(sizerOKCancel     , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

  this->SetSizer(sizerTotal);
  this->Layout();
  sizerTotal->Fit(this);
}

DialogoCalcular::~DialogoCalcular()
{
	SLD=NULL;
}

void DialogoCalcular::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void DialogoCalcular::OnOK(wxCommandEvent&   event)
{
	EndModal(wxID_OK);
}

void DialogoCalcular::OnCalcular(wxCommandEvent&   event)
{
	int numEntradas=ValoresEntradas.GetItemsInContainer();
	int numSalidas=NombresSalidas.GetItemsInContainer();
	float entra[numEntradas];
	float sale[numEntradas];
	for(int i=0;i<numEntradas;i++)
	{
	  wxString str;
	  str=ValoresEntradas.dato(i)->GetValue();
	  entra[i]=atof(str.c_str());
	}
	SLD->calcular(entra,sale);
	for(int i=0;i<numEntradas;i++)
	{
	  wxString str;
	  str << SLD->variableEntrada(i)->difusorEntrada()->centro();
	  ValoresEntradas.dato(i)->SetValue(str);
	}
	for(int i=0;i<numSalidas;i++)
	{
		wxString str=SLD->nombreVariableSalida(i);
		str << ": " << sale[i];
		NombresSalidas.dato(i)->SetLabel(str);
	}
}

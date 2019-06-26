#include "DialogoCalculo.h"

BEGIN_EVENT_TABLE(DialogoCalculo, wxDialog)
    EVT_CLOSE(DialogoCalculo::OnClose)
    EVT_BUTTON(DLG_CALCULO_CALCULAR      , DialogoCalculo::OnCalcular)
    EVT_BUTTON(wxID_OK   , DialogoCalculo::OnOK)
END_EVENT_TABLE()

DialogoCalculo::DialogoCalculo(wxWindow* parent)
:wxDialog::wxDialog(parent,wxID_ANY,wxString(_("Individual calculus")))
{
}

void DialogoCalculo::iniciar()
{
  wxFlexGridSizer* sizerTotal;
  wxFlexGridSizer* sizerControles;
  wxFlexGridSizer* sizerEntradas;
  wxFlexGridSizer* sizerSalidas;
  wxFlexGridSizer* sizerOKCancel;

  sizerTotal      = new wxFlexGridSizer(1,2,0);
  sizerControles  = new wxFlexGridSizer(3,1,0);
	sizerEntradas   = new wxFlexGridSizer(2,numeroEntradas(),0);
	sizerSalidas    = new wxFlexGridSizer(1,numeroSalidas(),0);
  sizerOKCancel    = new wxFlexGridSizer(2,1,0);

	for(int i=0;i<numeroEntradas();i++)
	{
	  wxStaticText *st=new wxStaticText(this,wxID_ANY,nombreEntrada(i));
	  sizerEntradas->Add(st, 0, wxALL, 0);

	  double minX=rangoMinimoEntrada(i);
	  double maxX=rangoMaximoEntrada(i);
	  double dx=(maxX-minX)/100;

	  wxSpinCtrlDouble *ct=new wxSpinCtrlDouble(this, wxID_ANY, "",wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, minX, maxX, 0, dx);
		Bind(wxEVT_SPINCTRLDOUBLE, &DialogoCalculo::OnCalcular, this, wxID_ANY);
	  ValoresEntradas.Add(ct);
	  sizerEntradas->Add(ct, 0, wxALL, 0);
	}
	for(int i=0;i<numeroSalidas();i++)
	{
		wxString str=nombreSalida(i);
		str << ":          ";// << sale[i];
	  wxStaticText *st=new wxStaticText(this,wxID_ANY,str,wxDefaultPosition,wxSize(150,25));
	  NombresSalidas.Add(st);
	  sizerSalidas->Add(st, 0, wxALL, 0);
	}

	buttonCalcular   = new wxButton(this, DLG_CALCULO_CALCULAR      , _("=>")      , wxDefaultPosition, wxSize(35,35), 0);
  buttonOK         = new wxButton(this,wxID_OK,_("OK"));
  buttonCancel     = new wxButton(this,wxID_CANCEL,_("Cancel"));

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

DialogoCalculo::~DialogoCalculo()
{
	//dtor
}

void DialogoCalculo::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void DialogoCalculo::OnOK(wxCommandEvent&   event)
{
	EndModal(wxID_OK);
}

void DialogoCalculo::OnCalcular(wxCommandEvent&   event)
{
	double entra[numeroEntradas()];
	double sale[numeroEntradas()];
	for(int i=0;i < numeroEntradas();i++)
	{
		entra[i]=ValoresEntradas.dato(i)->GetValue();
	}
	calcular(entra,sale);
	for(int i=0;i < numeroSalidas();i++)
	{
		wxString str=nombreSalida(i);
		str << _(" : ") << sale[i];
		NombresSalidas.dato(i)->SetLabel(str);
	}
}

#include "DialogoFuncion.h"

BEGIN_EVENT_TABLE(DialogoFuncion, wxDialog)
    EVT_PAINT(DialogoFuncion::OnPaint)
    EVT_CLOSE(DialogoFuncion::OnClose)
    EVT_BUTTON(wxID_OK , DialogoFuncion::OnOK)
    EVT_BUTTON(DLG_FUNCION_BTNPINTAR  , DialogoFuncion::pintar)
    EVT_BUTTON(DLG_FUNCION_BTNLIMPIAR , DialogoFuncion::limpiar)
    EVT_BUTTON(DLG_FUNCION_BTNCOLOR ,   DialogoFuncion::OnColor)
    EVT_CHOICE(DLG_FUNCION_CHOICEENTRA, DialogoFuncion::limpiar)
    EVT_CHOICE(DLG_FUNCION_CHOICESALE , DialogoFuncion::limpiar)
END_EVENT_TABLE()


DialogoFuncion::DialogoFuncion(wxWindow *parent)
:wxDialog(parent,wxID_ANY,wxString(_("Input-Output function")))
{
}

void DialogoFuncion::iniciar()
{
	colorData.SetChooseFull(true);
	colorData.SetColour(*wxBLUE);

  wxFlexGridSizer*  sizerTotal;
  wxFlexGridSizer*  sizerCentral;
  wxFlexGridSizer*  sizerControles;
  wxFlexGridSizer*  sizerChoices;
  wxFlexGridSizer*  sizerBotones;
  wxFlexGridSizer*  sizerValores;
  wxFlexGridSizer*  sizerOKCancel;

  sizerTotal       = new wxFlexGridSizer(1,4,0);
	sizerCentral     = new wxFlexGridSizer(2,2,0);
	sizerControles   = new wxFlexGridSizer(1,4,0);
	sizerChoices     = new wxFlexGridSizer(2,2,0);
	sizerBotones     = new wxFlexGridSizer(2,1,0);
	sizerValores     = new wxFlexGridSizer(2,10,0);
  sizerOKCancel    = new wxFlexGridSizer(2,1,0);

  canvasFuncion    = new wxSizerItem(600,400);

  wxArrayString strEntra,strSale;
  for(int i=0;i<numeroEntradas();i++)
	{
		strEntra.Add(nombreEntrada(i));
	}
  for(int i=0;i<numeroSalidas();i++)
	{
		strSale.Add(nombreSalida(i));
	}

	staticEntradas   = new wxStaticText(this,wxID_ANY,_("Horizontal axe"));
	staticSalidas    = new wxStaticText(this,wxID_ANY,_("Vertical axe"));
	choiceEntradas   = new wxChoice(this,DLG_FUNCION_CHOICEENTRA,wxDefaultPosition,wxDefaultSize,strEntra);
	choiceSalidas    = new wxChoice(this,DLG_FUNCION_CHOICESALE,wxDefaultPosition,wxDefaultSize,strSale);
	valoresEntradas  = new wxSpinCtrlDouble*[numeroEntradas()];
  for(int i=0;i<numeroEntradas();i++)
	{
		float mini,maxi,medi,incr;
		mini=rangoMinimoEntrada(i);
		maxi=rangoMaximoEntrada(i);
		medi=0.5*(mini+maxi);
		incr=0.01*(maxi-mini);
		valoresEntradas[i]=new wxSpinCtrlDouble(this,wxID_ANY,_("X"),wxDefaultPosition,wxDefaultSize, wxSP_ARROW_KEYS, mini,maxi,medi,incr);

		wxStaticText *stText;
		stText= new wxStaticText(this,wxID_ANY, nombreEntrada(i));
		sizerValores ->Add(stText             , 1, wxALIGN_RIGHT|wxALIGN_CENTRE_VERTICAL|wxALL, 3);
		sizerValores ->Add(valoresEntradas[i] , 1, wxALIGN_LEFT|wxALIGN_CENTRE_VERTICAL|wxALL, 3);
	}

  buttonPintar     = new wxButton(this,DLG_FUNCION_BTNPINTAR,_("Paint"));
  buttonLimpiar    = new wxButton(this,DLG_FUNCION_BTNLIMPIAR,_("Clean"));
  buttonColor      = new wxButton(this,DLG_FUNCION_BTNCOLOR  ,_("Color"));
  buttonOK         = new wxButton(this,wxID_OK,_("OK"));
  buttonCancel     = new wxButton(this,wxID_CANCEL,_("Cancel"));

  choiceEntradas->SetSelection(0);
  choiceSalidas->SetSelection(0);

  sizerBotones->Add(buttonPintar   , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
  sizerBotones->Add(buttonLimpiar  , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

  sizerChoices->Add(staticEntradas , 1, wxALIGN_RIGHT|wxALIGN_CENTRE_VERTICAL|wxALL, 5);
  sizerChoices->Add(choiceEntradas , 1, wxALIGN_LEFT|wxALIGN_CENTRE_VERTICAL|wxALL, 5);
  sizerChoices->Add(staticSalidas  , 1, wxALIGN_RIGHT|wxALIGN_CENTRE_VERTICAL|wxALL, 5);
  sizerChoices->Add(choiceSalidas  , 1, wxALIGN_LEFT|wxALIGN_CENTRE_VERTICAL|wxALL, 5);

  sizerControles->Add(sizerChoices   , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
  sizerControles->Add(sizerValores   , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
  sizerControles->Add(sizerBotones   , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
  sizerControles->Add(buttonColor    , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

  sizerCentral->Add(canvasFuncion);
  sizerCentral->Add(sizerControles , 1, wxALIGN_CENTRE_HORIZONTAL|wxALIGN_CENTRE_VERTICAL|wxALL, 5);

	sizerOKCancel->Add(buttonOK    , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerOKCancel->Add(buttonCancel, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

  sizerTotal->Add(sizerCentral          , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerTotal->Add(sizerOKCancel, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

	if(numeroEntradas()==1)
	{
		sizerValores->Show(false);
	}

  this->SetSizer(sizerTotal);
  this->Layout();
  sizerTotal->Fit(this);
}

DialogoFuncion::~DialogoFuncion()
{
}

void DialogoFuncion::OnClose       (wxCloseEvent&   event)
{
	EndModal(wxID_OK);
}

void DialogoFuncion::OnOK(wxCommandEvent&   event)
{
	EndModal(wxID_OK);
}

void DialogoFuncion::OnPaint       (wxPaintEvent& event)
{
	limpiar((wxCommandEvent&) event);
}

void DialogoFuncion::pintar(wxCommandEvent&   event)
{
	int numEntra=0;
	int numSale=0;
	numEntra = choiceEntradas->GetSelection();
	numSale  = choiceSalidas->GetSelection();
	pintarFuncion(false,true,numEntra,numSale);
}

void DialogoFuncion::limpiar (wxCommandEvent& event)
{
	int numEntra=0;
	int numSale=0;
	numEntra = choiceEntradas->GetSelection();
	numSale  = choiceSalidas->GetSelection();
	for(int i=0;i<numeroEntradas();i++)
	{
		if(i==numEntra)
		{
			valoresEntradas[i]->Show(false);
		}else
		{
			valoresEntradas[i]->Show(true);
		}
	}
	pintarFuncion(true,false,numEntra,numSale);
}

void DialogoFuncion::OnColor (wxCommandEvent& event)
{
	wxColourDialog dialog(this, &colorData);
	if (dialog.ShowModal() == wxID_OK)
	{
			colorData = dialog.GetColourData();
	}
}

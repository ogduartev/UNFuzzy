#include "DialogoPaso.h"

BEGIN_EVENT_TABLE(DialogoPaso, wxDialog)
    EVT_PAINT(DialogoPaso::OnPaint)
    EVT_CLOSE(DialogoPaso::OnClose)
    EVT_CHOICE(DLG_PASO_CHOICEENTRA         , DialogoPaso::OnCambioEntra)
    EVT_CHOICE(DLG_PASO_CHOICESALE          , DialogoPaso::OnCambioSale)
    EVT_GRID_LABEL_LEFT_CLICK( DialogoPaso::OnRegla)
END_EVENT_TABLE()

DialogoPaso::DialogoPaso(SistemaLogicaDifusa *sld, wxWindow *parent)
:wxDialog(parent,wxID_ANY,wxString(_("Step by step calculus")))
{
	SLD=sld;
	sale=new double[SLD->salidas->numeroVariables()];

  wxFlexGridSizer*  sizerTotal;
  wxFlexGridSizer*  sizerBloqueA;
  wxFlexGridSizer*  sizerBloqueB;
  wxFlexGridSizer*  sizerBloqueC;
  wxFlexGridSizer*  sizerControles;
  wxFlexGridSizer*  sizerChoices;
  wxFlexGridSizer*  sizerBotones;
  wxFlexGridSizer*  sizerValores;
  wxFlexGridSizer*  sizerOKCancel;

  sizerTotal       = new wxFlexGridSizer(1,4,0);
	sizerBloqueA     = new wxFlexGridSizer(4,1,0);
	sizerBloqueB     = new wxFlexGridSizer(4,1,0);
	sizerBloqueC     = new wxFlexGridSizer(4,1,0);
	sizerControles   = new wxFlexGridSizer(1,4,0);
	sizerChoices     = new wxFlexGridSizer(1,2,0);
	sizerValores     = new wxFlexGridSizer(2,10,0);
  sizerOKCancel    = new wxFlexGridSizer(3,1,0);

  canvasVarEntrada    = new wxSizerItem(400,160);
  canvasVarRegla      = new wxSizerItem(300,160);
  canvasVarSalida     = new wxSizerItem(300,160);

  wxArrayString strEntra,strSale;
  for(int i=0;i<SLD->entradas->numeroVariables();i++)
	{
		strEntra.Add(SLD->entradas->variable(i)->nombreVariable());
	}
  for(int i=0;i<SLD->salidas->numeroVariables();i++)
	{
		strSale.Add(SLD->salidas->variable(i)->nombreVariable());
	}
	int cols,rows;
	rows = 0;
	cols = SLD->motor->numeroEntradas() + SLD->motor->numeroSalidas();

	staticSalida     = new wxStaticText(this,wxID_ANY,_("                 "));
	choiceEntradas   = new wxChoice(this,DLG_PASO_CHOICEENTRA,wxDefaultPosition,wxDefaultSize,strEntra);
	choiceSalidas    = new wxChoice(this,DLG_PASO_CHOICESALE,wxDefaultPosition,wxDefaultSize,strSale);
	gridTabla = new wxGrid(this,DLG_PASO_TABLA, wxDefaultPosition, wxSize(600,200), wxFULL_REPAINT_ON_RESIZE);
	gridTabla->CreateGrid(rows,cols);
	valoresEntradas  = new wxSpinCtrlDouble*[SLD->entradas->numeroVariables()];
  for(int i=0;i<SLD->entradas->numeroVariables();i++)
	{
		double mini,maxi,medi,incr;
		mini=SLD->entradas->variable(i)->rangoMinimo();
		maxi=SLD->entradas->variable(i)->rangoMaximo();
		medi=0.5*(mini+maxi);
		incr=0.01*(maxi-mini);
		valoresEntradas[i]=new wxSpinCtrlDouble(this,DLG_PASO_SPINENTRA_BASE+i,_("X"),wxDefaultPosition,wxDefaultSize, wxSP_ARROW_KEYS, mini,maxi,medi,incr);
		Bind(wxEVT_SPINCTRLDOUBLE, &DialogoPaso::OnCambioSpinEntra, this, DLG_PASO_SPINENTRA_BASE+i);

		wxStaticText *stText;
		stText= new wxStaticText(this,wxID_ANY, SLD->entradas->variable(i)->nombreVariable());
		sizerValores ->Add(stText             , 0, wxALIGN_RIGHT|wxALIGN_CENTRE_VERTICAL|wxALL, 1);
		sizerValores ->Add(valoresEntradas[i] , 0, wxALIGN_LEFT|wxALIGN_CENTRE_VERTICAL|wxALL, 1);
	}

  buttonOK         = new wxButton(this,wxID_OK,_("OK"));
  buttonCancel     = new wxButton(this,wxID_CANCEL,_("Cancel"));

  choiceEntradas->SetSelection(0);
  choiceSalidas->SetSelection(0);

 	sizerChoices->Add(choiceEntradas      , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

	sizerBloqueA->Add(sizerValores      , 1, wxALIGN_CENTRE_HORIZONTAL| wxALIGN_CENTRE_VERTICAL|wxALL, 5);
	sizerBloqueA->Add(canvasVarEntrada);
	sizerBloqueA->Add(sizerChoices      , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

	sizerBloqueB->Add(gridTabla    , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

	sizerControles->Add(choiceSalidas    , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerControles->Add(staticSalida    , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

	sizerBloqueC->Add(canvasVarRegla);
	sizerBloqueC->Add(canvasVarSalida);
	sizerBloqueC->Add(sizerControles);

	sizerOKCancel->Add(buttonOK      , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerOKCancel->Add(buttonCancel  , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

  sizerTotal->Add(sizerBloqueA , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
  sizerTotal->Add(sizerBloqueB , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
  sizerTotal->Add(sizerBloqueC , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerTotal->Add(sizerOKCancel, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

  this->SetSizer(sizerTotal);
  this->Layout();
  sizerTotal->Fit(this);
  calcular();
  llenarTabla();
  llenarSalida();
}

DialogoPaso::~DialogoPaso()
{
	//dtor
}

void DialogoPaso::OnClose(wxCloseEvent &event)
{
	EndModal(wxID_OK);
}

void DialogoPaso::OnOK(wxCommandEvent&   event)
{
	EndModal(wxID_OK);
}

void DialogoPaso::OnPaint(wxPaintEvent& event)
{
	pintar();
}

void DialogoPaso::OnCambioEntra(wxCommandEvent&   event)
{
	pintarEntrada();
}

void DialogoPaso::OnCambioSale(wxCommandEvent&   event)
{
	pintarSalida();
	llenarSalida();
}

void DialogoPaso::OnCambioSpinEntra(wxSpinDoubleEvent&   event)
{
	calcular();
	pintarEntrada();
	pintarSalida();
}

void DialogoPaso::calcular()
{
	double entra[SLD->entradas->numeroVariables()];
	for(int i=0;i<SLD->entradas->numeroVariables();i++)
	{
		entra[i]=valoresEntradas[i]->GetValue();
	}
	SLD->calcular(entra,sale);

	wxArrayInt selectedRows=gridTabla->GetSelectedRows();
	int selectedRow=-1;
	if(selectedRows.Count()>0)
	{
		selectedRow=reglasActivas[selectedRows[0]];
	}

	llenarTabla();
	llenarSalida();

	int r=reglasActivas.Index(selectedRow);
	if(r!=wxNOT_FOUND)
	{
		gridTabla->SelectRow(r);
		pintarRegla(r);
	}
}

void DialogoPaso::pintar()
{
	pintarEntrada();
	pintarRegla();
	pintarSalida();
}

void DialogoPaso::pintarEntrada()
{
	int numEntrada=choiceEntradas->GetSelection();

	Variable* var=SLD->entradas->variable(numEntrada);
	wxClientDC dc(this);
	wxRect canvas=canvasVarEntrada->GetRect();

	Graficador Grafica(&dc,canvas);
	Grafica.pintarVariable(var,0,false);
	Grafica.pintarDifusor(var,false);
	Grafica.pintarTitle(var->nombreVariable());
}

void DialogoPaso::pintarRegla(int reglaInd)
{
	int numSalida =choiceSalidas->GetSelection();

	Variable* var=SLD->salidas->variable(numSalida);
	wxClientDC dc(this);
	wxRect canvas=canvasVarRegla->GetRect();

	double mnx, mxx, mny, mxy;
	mnx=SLD->salidas->variable(numSalida)->rangoMinimo();
	mxx=SLD->salidas->variable(numSalida)->rangoMaximo();
	mny=0.0;
	mxy=1.0;

	Graficador Grafica(&dc,canvas);
	Grafica.pintarMarco();
	Grafica.pintarEjes();
	Grafica.pintarTicks(mnx,mxx,mny,mxy);

	int regla;
	if(reglaInd>=0)
	{
		gridTabla->ClearSelection();
		gridTabla->SelectRow(reglaInd);
		regla=reglasActivas[reglaInd];
		Grafica.pintarComposicion(SLD,numSalida,regla);
	}
}

void DialogoPaso::pintarSalida()
{
	int numSalida =choiceSalidas->GetSelection();

	Variable* var=SLD->salidas->variable(numSalida);
	wxClientDC dc(this);
	wxRect canvas=canvasVarSalida->GetRect();

	double mnx, mxx, mny, mxy;
	mnx=SLD->salidas->variable(numSalida)->rangoMinimo();
	mxx=SLD->salidas->variable(numSalida)->rangoMaximo();
	mny=0.0;
	mxy=1.0;

	Graficador Grafica(&dc,canvas);
	Grafica.pintarMarco();
	Grafica.pintarEjes();
	Grafica.pintarTicks(mnx,mxx,mny,mxy);
	Grafica.pintarConjuncion(SLD,numSalida,sale[numSalida]);
}

void DialogoPaso::llenarTabla()
{
	wxString celda="";
	int offsetX=SLD->motor->entradas()->numeroVariables();

	for(int e=0;e<SLD->motor->numeroEntradas();e++)
	{
		celda ="";
		celda << SLD->motor->entradas()->variable(e)->nombreVariable();
		gridTabla->SetColLabelValue(e,celda);
	}
	for(int s=0;s<SLD->motor->numeroSalidas();s++)
	{
		celda ="";
		celda << SLD->motor->salidas()->variable(s)->nombreVariable();
		gridTabla->SetColLabelValue(offsetX+s,celda);
	}

	////////limpiar Tabla
	while(gridTabla->GetNumberRows()>0)
	{
		gridTabla->DeleteRows(0);
	}
	reglasActivas.Clear();
	/////////

	for(int i=0;i<SLD->motor->numeroReglas();i++)
	{
		if(SLD->motor->activarRegla(i))
		{
			reglasActivas.Add(i);
			gridTabla->AppendRows();
			int regla=gridTabla->GetNumberRows()-1;
			celda ="";
			celda << _("Rule ") << (i+1);

			gridTabla->SetRowLabelValue(regla,celda);
			for(int e=0;e<SLD->motor->numeroEntradas();e++)
			{
				celda ="";
				celda << SLD->motor->conjuntoEntrada(i,e)->nombre();

				if(SLD->motor->modificador(i,e)!=1.0)
				{
					celda << _("(") << SLD->motor->modificador(i,e) << _(")");
				}

				gridTabla->SetCellValue(regla,e,celda);
				gridTabla->SetCellBackgroundColour(regla,e,wxColour(0xFF,0xF6,0xBA));
			}
			for(int s=0;s<SLD->motor->numeroSalidas();s++)
			{
				celda ="";
				celda << SLD->motor->conjuntoSalida(i,s)->nombre();
				gridTabla->SetCellValue(regla,offsetX+s,celda);
				gridTabla->SetCellBackgroundColour(regla,offsetX+s,wxColour(0xDC,0xEF,0xF7));
			}
		}
	}
}

void DialogoPaso::llenarSalida()
{
	int numSalida =choiceSalidas->GetSelection();
	wxString str="";
	str << sale[numSalida];
	staticSalida->SetLabel(str);
}

void DialogoPaso::OnRegla(wxGridEvent& event)
{
	int row=event.GetRow();
	if(row>=0)
	{
		pintarRegla(row);
	}
}

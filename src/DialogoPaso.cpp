#include "DialogoPaso.h"

BEGIN_EVENT_TABLE(DialogoPaso, wxDialog)
    EVT_PAINT(DialogoPaso::OnPaint)
    EVT_CLOSE(DialogoPaso::OnClose)
    EVT_BUTTON(wxID_OK                      , DialogoPaso::OnOK)
    EVT_BUTTON(DLG_PASO_BTNCALCULAR         , DialogoPaso::OnCalcular)
    EVT_GRID_LABEL_LEFT_CLICK( DialogoPaso::OnRegla)
END_EVENT_TABLE()

DialogoPaso::DialogoPaso(SistemaLogicaDifusa *sld, wxWindow *parent)
:wxDialog(parent,wxID_ANY,wxString(_T("Cálculo paso a paso")))
{
	SLD=sld;
	sale=new float[SLD->salidas->numeroVariables()];

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
	sizerChoices     = new wxFlexGridSizer(2,2,0);
//	sizerBotones     = new wxFlexGridSizer(2,1,0);
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

//	staticEntradas   = new wxStaticText(this,wxID_ANY,_T("Entradas"));
	staticSalida     = new wxStaticText(this,wxID_ANY,_T("                 "));
	choiceEntradas   = new wxChoice(this,DLG_PASO_CHOICEENTRA,wxDefaultPosition,wxDefaultSize,strEntra);
	choiceSalidas    = new wxChoice(this,DLG_PASO_CHOICESALE,wxDefaultPosition,wxDefaultSize,strSale);
	gridTabla = new wxGrid(this,DLG_PASO_TABLA, wxDefaultPosition, wxSize(600,200), wxFULL_REPAINT_ON_RESIZE);
	gridTabla->CreateGrid(rows,cols);
	valoresEntradas  = new wxSpinCtrlDouble*[SLD->entradas->numeroVariables()];
  for(int i=0;i<SLD->entradas->numeroVariables();i++)
	{
		float mini,maxi,medi,incr;
		mini=SLD->entradas->variable(i)->rangoMinimo();
		maxi=SLD->entradas->variable(i)->rangoMaximo();
		medi=0.5*(mini+maxi);
		incr=0.01*(maxi-mini);
		valoresEntradas[i]=new wxSpinCtrlDouble(this,wxID_ANY,_T("X"),wxDefaultPosition,wxDefaultSize, wxSP_ARROW_KEYS, mini,maxi,medi,incr);

		wxStaticText *stText;
		stText= new wxStaticText(this,wxID_ANY, SLD->entradas->variable(i)->nombreVariable());
		sizerValores ->Add(stText             , 1, wxALIGN_RIGHT|wxALIGN_CENTRE_VERTICAL|wxALL, 3);
		sizerValores ->Add(valoresEntradas[i] , 1, wxALIGN_LEFT|wxALIGN_CENTRE_VERTICAL|wxALL, 3);
	}

  buttonCalcular         = new wxButton(this,DLG_PASO_BTNCALCULAR,_("Calcular"));
  buttonOK         = new wxButton(this,wxID_OK,_("OK"));
  buttonCancel     = new wxButton(this,wxID_CANCEL,_("Cancelar"));

  choiceEntradas->SetSelection(0);
  choiceSalidas->SetSelection(0);

	sizerBloqueA->Add(sizerValores     , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerBloqueA->Add(choiceEntradas      , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerBloqueA->Add(canvasVarEntrada);

	sizerBloqueB->Add(gridTabla    , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

	sizerControles->Add(choiceSalidas    , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerControles->Add(staticSalida    , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

	sizerBloqueC->Add(canvasVarRegla);
	sizerBloqueC->Add(canvasVarSalida);
	sizerBloqueC->Add(sizerControles);

	sizerOKCancel->Add(buttonCalcular, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
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

void DialogoPaso::OnCalcular(wxCommandEvent&   event)
{
	calcular();
	pintar();
}

void DialogoPaso::calcular()
{
	float entra[SLD->entradas->numeroVariables()];
	for(int i=0;i<SLD->entradas->numeroVariables();i++)
	{
		entra[i]=valoresEntradas[i]->GetValue();
	}
	SLD->calcular(entra,sale);
	llenarTabla();
	llenarSalida();
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
	wxPaintDC dc(this);
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
	wxPaintDC dc(this);
	wxRect canvas=canvasVarRegla->GetRect();

	float mnx, mxx, mny, mxy;
	mnx=SLD->salidas->variable(numSalida)->rangoMinimo();
	mxx=SLD->salidas->variable(numSalida)->rangoMaximo();
	mny=0.0;
	mxy=1.0;

	Graficador Grafica(&dc,canvas);
	Grafica.pintarMarco();
	Grafica.pintarEjes();
	Grafica.pintarTicks(mnx,mxx,mny,mxy);

	int regla;
	if(reglaInd<0){reglaInd=0;}
	gridTabla->ClearSelection();
	gridTabla->SelectRow(reglaInd);
  regla=reglasActivas[reglaInd];
	Grafica.pintarComposicion(SLD,numSalida,regla);
}

void DialogoPaso::pintarSalida()
{
	int numSalida =choiceSalidas->GetSelection();

	Variable* var=SLD->salidas->variable(numSalida);
	wxPaintDC dc(this);
	wxRect canvas=canvasVarSalida->GetRect();

	float mnx, mxx, mny, mxy;
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
			celda << _T("Regla ") << (i+1);

			gridTabla->SetRowLabelValue(regla,celda);
			for(int e=0;e<SLD->motor->numeroEntradas();e++)
			{
				celda ="";
				celda << SLD->motor->conjuntoEntrada(i,e)->nombre();

				if(SLD->motor->modificador(i,e)!=1.0)
				{
					celda << _T("(") << SLD->motor->modificador(i,e) << _T(")");
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

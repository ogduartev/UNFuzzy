#include "DialogoEntrenamiento.h"

BEGIN_EVENT_TABLE(DialogoEntrenamiento, wxDialog)
    EVT_CLOSE(DialogoEntrenamiento::OnClose)
    EVT_BUTTON(wxID_OK   , DialogoEntrenamiento::OnOK)
    EVT_BUTTON(DLG_ENTRENA_INSERTAR   , DialogoEntrenamiento::OnInsertar)
    EVT_BUTTON(DLG_ENTRENA_ELIMINAR   , DialogoEntrenamiento::OnEliminar)
    EVT_BUTTON(DLG_ENTRENA_CARGAR     , DialogoEntrenamiento::OnCargar)
    EVT_BUTTON(DLG_ENTRENA_ENTRENAR   , DialogoEntrenamiento::OnEntrenar)
END_EVENT_TABLE()

DialogoEntrenamiento::DialogoEntrenamiento(SistemaLogicaDifusa *SLD, wxWindow *parent)
:wxDialog(parent,wxID_ANY,wxString(wxT("Entrenamiento del sistema")))
{
	Motor = SLD->motor;

  wxFlexGridSizer* sizerTotal;
  wxFlexGridSizer* sizerControles;
  wxFlexGridSizer* sizerBotones;
  wxFlexGridSizer* sizerOKCancel;

  sizerTotal       = new wxFlexGridSizer(1,2,0);
  sizerControles   = new wxFlexGridSizer(2,4,0);
  sizerBotones     = new wxFlexGridSizer(1,8,0);
  sizerOKCancel    = new wxFlexGridSizer(2,1,0);

	int cols,rows;
	rows = 0;
	cols = Motor->numeroEntradas() + Motor->numeroSalidas();

	gridTabla = new wxGrid(this,DLG_ENTRENA_TABLA, wxDefaultPosition, wxSize(600,400), wxFULL_REPAINT_ON_RESIZE);
	gridTabla->CreateGrid(rows,cols);


	wxArrayString algoritmos;
	algoritmos.Add(_T("Universos fijos"));
	algoritmos.Add(_T("Universos variables"));

  buttonInsertar   = new wxButton(this,DLG_ENTRENA_INSERTAR    ,_T("Insertar Patrón"));
  buttonEliminar   = new wxButton(this,DLG_ENTRENA_ELIMINAR    ,_T("Eliminar Patrón"));
  buttonCargar     = new wxButton(this,DLG_ENTRENA_CARGAR      ,_T("Cargar Patrones"));
  buttonEntrenar   = new wxButton(this,DLG_ENTRENA_ENTRENAR    ,_T("Entrenar"));
  checkLimpiar     = new wxCheckBox(this,DLG_ENTRENA_CHECKLIMPIAR, _T("Limpiar el sistema"));
  staticAlgoritmo  = new wxStaticBox(this,wxID_ANY, _T("Algoritmo de entrenamiento"));
  choiceAlgoritmo  = new wxChoice(this,DLG_ENTRENA_CHOICEALGORITMO,wxDefaultPosition,wxDefaultSize,algoritmos);

  buttonOK         = new wxButton(this,wxID_OK,_("OK"));
  buttonCancel     = new wxButton(this,wxID_CANCEL,_("Cancelar"));

	llenarTabla();
  choiceAlgoritmo->SetSelection(0);

	sizerBotones->Add(buttonInsertar   , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerBotones->Add(buttonEliminar   , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerBotones->Add(buttonCargar     , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerBotones->Add(checkLimpiar     , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerBotones->Add(staticAlgoritmo  , 1, wxALIGN_CENTRE_HORIZONTAL|wxTOP, 5);
	sizerBotones->Add(choiceAlgoritmo  , 1, wxALIGN_CENTRE_HORIZONTAL|wxBOTTOM, 5);
	sizerBotones->Add(buttonEntrenar   , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

	sizerControles->Add(gridTabla, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerControles->Add(sizerBotones, 1, wxALIGN_CENTRE_HORIZONTAL|wxALIGN_CENTRE_VERTICAL|wxALL, 5);

	sizerOKCancel->Add(buttonOK, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerOKCancel->Add(buttonCancel, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

  sizerTotal->Add(sizerControles   , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
  sizerTotal->Add(sizerOKCancel    , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

  this->SetSizer(sizerTotal);
  this->Layout();
  sizerTotal->Fit(this);
}

DialogoEntrenamiento::~DialogoEntrenamiento()
{
	//dtor
}

void DialogoEntrenamiento::OnClose       (wxCloseEvent&   event)
{
	EndModal(wxID_OK);
}

void DialogoEntrenamiento::OnOK          (wxCommandEvent&   event)
{
	EndModal(wxID_OK);
}

void DialogoEntrenamiento::llenarTabla()
{
	wxString celda="";
	int offsetX=Motor->entradas()->numeroVariables();

	for(int e=0;e<Motor->numeroEntradas();e++)
	{
		celda ="";
		celda << Motor->entradas()->variable(e)->nombreVariable();
		gridTabla->SetColLabelValue(e,celda);
	}
	for(int s=0;s<Motor->numeroSalidas();s++)
	{
		celda ="";
		celda << Motor->salidas()->variable(s)->nombreVariable();
		gridTabla->SetColLabelValue(offsetX+s,celda);
	}

}

void DialogoEntrenamiento::OnInsertar    (wxCommandEvent&   event)
{
	wxString celda="";
	int offsetX=Motor->entradas()->numeroVariables();
	gridTabla->AppendRows();
	int patron=gridTabla->GetNumberRows()-1;

	for(int e=0;e<Motor->numeroEntradas();e++)
	{
		float minimo,maximo,valor;
		minimo=Motor->entradas()->variable(e)->rangoMinimo();
		maximo=Motor->entradas()->variable(e)->rangoMaximo();
		valor=0.5*(minimo+maximo);
		celda ="";
		celda << valor;
		gridTabla->SetCellValue(patron,e,celda);
		gridTabla->SetCellBackgroundColour(patron,e,wxColour(0xFF,0xF6,0xBA));
		wxGridCellEditor *cellEditor;
		cellEditor = new wxGridCellFloatEditor();
		gridTabla->SetCellEditor(patron,e,cellEditor);
		gridTabla->SetCellTextColour(patron,e,wxColour(0,0,255));
	}
	for(int s=0;s<Motor->numeroSalidas();s++)
	{
		float minimo,maximo,valor;
		minimo=Motor->salidas()->variable(s)->rangoMinimo();
		maximo=Motor->salidas()->variable(s)->rangoMaximo();
		valor=0.5*(minimo+maximo);
		celda ="";
		celda << valor;
		gridTabla->SetCellValue(patron,offsetX+s,celda);
		gridTabla->SetCellBackgroundColour(patron,offsetX+s,wxColour(0xDC,0xEF,0xF7));
		wxGridCellEditor *cellEditor;
		cellEditor = new wxGridCellFloatEditor();
		gridTabla->SetCellEditor(patron,offsetX+s,cellEditor);
		gridTabla->SetCellTextColour(patron,offsetX+s,wxColour(0,0,255));
	}
}

void DialogoEntrenamiento::OnEliminar    (wxCommandEvent&   event)
{
	wxArrayInt selection=gridTabla->GetSelectedRows();

	if(selection.GetCount()<1)
	{
		wxMessageBox(_T("Seleccione los patrones a eliminar"));
		return;
	}
	wxMessageDialog *dial;
	dial=new wxMessageDialog (this, _T("¿Desea eliminar los patrones?"), _T("Confirmación"), wxOK|wxCANCEL|wxCENTRE);
	if(dial->ShowModal() == wxID_OK)
	{
		for(int i=selection.GetCount()-1;i>-1;i--)
		{
			gridTabla->DeleteRows(selection[i]);
		}
		gridTabla->ClearSelection();
	}
	delete dial;
}

void DialogoEntrenamiento::verificarDatos()
{
	int numArreglos=0;
	float minimo,maximo,valor;
	double valorD;
	wxString celda="";
	int offsetX=Motor->entradas()->numeroVariables();
	gridTabla->ClearSelection();
	gridTabla->SetSelectionMode(wxGrid::wxGridSelectCells);
	for(int patron=0;patron<gridTabla->GetNumberRows();patron++)
	{
		for(int e=0;e<Motor->numeroEntradas();e++)
		{
			gridTabla->SetCellTextColour(patron,e,wxColour(0,0,255));
			minimo=Motor->entradas()->variable(e)->rangoMinimo();
			maximo=Motor->entradas()->variable(e)->rangoMaximo();
			gridTabla->GetCellValue(patron,e).ToDouble(&valorD);
			valor=(float)valorD;
			if(valor<minimo)
			{
				valor=minimo;
				celda = "";
				celda << valor;
				gridTabla->SetCellValue(patron,e,celda);
				gridTabla->SetCellTextColour(patron,e,wxColour(255,0,0));
				numArreglos++;
			}
			if(valor>maximo)
			{
				valor=maximo;
				celda = "";
				celda << valor;
				gridTabla->SetCellValue(patron,e,celda);
				gridTabla->SetCellTextColour(patron,e,wxColour(255,0,0));
				numArreglos++;
			}
		}
		for(int s=0;s<Motor->numeroSalidas();s++)
		{
			gridTabla->SetCellTextColour(patron,offsetX+s,wxColour(0,0,255));
			minimo=Motor->salidas()->variable(s)->rangoMinimo();
			maximo=Motor->salidas()->variable(s)->rangoMaximo();
			gridTabla->GetCellValue(patron,offsetX+s).ToDouble(&valorD);
			valor=(float)valorD;
			if(valor<minimo)
			{
				valor=minimo;
				celda = "";
				celda << valor;
				gridTabla->SetCellValue(patron,offsetX+s,celda);
				gridTabla->SetCellTextColour(patron,offsetX+s,wxColour(255,0,0));
				numArreglos++;
			}
			if(valor>maximo)
			{
				valor=maximo;
				celda = "";
				celda << valor;
				gridTabla->SetCellValue(patron,offsetX+s,celda);
				gridTabla->SetCellTextColour(patron,offsetX+s,wxColour(255,0,0));
				numArreglos++;
			}
		}
	}
	if(numArreglos>0)
	{
	  wxString str=_T("Se han detectado y ajustado ");
  	str << numArreglos << _T(" valores por fuera de los rangos de las variables");
  	wxMessageBox(str,_T("Atención"));
	}
}

void DialogoEntrenamiento::cargarLinea(wxString linea)
{
	wxString otrosSep=";%$#/\t";
	wxArrayString patrones;
	wxChar sep=' ';
	for(int i=0;i<otrosSep.Len();i++)
	{
		linea.Replace(otrosSep[i],sep);
	}
	patrones=wxSplit(linea,sep);
	for(int i=patrones.GetCount()-1;i>=0;i--)
	{
		double val;
		patrones[i].ToDouble(&val);
		patrones[i]="";
		patrones[i] << val;
		if(patrones[i].Len()<1)
		{
			patrones.RemoveAt(i);
		}
	}

	if(patrones.GetCount()<1){return;}

  int NumCols = gridTabla->GetNumberCols();
  for(int i=patrones.GetCount(); i <= (NumCols); i++)
	{
		patrones.Add("0");
	}

	gridTabla->AppendRows();
	int patron=gridTabla->GetNumberRows()-1;
	for(int i=0;i<NumCols;i++)
	{
		gridTabla->SetCellValue(patron,i,patrones[i]);
	}

}

void DialogoEntrenamiento::OnCargar      (wxCommandEvent&   event)
{
	wxString extensiones="";
	extensiones << _T("Archivos CSV (*.csv)|*.csv");
	extensiones << _T("|Archivos TXT (*.txt)|*.txt");
	extensiones << _T("|Todos los archivos (*.*)|*.*");

	wxFileDialog dial(this, _("Tabla de datos"), "", "",extensiones,
											wxFD_OPEN|wxFD_FILE_MUST_EXIST);
  if (dial.ShowModal() == wxID_OK)
	{
		wxTextFile filePatrones;
		filePatrones.Open(dial.GetPath());
		wxString linea = filePatrones.GetFirstLine();
		cargarLinea(linea);
		while(!filePatrones.Eof())
		{
		  wxString linea = filePatrones.GetNextLine();
		  cargarLinea(linea);
		}
	}
	verificarDatos();
}

void DialogoEntrenamiento::limpiar      (int tipoAlgoritmo)
{
		switch(tipoAlgoritmo)
		{
			case 0 : Motor->limpiaAntesUniversoFijo();
								break;
			case 1 : Motor->limpiaAntesUniversoVariable();
								break;
			default : break;
		}

}

void DialogoEntrenamiento::OnEntrenar    (wxCommandEvent&   event)
{
	verificarDatos();
	bool flagLimpiar=checkLimpiar->GetValue();
	int tipoAlgoritmo=choiceAlgoritmo->GetSelection();

	if(flagLimpiar)
	{
		limpiar(tipoAlgoritmo);
	}

	double valorD;
	wxString celda="";
	int offsetX=Motor->entradas()->numeroVariables();
	for(int patron=0;patron<gridTabla->GetNumberRows();patron++)
	{
		float antecedentes[Motor->entradas()->numeroVariables()];
		float consecuentes[Motor->salidas()->numeroVariables()];

		for(int e=0;e<Motor->numeroEntradas();e++)
		{
			gridTabla->GetCellValue(patron,e).ToDouble(&valorD);
			antecedentes[e]=(float)valorD;
		}
		for(int s=0;s<Motor->numeroSalidas();s++)
		{
			gridTabla->GetCellValue(patron,offsetX+s).ToDouble(&valorD);
			consecuentes[s]=(float)valorD;
		}

		switch(tipoAlgoritmo)
		{
			case 0 : Motor->EntrenaUniversoFijo(antecedentes, consecuentes);
								break;
			case 1 : Motor->EntrenaUniversoVariable(antecedentes, consecuentes);
								break;
			default: break;
		}
	}

}

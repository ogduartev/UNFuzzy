#include "DialogoReglas.h"

BEGIN_EVENT_TABLE(DialogoReglas, wxDialog)
    EVT_CLOSE(DialogoReglas::OnClose)
    EVT_BUTTON(wxID_OK   , DialogoReglas::OnOK)
    EVT_BUTTON(DLG_REGLAS_BTNINSERTAR   , DialogoReglas::OnInsertar)
    EVT_BUTTON(DLG_REGLAS_BTNELIMINAR   , DialogoReglas::OnEliminar)
    EVT_BUTTON(DLG_REGLAS_BTNMODIFICADOR, DialogoReglas::OnModificador)
    EVT_BUTTON(DLG_REGLAS_BTNCERTEZA    , DialogoReglas::OnCerteza)
    EVT_BUTTON(DLG_REGLAS_BTNLLENAR     , DialogoReglas::OnLlenar)
    EVT_BUTTON(DLG_REGLAS_BTNRAPIDA     , DialogoReglas::OnRapida)
    EVT_BUTTON(DLG_REGLAS_BTNDESOCUPAR  , DialogoReglas::OnDesocupar)
END_EVENT_TABLE()

DialogoReglas::DialogoReglas(SistemaLogicaDifusa *SLD, wxWindow *parent)
:wxDialog(parent,wxID_ANY,wxString(_("Base de reglas")))
{
	Motor = SLD->motor;

  wxFlexGridSizer* sizerTotal;
  wxFlexGridSizer* sizerControles;
  wxFlexGridSizer* sizerBotones;
  wxFlexGridSizer* sizerOKCancel;
  wxStaticBoxSizer* sizerReglas;

  sizerTotal       = new wxFlexGridSizer(1,2,0);
  sizerControles   = new wxFlexGridSizer(2,4,0);
  sizerBotones     = new wxFlexGridSizer(1,8,0);
  sizerOKCancel    = new wxFlexGridSizer(2,1,0);
  sizerReglas      = new wxStaticBoxSizer(wxHORIZONTAL,this,_("Base de reglas"));

	int cols,rows;
	rows = Motor->numeroReglas();
	cols = Motor->numeroEntradas() + Motor->numeroSalidas();

	gridTabla = new wxGrid(this,DLG_REGLAS_TABLA, wxDefaultPosition, wxSize(600,400), wxFULL_REPAINT_ON_RESIZE);
	gridTabla->CreateGrid(rows,cols);
	gridTabla->SetDefaultCellBackgroundColour(GetBackgroundColour());

	llenarTabla();

  buttonInsertar   = new wxButton(this,DLG_REGLAS_BTNINSERTAR    ,_("Insertar Regla"));
  buttonEliminar   = new wxButton(this,DLG_REGLAS_BTNELIMINAR    ,_("Eliminar Reglas"));
  buttonModificador= new wxButton(this,DLG_REGLAS_BTNMODIFICADOR ,_("Modificador Lingüístico"));
  buttonCerteza    = new wxButton(this,DLG_REGLAS_BTNCERTEZA     ,_("Certeza"));
  buttonLlenar     = new wxButton(this,DLG_REGLAS_BTNLLENAR      ,_("Llenar la Base"));
  buttonRapida     = new wxButton(this,DLG_REGLAS_BTNRAPIDA      ,_("Definición rápida"));
  buttonDesocupar  = new wxButton(this,DLG_REGLAS_BTNDESOCUPAR   ,_("Vaciar la Base"));
  buttonOK         = new wxButton(this,wxID_OK,_("OK"));
  buttonCancel     = new wxButton(this,wxID_CANCEL,_("Cancelar"));

	sizerBotones->Add(buttonInsertar   , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerBotones->Add(buttonEliminar   , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerBotones->Add(buttonModificador, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerBotones->Add(buttonCerteza    , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerBotones->Add(buttonLlenar     , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerBotones->Add(buttonRapida     , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerBotones->Add(buttonDesocupar  , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

	sizerReglas->Add(gridTabla, 1, wxALL, 5);

	sizerControles->Add(sizerReglas, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerControles->Add(sizerBotones, 1, wxALIGN_CENTRE_HORIZONTAL|wxALIGN_CENTRE_VERTICAL|wxALL, 5);

	sizerOKCancel->Add(buttonOK, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerOKCancel->Add(buttonCancel, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

  sizerTotal->Add(sizerControles   , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
  sizerTotal->Add(sizerOKCancel    , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

  this->SetSizer(sizerTotal);
  this->Layout();
  sizerTotal->Fit(this);

}

DialogoReglas::~DialogoReglas()
{
	//dtor
}

void DialogoReglas::OnClose       (wxCloseEvent&   event)
{
	actualizarBase();
	EndModal(wxID_OK);
}

void DialogoReglas::OnOK(wxCommandEvent&   event)
{
	actualizarBase();
	EndModal(wxID_OK);
}

void DialogoReglas::llenarTabla()
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

	wxArrayString etiquetasEntrada[Motor->numeroEntradas()];
	for(int e=0;e<Motor->numeroEntradas();e++)
	{
		wxArrayString etiquetas;
		for(int et=0;et<Motor->entradas()->variable(e)->numeroConjuntos();et++)
		{
			etiquetas.Add(Motor->entradas()->variable(e)->conjunto(et)->nombre());
		}
		etiquetasEntrada[e]=etiquetas;
	}

	wxArrayString etiquetasSalida[Motor->numeroSalidas()];
	for(int e=0;e<Motor->numeroSalidas();e++)
	{
		wxArrayString etiquetas;
		for(int et=0;et<Motor->salidas()->variable(e)->numeroConjuntos();et++)
		{
			etiquetas.Add(Motor->salidas()->variable(e)->conjunto(et)->nombre());
		}
		etiquetasSalida[e]=etiquetas;
	}


	for(int regla=0;regla<Motor->numeroReglas();regla++)
	{
		celda ="";
		celda << _("Regla ") << (regla+1);

		float certeza = Motor->regla(regla)->certeza();
		if(certeza!=1.0)
		{
			celda << _("(") << certeza << _(")");
		}

		gridTabla->SetRowLabelValue(regla,celda);
		for(int e=0;e<Motor->numeroEntradas();e++)
		{
			celda ="";
			celda << Motor->conjuntoEntrada(regla,e)->nombre();

			if(Motor->modificador(regla,e)!=1.0)
			{
			  celda << _("(") << Motor->modificador(regla,e) << _(")");
			}

			gridTabla->SetCellValue(regla,e,celda);
			gridTabla->SetCellBackgroundColour(regla,e,wxColour(0xFF,0xF6,0xBA));
			wxGridCellEditor *cellEditor;
			cellEditor = new wxGridCellChoiceEditor(etiquetasEntrada[e]);
			gridTabla->SetCellEditor(regla,e,cellEditor);
		}
		for(int s=0;s<Motor->numeroSalidas();s++)
		{
			celda ="";
			celda << Motor->conjuntoSalida(regla,s)->nombre();
			gridTabla->SetCellValue(regla,offsetX+s,celda);
			gridTabla->SetCellBackgroundColour(regla,offsetX+s,wxColour(0xDC,0xEF,0xF7));
			wxGridCellEditor *cellEditor;
			cellEditor = new wxGridCellChoiceEditor(etiquetasSalida[s]);
			gridTabla->SetCellEditor(regla,offsetX+s,cellEditor);
		}

	}
}

void DialogoReglas::OnInsertar    (wxCommandEvent&   event)
{
	Regla *regla;
	regla=new Regla(Motor->entradas()->numeroVariables(),Motor->salidas()->numeroVariables());
	Motor->adicionarRegla(regla);
	gridTabla->AppendRows();
	llenarTabla();
}

void DialogoReglas::OnEliminar    (wxCommandEvent&   event)
{
	wxArrayInt selection=gridTabla->GetSelectedRows();

	if(selection.GetCount()<1)
	{
		wxMessageBox(_("Seleccione las reglas a eliminar"));
		return;
	}
	wxMessageDialog *dial;
	dial=new wxMessageDialog (this, _("¿Desea eliminar las reglas?"), _("Confirmación"), wxOK|wxCANCEL|wxCENTRE);
	if(dial->ShowModal() == wxID_OK)
	{
		for(int i=selection.GetCount()-1;i>-1;i--)
		{
			Motor->eliminarRegla(selection[i]);
			gridTabla->DeleteRows(selection[i]);
		}
		llenarTabla();
		gridTabla->ClearSelection();
	}
	delete dial;
}

void DialogoReglas::OnModificador    (wxCommandEvent&   event)
{
	actualizarBase();
  int NumCambios=0;
  wxTextEntryDialog *dial;
  wxString valor=_("1.000");

  dial = new wxTextEntryDialog(this, _("Valor del modificador (entre 0.0 y 5.0)"), _("Modificador Lingüístico"), valor, wxOK|wxCANCEL);
  if(dial->ShowModal()==wxID_CANCEL)
	{
		return;
	}
	valor=dial->GetValue();
	double modificaD=1.0;
	if(!valor.ToDouble(&modificaD))
	{
		wxMessageBox(_("El valor ingresado no es válido"),_("Atención"));
		return;
	}
	float modifica=(float)modificaD;
	if(modifica < 0.0){modifica=0.0;}
	if(modifica > 5.0){modifica=5.0;}
	int offsetX=Motor->entradas()->numeroVariables();

	wxGridCellCoordsArray celdas=gridTabla->GetSelectedCells();
	for(int i=0;i<celdas.Count();i++)
	{
  	int row = celdas[i].GetRow();
  	int col = celdas[i].GetCol();
  	if(col < offsetX)
		{
			Motor->modificador(row, col, modifica);
			NumCambios++;
		}else
		{
			gridTabla->DeselectCell(row,col);
		}
	}

	wxArrayInt colSel=gridTabla->GetSelectedCols();
	for(int i=0;i<colSel.Count();i++)
	{
		int col=colSel[i];
		if(col < offsetX)
		{
			for(int row=0;row<Motor->numeroReglas();row++)
			{
				Motor->modificador(row, col, modifica);
				NumCambios++;
			}
		}else
		{
			gridTabla->DeselectCol(col);
		}
	}
	wxArrayInt rowSel=gridTabla->GetSelectedRows();
	for(int i=0;i<rowSel.Count();i++)
	{
		int row=rowSel[i];
		for(int col=0;col<Motor->entradas()->numeroVariables();col++)
		{
			Motor->modificador(row, col, modifica);
			NumCambios++;
		}
		for(int col=0;col<Motor->salidas()->numeroVariables();col++)
		{
			gridTabla->DeselectCell(row,col+offsetX);
		}
	}

  wxGridCellCoordsArray cellsTL=gridTabla->GetSelectionBlockTopLeft();
  wxGridCellCoordsArray cellsBR=gridTabla->GetSelectionBlockBottomRight();
  int numBloques=cellsTL.Count();
  if(numBloques>cellsBR.Count()){numBloques=cellsBR.Count();}

  for(int i=0;i<numBloques;i++)
	{
		int rowIni=cellsTL[i].GetRow();
		int colIni=cellsTL[i].GetCol();
		int rowFin=cellsBR[i].GetRow();
		int colFin=cellsBR[i].GetCol();
		for(int row=rowIni;row<=rowFin;row++)
		{
			for(int col=colIni;col<=colFin;col++)
			{
				if(col < offsetX)
				{
					Motor->modificador(row, col, modifica);
					NumCambios++;
				}else
				{
					gridTabla->DeselectCell(row,col);
				}
			}
		}
	}

	valor = _("Se ha aplicado el modificador ");
	valor << modifica << _(" a ") << NumCambios << _(" etiquetas");
	wxMessageBox(valor,_("Información"));
  llenarTabla();
}

void DialogoReglas::OnCerteza    (wxCommandEvent&   event)
{
	wxArrayInt selection=gridTabla->GetSelectedRows();

	if(selection.GetCount()<1)
	{
		wxMessageBox(_("Seleccione las reglas cuya certeza quiere cambiar"));
		return;
	}

  wxTextEntryDialog *dial;
  wxString valor=_("1.000");

  dial = new wxTextEntryDialog(this, _("Valor de la certeza (entre 0.0 y 1.0)"), _("Certeza de la regla"), valor, wxOK|wxCANCEL);
  if(dial->ShowModal()==wxID_CANCEL)
	{
		return;
	}
	valor=dial->GetValue();
	double certezaD=1.0;
	if(!valor.ToDouble(&certezaD))
	{
		wxMessageBox(_("El valor ingresado no es válido"),_("Atención"));
		return;
	}
	float certeza=(float)certezaD;
	if(certeza < 0.0){certeza=0.0;}
	if(certeza > 1.0){certeza=1.0;}

	for(int i=0;i<selection.Count();i++)
	{
		int row=selection[i];
		Motor->regla(row)->certeza(certeza);
	}
	llenarTabla();
}

void DialogoReglas::OnLlenar    (wxCommandEvent&   event)
{
	wxMessageDialog *dial;
	dial=new wxMessageDialog (this, _("Esta acción borra todas las reglas y crea una base nueva ¿Desea proceder?"), _("Confirmación"), wxOK|wxCANCEL|wxCENTRE);
	if(dial->ShowModal() == wxID_OK)
	{
		while(gridTabla->GetNumberRows()>0)
		{
			gridTabla->DeleteRows(0);
		}
		Motor->llenarEntradasBase();
		for(int i=0;i<Motor->numeroReglas();i++)
		{
			gridTabla->AppendRows();
		}
		llenarTabla();
		gridTabla->ClearSelection();
	}
	delete dial;
}

void DialogoReglas::OnRapida    (wxCommandEvent&   event)
{
	wxArrayInt selection=gridTabla->GetSelectedCols();
	int offsetX=Motor->entradas()->numeroVariables();

	for(int i=0;i<selection.GetCount();i++)
	{
		if(selection[i] < offsetX)
		{
			selection.RemoveAt(i);
			i--;
		}
	}

	if(selection.GetCount()!=1)
	{
		wxMessageBox(_("Seleccione una (y solo una) salida para definir de forma rápida"));
		return;
	}

	int numSal=selection[0]-offsetX;

	wxArrayString opciones;
	opciones.Add(_("Sentido creciente"));
	opciones.Add(_("Sentido decreciente"));
	for(int i=0;i<Motor->salidas()->variable(numSal)->numeroConjuntos();i++)
	{
		wxString str=_("Sentido constante: ");
		str << Motor->salidas()->variable(numSal)->conjunto(i)->nombre();
		opciones.Add(str);
	}

	wxSingleChoiceDialog *dial;
	dial=new wxSingleChoiceDialog (this, _("Estas son las opciones para definir las reglas de la salida"), _("Definición rápida de la base de reglas"), opciones);
	if(dial->ShowModal() == wxID_OK)
	{
		int caso=dial->GetSelection();
		switch(caso)
		{
			case 0 :
							Motor->llenarSalidaCreciente(numSal);
							break;
			case 1 :
							Motor->llenarSalidaDecreciente(numSal);
							break;
			default :
							Motor->llenarSalidaConstante(numSal,caso-2);
							break;
		}
		llenarTabla();
	}

}

void DialogoReglas::OnDesocupar    (wxCommandEvent&   event)
{
	wxMessageDialog *dial;
	dial=new wxMessageDialog (this, _("¿Desea eliminar todas las reglas?"), _("Confirmación"), wxOK|wxCANCEL|wxCENTRE);
	if(dial->ShowModal() == wxID_OK)
	{
		while(gridTabla->GetNumberRows()>0)
		{
			gridTabla->DeleteRows(0);
		}
		Motor->desocuparBaseReglas();
		gridTabla->ClearSelection();
	}
	delete dial;
}

void DialogoReglas::actualizarBase()
{
	wxString celda="";
	int offsetX=Motor->entradas()->numeroVariables();

	wxArrayString etiquetasEntrada[Motor->numeroEntradas()];
	for(int e=0;e<Motor->numeroEntradas();e++)
	{
		wxArrayString etiquetas;
		for(int et=0;et<Motor->entradas()->variable(e)->numeroConjuntos();et++)
		{
			etiquetas.Add(Motor->entradas()->variable(e)->conjunto(et)->nombre());
		}
		etiquetasEntrada[e]=etiquetas;
	}

	wxArrayString etiquetasSalida[Motor->numeroSalidas()];
	for(int e=0;e<Motor->numeroSalidas();e++)
	{
		wxArrayString etiquetas;
		for(int et=0;et<Motor->salidas()->variable(e)->numeroConjuntos();et++)
		{
			etiquetas.Add(Motor->salidas()->variable(e)->conjunto(et)->nombre());
		}
		etiquetasSalida[e]=etiquetas;
	}

	for(int regla=0;regla<gridTabla->GetNumberRows();regla++)
	{
		for(int e=0;e<Motor->numeroEntradas();e++)
		{
			celda = gridTabla->GetCellValue(regla,e);
			if(Motor->modificador(regla,e)!=1.0)
			{
			  celda << _("(") << Motor->modificador(regla,e) << _(")");
			}
			for(int j=0;j<etiquetasEntrada[e].GetCount();j++)
			{
				if(celda==etiquetasEntrada[e][j])
				{
					Motor->conjuntoEntrada(regla, e, j);
				}
			}

		}
		for(int s=0;s<Motor->numeroSalidas();s++)
		{
			celda = gridTabla->GetCellValue(regla,s+offsetX);
			for(int j=0;j<etiquetasSalida[s].GetCount();j++)
			{
				if(celda==etiquetasSalida[s][j])
				{
					Motor->conjuntoSalida(regla, s, j);
				}
			}
		}
	}
}

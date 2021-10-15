#include "DialogoReglas.h"

BEGIN_EVENT_TABLE(DialogoReglas, wxDialog)
    EVT_CLOSE(DialogoReglas::OnClose)
    EVT_BUTTON(wxID_OK   , DialogoReglas::OnOK)
    EVT_CHECKBOX(DLG_REGLAS_CHECK2D       , DialogoReglas::OnCheck2D)
    EVT_CHECKBOX(DLG_REGLAS_CHECK2D       , DialogoReglas::OnCheckCerteza)
    EVT_BUTTON(DLG_REGLAS_BTNINSERTAR   , DialogoReglas::OnInsertar)
    EVT_BUTTON(DLG_REGLAS_BTNELIMINAR   , DialogoReglas::OnEliminar)
    EVT_BUTTON(DLG_REGLAS_BTNMODIFICADOR, DialogoReglas::OnModificador)
    EVT_BUTTON(DLG_REGLAS_BTNCERTEZA    , DialogoReglas::OnCerteza)
    EVT_BUTTON(DLG_REGLAS_BTNLLENAR     , DialogoReglas::OnLlenar)
    EVT_BUTTON(DLG_REGLAS_BTNRAPIDA     , DialogoReglas::OnRapida)
    EVT_BUTTON(DLG_REGLAS_BTNDESOCUPAR  , DialogoReglas::OnDesocupar)
END_EVENT_TABLE()

DialogoReglas::DialogoReglas(SistemaLogicaDifusa *SLD, wxWindow *parent)
:wxDialog(parent,wxID_ANY,wxString(_("Rule base")))
{
	Motor = SLD->motor;
	flagCerteza=false;
	flag2D=false;

  wxFlexGridSizer* sizerTotal;
  wxFlexGridSizer* sizerControles;
  wxFlexGridSizer* sizerBotones;
  wxFlexGridSizer* sizerOKCancel;
  wxStaticBoxSizer* sizerReglas;

  sizerTotal       = new wxFlexGridSizer(1,2,0);
  sizerControles   = new wxFlexGridSizer(2,4,0);
  sizerBotones     = new wxFlexGridSizer(1,10,0);
  sizerOKCancel    = new wxFlexGridSizer(2,1,0);
  sizerReglas      = new wxStaticBoxSizer(wxHORIZONTAL,this,_("Rule base"));

	int cols,rows;
	rows = Motor->numeroReglas();
	cols = Motor->numeroEntradas() + Motor->numeroSalidas();

	gridTabla = new wxGrid(this,DLG_REGLAS_TABLA, wxDefaultPosition, wxSize(600,400), wxFULL_REPAINT_ON_RESIZE);
	gridTabla->CreateGrid(rows,cols);
	gridTabla->SetDefaultCellBackgroundColour(GetBackgroundColour());
	gridTabla->SetSelectionBackground(wxColour(0x4F,0x76,0xB9));

  check2D          = new wxCheckBox(this,DLG_REGLAS_CHECK2D   ,_("2D array"),                wxDefaultPosition, wxSize(175,25));
  checkCerteza     = new wxCheckBox(this,DLG_REGLAS_CHECK2D   ,_("Certainty"),                wxDefaultPosition, wxSize(175,25));
  buttonInsertar   = new wxButton(this,DLG_REGLAS_BTNINSERTAR    ,_("Insert rule"),             wxDefaultPosition, wxSize(175,25));
  buttonEliminar   = new wxButton(this,DLG_REGLAS_BTNELIMINAR    ,_("Delete rule"),             wxDefaultPosition, wxSize(175,25));
  buttonModificador= new wxButton(this,DLG_REGLAS_BTNMODIFICADOR ,_("Linguistic modifier"),     wxDefaultPosition, wxSize(175,25));
  buttonCerteza    = new wxButton(this,DLG_REGLAS_BTNCERTEZA     ,_("Certainty"),               wxDefaultPosition, wxSize(175,25));
  buttonLlenar     = new wxButton(this,DLG_REGLAS_BTNLLENAR      ,_("Fulfill the Rule base"),   wxDefaultPosition, wxSize(175,25));
  buttonRapida     = new wxButton(this,DLG_REGLAS_BTNRAPIDA      ,_("Rapid definition"),        wxDefaultPosition, wxSize(175,25));
  buttonDesocupar  = new wxButton(this,DLG_REGLAS_BTNDESOCUPAR   ,_("Delete all the Rule base"),wxDefaultPosition, wxSize(175,25));
  buttonOK         = new wxButton(this,wxID_OK,_("OK"));
  buttonCancel     = new wxButton(this,wxID_CANCEL,_("Cancel"));

	sizerBotones->Add(check2D          , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerBotones->Add(checkCerteza     , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerBotones->Add(buttonInsertar   , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerBotones->Add(buttonEliminar   , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerBotones->Add(buttonModificador, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerBotones->Add(buttonCerteza    , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerBotones->Add(buttonLlenar     , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerBotones->Add(buttonRapida     , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerBotones->Add(buttonDesocupar  , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

	if(Motor->numeroEntradas()==2 && Motor->numeroSalidas()==1)
	{
	  check2D->Show(true);
	}else
	{
	  check2D->Show(false);
	}
  checkCerteza->Show(true);
	check2D->SetValue(flag2D);
	checkCerteza->SetValue(flagCerteza);
	llenarTabla();

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

void DialogoReglas::OnCheck2D(wxCommandEvent&   event)
{
  llenarTabla();
  checkCerteza->Show(!check2D->GetValue());
  buttonModificador->Show(!check2D->GetValue());
  buttonCerteza->Show(!check2D->GetValue());
}

void DialogoReglas::OnCheckCerteza(wxCommandEvent&   event)
{
  llenarTabla();
//  buttonModificador->Show(!check2D->GetValue());
//  buttonCerteza->Show(!check2D->GetValue());
}

void DialogoReglas::llenarTabla()
{
	if(tabla2D())
	{
		llenarTabla2D();
		return;
	}
	int cols,rows;
	rows = Motor->numeroReglas();
	cols = Motor->numeroEntradas() + Motor->numeroSalidas();

	if(gridTabla->GetNumberCols()>0)
	{
  	gridTabla->DeleteCols(0,gridTabla->GetNumberCols());
	}
	if(gridTabla->GetNumberRows()>0)
	{
	  gridTabla->DeleteRows(0,gridTabla->GetNumberRows());
	}

	gridTabla->InsertCols(0,cols);
	gridTabla->InsertRows(0,rows);

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
		celda << _("Rule ") << (regla+1);
/*
		double certeza = Motor->regla(regla)->certeza();
		if(certeza!=1.0)
		{
			celda << _("(") << certeza << _(")");
		}
*/
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
	llenarCerteza();
	gridTabla->AutoSize();
}

void DialogoReglas::llenarCerteza()
{
	flagCerteza=checkCerteza->GetValue();
	int cols=gridTabla->GetNumberCols();
	if (!tabla2D() && flagCerteza)
	{
    gridTabla->InsertCols(cols,1);
    gridTabla->SetColLabelValue(cols,_("Certainty"));
		for(int regla=0;regla<Motor->numeroReglas();regla++)
		{
			wxString celda = "";

			double certeza = Motor->regla(regla)->certeza();
			celda << certeza ;

			gridTabla->SetCellValue(regla,cols,celda);
		}
	}
}

bool DialogoReglas::tabla2D()
{
	bool flag;
	flag2D=check2D->GetValue();
	flag=flag2D && Motor->entradas()->numeroVariables()==2 && Motor->salidas()->numeroVariables()==1;
	return flag;
}

void DialogoReglas::llenarTabla2D()
{
	/* OJO: Falta mostrar Modificadores y certezas */
	if(!tabla2D()){return;}

	int numSalida=0;

	wxString celda;
	int cols,rows;
	cols = Motor->entradas()->variable(0)->numeroConjuntos();
	rows = Motor->entradas()->variable(1)->numeroConjuntos();

	if(gridTabla->GetNumberCols()>0)
	{
  	gridTabla->DeleteCols(0,gridTabla->GetNumberCols());
	}
	if(gridTabla->GetNumberRows()>0)
	{
	  gridTabla->DeleteRows(0,gridTabla->GetNumberRows());
	}

	gridTabla->InsertCols(0,cols);
	gridTabla->InsertRows(0,rows);

	for(int e=0;e<cols;e++)
	{
		celda ="";
		celda << Motor->entradas()->conjuntoEnVariable(0,e)->nombre();
		gridTabla->SetColLabelValue(e,celda);
	}
	for(int e=0;e<rows;e++)
	{
		celda ="";
		celda << Motor->entradas()->conjuntoEnVariable(1,e)->nombre();
		gridTabla->SetRowLabelValue(e,celda);
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
		int col,row;
		col=Motor->numConjuntoEntrada(regla, 0);
		row=Motor->numConjuntoEntrada(regla, 1);

		celda ="";
		celda << Motor->conjuntoSalida(regla,numSalida)->nombre();

		gridTabla->SetCellValue(row,col,celda);
		gridTabla->SetCellBackgroundColour(row,col,wxColour(0xDC,0xEF,0xF7));
		wxGridCellEditor *cellEditor;
		cellEditor = new wxGridCellChoiceEditor(etiquetasSalida[numSalida]);
		gridTabla->SetCellEditor(row,col,cellEditor);
	}
	gridTabla->AutoSize();
}

wxGridCellCoordsArray DialogoReglas::getSelectedCells()
{
	int nc = gridTabla->GetNumberCols();
	int nr = gridTabla->GetNumberRows();
	wxGridCellCoordsArray   cells = gridTabla->GetSelectedCells();
	wxArrayInt               cols = gridTabla->GetSelectedCols();
	wxArrayInt               rows = gridTabla->GetSelectedRows();
	wxGridCellCoordsArray blockBR = gridTabla->GetSelectionBlockBottomRight();
	wxGridCellCoordsArray blockTL = gridTabla->GetSelectionBlockTopLeft();

	for(ulong c=0;c<cols.GetCount();c++)
	{
		for(int i=0;i<nr;i++)
		{
			cells.Add(wxGridCellCoords (i, cols[c]));
		}
	}

	for(ulong r=0;r<rows.GetCount();r++)
	{
		for(int i=0;i<nc;i++)
		{
			cells.Add(wxGridCellCoords (rows[r],i));
		}
	}

	for(ulong b=0;b<blockBR.GetCount();b++)
	{
	  int ro=blockTL[b].GetRow();
	  int rf=blockBR[b].GetRow();
	  int co=blockTL[b].GetCol();
	  int cf=blockBR[b].GetCol();

	  for(int r=ro;r<=rf;r++)
		{
		  for(int c=co;c<=cf;c++)
			{
				cells.Add(wxGridCellCoords (r,c));
			}
		}
	}

	wxGridCellCoordsArray cellsNR; // no se repite
	for(ulong i=0;i<cells.GetCount();i++)
  {
  	bool flag=false;
  	for(ulong j=0;j<cellsNR.GetCount();j++)
		{
		  if(cells[i]==cellsNR[j])
			{
			  flag=true;
			}
		}
		if(!flag)
		{
		  cellsNR.Add(wxGridCellCoords(cells[i].GetRow(),cells[i].GetCol()));
		}
  }

	return cells;
}

void DialogoReglas::insertar2D()
{
	wxGridCellCoordsArray cells=getSelectedCells();
	if(cells.GetCount()<1)
	{
		wxMessageBox(_("Select the position of rules to be inserted"));
		return;
	}
	for(int i=0;i<cells.GetCount();i++)
	{
		int e1=cells[i].GetCol();
		int e2=cells[i].GetRow();
		bool flag=false;
		for(int j=0;j<Motor->numeroReglas();j++)
		{
			if(Motor->numConjuntoEntrada(j,0)==e1 && Motor->numConjuntoEntrada(j,1)==e2)
			{
				flag=true;
			}
		}
		if(!flag)
		{
			Regla *regla;
			regla=new Regla(Motor->entradas()->numeroVariables(),Motor->salidas()->numeroVariables());
			regla->conjuntoEntrada(0,e1);
			regla->conjuntoEntrada(1,e2);
			regla->conjuntoSalida(0,0);
			Motor->adicionarRegla(regla);
		}
	}
	llenarTabla();
}

void DialogoReglas::OnInsertar    (wxCommandEvent&   event)
{
	if(tabla2D())
	{
		insertar2D();
		return;
	}
	Regla *regla;
	regla=new Regla(Motor->entradas()->numeroVariables(),Motor->salidas()->numeroVariables());
	Motor->adicionarRegla(regla);
	gridTabla->AppendRows();
	llenarTabla();
}

void DialogoReglas::eliminar2D()
{
	wxGridCellCoordsArray cells=getSelectedCells();
	if(cells.GetCount()<1)
	{
		wxMessageBox(_("Select the rules to be deleted"));
		return;
	}
	wxMessageDialog *dial;
	dial=new wxMessageDialog (this, _("Do you want to delete the rules?"), _("Confirmation"), wxOK|wxCANCEL|wxCENTRE);
	if(dial->ShowModal() == wxID_OK)
	{
		for(int i=cells.GetCount()-1;i>-1;i--)
		{
			int e1=cells[i].GetCol();
			int e2=cells[i].GetRow();
			for(int j=0;j<Motor->numeroReglas();j++)
			{
				if(Motor->numConjuntoEntrada(j,0)==e1 && Motor->numConjuntoEntrada(j,1)==e2)
				{
					Motor->eliminarRegla(j);
					j--;
				}
			}
		}
		llenarTabla();
		gridTabla->ClearSelection();
	}
	delete dial;
}

void DialogoReglas::OnEliminar    (wxCommandEvent&   event)
{
	if(tabla2D())
	{
		eliminar2D();
	  return;
	}

	wxArrayInt selection=gridTabla->GetSelectedRows();

	if(selection.GetCount()<1)
	{
		wxMessageBox(_("Select the rules to be deleted"));
		return;
	}
	wxMessageDialog *dial;
	dial=new wxMessageDialog (this, _("Do you want to delete the rules?"), _("Confirmation"), wxOK|wxCANCEL|wxCENTRE);
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

  dial = new wxTextEntryDialog(this, _("Modifier value (between 0.0 y 5.0)"), _("Linguistic modifier"), valor, wxOK|wxCANCEL);
  if(dial->ShowModal()==wxID_CANCEL)
	{
		return;
	}
	valor=dial->GetValue();
	double modificaD=1.0;
	if(!valor.ToDouble(&modificaD))
	{
		wxMessageBox(_("The value provided is not a valid one"),_("Warning"));
		return;
	}
	double modifica=(double)modificaD;
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

	valor = _("The modifier has been applied ");
	valor << modifica << _(" to ") << NumCambios << _(" labels");
	wxMessageBox(valor,_("Information"));
  llenarTabla();
}

void DialogoReglas::OnCerteza    (wxCommandEvent&   event)
{
	wxArrayInt selection=gridTabla->GetSelectedRows();

	if(selection.GetCount()<1)
	{
		wxMessageBox(_("Select the rules whose certainty you want to change"));
		return;
	}

  wxTextEntryDialog *dial;
  wxString valor=_("1.000");

  dial = new wxTextEntryDialog(this, _("Certainty value (between 0.0 y 1.0)"), _("Rule certainty"), valor, wxOK|wxCANCEL);
  if(dial->ShowModal()==wxID_CANCEL)
	{
		return;
	}
	valor=dial->GetValue();
	double certezaD=1.0;
	if(!valor.ToDouble(&certezaD))
	{
		wxMessageBox(_("The value provided is not a valid one"),_("Warning"));
		return;
	}
	double certeza=(double)certezaD;
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
	dial=new wxMessageDialog (this, _("This action will delete all the rules and create a new rule base ¿Do you want to proceed?"), _("Confirmation"), wxOK|wxCANCEL|wxCENTRE);
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
	int numSal;
	if(tabla2D())
	{
	  numSal=0;
	}else
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
			wxMessageBox(_("Select one (and only one) output to be rapidly defined"));
			return;
		}

		numSal=selection[0]-offsetX;
	}


	wxArrayString opciones;
	opciones.Add(_("Increasing direction"));
	opciones.Add(_("Decreasing direction"));
	for(int i=0;i<Motor->salidas()->variable(numSal)->numeroConjuntos();i++)
	{
		wxString str=_("Constant direction: ");
		str << Motor->salidas()->variable(numSal)->conjunto(i)->nombre();
		opciones.Add(str);
	}

	wxSingleChoiceDialog *dial;
	dial=new wxSingleChoiceDialog (this, _("These are the options to define the rules of the ouput"), _("Rule base rapid definition"), opciones);
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
	dial=new wxMessageDialog (this, _("Do you want to delete the rules?"), _("Confirmation"), wxOK|wxCANCEL|wxCENTRE);
	if(dial->ShowModal() == wxID_OK)
	{
		while(gridTabla->GetNumberRows()>0)
		{
			gridTabla->DeleteRows(0);
		}
		Motor->desocuparBaseReglas();
		gridTabla->ClearSelection();
		llenarTabla();
	}
	delete dial;
}

void DialogoReglas::actualizarBase()
{
	if(tabla2D())
	{
	  actualizarBase2D();
	  return;
	}
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

void DialogoReglas::actualizarBase2D()
{
  if(!tabla2D()){return;}
  int numSalida=0;

  wxString celda;
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

	int cols,rows;
	cols = Motor->entradas()->variable(0)->numeroConjuntos();
	rows = Motor->entradas()->variable(1)->numeroConjuntos();
	for(int row=0;row<rows;row++)
	{
	  for(int col=0;col<cols;col++)
		{
			for(int regla=0;regla < Motor->numeroReglas(); regla++)
			{
			  if(Motor->regla(regla)->conjuntoEntrada(0)== col &&
					 Motor->regla(regla)->conjuntoEntrada(1)== row)
				{
					celda = gridTabla->GetCellValue(row,col);
					for(int j=0;j<etiquetasSalida[numSalida].GetCount();j++)
					{
						if(celda==etiquetasSalida[numSalida][j])
						{
							Motor->conjuntoSalida(regla, numSalida, j);
						}
					}
				}
			}
		}
	}
}

#include "DialogoSLD.h"


BEGIN_EVENT_TABLE(DialogoSLD, wxDialog)
    EVT_CLOSE(DialogoSLD::OnClose)
    EVT_BUTTON(DLG_FRONTAL_SALIR      , DialogoSLD::OnSalir)
    EVT_BUTTON(DLG_FRONTAL_AYUDA      , DialogoSLD::OnAyuda)
    EVT_BUTTON(DLG_FRONTAL_ENTRADAS   , DialogoSLD::OnEntradas)
    EVT_BUTTON(DLG_FRONTAL_SALIDAS    , DialogoSLD::OnSalidas)
    EVT_BUTTON(DLG_FRONTAL_REGLAS     , DialogoSLD::OnReglas)
    EVT_BUTTON(DLG_FRONTAL_INFERENCIA , DialogoSLD::OnInferencia)
    EVT_BUTTON(DLG_FRONTAL_NUEVO      , DialogoSLD::OnNuevo)
    EVT_BUTTON(DLG_FRONTAL_DESCRIPCION, DialogoSLD::OnDescripcion)
    EVT_BUTTON(DLG_FRONTAL_LEER       , DialogoSLD::OnLeer)
    EVT_BUTTON(DLG_FRONTAL_GUARDAR    , DialogoSLD::OnGuardar)
    EVT_BUTTON(DLG_FRONTAL_ENTRENAR   , DialogoSLD::OnEntrenar)
    EVT_BUTTON(DLG_FRONTAL_FUNCION    , DialogoSLD::OnFuncion)
    EVT_BUTTON(DLG_FRONTAL_CALCULAR   , DialogoSLD::OnCalcular)
    EVT_BUTTON(DLG_FRONTAL_PASOAPASO  , DialogoSLD::OnPasoAPaso)
    EVT_BUTTON(DLG_FRONTAL_CODIGO     , DialogoSLD::OnCodigo)
    EVT_BUTTON(DLG_FRONTAL_TABLA      , DialogoSLD::OnTabla)
    EVT_BUTTON(DLG_FRONTAL_IDIOMA     , DialogoSLD::OnIdioma)
    EVT_BUTTON(DLG_FRONTAL_ABOUT      , DialogoSLD::OnAbout)
END_EVENT_TABLE()

DialogoSLD::DialogoSLD(wxWindow* parent, SistemaLogicaDifusa* sld,bool flagStandAlone, const wxString &title)
    : wxDialog(parent, -1, title)
{
	SLD=sld;
    this->SetSizeHints(wxDefaultSize, wxDefaultSize);
    wxFlexGridSizer*  sizerTotal;
    wxFlexGridSizer*  sizerIconos;
    wxBoxSizer*       sizerControles;
    wxGridBagSizer*   sizerSLD;

    sizerTotal      = new wxFlexGridSizer(1,3,0);
    sizerIconos     = new wxFlexGridSizer(12,1,0);
    sizerControles  = new wxBoxSizer(wxHORIZONTAL);
    sizerSLD        = new wxGridBagSizer(0,0);

    staticTextDescripcion = new wxStaticText(this, DLG_FRONTAL_DESCRIBE, _("Description:\n"), wxDefaultPosition, wxDefaultSize, 0);
//f4cdb5
    buttonSalir           = new wxButton(this, DLG_FRONTAL_SALIR      , _("&Exit")      , wxDefaultPosition, wxDefaultSize, 0);
    buttonAyuda           = new wxButton(this, DLG_FRONTAL_AYUDA      , _("&Help")      , wxDefaultPosition, wxDefaultSize, 0);

    buttonEntradas        = new wxBitmapButton(this, DLG_FRONTAL_ENTRADAS   , wxMEMORY_BITMAP(entradas));
    buttonSalidas         = new wxBitmapButton(this, DLG_FRONTAL_SALIDAS    , wxMEMORY_BITMAP(salidas));
    buttonReglas          = new wxBitmapButton(this, DLG_FRONTAL_REGLAS     , wxMEMORY_BITMAP(reglas));
    buttonInferencia      = new wxBitmapButton(this, DLG_FRONTAL_INFERENCIA , wxMEMORY_BITMAP(motor));

    buttonNuevo           = new wxBitmapButton(this, DLG_FRONTAL_NUEVO      , wxMEMORY_BITMAP(nuevo)    ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
    buttonLeer            = new wxBitmapButton(this, DLG_FRONTAL_LEER       , wxMEMORY_BITMAP(leer)     ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
    buttonGuardar         = new wxBitmapButton(this, DLG_FRONTAL_GUARDAR    , wxMEMORY_BITMAP(guardar)  ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
    buttonDescripcion     = new wxBitmapButton(this, DLG_FRONTAL_DESCRIPCION, wxMEMORY_BITMAP(describe) ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
    buttonEntrenar        = new wxBitmapButton(this, DLG_FRONTAL_ENTRENAR   , wxMEMORY_BITMAP(entrenar) ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
    buttonFuncion         = new wxBitmapButton(this, DLG_FRONTAL_FUNCION    , wxMEMORY_BITMAP(funcion)  ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
    buttonCalcular        = new wxBitmapButton(this, DLG_FRONTAL_CALCULAR   , wxMEMORY_BITMAP(calcular) ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
    buttonPasoAPaso       = new wxBitmapButton(this, DLG_FRONTAL_PASOAPASO  , wxMEMORY_BITMAP(paso)     ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
    buttonCodigo          = new wxBitmapButton(this, DLG_FRONTAL_CODIGO     , wxMEMORY_BITMAP(codigo)   ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
    buttonTabla           = new wxBitmapButton(this, DLG_FRONTAL_TABLA      , wxMEMORY_BITMAP(tabla)    ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
    buttonIdioma          = new wxBitmapButton(this, DLG_FRONTAL_IDIOMA     , wxMEMORY_BITMAP(idioma)   ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
    buttonAbout           = new wxBitmapButton(this, DLG_FRONTAL_ABOUT      , wxMEMORY_BITMAP(acerca)   ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);

		if(flagStandAlone)
		{
			wxFileName f(wxStandardPaths::Get().GetExecutablePath());
			wxString strLocale(f.GetPath());
			strLocale << "/locale/";
			MiLocale =new wxLocale(wxLANGUAGE_DEFAULT);
			MiLocale->AddCatalogLookupPathPrefix(strLocale);
			MiLocale->AddCatalog("en");
			setlocale (LC_NUMERIC,"C");
		}else
		{
			buttonIdioma->Show(false);
			MiLocale=NULL;
		}

    staticTextDescripcion->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT , wxNORMAL, wxNORMAL));
    llenarTexto();

    int sepIcon=1;
#ifdef __WXGTK__
 		sepIcon=-3;
#endif


    sizerIconos->Add(buttonNuevo      , 0, wxALL, sepIcon);
    sizerIconos->Add(buttonLeer       , 0, wxALL, sepIcon);
    sizerIconos->Add(buttonGuardar    , 0, wxALL, sepIcon);
    sizerIconos->Add(buttonDescripcion, 0, wxALL, sepIcon);
    sizerIconos->Add(buttonEntrenar   , 0, wxALL, sepIcon);
    sizerIconos->Add(buttonFuncion    , 0, wxALL, sepIcon);
    sizerIconos->Add(buttonCalcular   , 0, wxALL, sepIcon);
    sizerIconos->Add(buttonPasoAPaso  , 0, wxALL, sepIcon);
    sizerIconos->Add(buttonCodigo     , 0, wxALL, sepIcon);
    sizerIconos->Add(buttonTabla      , 0, wxALL, sepIcon);
    sizerIconos->Add(buttonIdioma     , 0, wxALL, sepIcon);
    sizerIconos->Add(buttonAbout      , 0, wxALL, sepIcon);

    sizerSLD->Add(buttonEntradas  ,wxGBPosition(1,0), wxDefaultSpan, wxALL,0);
    sizerSLD->Add(buttonSalidas   ,wxGBPosition(1,2), wxDefaultSpan, wxALL,0);
    sizerSLD->Add(buttonReglas    ,wxGBPosition(0,1), wxDefaultSpan, wxALL,0);
    sizerSLD->Add(buttonInferencia,wxGBPosition(1,1), wxDefaultSpan, wxALL,0);

    sizerControles->Add(buttonAyuda     , 0, wxALL, 5);
    sizerControles->Add(buttonSalir     , 0, wxALL, 5);

    sizerTotal->Add(sizerIconos          , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 0);
    sizerTotal->Add(staticTextDescripcion, 0,wxALIGN_CENTRE_HORIZONTAL|wxTOP, 5);
    sizerTotal->Add(sizerSLD             , 1, wxALIGN_CENTRE_HORIZONTAL|wxTOP|wxBOTTOM, 20);
    sizerTotal->Add(sizerControles       , 1, wxALIGN_CENTRE_HORIZONTAL, 0);

    this->SetSizer(sizerTotal);
    this->Layout();
    sizerTotal->Fit(this);
}


DialogoSLD::~DialogoSLD()
{
}

void DialogoSLD::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void DialogoSLD::OnSalir(wxCommandEvent &event)
{
    Destroy();
}

void DialogoSLD::OnAyuda(wxCommandEvent &event)
{
  wxMessageBox(_("Under development..."), _("Help"));
}

void DialogoSLD::OnEntradas(wxCommandEvent &event)
{
	DialogoVariable *dlg;
	dlg=new DialogoVariable(SLD->entradas, SLD, true, this);
	if(dlg->ShowModal() == wxID_OK)
	{
		llenarTexto();
	}
	delete dlg;
}

void DialogoSLD::OnSalidas(wxCommandEvent &event)
{
	DialogoVariable *dlg;
	dlg=new DialogoVariable(SLD->salidas, SLD, false, this);
	if(dlg->ShowModal() == wxID_OK)
	{
		llenarTexto();
	}
	delete dlg;
}

void DialogoSLD::OnReglas(wxCommandEvent &event)
{
	DialogoReglas *dlg;
	dlg=new DialogoReglas(SLD, this);
	if(dlg->ShowModal() == wxID_OK)
	{
		llenarTexto();
	}
	delete dlg;
}

void DialogoSLD::OnInferencia(wxCommandEvent &event)
{
	DialogoMotor *dlg;
	dlg=new DialogoMotor(SLD,this);
	if(dlg->ShowModal() == wxID_OK)
	{
  	llenarTexto();
	}
	delete dlg;
}

void DialogoSLD::OnNuevo      (wxCommandEvent& event)
{
	wxMessageDialog* dial;
  dial = new wxMessageDialog(this,_("This action will erase all the previous definitions and create a new system. It can not be undo. ¿Do you want to proceed?"),_("Warning"),wxOK|wxCANCEL|wxCANCEL_DEFAULT);
	if(dial->ShowModal() == wxID_OK)
	{
  	SLD->crearMinimoSLD(1,1);
  	llenarTexto();
	}
	delete dial;
}

void DialogoSLD::OnLeer       (wxCommandEvent& event)
{
	wxMessageDialog* dial;
  dial = new wxMessageDialog(this,_("This action will erase all the previous definitions and create a new system. It can not be undo. ¿Do you want to proceed?"),_("Warning"),wxOK|wxCANCEL|wxCANCEL_DEFAULT);
	if(dial->ShowModal() == wxID_OK)
	{
		wxString extensiones="";
		extensiones << _("UNFUZZY 3 files (*.unf)|*.unf");
//		extensiones << _("|Archivos UNFUZZY 1 (*.dif)|*.dif");
//		extensiones << _("|Archivos UNFUZZY 1 (*.*)|*.*");

		wxFileDialog dial2(this, _("Fuzzy Logic System"), "", "",extensiones,
												wxFD_OPEN|wxFD_FILE_MUST_EXIST);
		if (dial2.ShowModal() == wxID_OK)
		{
			Archivador Archivo(SLD);
			Archivo.leer(dial2.GetPath());
		}

  	llenarTexto();
	}
	delete dial;
}

void DialogoSLD::OnGuardar    (wxCommandEvent& event)
{
	wxString extensiones="";
	extensiones << _("UNFUZZY 3 files (*.unf)|*.unf");

	wxFileDialog dial(this, _("Fuzzy Logic System"), "", "",extensiones,
											wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
  if (dial.ShowModal() == wxID_OK)
	{
		Archivador Archivo(SLD);
		Archivo.guardar(dial.GetPath());
	}

}

void DialogoSLD::OnDescripcion(wxCommandEvent& event)
{
	DialogoInfo *dlg;
	dlg=new DialogoInfo(wxString(SLD->nombre),wxString(SLD->descripcion), this);
	if(dlg->ShowModal() == wxID_OK)
	{
		SLD->nombre=dlg->Nombre;
		SLD->descripcion=dlg->Descripcion;
		llenarTexto();
	}
	delete dlg;
}

void DialogoSLD::OnEntrenar   (wxCommandEvent& event)
{
	DialogoEntrenamiento *dlg;
	dlg=new DialogoEntrenamiento(SLD, this);
	if(dlg->ShowModal() == wxID_OK)
	{
		llenarTexto();
	}
	delete dlg;
}

void DialogoSLD::OnFuncion    (wxCommandEvent& event)
{
	DialogoFuncionSld *dlg;
	dlg=new DialogoFuncionSld(SLD,this);
	if(dlg->ShowModal() == wxID_OK)
	{
	}
	delete dlg;
}

void DialogoSLD::OnCalcular   (wxCommandEvent& event)
{
	DialogoCalculoSld *dlg;
	dlg=new DialogoCalculoSld(SLD,this);
	if(dlg->ShowModal() == wxID_OK)
	{
	}
	delete dlg;
}

void DialogoSLD::OnPasoAPaso (wxCommandEvent& event)
{
	DialogoPaso *dlg;
	dlg=new DialogoPaso(SLD,this);
	if(dlg->ShowModal() == wxID_OK)
	{
	}
	delete dlg;
}

void DialogoSLD::OnCodigo    (wxCommandEvent& event)
{
	wxString extensiones="";
	extensiones << _("CPP files (*.cpp)|*.cpp");
	extensiones << _("|C files (*.c)|*.c");

	wxFileDialog dial(this, _("Source code generated"), "", "",extensiones,
											wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
  if (dial.ShowModal() == wxID_OK)
	{
		wxString nombreClase=_("myFLS");  // solo se usa en cpp
		SLD->generarCodigo(dial.GetPath(),nombreClase);
	}
}

void DialogoSLD::OnTabla     (wxCommandEvent& event)
{
	wxString extensiones="";
	extensiones << _("CSV files (*.csv)|*.csv");
	extensiones << _("|text files (*.txt)|*.txt");
	extensiones << _("|All files (*.*)|*.*");

	wxFileDialog dial(this, _("Data table"), "", "",extensiones,
											wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
  if (dial.ShowModal() == wxID_OK)
	{
		SLD->crearArchivoTabla(dial.GetPath());
	}
}

void DialogoSLD::OnIdioma    (wxCommandEvent& event)
{
	wxSingleChoiceDialog *dialogo;
	wxArrayString idiomas;
	idiomas.push_back(_("Spanish"));
	idiomas.push_back(_("English"));
	dialogo=new wxSingleChoiceDialog((wxWindow*)this,_("Available languages"),_("Select the language"),idiomas);//,(char**)NULL,wxCHOICEDLG_STYLE,wxDefaultPosition);
	if(dialogo->ShowModal()==wxID_OK)
	{
		wxDELETE(MiLocale);
		wxFileName f(wxStandardPaths::Get().GetExecutablePath());
		wxString strLocale(f.GetPath());
		strLocale << "/locale/";
		int idioma=dialogo->GetSelection();
		switch(idioma)
		{
			case 0 :	MiLocale =new wxLocale(wxLANGUAGE_SPANISH);
								MiLocale->AddCatalogLookupPathPrefix(strLocale);
								MiLocale->AddCatalog("es");
								break;
			case 1 :	MiLocale =new wxLocale(wxLANGUAGE_ENGLISH);
								MiLocale->AddCatalogLookupPathPrefix(strLocale);
								MiLocale->AddCatalog("en");
								break;
			default:	MiLocale =new wxLocale(wxLANGUAGE_DEFAULT);
								MiLocale->AddCatalogLookupPathPrefix(strLocale);
								MiLocale->AddCatalog("es");
								break;
		}
		setlocale (LC_NUMERIC,"C");
		llenarTexto();
	}
}

void DialogoSLD::OnAbout(wxCommandEvent& event)
{
  wxAboutDialogInfo info;
  info.SetName(_("UNFuzzy"));
  info.SetVersion(_("3.0.0. Beta"));
  info.SetDescription(_("Software for design of Fuzzy Logic Systems.\nUniversidad Nacional de Colombia"));
  info.SetCopyright(_("(C) 2019 Oscar Duarte <ogduartev@unal.edu.co>"));
  wxAboutBox(info);
}

void DialogoSLD::llenarTexto()
{
	wxString str="";
	str << SLD->nombre << _("\n");
	str << SLD->entradas->numeroVariables() << _(" inputs, ");
	str << SLD->salidas->numeroVariables() << _(" outputs, ");
	str << SLD->motor->numeroReglas() << _(" rules.");
	staticTextDescripcion->SetLabel(str);

	llenarButton(buttonEntradas,  _("Inputs"));
	llenarButton(buttonSalidas,   _("Outputs"));
	llenarButton(buttonReglas,    _("Rules"));
	llenarButton(buttonInferencia,_("Engine"));
}

void DialogoSLD::llenarButton(wxButton* button, wxString label)
{
  wxBitmap bmp;
  bmp=button->GetBitmap();
	wxMemoryDC dc(bmp);

	int tamPt=10;
	dc.SetFont(wxFont(tamPt,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL));
	wxSize sz=dc.GetTextExtent(label);
	int x,y;
	x=0.5*(bmp.GetWidth() - sz.GetWidth());
	y=bmp.GetHeight()- sz.GetHeight() - 3;
	dc.SetPen(*wxWHITE_PEN);
	dc.SetBrush(*wxWHITE_BRUSH);
	dc.DrawRectangle(0,bmp.GetHeight()-20,bmp.GetWidth(),20);
	dc.DrawText(label,x,y);

	button->SetBitmap(bmp);
}


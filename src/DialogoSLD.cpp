#include "DialogoSLD.h"


BEGIN_EVENT_TABLE(DialogoSLD, wxDialog)
    EVT_CLOSE(DialogoSLD::OnClose)
    EVT_BUTTON(DLG_FRONTAL_SALIR      , DialogoSLD::OnSalir)
    EVT_BUTTON(DLG_FRONTAL_AYUDA      , DialogoSLD::OnAyuda)
    EVT_BUTTON(DLG_FRONTAL_ACERCA     , DialogoSLD::OnAcerca)
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
    EVT_BUTTON(DLG_FRONTAL_ABOUT      , DialogoSLD::OnAbout)
END_EVENT_TABLE()

DialogoSLD::DialogoSLD(wxDialog *dlg, SistemaLogicaDifusa* sld, const wxString &title)
    : wxDialog(dlg, -1, title)
{
	SLD=sld;
    this->SetSizeHints(wxDefaultSize, wxDefaultSize);
    wxFlexGridSizer*  sizerTotal;
    wxFlexGridSizer*  sizerIconos;
    wxBoxSizer*       sizerControles;
    wxGridBagSizer*   sizerSLD;

    sizerTotal      = new wxFlexGridSizer(1,3,0);
    sizerIconos     = new wxFlexGridSizer(11,1,0);
    sizerControles  = new wxBoxSizer(wxHORIZONTAL);
    sizerSLD        = new wxGridBagSizer(0,0);

    staticTextDescripcion = new wxStaticText(this, DLG_FRONTAL_DESCRIPCION, wxT("Descripción:\n"), wxDefaultPosition, wxDefaultSize, 0);
//f4cdb5
    buttonSalir           = new wxButton(this, DLG_FRONTAL_SALIR      , wxT("&Salir")      , wxDefaultPosition, wxDefaultSize, 0);
    buttonAyuda           = new wxButton(this, DLG_FRONTAL_AYUDA      , wxT("A&yuda")      , wxDefaultPosition, wxDefaultSize, 0);
    buttonAcerca          = new wxButton(this, DLG_FRONTAL_ACERCA     , wxT("&Acerca")     , wxDefaultPosition, wxDefaultSize, 0);

    buttonEntradas        = new wxBitmapButton(this, DLG_FRONTAL_ENTRADAS   , wxBitmap("bmp/Entradas.bmp",wxBITMAP_TYPE_BMP));
    buttonSalidas         = new wxBitmapButton(this, DLG_FRONTAL_SALIDAS    , wxBitmap("bmp/Salidas.bmp",wxBITMAP_TYPE_BMP));
    buttonReglas          = new wxBitmapButton(this, DLG_FRONTAL_REGLAS     , wxBitmap("bmp/Reglas.bmp",wxBITMAP_TYPE_BMP));
    buttonInferencia      = new wxBitmapButton(this, DLG_FRONTAL_INFERENCIA , wxBitmap("bmp/Motor.bmp",wxBITMAP_TYPE_BMP));

    buttonNuevo           = new wxBitmapButton(this, DLG_FRONTAL_NUEVO      , wxBitmap("bmp/Nuevo.bmp",wxBITMAP_TYPE_BMP)    ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
    buttonLeer            = new wxBitmapButton(this, DLG_FRONTAL_LEER       , wxBitmap("bmp/Leer.bmp",wxBITMAP_TYPE_BMP)     ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
    buttonGuardar         = new wxBitmapButton(this, DLG_FRONTAL_GUARDAR    , wxBitmap("bmp/Guardar.bmp",wxBITMAP_TYPE_BMP)  ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
    buttonDescripcion     = new wxBitmapButton(this, DLG_FRONTAL_DESCRIPCION, wxBitmap("bmp/Describe.bmp",wxBITMAP_TYPE_BMP) ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
    buttonEntrenar        = new wxBitmapButton(this, DLG_FRONTAL_ENTRENAR   , wxBitmap("bmp/Entrenar.bmp",wxBITMAP_TYPE_BMP) ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
    buttonFuncion         = new wxBitmapButton(this, DLG_FRONTAL_FUNCION    , wxBitmap("bmp/Funcion.bmp",wxBITMAP_TYPE_BMP)  ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
    buttonCalcular        = new wxBitmapButton(this, DLG_FRONTAL_CALCULAR   , wxBitmap("bmp/Calcular.bmp",wxBITMAP_TYPE_BMP) ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
    buttonPasoAPaso       = new wxBitmapButton(this, DLG_FRONTAL_PASOAPASO  , wxBitmap("bmp/Paso.bmp",wxBITMAP_TYPE_BMP)     ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
    buttonCodigo          = new wxBitmapButton(this, DLG_FRONTAL_CODIGO     , wxBitmap("bmp/Codigo.bmp",wxBITMAP_TYPE_BMP)   ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
    buttonTabla           = new wxBitmapButton(this, DLG_FRONTAL_TABLA      , wxBitmap("bmp/Tabla.bmp",wxBITMAP_TYPE_BMP)    ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
    buttonAbout           = new wxBitmapButton(this, DLG_FRONTAL_ABOUT      , wxBitmap("bmp/Acerca.bmp",wxBITMAP_TYPE_BMP)    ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);

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
    sizerIconos->Add(buttonAbout      , 0, wxALL, sepIcon);

    sizerSLD->Add(buttonEntradas  ,wxGBPosition(1,0), wxDefaultSpan, wxALL,0);
    sizerSLD->Add(buttonSalidas   ,wxGBPosition(1,2), wxDefaultSpan, wxALL,0);
    sizerSLD->Add(buttonReglas    ,wxGBPosition(0,1), wxDefaultSpan, wxALL,0);
    sizerSLD->Add(buttonInferencia,wxGBPosition(1,1), wxDefaultSpan, wxALL,0);

    sizerControles->Add(buttonAyuda     , 0, wxALL, 5);
    sizerControles->Add(buttonAcerca    , 0, wxALL, 5);
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
  wxMessageBox(_T("Ayuda"), _T("Ayuda"));
}

void DialogoSLD::OnAcerca(wxCommandEvent &event)
{
  wxMessageBox(_T("Acerca de..."), _T("Acerca de..."));
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
//	*(SLD->salidas)=*(SLD->entradas);
//		return;
	wxMessageDialog* dial;
  dial = new wxMessageDialog(this,_T("Esta acción borra todas las definiciones previas y crea un sistema nuevo. No puede deshacerse. ¿Desea continuar?"),_T("Atención"),wxOK|wxCANCEL|wxCANCEL_DEFAULT);
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
  dial = new wxMessageDialog(this,_T("Esta acción borra todas las definiciones previas y crea un sistema nuevo. No puede deshacerse. ¿Desea continuar?"),_T("Atención"),wxOK|wxCANCEL|wxCANCEL_DEFAULT);
	if(dial->ShowModal() == wxID_OK)
	{
		wxString extensiones="";
		extensiones << _T("Archivos XML (*.xml)|*.xml");
		extensiones << _T("|Archivos UNFUZZY3 (*.unf)|*.unf");

		wxFileDialog dial2(this, _("Sistema de Lógica Difusa"), "", "",extensiones,
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
	extensiones << _T("Archivos XML (*.xml)|*.xml");
	extensiones << _T("|Archivos UNFUZZY3 (*.unf)|*.unf");

	wxFileDialog dial(this, _("Sistema de Lógica Difusa"), "", "",extensiones,
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
	dlg=new DialogoInfo(SLD, this);
	if(dlg->ShowModal() == wxID_OK)
	{
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
	DialogoFuncion *dlg;
	dlg=new DialogoFuncion(SLD,this);
	if(dlg->ShowModal() == wxID_OK)
	{
	}
	delete dlg;
}

void DialogoSLD::OnCalcular   (wxCommandEvent& event)
{
	DialogoCalcular *dlg;
	dlg=new DialogoCalcular(SLD,this);
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
	extensiones << _T("Archivos CPP (*.cpp)|*.cpp");
	extensiones << _T("|Archivos de texto (*.c)|*.c");

	wxFileDialog dial(this, _T("Código fuente generado"), "", "",extensiones,
											wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
  if (dial.ShowModal() == wxID_OK)
	{
		SLD->generarCodigo(dial.GetPath());
	}
}

void DialogoSLD::OnTabla     (wxCommandEvent& event)
{
	wxString extensiones="";
	extensiones << _T("Archivos CSV (*.csv)|*.csv");
	extensiones << _T("|Archivos de texto (*.txt)|*.txt");
	extensiones << _T("|Todos los archivos (*.*)|*.*");

	wxFileDialog dial(this, _("Tabla de datos"), "", "",extensiones,
											wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
  if (dial.ShowModal() == wxID_OK)
	{
		SLD->crearArchivoTabla(dial.GetPath());
	}
}

void DialogoSLD::OnAbout(wxCommandEvent& event)
{
  wxAboutDialogInfo info;
  info.SetName(_T("UNFuzzy"));
  info.SetVersion(_T("3.0.0. Beta"));
  info.SetDescription(_T("Programa de diseño de Sistemas de Lógica Difusa\nUniversidad Nacional de Colombia"));
  info.SetCopyright(_T("(C) 2019 Oscar Duarte <ogduartev@unal.edu.co>"));
  wxAboutBox(info);}

void DialogoSLD::llenarTexto()
{
	wxString str=_T("");
	str << SLD->nombre << _T("\n");
	str << SLD->entradas->numeroVariables() << _T(" entradas, ");
	str << SLD->salidas->numeroVariables() << _T(" salidas, ");
	str << SLD->motor->numeroReglas() << _T(" reglas.");
	staticTextDescripcion->SetLabel(str);
}


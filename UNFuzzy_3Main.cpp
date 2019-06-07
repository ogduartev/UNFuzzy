/***************************************************************
 * Name:      UNFuzzy_3Main.cpp
 * Purpose:   Code for Application Frame
 * Author:    Oscar Duarte (ogduartev@unal.edu.co)
 * Created:   2019-05-20
 * Copyright: Oscar Duarte ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "UNFuzzy_3Main.h"


//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}


BEGIN_EVENT_TABLE(UNFuzzy_3Dialog, wxDialog)
    EVT_CLOSE(UNFuzzy_3Dialog::OnClose)
    EVT_BUTTON(DLG_FRONTAL_SALIR      , UNFuzzy_3Dialog::OnSalir)
    EVT_BUTTON(DLG_FRONTAL_AYUDA      , UNFuzzy_3Dialog::OnAyuda)
    EVT_BUTTON(DLG_FRONTAL_ACERCA     , UNFuzzy_3Dialog::OnAcerca)
    EVT_BUTTON(DLG_FRONTAL_ENTRADAS   , UNFuzzy_3Dialog::OnEntradas)
    EVT_BUTTON(DLG_FRONTAL_SALIDAS    , UNFuzzy_3Dialog::OnSalidas)
    EVT_BUTTON(DLG_FRONTAL_REGLAS     , UNFuzzy_3Dialog::OnReglas)
    EVT_BUTTON(DLG_FRONTAL_INFERENCIA , UNFuzzy_3Dialog::OnInferencia)
    EVT_BUTTON(DLG_FRONTAL_NUEVO      , UNFuzzy_3Dialog::OnNuevo)
    EVT_BUTTON(DLG_FRONTAL_DESCRIPCION, UNFuzzy_3Dialog::OnDescripcion)
    EVT_BUTTON(DLG_FRONTAL_LEER       , UNFuzzy_3Dialog::OnLeer)
    EVT_BUTTON(DLG_FRONTAL_GUARDAR    , UNFuzzy_3Dialog::OnGuardar)
    EVT_BUTTON(DLG_FRONTAL_ENTRENAR   , UNFuzzy_3Dialog::OnEntrenar)
    EVT_BUTTON(DLG_FRONTAL_FUNCION    , UNFuzzy_3Dialog::OnFuncion)
    EVT_BUTTON(DLG_FRONTAL_CALCULAR   , UNFuzzy_3Dialog::OnCalcular)
    EVT_BUTTON(DLG_FRONTAL_PASOAPASO  , UNFuzzy_3Dialog::OnPasoAPaso)
    EVT_BUTTON(DLG_FRONTAL_CODIGO     , UNFuzzy_3Dialog::OnCodigo)
    EVT_BUTTON(DLG_FRONTAL_TABLA      , UNFuzzy_3Dialog::OnTabla)
    EVT_BUTTON(DLG_FRONTAL_ABOUT      , UNFuzzy_3Dialog::OnAbout)
END_EVENT_TABLE()

UNFuzzy_3Dialog::UNFuzzy_3Dialog(wxDialog *dlg, const wxString &title)
    : wxDialog(dlg, -1, title)
{
  	SLD.crearMinimoSLD(3,2);
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

    buttonEntradas        = new wxBitmapButton(this, DLG_FRONTAL_ENTRADAS   , wxBitmap("bmp/Entradas.bmp"));
    buttonSalidas         = new wxBitmapButton(this, DLG_FRONTAL_SALIDAS    , wxBitmap("bmp/Salidas.bmp"));
    buttonReglas          = new wxBitmapButton(this, DLG_FRONTAL_REGLAS     , wxBitmap("bmp/Reglas.bmp"));
    buttonInferencia      = new wxBitmapButton(this, DLG_FRONTAL_INFERENCIA , wxBitmap("bmp/Motor.bmp"));

    buttonNuevo           = new wxBitmapButton(this, DLG_FRONTAL_NUEVO      , wxBitmap("bmp/Nuevo.bmp")    ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
    buttonLeer            = new wxBitmapButton(this, DLG_FRONTAL_LEER       , wxBitmap("bmp/Leer.bmp")     ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
    buttonGuardar         = new wxBitmapButton(this, DLG_FRONTAL_GUARDAR    , wxBitmap("bmp/Guardar.bmp")  ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
    buttonDescripcion     = new wxBitmapButton(this, DLG_FRONTAL_DESCRIPCION, wxBitmap("bmp/Describe.bmp") ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
    buttonEntrenar        = new wxBitmapButton(this, DLG_FRONTAL_ENTRENAR   , wxBitmap("bmp/Entrenar.bmp") ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
    buttonFuncion         = new wxBitmapButton(this, DLG_FRONTAL_FUNCION    , wxBitmap("bmp/Funcion.bmp")  ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
    buttonCalcular        = new wxBitmapButton(this, DLG_FRONTAL_CALCULAR   , wxBitmap("bmp/Calcular.bmp") ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
    buttonPasoAPaso       = new wxBitmapButton(this, DLG_FRONTAL_PASOAPASO  , wxBitmap("bmp/Paso.bmp")     ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
    buttonCodigo          = new wxBitmapButton(this, DLG_FRONTAL_CODIGO     , wxBitmap("bmp/Codigo.bmp")   ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
    buttonTabla           = new wxBitmapButton(this, DLG_FRONTAL_TABLA      , wxBitmap("bmp/Tabla.bmp")    ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
    buttonAbout           = new wxBitmapButton(this, DLG_FRONTAL_ABOUT      , wxBitmap("bmp/Acerca.bmp")    ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);

    staticTextDescripcion->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT , wxNORMAL, wxNORMAL));
    llenarTexto();

    sizerIconos->Add(buttonNuevo      , 0, wxALL, -3);
    sizerIconos->Add(buttonLeer       , 0, wxALL, -3);
    sizerIconos->Add(buttonGuardar    , 0, wxALL, -3);
    sizerIconos->Add(buttonDescripcion, 0, wxALL, -3);
    sizerIconos->Add(buttonEntrenar   , 0, wxALL, -3);
    sizerIconos->Add(buttonFuncion    , 0, wxALL, -3);
    sizerIconos->Add(buttonCalcular   , 0, wxALL, -3);
    sizerIconos->Add(buttonPasoAPaso  , 0, wxALL, -3);
    sizerIconos->Add(buttonCodigo     , 0, wxALL, -3);
    sizerIconos->Add(buttonTabla      , 0, wxALL, -3);
    sizerIconos->Add(buttonAbout      , 0, wxALL, -3);

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


UNFuzzy_3Dialog::~UNFuzzy_3Dialog()
{
}

void UNFuzzy_3Dialog::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void UNFuzzy_3Dialog::OnSalir(wxCommandEvent &event)
{
    Destroy();
}

void UNFuzzy_3Dialog::OnAyuda(wxCommandEvent &event)
{
  wxMessageBox(_T("Ayuda"), _T("Ayuda"));
}

void UNFuzzy_3Dialog::OnAcerca(wxCommandEvent &event)
{
  wxMessageBox(_T("Acerca de..."), _T("Acerca de..."));
}

void UNFuzzy_3Dialog::OnEntradas(wxCommandEvent &event)
{
	DialogoVariable *dlg;
	dlg=new DialogoVariable(SLD.entradas, &SLD, true, this);
	if(dlg->ShowModal() == wxID_OK)
	{
		llenarTexto();
	}
	delete dlg;
}

void UNFuzzy_3Dialog::OnSalidas(wxCommandEvent &event)
{
	DialogoVariable *dlg;
	dlg=new DialogoVariable(SLD.salidas, &SLD, false, this);
	if(dlg->ShowModal() == wxID_OK)
	{
		llenarTexto();
	}
	delete dlg;
}

void UNFuzzy_3Dialog::OnReglas(wxCommandEvent &event)
{
	DialogoReglas *dlg;
	dlg=new DialogoReglas(&SLD, this);
	if(dlg->ShowModal() == wxID_OK)
	{
		llenarTexto();
	}
	delete dlg;
}

void UNFuzzy_3Dialog::OnInferencia(wxCommandEvent &event)
{
	DialogoMotor *dlg;
	dlg=new DialogoMotor(&SLD,this);
	if(dlg->ShowModal() == wxID_OK)
	{
  	llenarTexto();
	}
	delete dlg;
}

void UNFuzzy_3Dialog::OnNuevo      (wxCommandEvent& event)
{
	wxMessageDialog* dial;
  dial = new wxMessageDialog(this,_T("Esta acción borra todas las definiciones previas y crea un sistema nuevo. No puede deshacerse. ¿Desea continuar?"),_T("Atención"),wxOK|wxCANCEL|wxCANCEL_DEFAULT);
	if(dial->ShowModal() == wxID_OK)
	{
  	SLD.crearMinimoSLD(1,1);
  	llenarTexto();
	}
	delete dial;
}


void UNFuzzy_3Dialog::OnLeer       (wxCommandEvent& event)
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
			Archivador Archivo(&SLD);
			Archivo.leer(dial2.GetPath());
		}

  	llenarTexto();
	}
	delete dial;
}

void UNFuzzy_3Dialog::OnGuardar    (wxCommandEvent& event)
{
	wxString extensiones="";
	extensiones << _T("Archivos XML (*.xml)|*.xml");
	extensiones << _T("|Archivos UNFUZZY3 (*.unf)|*.unf");

	wxFileDialog dial(this, _("Sistema de Lógica Difusa"), "", "",extensiones,
											wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
  if (dial.ShowModal() == wxID_OK)
	{
		Archivador Archivo(&SLD);
		Archivo.guardar(dial.GetPath());
	}

}

void UNFuzzy_3Dialog::OnDescripcion(wxCommandEvent& event)
{
	DialogoInfo *dlg;
	dlg=new DialogoInfo(&SLD, this);
	if(dlg->ShowModal() == wxID_OK)
	{
		llenarTexto();
	}
	delete dlg;
}

void UNFuzzy_3Dialog::OnEntrenar   (wxCommandEvent& event)
{
	DialogoEntrenamiento *dlg;
	dlg=new DialogoEntrenamiento(&SLD, this);
	if(dlg->ShowModal() == wxID_OK)
	{
		llenarTexto();
	}
	delete dlg;
}

void UNFuzzy_3Dialog::OnFuncion    (wxCommandEvent& event)
{
	DialogoFuncion *dlg;
	dlg=new DialogoFuncion(&SLD,this);
	if(dlg->ShowModal() == wxID_OK)
	{
	}
	delete dlg;
}

void UNFuzzy_3Dialog::OnCalcular   (wxCommandEvent& event)
{
	DialogoCalcular *dlg;
	dlg=new DialogoCalcular(&SLD,this);
	if(dlg->ShowModal() == wxID_OK)
	{
	}
	delete dlg;
}

void UNFuzzy_3Dialog::OnPasoAPaso (wxCommandEvent& event)
{
	DialogoPaso *dlg;
	dlg=new DialogoPaso(&SLD,this);
	if(dlg->ShowModal() == wxID_OK)
	{
	}
	delete dlg;
}

void UNFuzzy_3Dialog::OnCodigo    (wxCommandEvent& event)
{
	wxString extensiones="";
	extensiones << _T("Archivos CPP (*.cpp)|*.cpp");
	extensiones << _T("|Archivos de texto (*.c)|*.c");

	wxFileDialog dial(this, _T("Código fuente generado"), "", "",extensiones,
											wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
  if (dial.ShowModal() == wxID_OK)
	{
		SLD.generarCodigo(dial.GetPath());
	}
}

void UNFuzzy_3Dialog::OnTabla     (wxCommandEvent& event)
{
	wxString extensiones="";
	extensiones << _T("Archivos CSV (*.csv)|*.csv");
	extensiones << _T("|Archivos de texto (*.txt)|*.txt");
	extensiones << _T("|Todos los archivos (*.*)|*.*");

	wxFileDialog dial(this, _("Tabla de datos"), "", "",extensiones,
											wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
  if (dial.ShowModal() == wxID_OK)
	{
		SLD.crearArchivoTabla(dial.GetPath());
	}
}

void UNFuzzy_3Dialog::OnAbout(wxCommandEvent& event)
{
  wxAboutDialogInfo info;
  info.SetName(_T("UNFuzzy"));
  info.SetVersion(_T("3.0.0. Beta"));
  info.SetDescription(_T("Programa de diseño de Sistemas de Lógica Difusa\nUniversidad Nacional de Colombia"));
  info.SetCopyright(_T("(C) 2019 Oscar Duarte <ogduartev@unal.edu.co>"));
  wxAboutBox(info);}

void UNFuzzy_3Dialog::llenarTexto()
{
	wxString str=_T("");
	str << SLD.nombre << _T("\n");
	str << SLD.entradas->numeroVariables() << _T(" entradas, ");
	str << SLD.salidas->numeroVariables() << _T(" salidas, ");
	str << SLD.motor->numeroReglas() << _T(" reglas.");
	staticTextDescripcion->SetLabel(str);
}


/***************************************************************
 * Name:      UNFuzzyNetworkMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Oscar Duarte (ogduartev@unal.edu.co)
 * Created:   2019-06-09
 * Copyright: Oscar Duarte ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "UNFuzzyNetworkMain.h"

//helper functions

BEGIN_EVENT_TABLE(UNFuzzyNetworkFrame, wxFrame)
		EVT_PAINT(UNFuzzyNetworkFrame::OnPaint)
    EVT_CLOSE(UNFuzzyNetworkFrame::OnClose)
    EVT_LEFT_DOWN(UNFuzzyNetworkFrame::OnMouseLeftDown)
    EVT_LEFT_UP(UNFuzzyNetworkFrame::OnMouseLeftUp)
    EVT_BUTTON(DLG_FRONTALNET_NUEVO      , UNFuzzyNetworkFrame::OnNuevo)
    EVT_BUTTON(DLG_FRONTALNET_DESCRIPCION, UNFuzzyNetworkFrame::OnDescripcion)
    EVT_BUTTON(DLG_FRONTALNET_LEER       , UNFuzzyNetworkFrame::OnLeer)
    EVT_BUTTON(DLG_FRONTALNET_GUARDAR    , UNFuzzyNetworkFrame::OnGuardar)
    EVT_BUTTON(DLG_FRONTALNET_FUNCION    , UNFuzzyNetworkFrame::OnFuncion)
    EVT_BUTTON(DLG_FRONTALNET_CALCULAR   , UNFuzzyNetworkFrame::OnCalcular)
    EVT_BUTTON(DLG_FRONTALNET_CODIGO     , UNFuzzyNetworkFrame::OnCodigo)
    EVT_BUTTON(DLG_FRONTALNET_IDIOMA     , UNFuzzyNetworkFrame::OnIdioma)
    EVT_BUTTON(DLG_FRONTALNET_ABOUT      , UNFuzzyNetworkFrame::OnAbout)
END_EVENT_TABLE()

UNFuzzyNetworkFrame::UNFuzzyNetworkFrame(wxFrame *frame, const wxString& title)
    : wxFrame(frame, -1, title)
{
	flagArrastre=false;
	pinInicioArrastre=NULL;
  capaInicioArrastre=0;

	tamPunto=20;
	tamElimina=8;
  tamIconoPlus=20;
  heightSLD=100;
  widthSLD=200;
  sepXSLD=50;
  sepYSLD=50;
  tamIconoPlus=20;

	wxFileName f(wxStandardPaths::Get().GetExecutablePath());
	wxString strLocale(f.GetPath());
	strLocale << "/locale/";
  MiLocale =new wxLocale(wxLANGUAGE_DEFAULT);
	MiLocale->AddCatalogLookupPathPrefix(strLocale);
	MiLocale->AddCatalog("en");
	setlocale (LC_NUMERIC,"C");

	wxFlexGridSizer*  sizerGrafico;
	wxFlexGridSizer*  sizerIconos;

  buttonNuevo           = new wxBitmapButton(this, DLG_FRONTALNET_NUEVO      , wxMEMORY_BITMAP(nuevo)    ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
  buttonLeer            = new wxBitmapButton(this, DLG_FRONTALNET_LEER       , wxMEMORY_BITMAP(leer)     ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
  buttonGuardar         = new wxBitmapButton(this, DLG_FRONTALNET_GUARDAR    , wxMEMORY_BITMAP(guardar)  ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
  buttonDescripcion     = new wxBitmapButton(this, DLG_FRONTALNET_DESCRIPCION, wxMEMORY_BITMAP(describe) ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
  buttonFuncion         = new wxBitmapButton(this, DLG_FRONTALNET_FUNCION    , wxMEMORY_BITMAP(funcion)  ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
  buttonCalcular        = new wxBitmapButton(this, DLG_FRONTALNET_CALCULAR   , wxMEMORY_BITMAP(calcular) ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
  buttonCodigo          = new wxBitmapButton(this, DLG_FRONTALNET_CODIGO     , wxMEMORY_BITMAP(codigo)   ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
  buttonIdioma          = new wxBitmapButton(this, DLG_FRONTALNET_IDIOMA     , wxMEMORY_BITMAP(vacio)    ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
  buttonAbout           = new wxBitmapButton(this, DLG_FRONTALNET_ABOUT      , wxMEMORY_BITMAP(acerca)   ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);

	staticNombre = new wxStaticText(this,wxID_ANY, Red.nombre);

  sizerTotal      = new wxFlexGridSizer(1,4,0);
  sizerCanvas     = new wxFlexGridSizer(1,1,0);
  sizerGrafico    = new wxFlexGridSizer(1,1,0);
  sizerIconos     = new wxFlexGridSizer(9,1,0);

  int sepIcon=1;
#ifdef __WXGTK__
 	sepIcon=-3;
#endif
  sizerIconos->Add(buttonNuevo      , 0, wxALL, sepIcon);
  sizerIconos->Add(buttonLeer       , 0, wxALL, sepIcon);
  sizerIconos->Add(buttonGuardar    , 0, wxALL, sepIcon);
  sizerIconos->Add(buttonDescripcion, 0, wxALL, sepIcon);
  sizerIconos->Add(buttonFuncion    , 0, wxALL, sepIcon);
  sizerIconos->Add(buttonCalcular   , 0, wxALL, sepIcon);
  sizerIconos->Add(buttonCodigo     , 0, wxALL, sepIcon);
  sizerIconos->Add(buttonIdioma     , 0, wxALL, sepIcon);
  sizerIconos->Add(buttonAbout      , 0, wxALL, sepIcon);

	canvasRed= new wxSizerItem(100,100);

  sizerCanvas->Add(canvasRed);
  sizerGrafico->Add(sizerCanvas    , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 20);

  sizerTotal->Add(sizerIconos      , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 0);
  sizerTotal->Add(staticNombre      , 1, wxALIGN_CENTRE_HORIZONTAL|wxTOP, 15);
  sizerTotal->Add(sizerGrafico     , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 20);

  this->SetSizer(sizerTotal);
  this->Layout();

	crearStatusBar();
	crearSizers();
}

void UNFuzzyNetworkFrame::crearStatusBar()
{
    CreateStatusBar(1);
    SetStatusText(_("Redes de Sistemas de Lógica Difusa"),0);
}

void UNFuzzyNetworkFrame::crearSizers()
{

  int W=Red.capas()->GetItemsInContainer()*(sepYSLD + widthSLD);
  int H=0;
  for(int i=0;i<Red.capas()->GetItemsInContainer();i++)
	{
	  int h;
	  h=Red.capas()->dato(i)->nodos()->GetItemsInContainer()*(sepXSLD + heightSLD);
	  if(h>H)
		{
			H=h;
		}
	}
	W+=tamIconoPlus*2;
	H+=tamIconoPlus*3/2;
	if(W < tamIconoPlus*2){W=tamIconoPlus*2;}
	if(H < tamIconoPlus*2){H=tamIconoPlus*2;}

	canvasRed->SetMinSize(W,H);
  sizerTotal->Fit(this);
}

UNFuzzyNetworkFrame::~UNFuzzyNetworkFrame()
{
}

void UNFuzzyNetworkFrame::OnNuevo     (wxCommandEvent& event)
{
	wxMessageDialog* dial;
  dial = new wxMessageDialog(this,_("Esta acción borra todas las definiciones previas y crea un sistema nuevo. No puede deshacerse. ¿Desea continuar?"),_("Atención"),wxOK|wxCANCEL|wxCANCEL_DEFAULT);
	if(dial->ShowModal() == wxID_OK)
	{
  	Red.crearRedMinima();
  	Refresh();
	}
	delete dial;
}

void UNFuzzyNetworkFrame::OnDescripcion(wxCommandEvent& event)
{
	DialogoInfo *dlg;
	dlg=new DialogoInfo(&Red.nombre,&Red.descripcion, this);
	if(dlg->ShowModal() == wxID_OK)
	{
		staticNombre->SetLabel(Red.nombre);
	}
	delete dlg;

}

void UNFuzzyNetworkFrame::OnLeer      (wxCommandEvent& event)
{
	wxMessageDialog* dial;
  dial = new wxMessageDialog(this,_("Esta acción borra todas las definiciones previas y crea un sistema nuevo. No puede deshacerse. ¿Desea continuar?"),_("Atención"),wxOK|wxCANCEL|wxCANCEL_DEFAULT);
	if(dial->ShowModal() == wxID_OK)
	{
		wxString extensiones="";
		extensiones << _("Archivos UNFuzzyNetwork (*.unn)|*.unn");

		wxFileDialog dial2(this, _("Sistema de Lógica Difusa"), "", "",extensiones,
												wxFD_OPEN|wxFD_FILE_MUST_EXIST);
		if (dial2.ShowModal() == wxID_OK)
		{
			archivadorRed Archivo(&Red);
			Archivo.leer(dial2.GetPath());
		}

  	Refresh();
	}
	delete dial;
}

void UNFuzzyNetworkFrame::OnGuardar   (wxCommandEvent& event)
{
	wxString extensiones="";
	extensiones << _("Archivos UNFuzzyNetwork (*.unn)|*.unn");

	wxFileDialog dial(this, _("Sistema de Lógica Difusa"), "", "",extensiones,
											wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
  if (dial.ShowModal() == wxID_OK)
	{
		archivadorRed Archivo(&Red);
		Archivo.guardar(dial.GetPath());
	}
}

void UNFuzzyNetworkFrame::OnFuncion   (wxCommandEvent& event)
{
	DialogoFuncionRed *dial;
	dial=new DialogoFuncionRed(&Red,this);
	if(dial->ShowModal()==wxID_OK)
	{
	}
	delete dial;
}

void UNFuzzyNetworkFrame::OnCalcular  (wxCommandEvent& event)
{
	DialogoCalculoRed *dial;
	dial=new DialogoCalculoRed(&Red,this);
	if(dial->ShowModal()==wxID_OK)
	{
	}
	delete dial;
}

void UNFuzzyNetworkFrame::OnCodigo    (wxCommandEvent& event)
{
	wxString extensiones="";
	extensiones << _("Archivos CPP (*.cpp)|*.cpp");

	wxFileDialog dial(this, _("Código fuente generado"), "", "",extensiones,
											wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
  if (dial.ShowModal() == wxID_OK)
	{
		wxString nombreClase=_("miRed");  // solo se usa en cpp
		Red.generarCodigo(dial.GetPath(),nombreClase);
	}

}

void UNFuzzyNetworkFrame::OnIdioma    (wxCommandEvent& event)
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
		paintNow();
    SetStatusText(_("Redes de Sistemas de Lógica Difusa"),0);
	}
}

void UNFuzzyNetworkFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void UNFuzzyNetworkFrame::OnAbout(wxCommandEvent &event)
{
  wxAboutDialogInfo info;
  info.SetName(_("UNFuzzyNetwork"));
  info.SetVersion(_("3.0.0. Beta"));
  info.SetDescription(_("Programa de diseño de\nRedes de Sistemas de Lógica Difusa\nUniversidad Nacional de Colombia"));
  info.SetCopyright(_("(C) 2019 Oscar Duarte <ogduartev@unal.edu.co>"));
  wxAboutBox(info);
}

void UNFuzzyNetworkFrame::OnPaint(wxPaintEvent& event)
{
  wxPaintDC dc(this);
  render(dc);
}

void UNFuzzyNetworkFrame::paintNow()
{
  wxClientDC dc(this);
  render(dc);
}

void UNFuzzyNetworkFrame::render(wxDC& dc)
{
	wxBrush brushFondo(*wxTRANSPARENT_BRUSH);
	dc.SetBrush(brushFondo);

	crearSizers();
	pintarNodos(dc);
	pintarEnlaces(dc);
	pintarIconosPlus(dc);
}

void UNFuzzyNetworkFrame::pintarNodos(wxDC& dc)
{
	delete botonesSLD;
  botonesSLD= new wxRect**[Red.capas()->GetItemsInContainer()];
  for(int i=0;i<Red.capas()->GetItemsInContainer();i++)
	{
		botonesSLD[i]= new wxRect*[Red.capas()->dato(i)->nodos()->GetItemsInContainer()];
	}

	wxRect canvas=canvasRed->GetRect();
	dc.DrawRectangle(canvas);
	canvas.SetHeight(canvas.GetHeight() - tamIconoPlus*3/2);

	graficadorRed Grafica(&dc,canvas);
	Grafica.tamPunto=tamPunto;
	Grafica.tamElimina=tamElimina;
	Grafica.tamIconoPlus=tamIconoPlus;

  for(int i=0;i<Red.capas()->GetItemsInContainer();i++)
	{
		for(int j=0;j<Red.capas()->dato(i)->nodos()->GetItemsInContainer();j++)
		{
			int N=Red.capas()->dato(i)->nodos()->GetItemsInContainer();
			int sepY= (canvas.GetHeight() - N*heightSLD)/N;
			int xo,yo;
			xo=canvas.GetLeftTop().x + sepXSLD/2 + i*(widthSLD+sepXSLD);
			yo=canvas.GetLeftTop().y + sepY/2 + j*(heightSLD+sepY);
			wxRect* canvasSLD=new wxRect(xo,yo,widthSLD,heightSLD);
			botonesSLD[i][j]=canvasSLD;
			Grafica.pintarNodo(Red.capas()->dato(i)->nodos()->dato(j),*canvasSLD);
		}
	}
}

void UNFuzzyNetworkFrame::pintarEnlaces(wxDC& dc)
{
	wxRect canvas=canvasRed->GetRect();
	graficadorRed Grafica(&dc,canvas);
	Grafica.heightSLD=heightSLD;
	Grafica.widthSLD=widthSLD;
	Grafica.pintarEnlaces(&Red,botonesSLD);
	return;
}

void UNFuzzyNetworkFrame::pintarIconosPlus(wxDC& dc)
{
	wxRect canvas=canvasRed->GetRect();
	graficadorRed Grafica(&dc,canvas);
	Grafica.widthSLD=widthSLD;
	Grafica.sepXSLD=sepXSLD;
	Grafica.tamIconoPlus=tamIconoPlus;
	Grafica.pintarIconosPlus(&Red);
	return;
}

void UNFuzzyNetworkFrame::OnMouseLeftDown(wxMouseEvent& event)
{
	wxPoint punto(event.GetX(),event.GetY());

	if(buscarPuntosEnEliminarNodo(punto))
	{
		Refresh();
		return;
	}
	if(buscarPuntosEnPinEntrada(punto))
	{
		return;
	}
	if(buscarPuntosEnPinSalidaDown(punto))
	{
		return;
	}
	if(buscarPuntosEnSLD(punto))
	{
		Refresh();
		return;
	}
	if(buscarPuntosEnEliminarCapa(punto))
	{
		Refresh();
		return;
	}
	if(buscarPuntosEnAdicionarNodo(punto))
	{
		Refresh();
		return;
	}
	if(buscarPuntosEnAdicionarCapa(punto))
	{
		Refresh();
		return;
	}
}


void UNFuzzyNetworkFrame::OnMouseLeftUp(wxMouseEvent& event)
{
	if(!flagArrastre or !pinInicioArrastre)
	{
		wxSetCursor(wxCursor(*wxSTANDARD_CURSOR));
		return;
	}

	wxPoint punto(event.GetX(),event.GetY());

	if(buscarPuntosEnPinSalidaUp(punto))
	{
		Refresh();
	}
	wxSetCursor(wxCursor(*wxSTANDARD_CURSOR));
	pinInicioArrastre=NULL;
	flagArrastre=false;
}

bool UNFuzzyNetworkFrame::buscarPuntosEnPinEntrada(wxPoint punto)
{
  for(int numCapa=0;numCapa < Red.capas()->GetItemsInContainer();numCapa++)
	{
		for(int numNodo=0;numNodo < Red.capas()->dato(numCapa)->nodos()->GetItemsInContainer();numNodo++)
		{
			wxPoint pt;
			pt.x=botonesSLD[numCapa][numNodo]->GetTopLeft().x;
			pt.y=botonesSLD[numCapa][numNodo]->GetTopLeft().y;

			nodo* Nodo=Red.ptrNodo( numCapa, numNodo);

			int numEntradas=Nodo->sld()->entradas->numeroVariables();
			float offset;

			offset=(float)(heightSLD)/(float)numEntradas;
			for(int i=0;i<numEntradas;i++)
			{
				int xo=pt.x;
				int yo=pt.y + offset/2 + offset*i-tamPunto/2;
				wxRect canvasPin(xo,yo,tamPunto,tamPunto);
				if(canvasPin.Contains(punto))
				{
					if(numCapa==0)
					{
						datoEntrada(numNodo, i);
						return true;
					}else
					{
						capaInicioArrastre=numCapa;
						pinInicioArrastre=Red.ptrPinEntrada(numCapa, numNodo, i);
						flagArrastre=true;
						wxSetCursor(wxCursor(*wxCROSS_CURSOR));
					}
					return true;
				}
			}
		}
	}
	return false;
}

bool UNFuzzyNetworkFrame::buscarPuntosEnPinSalidaUp(wxPoint punto)
{
	for(int numCapa=0;numCapa <=capaInicioArrastre-1;numCapa++)
  {
	for(int numNodo=0;numNodo < Red.capas()->dato(numCapa)->nodos()->GetItemsInContainer();numNodo++)
	{
		wxPoint pt;
		pt.x=botonesSLD[numCapa][numNodo]->GetTopLeft().x;
		pt.y=botonesSLD[numCapa][numNodo]->GetTopLeft().y;

		nodo* Nodo=Red.ptrNodo( numCapa, numNodo);

		int numSalidas =Nodo->sld()->salidas->numeroVariables();
		float offset;

		offset=(float)(heightSLD)/(float)numSalidas;
		for(int i=0;i<numSalidas;i++)
		{
			int xo=pt.x + widthSLD -tamPunto;
			int yo=pt.y + offset/2 + offset*i-tamPunto/2;
			wxRect canvasPin(xo,yo,tamPunto,tamPunto);
			if(canvasPin.Contains(punto))
			{
				pin* pinFinArrastre;
				pinFinArrastre=Red.ptrPinSalida(numCapa, numNodo, i);
				if(pinFinArrastre)
				{
					pinInicioArrastre->contacto(pinFinArrastre);
				}
				capaInicioArrastre=0;
				return true;
			}
		}
	}
  }
	capaInicioArrastre=0;

	return false;
}

bool UNFuzzyNetworkFrame::buscarPuntosEnPinSalidaDown(wxPoint punto)
{
	for(int numCapa=0; numCapa < Red.capas()->GetItemsInContainer();numCapa++)
	{
		for(int numNodo=0;numNodo < Red.capas()->dato(numCapa)->nodos()->GetItemsInContainer();numNodo++)
		{
			wxPoint pt;
			pt.x=botonesSLD[numCapa][numNodo]->GetTopLeft().x;
			pt.y=botonesSLD[numCapa][numNodo]->GetTopLeft().y;

			nodo* Nodo=Red.ptrNodo( numCapa, numNodo);

			int numEntradas=Nodo->sld()->entradas->numeroVariables();
			int numSalidas =Nodo->sld()->salidas->numeroVariables();
			float offset;

			offset=(float)(heightSLD)/(float)numSalidas;
			for(int i=0;i<numSalidas;i++)
			{
				int xo=pt.x + widthSLD -tamPunto;
				int yo=pt.y + offset/2 + offset*i-tamPunto/2;
				wxRect canvasPin(xo,yo,tamPunto,tamPunto);
				if(canvasPin.Contains(punto))
				{
					pin *Pin=Red.ptrPinSalida(numCapa, numNodo, i);
					wxString str=_("El valor de la variable ");
					str << Red.ptrNodo(numCapa, numNodo)->sld()->nombreVariableSalida(i);
					str << _(" (") << Red.ptrNodo(numCapa, numNodo)->sld()->nombre << _(") es : ");
					str << Pin->valor();
					wxMessageBox(str, "");

					return true;
				}
			}
		}
	}
	capaInicioArrastre=0;

	return false;
}


bool UNFuzzyNetworkFrame::buscarPuntosEnSLD(wxPoint punto)
{
  for(int numCapa=0;numCapa<Red.capas()->GetItemsInContainer();numCapa++)
	{
		for(int numNodo=0;numNodo<Red.capas()->dato(numCapa)->nodos()->GetItemsInContainer();numNodo++)
		{
			wxRect canvasSLD=*botonesSLD[numCapa][numNodo];
			if(canvasSLD.Contains(punto))
			{
				nodo* Nodo;
				Nodo=Red.ptrNodo(numCapa, numNodo);
				editarSLD(Nodo->sld());
				Nodo->ajustarPinesAsld();
				return true;
			}
		}
	}
	return false;
}


bool UNFuzzyNetworkFrame::buscarPuntosEnEliminarNodo(wxPoint punto)
{
  for(int numCapa=0;numCapa<Red.capas()->GetItemsInContainer();numCapa++)
	{
		for(int numNodo=0;numNodo<Red.capas()->dato(numCapa)->nodos()->GetItemsInContainer();numNodo++)
		{
			wxRect canvasSLD=*botonesSLD[numCapa][numNodo];
			wxRect elimina(canvasSLD.GetTopRight().x - tamElimina + 1, canvasSLD.GetTopRight().y, tamElimina, tamElimina);

			if(elimina.Contains(punto))
			{
				eliminarNodo(numCapa,numNodo);
				return true;
			}
		}
	}
	return false;
}

bool UNFuzzyNetworkFrame::buscarPuntosEnEliminarCapa(wxPoint punto)
{
  for(int numCapa=0;numCapa < Red.capas()->GetItemsInContainer(); numCapa++)
	{
		int Xo=canvasRed->GetRect().GetLeftBottom().x + sepXSLD/2 + numCapa*(widthSLD+sepXSLD) + widthSLD/2;
		int Yo=canvasRed->GetRect().GetLeftBottom().y - tamIconoPlus*3/2;
		int xo,yo;
		yo=Yo;
		xo=Xo - tamIconoPlus*3/2;
		wxRect icono(xo,yo,tamIconoPlus,tamIconoPlus);
		if(icono.Contains(punto))
		{
			eliminarCapa(numCapa);
			return true;
		}
	}
	return false;
}

bool UNFuzzyNetworkFrame::buscarPuntosEnAdicionarNodo(wxPoint punto)
{
  for(int numCapa=0;numCapa < Red.capas()->GetItemsInContainer(); numCapa++)
	{
		int Xo=canvasRed->GetRect().GetLeftBottom().x + sepXSLD/2 + numCapa*(widthSLD+sepXSLD) + widthSLD/2;
		int Yo=canvasRed->GetRect().GetLeftBottom().y - tamIconoPlus*3/2;
		int xo,yo;
		yo=Yo;
		xo=Xo + tamIconoPlus*1/2 ;
		wxRect icono(xo,yo,tamIconoPlus,tamIconoPlus);
		if(icono.Contains(punto))
		{
			Red.adicionarNodo(numCapa);
			return true;
		}
	}
	return false;
}

bool UNFuzzyNetworkFrame::buscarPuntosEnAdicionarCapa(wxPoint punto)
{
	int xo=canvasRed->GetRect().GetRightBottom().x - tamIconoPlus*3/2;
	int yo=canvasRed->GetRect().GetLeftBottom().y - tamIconoPlus*3/2;
	wxRect icono(xo,yo,tamIconoPlus,tamIconoPlus);
	if(icono.Contains(punto))
	{
		Red.adicionarCapa();
		return true;
	}
	return false;
}


void UNFuzzyNetworkFrame::editarSLD(SistemaLogicaDifusa* SLD)
{
	DialogoSLD *dial;
	dial=new DialogoSLD(this,SLD,false,_("Edición del Sistema de Lógica Difusa"));
	if(dial->ShowModal()==wxID_OK)
	{
	}
}

void UNFuzzyNetworkFrame::eliminarNodo(int numCapa,int numNodo)
{
	wxMessageDialog* dial;
  dial = new wxMessageDialog(this,_("¿Desea eliminar el nodo?"),_("Atención"),wxOK|wxCANCEL|wxCANCEL_DEFAULT);
	if(dial->ShowModal() == wxID_OK)
	{
		Red.eliminarNodo(numCapa,numNodo);
	}
	delete dial;
}

void UNFuzzyNetworkFrame::eliminarCapa(int numCapa)
{
	wxMessageDialog* dial;
  dial = new wxMessageDialog(this,_("¿Desea eliminar la capa?"),_("Atención"),wxOK|wxCANCEL|wxCANCEL_DEFAULT);
	if(dial->ShowModal() == wxID_OK)
	{
		Red.eliminarCapa(numCapa);
	}
	delete dial;
}

void UNFuzzyNetworkFrame::datoEntrada(int numNodo, int numPin)
{
	int numCapa=0;
	wxString str=_("Ingrese el valor de la variable ");
	str << Red.ptrNodo(numCapa, numNodo)->sld()->nombreVariableEntrada(numPin);
	str << _(" (") << Red.ptrNodo(numCapa, numNodo)->sld()->nombre << _("). ");
	str << _("Debe estar entre ");
	str << Red.ptrNodo(numCapa, numNodo)->sld()->variableEntrada(numPin)->rangoMinimo();
	str << _(" y ");
	str << Red.ptrNodo(numCapa, numNodo)->sld()->variableEntrada(numPin)->rangoMaximo();
	str << _(" : ");
	wxTextEntryDialog *dial;
	float val;
	val=Red.ptrPinEntrada(numCapa, numNodo, numPin)->valor();
	dial=new wxTextEntryDialog(this, str, _("Atención"), wxString::Format("%f",val));
	if(dial->ShowModal()==wxID_OK)
	{
		wxString strValue=dial->GetValue();
		double valD;
		strValue.ToDouble(&valD);
		val=(float)valD;
		if(val < Red.ptrNodo(numCapa, numNodo)->sld()->variableEntrada(numPin)->rangoMinimo())
		{
			val=Red.ptrNodo(numCapa, numNodo)->sld()->variableEntrada(numPin)->rangoMinimo();
		}
		if(val > Red.ptrNodo(numCapa, numNodo)->sld()->variableEntrada(numPin)->rangoMaximo())
		{
			val=Red.ptrNodo(numCapa, numNodo)->sld()->variableEntrada(numPin)->rangoMaximo();
		}
		Red.ptrPinEntrada(numCapa, numNodo, numPin)->valor(val);
		Red.calcularRed();
	}
	delete dial;
}


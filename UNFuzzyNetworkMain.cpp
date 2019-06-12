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
//    EVT_MENU(idMenuQuit, UNFuzzyNetworkFrame::OnQuit)
//    EVT_MENU(idMenuAbout, UNFuzzyNetworkFrame::OnAbout)
    EVT_LEFT_DOWN(UNFuzzyNetworkFrame::OnMouseLeftDown)
    EVT_LEFT_UP(UNFuzzyNetworkFrame::OnMouseLeftUp)
    EVT_BUTTON(DLG_FRONTALNET_NUEVO      , UNFuzzyNetworkFrame::OnNuevo)
    EVT_BUTTON(DLG_FRONTALNET_DESCRIPCION, UNFuzzyNetworkFrame::OnDescripcion)
    EVT_BUTTON(DLG_FRONTALNET_LEER       , UNFuzzyNetworkFrame::OnLeer)
    EVT_BUTTON(DLG_FRONTALNET_GUARDAR    , UNFuzzyNetworkFrame::OnGuardar)
    EVT_BUTTON(DLG_FRONTALNET_FUNCION    , UNFuzzyNetworkFrame::OnFuncion)
    EVT_BUTTON(DLG_FRONTALNET_CALCULAR   , UNFuzzyNetworkFrame::OnCalcular)
    EVT_BUTTON(DLG_FRONTALNET_CODIGO     , UNFuzzyNetworkFrame::OnCodigo)
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

  buttonNuevo           = new wxBitmapButton(this, DLG_FRONTALNET_NUEVO      , wxBitmap("bmp/Nuevo.bmp",wxBITMAP_TYPE_BMP)    ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
  buttonLeer            = new wxBitmapButton(this, DLG_FRONTALNET_LEER       , wxBitmap("bmp/Leer.bmp",wxBITMAP_TYPE_BMP)     ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
  buttonGuardar         = new wxBitmapButton(this, DLG_FRONTALNET_GUARDAR    , wxBitmap("bmp/Guardar.bmp",wxBITMAP_TYPE_BMP)  ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
  buttonDescripcion     = new wxBitmapButton(this, DLG_FRONTALNET_DESCRIPCION, wxBitmap("bmp/Describe.bmp",wxBITMAP_TYPE_BMP) ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
  buttonFuncion         = new wxBitmapButton(this, DLG_FRONTALNET_FUNCION    , wxBitmap("bmp/Funcion.bmp",wxBITMAP_TYPE_BMP)  ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
  buttonCalcular        = new wxBitmapButton(this, DLG_FRONTALNET_CALCULAR   , wxBitmap("bmp/Calcular.bmp",wxBITMAP_TYPE_BMP) ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
  buttonCodigo          = new wxBitmapButton(this, DLG_FRONTALNET_CODIGO     , wxBitmap("bmp/Codigo.bmp",wxBITMAP_TYPE_BMP)   ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
  buttonAbout           = new wxBitmapButton(this, DLG_FRONTALNET_ABOUT      , wxBitmap("bmp/Acerca.bmp",wxBITMAP_TYPE_BMP)    ,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);

	staticNombre = new wxStaticText(this,wxID_ANY, Red.nombre);

//	crearMenu();
	crearStatusBar();
	crearSizers();
}

/*
void UNFuzzyNetworkFrame::crearMenu()
{
    wxMenuBar* mbar = new wxMenuBar();
    wxMenu* fileMenu = new wxMenu(_T(""));
    fileMenu->Append(idMenuQuit, _T("&Quit\tAlt-F4"), _T("Quit the application"));
    mbar->Append(fileMenu, _T("&File"));

    wxMenu* helpMenu = new wxMenu(_T(""));
    helpMenu->Append(idMenuAbout, _T("&About\tF1"), _T("Show info about this application"));
    mbar->Append(helpMenu, _T("&Help"));

    SetMenuBar(mbar);
}*/

void UNFuzzyNetworkFrame::crearStatusBar()
{
    CreateStatusBar(1);
    SetStatusText(_T("Redes de Sistemas de Lógica Difusa"),0);
}

void UNFuzzyNetworkFrame::crearSizers()
{
  wxFlexGridSizer*  sizerTotal;
	wxFlexGridSizer*  sizerCanvas;
	wxFlexGridSizer*  sizerGrafico;
	wxFlexGridSizer*  sizerIconos;

  sizerTotal      = new wxFlexGridSizer(1,4,0);
  sizerCanvas     = new wxFlexGridSizer(1,1,0);
  sizerGrafico    = new wxFlexGridSizer(1,1,0);

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

  int sepIcon=1;
#ifdef __WXGTK__
 	sepIcon=-3;
#endif

  sizerIconos = new wxFlexGridSizer(8,1,0);

  sizerIconos->Add(buttonNuevo      , 0, wxALL, sepIcon);
  sizerIconos->Add(buttonLeer       , 0, wxALL, sepIcon);
  sizerIconos->Add(buttonGuardar    , 0, wxALL, sepIcon);
  sizerIconos->Add(buttonDescripcion, 0, wxALL, sepIcon);
  sizerIconos->Add(buttonFuncion    , 0, wxALL, sepIcon);
  sizerIconos->Add(buttonCalcular   , 0, wxALL, sepIcon);
  sizerIconos->Add(buttonCodigo     , 0, wxALL, sepIcon);
  sizerIconos->Add(buttonAbout      , 0, wxALL, sepIcon);

	canvasRed= new wxSizerItem(W,H);

  sizerCanvas->Add(canvasRed);
  sizerGrafico->Add(sizerCanvas    , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 20);

  sizerTotal->Add(sizerIconos      , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 0);
  sizerTotal->Add(staticNombre      , 1, wxALIGN_CENTRE_HORIZONTAL|wxTOP, 15);
  sizerTotal->Add(sizerGrafico     , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 20);

  this->SetSizer(sizerTotal);
  this->Layout();
  sizerTotal->Fit(this);
}

UNFuzzyNetworkFrame::~UNFuzzyNetworkFrame()
{
}

void UNFuzzyNetworkFrame::OnNuevo     (wxCommandEvent& event)
{
	wxMessageDialog* dial;
  dial = new wxMessageDialog(this,_T("Esta acción borra todas las definiciones previas y crea un sistema nuevo. No puede deshacerse. ¿Desea continuar?"),_T("Atención"),wxOK|wxCANCEL|wxCANCEL_DEFAULT);
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
	extensiones << _T("Archivos XML (*.xml)|*.xml");
	extensiones << _T("|Archivos UNFUZZY3 (*.unf)|*.unf");

	wxFileDialog dial(this, _("Sistema de Lógica Difusa"), "", "",extensiones,
											wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
  if (dial.ShowModal() == wxID_OK)
	{
		archivadorRed Archivo(&Red);
		Archivo.guardar(dial.GetPath());
	}
}

void UNFuzzyNetworkFrame::OnFuncion   (wxCommandEvent& event){}
void UNFuzzyNetworkFrame::OnCalcular  (wxCommandEvent& event){}
void UNFuzzyNetworkFrame::OnCodigo    (wxCommandEvent& event)
{
	wxString extensiones="";
	extensiones << _T("Archivos CPP (*.cpp)|*.cpp");

	wxFileDialog dial(this, _T("Código fuente generado"), "", "",extensiones,
											wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
  if (dial.ShowModal() == wxID_OK)
	{
		wxString nombreClase=_T("miRed");  // solo se usa en cpp
		Red.generarCodigo(dial.GetPath(),nombreClase);
	}

}

void UNFuzzyNetworkFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

/*
void UNFuzzyNetworkFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}*/

void UNFuzzyNetworkFrame::OnAbout(wxCommandEvent &event)
{
  wxAboutDialogInfo info;
  info.SetName(_T("UNFuzzyNetwork"));
  info.SetVersion(_T("3.0.0. Beta"));
  info.SetDescription(_T("Programa de diseño de\nRedes de Sistemas de Lógica Difusa\nUniversidad Nacional de Colombia"));
  info.SetCopyright(_T("(C) 2019 Oscar Duarte <ogduartev@unal.edu.co>"));
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
			int numSalidas =Nodo->sld()->salidas->numeroVariables();
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
	int numCapa=capaInicioArrastre-1;

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
					wxString str=_T("El valor de la variable ");
					str << Red.ptrNodo(numCapa, numNodo)->sld()->nombreVariableSalida(i);
					str << _T(" (") << Red.ptrNodo(numCapa, numNodo)->sld()->nombre << _T(") es : ");
					str << Pin->valor();
					wxMessageBox(str, _T(""));

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
	dial=new DialogoSLD(this,SLD,_T("Edición del Sistema de Lógica Difusa"));
	if(dial->ShowModal()==wxID_OK)
	{
	}
}

void UNFuzzyNetworkFrame::eliminarNodo(int numCapa,int numNodo)
{
	wxMessageDialog* dial;
  dial = new wxMessageDialog(this,_T("¿Desea eliminar el nodo?"),_T("Atención"),wxOK|wxCANCEL|wxCANCEL_DEFAULT);
	if(dial->ShowModal() == wxID_OK)
	{
		Red.eliminarNodo(numCapa,numNodo);
	}
	delete dial;
}

void UNFuzzyNetworkFrame::eliminarCapa(int numCapa)
{
	wxMessageDialog* dial;
  dial = new wxMessageDialog(this,_T("¿Desea eliminar la capa?"),_T("Atención"),wxOK|wxCANCEL|wxCANCEL_DEFAULT);
	if(dial->ShowModal() == wxID_OK)
	{
		Red.eliminarCapa(numCapa);
	}
	delete dial;
}

void UNFuzzyNetworkFrame::datoEntrada(int numNodo, int numPin)
{
	int numCapa=0;
	wxString str=_T("Ingrese el valor de la variable ");
	str << Red.ptrNodo(numCapa, numNodo)->sld()->nombreVariableEntrada(numPin);
	str << _T(" (") << Red.ptrNodo(numCapa, numNodo)->sld()->nombre << _T("). ");
	str << _T("Debe estar entre ");
	str << Red.ptrNodo(numCapa, numNodo)->sld()->variableEntrada(numPin)->rangoMinimo();
	str << _T(" y ");
	str << Red.ptrNodo(numCapa, numNodo)->sld()->variableEntrada(numPin)->rangoMaximo();
	str << _T(" : ");
	wxTextEntryDialog *dial;
	float val;
	val=Red.ptrPinEntrada(numCapa, numNodo, numPin)->valor();
	dial=new wxTextEntryDialog(this, str, _T("Atención"), wxString::Format("%f",val));
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


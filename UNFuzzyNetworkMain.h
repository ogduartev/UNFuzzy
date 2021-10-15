/***************************************************************
 * Name:      UNFuzzyNetworkMain.h
 * Purpose:   Defines Application Frame
 * Author:    Oscar Duarte (ogduartev@unal.edu.co)
 * Created:   2019-06-09
 * Copyright: Oscar Duarte ()
 * License:
 **************************************************************/

#ifndef UNFUZZYNETWORKMAIN_H
#define UNFUZZYNETWORKMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
		#include <wx/gbsizer.h>
		#include <wx/filefn.h>
		#include <wx/filename.h>
		#include <wx/stdpaths.h>
#endif

#include "UNFuzzyNetworkApp.h"
#include "graficadorRed.h"
#include "red.h"
#include "archivadorRed.h"
#include "bmps.h"

#include "DialogoSLD.h"
#include "DialogoCalculoRed.h"
#include "DialogoFuncionRed.h"

class UNFuzzyNetworkFrame: public wxFrame
{
    public:
        UNFuzzyNetworkFrame(wxFrame *frame, const wxString& title);
        ~UNFuzzyNetworkFrame();

        void OnNuevo     (wxCommandEvent& event);
				void OnDescripcion(wxCommandEvent& event);
        void OnLeer      (wxCommandEvent& event);
        void OnGuardar   (wxCommandEvent& event);
        void OnFuncion   (wxCommandEvent& event);
        void OnCalcular  (wxCommandEvent& event);
				void OnCodigo    (wxCommandEvent& event);
				void OnIdioma     (wxCommandEvent& event);
				void OnAbout     (wxCommandEvent& event);

//        void crearMenu();
        void crearStatusBar();
        void crearSizers();

        void OnClose(wxCloseEvent& event);
//        void OnQuit(wxCommandEvent& event);
//        void OnAbout(wxCommandEvent& event);
        void OnPaint(wxPaintEvent& event);
        void OnMouseLeftDown(wxMouseEvent& event);
        void OnMouseLeftUp(wxMouseEvent& event);
        void OnMouseRightDown(wxMouseEvent& event);

        void paintNow();
        void render(wxDC& dc);
        void pintarNodos(wxDC& dc);
        void pintarEnlaces(wxDC& dc);
        void pintarIconosPlus(wxDC& dc);

        bool buscarPuntosEnPinEntrada(wxPoint punto);
        bool buscarPuntosEnPinSalidaDown (wxPoint punto);
        bool buscarPuntosEnPinSalidaUp (wxPoint punto);
        bool buscarPuntosEnSLD(wxPoint punto);
        bool buscarPuntosEnEliminarNodo(wxPoint punto);
        bool buscarPuntosEnEliminarCapa(wxPoint punto);
        bool buscarPuntosEnAdicionarNodo(wxPoint punto);
        bool buscarPuntosEnAdicionarCapa(wxPoint punto);

        void editarSLD(SistemaLogicaDifusa* SLD);
        void eliminarNodo(int numCapa,int numNodo);
        void eliminarCapa(int numCapa);
        void datoEntrada(int numNodo, int numPin);

        void copiarAlClipboard();

    private:
    	red Red;
    	bool flagArrastre;
    	pin* pinInicioArrastre;
    	int capaInicioArrastre;

    	wxLocale *MiLocale;

			int tamElimina;
    	int tamPunto;
    	int tamIconoPlus;
    	int heightSLD;
    	int widthSLD;
    	int sepXSLD;
    	int sepYSLD;

  		wxSizerItem *canvasRed;

  		wxRect***					botonesSLD;


			wxButton* buttonNuevo;
			wxButton* buttonDescripcion;
			wxButton* buttonLeer;
			wxButton* buttonGuardar;
			wxButton* buttonFuncion;
			wxButton* buttonCalcular;
			wxButton* buttonCodigo;
			wxButton* buttonIdioma;
			wxButton* buttonAbout;
			wxStaticText* staticNombre;

			wxFlexGridSizer*  sizerTotal;
			wxFlexGridSizer*  sizerCanvas;

			DECLARE_EVENT_TABLE()
};

enum
{
  DLG_FRONTALNET_SALIR =1,
  DLG_FRONTALNET_AYUDA,
  DLG_FRONTALNET_ACERCA,
  DLG_FRONTALNET_ENTRADAS,
  DLG_FRONTALNET_SALIDAS,
  DLG_FRONTALNET_REGLAS,
  DLG_FRONTALNET_INFERENCIA,
  DLG_FRONTALNET_NUEVO,
  DLG_FRONTALNET_DESCRIPCION,
  DLG_FRONTALNET_LEER,
  DLG_FRONTALNET_GUARDAR,
  DLG_FRONTALNET_FUNCION,
  DLG_FRONTALNET_CALCULAR,
  DLG_FRONTALNET_CODIGO,
  DLG_FRONTALNET_IDIOMA,
  DLG_FRONTALNET_ABOUT
};
#endif // UNFUZZYNETWORKMAIN_H

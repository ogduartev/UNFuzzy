#ifndef DIALGOSLD_H
#define DIALGOSLD_H

#include <wx/wx.h>

#include "SistemaLogicaDifusa.h"
#include "Archivador.h"

#include <wx/button.h>
#include <wx/statline.h>
#include <wx/gbsizer.h>
#include <wx/aboutdlg.h>

#include "DialogoCalcular.h"
#include "DialogoVariable.h"
#include "DialogoMotor.h"
#include "DialogoReglas.h"
#include "DialogoEntrenamiento.h"
#include "DialogoInfo.h"
#include "DialogoFuncion.h"
#include "DialogoPaso.h"

class DialogoSLD: public wxDialog
{
    public:
        DialogoSLD(wxDialog *dlg, SistemaLogicaDifusa* sld, const wxString& title);
        ~DialogoSLD();

    protected:

        wxStaticText* staticTextDescripcion;

        wxButton* buttonAcerca;
        wxButton* buttonAyuda;
        wxButton* buttonSalir;

        wxButton* buttonEntradas;
        wxButton* buttonSalidas;
        wxButton* buttonReglas;
        wxButton* buttonInferencia;

        wxButton* buttonNuevo;
        wxButton* buttonDescripcion;
        wxButton* buttonLeer;
        wxButton* buttonGuardar;

        wxButton* buttonFuncion;
        wxButton* buttonCalcular;
        wxButton* buttonPasoAPaso;

        wxButton* buttonEntrenar;
        wxButton* buttonCodigo;
        wxButton* buttonTabla;

        wxButton* buttonAbout;

    private:
	    	SistemaLogicaDifusa* SLD;
        void OnClose      (wxCloseEvent&   event);
        void OnSalir      (wxCommandEvent& event);
        void OnAyuda      (wxCommandEvent& event);
        void OnAcerca     (wxCommandEvent& event);

        void OnEntradas  (wxCommandEvent& event);
        void OnSalidas   (wxCommandEvent& event);
        void OnReglas    (wxCommandEvent& event);
        void OnInferencia(wxCommandEvent& event);

        void OnNuevo     (wxCommandEvent& event);
				void OnDescripcion(wxCommandEvent& event);
        void OnLeer      (wxCommandEvent& event);
        void OnGuardar   (wxCommandEvent& event);

        void OnEntrenar  (wxCommandEvent& event);
        void OnFuncion   (wxCommandEvent& event);
        void OnCalcular  (wxCommandEvent& event);
        void OnPasoAPaso (wxCommandEvent& event);

				void OnCodigo    (wxCommandEvent& event);
				void OnTabla     (wxCommandEvent& event);

				void OnAbout     (wxCommandEvent& event);

				void llenarTexto();

        DECLARE_EVENT_TABLE()
};

enum
{
  DLG_FRONTAL_SALIR =1,
  DLG_FRONTAL_AYUDA,
  DLG_FRONTAL_ACERCA,
  DLG_FRONTAL_ENTRADAS,
  DLG_FRONTAL_SALIDAS,
  DLG_FRONTAL_REGLAS,
  DLG_FRONTAL_INFERENCIA,
  DLG_FRONTAL_NUEVO,
  DLG_FRONTAL_DESCRIPCION,
  DLG_FRONTAL_LEER,
  DLG_FRONTAL_GUARDAR,
  DLG_FRONTAL_ENTRENAR,
  DLG_FRONTAL_FUNCION,
  DLG_FRONTAL_CALCULAR,
  DLG_FRONTAL_PASOAPASO,
  DLG_FRONTAL_CODIGO,
  DLG_FRONTAL_TABLA,
  DLG_FRONTAL_ABOUT
};



#endif // DIALGOSLD_H

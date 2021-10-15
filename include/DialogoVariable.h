#ifndef DIALOGOVARIABLE_H
#define DIALOGOVARIABLE_H

#include <iostream>
#include <string>
using namespace std;
#include <wx/wx.h>
#include <wx/clipbrd.h>

#include <SistemaLogicaDifusa.h>
#include <Graficador.h>
#include <DialogoEditarVariable.h>
#include <DialogoAutodefinirVariable.h>
#include <DialogoAsignarEtiquetas.h>

class DialogoVariable : public wxDialog
{
	public:
		DialogoVariable(Universo *u, SistemaLogicaDifusa *sld, bool flagDif, wxWindow *parent);
		virtual ~DialogoVariable();

		void llenarDatos();

		void pintarVariable(int var,int conj);
		void pintarDifusor(int var,int conj);

		void OnClose       (wxCloseEvent&   event);
		void OnOK(wxCommandEvent&   event);
		void OnPaint       (wxPaintEvent& event);
		void OnLeftDown    (wxMouseEvent& event);
		void OnLeftUp      (wxMouseEvent& event);
		void OnRightClick (wxMouseEvent& event);
		void cambiaVariable(wxCommandEvent&   event);
		void cambiaConjunto(wxCommandEvent&   event);
		void cambiaDifusor(wxCommandEvent&   event);
		void cambiaConcresor(wxCommandEvent&   event);
		void copiarAlClipboard(int caso);

		void OnEditarVar      (wxCommandEvent&   event);
		void OnEliminarVar    (wxCommandEvent&   event);
		void OnAdicionarVar   (wxCommandEvent&   event);
		void OnAutodefinirVar (wxCommandEvent&   event);
		void OnEtiquetarVar   (wxCommandEvent&   event);
		void OnEditarCon      (wxCommandEvent&   event);
		void OnEliminarCon    (wxCommandEvent&   event);
		void OnAdicionarCon   (wxCommandEvent&   event);
		void OnTipoCon        (wxCommandEvent&   event);
		void OnSpinIntervalos (wxSpinEvent&   event);
		void OnSpinAncho      (wxSpinDoubleEvent&   event);

		Universo *U;
		BloqueConcrecion *Concreto;
		SistemaLogicaDifusa *SLD;

		bool flagDifusor;
	protected:
	  wxSizerItem *canvasVar;
	  wxSizerItem *canvasDif;
//	  wxStaticText *staticNombreVar;
	  wxStaticText *staticLabelVar;
	  wxStaticText *staticLabelDif;
	  wxStaticText *staticTipoDif;
	  wxStaticText *staticInterDif;
	  wxStaticText *staticAnchoDif;

	  wxListBox *listaVariables;
	  wxListBox *listaConjuntos;

	  wxButton* buttonEditarVar;
	  wxButton* buttonEliminarVar;
	  wxButton* buttonAdicionarVar;
	  wxButton* buttonAutodefinirVar;
	  wxButton* buttonEtiquetarVar;

	  wxButton* buttonEditarCon;
	  wxButton* buttonEliminarCon;
	  wxButton* buttonAdicionarCon;
	  wxComboBox* comboTipoCon;

	  wxComboBox* comboTipoConcresor;
	  wxComboBox* comboTipoDifusor;
	  wxSpinCtrl* spinDifIntervalos;
	  wxSpinCtrlDouble* spinDifAncho;

		int numeroPuntosArrastre;
 		wxPoint puntosArrastre[10];
		int tamArrastre;
		bool flagArrastre;
		int puntoArrastrado;
		int NumVar;
		int NumCon;

		wxButton* buttonOK;
		wxButton* buttonCancel;

		DECLARE_EVENT_TABLE()
	private:
};

enum
{
	DLG_VARIABLE_BMPVAR = 1,
	DLG_VARIABLE_LISTAVAR,
	DLG_VARIABLE_LISTACON,
	DLG_VARIABLE_VAREDITAR,
	DLG_VARIABLE_VARELIMINAR,
	DLG_VARIABLE_VARADICIONAR,
	DLG_VARIABLE_VARAUTODEFINIR,
	DLG_VARIABLE_VARETIQUETAR,
	DLG_VARIABLE_CONEDITAR,
	DLG_VARIABLE_CONELIMINAR,
	DLG_VARIABLE_CONADICIONAR,
	DLG_VARIABLE_CONTIPO,
	DLG_VARIABLE_COMBODIFUSOR,
	DLG_VARIABLE_COMBOCONCRESOR,
	DLG_VARIABLE_SPINDIFINTERVALOS,
	DLG_VARIABLE_SPINDIFANCHO
};
#endif // DIALOGOVARIABLE_H

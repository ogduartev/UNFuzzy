#ifndef DIALOGOPASO_H
#define DIALOGOPASO_H

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/spinctrl.h>
#include <wx/clipbrd.h>

#include <SistemaLogicaDifusa.h>
#include <Graficador.h>

class DialogoPaso : public wxDialog
{
	public:
		DialogoPaso(SistemaLogicaDifusa *sld, wxWindow *parent);
		virtual ~DialogoPaso();

		void OnClose(wxCloseEvent &event);
		void OnOK(wxCommandEvent&   event);
		void OnPaint(wxPaintEvent& event);
		void OnRegla(wxGridEvent& event);
		void OnCambioEntra(wxCommandEvent&   event);
		void OnCambioSale(wxCommandEvent&   event);
		void OnCambioActivas(wxCommandEvent&   event);
		void OnCambioSpinEntra(wxSpinDoubleEvent&   event);
		void OnRightClick (wxMouseEvent& event);

		void calcular();
		void pintar();
		void pintarEntrada();
		void pintarRegla(int reglaInd=-1);
		void pintarSalida();
		void llenarTabla();
		void llenarSalida();
		void copiarAlClipboard(int caso);

	protected:
		SistemaLogicaDifusa *SLD;
		double* sale;
		wxArrayInt reglasActivas;

	  wxStaticText* staticSalida;
		wxSizerItem* canvasVarEntrada;
		wxSizerItem* canvasVarRegla;
		wxSizerItem* canvasVarSalida;
	  wxCheckBox* checkActivas;
		wxGrid *gridTabla;
	  wxChoice* choiceEntradas;
	  wxChoice* choiceSalidas;
	  wxSpinCtrlDouble** valoresEntradas;

		wxButton* buttonOK;
		wxButton* buttonCancel;


		DECLARE_EVENT_TABLE()
	private:
};

enum
{
	DLG_PASO_TABLA=1,
	DLG_PASO_CHOICEENTRA,
	DLG_PASO_CHOICESALE,
	DLG_PASO_CHECKACTIVAS,
	DLG_PASO_SPINENTRA_BASE
};

#endif // DIALOGOPASO_H

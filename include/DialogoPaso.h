#ifndef DIALOGOPASO_H
#define DIALOGOPASO_H

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/spinctrl.h>

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
		void OnCalcular(wxCommandEvent&   event);
		void OnRegla(wxGridEvent& event);

		void calcular();
		void pintar();
		void pintarEntrada();
		void pintarRegla(int reglaInd=-1);
		void pintarSalida();
		void llenarTabla();
		void llenarSalida();

	protected:
		SistemaLogicaDifusa *SLD;
		float* sale;
		wxArrayInt reglasActivas;

//	  wxStaticText* staticEntradas;
	  wxStaticText* staticSalida;
		wxSizerItem* canvasVarEntrada;
		wxSizerItem* canvasVarRegla;
		wxSizerItem* canvasVarSalida;
		wxGrid *gridTabla;
	  wxChoice* choiceEntradas;
	  wxChoice* choiceSalidas;
	  wxSpinCtrlDouble** valoresEntradas;
		wxButton* buttonCalcular;

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
	DLG_PASO_BTNCALCULAR
};

#endif // DIALOGOPASO_H

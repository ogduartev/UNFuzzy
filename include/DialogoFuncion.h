#ifndef DIALOGOFUNCION_H
#define DIALOGOFUNCION_H

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/colordlg.h>
#include <wx/colourdata.h>

#include <SistemaLogicaDifusa.h>
#include <Graficador.h>


class DialogoFuncion : public wxDialog
{
	public:
		DialogoFuncion(SistemaLogicaDifusa *sld, wxWindow *parent);
		virtual ~DialogoFuncion();
		void iniciar();

		void OnClose       (wxCloseEvent&   event);
		void OnOK(wxCommandEvent&   event);
		void OnPaint       (wxPaintEvent& event);
		void limpiar (wxCommandEvent& event);
		void OnColor (wxCommandEvent& event);

		void crearGrafica();
		void pintar(wxCommandEvent&   event);
		void pintarFuncion(bool flagFondo, bool flagCurva, int numEntra,int numSale);

		virtual int numeroEntradas();
		virtual int numeroSalidas();
		virtual wxString nombreEntrada(int i);
		virtual wxString nombreSalida (int i);
		virtual float rangoMinimoEntrada(int i);
		virtual float rangoMaximoEntrada(int i);
		virtual float rangoMinimoSalida(int i);
		virtual float rangoMaximoSalida(int i);
		virtual void calcular(float* entra, float* sale);


	protected:
		SistemaLogicaDifusa *SLD;
	  Graficador *Grafica;

	  wxSizerItem *canvasFuncion;

	  wxStaticText* staticEntradas;
	  wxStaticText* staticSalidas;
	  wxChoice* choiceEntradas;
	  wxChoice* choiceSalidas;
	  wxSpinCtrlDouble** valoresEntradas;

		wxButton* buttonPintar;
		wxButton* buttonLimpiar;
		wxButton* buttonColor;
		wxButton* buttonOK;
		wxButton* buttonCancel;

		DECLARE_EVENT_TABLE()

	private:
	wxColourData colorData;
};

enum
{
	DLG_FUNCION_CHOICEENTRA = 1,
	DLG_FUNCION_CHOICESALE,
	DLG_FUNCION_BTNPINTAR,
	DLG_FUNCION_BTNLIMPIAR,
	DLG_FUNCION_BTNCOLOR
};

#endif // DIALOGOFUNCION_H

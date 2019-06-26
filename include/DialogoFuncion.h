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
		DialogoFuncion(wxWindow *parent);
		virtual ~DialogoFuncion();
		void iniciar();

		void OnClose       (wxCloseEvent&   event);
		void OnOK(wxCommandEvent&   event);
		void OnPaint       (wxPaintEvent& event);
		void limpiar (wxCommandEvent& event);
		void OnColor (wxCommandEvent& event);

		void crearGrafica();
		void pintar(wxCommandEvent&   event);
		virtual void pintarFuncion(bool flagFondo, bool flagCurva, int numEntra,int numSale)=0;

		virtual int numeroEntradas()=0;
		virtual int numeroSalidas()=0;
		virtual wxString nombreEntrada(int i)=0;
		virtual wxString nombreSalida (int i)=0;
		virtual double rangoMinimoEntrada(int i)=0;
		virtual double rangoMaximoEntrada(int i)=0;
		virtual double rangoMinimoSalida(int i)=0;
		virtual double rangoMaximoSalida(int i)=0;

	protected:
		SistemaLogicaDifusa *SLD;
	  Graficador *Grafica;

		wxColourData colorData;

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

#ifndef DIALOGOCALCULO_H
#define DIALOGOCALCULO_H

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/spinctrl.h>

#include "Arreglo.h"

class DialogoCalculo : public wxDialog
{
	public:
		DialogoCalculo(wxWindow* parent);
		virtual ~DialogoCalculo();

		void iniciar();
		virtual int numeroEntradas()=0;
		virtual int numeroSalidas()=0;
		virtual wxString nombreEntrada(int i)=0;
		virtual wxString nombreSalida (int i)=0;
		virtual float rangoMinimoEntrada(int i)=0;
		virtual float rangoMaximoEntrada(int i)=0;
		virtual void calcular(float* entra, float* sale)=0;


		void OnClose      (wxCloseEvent&   event);
		void OnOK         (wxCommandEvent&   event);
   	void OnCalcular   (wxCommandEvent&   event);

	protected:
   	typedef Arreglo<wxStaticText> ListaStatic;
   	typedef Arreglo<wxSpinCtrlDouble> ListaEdit;

   	ListaStatic NombresSalidas;
   	ListaEdit		ValoresEntradas;

	  wxSpinCtrlDouble** valoresEntradas;
		wxStaticText**     staticSalidas;
		wxButton*          buttonCalcular;

		wxButton* buttonOK;
		wxButton* buttonCancel;

		DECLARE_EVENT_TABLE()
	private:
};


enum
{
  DLG_CALCULO_CALCULAR =1,
};

#endif // DIALOGOCALCULO_H

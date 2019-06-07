#ifndef DIALOGOCALCULAR_H
#define DIALOGOCALCULAR_H

#include <wx/wx.h>

#include "SistemaLogicaDifusa.h"

class DialogoCalcular : public wxDialog
{
	public:
		DialogoCalcular(SistemaLogicaDifusa *sld, wxWindow *parent);
		virtual ~DialogoCalcular();

	protected:
    SistemaLogicaDifusa *SLD;

   	typedef Arreglo<wxStaticText> ListaStatic;
   	typedef Arreglo<wxTextCtrl> ListaEdit;

   	ListaStatic NombresEntradas;
   	ListaStatic NombresSalidas;
   	ListaEdit		ValoresEntradas;

   	wxButton *buttonCalcular;

		void OnClose      (wxCloseEvent&   event);
		void OnOK(wxCommandEvent&   event);
   	void OnCalcular   (wxCommandEvent&   event);

		wxButton* buttonOK;
		wxButton* buttonCancel;

		DECLARE_EVENT_TABLE()

	private:
};

enum
{
  DLG_CALCULAR_CALCULAR =1,
};

#endif // DIALOGOCALCULAR_H

#ifndef DIALOGOEDITARVARIABLE_H
#define DIALOGOEDITARVARIABLE_H

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <Variable.h>

class DialogoEditarVariable : public wxDialog
{
	public:
		DialogoEditarVariable(Variable *var,wxWindow* parent);
		virtual ~DialogoEditarVariable();

		void llenarDatos();
		void OnClose(wxCloseEvent&   event);
		void OnOK(wxCommandEvent&   event);

		wxString nombre;
		double min_;
		double max_;
		int intervalos;
	protected:
		Variable *Var;
		wxStaticText *staticNombre;
		wxStaticText *staticMinimo;
		wxStaticText *staticMaximo;
		wxStaticText *staticIntervalos;

		wxTextCtrl* textNombre;
		wxTextCtrl* textMinimo;
		wxTextCtrl* textMaximo;
		wxSpinCtrl* spinIntervalos;

		wxButton* buttonOK;
		wxButton* buttonCancel;

		DECLARE_EVENT_TABLE()
	private:
};

enum
{
	DLG_EDITVAR_NOMBRE=1,
	DLG_EDITVAR_MINIMO,
	DLG_EDITVAR_MAXIMO,
	DLG_EDITVAR_INTERVALOS
};

#endif // DIALOGOEDITARVARIABLE_H

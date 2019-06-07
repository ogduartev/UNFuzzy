#ifndef DIALOGOAUTODEFINIRVARIABLE_H
#define DIALOGOAUTODEFINIRVARIABLE_H

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <Variable.h>

class DialogoAutodefinirVariable : public wxDialog
{
	public:
		DialogoAutodefinirVariable(Variable *var,wxWindow* parent);
		virtual ~DialogoAutodefinirVariable();

		void OnClose(wxCloseEvent&   event);
		void OnOK(wxCommandEvent&   event);

		bool flagRectos;
		int numConjuntos;
	protected:
		Variable *Var;

		wxStaticText *staticNumero;
		wxRadioBox *radioForma;
		wxSpinCtrl *spinNumero;

		wxButton* buttonOK;
		wxButton* buttonCancel;

		DECLARE_EVENT_TABLE()
	private:
};

enum
{
	DLG_AUTOVAR_FORMA=1,
	DLG_AUTOVAR_NUMERO
};

#endif // DIALOGOAUTODEFINIRVARIABLE_H

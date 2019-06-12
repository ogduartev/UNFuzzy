#ifndef DIALOGOINFO_H
#define DIALOGOINFO_H

#include <wx/wx.h>
#include "SistemaLogicaDifusa.h"


class DialogoInfo : public wxDialog
{
	public:
		DialogoInfo(wxString *N, wxString *D, wxWindow *parent);
		virtual ~DialogoInfo();
		void OnClose       (wxCloseEvent&   event);
		void OnOK          (wxCommandEvent&   event);

	protected:
		wxString *Nombre;
		wxString *Descripcion;

		wxStaticText*  staticNombre;
		wxStaticText*  staticDescribe;
		wxTextCtrl*    editNombre;
		wxTextCtrl*    editDescribe;

		wxButton* buttonOK;
		wxButton* buttonCancel;

		DECLARE_EVENT_TABLE()

	private:
};

enum
{
	DLG_INFO_NOMBRE = 1,
	DLG_INFO_DESCRIBE
};

#endif // DIALOGOINFO_H

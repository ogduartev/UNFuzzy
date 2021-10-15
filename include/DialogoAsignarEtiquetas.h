#ifndef DIALOGOASIGNARETIQUETAS_H
#define DIALOGOASIGNARETIQUETAS_H

#include <wx/wx.h>
#include <wx/textfile.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>

#include <Variable.h>

class DialogoAsignarEtiquetas : public wxDialog
{
	public:
		DialogoAsignarEtiquetas(Variable *var,wxWindow* parent);
		virtual ~DialogoAsignarEtiquetas();

		void OnClose(wxCloseEvent&   event);
		void OnOK(wxCommandEvent&   event);

		void cargarEtiquetas();
		wxArrayString cargarLinea(wxString linea);

	protected:
		Variable *Var;

		wxListBox* listaEtiquetas;
		wxCheckBox *checkOrden;

		wxButton* buttonOK;
		wxButton* buttonCancel;

		DECLARE_EVENT_TABLE()
	private:
};

enum
{
	DLG_ETIQUETAR_LISTETIQUETAS=1,
	DLG_ETIQUETAR_CHECKORDEN
};
#endif // DIALOGOASIGNARETIQUETAS_H

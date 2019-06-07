#ifndef DIALOGOENTRENAMIENTO_H
#define DIALOGOENTRENAMIENTO_H

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/valnum.h>
#include "SistemaLogicaDifusa.h"

class DialogoEntrenamiento : public wxDialog
{
	public:
		DialogoEntrenamiento(SistemaLogicaDifusa *SLD, wxWindow *parent);
		virtual ~DialogoEntrenamiento();
		void OnClose       (wxCloseEvent&   event);
		void OnOK          (wxCommandEvent&   event);
		void OnInsertar    (wxCommandEvent&   event);
		void OnEliminar    (wxCommandEvent&   event);
		void OnCargar      (wxCommandEvent&   event);
		void OnEntrenar    (wxCommandEvent&   event);

		void llenarTabla();
		void verificarDatos();
		void limpiar(int tipoAlgoritmo);
		void cargarLinea(wxString linea);

	protected:
		MaquinaInferencia *Motor;

		wxGrid *gridTabla;

		wxButton*    buttonInsertar;
		wxButton*    buttonEliminar;
		wxButton*    buttonCargar;
		wxButton*    buttonEntrenar;
		wxCheckBox*  checkLimpiar;
		wxStaticBox* staticAlgoritmo;
		wxChoice*    choiceAlgoritmo;

		wxButton* buttonOK;
		wxButton* buttonCancel;

		DECLARE_EVENT_TABLE()
	private:
};
enum
{
	DLG_ENTRENA_TABLA = 1,
	DLG_ENTRENA_INSERTAR,
	DLG_ENTRENA_ELIMINAR,
	DLG_ENTRENA_CARGAR,
	DLG_ENTRENA_ENTRENAR,
	DLG_ENTRENA_CHECKLIMPIAR,
	DLG_ENTRENA_CHOICEALGORITMO
};

#endif // DIALOGOENTRENAMIENTO_H

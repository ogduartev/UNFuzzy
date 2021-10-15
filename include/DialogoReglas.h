#ifndef DIALOGOREGLAS_H
#define DIALOGOREGLAS_H

#include <wx/wx.h>
#include <wx/grid.h>
#include "SistemaLogicaDifusa.h"

class DialogoReglas : public wxDialog
{
	public:
		DialogoReglas(SistemaLogicaDifusa *SLD, wxWindow *parent);
		virtual ~DialogoReglas();
		void OnClose       (wxCloseEvent&   event);
		void OnOK          (wxCommandEvent&   event);
		void OnCheck2D     (wxCommandEvent&   event);
		void OnCheckCerteza(wxCommandEvent&   event);
		void OnInsertar    (wxCommandEvent&   event);
		void OnEliminar    (wxCommandEvent&   event);
		void OnModificador (wxCommandEvent&   event);
		void OnCerteza     (wxCommandEvent&   event);
		void OnLlenar      (wxCommandEvent&   event);
		void OnRapida      (wxCommandEvent&   event);
		void OnDesocupar   (wxCommandEvent&   event);

		void actualizarBase();

		void llenarTabla();
		void llenarCerteza();

		bool tabla2D();
		void actualizarBase2D();
		void llenarTabla2D();
		void insertar2D();
		void eliminar2D();
		wxGridCellCoordsArray getSelectedCells();

	protected:
		MaquinaInferencia *Motor;
		bool flag2D;
		bool flagCerteza;

		wxGrid *gridTabla;

		wxCheckBox* check2D;
		wxCheckBox* checkCerteza;
		wxButton* buttonInsertar;
		wxButton* buttonEliminar;
		wxButton* buttonModificador;
		wxButton* buttonCerteza;
		wxButton* buttonLlenar;
		wxButton* buttonRapida;
		wxButton* buttonDesocupar;

		wxButton* buttonOK;
		wxButton* buttonCancel;

		DECLARE_EVENT_TABLE()
	private:
};

enum
{
	DLG_REGLAS_TABLA = 1,
	DLG_REGLAS_CHECK2D,
	DLG_REGLAS_CHECKCERTEZA,
	DLG_REGLAS_BTNINSERTAR,
	DLG_REGLAS_BTNELIMINAR,
	DLG_REGLAS_BTNMODIFICADOR,
	DLG_REGLAS_BTNCERTEZA,
	DLG_REGLAS_BTNLLENAR,
	DLG_REGLAS_BTNRAPIDA,
	DLG_REGLAS_BTNDESOCUPAR,
};


#endif // DIALOGOREGLAS_H

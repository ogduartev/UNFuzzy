#ifndef DIALOGOMOTOR_H
#define DIALOGOMOTOR_H

#include <wx/wx.h>
#include "SistemaLogicaDifusa.h"

class DialogoMotor : public wxDialog
{
	public:
		DialogoMotor(SistemaLogicaDifusa *SLD, wxWindow *parent);
		virtual ~DialogoMotor();

		void OnClose          (wxCloseEvent&   event);
		void OnOK             (wxCommandEvent&   event);
		void OnImplicacion    (wxCommandEvent& event);
		void OnMinComposicion (wxCommandEvent& event);
		void OnMaxComposicion (wxCommandEvent& event);
		void OnAnd            (wxCommandEvent& event);
		void OnConjuncion     (wxCommandEvent& event);
		void nuevaImplicacion    ();
		void nuevaMinComposicion ();
		void nuevaMaxComposicion ();
		void nuevaAnd            ();
		void nuevaConjuncion     ();
		Norma *nuevaSNorma(int caso);
		Norma *nuevaTNorma(int caso);
		void getParametro(double *par,double minimo=0,double maximo=10.0);

		void llenarCombos();
		void seleccionarCombos();
		bool verificar();

	protected:
		MaquinaInferencia *Motor;
		BloqueConcrecion *Concreto;

		wxStaticText *staticImplicacion;
		wxStaticText *staticMinComposicion;
		wxStaticText *staticMaxComposicion;
		wxStaticText *staticAnd;
		wxStaticText *staticConjuncion;
		wxComboBox *comboImplicacion;
		wxComboBox *comboMinComposicion;
		wxComboBox *comboMaxComposicion;
		wxComboBox *comboAnd;
		wxComboBox *comboConjuncion;

		wxButton* buttonOK;
		wxButton* buttonCancel;

		DECLARE_EVENT_TABLE()

	private:
};

enum
{
	DLG_MOTOR_IMPLICACION = 1,
	DLG_MOTOR_MINCOMPOSICION,
	DLG_MOTOR_MAXCOMPOSICION,
	DLG_MOTOR_AND,
	DLG_MOTOR_CONJUNCION
};

#endif // DIALOGOMOTOR_H

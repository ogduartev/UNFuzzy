#ifndef DIALOGOMOTOR_H
#define DIALOGOMOTOR_H

#include <wx/wx.h>
#include "SistemaLogicaDifusa.h"

class DialogoMotor : public wxDialog
{
	public:
		DialogoMotor(SistemaLogicaDifusa *SLD, wxWindow *parent);
		virtual ~DialogoMotor();

		void OnClose       (wxCloseEvent&   event);
		void OnOK          (wxCommandEvent&   event);
		void OnImplicacion (wxCommandEvent& event);
		void OnComposicion (wxCommandEvent& event);
		void OnAnd         (wxCommandEvent& event);
		void OnConjuncion  (wxCommandEvent& event);
		void nuevaImplicacion ();
		void nuevaComposicion ();
		void nuevaAnd         ();
		void nuevaConjuncion  ();
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
		wxStaticText *staticComposicion;
		wxStaticText *staticAnd;
		wxStaticText *staticConjuncion;
		wxComboBox *comboImplicacion;
		wxComboBox *comboComposicion;
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
	DLG_MOTOR_COMPOSICION,
	DLG_MOTOR_AND,
	DLG_MOTOR_CONJUNCION
};

#endif // DIALOGOMOTOR_H

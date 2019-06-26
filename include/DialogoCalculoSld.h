#ifndef DIALOGOCALCULOSLD_H
#define DIALOGOCALCULOSLD_H

#include <DialogoCalculo.h>
#include "SistemaLogicaDifusa.h"

class DialogoCalculoSld : public DialogoCalculo
{
	public:
		DialogoCalculoSld(SistemaLogicaDifusa* sld,wxWindow* parent);
		virtual ~DialogoCalculoSld();

		int numeroEntradas();
		int numeroSalidas();
		wxString nombreEntrada(int i);
		wxString nombreSalida (int i);
		double rangoMinimoEntrada(int i);
		double rangoMaximoEntrada(int i);
		void calcular(double* entra, double* sale);

	protected:

	private:
		SistemaLogicaDifusa* SLD;
};

#endif // DIALOGOCALCULOSLD_H

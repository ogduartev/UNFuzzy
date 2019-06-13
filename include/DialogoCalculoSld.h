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
		float rangoMinimoEntrada(int i);
		float rangoMaximoEntrada(int i);
		void calcular(float* entra, float* sale);

	protected:

	private:
		SistemaLogicaDifusa* SLD;
};

#endif // DIALOGOCALCULOSLD_H

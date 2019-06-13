#ifndef DIALOGOCALCULORED_H
#define DIALOGOCALCULORED_H

#include <DialogoCalculo.h>
#include "red.h"

class DialogoCalculoRed : public DialogoCalculo
{
	public:
		DialogoCalculoRed(red* R,wxWindow* parent);
		virtual ~DialogoCalculoRed();

		int numeroEntradas();
		int numeroSalidas();
		wxString nombreEntrada(int i);
		wxString nombreSalida (int i);
		float rangoMinimoEntrada(int i);
		float rangoMaximoEntrada(int i);
		void calcular(float* entra, float* sale);

	protected:

	private:
		red* Red;
};

#endif // DIALOGOCALCULORED_H

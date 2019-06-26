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
		double rangoMinimoEntrada(int i);
		double rangoMaximoEntrada(int i);
		void calcular(double* entra, double* sale);

	protected:

	private:
		red* Red;
};

#endif // DIALOGOCALCULORED_H

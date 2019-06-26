#ifndef DIALOGOFUNCIONRED_H
#define DIALOGOFUNCIONRED_H

#include <DialogoFuncion.h>


class DialogoFuncionRed : public DialogoFuncion
{
	public:
		DialogoFuncionRed(red *r,wxWindow *parent);
		virtual ~DialogoFuncionRed();

		void pintarFuncion(bool flagFondo, bool flagCurva, int numEntra,int numSale);
		int numeroEntradas();
		int numeroSalidas();
		wxString nombreEntrada(int i);
		wxString nombreSalida (int i);
		double rangoMinimoEntrada(int i);
		double rangoMaximoEntrada(int i);
		double rangoMinimoSalida(int i);
		double rangoMaximoSalida(int i);


	protected:
		red* Red;

	private:
};

#endif // DIALOGOFUNCIONRED_H

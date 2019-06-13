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
		float rangoMinimoEntrada(int i);
		float rangoMaximoEntrada(int i);
		float rangoMinimoSalida(int i);
		float rangoMaximoSalida(int i);


	protected:
		red* Red;

	private:
};

#endif // DIALOGOFUNCIONRED_H

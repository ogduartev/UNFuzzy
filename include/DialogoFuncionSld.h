#ifndef DIALOGOFUNCIONSLD_H
#define DIALOGOFUNCIONSLD_H

#include <DialogoFuncion.h>


class DialogoFuncionSld : public DialogoFuncion
{
	public:
		DialogoFuncionSld(SistemaLogicaDifusa *sld,wxWindow *parent);
		virtual ~DialogoFuncionSld();

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
		SistemaLogicaDifusa *SLD;

	private:
};

#endif // DIALOGOFUNCIONSLD_H

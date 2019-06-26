#ifndef NODO_H
#define NODO_H

#include "SistemaLogicaDifusa.h"
#include "pin.h"

typedef Arreglo<pin> ListaPines;

class nodo
{
	public:
		nodo(int numEntradas,int numSalidas);
		virtual ~nodo();
		ListaPines* entradas()
		{
			return &Entradas;
		}
		ListaPines* salidas()
		{
			return &Salidas;
		}
		SistemaLogicaDifusa* sld()
		{
			return &SLD;
		}
		void calcularNodo();
		void actualizarEntradas();
		void calcular(double* entra, double* sale); // =0 para hacer virtual y heredar de SLD
		void ajustarPinesAsld();

	protected:

	private:
  SistemaLogicaDifusa SLD;
	ListaPines Entradas;
	ListaPines Salidas;
};

#endif // NODO_H

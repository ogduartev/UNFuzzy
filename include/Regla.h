#ifndef REGLA_H
#define REGLA_H

typedef int BOOL;

/*///////////////////////////////////////////////
class Regla

atributos:
	int NumeroEntradas;	Número de Variables en el Universo de Entrada
	int NumeroSalidas;	Número de Variables en el Universo de Entrada

	int *Antecedente;
				Vector de NumeroEntrada elementos,
				que hace referencia a los Valores Lingüísticos
				del Antecedente
	int *Consecuente;
				Vector de NumeroSalida elementos,
				que hace referencia a los Valores Lingüísticos
				del Consecuente
	double *Modificadores;
				Vector de NumeroEntrada elementos,
				que hace referencia a los modificadores de los
				Valores Lingüísticos del Antecedente

	double Certeza;		parametro útil para entrenamiento de Sistemas de Lógica Difusa

procedimientos:
	int conjuntoEntrada(int numVar)
			Consultor de Antecedente
	void conjuntoEntrada(int numVar,int numCon)
			Modificador de Antecedente
	int conjuntoSalida(int numVar)
			Consultor de Consecuente
	void conjuntoSalida(int numVar,int numCon)
			Modificador de Consecuente
	double modificador(int numVar)
			Consultor de Modificadores
	void modificador(int numVar,double modif)
			Modificador de Modificadores
	void certeza(double cer)
			Modificador de Certeza
	double certeza()
			Consultor de Certeza
	BOOL operator==(const Regla& other)
		operador definido para poder hacer listas de Reglas
////////////////////////////////////////////////*/

class Regla
{
public:
	Regla(int numEntradas, int numSalidas)
	{
		NumeroEntradas=numEntradas;
		NumeroSalidas=numSalidas;
		Antecedente=new int[numEntradas];
		Consecuente=new int[numSalidas];
		Modificadores=new double[numEntradas];
		for(int i=0;i<NumeroEntradas;i++)
		{
			Antecedente[i]=0;
			Modificadores[i]=1.0;
		}
		for(int i=0;i<NumeroSalidas;i++)
		{
			Consecuente[i]=0;
		}
		Certeza=1.0;
	}
	~Regla()
	{
		delete[] Antecedente;
		delete[] Consecuente;
		delete[] Modificadores;
	}
	int conjuntoEntrada(int numVar)
	{
		return Antecedente[numVar];
	}
	void conjuntoEntrada(int numVar,int numCon)
	{
		Antecedente[numVar]=numCon;
	}
	int conjuntoSalida(int numVar)
	{
		return Consecuente[numVar];
	}
	void conjuntoSalida(int numVar,int numCon)
	{
		Consecuente[numVar]=numCon;
	}
	double modificador(int numVar)
	{
		return Modificadores[numVar];
	}
	void modificador(int numVar,double modif)
	{
		Modificadores[numVar]=modif;
	}
	void certeza(double cer)
	{
		Certeza=cer;
	}
	double certeza()
	{
		return Certeza;
	}
	BOOL operator==(const Regla& other)
	{
		return ( ( Antecedente == other.Antecedente)&
		( Consecuente == other.Consecuente)&
		( Modificadores == other.Modificadores) );
	}
	void adicionarEntrada();
	void adicionarSalida();
	void eliminarEntrada(int NumVar);
	void eliminarSalida(int NumVar);

protected:
	int NumeroEntradas;
	int NumeroSalidas;

	int *Antecedente;
	int *Consecuente;
	double *Modificadores;

	double Certeza;

};


#endif // REGLA_H

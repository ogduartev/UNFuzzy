#ifndef RED_H
#define RED_H

#include <wx/wx.h>
#include "capa.h"

typedef Arreglo<capa> ListaCapas;

class red
{
	public:
		red();
		virtual ~red();
		void crearRedMinima();
		bool conectar(int capa1, int nodo1, int pin1,int capa2, int nodo2, int pin2);
		bool buscarCapa(int numCapa);
		bool buscarNodo(int numCapa, int numNodo);
		bool buscarPinEntrada(int numCapa, int numNodo, int numPin);
		bool buscarPinSalida(int numCapa, int numNodo, int numPin);
		float valorPinEntrada(int numCapa, int numNodo, int numPin);
		float valorPinSalida(int numCapa, int numNodo, int numPin);
		void valorEntrada(int numNodo, int numPin, float Valor);
		nodo* ptrNodo(int numCapa, int numNodo);
		pin* ptrPinEntrada(int numCapa, int numNodo, int numPin);
		pin* ptrPinSalida (int numCapa, int numNodo, int numPin);
		void desconectarSalida(int numCapa, int numNodo, int numPin);
		void desconectarEntradasNodo(int numCapa, int numNodo);
		void desconectarSalidasNodo (int numCapa, int numNodo);
		void eliminarNodo(int numCapa, int numNodo);
		void eliminarCapa(int numCapa);
		void eliminarCapas();
		void adicionarCapa();
		void adicionarNodo(int numCapa);
		bool buscarPinEntrada(pin* Pin, int *numCapa, int *numNodo, int *numPin);
		bool buscarPinSalida(pin* Pin, int *numCapa, int *numNodo, int *numPin);
		int numeroEntradas();
		int numeroSalidas();
		Variable* variableEntrada(int i);
		Variable* variableSalida(int i);
		void asignarEntradas(float* entra);
		void leerSalidas(float* sale);
		void calcular(float* entra, float* sale);
		void calcularRed();

		ListaCapas* capas()
		{
			return &Capas;
		}

		void generarCodigo             (wxString nombreArchivo,wxString nombreClase);
		void generarCodigoCPP          (wxString nombreArchivo,wxString nombreClase);
		void generarCodigoCPPEncabezado(wxTextFile* codigoFile);
		void generarCodigoCPPsld       (wxTextFile* codigoFile);
		void generarCodigoCPPClase     (wxTextFile* codigoFile,wxString nombreClase);
		void generarCodigoCPPMain      (wxTextFile* codigoFile,wxString nombreClase);

		wxString nombre;
		wxString descripcion;

	protected:
	private:

	ListaCapas Capas;
};

#endif // RED_H

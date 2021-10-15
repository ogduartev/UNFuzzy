#ifndef GRAFICADOR_H
#define GRAFICADOR_H

#include <wx/wx.h>
#include <SistemaLogicaDifusa.h>
#include <red.h>


class Graficador
{
	public:
		Graficador(wxClientDC *Dc, wxRect R);
		virtual ~Graficador();

		void calcularRects();
		void pintarMarco();
		void pintarEjes();
		void pintarTitle(wxString strT);
		void pintarLabels(wxString strH, wxString strV);
		void pintarTicks(double mnx, double mxx, double mny, double mxy);

		void pintarVariable(Variable *Var,int numConjunto,bool flagColor=true);
		void pintarDifusor(Variable *Var, bool flagEjes=true);
		void pintarConjunto(Variable *Var,ConjuntoDifuso *C);
		void pintarPuntosArrastre(Variable *Var,ConjuntoDifuso *C);

		void pintarFondoFuncion(double mnx, double mxx, double mny, double mxy, wxString nomEntra, wxString nomSale);
		void pintarCurvaFuncion(double mnx, double mxx, double mny, double mxy,int numSalidas, int numEntra, int numSale, double* entra,wxColour &color);

		void pintarFondoFuncionES(SistemaLogicaDifusa* SLD, int numEntra, int numSale);
		void pintarCurvaFuncionES(SistemaLogicaDifusa* SLD, int numEntra, int numSale, double* entra,wxColour &color);
		void pintarCurvaFuncionES(red* Red, int numEntra, int numSale, double* entra,wxColour &color);
		void pintarComposicion(SistemaLogicaDifusa* SLD, int numSale, int numRegla);
		void pintarConjuncion(SistemaLogicaDifusa* SLD, int numSale,double salida);

		void calcularFuncion(double*entra, double* sale);

		int numeroPuntosArrastre;
		wxPoint puntosArrastre[10];
  	int tamArrastre;
    wxClientDC *dc;

	protected:
    wxRect marco;
    wxRect ejes;
    wxRect canvas;

   	int margenIzq;
		int margenDer;
		int margenSup;
		int margenInf;
		int margenFlecha;
		int tamFlecha;
  	int tickTam;
	  int numDX;
  	int numDY;

		double arrastre[10];
	private:
};

#endif // GRAFICADOR_H

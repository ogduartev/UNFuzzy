#ifndef GRAFICADOR_H
#define GRAFICADOR_H

#include <wx/wx.h>
#include <SistemaLogicaDifusa.h>


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
		void pintarTicks(float mnx, float mxx, float mny, float mxy);
		void pintarVariable(Variable *Var,int numConjunto,bool flagColor=true);
		void pintarDifusor(Variable *Var, bool flagEjes=true);
		void pintarConjunto(Variable *Var,ConjuntoDifuso *C);
		void pintarPuntosArrastre(Variable *Var,ConjuntoDifuso *C);
		void pintarFondoFuncionES(SistemaLogicaDifusa* SLD, int numEntra, int numSale);
		void pintarCurvaFuncionES(SistemaLogicaDifusa* SLD, int numEntra, int numSale, float* entra,wxColour &color);
		void pintarComposicion(SistemaLogicaDifusa* SLD, int numSale, int numRegla);
		void pintarConjuncion(SistemaLogicaDifusa* SLD, int numSale,float salida);

		int numeroPuntosArrastre;
		wxPoint puntosArrastre[10];
  	int tamArrastre;

	protected:
    wxRect marco;
    wxRect ejes;
    wxRect canvas;
    wxClientDC *dc;

   	int margenIzq;
		int margenDer;
		int margenSup;
		int margenInf;
		int margenFlecha;
		int tamFlecha;
  	int tickTam;
	  int numDX;
  	int numDY;

		float arrastre[10];
	private:
};

#endif // GRAFICADOR_H

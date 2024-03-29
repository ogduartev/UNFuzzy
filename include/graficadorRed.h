#ifndef GRAFICADORRED_H
#define GRAFICADORRED_H

#include <wx/filefn.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>

#include "red.h"
#include "bmps.h"

class graficadorRed
{
	public:
		graficadorRed(wxDC *Dc, wxRect R);
		virtual ~graficadorRed();

    void pintarNodo(nodo *Nodo, wxRect canvasSLD);
    void ubicarEnlaces(red *Red, wxRect***	botonesSLD);
    void pintarEnlaces(red *Red, wxRect***	botonesSLD);
    void pintarIconosPlus(red *Red);

   	int tamPunto;
		int tamElimina;
		int tamIconoPlus;
   	int heightSLD;
   	int widthSLD;
   	int sepXSLD;
   	int sepYSLD;

	protected:

	private:
    wxRect marco;
    wxDC *dc;


};

#endif // GRAFICADORRED_H

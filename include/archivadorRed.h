#ifndef ARCHIVADORRED_H
#define ARCHIVADORRED_H

#include <wx/wx.h>
#include <wx/xml/xml.h>

#include "Archivador.h"
#include "red.h"

class archivadorRed
{
	public:
		archivadorRed(red *r);
		virtual ~archivadorRed();

		void guardar(wxString fileName);
		void guardarCapas   (wxXmlNode* parent);
		void guardarCapa    (wxXmlNode* parent, capa *Capa);
		void guardarNodo    (wxXmlNode* parent, nodo *Nodo);
		void guardarSLD     (wxXmlNode* parent, SistemaLogicaDifusa *SLD);
		void guardarEnlaces (wxXmlNode* parent);
		void guardarEnlace  (wxXmlNode* parent,pin* PinEntra, pin* PinSale);

		void leer           (wxString fileName);
		void leerCapas      (wxXmlNode* parent);
		void leerCapa       (wxXmlNode* parent, capa *Capa);
		void leerNodo       (wxXmlNode* parent, nodo *Nodo);
		void leerSLD        (wxXmlNode* parent, SistemaLogicaDifusa *SLD);
		void leerEnlaces    (wxXmlNode* parent);
		void leerEnlace     (wxXmlNode* parent);


	protected:
		red* Red;
		wxXmlDocument doc;

	private:
};

#endif // ARCHIVADORRED_H

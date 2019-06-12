#ifndef ARCHIVADOR_H
#define ARCHIVADOR_H

#include <wx/wx.h>
#include <wx/xml/xml.h>

#include "SistemaLogicaDifusa.h"

class Archivador
{
	public:
		Archivador(SistemaLogicaDifusa* sld);
		virtual ~Archivador();

		void guardar(wxString fileName);
		void guardarSLD        (wxXmlNode* parent);
		void guardarEntradas   (wxXmlNode* parent);
		void guardarSalidas    (wxXmlNode* parent);
		void guardarVariable   (wxXmlNode* parent, Variable *var, bool flagDifusor);
		void guardarDifusor    (wxXmlNode* parent, Difusor *dif);
		void guardarConjunto   (wxXmlNode* parent, ConjuntoDifuso *cd);
		void guardarMaquina    (wxXmlNode* parent);
		void guardarBase       (wxXmlNode* parent);
		void guardarRegla      (wxXmlNode* parent, Regla *regla);
		void guardarAntecedente(wxXmlNode* parent, Regla *regla, int num);
		void guardarConsecuente(wxXmlNode* parent, Regla *regla, int num);
		void guardarNorma      (wxXmlNode* parent, Norma *norma, wxString label);
		void guardarImplicacion(wxXmlNode* parent, Implicacion *imp);
		void guardarConcrecion (wxXmlNode* parent);
		void guardarConcresor  (wxXmlNode* parent, Concresor *conc, int numVar);

		void leer(wxString fileName);
		void leerSLD                   (wxXmlNode* parent);
		void leerEntradas              (wxXmlNode* parent);
		void leerSalidas               (wxXmlNode* parent);
		void leerVariable              (wxXmlNode* parent, Variable *var, bool flagDifusor);
		Difusor*        leerDifusor    (wxXmlNode* parent, Variable *var);
		ConjuntoDifuso* leerConjunto   (wxXmlNode* parent, Variable *var);
		void leerMaquina               (wxXmlNode* parent);
		void leerBase                  (wxXmlNode* parent);
		void leerRegla                 (wxXmlNode* parent, Regla *regla);
		Norma* leerNorma							 (wxXmlNode* parent);
		void leerImplicacion           (wxXmlNode* parent);
		void leerConcrecion            (wxXmlNode* parent);
		void leerConcresor             (wxXmlNode* parent);

	protected:
		SistemaLogicaDifusa* SLD;
		wxXmlDocument doc;

	private:
};

#endif // ARCHIVADOR_H

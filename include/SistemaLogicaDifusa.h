#ifndef SISTEMALOGICADIFUSA_H
#define SISTEMALOGICADIFUSA_H

#include <wx/wx.h>
#include <wx/textfile.h>
#include <wx/progdlg.h>
#include <wx/filename.h>

#include <iostream>
#include <string>
using namespace std;

#include "BloqueConcrecion.h"

class SistemaLogicaDifusa
{
public:
	SistemaLogicaDifusa()
	{
		entradas=0;
		salidas=0;
		motor=0;
		concreto=0;
	}
	~SistemaLogicaDifusa()
	{
		delete entradas;
		delete salidas;
		delete motor;
		delete concreto;
	}
	Variable *variableEntrada(int num)
	{
	  Variable* Var=NULL;
	  if(num< numeroEntradas())
		{
		  Var=entradas->variable(num);
		}
	  return Var;
	}
	Variable *variableSalida(int num)
	{
	  Variable* Var=NULL;
	  if(num< numeroSalidas())
		{
		  Var=salidas->variable(num);
		}
	  return Var;
	}
	int numeroEntradas()
	{
		return entradas->numeroVariables();
	}
	int numeroSalidas()
	{
		return salidas->numeroVariables();
	}
	string nombreVariableEntrada(int numVar)
	{
		return entradas->nombreVariable(numVar);
	}
	string nombreVariableSalida(int numVar)
	{
		return salidas->nombreVariable(numVar);
	}
	void calcular(double *entra,double *sale)
	{
		concreto->salidaConcreta(entra,sale);
	}
	MaquinaInferencia *Motor(){return motor;}
	void EntrenaUniversoFijo(double *antecedente, double *consecuente)
	{
		motor->EntrenaUniversoFijo(antecedente,consecuente);
	}
	void EntrenaUniversoVariable(double *antecedente, double *consecuente)
	{
		motor->EntrenaUniversoVariable(antecedente,consecuente);
	}
	void crearMinimoSLD(int numEnt,int numSal);
	wxString crearEncabezadoTabla(wxString nombreArchivo);
	void crearArchivoTabla(wxString nombreArchivo);
	void generarCodigo(wxString nombreArchivo,wxString nombreClase);

	void generarCodigoCPP(wxString nombreArchivo,wxString nombreClase);
	void generarCodigoCPPEncabezado(wxTextFile* codigoFile);
	void generarCodigoCPPClase(wxTextFile* codigoFile,wxString nombreClase);
	void generarCodigoCPPMain(wxTextFile* codigoFile,wxString nombreClase);

	void generarCodigoC(wxString nombreArchivo);
	void generarCodigoCEncabezado(wxTextFile* codigoFile);
	void generarCodigoCDefs(wxTextFile* codigoFile);
	void generarCodigoCMain(wxTextFile* codigoFile);
	void generarCodigoCFunciones(wxTextFile* codigoFile);
	void generarCodigoCSistema(wxTextFile* codigoFile);

//protected:
	Universo *entradas;
	Universo *salidas;
	MaquinaInferencia *motor;
	BloqueConcrecion *concreto;

	string nombre;
	string descripcion;
};

#endif // SISTEMALOGICADIFUSA_H

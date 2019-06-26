#ifndef PIN_H
#define PIN_H

#include <wx/wx.h>

class pin
{
	public:
		pin();
		virtual ~pin();
		pin* contacto() const
		{
			return Contacto;
		}
		void contacto(pin* c)
		{
			Contacto=c;
		}
		double valor()
		{
			return Valor;
		}
		void valor(double V)
		{
			Valor=V;
		}

		wxPoint Posicion;
	protected:

	private:
		pin* Contacto;
		double Valor;

};

#endif // PIN_H

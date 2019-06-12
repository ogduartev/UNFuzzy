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
		float valor()
		{
			return Valor;
		}
		void valor(float V)
		{
			Valor=V;
		}

		wxPoint Posicion;
	protected:

	private:
		pin* Contacto;
		float Valor;

};

#endif // PIN_H

#include "Implicacion.h"

string Implicacion::tipo(int caso)
{
	wxString str;
	switch(caso)
	{
		case 0 : str=_("Product"); break;
		case 1 : str=_("Minimum"); break;
		case 2 : str=_("Kleene-Dienes"); break;
		case 3 : str=_("Lukasiewicz"); break;
		case 4 : str=_("Zadeh"); break;
		case 5 : str=_("Stochastic"); break;
		case 6 : str=_("Goguen"); break;
		case 7 : str=_("Godel"); break;
		case 8 : str=_("Sharp"); break;
		default : str=""; break;
	}
	return string(str.mb_str());
}

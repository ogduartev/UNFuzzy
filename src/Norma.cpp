#include "Norma.h"

string Norma::tipo(int caso)
{
	wxString str;
	switch(caso)
	{
		case 0 : str=_("Product"); break;
		case 1 : str=_("Minimum"); break;
		case 2 : str=_("Bounded Product"); break;
		case 3 : str=_("Drastic Product"); break;
		case 4 : str=_("Tp Family"); break;
		case 5 : str=_("Hamacher Family"); break;
		case 6 : str=_("Sugeno Family"); break;  // SNORMA
		case 7 : str=_("Frank Family"); break;
		case 8 : str=_("Yager Family"); break;
		case 9 : str=_("Dubois-Prade Family"); break;
		case 10: str=_("Maximum"); break;  // SNORMA
		case 11: str=_("Bounded Sum"); break;  // SNORMA
		case 12: str=_("Drastic Sum"); break;  // SNORMA
		default : str=""; break;
	}
	return string(str.mb_str());
}

#include "DialogoDifusor.h"

DialogoDifusor::DialogoDifusor(Difusor *dif, wxWindow *parent)
:wxDialog(parent,wxID_ANY,wxString(_("Fuzzyfier design")))
{
	Dif=dif;
}

DialogoDifusor::~DialogoDifusor()
{
	//dtor
}

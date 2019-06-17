#include "DialogoDifusor.h"

DialogoDifusor::DialogoDifusor(Difusor *dif, wxWindow *parent)
:wxDialog(parent,wxID_ANY,wxString(_("Edición del difusor")))
{
	Dif=dif;
}

DialogoDifusor::~DialogoDifusor()
{
	//dtor
}

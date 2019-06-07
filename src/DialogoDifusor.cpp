#include "DialogoDifusor.h"

DialogoDifusor::DialogoDifusor(Difusor *dif, wxWindow *parent)
:wxDialog(parent,wxID_ANY,wxString(wxT("Edición del difusor")))
{
	Dif=dif;
}

DialogoDifusor::~DialogoDifusor()
{
	//dtor
}

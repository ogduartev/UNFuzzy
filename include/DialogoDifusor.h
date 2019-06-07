#ifndef DIALOGODIFUSOR_H
#define DIALOGODIFUSOR_H

#include <wx/wx.h>
#include"Variable.h"

class DialogoDifusor : public wxDialog
{
	public:
		DialogoDifusor(Difusor *dif, wxWindow *parent);
		virtual ~DialogoDifusor();

	protected:
		Difusor *Dif;

	private:
};

#endif // DIALOGODIFUSOR_H

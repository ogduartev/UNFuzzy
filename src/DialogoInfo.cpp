#include "DialogoInfo.h"

BEGIN_EVENT_TABLE(DialogoInfo, wxDialog)
    EVT_CLOSE(DialogoInfo::OnClose)
    EVT_BUTTON(wxID_OK   , DialogoInfo::OnOK)
END_EVENT_TABLE()


DialogoInfo::DialogoInfo(wxString *N, wxString *D, wxWindow *parent)
:wxDialog(parent,wxID_ANY,wxString(wxT("Base de reglas")))
{
	Nombre=N;
	Descripcion=D;

  wxFlexGridSizer* sizerTotal;
  wxFlexGridSizer* sizerControles;
  wxFlexGridSizer* sizerOKCancel;

  sizerTotal       = new wxFlexGridSizer(1,2,0);
  sizerControles   = new wxFlexGridSizer(2,2,0);
  sizerOKCancel    = new wxFlexGridSizer(2,1,0);

  staticNombre     = new wxStaticText(this,wxID_ANY, _T("Nombre:"));
  staticDescribe   = new wxStaticText(this,wxID_ANY, _T("Descripción:"));
  editNombre       = new wxTextCtrl(this,DLG_INFO_NOMBRE  , *Nombre     , wxDefaultPosition, wxSize(200,25));
  editDescribe     = new wxTextCtrl(this,DLG_INFO_DESCRIBE, *Descripcion, wxDefaultPosition, wxSize(200,100), wxTE_MULTILINE);
  buttonOK         = new wxButton(this,wxID_OK,_("OK"));
  buttonCancel     = new wxButton(this,wxID_CANCEL,_("Cancelar"));

  sizerControles->Add(staticNombre   , 1, wxALIGN_RIGHT|wxALL, 5);
  sizerControles->Add(editNombre     , 1, wxALIGN_LEFT|wxALL, 5);
  sizerControles->Add(staticDescribe , 1, wxALIGN_RIGHT|wxALL, 5);
  sizerControles->Add(editDescribe   , 1, wxALIGN_LEFT|wxALL, 5);

	sizerOKCancel->Add(buttonOK, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerOKCancel->Add(buttonCancel, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

  sizerTotal->Add(sizerControles   , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
  sizerTotal->Add(sizerOKCancel    , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

  this->SetSizer(sizerTotal);
  this->Layout();
  sizerTotal->Fit(this);


}

DialogoInfo::~DialogoInfo()
{
	//dtor
}

void DialogoInfo::OnClose       (wxCloseEvent&   event)
{
	EndModal(wxID_OK);
}

void DialogoInfo::OnOK          (wxCommandEvent&   event)
{
	*Nombre      = editNombre->GetValue();
	*Descripcion = editDescribe->GetValue();

	EndModal(wxID_OK);
}

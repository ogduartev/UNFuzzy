#include "DialogoAsignarEtiquetas.h"


BEGIN_EVENT_TABLE(DialogoAsignarEtiquetas, wxDialog)
    EVT_CLOSE(DialogoAsignarEtiquetas::OnClose)
    EVT_BUTTON(wxID_OK   , DialogoAsignarEtiquetas::OnOK)
END_EVENT_TABLE()

DialogoAsignarEtiquetas::DialogoAsignarEtiquetas(Variable *var,wxWindow* parent)
:wxDialog(parent,wxID_ANY,wxString(_("Variable labeling")))
{
	Var=var;

  wxFlexGridSizer*  sizerTotal;
  wxFlexGridSizer*  sizerControles;
  wxFlexGridSizer*  sizerOKCancel;

  sizerTotal       = new wxFlexGridSizer(1,4,0);
  sizerControles   = new wxFlexGridSizer(1,3,0);
  sizerOKCancel    = new wxFlexGridSizer(2,1,0);

  wxStaticText *staticSet;
  staticSet        = new wxStaticText(this,wxID_ANY, _("Set of labels"));
  listaEtiquetas   = new wxListBox(this,DLG_ETIQUETAR_LISTETIQUETAS,wxDefaultPosition,wxSize(300,300));
  checkOrden       = new wxCheckBox(this,DLG_ETIQUETAR_CHECKORDEN,_("Invert order of labels"));

  buttonOK         = new wxButton(this,wxID_OK,_("OK"));
  buttonCancel     = new wxButton(this,wxID_CANCEL,_("Cancel"));

  sizerControles->Add(staticSet, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
  sizerControles->Add(listaEtiquetas, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
  sizerControles->Add(checkOrden, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

	sizerOKCancel->Add(buttonOK, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerOKCancel->Add(buttonCancel, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

	sizerTotal->Add(sizerControles, 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);
	sizerTotal->Add(sizerOKCancel , 1, wxALIGN_CENTRE_HORIZONTAL|wxALL, 5);

	cargarEtiquetas();

  this->SetSizer(sizerTotal);
  this->Layout();
  sizerTotal->Fit(this);

}

DialogoAsignarEtiquetas::~DialogoAsignarEtiquetas()
{
	//dtor
}

void DialogoAsignarEtiquetas::OnClose(wxCloseEvent&   event)
{
}

void DialogoAsignarEtiquetas::OnOK(wxCommandEvent&   event)
{
	int selEtiqueta=listaEtiquetas->GetSelection();
	if(selEtiqueta!=wxNOT_FOUND)
	{
	  wxString linea=listaEtiquetas->GetString(selEtiqueta);
	  wxArrayString etiquetas=cargarLinea(linea);
	  for(int i=0;i<etiquetas.Count();i++)
		{
			int index;
			if(checkOrden->IsChecked())
			{
				index= etiquetas.Count()-1-i;
			}else
			{
			  index=i;
			}
			wxString nom=etiquetas[index];
			const char* ascii_str = (const char*)nom.mb_str(wxConvUTF8);
		  Var->conjunto(i)->nombre(ascii_str);
		}
	}
	EndModal(wxID_OK);
}

wxArrayString DialogoAsignarEtiquetas::cargarLinea(wxString linea)
{
	wxString otrosSep=",;%$#/\t";
	wxArrayString patrones;
	wxChar sep='-';
	for(int i=0;i<otrosSep.Len();i++)
	{
		linea.Replace(otrosSep[i],sep);
	}
	patrones=wxSplit(linea,sep);
	for(int i=0;i<patrones.Count();i++)
	{
	  patrones[i]=patrones[i].Trim(true);
	  patrones[i]=patrones[i].Trim(false);
	}
	return patrones;
}

void DialogoAsignarEtiquetas::cargarEtiquetas()
{
	wxTextFile fileLabels;
	wxFileName f(wxStandardPaths::Get().GetExecutablePath());
	wxString labelsFile(f.GetPath());
	labelsFile << "/locale/" << _("labels_EN");
	fileLabels.Open(labelsFile);
	wxString linea = fileLabels.GetFirstLine();
	cargarLinea(linea);
  wxArrayString labelsN;
	while(!fileLabels.Eof())
	{
	  wxString linea = fileLabels.GetNextLine();
	  wxArrayString labels;
	  labels=cargarLinea(linea);
		if(labels.Count()==Var->numeroConjuntos())
		{
		  wxString todas="";
		  for(long i=0;i < labels.Count();i++)
			{
			  todas << labels[i];
			  if(i < labels.Count()-1)
				{
					todas << " - ";
				}
			}
			labelsN.Add(todas);
		}
	}
  wxString todas="";
  for(long i=0;i < Var->numeroConjuntos();i++)
	{
	  todas << _("Set ") << (i+1) ;
	  if(i < Var->numeroConjuntos()-1)
		{
			todas << " - ";
		}
	}
	labelsN.Add(todas);
	if(labelsN.Count()>0)
	{
 		listaEtiquetas->InsertItems(labelsN,0);
	}
}

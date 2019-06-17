#include "graficadorRed.h"

graficadorRed::graficadorRed(wxDC *Dc, wxRect R)
{
	dc=Dc;
	marco=R;
}

graficadorRed::~graficadorRed()
{
	//dtor
}

void graficadorRed::pintarNodo(nodo *Nodo, wxRect canvasSLD)
{
	int Xo=canvasSLD.GetTopLeft().x;
	int Yo=canvasSLD.GetTopLeft().y;
	int width=canvasSLD.GetWidth();
	int height=canvasSLD.GetHeight();

	wxBrush brushNodo(*wxWHITE);
	dc->SetBrush(brushNodo);

  dc->DrawRectangle(Xo, Yo, width, height );
  wxString str;
  wxSize sz;

  str=Nodo->sld()->nombre;
	while(dc->GetTextExtent(str).GetWidth() > width*0.75)
	{
		str=str.Left(str.Length()-2);
	}
	sz=dc->GetTextExtent(str);
	int xo=Xo;
	int yo=Yo;
	xo=Xo+width/2 - sz.GetWidth()/2;
	yo=Yo+5;
	dc->DrawText(str,xo,yo);
  int numEntradas=Nodo->sld()->entradas->numeroVariables();
  int numSalidas =Nodo->sld()->salidas->numeroVariables();
  float offset;

 	wxBrush brushPinEntra(wxColour(0xFF,0xF6,0xBA));
	dc->SetBrush(brushPinEntra);

  offset=(float)height/(float)numEntradas;
  for(int i=0;i<numEntradas;i++)
	{
		xo=Xo;
		yo=Yo+offset/2 + offset*i -tamPunto/2;
		dc->DrawRectangle( xo, yo , tamPunto, tamPunto );
		str=Nodo->sld()->nombreVariableEntrada(i);
		str=str.Left(3);
		sz=dc->GetTextExtent(str);
		xo=Xo + tamPunto + 5 ;
		yo=Yo+ offset/2 + offset*i - sz.GetHeight()/2;
		dc->DrawText(str,xo,yo);
	}

 	wxBrush brushPinSale(wxColour(0xDC,0xEF,0xF7));
	dc->SetBrush(brushPinSale);

  offset=(float)height/(float)numSalidas;
  for(int i=0;i<numSalidas;i++)
	{
		xo=Xo + width - tamPunto;
		yo=Yo + offset/2 + offset*i -tamPunto/2;
		dc->DrawRectangle( xo, yo , tamPunto, tamPunto );
		wxString str=Nodo->sld()->nombreVariableSalida(i);
		str=str.Left(3);
		sz=dc->GetTextExtent(str);
		xo=Xo + width - tamPunto - sz.GetWidth() - 5 ;
		yo=Yo + offset/2 + offset*i - sz.GetHeight()/2;
		dc->DrawText(str,xo,yo);
	}

 	wxBrush brushElimina(wxColour(0xFF,0x70,0x70));
	dc->SetBrush(brushElimina);
	int x=canvasSLD.GetTopRight().x - tamElimina +1;
	int y=canvasSLD.GetTopRight().y;
	dc->DrawRectangle(x,y,tamElimina,tamElimina);

}

void graficadorRed::ubicarEnlaces(red *Red, wxRect***	botonesSLD)
{
  for(int numCapa=0;numCapa < Red->capas()->GetItemsInContainer();numCapa++)
	{
		for(int numNodo=0;numNodo < Red->capas()->dato(numCapa)->nodos()->GetItemsInContainer();numNodo++)
		{
			wxPoint pt;
			pt.x=botonesSLD[numCapa][numNodo]->GetTopLeft().x;
			pt.y=botonesSLD[numCapa][numNodo]->GetTopLeft().y;
			nodo* Nodo=Red->ptrNodo( numCapa, numNodo);

			int numEntradas=Nodo->sld()->entradas->numeroVariables();
			int numSalidas =Nodo->sld()->salidas->numeroVariables();
			float offset;

			offset=(float)(heightSLD)/(float)numEntradas;
			for(int i=0;i<numEntradas;i++)
			{
				int xo=pt.x;
				int yo=pt.y + offset/2 + offset*i;
				Nodo->entradas()->dato(i)->Posicion = wxPoint(xo,yo);
			}
			offset=(float)(heightSLD)/(float)numSalidas;
			for(int i=0;i<numSalidas;i++)
			{
				int xo=pt.x + widthSLD;
				int yo=pt.y + offset/2 + offset*i ;
				Nodo->salidas()->dato(i)->Posicion = wxPoint(xo,yo);
			}
		}
	}
}


void graficadorRed::pintarEnlaces(red *Red, wxRect***	botonesSLD)
{
	ubicarEnlaces(Red, botonesSLD);
	wxPen penEnlace(*wxBLUE,2);
	dc->SetPen(penEnlace);
  for(int numCapa=0;numCapa < Red->capas()->GetItemsInContainer();numCapa++)
	{
		for(int numNodo=0;numNodo < Red->capas()->dato(numCapa)->nodos()->GetItemsInContainer();numNodo++)
		{
			nodo* Nodo=Red->ptrNodo( numCapa, numNodo);
			int numEntradas =Nodo->sld()->entradas->numeroVariables();
			for(int numPin=0;numPin<numEntradas;numPin++)
			{
				pin* pinE=Nodo->entradas()->dato(numPin);
				pin* pinS=pinE->contacto();
				if(pinS)
				{
				  dc->DrawLine(pinE->Posicion, pinS->Posicion);
				}
			}
		}
	}
}

void graficadorRed::pintarIconosPlus(red *Red)
{
	wxPen penIconoPlus(*wxBLACK,1);
	dc->SetPen(penIconoPlus);
	wxBrush brushIconoPlus(*wxTRANSPARENT_BRUSH);
	dc->SetBrush(brushIconoPlus);

  for(int numCapa=0;numCapa < Red->capas()->GetItemsInContainer(); numCapa++)
	{
		int Xo=marco.GetLeftBottom().x + sepXSLD/2 + numCapa*(widthSLD+sepXSLD) + widthSLD/2;
		int Yo=marco.GetLeftBottom().y - tamIconoPlus*3/2;
		int xo,yo;
		yo=Yo;
		xo=Xo - tamIconoPlus*3/2;
		dc->DrawBitmap(wxMEMORY_BITMAP(eliminacapa),xo,yo);
		xo=Xo + tamIconoPlus*1/2 ;
		dc->DrawBitmap(wxMEMORY_BITMAP(adicionanodo),xo,yo);
	}
	int xo=marco.GetRightBottom().x - tamIconoPlus*3/2;
	int yo=marco.GetLeftBottom().y - tamIconoPlus*3/2;
	dc->DrawBitmap(wxMEMORY_BITMAP(adicionacapa),xo,yo);
}

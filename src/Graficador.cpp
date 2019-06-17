#include "Graficador.h"

Graficador::Graficador(wxClientDC *Dc, wxRect R)
{
	dc=Dc;
	marco=R;
	margenIzq=60;
	margenDer=15;
	margenSup=15;
	margenInf=30;
	margenFlecha=10;
	tamFlecha=5;
  numDX=5;
  numDY=3;
  tickTam=5;
  tamArrastre=4;
  calcularRects();
}

Graficador::~Graficador()
{
	//dtor
}

void Graficador::pintarMarco()
{
  wxBrush brushFondo(*wxWHITE_BRUSH);
  wxBrush brushFlecha(*wxBLACK_BRUSH);
  wxPen penMarco(*wxBLACK, 1);

  dc->SetBrush(brushFondo);
  dc->SetPen(penMarco);
  dc->DrawRectangle(marco);
}

void Graficador::calcularRects()
{
	ejes.SetLeft  (marco.GetLeft()  + margenIzq);
	ejes.SetRight (marco.GetRight() - margenDer);
	ejes.SetTop   (marco.GetTop()   + margenSup);
	ejes.SetBottom(marco.GetBottom()- margenInf);

	canvas.SetLeft  (marco.GetLeft()  + margenIzq);
	canvas.SetRight (marco.GetRight() - margenDer - margenFlecha);
	canvas.SetTop   (marco.GetTop()   + margenSup + margenFlecha);
	canvas.SetBottom(marco.GetBottom()- margenInf);
}


void Graficador::pintarEjes()
{

	wxPoint puntaX[3];
	puntaX[0]=wxPoint(ejes.GetBottomRight().x-0,ejes.GetBottomRight().y-0);
	puntaX[1]=wxPoint(ejes.GetBottomRight().x-tamFlecha,ejes.GetBottomRight().y-tamFlecha);
	puntaX[2]=wxPoint(ejes.GetBottomRight().x-tamFlecha,ejes.GetBottomRight().y+tamFlecha);
	wxPoint puntaY[3];
	puntaY[0]=wxPoint(ejes.GetTopLeft().x-0,ejes.GetTopLeft().y-0);
	puntaY[1]=wxPoint(ejes.GetTopLeft().x-tamFlecha,ejes.GetTopLeft().y+tamFlecha);
	puntaY[2]=wxPoint(ejes.GetTopLeft().x+tamFlecha,ejes.GetTopLeft().y+tamFlecha);


  wxBrush brushFlecha(*wxBLACK_BRUSH);
  wxPen penEjes(*wxBLACK, 1);
  dc->SetBrush(brushFlecha);
  dc->SetPen(penEjes);
  dc->DrawLine(ejes.GetBottomLeft(),ejes.GetBottomRight());
  dc->DrawPolygon(3,puntaX);
  dc->DrawLine(ejes.GetBottomLeft(),ejes.GetTopLeft());
  dc->DrawPolygon(3,puntaY);
}


void Graficador::pintarTitle(wxString strT)
{
	int x,y;
	x=0.5*(ejes.GetTopLeft().x +ejes.GetTopRight().x);
	y=marco.GetTopLeft().y;
  wxSize sz=dc->GetTextExtent(strT);
  dc->DrawText(strT,x-sz.GetWidth()/2,y+2);
}

void Graficador::pintarTicks(float mnx, float mxx, float mny, float mxy)
{
	int xo,yo,xf,yf;

  for(int i=0;i<numDX;i++)
	{
		float mn=mnx;
		float mx=mxx;
		float DR=(mx-mn)/(numDX-1);
		float R=mn + i*DR;
		int dx=canvas.GetBottomRight().x-canvas.GetBottomLeft().x;
	  xo=canvas.GetBottomLeft().x + i * dx/(numDX-1);
	  xf=xo;
	  yo=canvas.GetBottomLeft().y-tickTam;
	  yf=canvas.GetBottomLeft().y+tickTam;
	  dc->DrawLine(xo,yo,xf,yf);
	  char cad[40];
	  sprintf(cad,"%.2f",R);
	  wxString str=cad;
	  wxSize sz=dc->GetTextExtent(str);
	  dc->DrawText(cad,xf-sz.GetWidth()/2,yf+tickTam);
	}

  for(int i=0;i<numDY;i++)
	{
		float mn=mny;
		float mx=mxy;
		float DR=(mx-mn)/(numDY-1);
		float R=mn + i*DR;
		int dy=canvas.GetBottomLeft().y-canvas.GetTopLeft().y;
	  yo=canvas.GetBottomLeft().y - i * dy/(numDY-1);
	  yf=yo;
	  xo=canvas.GetBottomLeft().x-tickTam;
	  xf=canvas.GetBottomLeft().x+tickTam;
	  dc->DrawLine(xo,yo,xf,yf);
	  char cad[40];
	  sprintf(cad,"%.2f",R);
	  wxString str=cad;
	  wxSize sz=dc->GetTextExtent(str);
	  dc->DrawText(cad,xo-sz.GetWidth()-tickTam,yf-sz.GetHeight()/2);
	}
}

void Graficador::pintarVariable(Variable *Var,int numConjunto,bool flagColor)
{
	pintarMarco();
	pintarEjes();
	pintarTicks(Var->rangoMinimo(),Var->rangoMaximo(),0.0,1.0);

  wxPen penConjunto(*wxBLUE, 2);
  wxPen penConjuntoActual(*wxRED, 2);

  for(int i=0;i<Var->numeroConjuntos();i++)
	{
		if((i==numConjunto) and flagColor)
		{
			dc->SetPen(penConjuntoActual);
		}else
		{
			dc->SetPen(penConjunto);
		}
		ConjuntoDifuso *C=Var->conjunto(i);
		pintarConjunto(Var,C);
		if((i==numConjunto) and flagColor)
		{
			pintarPuntosArrastre(Var,C);
		}
	}
}

void Graficador::pintarDifusor(Variable *Var, bool flagEjes)
{
	if(flagEjes)
	{
		pintarMarco();
		pintarEjes();
		pintarTicks(Var->rangoMinimo(),Var->rangoMaximo(),0.0,1.0);
	}

  wxPen penConjunto(*wxBLUE, 2);
  wxPen penConjuntoActual(*wxRED, 2);

	dc->SetPen(penConjuntoActual);

	Difusor* dif=Var->difusorEntrada();
	float xmn=dif->minimo();
	float xmx=dif->maximo();
	int XMN=canvas.GetBottomLeft().x  + (xmn-Var->rangoMinimo())*(canvas.GetBottomRight().x-canvas.GetBottomLeft().x)/(Var->rangoMaximo()-Var->rangoMinimo());
	int XMX=canvas.GetBottomRight().x + (xmx-Var->rangoMinimo())*(canvas.GetBottomRight().x-canvas.GetBottomLeft().x)/(Var->rangoMaximo()-Var->rangoMinimo());
	int Intervalos=XMX-XMN+2;
	for(int j=0;j<Intervalos;j++)
	{
		float x,y;
		int X,Y;
		int XO,YO,XF,YF;
		x=xmn + j*(xmx-xmn)/(XMX-XMN);
		y=dif->pertenencia(x);
		X=canvas.GetBottomLeft().x + (x-Var->rangoMinimo())*(canvas.GetBottomRight().x-canvas.GetBottomLeft().x)/(Var->rangoMaximo()-Var->rangoMinimo());
		Y=canvas.GetBottomLeft().y + (y-0.0)*(canvas.GetTopLeft().y-canvas.GetBottomLeft().y)/(1.0-0.0);
		if(j==0)
		{
			XO=X;
			YO=Y;
		}else
		{
			XF=X;
			YF=Y;
			dc->DrawLine(XO,YO,XF,YF);
			XO=X;
			YO=Y;
		}
	}

  wxPen penPuntos(*wxRED, 2);
	dc->SetPen(penPuntos);
	for(int j=0;j<dif->numeroPuntos();j++)
	{
		float dx=(xmx-xmn)/(dif->numeroPuntos()+1);
		float x,y;
		int XO,YO,XF,YF;
		x=xmn + (j+1)*dx;
		y=dif->pertenencia(x);
		XF=canvas.GetBottomLeft().x + (x-Var->rangoMinimo())*(canvas.GetBottomRight().x-canvas.GetBottomLeft().x)/(Var->rangoMaximo()-Var->rangoMinimo());
		YF=canvas.GetBottomLeft().y + (y-0.0)*(canvas.GetTopLeft().y-canvas.GetBottomLeft().y)/(1.0-0.0);
		XO=XF;
		YO=canvas.GetBottomLeft().y;
		dc->DrawLine(XO,YO,XF,YF);
	}


}

void Graficador::pintarConjunto(Variable *Var,ConjuntoDifuso *C)
{
	float xmn=C->minimo();
	float xmx=C->maximo();
	int XMN=canvas.GetBottomLeft().x  + (xmn-Var->rangoMinimo())*(canvas.GetBottomRight().x-canvas.GetBottomLeft().x)/(Var->rangoMaximo()-Var->rangoMinimo());
	int XMX=canvas.GetBottomRight().x + (xmx-Var->rangoMinimo())*(canvas.GetBottomRight().x-canvas.GetBottomLeft().x)/(Var->rangoMaximo()-Var->rangoMinimo());
	int Intervalos=XMX-XMN+2;
	for(int j=0;j<Intervalos;j++)
	{
		float x,y;
		int X,Y;
		int XO,YO,XF,YF;
		x=xmn + j*(xmx-xmn)/(XMX-XMN);
		y=C->pertenencia(x);
		X=canvas.GetBottomLeft().x + (x-Var->rangoMinimo())*(canvas.GetBottomRight().x-canvas.GetBottomLeft().x)/(Var->rangoMaximo()-Var->rangoMinimo());
		Y=canvas.GetBottomLeft().y + (y-0.0)*(canvas.GetTopLeft().y-canvas.GetBottomLeft().y)/(1.0-0.0);
		if(j==0)
		{
			XO=X;
			YO=Y;
		}else
		{
			XF=X;
			YF=Y;
			dc->DrawLine(XO,YO,XF,YF);
			XO=X;
			YO=Y;
		}
	}
}

void Graficador::pintarPuntosArrastre(Variable *Var,ConjuntoDifuso *C)
{
  wxBrush brushArrastre(*wxWHITE_BRUSH);
  dc->SetBrush(brushArrastre);

	numeroPuntosArrastre=C->numeroPuntosClaves();
	C->puntosClaves(arrastre);
	puntosArrastre[0]=canvas.GetTopLeft();
	puntosArrastre[numeroPuntosArrastre+1]=canvas.GetBottomRight();

	int Xo,Xf,Yo,Yf;
	float xo,xf,yo,yf;
	Xo=puntosArrastre[0].x;
	Yf=puntosArrastre[0].y;
	Xf=puntosArrastre[numeroPuntosArrastre+1].x;
	Yo=puntosArrastre[numeroPuntosArrastre+1].y;
	xo=Var->rangoMinimo();
	yo=0.0;
	xf=Var->rangoMaximo();
	yf=1.0;

	int i;
	for(i=1;i<=numeroPuntosArrastre;i++)
	{
		float x,y;
		int X,Y;
		x=arrastre[i-1];
		y=C->pertenencia(x);
		X=Xo+(int)((x-xo)*(Xf-Xo)/(xf-xo));
		Y=Yo+(int)((y-yo)*(Yf-Yo)/(yf-yo));
		puntosArrastre[i]=wxPoint(X,Y);
		wxRect rect(X-tamArrastre,Y-tamArrastre,tamArrastre*2,tamArrastre*2);
		dc->DrawRectangle(rect);
	}
}

void Graficador::pintarFondoFuncion(float mnx, float mxx, float mny, float mxy, wxString nomEntra, wxString nomSale)
{
	numDX=5;
	numDY=5;

	pintarMarco();
	pintarEjes();
	pintarTicks(mnx,mxx,mny,mxy);
	pintarLabels(nomEntra,nomSale);
}

void Graficador::pintarFondoFuncionES(SistemaLogicaDifusa* SLD, int numEntra, int numSale)
{
	float mnx, mxx, mny, mxy;
	mnx=SLD->entradas->variable(numEntra)->rangoMinimo();
	mxx=SLD->entradas->variable(numEntra)->rangoMaximo();
	mny=SLD->salidas-> variable(numSale) ->rangoMinimo();
	mxy=SLD->salidas-> variable(numSale) ->rangoMaximo();
	wxString nomEntra=SLD->entradas->variable(numEntra)->nombreVariable();
	wxString nomSale=SLD->salidas->variable(numSale)->nombreVariable();

	pintarFondoFuncion(mnx,mxx,mny,mxy,nomEntra,nomSale);
}

void Graficador::pintarCurvaFuncion(float mnx, float mxx, float mny, float mxy,
																		int numSalidas, int numEntra, int numSale, float* entra,
																		wxColour &color)
{
  wxPen penCurva(color, 2);
  dc->SetPen(penCurva);

	int MNX, MXX, MNY, MXY;
	MNX=canvas.GetBottomLeft().x;
	MNY=canvas.GetBottomLeft().y;
	MXX=canvas.GetTopRight().x;
	MXY=canvas.GetTopRight().y;

	float sale[numSalidas];
	float x,y;
	int XO,YO,XF,YF;

	XO=MNX;
	entra[numEntra]=mnx;
	calcularFuncion(entra,sale);
	y=sale[numSale];
	YO=MNY + (y-mny)*(MXY-MNY)/(mxy-mny);
	for(int X=MNX; X <= MXX; X++)
	{
		x=mnx + (X-MNX)*(mxx-mnx)/(MXX-MNX);
		entra[numEntra]=x;
		calcularFuncion(entra,sale);
		y=sale[numSale];
		XF=X;
		YF=MNY + (y-mny)*(MXY-MNY)/(mxy-mny);
		dc->DrawLine(XO,YO,XF,YF);
		XO=XF;
		YO=YF;
	}
}

void Graficador::pintarCurvaFuncionES(SistemaLogicaDifusa* SLD, int numEntra, int numSale, float* entra,wxColour &color)
{
  wxPen penCurva(color, 2);
  dc->SetPen(penCurva);

	float mnx, mxx, mny, mxy;
	mnx=SLD->entradas->variable(numEntra)->rangoMinimo();
	mxx=SLD->entradas->variable(numEntra)->rangoMaximo();
	mny=SLD->salidas-> variable(numSale) ->rangoMinimo();
	mxy=SLD->salidas-> variable(numSale) ->rangoMaximo();

  int numSalidas=SLD->salidas->numeroVariables();

	int MNX, MXX, MNY, MXY;
	MNX=canvas.GetBottomLeft().x;
	MNY=canvas.GetBottomLeft().y;
	MXX=canvas.GetTopRight().x;
	MXY=canvas.GetTopRight().y;

	float sale[SLD->salidas->numeroVariables()];
	float x,y;
	int XO,YO,XF,YF;

	XO=MNX;
	entra[numEntra]=mnx;
	SLD->calcular(entra,sale);
	y=sale[numSale];
	YO=MNY + (y-mny)*(MXY-MNY)/(mxy-mny);
	for(int X=MNX; X <= MXX; X++)
	{
		x=mnx + (X-MNX)*(mxx-mnx)/(MXX-MNX);
		entra[numEntra]=x;
		SLD->calcular(entra,sale);
		y=sale[numSale];
		XF=X;
		YF=MNY + (y-mny)*(MXY-MNY)/(mxy-mny);
		dc->DrawLine(XO,YO,XF,YF);
		XO=XF;
		YO=YF;
	}

}

void Graficador::pintarCurvaFuncionES(red* Red, int numEntra, int numSale, float* entra,wxColour &color)
{
  wxPen penCurva(color, 2);
  dc->SetPen(penCurva);

	float mnx, mxx, mny, mxy;
	mnx=Red->variableEntrada(numEntra)->rangoMinimo();
	mxx=Red->variableEntrada(numEntra)->rangoMaximo();
	mny=Red->variableSalida(numSale)->rangoMinimo();
	mxy=Red->variableSalida(numSale)->rangoMaximo();

  int numSalidas=Red->numeroSalidas();

//	pintarCurvaFuncion(mnx, mxx, mny, mxy, numSalidas, numEntra, numSale, entra, color);
//	return;

	int MNX, MXX, MNY, MXY;
	MNX=canvas.GetBottomLeft().x;
	MNY=canvas.GetBottomLeft().y;
	MXX=canvas.GetTopRight().x;
	MXY=canvas.GetTopRight().y;

	float sale[Red->numeroSalidas()];
	float x,y;
	int XO,YO,XF,YF;

	XO=MNX;
	entra[numEntra]=mnx;
	Red->calcular(entra,sale);
	y=sale[numSale];
	YO=MNY + (y-mny)*(MXY-MNY)/(mxy-mny);
	for(int X=MNX; X <= MXX; X++)
	{
		x=mnx + (X-MNX)*(mxx-mnx)/(MXX-MNX);
		entra[numEntra]=x;
		Red->calcular(entra,sale);
		y=sale[numSale];
		XF=X;
		YF=MNY + (y-mny)*(MXY-MNY)/(mxy-mny);
		dc->DrawLine(XO,YO,XF,YF);
		XO=XF;
		YO=YF;
	}
}

void Graficador::pintarLabels(wxString strH, wxString strV)
{
  wxSize szH=dc->GetTextExtent(strH);
  wxSize szV=dc->GetTextExtent(strV);
  wxPoint pH(canvas.GetBottomRight().x - szH.GetWidth() ,canvas.GetBottomRight().y - szH.GetHeight() - tickTam);
  wxPoint pV(canvas.GetTopLeft().x + tickTam,canvas.GetTopLeft().y + szV.GetWidth());

  dc->DrawText(strH,pH);
  dc->DrawRotatedText(strV,pV,90);
}

void Graficador::pintarComposicion(SistemaLogicaDifusa* SLD, int numSale, int numRegla)
{
  wxPen penCurva(*wxBLUE, 2);
  dc->SetPen(penCurva);

	float mnx, mxx, mny, mxy;
	mnx=SLD->salidas->variable(numSale)->rangoMinimo();
	mxx=SLD->salidas->variable(numSale)->rangoMaximo();
	mny=0.0;
	mxy=1.0;
	numDX=5;
	numDY=5;

	int MNX, MXX, MNY, MXY;
	MNX=canvas.GetBottomLeft().x;
	MNY=canvas.GetBottomLeft().y;
	MXX=canvas.GetTopRight().x;
	MXY=canvas.GetTopRight().y;

	float x,y;
	int XO,YO,XF,YF;

	XO=MNX;
	x=mnx;
	y=SLD->motor->pertenenciaComposicion(numSale, numRegla, x);
	YO=MNY + (y-mny)*(MXY-MNY)/(mxy-mny);
	for(int X=MNX; X <= MXX; X++)
	{
		x=mnx + (X-MNX)*(mxx-mnx)/(MXX-MNX);
		y=SLD->motor->pertenenciaComposicion(numSale, numRegla, x);
		XF=X;
		YF=MNY + (y-mny)*(MXY-MNY)/(mxy-mny);
		dc->DrawLine(XO,YO,XF,YF);
		XO=XF;
		YO=YF;
	}
	pintarTitle(wxString::Format("Regla %d",(numRegla+1)));
}

void Graficador::pintarConjuncion(SistemaLogicaDifusa* SLD, int numSale,float salida)
{
  wxPen penCurva(*wxBLUE, 2);
  dc->SetPen(penCurva);

	float mnx, mxx, mny, mxy;
	mnx=SLD->salidas->variable(numSale)->rangoMinimo();
	mxx=SLD->salidas->variable(numSale)->rangoMaximo();
	mny=0.0;
	mxy=1.0;
	numDX=5;
	numDY=5;

	int MNX, MXX, MNY, MXY;
	MNX=canvas.GetBottomLeft().x;
	MNY=canvas.GetBottomLeft().y;
	MXX=canvas.GetTopRight().x;
	MXY=canvas.GetTopRight().y;

	float x,y;
	int XO,YO,XF,YF;

	XO=MNX;
	x=mnx;
	y=SLD->concreto->pertenenciaConjuncion(numSale, x);
	YO=MNY + (y-mny)*(MXY-MNY)/(mxy-mny);
	for(int X=MNX; X <= MXX; X++)
	{
		x=mnx + (X-MNX)*(mxx-mnx)/(MXX-MNX);
		y=SLD->concreto->pertenenciaConjuncion(numSale, x);
		XF=X;
		YF=MNY + (y-mny)*(MXY-MNY)/(mxy-mny);
		dc->DrawLine(XO,YO,XF,YF);
		XO=XF;
		YO=YF;
	}

  wxPen penConcreto(*wxRED, 2);
  dc->SetPen(penConcreto);
  x=salida;
	XO=MNX + (x-mnx)*(MXX-MNX)/(mxx-mnx);
	XF=XO;
	YO=MNY;
	YF=MXY;
	dc->DrawLine(XO,YO,XF,YF);
	pintarTitle(_("Conjunction"));
}

void Graficador::calcularFuncion(float*entra, float* sale)
{
	sale[0]=0.2;
}

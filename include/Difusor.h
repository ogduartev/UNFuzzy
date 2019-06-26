#ifndef DIFUSOR_H
#define DIFUSOR_H

#include <cstdio>

#include <ConjuntoDifuso.h>


/*//////////////////////////////////////////
class Difusor:public ConjuntoDifuso

    Tiene por propósito definir los difusores que pueden
    emplear las Variables Linguísticas de Entrada.
    Es un conjunto Difuso de forma constante, pero cuyo Centro
    se puede modificar, alterando con ello los parámetros que
    definen la función de pertenencia. El difusor se evalúa en un
    número finito de puntos (NúmeroPuntos), y no en todo el Soporte,
    por lo tanto, se crea un intervalo de evaluación (dx).

    Esta clase es abstracta, y sus herederas tiene herencia múltiple
    de Difusor, y de otra clase heredera de ConjuntoDifuso (por ejemplo
    ConjuntoTriangulo). Este hecho crea ambiguedades en el llamado
    de las funciones del padre ConjuntoDifuso. Hay funciones
    encargadas de resolver estas ambiguedades

atributos
	char *Codigo_C;
	char *Codigo_CPP;
	int NumeroPuntos;
	double dx;
	double Centro;

procedimientos
	void numeroPuntos(int num)          modificador de NumeroPuntos, tambien cambia dx
	void ancho(double soporte)           permite editar el ancho del Difusor
	int numeroPuntos()                  consultor de NumeroPuntos
	double intervalo()                   consultor de dx
	double centro()                      consultor de Centro

procedimiento sin utilidad, que debe definirse por heredar virtual de ConjuntoDifuso

    double centroAltura()
	void nuevoPuntoClave(int, double )
	char *codigoC()
	char *codigoCPP()

Las funciones virtual=0 deben ser redefinidas por los hijos

	virtual void entrada(double)=0;      Cambia el centro del Difusor,
													 movienndo todos los parámetros
													 del padre, para cambiar su
													 función de pertenencia

estas funciones llaman a las del padre adecuado
	 para resolver las ambiguedades de tener herencia múltiple
	 pero con el mismo "abuelo"

	virtual void puntosClaves(double* )=0;
	virtual int numeroPuntosClaves()=0;
	virtual void ajustar(double nuevoMinimo,double nuevoMaximo)=0;
	virtual void recibirDatos(TWindow *parent, double mn, double mx)=0;
	virtual double pertenencia(double)=0;
	virtual double minimo()=0;
	virtual double maximo()=0;
	virtual void minimo(double mn)=0;
	virtual void maximo(double mx)=0;
	virtual char *nombre()=0;
	virtual char *tipo()=0;
	virtual double var1()=0;
	virtual double var2()=0;
	virtual double var3()=0;
	virtual double var4()=0;
	virtual int identificador()=0;


Estas funciones devuelven el texto necesario para generar
    código C y C++

	virtual char *codigo_C(int i)=0;
	virtual char *codigo_CPP()=0;

/////////////////////////////////////////////*/


class Difusor:public ConjuntoDifuso
{
public:
	Difusor()
	{
		NumeroPuntos=1;
	}
	~Difusor()
	{
	}
	void numeroPuntos(int num)
	{
		if(num<1)
			num=1;
		NumeroPuntos=num;
		dx=(maximo()-minimo())/(num+1);
	}
	void ancho(double soporte)
	{
		double centro,mn,mx;
		centro=(maximo()+minimo())/2;
		mn=centro-soporte/2;
		mx=centro+soporte/2;
		minimo(mn);
		maximo(mx);
		numeroPuntos(NumeroPuntos);
	}
	int numeroPuntos()
	{
		return NumeroPuntos;
	}
	double intervalo()
	{
		return dx;
	}
	double centro()
	{
		return Centro;
	}
	double centroAltura()
  {
      return 0.0;
  }
	virtual void puntosClaves(double* x)=0;
	virtual int numeroPuntosClaves()=0;
	void nuevoPuntoClave(int, double ){}
	virtual void entrada(double)=0;
	virtual void ajustar(double nuevoMinimo,double nuevoMaximo)=0;
//	virtual void recibirDatos(TWindow *parent, double mn, double mx)=0;
	virtual double pertenencia(double)=0;
	virtual double minimo()=0;
	virtual double maximo()=0;
	virtual void minimo(double mn)=0;
	virtual void maximo(double mx)=0;
	virtual string nombre()=0;
	virtual string tipo()=0;
	virtual double var1()=0;
	virtual double var2()=0;
	virtual double var3()=0;
	virtual double var4()=0;
	virtual int identificador()=0;
	string codigoC(){return "";}
	string codigoCPP(){return "";}
	virtual string codigo_C(int i)=0;
	virtual string codigo_CPP()=0;
protected:
	int NumeroPuntos;
	double dx;
	double Centro;
};

class DifusorTriangulo:public virtual ConjuntoTriangulo,public virtual Difusor
{
public:
	DifusorTriangulo(double x, double me, double ma):ConjuntoTriangulo("",x-me,x,x+ma)
	{
		Centro=x;
		menos=me;
		mas=ma;
		NumeroPuntos=3;
	}
	~DifusorTriangulo()
	{
	}
	void puntosClaves(double *x)
	{
		ConjuntoTriangulo::puntosClaves(x);
	}
	int numeroPuntosClaves()
	{
		return ConjuntoTriangulo::numeroPuntosClaves();
	}
	void entrada(double x1)
	{
		ConjuntoTriangulo::minimo(x1-menos);
		ConjuntoTriangulo::maximo(x1+mas);
		ConjuntoTriangulo::primerCorte(x1);
		Centro=x1;
	}
	double pertenencia(double x)
	{
		return ConjuntoTriangulo::pertenencia(x);
	}
	double minimo()
	{
		return ConjuntoTriangulo::minimo();
	}
	double maximo()
	{
		return ConjuntoTriangulo::maximo();
	}
	double primerCorte()
	{
		return ConjuntoTriangulo::primerCorte();
	}
	void primerCorte(double pc)
	{
		ConjuntoTriangulo::primerCorte(pc);
	}
	void minimo(double mn)
	{
		ConjuntoTriangulo::minimo(mn);
	}
	void maximo(double mx)
	{
		ConjuntoTriangulo::maximo(mx);
	}
	string nombre()
	{
		return ConjuntoTriangulo::nombre();
	}
	string tipo()
	{
		return ConjuntoTriangulo::tipo();
	}
//	void recibirDatos(TWindow *parent,double mn,double mx);
	void ajustar(double nuevoMinimo, double nuevoMaximo)
	{
		ConjuntoTriangulo::ajustar(nuevoMinimo,nuevoMaximo);
		menos=primerCorte()-minimo();
		mas=maximo()-primerCorte();
		dx=(maximo()-minimo())/(NumeroPuntos+1);
	}
	double var1()
	{
		return minimo();
	}
	double var2()
	{
		return primerCorte();
	}
	double var3()
	{
		return maximo();
	}
	double var4()
	{
		return 0;
	}
	int identificador()
	{
		return ConjuntoTriangulo::identificador();
	}
	string codigo_C(int i)
	{
		wxString CodigoC="";
		CodigoC << ("            if(x<Difusores[") << i << ("].var1)\n");
		CodigoC << ("            	ux=0;\n");
		CodigoC << ("            if(x<Difusores[") << i << ("].var2&&x>=Difusores[") << i << ("].var1)\n");
		CodigoC << ("            	ux=(x-Difusores[") << i << ("].var1)/(Difusores[") << i << ("].var2-Difusores[") << i << ("].var1);\n");
		CodigoC << ("            if(x<Difusores[") << i << ("].var3&&x>=Difusores[") << i << ("].var2)\n");
		CodigoC << ("            	ux=(Difusores[") << i << ("].var3-x)/(Difusores[") << i << ("].var3-Difusores[") << i << ("].var2);\n");
		CodigoC << ("            if(x>=Difusores[") << i << ("].var3)\n");
		CodigoC << ("            	ux=0;");
		return std::string(CodigoC.mb_str());
	}
	string codigo_CPP()
	{
		wxString CodigoCPP="";
		CodigoCPP=("    dif=new DifusorTriangulo(");
		CodigoCPP << centro() << (",") << menos << (",") << mas << (");");
		return std::string(CodigoCPP.mb_str());
	}
protected:
	double mas;
	double menos;
};

class DifusorPi:public virtual ConjuntoPi,public virtual Difusor
{
public:
	DifusorPi(double x, double me1, double me2, double ma1, double ma2):ConjuntoPi("",x-me1,x-me2,x+ma1,x+ma2)
	{
		Centro=x;
		menos1=me1;
		menos2=me2;
		mas1=ma1;
		mas2=ma2;
		NumeroPuntos=3;
	}
	~DifusorPi()
	{
	}
	void puntosClaves(double *x)
	{
		ConjuntoPi::puntosClaves(x);
	}
	int numeroPuntosClaves()
	{
		return ConjuntoPi::numeroPuntosClaves();
	}
	void entrada(double x1)
	{
		ConjuntoPi::minimo(x1-menos1);
		ConjuntoPi::maximo(x1+mas2);
		ConjuntoPi::primerCorte(x1-menos2);
		ConjuntoPi::segundoCorte(x1+mas1);
		Centro=x1;
	}
	double pertenencia(double x)
	{
		return ConjuntoPi::pertenencia(x);
	}
	double minimo()
	{
		return ConjuntoPi::minimo();
	}
	double maximo()
	{
		return ConjuntoPi::maximo();
	}
	double primerCorte()
	{
		return ConjuntoPi::primerCorte();
	}
	double segundoCorte()
	{
		return ConjuntoPi::segundoCorte();
	}
	void primerCorte(double pc)
	{
		ConjuntoPi::primerCorte(pc);
	}
	void segundoCorte(double sc)
	{
		ConjuntoPi::segundoCorte(sc);
	}
	void minimo(double mn)
	{
		ConjuntoPi::minimo(mn);
	}
	void maximo(double mx)
	{
		ConjuntoPi::maximo(mx);
	}
	string nombre()
	{
		return ConjuntoPi::nombre();
	}
	string tipo()
	{
		return ConjuntoPi::tipo();
	}
//	void recibirDatos(TWindow *parent,double mn,double mx);
	void ajustar(double nuevoMinimo, double nuevoMaximo)
	{
		ConjuntoPi::ajustar(nuevoMinimo,nuevoMaximo);
		menos1=centro()-minimo();
		menos2=centro()-primerCorte();
		mas1=segundoCorte()-centro();;
		mas2=maximo()-centro();
		dx=(maximo()-minimo())/(NumeroPuntos+1);
	}
	double var1()
	{
		return minimo();
	}
	double var2()
	{
		return primerCorte();
	}
	double var3()
	{
		return segundoCorte();
	}
	double var4()
	{
		return maximo();
	}
	int identificador()
	{
		return ConjuntoPi::identificador();
	}
	string codigo_C(int i)
	{
		wxString CodigoC="";
		CodigoC << ("            if(x<Difusores[") << i << ("].var1)\n");
		CodigoC << ("            	ux=0;\n");
		CodigoC << ("            if(x<Difusores[") << i << ("].var2&&x>=Difusores[") << i << ("].var1)\n");
		CodigoC << ("            	ux=(x-Difusores[") << i << ("].var1)/(Difusores[") << i << ("].var2-Difusores[") << i << ("].var1);\n");
		CodigoC << ("            if(x<Difusores[") << i << ("].var3&&x>=Difusores[") << i << ("].var2)\n");
		CodigoC << ("            	ux=1;\n");
		CodigoC << ("            if(x<Difusores[") << i << ("].var4&&x>=Difusores[") << i << ("].var3)\n");
		CodigoC << ("            	ux=(Difusores[") << i << ("].var4-x)/(Difusores[") << i << ("].var4-Difusores[") << i << ("].var3);\n");
		CodigoC << ("            if(x>=Difusores[") << i << ("].var4)\n");
		CodigoC << ("            	ux=0;");
		return std::string(CodigoC.mb_str());
	}
	string codigo_CPP()
	{
		wxString CodigoCPP="";
		CodigoCPP=("    dif=new DifusorPi(");
		CodigoCPP << centro() << (",") << menos1 << (",") << menos2 << (",") << mas1 << (",") << mas2 << (");");
		return std::string(CodigoCPP.mb_str());
	}
protected:
	double mas1;
	double mas2;
	double menos1;
	double menos2;
};

class DifusorCampana:public virtual ConjuntoCampana,public virtual Difusor
{
public:
	DifusorCampana(double x, double me, double ma):ConjuntoCampana("",x-me,x,x+ma)
	{
		Centro=x;
		menos=me;
		mas=ma;
		NumeroPuntos=5;
	}
	~DifusorCampana()
	{
	}
	void puntosClaves(double *x)
	{
		ConjuntoCampana::puntosClaves(x);
	}
	int numeroPuntosClaves()
	{
		return ConjuntoCampana::numeroPuntosClaves();
	}
	void entrada(double x1)
	{
		ConjuntoCampana::minimo(x1-menos);
		ConjuntoCampana::maximo(x1+mas);
		ConjuntoCampana::primerCorte(x1);
		Centro=x1;
	}
	double pertenencia(double x)
	{
		return ConjuntoCampana::pertenencia(x);
	}
	double minimo()
	{
		return ConjuntoCampana::minimo();
	}
	double maximo()
	{
		return ConjuntoCampana::maximo();
	}
	double primerCorte()
	{
		return ConjuntoCampana::primerCorte();
	}
	void primerCorte(double pc)
	{
		ConjuntoCampana::primerCorte(pc);
	}
	void minimo(double mn)
	{
		ConjuntoCampana::minimo(mn);
	}
	void maximo(double mx)
	{
		ConjuntoCampana::maximo(mx);
	}
	string nombre()
	{
		return ConjuntoCampana::nombre();
	}
	string tipo()
	{
		return ConjuntoCampana::tipo();
	}
//	void recibirDatos(TWindow *parent,double mn,double mx);
	void ajustar(double nuevoMinimo, double nuevoMaximo)
	{
		ConjuntoCampana::ajustar(nuevoMinimo,nuevoMaximo);
		menos=primerCorte()-minimo();
		mas=maximo()-primerCorte();
		dx=(maximo()-minimo())/(NumeroPuntos+1);
	}
	double var1()
	{
		return minimo();
	}
	double var2()
	{
		return primerCorte();
	}
	double var3()
	{
		return maximo();
	}
	double var4()
	{
		return 0;
	}
	int identificador()
	{
		return ConjuntoCampana::identificador();
	}
	string codigo_C(int i)
	{
		wxString CodigoC="";
		CodigoC << ("            if(x<Difusores[") << i << ("].var1)\n");
		CodigoC << ("            	ux=0;\n");
		CodigoC << ("            if(x<(Difusores[") << i << ("].var2+Difusores[") << i << ("].var1)/2&&x>=Difusores[") << i << ("].var1){\n");
		CodigoC << ("            	ux=(x-Difusores[") << i << ("].var1)/(Difusores[") << i << ("].var2-Difusores[") << i << ("].var1);\n");
		CodigoC << ("            	ux=2*ux*ux;\n");
		CodigoC << ("            	}\n");
		CodigoC << ("            if(x<Difusores[") << i << ("].var2&&x>=(Difusores[") << i << ("].var2+Difusores[") << i << ("].var1)/2){\n");
		CodigoC << ("            	ux=(x-Difusores[") << i << ("].var2)/(Difusores[") << i << ("].var2-Difusores[") << i << ("].var1);\n");
		CodigoC << ("            	ux=1-2*ux*ux;\n");
		CodigoC << ("            	}\n");
		CodigoC << ("            if(x<(Difusores[") << i << ("].var2+Difusores[") << i << ("].var3)/2&&x>=Difusores[") << i << ("].var2){\n");
		CodigoC << ("            	ux=(x-Difusores[") << i << ("].var2)/(Difusores[") << i << ("].var3-Difusores[") << i << ("].var2);\n");
		CodigoC << ("            	ux=1-2*ux*ux;\n");
		CodigoC << ("            	}\n");
		CodigoC << ("            if(x<Difusores[") << i << ("].var3&&x>=(Difusores[") << i << ("].var2+Difusores[") << i << ("].var3)/2){\n");
		CodigoC << ("            	ux=(x-Difusores[") << i << ("].var3)/(Difusores[") << i << ("].var3-Difusores[") << i << ("].var2);\n");
		CodigoC << ("            	ux=2*ux*ux;\n");
		CodigoC << ("            	}\n");
		CodigoC << ("            if(x>=Difusores[") << i << ("].var3)\n");
		CodigoC << ("            	ux=0;");
		return std::string(CodigoC.mb_str());
	}
	string codigo_CPP()
	{
		wxString CodigoCPP="";
		CodigoCPP=("    dif=new DifusorCampana(");
		CodigoCPP << centro() << (",") << menos << (",") << mas << (");");
		return std::string(CodigoCPP.mb_str());
	}
protected:
	double mas;
	double menos;
};

class DifusorPiCampana:public virtual ConjuntoPiCampana,public virtual Difusor
{
public:
	DifusorPiCampana(double x, double me1, double me2, double ma1, double ma2):ConjuntoPiCampana("",x-me1,x-me2,x+ma1,x+ma2)
	{
		Centro=x;
		menos1=me1;
		menos2=me2;
		mas1=ma1;
		mas2=ma2;
		NumeroPuntos=5;
	}
	~DifusorPiCampana()
	{
	}
	void puntosClaves(double *x)
	{
		ConjuntoPiCampana::puntosClaves(x);
	}
	int numeroPuntosClaves()
	{
		return ConjuntoPiCampana::numeroPuntosClaves();
	}
	void entrada(double x1)
	{
		ConjuntoPiCampana::minimo(x1-menos1);
		ConjuntoPiCampana::maximo(x1+mas2);
		ConjuntoPiCampana::primerCorte(x1-menos2);
		ConjuntoPiCampana::segundoCorte(x1+mas1);
		Centro=x1;
	}
	double pertenencia(double x)
	{
		return ConjuntoPiCampana::pertenencia(x);
	}
	double minimo()
	{
		return ConjuntoPiCampana::minimo();
	}
	double maximo()
	{
		return ConjuntoPiCampana::maximo();
	}
	double primerCorte()
	{
		return ConjuntoPiCampana::primerCorte();
	}
	double segundoCorte()
	{
		return ConjuntoPiCampana::segundoCorte();
	}
	void primerCorte(double pc)
	{
		ConjuntoPiCampana::primerCorte(pc);
	}
	void segundoCorte(double sc)
	{
		ConjuntoPiCampana::segundoCorte(sc);
	}
	void minimo(double mn)
	{
		ConjuntoPiCampana::minimo(mn);
	}
	void maximo(double mx)
	{
		ConjuntoPiCampana::maximo(mx);
	}
	string nombre()
	{
		return ConjuntoPiCampana::nombre();
	}
	string tipo()
	{
		return ConjuntoPiCampana::tipo();
	}
//	void recibirDatos(TWindow *parent,double mn,double mx);
	void ajustar(double nuevoMinimo, double nuevoMaximo)
	{
		ConjuntoPiCampana::ajustar(nuevoMinimo,nuevoMaximo);
		menos1=centro()-minimo();
		menos2=centro()-primerCorte();
		mas1=segundoCorte()-centro();;
		mas2=maximo()-centro();
		dx=(maximo()-minimo())/(NumeroPuntos+1);
	}
	double var1()
	{
		return minimo();
	}
	double var2()
	{
		return primerCorte();
	}
	double var3()
	{
		return segundoCorte();
	}
	double var4()
	{
		return maximo();
	}
	int identificador()
	{
		return ConjuntoPiCampana::identificador();
	}
	string codigo_C(int i)
	{
		wxString CodigoC="";
		CodigoC << ("            if(x<Difusores[") << i << ("].var1)\n");
		CodigoC << ("            	ux=0;\n");
		CodigoC << ("            if(x<(Difusores[") << i << ("].var2+Difusores[") << i << ("].var1)/2&&x>=Difusores[") << i << ("].var1){\n");
		CodigoC << ("            	ux=(x-Difusores[") << i << ("].var1)/(Difusores[") << i << ("].var2-Difusores[") << i << ("].var1);\n");
		CodigoC << ("            	ux=2*ux*ux;\n");
		CodigoC << ("            	}\n");
		CodigoC << ("            if(x<Difusores[") << i << ("].var2&&x>=(Difusores[") << i << ("].var2+Difusores[") << i << ("].var1)/2){\n");
		CodigoC << ("            	ux=(x-Difusores[") << i << ("].var2)/(Difusores[") << i << ("].var2-Difusores[") << i << ("].var1);\n");
		CodigoC << ("            	ux=1-2*ux*ux;\n");
		CodigoC << ("            	}\n");
		CodigoC << ("            if(x<Difusores[") << i << ("].var3&&x>=Difusores[") << i << ("].var2){\n");
		CodigoC << ("            	ux=1;\n");
		CodigoC << ("            	}\n");
		CodigoC << ("            if(x<(Difusores[") << i << ("].var3+Difusores[") << i << ("].var4)/2&&x>=Difusores[") << i << ("].var3){\n");
		CodigoC << ("            	ux=(x-Difusores[") << i << ("].var3)/(Difusores[") << i << ("].var4-Difusores[") << i << ("].var3);\n");
		CodigoC << ("            	ux=1-2*ux*ux;\n");
		CodigoC << ("            	}\n");
		CodigoC << ("            if(x<Difusores[") << i << ("].var4&&x>=(Difusores[") << i << ("].var3+Difusores[") << i << ("].var2)/2){\n");
		CodigoC << ("            	ux=(x-Difusores[") << i << ("].var4)/(Difusores[") << i << ("].var4-Difusores[") << i << ("].var3);\n");
		CodigoC << ("            	ux=2*ux*ux;\n");
		CodigoC << ("            	}\n");
		CodigoC << ("            if(x>=Difusores[") << i << ("].var3)\n");
		CodigoC << ("            	ux=0;");
		return std::string(CodigoC.mb_str());
	}
	string codigo_CPP()
	{
		wxString CodigoCPP="";
		CodigoCPP=("    dif=new DifusorPiCampana(");
		CodigoCPP << centro() << (",") << menos1 << (",") << menos2 << (",") << mas1 << (",") << mas2 << (");");
		return std::string(CodigoCPP.mb_str());
	}
protected:
	double mas1;
	double mas2;
	double menos1;
	double menos2;
};


class DifusorSinglenton:public virtual ConjuntoSinglenton, public virtual Difusor
{
public:
	DifusorSinglenton(double x, double de):ConjuntoSinglenton("",x,de)
	{
		Centro=x;
		NumeroPuntos=1;
	}
	~DifusorSinglenton()
	{
	}
	void puntosClaves(double *x)
	{
		ConjuntoSinglenton::puntosClaves(x);
	}
	int numeroPuntosClaves()
	{
		return ConjuntoSinglenton::numeroPuntosClaves();
	}
	void entrada(double x1)
	{
		ConjuntoSinglenton::minimo(x1-delta()/2);
		ConjuntoSinglenton::maximo(x1+delta()/2);
		Centro=x1;
	}
	double pertenencia(double x)
	{
		return ConjuntoSinglenton::pertenencia(x);
	}
	double minimo()
	{
		return ConjuntoSinglenton::minimo();
	}
	double maximo()
	{
		return ConjuntoSinglenton::maximo();
	}
	void minimo(double mn)
	{
		ConjuntoSinglenton::minimo(mn);
	}
	void maximo(double mx)
	{
		ConjuntoSinglenton::maximo(mx);
	}
	string nombre()
	{
		return ConjuntoSinglenton::nombre();
	}
	string tipo()
	{
		return ConjuntoSinglenton::tipo();
	}
//	void recibirDatos(TWindow *parent,double mn,double mx);
	void ajustar(double nuevoMinimo, double nuevoMaximo)
	{
		ConjuntoSinglenton::ajustar(nuevoMinimo,nuevoMaximo);
		Pico=(maximo()+minimo())/2;
		Delta=maximo()-minimo();
		dx=(maximo()-minimo())/(NumeroPuntos+1);
	}
	double var1()
	{
		return minimo();
	}
	double var2()
	{
		return maximo();
	}
	double var3()
	{
		return 0;
	}
	double var4()
	{
		return 0;
	}
	int identificador()
	{
		return ConjuntoSinglenton::identificador();
	}
	string codigo_C(int i)
	{
		wxString CodigoC="";
		CodigoC << ("            if(x<Difusores[") << i << ("].var1)\n");
		CodigoC << ("            	ux=0;\n");
		CodigoC << ("            if(x<Difusores[") << i << ("].var2&&x>=Difusores[") << i << ("].var1)\n");
		CodigoC << ("            	ux=1;\n");
		CodigoC << ("            if(x>=Difusores[") << i << ("].var2)\n");
		CodigoC << ("            	ux=0;");
		return std::string(CodigoC.mb_str());
	}
	string codigo_CPP()
	{
		wxString CodigoCPP="";
		CodigoCPP=("    dif=new DifusorSinglenton(");
		CodigoCPP << centro() << (",") << ConjuntoSinglenton::delta() << (");");
		return std::string(CodigoCPP.mb_str());
	}
protected:
};

#endif

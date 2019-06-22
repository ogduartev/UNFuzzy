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
	float dx;
	float Centro;

procedimientos
	void numeroPuntos(int num)          modificador de NumeroPuntos, tambien cambia dx
	void ancho(float soporte)           permite editar el ancho del Difusor
	int numeroPuntos()                  consultor de NumeroPuntos
	float intervalo()                   consultor de dx
	float centro()                      consultor de Centro

procedimiento sin utilidad, que debe definirse por heredar virtual de ConjuntoDifuso

    float centroAltura()
	void nuevoPuntoClave(int, float )
	char *codigoC()
	char *codigoCPP()

Las funciones virtual=0 deben ser redefinidas por los hijos

	virtual void entrada(float)=0;      Cambia el centro del Difusor,
													 movienndo todos los parámetros
													 del padre, para cambiar su
													 función de pertenencia

estas funciones llaman a las del padre adecuado
	 para resolver las ambiguedades de tener herencia múltiple
	 pero con el mismo "abuelo"

	virtual void puntosClaves(float* )=0;
	virtual int numeroPuntosClaves()=0;
	virtual void ajustar(float nuevoMinimo,float nuevoMaximo)=0;
	virtual void recibirDatos(TWindow *parent, float mn, float mx)=0;
	virtual float pertenencia(float)=0;
	virtual float minimo()=0;
	virtual float maximo()=0;
	virtual void minimo(float mn)=0;
	virtual void maximo(float mx)=0;
	virtual char *nombre()=0;
	virtual char *tipo()=0;
	virtual float var1()=0;
	virtual float var2()=0;
	virtual float var3()=0;
	virtual float var4()=0;
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
	void ancho(float soporte)
	{
		float centro,mn,mx;
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
	float intervalo()
	{
		return dx;
	}
	float centro()
	{
		return Centro;
	}
	float centroAltura()
  {
      return 0.0;
  }
	virtual void puntosClaves(float* x)=0;
	virtual int numeroPuntosClaves()=0;
	void nuevoPuntoClave(int, float ){}
	virtual void entrada(float)=0;
	virtual void ajustar(float nuevoMinimo,float nuevoMaximo)=0;
//	virtual void recibirDatos(TWindow *parent, float mn, float mx)=0;
	virtual float pertenencia(float)=0;
	virtual float minimo()=0;
	virtual float maximo()=0;
	virtual void minimo(float mn)=0;
	virtual void maximo(float mx)=0;
	virtual string nombre()=0;
	virtual string tipo()=0;
	virtual float var1()=0;
	virtual float var2()=0;
	virtual float var3()=0;
	virtual float var4()=0;
	virtual int identificador()=0;
	string codigoC(){return "";}
	string codigoCPP(){return "";}
	virtual string codigo_C(int i)=0;
	virtual string codigo_CPP()=0;
protected:
	int NumeroPuntos;
	float dx;
	float Centro;
};

class DifusorTriangulo:public virtual ConjuntoTriangulo,public virtual Difusor
{
public:
	DifusorTriangulo(float x, float me, float ma):ConjuntoTriangulo("",x-me,x,x+ma)
	{
		Centro=x;
		menos=me;
		mas=ma;
		NumeroPuntos=3;
	}
	~DifusorTriangulo()
	{
	}
	void puntosClaves(float *x)
	{
		ConjuntoTriangulo::puntosClaves(x);
	}
	int numeroPuntosClaves()
	{
		return ConjuntoTriangulo::numeroPuntosClaves();
	}
	void entrada(float x1)
	{
		ConjuntoTriangulo::minimo(x1-menos);
		ConjuntoTriangulo::maximo(x1+mas);
		ConjuntoTriangulo::primerCorte(x1);
		Centro=x1;
	}
	float pertenencia(float x)
	{
		return ConjuntoTriangulo::pertenencia(x);
	}
	float minimo()
	{
		return ConjuntoTriangulo::minimo();
	}
	float maximo()
	{
		return ConjuntoTriangulo::maximo();
	}
	float primerCorte()
	{
		return ConjuntoTriangulo::primerCorte();
	}
	void primerCorte(float pc)
	{
		ConjuntoTriangulo::primerCorte(pc);
	}
	void minimo(float mn)
	{
		ConjuntoTriangulo::minimo(mn);
	}
	void maximo(float mx)
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
//	void recibirDatos(TWindow *parent,float mn,float mx);
	void ajustar(float nuevoMinimo, float nuevoMaximo)
	{
		ConjuntoTriangulo::ajustar(nuevoMinimo,nuevoMaximo);
		menos=primerCorte()-minimo();
		mas=maximo()-primerCorte();
		dx=(maximo()-minimo())/(NumeroPuntos+1);
	}
	float var1()
	{
		return minimo();
	}
	float var2()
	{
		return primerCorte();
	}
	float var3()
	{
		return maximo();
	}
	float var4()
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
	float mas;
	float menos;
};

class DifusorPi:public virtual ConjuntoPi,public virtual Difusor
{
public:
	DifusorPi(float x, float me1, float me2, float ma1, float ma2):ConjuntoPi("",x-me1,x-me2,x+ma1,x+ma2)
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
	void puntosClaves(float *x)
	{
		ConjuntoPi::puntosClaves(x);
	}
	int numeroPuntosClaves()
	{
		return ConjuntoPi::numeroPuntosClaves();
	}
	void entrada(float x1)
	{
		ConjuntoPi::minimo(x1-menos1);
		ConjuntoPi::maximo(x1+mas2);
		ConjuntoPi::primerCorte(x1-menos2);
		ConjuntoPi::segundoCorte(x1+mas1);
		Centro=x1;
	}
	float pertenencia(float x)
	{
		return ConjuntoPi::pertenencia(x);
	}
	float minimo()
	{
		return ConjuntoPi::minimo();
	}
	float maximo()
	{
		return ConjuntoPi::maximo();
	}
	float primerCorte()
	{
		return ConjuntoPi::primerCorte();
	}
	float segundoCorte()
	{
		return ConjuntoPi::segundoCorte();
	}
	void primerCorte(float pc)
	{
		ConjuntoPi::primerCorte(pc);
	}
	void segundoCorte(float sc)
	{
		ConjuntoPi::segundoCorte(sc);
	}
	void minimo(float mn)
	{
		ConjuntoPi::minimo(mn);
	}
	void maximo(float mx)
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
//	void recibirDatos(TWindow *parent,float mn,float mx);
	void ajustar(float nuevoMinimo, float nuevoMaximo)
	{
		ConjuntoPi::ajustar(nuevoMinimo,nuevoMaximo);
		menos1=centro()-minimo();
		menos2=centro()-primerCorte();
		mas1=segundoCorte()-centro();;
		mas2=maximo()-centro();
		dx=(maximo()-minimo())/(NumeroPuntos+1);
	}
	float var1()
	{
		return minimo();
	}
	float var2()
	{
		return primerCorte();
	}
	float var3()
	{
		return segundoCorte();
	}
	float var4()
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
	float mas1;
	float mas2;
	float menos1;
	float menos2;
};

class DifusorCampana:public virtual ConjuntoCampana,public virtual Difusor
{
public:
	DifusorCampana(float x, float me, float ma):ConjuntoCampana("",x-me,x,x+ma)
	{
		Centro=x;
		menos=me;
		mas=ma;
		NumeroPuntos=5;
	}
	~DifusorCampana()
	{
	}
	void puntosClaves(float *x)
	{
		ConjuntoCampana::puntosClaves(x);
	}
	int numeroPuntosClaves()
	{
		return ConjuntoCampana::numeroPuntosClaves();
	}
	void entrada(float x1)
	{
		ConjuntoCampana::minimo(x1-menos);
		ConjuntoCampana::maximo(x1+mas);
		ConjuntoCampana::primerCorte(x1);
		Centro=x1;
	}
	float pertenencia(float x)
	{
		return ConjuntoCampana::pertenencia(x);
	}
	float minimo()
	{
		return ConjuntoCampana::minimo();
	}
	float maximo()
	{
		return ConjuntoCampana::maximo();
	}
	float primerCorte()
	{
		return ConjuntoCampana::primerCorte();
	}
	void primerCorte(float pc)
	{
		ConjuntoCampana::primerCorte(pc);
	}
	void minimo(float mn)
	{
		ConjuntoCampana::minimo(mn);
	}
	void maximo(float mx)
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
//	void recibirDatos(TWindow *parent,float mn,float mx);
	void ajustar(float nuevoMinimo, float nuevoMaximo)
	{
		ConjuntoCampana::ajustar(nuevoMinimo,nuevoMaximo);
		menos=primerCorte()-minimo();
		mas=maximo()-primerCorte();
		dx=(maximo()-minimo())/(NumeroPuntos+1);
	}
	float var1()
	{
		return minimo();
	}
	float var2()
	{
		return primerCorte();
	}
	float var3()
	{
		return maximo();
	}
	float var4()
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
	float mas;
	float menos;
};

class DifusorPiCampana:public virtual ConjuntoPiCampana,public virtual Difusor
{
public:
	DifusorPiCampana(float x, float me1, float me2, float ma1, float ma2):ConjuntoPiCampana("",x-me1,x-me2,x+ma1,x+ma2)
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
	void puntosClaves(float *x)
	{
		ConjuntoPiCampana::puntosClaves(x);
	}
	int numeroPuntosClaves()
	{
		return ConjuntoPiCampana::numeroPuntosClaves();
	}
	void entrada(float x1)
	{
		ConjuntoPiCampana::minimo(x1-menos1);
		ConjuntoPiCampana::maximo(x1+mas2);
		ConjuntoPiCampana::primerCorte(x1-menos2);
		ConjuntoPiCampana::segundoCorte(x1+mas1);
		Centro=x1;
	}
	float pertenencia(float x)
	{
		return ConjuntoPiCampana::pertenencia(x);
	}
	float minimo()
	{
		return ConjuntoPiCampana::minimo();
	}
	float maximo()
	{
		return ConjuntoPiCampana::maximo();
	}
	float primerCorte()
	{
		return ConjuntoPiCampana::primerCorte();
	}
	float segundoCorte()
	{
		return ConjuntoPiCampana::segundoCorte();
	}
	void primerCorte(float pc)
	{
		ConjuntoPiCampana::primerCorte(pc);
	}
	void segundoCorte(float sc)
	{
		ConjuntoPiCampana::segundoCorte(sc);
	}
	void minimo(float mn)
	{
		ConjuntoPiCampana::minimo(mn);
	}
	void maximo(float mx)
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
//	void recibirDatos(TWindow *parent,float mn,float mx);
	void ajustar(float nuevoMinimo, float nuevoMaximo)
	{
		ConjuntoPiCampana::ajustar(nuevoMinimo,nuevoMaximo);
		menos1=centro()-minimo();
		menos2=centro()-primerCorte();
		mas1=segundoCorte()-centro();;
		mas2=maximo()-centro();
		dx=(maximo()-minimo())/(NumeroPuntos+1);
	}
	float var1()
	{
		return minimo();
	}
	float var2()
	{
		return primerCorte();
	}
	float var3()
	{
		return segundoCorte();
	}
	float var4()
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
	float mas1;
	float mas2;
	float menos1;
	float menos2;
};


class DifusorSinglenton:public virtual ConjuntoSinglenton, public virtual Difusor
{
public:
	DifusorSinglenton(float x, float de):ConjuntoSinglenton("",x,de)
	{
		Centro=x;
		NumeroPuntos=1;
	}
	~DifusorSinglenton()
	{
	}
	void puntosClaves(float *x)
	{
		ConjuntoSinglenton::puntosClaves(x);
	}
	int numeroPuntosClaves()
	{
		return ConjuntoSinglenton::numeroPuntosClaves();
	}
	void entrada(float x1)
	{
		ConjuntoSinglenton::minimo(x1-delta()/2);
		ConjuntoSinglenton::maximo(x1+delta()/2);
		Centro=x1;
	}
	float pertenencia(float x)
	{
		return ConjuntoSinglenton::pertenencia(x);
	}
	float minimo()
	{
		return ConjuntoSinglenton::minimo();
	}
	float maximo()
	{
		return ConjuntoSinglenton::maximo();
	}
	void minimo(float mn)
	{
		ConjuntoSinglenton::minimo(mn);
	}
	void maximo(float mx)
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
//	void recibirDatos(TWindow *parent,float mn,float mx);
	void ajustar(float nuevoMinimo, float nuevoMaximo)
	{
		ConjuntoSinglenton::ajustar(nuevoMinimo,nuevoMaximo);
		Pico=(maximo()+minimo())/2;
		Delta=maximo()-minimo();
		dx=(maximo()-minimo())/(NumeroPuntos+1);
	}
	float var1()
	{
		return minimo();
	}
	float var2()
	{
		return maximo();
	}
	float var3()
	{
		return 0;
	}
	float var4()
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

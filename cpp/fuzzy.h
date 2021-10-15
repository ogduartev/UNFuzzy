#ifndef __FUZZY_H
#define __FUZZY_H
#endif

#ifndef __IOSTREAM_H
#include <iostream>
#endif

#ifndef __STRING_H
#include<string.h>
#endif

#ifndef __STDIO_H
#include<stdio.h>
#endif

#ifndef __MATH_H
#include<math.h>
#endif

using namespace std;

template<class T>
class Arreglo
{
public:
	Arreglo(int sz=10)
	{
		init(sz);
	}
	virtual ~Arreglo(void)
	{
		delete [] data;
	}
	void Add(T* dato);
	int size(void) const;
	int GetItemsInContainer(void) const;
	T *dato(int index);
	void Destroy(int index);
	void Detach(int index);
private:
	int n;
	int items;
	T **data;
	void init(int sz);
};

template <class T>
void Arreglo<T>::init (int sz)
{
	if(sz<1)
	{
		sz=1;
	}
	n=sz;
	items=0;
	data=new T*[n];
}

template <class T>
int Arreglo<T>::size (void ) const
{
	return (n);
}

template <class T>
int Arreglo<T>::GetItemsInContainer (void ) const
{
	return (items);
}

template <class T>
T *Arreglo<T>::dato (int index)
{
	if (index <0){index=0;}
	if (index >=n){index=n-1;}
	return (data[index]);
}

template <class T>
void Arreglo<T>::Add(T* dato)
{
	items++;
	if(items>n)
	{
		T** temp;
		temp=new T*[items];
		n=items;
		int i;
		for(i=0;i<items-1;i++)
		{
			temp[i]=data[i];
		}
		delete [] data;
		data=temp;
	}
	data[items-1]=dato;
}

template <class T>
void Arreglo<T>::Destroy (int index)
{
	T* temp;
	temp=dato(index);
	delete temp;
	int i;
	for(i=index;i<items;i++)
	{
		data[i]=data[i+1];
	}
	items--;
}

template <class T>
void Arreglo<T>::Detach (int index)
{
	int i;
	for(i=index;i<items;i++)
	{
		data[i]=data[i+1];
	}
	items--;
}

typedef int BOOL;

class ConjuntoDifuso
{
public:
	ConjuntoDifuso(){}
	virtual ~ConjuntoDifuso(){}
	void minimo(double min)
	{
		Minimo=min;
	}
	double minimo()
	{
		return Minimo;
	}
	void maximo(double max)
	{
		Maximo=max;
	}
	double maximo()
	{
		return Maximo;
	}
	int identificador()
	{
		return Identificador;
	}
	int numeroPuntosClaves()
	{
		return NumeroPuntosClaves;
	}
	virtual void puntosClaves(double *puntos)=0;
	virtual void nuevoPuntoClave(int punto, double x)=0;
	virtual double pertenencia(double x)=0;
	virtual double centroAltura()=0;
	BOOL operator==(const ConjuntoDifuso& other)
	{
		return (( Minimo == other.Minimo)&
		( Maximo == other.Maximo) );
	}
protected:
	double Minimo;
	double Maximo;
	int NumeroPuntosClaves;
	int Identificador;
};


class ConjuntoL: public ConjuntoDifuso
{
public:
	ConjuntoL(double min, double pcor, double max)
	{
		Minimo=min;
		PrimerCorte=pcor;
		Maximo=max;
		NumeroPuntosClaves=2;
		Identificador=0;
	}
	~ConjuntoL(){}
	double pertenencia(double);
	void puntosClaves(double *puntos)
	{
		puntos[0]=primerCorte();
		puntos[1]=maximo();
	}
	void nuevoPuntoClave(int punto, double x);
	double centroAltura()
	{
		return((Minimo+PrimerCorte)/2.0);
	}
protected:
	double PrimerCorte;
	void primerCorte(double pcor)
	{
		PrimerCorte=pcor;
	}
	double primerCorte()
	{
		return PrimerCorte;
	}
};

class ConjuntoTriangulo: public ConjuntoDifuso
{
public:
	ConjuntoTriangulo(double min, double pcor, double max)
	{
		Minimo=min;
		PrimerCorte=pcor;
		Maximo=max;
		NumeroPuntosClaves=3;
		Identificador=1;
	}
	~ConjuntoTriangulo(){}
	double pertenencia(double);
	void puntosClaves(double *puntos)
	{
		puntos[0]=minimo();
		puntos[1]=primerCorte();
		puntos[2]=maximo();
	}
	void nuevoPuntoClave(int punto, double x);
	double centroAltura()
	{
		return(PrimerCorte);
	}
protected:
	double PrimerCorte;
	void primerCorte(double pcor)
	{
		PrimerCorte=pcor;
	}
	double primerCorte()
	{
		return PrimerCorte;
	}
};

class ConjuntoPi: public ConjuntoDifuso
{
public:
	ConjuntoPi(double min, double pcor, double scor, double max)
	{
		Minimo=min;
		PrimerCorte=pcor;
		SegundoCorte=scor;
		Maximo=max;
		NumeroPuntosClaves=4;
		Identificador=2;
	}
	~ConjuntoPi(){}
	double pertenencia(double x);
	void puntosClaves(double *puntos)
	{
		puntos[0]=minimo();
		puntos[1]=primerCorte();
		puntos[2]=segundoCorte();
		puntos[3]=maximo();
	}
	void nuevoPuntoClave(int punto, double x);
	double centroAltura()
	{
		return((PrimerCorte+SegundoCorte)/2.0);
	}
protected:
	double PrimerCorte;
	double SegundoCorte;
	void primerCorte(double pcor)
	{
		PrimerCorte=pcor;
	}
	double primerCorte()
	{
		return PrimerCorte;
	}
	void segundoCorte(double scor)
	{
		SegundoCorte=scor;
	}
	double segundoCorte()
	{
		return SegundoCorte;
	}
};

class ConjuntoGamma: public ConjuntoDifuso
{
public:
	ConjuntoGamma(double min, double pcor,  double max)
	{
		Minimo=min;
		PrimerCorte=pcor;
		Maximo=max;
		NumeroPuntosClaves=2;
		Identificador=3;
	}
	~ConjuntoGamma(){}
	double pertenencia(double);
	void puntosClaves(double *puntos)
	{
		puntos[0]=minimo();
		puntos[1]=primerCorte();
	}
	void nuevoPuntoClave(int punto, double x);
	double centroAltura()
	{
		return((Maximo+PrimerCorte)/2.0);
	}
protected:
	double PrimerCorte;
	void primerCorte(double pcor)
	{
		PrimerCorte=pcor;
	}
	double primerCorte()
	{
		return PrimerCorte;
	}
};

class ConjuntoZ: public ConjuntoDifuso
{
public:
	ConjuntoZ(double min, double pcor, double max)
	{
		Minimo=min;
		PrimerCorte=pcor;
		Maximo=max;
		NumeroPuntosClaves=2;
		Identificador=4;
	}
	~ConjuntoZ(){}
	double pertenencia(double);
	void puntosClaves(double *puntos)
	{
		puntos[0]=primerCorte();
		puntos[1]=maximo();
	}
	void nuevoPuntoClave(int punto, double x);
	double centroAltura()
	{
		return((Minimo+PrimerCorte)/2.0);
	}
protected:
	double PrimerCorte;
	void primerCorte(double pcor)
	{
		PrimerCorte=pcor;
	}
	double primerCorte()
	{
		return PrimerCorte;
	}
};

class ConjuntoCampana: public ConjuntoDifuso
{
public:
	ConjuntoCampana(double min, double pcor, double max)
	{
		Minimo=min;
		PrimerCorte=pcor;
		Maximo=max;
		NumeroPuntosClaves=3;
		Identificador=5;
	}
	~ConjuntoCampana(){}
	double pertenencia(double);
	void puntosClaves(double *puntos)
	{
		puntos[0]=minimo();
		puntos[1]=primerCorte();
		puntos[2]=maximo();
	}
	void nuevoPuntoClave(int punto, double x);
	double centroAltura()
	{
		return(PrimerCorte);
	}
protected:
	double PrimerCorte;
	void primerCorte(double pcor)
	{
		PrimerCorte=pcor;
	}
	double primerCorte()
	{
		return PrimerCorte;
	}
};

class ConjuntoS: public ConjuntoDifuso
{
public:
	ConjuntoS(double min, double pcor, double max)
	{
		Minimo=min;
		PrimerCorte=pcor;
		Maximo=max;
		NumeroPuntosClaves=2;
		Identificador=6;
	}
	~ConjuntoS(){}
	double pertenencia(double);
	void puntosClaves(double *puntos)
	{
		puntos[0]=minimo();
		puntos[1]=primerCorte();
	}
	void nuevoPuntoClave(int punto, double x);
	double centroAltura()
	{
		return((Maximo+PrimerCorte)/2.0);
	}
protected:
	double PrimerCorte;
	void primerCorte(double pcor)
	{
		PrimerCorte=pcor;
	}
	double primerCorte()
	{
		return PrimerCorte;
	}
};

class ConjuntoPiCampana: public ConjuntoDifuso
{
public:
	ConjuntoPiCampana(double min, double pcor, double scor, double max)
	{
		Minimo=min;
		PrimerCorte=pcor;
		SegundoCorte=scor;
		Maximo=max;
		NumeroPuntosClaves=4;
		Identificador=7;
	}
	~ConjuntoPiCampana(){}
	double pertenencia(double);
	void puntosClaves(double *puntos)
	{
		puntos[0]=minimo();
		puntos[1]=primerCorte();
		puntos[2]=segundoCorte();
		puntos[3]=maximo();
	}
	void nuevoPuntoClave(int punto, double x);
	double centroAltura()
	{
		return((PrimerCorte+SegundoCorte)/2.0);
	}
protected:
	double PrimerCorte;
	double SegundoCorte;
	void primerCorte(double pcor)
	{
		PrimerCorte=pcor;
	}
	double primerCorte()
	{
		return PrimerCorte;
	}
	void segundoCorte(double scor)
	{
		SegundoCorte=scor;
	}
	double segundoCorte()
	{
		return SegundoCorte;
	}
};


class ConjuntoSinglenton: public ConjuntoDifuso
{
public:
	ConjuntoSinglenton(double pi, double de)
	{
		Pico=pi;
		Delta=de;
		Minimo=Pico-Delta/2;
		Maximo=Pico+Delta/2;
		NumeroPuntosClaves=2;
		Identificador=8;
	}
	~ConjuntoSinglenton(){}
	double pertenencia(double);
	void puntosClaves(double *puntos)
	{
		puntos[0]=minimo();
		puntos[1]=maximo();
	}
	void nuevoPuntoClave(int punto, double x);
	double centroAltura()
	{
		return(Pico);
	}
protected:
	double pico(){return Pico;}
	double delta(){return Delta;}
	double Delta;
	double Pico;
};

inline double ConjuntoL::pertenencia(double x)
{
	double ux;
	if(x<minimo())
		ux=1;
	if(x<primerCorte()&&x>=minimo())
		ux=1;
	if(x<maximo()&&x>=primerCorte())
		ux=(maximo()-x)/(maximo()-primerCorte());
	if(x>=maximo())
		ux=0;
	if(ux<0.0001)
		ux=0;
	return ux ;
}


inline double ConjuntoTriangulo::pertenencia(double x)
{
	double ux;
	if(x<minimo())
		ux=0;
	if(x<primerCorte()&&x>=minimo())
		ux=(x-minimo())/(primerCorte()-minimo());
	if(x<maximo()&&x>=primerCorte())
		ux=(maximo()-x)/(maximo()-primerCorte());
	if(x>=maximo())
		ux=0;
	if(ux<0.0001)
		ux=0;
	return ux ;
}


inline double ConjuntoPi::pertenencia(double x)
{
	double ux;
	if(x<minimo())
		ux=0;
	if(x<primerCorte()&&x>=minimo())
		ux=(x-minimo())/(primerCorte()-minimo());
	if(x<segundoCorte()&&x>=primerCorte())
		ux=1;
	if(x<maximo()&&x>=segundoCorte())
		ux=(maximo()-x)/(maximo()-segundoCorte());
	if(x>=maximo())
		ux=0;
	if(ux<0.0001)
		ux=0;
	return ux ;
}


inline double ConjuntoGamma::pertenencia(double x)
{
	double ux;
	if(x<minimo())
		ux=0;
	if(x<primerCorte()&&x>=minimo())
		ux=(x-minimo())/(primerCorte()-minimo());
	if(x<maximo()&&x>=primerCorte())
		ux=1;
	if(x>=maximo())
		ux=1;
	if(ux<0.0001)
		ux=0;
	return ux ;
}

inline double ConjuntoZ::pertenencia(double x)
{
	double ux;
	if(x<minimo())
		ux=1;
	if(x<primerCorte())
		ux=1;
	if(x<(primerCorte()+maximo())/2&&x>=primerCorte())
		{
			ux=(x-primerCorte())/(maximo()-primerCorte());
			ux=1-2*ux*ux;
		}
	if(x<maximo()&&x>=(primerCorte()+maximo())/2)
		{
			ux=(x-maximo())/(maximo()-primerCorte());
			ux=2*ux*ux;
		}
	if(x>=maximo())
		ux=0;
	if(ux<0.0001)
		ux=0;
	return ux ;
}

inline double ConjuntoCampana::pertenencia(double x)
{
	double ux;
	if(x<minimo())
		ux=0;
	if(x<(primerCorte()+minimo())/2&&x>=minimo())
		{
			ux=(x-minimo())/(primerCorte()-minimo());
			ux=2*ux*ux;
		}
	if(x<primerCorte()&&x>=(primerCorte()+minimo())/2)
		{
			ux=(x-primerCorte())/(primerCorte()-minimo());
			ux=1-2*ux*ux;
		}
	if(x<(primerCorte()+maximo())/2&&x>=primerCorte())
		{
			ux=(x-primerCorte())/(maximo()-primerCorte());
			ux=1-2*ux*ux;
		}
	if(x<maximo()&&x>=(primerCorte()+maximo())/2)
		{
			ux=(x-maximo())/(maximo()-primerCorte());
			ux=2*ux*ux;
		}
	if(x>=maximo())
		ux=0;
	if(ux<0.0001)
		ux=0;
	return ux ;
}


inline double ConjuntoS::pertenencia(double x)
{
	double ux;
	if(x<minimo())
		ux=0;
	if(x<(primerCorte()+minimo())/2&&x>=minimo())
		{
			ux=(x-minimo())/(primerCorte()-minimo());
			ux=2*ux*ux;
		}
	if(x<primerCorte()&&x>=(primerCorte()+minimo())/2)
		{
			ux=(x-primerCorte())/(primerCorte()-minimo());
			ux=1-2*ux*ux;
		}
	if(x>=primerCorte())
		ux=1;
	if(ux<0.0001)
		ux=0;
	return ux ;
}

inline double ConjuntoPiCampana::pertenencia(double x)
{
	double ux;
	if(x<minimo())
		ux=0;
	if(x<(primerCorte()+minimo())/2&&x>=minimo())
		{
			ux=(x-minimo())/(primerCorte()-minimo());
			ux=2*ux*ux;
		}
	if(x<primerCorte()&&x>=(primerCorte()+minimo())/2)
		{
			ux=(x-primerCorte())/(primerCorte()-minimo());
			ux=1-2*ux*ux;
		}
	if(x<segundoCorte()&&x>=primerCorte())
		ux=1;
	if(x<(segundoCorte()+maximo())/2&&x>=segundoCorte())
		{
			ux=(x-segundoCorte())/(maximo()-segundoCorte());
			ux=1-2*ux*ux;
		}
	if(x<maximo()&&x>=(segundoCorte()+maximo())/2)
		{
			ux=(x-maximo())/(maximo()-segundoCorte());
			ux=2*ux*ux;
		}
	if(x>=maximo())
		ux=0;
	if(ux<0.0001)
		ux=0;
	return ux ;
}


inline double ConjuntoSinglenton::pertenencia(double x)
{
	double ux;
	if(x<minimo())
		ux=0;
	if(x<maximo()&&x>=minimo())
		ux=1;
	if(x>=maximo())
		ux=0;
	if(ux<0.0001)
		ux=0;
	return ux ;
}



////////////////////////////////////////

class Difusor:public ConjuntoDifuso
{
public:
	Difusor()
	{
		NumeroPuntos=1;
	}
	~Difusor()
	{}
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
	double centroAltura(){return 0.0;}
	virtual double pertenencia(double)=0;
	virtual double minimo()=0;
	virtual double maximo()=0;
	virtual void minimo(double mn)=0;
	virtual void maximo(double mx)=0;
	virtual void entrada(double)=0;
	void puntosClaves(double* ){}
	void nuevoPuntoClave(int, double ){}
protected:
	int NumeroPuntos;
	double dx;
	double Centro;
};

class DifusorTriangulo:public virtual ConjuntoTriangulo,public virtual Difusor
{
public:
	DifusorTriangulo(double x, double me, double ma):ConjuntoTriangulo(x-me,x,x+ma)
	{
		Centro=x;
		menos=me;
		mas=ma;
	}
	~DifusorTriangulo()
	{
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
protected:
	double mas;
	double menos;
};

class DifusorPi:public virtual ConjuntoPi,public virtual Difusor
{
public:
	DifusorPi(double x, double me1, double me2, double ma1, double ma2):ConjuntoPi(x-me1,x-me2,x+ma1,x+ma2)
	{
		Centro=x;
		menos1=me1;
		menos2=me2;
		mas1=ma1;
		mas2=ma2;
	}
	~DifusorPi()
	{
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
protected:
	double mas1;
	double mas2;
	double menos1;
	double menos2;
};

class DifusorCampana:public virtual ConjuntoCampana,public virtual Difusor
{
public:
	DifusorCampana(double x, double me, double ma):ConjuntoCampana(x-me,x,x+ma)
	{
		Centro=x;
		menos=me;
		mas=ma;
	}
	~DifusorCampana()
	{
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
protected:
	double mas;
	double menos;
};

class DifusorPiCampana:public virtual ConjuntoPiCampana,public virtual Difusor
{
public:
	DifusorPiCampana(double x, double me1, double me2, double ma1, double ma2):ConjuntoPiCampana(x-me1,x-me2,x+ma1,x+ma2)
	{
		Centro=x;
		menos1=me1;
		menos2=me2;
		mas1=ma1;
		mas2=ma2;
	}
	~DifusorPiCampana()
	{
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
protected:
	double mas1;
	double mas2;
	double menos1;
	double menos2;
};


class DifusorSinglenton:public virtual ConjuntoSinglenton, public virtual Difusor
{
public:
	DifusorSinglenton(double x, double de):ConjuntoSinglenton(x,de)
	{
		Centro=x;
	}
	~DifusorSinglenton()
	{
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
protected:
};

////////////////////////////////////

class Variable
{
public:
	Variable(int num=10)
	{
		Conjuntos = new ListaConjuntos(num);
		DifusorEntrada= new DifusorTriangulo(0.0,0.1,0.1);
		NombreVariable="";
	}
	~Variable();
	Difusor *difusorEntrada()
	{
		return DifusorEntrada;
	}
	void difusorEntrada(Difusor *dif)
	{
		delete DifusorEntrada;
		DifusorEntrada=dif;
	}
	string nombreVariable()
	{
		return NombreVariable;
	}
	void nombreVariable(string s)
	{
		NombreVariable=s;
	}
	void adicionarConjuntos(ConjuntoDifuso* cd)
	{
		Conjuntos->Add(cd);
	}
	void eliminarConjuntos(int cd)
	{
		Conjuntos->Destroy(cd);
	}
	void limpiarListaConjuntos();
	int numeroConjuntos()
	{
		return Conjuntos->GetItemsInContainer();
	}
	void numeroIntervalos(int num)
	{
		NumeroIntervalos=num;
		Intervalo=(rangoMaximo()-rangoMinimo())/(NumeroIntervalos);
	}
	int numeroIntervalos()
	{
		return NumeroIntervalos;
	}
	double intervalo()
	{
		return Intervalo;
	}

	ConjuntoDifuso* conjunto(int conj);
	double pertenencia(ConjuntoDifuso*, double);
	double pertenencia(int, double);
	double pertenenciaDifusor(double);
	double rangoMinimo(){return RangoMinimo;}
	void rangoMinimo(double rm){RangoMinimo=rm;}
	double rangoMaximo(){return RangoMaximo;}
	void rangoMaximo(double rm){RangoMaximo=rm;}
	BOOL operator==(const Variable& other)
	{
		return ( (NombreVariable == other.NombreVariable)&
		( RangoMinimo == other.RangoMinimo)&
		( RangoMaximo == other.RangoMaximo)&
		( DifusorEntrada == other.DifusorEntrada)&
		( Conjuntos == other.Conjuntos) );
	}
protected:
	typedef Arreglo<ConjuntoDifuso> ListaConjuntos;

	ListaConjuntos *Conjuntos;
	Difusor *DifusorEntrada;
	double RangoMinimo;
	double RangoMaximo;
	int NumeroIntervalos;
	double Intervalo;
	string NombreVariable;
};

class Universo
{
public:
	Universo(int num=10)
	{
		Variables=new ListaVariables(num);
	}
	~Universo();
	void adicionarVariable(Variable *var)
	{
		Variables->Add(var);
	}
	void eliminarVariable(int var)
	{
		Variables->Destroy(var);
	}
	int numeroVariables()
	{
		return Variables->GetItemsInContainer();
	}
	Variable *variable(int numVar);
	void limpiarListaVariables();
	Difusor *difusor(int num);
	double intervaloDifusor(int numVar)
	{
		Difusor *dif;
		dif=difusor(numVar);
		return dif->intervalo();
	}
	void numeroPuntosDifusor(int numVar,int numPuntos)
	{
		Difusor *dif;
		dif=difusor(numVar);
		dif->numeroPuntos(numPuntos);
	}
	int numeroPuntosDifusor(int numVar)
	{
		Difusor *dif;
		dif=difusor(numVar);
		return dif->numeroPuntos();
	}
	double pertenenciaDifusor(int numVar, double x)
	{
		Variable *var;
		var=variable(numVar);
		return pertenenciaDifusor(var,x);
	}
	string nombreVariable(int numVar)
	{
		Variable *var;
		var=variable(numVar);
		return nombreVariable(var);
	}
	void nombreVariable(string nom,int numVar)
	{
		Variable *var;
		var=variable(numVar);
		nombreVariable(nom,var);
	}
	void entradaReal(int numVar, double x)
	{
		Difusor *dif;
		dif=difusor(numVar);
		entradaReal(dif,x);
	}
	void entradaReal(double *ent);
	int numeroConjuntosEnVariable(int numVar)
	{
		Variable *var;
		var=variable(numVar);
		return numeroConjuntosEnVariable (var);
	}
	int numeroIntervalosEnVariable(int numVar)
	{
		Variable *var;
		var=variable(numVar);
		return numeroIntervalosEnVariable (var);
	}
	void numeroIntervalosEnVariable(int numVar,int intervalos)
	{
		Variable *var;
		var=variable(numVar);
		var->numeroIntervalos(intervalos);
	}
	double intervaloEnVariable(int numVar)
	{
		Variable *var;
		var=variable(numVar);
		return intervaloEnVariable (var);
	}
	ConjuntoDifuso *conjuntoEnVariable(int numVar, int numCon)
	{
		Variable *var;
		var=variable(numVar);
		return conjuntoEnVariable(var,numCon);
	}
	double rangoMinimoVariable(int numVar)
	{
		Variable *var;
		var=variable(numVar);
		return rangoMinimoVariable(var);
	}
	void rangoMinimoVariable(double rm,int numVar)
	{
		Variable *var;
		var=variable(numVar);
		rangoMinimoVariable(rm,var);
	}
	double rangoMaximoVariable(int numVar)
	{
		Variable *var;
		var=variable(numVar);
		return rangoMaximoVariable(var);
	}
	void rangoMaximoVariable(double rm,int numVar)
	{
		Variable *var;
		var=variable(numVar);
		rangoMaximoVariable(rm,var);
	}
	double minimoEnConjunto(int numVar, int numCon)
	{
		ConjuntoDifuso *cd;
		cd=conjuntoEnVariable(numVar, numCon);
		return minimoEnConjunto(cd);
	}
	double maximoEnConjunto(int numVar, int numCon)
	{
		ConjuntoDifuso *cd;
		cd=conjuntoEnVariable(numVar, numCon);
		return maximoEnConjunto(cd);
	}
	double minimoEnDifusor(int numVar)
	{
		Difusor *dif;
		dif=difusor(numVar);
		return minimoEnDifusor(dif);
	}
	double maximoEnDifusor(int numVar)
	{
		Difusor *dif;
		dif=difusor(numVar);
		return maximoEnDifusor(dif);
	}
	double pertenenciaVariable(int numVar, int numCon, double x)
	{
		ConjuntoDifuso *cd;
		cd=conjuntoEnVariable(numVar, numCon);
		return pertenenciaVariable(cd,x);
	}
	double centroEnDifusor(int numVar)
	{
		double x;
		x=difusor(numVar)->centro();;
		return x;
	}

protected:
	typedef Arreglo<Variable> ListaVariables;

	ListaVariables *Variables;

private:
	Difusor *difusor(Variable *var)
	{
		return var->difusorEntrada();
	}
	double pertenenciaDifusor(Variable *var, double x)
	{
		return var->pertenenciaDifusor(x);
	}
	string nombreVariable(Variable *var)
	{
		return var->nombreVariable();
	}
	void nombreVariable(string nom,Variable *var)
	{
		var->nombreVariable(nom);
	}
	void entradaReal(Difusor *dif, double x)
	{
		dif->entrada(x);
	}
	void entradaReal(Variable *var,double x)
	{
		Difusor *dif;
		dif=var->difusorEntrada();
		dif->entrada(x);
	}
	int numeroConjuntosEnVariable(Variable *var)
	{
		return var->numeroConjuntos();
	}
	int numeroIntervalosEnVariable(Variable *var)
	{
		return var->numeroIntervalos();
	}
	double intervaloEnVariable(Variable *var)
	{
		return var->intervalo();
	}
	ConjuntoDifuso *conjuntoEnVariable(Variable *var, int numCon)
	{
		return var->conjunto(numCon);
	}
	double rangoMinimoVariable(Variable *var)
	{
		return var->rangoMinimo();
	}
	void rangoMinimoVariable(double rm,Variable *var)
	{
		var->rangoMinimo(rm);
	}
	double rangoMaximoVariable(Variable *var)
	{
		return var->rangoMaximo();
	}
	void rangoMaximoVariable(double rm,Variable *var)
	{
		var->rangoMaximo(rm);
	}
	double minimoEnConjunto(Variable *var, int numCon)
	{
		ConjuntoDifuso *cd;
		cd=conjuntoEnVariable(var, numCon);
		return minimoEnConjunto(cd);
	}
	double minimoEnConjunto(ConjuntoDifuso *cd)
	{
		return cd->minimo();
	}
	double maximoEnConjunto(Variable *var, int numCon)
	{
		ConjuntoDifuso *cd;
		cd=conjuntoEnVariable(var, numCon);
		return maximoEnConjunto(cd);
	}
	double maximoEnConjunto(ConjuntoDifuso *cd)
	{
		return cd->maximo();
	}
	double minimoEnDifusor(Variable *var)
	{
		Difusor *dif;
		dif=difusor(var);
		return minimoEnDifusor(dif);
	}
	double minimoEnDifusor(Difusor *dif)
	{
		return dif->minimo();
	}
	double maximoEnDifusor(Variable *var)
	{
		Difusor *dif;
		dif=difusor(var);
		return maximoEnDifusor(dif);
	}
	double maximoEnDifusor(Difusor *dif)
	{
		return dif->maximo();
	}
	double pertenenciaVariable(Variable *var, int numCon, double x)
	{
		ConjuntoDifuso *cd;
		cd=conjuntoEnVariable(var, numCon);
		return pertenenciaVariable(cd,x);
	}
	double pertenenciaVariable(ConjuntoDifuso *cd,double x)
	{
		return cd->pertenencia(x);
	}
};


class Norma
{
public:
	Norma()
	{
	}
	~Norma()
	{
	}
	virtual double ToSNorm()=0;
	virtual double opera(double, double)=0;
protected:
};

class T_Norma:public Norma
{
public:
	T_Norma(){}
	~T_Norma(){}
	double ToSNorm()
	{
		return 1.0;
	}
	virtual double opera(double, double)=0;
protected:
};

class S_Norma:public Norma
{
public:
	S_Norma(){}
	~S_Norma(){}
	double ToSNorm()
	{
		return 0.0;
	}
	virtual double opera(double, double)=0;
protected:
};

//////////////////// T_Norma

class Producto:public T_Norma
{
public:
	Producto()
	{
	}
	~Producto(){}
	double opera(double x, double y)
	{
		double z;
		z=x*y;
		return z;
	}
protected:
};

class Minimo:public T_Norma
{
public:
	Minimo()
	{
	}
	~Minimo(){}
	double opera(double x, double y)
	{
		double z;
		if(x<y)
		{
			z=x;
		}else
		{
			z=y;
		}
		return z;
	}
protected:
};

class ProductoAcotado:public T_Norma
{
public:
	ProductoAcotado()
	{
	}
	~ProductoAcotado(){}
	double opera(double x, double y)
	{
		double z;
		z=x+y-1;
		if(z<0)
		{
			z=0;
		}
		return z;
	}
protected:
};

class ProductoDrastico:public T_Norma
{
public:
	ProductoDrastico()
	{
	}
	~ProductoDrastico(){}
	double opera(double x, double y)
	{
		double z;
		if(y==1)
		{
			z=x;
		}
		if(x==1)
		{
			z=y;
		}
		if(x<1&&y<1)
		{
			z=0;
		}
		return z;
	}
protected:
};

class FamiliaTp:public T_Norma
{
public:
	FamiliaTp()
	{
		p=1;
	}
	FamiliaTp(double parametro)
	{
		p=parametro;
	}
	~FamiliaTp(){}
	double opera(double x, double y)
	{
		double z;
		z=pow(1-x,p)+pow(1-y,p)-pow(1-x,p)*pow(1-y,p);
		z=1-pow(z,(1/p));
		return z;
	}
protected:
	double p;
};

class FamiliaHp:public T_Norma
{
public:
	FamiliaHp()
	{
		p=1;
	}
	FamiliaHp(double parametro)
	{
		p=parametro;
	}
	~FamiliaHp(){}
	double opera(double x, double y)
	{
		double z;
		z=p-(1-p)*(x+y-x*y);
		z=x*y/z;
		return z;
	}
protected:
	double p;
};

class FamiliaFp:public T_Norma
{
public:
	FamiliaFp()
	{
		p=2;
	}
	FamiliaFp(double parametro)
	{
		p=parametro;
	}
	~FamiliaFp(){}
	double opera(double x, double y)
	{
		double z;
		z=1+(pow(p,x)-1)*(pow(p,y)-1)/(p-1);
		z=log(z)/log(p);
		return z;
	}
protected:
	double p;
};

class FamiliaYp:public T_Norma
{
public:
	FamiliaYp()
	{
		p=1;
	}
	FamiliaYp(double parametro)
	{
		p=parametro;
	}
	~FamiliaYp(){}
	double opera(double x, double y)
	{
		double z;
		z=pow(1-x,p)+pow(1-y,p);
		z=pow(z,(1/p));
		if(z>1)
		{
			z=1;
		}
		z=1-z;
		return z;
	}
protected:
	double p;
};

class FamiliaAp:public T_Norma
{
public:
	FamiliaAp()
	{
		p=1;
	}
	FamiliaAp(double parametro)
	{
		p=parametro;
	}
	~FamiliaAp(){}
	double opera(double x, double y)
	{
		double z;
		z=x;
		if(y>z)
		{
			z=y;
		}
		if(p>z)
		{
			z=p;
		}
		z=x*y/z;
		return z;
	}
protected:
	double p;
};



///////////////// S-Normas

class Maximo:public S_Norma
{
public:
	Maximo()
	{
	}
	~Maximo(){}
	double opera(double x, double y)
	{
		double z;
		if(x>y)
		{
			z=x;
		}else
		{
			z=y;
		}
		return z;
	}
protected:
};

class SumaAcotada:public S_Norma
{
public:
	SumaAcotada()
	{
	}
	~SumaAcotada(){}
	double opera(double x, double y)
	{
		double z;
		z=x+y;
		if(z>1)
		{
			z=1;
		}
		return z;
	}
protected:
};

class SumaDrastica:public S_Norma
{
public:
	SumaDrastica()
	{
	}
	~SumaDrastica(){}
	double opera(double x, double y)
	{
		double z;
		if(y==0)
		{
			z=x;
		}
		if(x==0)
		{
			z=y;
		}
		if(x>0&&y>0)
		{
			z=1;
		}
		return z;
	}
protected:
};

class FamiliaSp:public S_Norma
{
public:
	FamiliaSp()
	{
		p=1;
	}
	FamiliaSp(double parametro)
	{
		p=parametro;
	}
	~FamiliaSp(){}
	double opera(double x, double y)
	{
		double z;
		z=x+y+p*x*y;
		if(z>1)
		{
			z=1;
		}
		return z;
	}
protected:
	double p;
};


class Implicacion
{
public:
	Implicacion()
	{
	}
	~Implicacion()
	{
	}
	virtual double implica(double,double)=0;
	virtual double defecto()=0;
protected:
};

class ImplicacionT_Norma:public Implicacion
{
public:
	ImplicacionT_Norma(){}
	~ImplicacionT_Norma(){}
	double defecto()
	{
		return 0;
	}
	virtual double implica(double x, double y)=0;
protected:
};

class ImplicacionIf_Then:public Implicacion
{
public:
	ImplicacionIf_Then(){}
	~ImplicacionIf_Then(){}
	double defecto()
	{
		return 1;
	}
	virtual double implica(double x, double y)=0;
protected:
};


class ImplicacionProducto:public ImplicacionT_Norma
{
public:
	ImplicacionProducto()
	{
	}
	~ImplicacionProducto()
	{
	}
	double implica(double x, double y)
	{
		double z;
		z=x*y;
		return z;
	}
protected:
};

class ImplicacionMinimo:public ImplicacionT_Norma
{
public:
	ImplicacionMinimo()
	{
	}
	~ImplicacionMinimo()
	{
	}
	double implica(double x, double y)
	{
		double z;
		if(x<y)
			z=x;
		else
			z=y;
		return z;
	}
protected:
};

class ImplicacionKleenDienes:public ImplicacionIf_Then
{
public:
	ImplicacionKleenDienes()
	{
	}
	~ImplicacionKleenDienes()
	{
	}
	double implica(double x, double y)
	{
		double rel;
		x=1-x;
		if(x>y)
			rel=x;
		else
			rel=y;
		return(rel);
	}
protected:
};


class ImplicacionLukasiewicz:public ImplicacionIf_Then
{
public:
	ImplicacionLukasiewicz()
	{
	}
	~ImplicacionLukasiewicz()
	{
	}
	double implica(double x, double y)
	{
		double rel;
		rel=1-x+y;
		if(rel>1)
			rel=1;
		return(rel);
	}
protected:
};


class ImplicacionZadeh:public ImplicacionIf_Then
{
public:
	ImplicacionZadeh()
	{
	}
	~ImplicacionZadeh()
	{
	}
	double implica(double x, double y)
	{
		double rel;
		if(x<y)
			rel=x;
		else
			rel=y;
		x=1-x;
		if(rel<x)
			rel=x;
		return(rel);
	}
protected:
};


class ImplicacionEstocastica:public ImplicacionIf_Then
{
public:
	ImplicacionEstocastica()
	{
	}
	~ImplicacionEstocastica()
	{
	}
	double implica(double x, double y)
	{
		double rel;
		rel=x*y;
		x=1-x;
		if(rel<x)
			rel=x;
		return(rel);
	}
protected:
};


class ImplicacionGoguen:public ImplicacionIf_Then
{
public:
	ImplicacionGoguen()
	{
	}
	~ImplicacionGoguen()
	{
	}
	double implica(double x, double y)
	{
		double rel;
		if(x>0.00001)
			rel=y/x;
		else
			rel=1000;
		if(rel>1)
			rel=1;
		return(rel);
	}
protected:
};


class ImplicacionGodel:public ImplicacionIf_Then
{
public:
	ImplicacionGodel()
	{
	}
	~ImplicacionGodel()
	{
	}
	double implica(double x, double y)
	{
		double rel;
		if(x<=y)
			rel=1;
		else
			rel=y;
		return(rel);
	}
protected:
};


class ImplicacionAguda:public ImplicacionIf_Then
{
public:
	ImplicacionAguda()
	{
	}
	~ImplicacionAguda()
	{
	}
	double implica(double x, double y)
	{
		double rel;
		if(x<=y)
			rel=1;
		else
			rel=0;
		return(rel);
	}
protected:
};

//////////////////////////////////////

class Regla
{
public:
	Regla(int numEntradas, int numSalidas)
	{
		Antecedente=new int[numEntradas];
		Consecuente=new int[numSalidas];
		Modificadores=new double[numEntradas];
	}
	~Regla()
	{
		delete[] Antecedente;
		delete[] Consecuente;
		delete[] Modificadores;
	}
	int conjuntoEntrada(int numVar)
	{
		return Antecedente[numVar];
	}
	void conjuntoEntrada(int numVar,int numCon)
	{
		Antecedente[numVar]=numCon;
	}
	int conjuntoSalida(int numVar)
	{
		return Consecuente[numVar];
	}
	void conjuntoSalida(int numVar,int numCon)
	{
		Consecuente[numVar]=numCon;
	}
	double modificador(int numVar)
	{
		return Modificadores[numVar];
	}
	void modificador(int numVar,double modif)
	{
		Modificadores[numVar]=modif;
	}
	void certeza(double cer)
	{
		Certeza=cer;
	}
	double certeza()
	{
		return Certeza;
	}
	BOOL operator==(const Regla& other)
	{
		return ( ( Antecedente == other.Antecedente)&
		( Consecuente == other.Consecuente)&
		( Modificadores == other.Modificadores) );
	}

protected:
	int *Antecedente;
	int *Consecuente;
	double *Modificadores;

   double Certeza;
};


class MaquinaInferencia
{
public:
	MaquinaInferencia(Universo *ent,Universo *sal,int numReg);
	~MaquinaInferencia();
	Implicacion* implicacion()
	{
		return Implicaciones;
	}
	void implicacion(Implicacion *imp)
	{
		delete Implicaciones;
		Implicaciones=imp;
	}
	Norma *and_()
	{
		return And;
	}
	void and_(Norma *nor)
	{
		delete And;
		And=nor;
	}
	Norma *minComposicion()
	{
		return MinComposicion;
	}
	void minComposicion(Norma *nor)
	{
		delete MinComposicion;
		MinComposicion=nor;
	}
	Norma *maxComposicion()
	{
		return MaxComposicion;
	}
	void maxComposicion(Norma *nor)
	{
		delete MaxComposicion;
		MaxComposicion=nor;
	}

	Regla *regla(int numRegla);
	void conjuntoEntrada(int numRegla, int numVar, int numCon)
	{
		regla(numRegla)->conjuntoEntrada(numVar,numCon);
	}
	ConjuntoDifuso *conjuntoEntrada(int numRegla, int numVar)
	{
		return Entradas->conjuntoEnVariable(numVar,regla(numRegla)->conjuntoEntrada(numVar));
	}
	int numConjuntoEntrada(int numRegla, int numVar)
	{
		return regla(numRegla)->conjuntoEntrada(numVar);
	}
	void modificador(int numRegla, int numVar, double modif)
	{
		regla(numRegla)->modificador(numVar,modif);
	}
	double modificador(int numRegla, int numVar)
	{
		return regla(numRegla)->modificador(numVar);
	}
	void conjuntoSalida(int numRegla, int numVar, int numCon)
	{
		regla(numRegla)->conjuntoSalida(numVar,numCon);
	}
	ConjuntoDifuso *conjuntoSalida(int numRegla, int numVar)
	{
		return Salidas->conjuntoEnVariable(numVar,regla(numRegla)->conjuntoSalida(numVar));
	}
	int numConjuntoSalida(int numRegla, int numVar)
	{
		return regla(numRegla)->conjuntoSalida(numVar);
	}
	Universo *entradas()
	{
		return Entradas;
	}
	Universo *salidas()
	{
		return Salidas;
	}
	int numeroReglas()
	{
		return NumeroReglas;
	}
	int numeroEntradas()
	{
		return NumeroEntradas;
	}
	int numeroSalidas()
	{
		return NumeroSalidas;
	}
	void limpiarMaquinaInferencia();
	void adicionarRegla(Regla *reg)
	{
		BaseReglas->Add(reg);
		NumeroReglas++;
	}
	void eliminarRegla(int num)
	{
		BaseReglas->Destroy(num);
		NumeroReglas--;
	}
	void actualizarEntradas(double *ent);
	double pertenenciaDifusores(double *ent);
	double pertenenciaImplicacion(int numSal,int numRegla, double *ent,double sal);
	double pertenenciaConsecuente(int numSal,int numRegla,double sal);
	double pertenenciaAntecedente(int numRegla,double *ent);
	double pertenenciaComposicion(int numVar, int numRegla,double sal);
	int activarRegla(int numregla);
	void desocuparBaseReglas();
	void EntrenaUniversoFijo(double *antecedente, double *consecuente);
	void EntrenaUniversoVariable(double *antecedente, double *consecuente);
	void llenarRegla(Regla *rg,double *antec, double *consec);
	int compararAntec(Regla *rg1, Regla *rg2);
protected:
	typedef Arreglo<Regla> ListaReglas;

	ListaReglas *BaseReglas;
	Universo *Entradas;
	Universo *Salidas;

	Implicacion *Implicaciones;
	Norma *MinComposicion;
	Norma *MaxComposicion;
	Norma *And;

	int NumeroReglas;
	int NumeroEntradas;
	int NumeroSalidas;
};

class Concresor
{
public:
	Concresor(MaquinaInferencia *maq, int numVar, Norma *nor)
	{
		Motor=maq;
		NumeroVariable=numVar;
		Conjuncion=nor;
	}
	~Concresor()
	{
	}
	int numeroVariable()
	{
		return NumeroVariable;
	}
	MaquinaInferencia *motor()
	{
		return Motor;
	}
	void motor(MaquinaInferencia *maq)
	{
		Motor=maq;
	}
	double defecto()
	{
		return Motor->implicacion()->defecto();
	}
	Norma *conjuncion()
	{
		return Conjuncion;
	}
	void conjuncion(Norma *nor)
	{
		Conjuncion=nor;
	}
	virtual double salidaConcreta(double *ent)=0;
	BOOL operator==(const Concresor& other)
	{
		return ( ( Motor == other.Motor)&
		( NumeroVariable == other.NumeroVariable)&
		( Conjuncion == other.Conjuncion) );
	}
protected:
	MaquinaInferencia *Motor;
	int NumeroVariable;
	Norma *Conjuncion;
};

class PrimerMaximo:public Concresor
{
public:
	PrimerMaximo(MaquinaInferencia *maq, int numVar, Norma *nor):Concresor(maq,numVar,nor)
	{}
	~PrimerMaximo(){}
	double salidaConcreta(double *ent);
protected:
};

class UltimoMaximo:public Concresor
{
public:
	UltimoMaximo(MaquinaInferencia *maq, int numVar, Norma *nor):Concresor(maq,numVar,nor)
	{}
	~UltimoMaximo(){}
	double salidaConcreta(double *ent);
protected:
};

class MediaDeMaximos:public Concresor
{
public:
	MediaDeMaximos(MaquinaInferencia *maq, int numVar, Norma *nor):Concresor(maq,numVar,nor)
	{}
	~MediaDeMaximos(){}
	double salidaConcreta(double *ent);
protected:
};

class CentroDeGravedad:public Concresor
{
public:
	CentroDeGravedad(MaquinaInferencia *maq, int numVar, Norma *nor):Concresor(maq,numVar,nor)
	{}
	~CentroDeGravedad(){}
	double salidaConcreta(double *ent);
protected:
};


class Altura:public Concresor
{
public:
	Altura(MaquinaInferencia *maq, int numVar, Norma *nor):Concresor(maq,numVar,nor)
	{}
	~Altura(){}
	double salidaConcreta(double *ent);
protected:
};

class BloqueConcrecion
{
public:
	BloqueConcrecion(MaquinaInferencia *maq)
	{
		Motor=maq;
		int numSal;
		numSal=Motor->numeroSalidas()+1;
		Concresores=new ListaConcresores(numSal);
	}
	~BloqueConcrecion()
	{
		limpiarListaConcresores();
		delete Concresores;
	}
	void adicionarConcresor(Concresor* conc)
	{
		Concresores->Add(conc);
	}
	int numeroConcresores()
	{
		return Motor->salidas()->numeroVariables();
	}
	void eliminarConcresor(int conc)
	{
		Concresores->Destroy(conc);
	}
	Norma *conjuncion()
	{
		return concresor(0)->conjuncion();
	}
	void conjuncion(Norma *nor);
	void limpiarListaConcresores();
	void motor(MaquinaInferencia* maq);
	MaquinaInferencia *motor()
	{
		return Motor;
	}
	Concresor *concresor(int numSal);
	double salidaConcreta(int numSal,double *ent)
	{
		Concresor *conc;
		conc=concresor(numSal);
		return conc->salidaConcreta(ent);
	}
	void salidaConcreta(double *ent,double *sal);
	void autodefinirBloqueConcrecion(MaquinaInferencia* maq,Norma *conjuncion);
protected:
	typedef Arreglo<Concresor> ListaConcresores;

	ListaConcresores *Concresores;
	MaquinaInferencia *Motor;
};

class SistemaLogicaDifusa
{
public:
	SistemaLogicaDifusa()
	{
		entradas=0;
		salidas=0;
		motor=0;
		concreto=0;
	}
	~SistemaLogicaDifusa()
	{
		delete entradas;
		delete salidas;
		delete motor;
		delete concreto;
	}
	int numeroEntradas()
	{
		return entradas->numeroVariables();
	}
	int numeroSalidas()
	{
		return salidas->numeroVariables();
	}
	string nombreVariableEntrada(int numVar)
	{
		return entradas->nombreVariable(numVar);
	}
	string nombreVariableSalida(int numVar)
	{
		return salidas->nombreVariable(numVar);
	}
	void calcular(double *entra,double *sale)
	{
		concreto->salidaConcreta(entra,sale);
	}
	MaquinaInferencia *Motor(){return motor;}
	void EntrenaUniversoFijo(double *antecedente, double *consecuente)
	{
		motor->EntrenaUniversoFijo(antecedente,consecuente);
	}
	void EntrenaUniversoVariable(double *antecedente, double *consecuente)
	{
		motor->EntrenaUniversoVariable(antecedente,consecuente);
	}

	Universo *entradas;
	Universo *salidas;
	MaquinaInferencia *motor;
	BloqueConcrecion *concreto;
};

class pin
{
	public:
		pin()
		{
			Contacto=NULL;
			Valor=0.0;
		}
		virtual ~pin(){}
		pin* contacto() const
		{
			return Contacto;
		}
		void contacto(pin* c)
		{
			Contacto=c;
		}
		double valor()
		{
			return Valor;
		}
		void valor(double V)
		{
			Valor=V;
		}

	protected:

	private:
		pin* Contacto;
		double Valor;

};


typedef Arreglo<pin> ListaPines;

class nodo
{
	public:
		nodo(){}
		virtual ~nodo(){}
		ListaPines* entradas()
		{
			return &Entradas;
		}
		ListaPines* salidas()
		{
			return &Salidas;
		}
		SistemaLogicaDifusa* sld()
		{
			return SLD;
		}
		void sld(SistemaLogicaDifusa* sld)
		{
			SLD=sld;
		}
		void calcularNodo();
		void actualizarEntradas();
		void calcular(double* entra, double* sale); // =0 para hacer virtual y heredar de SLD
		void ajustarPinesAsld();

	protected:

	private:
  SistemaLogicaDifusa *SLD;
	ListaPines Entradas;
	ListaPines Salidas;
};

	typedef Arreglo<nodo> ListaNodos;

class capa
{
	public:
		capa(){}
		virtual ~capa(){}

		ListaNodos* nodos()
		{
			return &Nodos;
		}
	protected:


	ListaNodos Nodos;
};


typedef Arreglo<capa> ListaCapas;

class red
{
	public:
		red(){}
		virtual ~red(){}
		bool conectar(int capa1, int nodo1, int pin1,int capa2, int nodo2, int pin2);
		bool buscarCapa(int numCapa);
		bool buscarNodo(int numCapa, int numNodo);
		bool buscarPinEntrada(int numCapa, int numNodo, int numPin);
		bool buscarPinSalida(int numCapa, int numNodo, int numPin);
		double valorPinEntrada(int numCapa, int numNodo, int numPin);
		double valorPinSalida(int numCapa, int numNodo, int numPin);
		void valorEntrada(int numNodo, int numPin, double Valor);
		nodo* ptrNodo(int numCapa, int numNodo);
		pin* ptrPinEntrada(int numCapa, int numNodo, int numPin);
		pin* ptrPinSalida (int numCapa, int numNodo, int numPin);
		void desconectarSalida(int numCapa, int numNodo, int numPin);
		void desconectarEntradasNodo(int numCapa, int numNodo);
		void desconectarSalidasNodo (int numCapa, int numNodo);
		void eliminarNodo(int numCapa, int numNodo);
		void eliminarCapa(int numCapa);
		void eliminarCapas();
		void adicionarCapa();
		void adicionarNodo(int numCapa);
		bool buscarPinEntrada(pin* Pin, int *numCapa, int *numNodo, int *numPin);
		bool buscarPinSalida(pin* Pin, int *numCapa, int *numNodo, int *numPin);
		int numeroEntradas();
		int numeroSalidas();
		void asignarEntradas(double* entra);
		void leerSalidas(double* sale);
		void calcular(double* entra, double* sale);

		void calcularRed();

		ListaCapas* capas()
		{
			return &Capas;
		}

	protected:
	private:

	ListaCapas Capas;
};



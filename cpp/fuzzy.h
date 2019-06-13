#ifndef __FUZZY_H
#define __FUZZY_H
#endif

#ifndef __IOSTREAM_H
#include <iostream>
#endif

#ifndef __STRIGN_H
#include<string.h>
#endif

#ifndef __STDIO_H
#include<stdio.h>
#endif

#ifndef __MATH_H
#include<math.h>
#endif


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
	void minimo(float min)
	{
		Minimo=min;
	}
	float minimo()
	{
		return Minimo;
	}
	void maximo(float max)
	{
		Maximo=max;
	}
	float maximo()
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
	virtual void puntosClaves(float *puntos)=0;
	virtual void nuevoPuntoClave(int punto, float x)=0;
	virtual float pertenencia(float x)=0;
	virtual float centroAltura()=0;
	BOOL operator==(const ConjuntoDifuso& other)
	{
		return (( Minimo == other.Minimo)&
		( Maximo == other.Maximo) );
	}
protected:
	float Minimo;
	float Maximo;
	int NumeroPuntosClaves;
	int Identificador;
};


class ConjuntoL: public ConjuntoDifuso
{
public:
	ConjuntoL(float min, float pcor, float max)
	{
		Minimo=min;
		PrimerCorte=pcor;
		Maximo=max;
		NumeroPuntosClaves=2;
		Identificador=0;
	}
	~ConjuntoL(){}
	float pertenencia(float);
	void puntosClaves(float *puntos)
	{
		puntos[0]=primerCorte();
		puntos[1]=maximo();
	}
	void nuevoPuntoClave(int punto, float x);
	float centroAltura()
	{
		return((Minimo+PrimerCorte)/2.0);
	}
protected:
	float PrimerCorte;
	void primerCorte(float pcor)
	{
		PrimerCorte=pcor;
	}
	float primerCorte()
	{
		return PrimerCorte;
	}
};

class ConjuntoTriangulo: public ConjuntoDifuso
{
public:
	ConjuntoTriangulo(float min, float pcor, float max)
	{
		Minimo=min;
		PrimerCorte=pcor;
		Maximo=max;
		NumeroPuntosClaves=3;
		Identificador=1;
	}
	~ConjuntoTriangulo(){}
	float pertenencia(float);
	void puntosClaves(float *puntos)
	{
		puntos[0]=minimo();
		puntos[1]=primerCorte();
		puntos[2]=maximo();
	}
	void nuevoPuntoClave(int punto, float x);
	float centroAltura()
	{
		return(PrimerCorte);
	}
protected:
	float PrimerCorte;
	void primerCorte(float pcor)
	{
		PrimerCorte=pcor;
	}
	float primerCorte()
	{
		return PrimerCorte;
	}
};

class ConjuntoPi: public ConjuntoDifuso
{
public:
	ConjuntoPi(float min, float pcor, float scor, float max)
	{
		Minimo=min;
		PrimerCorte=pcor;
		SegundoCorte=scor;
		Maximo=max;
		NumeroPuntosClaves=4;
		Identificador=2;
	}
	~ConjuntoPi(){}
	float pertenencia(float x);
	void puntosClaves(float *puntos)
	{
		puntos[0]=minimo();
		puntos[1]=primerCorte();
		puntos[2]=segundoCorte();
		puntos[3]=maximo();
	}
	void nuevoPuntoClave(int punto, float x);
	float centroAltura()
	{
		return((PrimerCorte+SegundoCorte)/2.0);
	}
protected:
	float PrimerCorte;
	float SegundoCorte;
	void primerCorte(float pcor)
	{
		PrimerCorte=pcor;
	}
	float primerCorte()
	{
		return PrimerCorte;
	}
	void segundoCorte(float scor)
	{
		SegundoCorte=scor;
	}
	float segundoCorte()
	{
		return SegundoCorte;
	}
};

class ConjuntoGamma: public ConjuntoDifuso
{
public:
	ConjuntoGamma(float min, float pcor,  float max)
	{
		Minimo=min;
		PrimerCorte=pcor;
		Maximo=max;
		NumeroPuntosClaves=2;
		Identificador=3;
	}
	~ConjuntoGamma(){}
	float pertenencia(float);
	void puntosClaves(float *puntos)
	{
		puntos[0]=minimo();
		puntos[1]=primerCorte();
	}
	void nuevoPuntoClave(int punto, float x);
	float centroAltura()
	{
		return((Maximo+PrimerCorte)/2.0);
	}
protected:
	float PrimerCorte;
	void primerCorte(float pcor)
	{
		PrimerCorte=pcor;
	}
	float primerCorte()
	{
		return PrimerCorte;
	}
};

class ConjuntoZ: public ConjuntoDifuso
{
public:
	ConjuntoZ(float min, float pcor, float max)
	{
		Minimo=min;
		PrimerCorte=pcor;
		Maximo=max;
		NumeroPuntosClaves=2;
		Identificador=4;
	}
	~ConjuntoZ(){}
	float pertenencia(float);
	void puntosClaves(float *puntos)
	{
		puntos[0]=primerCorte();
		puntos[1]=maximo();
	}
	void nuevoPuntoClave(int punto, float x);
	float centroAltura()
	{
		return((Minimo+PrimerCorte)/2.0);
	}
protected:
	float PrimerCorte;
	void primerCorte(float pcor)
	{
		PrimerCorte=pcor;
	}
	float primerCorte()
	{
		return PrimerCorte;
	}
};

class ConjuntoCampana: public ConjuntoDifuso
{
public:
	ConjuntoCampana(float min, float pcor, float max)
	{
		Minimo=min;
		PrimerCorte=pcor;
		Maximo=max;
		NumeroPuntosClaves=3;
		Identificador=5;
	}
	~ConjuntoCampana(){}
	float pertenencia(float);
	void puntosClaves(float *puntos)
	{
		puntos[0]=minimo();
		puntos[1]=primerCorte();
		puntos[2]=maximo();
	}
	void nuevoPuntoClave(int punto, float x);
	float centroAltura()
	{
		return(PrimerCorte);
	}
protected:
	float PrimerCorte;
	void primerCorte(float pcor)
	{
		PrimerCorte=pcor;
	}
	float primerCorte()
	{
		return PrimerCorte;
	}
};

class ConjuntoS: public ConjuntoDifuso
{
public:
	ConjuntoS(float min, float pcor, float max)
	{
		Minimo=min;
		PrimerCorte=pcor;
		Maximo=max;
		NumeroPuntosClaves=2;
		Identificador=6;
	}
	~ConjuntoS(){}
	float pertenencia(float);
	void puntosClaves(float *puntos)
	{
		puntos[0]=minimo();
		puntos[1]=primerCorte();
	}
	void nuevoPuntoClave(int punto, float x);
	float centroAltura()
	{
		return((Maximo+PrimerCorte)/2.0);
	}
protected:
	float PrimerCorte;
	void primerCorte(float pcor)
	{
		PrimerCorte=pcor;
	}
	float primerCorte()
	{
		return PrimerCorte;
	}
};

class ConjuntoPiCampana: public ConjuntoDifuso
{
public:
	ConjuntoPiCampana(float min, float pcor, float scor, float max)
	{
		Minimo=min;
		PrimerCorte=pcor;
		SegundoCorte=scor;
		Maximo=max;
		NumeroPuntosClaves=4;
		Identificador=7;
	}
	~ConjuntoPiCampana(){}
	float pertenencia(float);
	void puntosClaves(float *puntos)
	{
		puntos[0]=minimo();
		puntos[1]=primerCorte();
		puntos[2]=segundoCorte();
		puntos[3]=maximo();
	}
	void nuevoPuntoClave(int punto, float x);
	float centroAltura()
	{
		return((PrimerCorte+SegundoCorte)/2.0);
	}
protected:
	float PrimerCorte;
	float SegundoCorte;
	void primerCorte(float pcor)
	{
		PrimerCorte=pcor;
	}
	float primerCorte()
	{
		return PrimerCorte;
	}
	void segundoCorte(float scor)
	{
		SegundoCorte=scor;
	}
	float segundoCorte()
	{
		return SegundoCorte;
	}
};


class ConjuntoSinglenton: public ConjuntoDifuso
{
public:
	ConjuntoSinglenton(float pi, float de)
	{
		Pico=pi;
		Delta=de;
		Minimo=Pico-Delta/2;
		Maximo=Pico+Delta/2;
		NumeroPuntosClaves=2;
		Identificador=8;
	}
	~ConjuntoSinglenton(){}
	float pertenencia(float);
	void puntosClaves(float *puntos)
	{
		puntos[0]=minimo();
		puntos[1]=maximo();
	}
	void nuevoPuntoClave(int punto, float x);
	float centroAltura()
	{
		return(Pico);
	}
protected:
	float pico(){return Pico;}
	float delta(){return Delta;}
	float Delta;
	float Pico;
};

inline float ConjuntoL::pertenencia(float x)
{
	float ux;
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


inline float ConjuntoTriangulo::pertenencia(float x)
{
	float ux;
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


inline float ConjuntoPi::pertenencia(float x)
{
	float ux;
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


inline float ConjuntoGamma::pertenencia(float x)
{
	float ux;
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

inline float ConjuntoZ::pertenencia(float x)
{
	float ux;
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

inline float ConjuntoCampana::pertenencia(float x)
{
	float ux;
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


inline float ConjuntoS::pertenencia(float x)
{
	float ux;
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

inline float ConjuntoPiCampana::pertenencia(float x)
{
	float ux;
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


inline float ConjuntoSinglenton::pertenencia(float x)
{
	float ux;
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
	float centroAltura(){return 0.0;}
	virtual float pertenencia(float)=0;
	virtual float minimo()=0;
	virtual float maximo()=0;
	virtual void minimo(float mn)=0;
	virtual void maximo(float mx)=0;
	virtual void entrada(float)=0;
	void puntosClaves(float* ){}
	void nuevoPuntoClave(int, float ){}
protected:
	int NumeroPuntos;
	float dx;
	float Centro;
};

class DifusorTriangulo:public virtual ConjuntoTriangulo,public virtual Difusor
{
public:
	DifusorTriangulo(float x, float me, float ma):ConjuntoTriangulo(x-me,x,x+ma)
	{
		Centro=x;
		menos=me;
		mas=ma;
	}
	~DifusorTriangulo()
	{
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
protected:
	float mas;
	float menos;
};

class DifusorPi:public virtual ConjuntoPi,public virtual Difusor
{
public:
	DifusorPi(float x, float me1, float me2, float ma1, float ma2):ConjuntoPi(x-me1,x-me2,x+ma1,x+ma2)
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
protected:
	float mas1;
	float mas2;
	float menos1;
	float menos2;
};

class DifusorCampana:public virtual ConjuntoCampana,public virtual Difusor
{
public:
	DifusorCampana(float x, float me, float ma):ConjuntoCampana(x-me,x,x+ma)
	{
		Centro=x;
		menos=me;
		mas=ma;
	}
	~DifusorCampana()
	{
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
protected:
	float mas;
	float menos;
};

class DifusorPiCampana:public virtual ConjuntoPiCampana,public virtual Difusor
{
public:
	DifusorPiCampana(float x, float me1, float me2, float ma1, float ma2):ConjuntoPiCampana(x-me1,x-me2,x+ma1,x+ma2)
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
protected:
	float mas1;
	float mas2;
	float menos1;
	float menos2;
};


class DifusorSinglenton:public virtual ConjuntoSinglenton, public virtual Difusor
{
public:
	DifusorSinglenton(float x, float de):ConjuntoSinglenton(x,de)
	{
		Centro=x;
	}
	~DifusorSinglenton()
	{
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
		NombreVariable=0;
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
	char* nombreVariable()
	{
		return NombreVariable;
	}
	char* nombreVariable(const char* s)
	{
		delete[] NombreVariable;
		NombreVariable=new char[strlen(s)+1];
		strcpy(NombreVariable,s);
		return NombreVariable;
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
	float intervalo()
	{
		return Intervalo;
	}

	ConjuntoDifuso* conjunto(int conj);
	float pertenencia(ConjuntoDifuso*, float);
	float pertenencia(int, float);
	float pertenenciaDifusor(float);
	float rangoMinimo(){return RangoMinimo;}
	void rangoMinimo(float rm){RangoMinimo=rm;}
	float rangoMaximo(){return RangoMaximo;}
	void rangoMaximo(float rm){RangoMaximo=rm;}
	BOOL operator==(const Variable& other)
	{
		return ( strcmp( NombreVariable,other.NombreVariable)&
		( RangoMinimo == other.RangoMinimo)&
		( RangoMaximo == other.RangoMaximo)&
		( DifusorEntrada == other.DifusorEntrada)&
		( Conjuntos == other.Conjuntos) );
	}
protected:
	typedef Arreglo<ConjuntoDifuso> ListaConjuntos;

	ListaConjuntos *Conjuntos;
	Difusor *DifusorEntrada;
	float RangoMinimo;
	float RangoMaximo;
	int NumeroIntervalos;
	float Intervalo;
	char *NombreVariable;
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
	float intervaloDifusor(int numVar)
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
	float pertenenciaDifusor(int numVar, float x)
	{
		Variable *var;
		var=variable(numVar);
		return pertenenciaDifusor(var,x);
	}
	char *nombreVariable(int numVar)
	{
		Variable *var;
		var=variable(numVar);
		return nombreVariable(var);
	}
	void nombreVariable(char *nom,int numVar)
	{
		Variable *var;
		var=variable(numVar);
		nombreVariable(nom,var);
	}
	void entradaReal(int numVar, float x)
	{
		Difusor *dif;
		dif=difusor(numVar);
		entradaReal(dif,x);
	}
	void entradaReal(float *ent);
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
	float intervaloEnVariable(int numVar)
	{
		Variable *var;
		var=variable(numVar);
		return intervaloEnVariable (var);
	}
	ConjuntoDifuso *conjuntoEnVariable(int numVar, int numCon)
	{
		Variable *var;
		var=variable(numVar);
		return var->conjunto(numCon);
	}
	float rangoMinimoVariable(int numVar)
	{
		Variable *var;
		var=variable(numVar);
		return rangoMinimoVariable(var);
	}
	void rangoMinimoVariable(float rm,int numVar)
	{
		Variable *var;
		var=variable(numVar);
		rangoMinimoVariable(rm,var);
	}
	float rangoMaximoVariable(int numVar)
	{
		Variable *var;
		var=variable(numVar);
		return rangoMaximoVariable(var);
	}
	void rangoMaximoVariable(float rm,int numVar)
	{
		Variable *var;
		var=variable(numVar);
		rangoMaximoVariable(rm,var);
	}
	float minimoEnConjunto(int numVar, int numCon)
	{
		ConjuntoDifuso *cd;
		cd=conjuntoEnVariable(numVar, numCon);
		return minimoEnConjunto(cd);
	}
	float maximoEnConjunto(int numVar, int numCon)
	{
		ConjuntoDifuso *cd;
		cd=conjuntoEnVariable(numVar, numCon);
		return maximoEnConjunto(cd);
	}
	float minimoEnDifusor(int numVar)
	{
		Difusor *dif;
		dif=difusor(numVar);
		return minimoEnDifusor(dif);
	}
	float maximoEnDifusor(int numVar)
	{
		Difusor *dif;
		dif=difusor(numVar);
		return maximoEnDifusor(dif);
	}
	float pertenenciaVariable(int numVar, int numCon, float x)
	{
		ConjuntoDifuso *cd;
		cd=conjuntoEnVariable(numVar, numCon);
		return pertenenciaVariable(cd,x);
	}
	float centroEnDifusor(int numVar)
	{
		float x;
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
	float pertenenciaDifusor(Variable *var, float x)
	{
		return var->pertenenciaDifusor(x);
	}
	char *nombreVariable(Variable *var)
	{
		return var->nombreVariable();
	}
	void nombreVariable(char *nom,Variable *var)
	{
		var->nombreVariable(nom);
	}
	void entradaReal(Difusor *dif, float x)
	{
		dif->entrada(x);
	}
	void entradaReal(Variable *var,float x)
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
	float intervaloEnVariable(Variable *var)
	{
		return var->intervalo();
	}
	ConjuntoDifuso *conjuntoEnVariable(Variable *var, int numCon)
	{
		return var->conjunto(numCon);
	}
	float rangoMinimoVariable(Variable *var)
	{
		return var->rangoMinimo();
	}
	void rangoMinimoVariable(float rm,Variable *var)
	{
		var->rangoMinimo(rm);
	}
	float rangoMaximoVariable(Variable *var)
	{
		return var->rangoMaximo();
	}
	void rangoMaximoVariable(float rm,Variable *var)
	{
		var->rangoMaximo(rm);
	}
	float minimoEnConjunto(Variable *var, int numCon)
	{
		ConjuntoDifuso *cd;
		cd=conjuntoEnVariable(var, numCon);
		return minimoEnConjunto(cd);
	}
	float minimoEnConjunto(ConjuntoDifuso *cd)
	{
		return cd->minimo();
	}
	float maximoEnConjunto(Variable *var, int numCon)
	{
		ConjuntoDifuso *cd;
		cd=conjuntoEnVariable(var, numCon);
		return maximoEnConjunto(cd);
	}
	float maximoEnConjunto(ConjuntoDifuso *cd)
	{
		return cd->maximo();
	}
	float minimoEnDifusor(Variable *var)
	{
		Difusor *dif;
		dif=difusor(var);
		return minimoEnDifusor(dif);
	}
	float minimoEnDifusor(Difusor *dif)
	{
		return dif->minimo();
	}
	float maximoEnDifusor(Variable *var)
	{
		Difusor *dif;
		dif=difusor(var);
		return maximoEnDifusor(dif);
	}
	float maximoEnDifusor(Difusor *dif)
	{
		return dif->maximo();
	}
	float pertenenciaVariable(Variable *var, int numCon, float x)
	{
		ConjuntoDifuso *cd;
		cd=conjuntoEnVariable(var, numCon);
		return pertenenciaVariable(cd,x);
	}
	float pertenenciaVariable(ConjuntoDifuso *cd,float x)
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
	virtual float ToSNorm()=0;
	virtual float opera(float, float)=0;
protected:
};

class T_Norma:public Norma
{
public:
	T_Norma(){}
	~T_Norma(){}
	float ToSNorm()
	{
		return 1.0;
	}
	virtual float opera(float, float)=0;
protected:
};

class S_Norma:public Norma
{
public:
	S_Norma(){}
	~S_Norma(){}
	float ToSNorm()
	{
		return 0.0;
	}
	virtual float opera(float, float)=0;
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
	float opera(float x, float y)
	{
		float z;
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
	float opera(float x, float y)
	{
		float z;
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
	float opera(float x, float y)
	{
		float z;
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
	float opera(float x, float y)
	{
		float z;
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
	FamiliaTp(float parametro)
	{
		p=parametro;
	}
	~FamiliaTp(){}
	float opera(float x, float y)
	{
		float z;
		z=pow(1-x,p)+pow(1-y,p)-pow(1-x,p)*pow(1-y,p);
		z=1-pow(z,(1/p));
		return z;
	}
protected:
	float p;
};

class FamiliaHp:public T_Norma
{
public:
	FamiliaHp()
	{
		p=1;
	}
	FamiliaHp(float parametro)
	{
		p=parametro;
	}
	~FamiliaHp(){}
	float opera(float x, float y)
	{
		float z;
		z=p-(1-p)*(x+y-x*y);
		z=x*y/z;
		return z;
	}
protected:
	float p;
};

class FamiliaFp:public T_Norma
{
public:
	FamiliaFp()
	{
		p=2;
	}
	FamiliaFp(float parametro)
	{
		p=parametro;
	}
	~FamiliaFp(){}
	float opera(float x, float y)
	{
		float z;
		z=1+(pow(p,x)-1)*(pow(p,y)-1)/(p-1);
		z=log(z)/log(p);
		return z;
	}
protected:
	float p;
};

class FamiliaYp:public T_Norma
{
public:
	FamiliaYp()
	{
		p=1;
	}
	FamiliaYp(float parametro)
	{
		p=parametro;
	}
	~FamiliaYp(){}
	float opera(float x, float y)
	{
		float z;
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
	float p;
};

class FamiliaAp:public T_Norma
{
public:
	FamiliaAp()
	{
		p=1;
	}
	FamiliaAp(float parametro)
	{
		p=parametro;
	}
	~FamiliaAp(){}
	float opera(float x, float y)
	{
		float z;
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
	float p;
};



///////////////// S-Normas

class Maximo:public S_Norma
{
public:
	Maximo()
	{
	}
	~Maximo(){}
	float opera(float x, float y)
	{
		float z;
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
	float opera(float x, float y)
	{
		float z;
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
	float opera(float x, float y)
	{
		float z;
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
	FamiliaSp(float parametro)
	{
		p=parametro;
	}
	~FamiliaSp(){}
	float opera(float x, float y)
	{
		float z;
		z=x+y+p*x*y;
		if(z>1)
		{
			z=1;
		}
		return z;
	}
protected:
	float p;
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
	virtual float implica(float,float)=0;
	virtual float defecto()=0;
protected:
};

class ImplicacionT_Norma:public Implicacion
{
public:
	ImplicacionT_Norma(){}
	~ImplicacionT_Norma(){}
	float defecto()
	{
		return 0;
	}
	virtual float implica(float x, float y)=0;
protected:
};

class ImplicacionIf_Then:public Implicacion
{
public:
	ImplicacionIf_Then(){}
	~ImplicacionIf_Then(){}
	float defecto()
	{
		return 1;
	}
	virtual float implica(float x, float y)=0;
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
	float implica(float x, float y)
	{
		float z;
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
	float implica(float x, float y)
	{
		float z;
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
	float implica(float x, float y)
	{
		float rel;
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
	float implica(float x, float y)
	{
		float rel;
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
	float implica(float x, float y)
	{
		float rel;
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
	float implica(float x, float y)
	{
		float rel;
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
	float implica(float x, float y)
	{
		float rel;
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
	float implica(float x, float y)
	{
		float rel;
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
	float implica(float x, float y)
	{
		float rel;
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
		Modificadores=new float[numEntradas];
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
	float modificador(int numVar)
	{
		return Modificadores[numVar];
	}
	void modificador(int numVar,float modif)
	{
		Modificadores[numVar]=modif;
	}
	void certeza(float cer)
	{
		Certeza=cer;
	}
	float certeza()
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
	float *Modificadores;

   float Certeza;
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
	Norma *composicion()
	{
		return Composicion;
	}
	void composicion(Norma *nor)
	{
		delete Composicion;
		Composicion=nor;
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
	void modificador(int numRegla, int numVar, float modif)
	{
		regla(numRegla)->modificador(numVar,modif);
	}
	float modificador(int numRegla, int numVar)
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
	void actualizarEntradas(float *ent);
	float pertenenciaDifusores(float *ent);
	float pertenenciaImplicacion(int numSal,int numRegla, float *ent,float sal);
	float pertenenciaConsecuente(int numSal,int numRegla,float sal);
	float pertenenciaAntecedente(int numRegla,float *ent);
	float pertenenciaComposicion(int numVar, int numRegla,float sal);
	int activarRegla(int numregla);
	void desocuparBaseReglas();
	void EntrenaUniversoFijo(float *antecedente, float *consecuente);
	void EntrenaUniversoVariable(float *antecedente, float *consecuente);
	void llenarRegla(Regla *rg,float *antec, float *consec);
	int compararAntec(Regla *rg1, Regla *rg2);
protected:
	typedef Arreglo<Regla> ListaReglas;

	ListaReglas *BaseReglas;
	Universo *Entradas;
	Universo *Salidas;

	Implicacion *Implicaciones;
	Norma *Composicion;
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
	float defecto()
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
	virtual float salidaConcreta(float *ent)=0;
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
	float salidaConcreta(float *ent);
protected:
};

class UltimoMaximo:public Concresor
{
public:
	UltimoMaximo(MaquinaInferencia *maq, int numVar, Norma *nor):Concresor(maq,numVar,nor)
	{}
	~UltimoMaximo(){}
	float salidaConcreta(float *ent);
protected:
};

class MediaDeMaximos:public Concresor
{
public:
	MediaDeMaximos(MaquinaInferencia *maq, int numVar, Norma *nor):Concresor(maq,numVar,nor)
	{}
	~MediaDeMaximos(){}
	float salidaConcreta(float *ent);
protected:
};

class CentroDeGravedad:public Concresor
{
public:
	CentroDeGravedad(MaquinaInferencia *maq, int numVar, Norma *nor):Concresor(maq,numVar,nor)
	{}
	~CentroDeGravedad(){}
	float salidaConcreta(float *ent);
protected:
};


class Altura:public Concresor
{
public:
	Altura(MaquinaInferencia *maq, int numVar, Norma *nor):Concresor(maq,numVar,nor)
	{}
	~Altura(){}
	float salidaConcreta(float *ent);
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
	float salidaConcreta(int numSal,float *ent)
	{
		Concresor *conc;
		conc=concresor(numSal);
		return conc->salidaConcreta(ent);
	}
	void salidaConcreta(float *ent,float *sal);
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
	char *nombreVariableEntrada(int numVar)
	{
		return entradas->nombreVariable(numVar);
	}
	char *nombreVariableSalida(int numVar)
	{
		return salidas->nombreVariable(numVar);
	}
	void calcular(float *entra,float *sale)
	{
		concreto->salidaConcreta(entra,sale);
	}
	MaquinaInferencia *Motor(){return motor;}
	void EntrenaUniversoFijo(float *antecedente, float *consecuente)
	{
		motor->EntrenaUniversoFijo(antecedente,consecuente);
	}
	void EntrenaUniversoVariable(float *antecedente, float *consecuente)
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
		float valor()
		{
			return Valor;
		}
		void valor(float V)
		{
			Valor=V;
		}

	protected:

	private:
		pin* Contacto;
		float Valor;

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
		void calcular(float* entra, float* sale); // =0 para hacer virtual y heredar de SLD
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
		float valorPinEntrada(int numCapa, int numNodo, int numPin);
		float valorPinSalida(int numCapa, int numNodo, int numPin);
		void valorEntrada(int numNodo, int numPin, float Valor);
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
		void asignarEntradas(float* entra);
		void leerSalidas(float* sale);
		void calcular(float* entra, float* sale);

		void calcularRed();

		ListaCapas* capas()
		{
			return &Capas;
		}

	protected:
	private:

	ListaCapas Capas;
};


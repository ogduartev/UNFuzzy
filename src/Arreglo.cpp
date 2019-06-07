#include "Arreglo.h"
/*
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
}*/

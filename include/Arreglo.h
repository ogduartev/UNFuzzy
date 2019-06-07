#ifndef ARREGLO_H
#define ARREGLO_H

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
	void Add(T* dato)
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
	void AddAt(T* dato,int index)
	{
		//if(index>items){return Add(dato);}
		items++;
		if(items>n)
		{
			T** temp;
			temp=new T*[items];
			n=items;
			int i;
			for(i=0;i<index;i++)
			{
				temp[i]=data[i];
			}
			temp[index]=dato;
			for(i=index+1;i<items;i++)
			{
				temp[i]=data[i-1];
			}
			delete [] data;
			data=temp;
		}else
		{
			int i;
			for(i=items;i>index;i--)
			{
				data[i]=data[i-1];
			}
			data[index]=dato;
		}
	}
	int size(void) const
	{
		return (n);
	}
	int GetItemsInContainer(void) const
	{
	  return (items);
  }
	T *dato(int index)
	{
		if (index <0){index=0;}
		if (index >=n){index=n-1;}
		return (data[index]);
	}

	void Destroy(int index)
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
	void Detach(int index)
	{
		int i;
		for(i=index;i<items;i++)
		{
			data[i]=data[i+1];
		}
		items--;
	}
private:
	int n;
	int items;
	T **data;
	void init(int sz)
	{
		if(sz<1)
		{
			sz=1;
		}
		n=sz;
		items=0;
		data=new T*[n];
	}
};

#endif // ARREGLO_H

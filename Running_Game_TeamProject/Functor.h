#ifndef __Functor_H_
#define __Functor_H_



template <typename T>
void Safe_Delete(T& Obj)
{
	if (nullptr != Obj)
	{
		delete Obj;
		Obj = nullptr;
	}
}


template <typename T>
void Safe_Delete_Arr(T& Obj)
{
	if (nullptr != Obj)
	{
		delete[] Obj;
		Obj = nullptr;
	}
}

template <typename T>
void Safe_Release(T& Obj)
{
	if (nullptr != Obj)
	{
		Obj->Release();
		Obj = nullptr;
	}
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////










#endif // !__Functor_H_

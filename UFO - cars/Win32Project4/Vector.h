#pragma once
//Вектор (он же одномерный массив) — 
//упорядоченный набор элементов с произвольным 
//доступом по числовому индексу. 

template <class T>class Vector{
	T* array;      //Массив наших элементов
	int size;      //Кол-во наших элементов
	int capability;//Сколько элементов мы тут можем хранить (размер массива)
public:
	Vector();
	void push_back(const T& value); //добавляет элемент в конец массива
	T& operator[](int index);
	int getSize();
	void remove(T t);
};


template<class T>
void Vector<T>::remove(T t){
	T *newArray = new T[capability];
	int j = 0;
	for (int i = 0; i < size; i++){
		if (array[i] != t){
			newArray[j] = array[i];
			j++;
		}
	}
	size--;
	delete[] array;
	array = newArray;
}



template<class T>
Vector<T>::Vector()
{
	size = 0;     //массив пока пустой
	capability = 5;//в нем есть место под 5 элементов
	array = new T[5];
}

template<class T>
void Vector<T>::push_back(const T& value)
{
	if (size >= capability){
	//если у нас уже массив забит, что делать?
		capability = capability + 10;
		T *newArray = new T[capability];
		for (int i = 0; i < size; i++)
			newArray[i] = array[i];
		delete[]array;
		array = newArray;
	}
	array[size] = value;
	size++;
}

template<class T> T& Vector<T>::operator[](int index)
{
	return array[index];
}

template<class T>
int Vector<T>::getSize(){
	return size;
}


//перегрузить оператор [ ] 
//который будет принимать int 
// - номер элемета
//возвращать элемент лежащий\
// в векторе по этому номеру


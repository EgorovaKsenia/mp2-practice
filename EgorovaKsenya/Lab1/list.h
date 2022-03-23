﻿#pragma once
using namespace std;
template<typename T>
class Node
{
public:
	T data;		                                                    
	Node* next;                                                        
	Node() { next = nullptr; }							   
	Node(T Data) { data = Data; next = nullptr; }					    
	bool operator< (const Node& z) const { return (data < z.data); }//перегрузка операции меньше
	bool operator> (const Node& z) const { return (data > z.data); }//перегрузка операции больше
};

template<typename T>
class list
{
private:
	Node<T>* head;					
	Node<T>* current;
public:
	void Clean();//очистка списка
	list();//конструктор по умолчанию					
	list(const list<T>& a);//конструктор копировния       	    
	~list();
	list<T>& operator=(const list<T>& a);//перегрузка оператора присваивания   
	//методы
	void Insert(T elem);//вставка элемента в упорядоченный список
	void InsertToTail(T elem);//вставка в конец списка 
	void InsertAfter(Node<T>* N, T Data);//вставка после определенного звена
	//перегрузка операторов сравнения
	bool operator==(const list<T>& sp) const;
	bool operator!=(const list<T>& sp) const { return !(*this == sp); }
	//методы навигации
	void Reset() { currentrent = head->next; }//в начало списка
	void Step() { current = current->next; }//шаг на одно звено вперед
	Node<T>* Getcurrent() const { return current; }//получить текущий элемент
	bool IsNotOver() const { return !(current == head); }//проверка на окончание списка
};


template <typename T>
void list<T>::Clean()
{
	Node<T>* current = head->next;
	while (current != head)
	{
		Node<T>* temp = current->next;
		delete current;
		current = temp;
	}
	head->next = head;
}


template <typename T>
list<T>::list()
{
	head = new Node<T>;
	head->next = head;
	current = head;
}


template <typename T>
list<T>::list(const list<T>& a)
{
	head = new Node<T>;
	Node<T>* A = a.head;
	Node<T>* B = head;
	if (A->next == a.head)
	{
		head->next = head;
		return;
	}
	while (A->next != a.head)
	{
		A = A->next;
		B->next = new Node<T>(A->data);
		B = B->next;
	}
	B->next = head;
	current = head->next;
}



template <typename T>
list<T>::~list()
{
	Clean();
	delete head;
}

template <typename T>
list<T>& list<T>::operator=(const list<T>& a)
{
	Clean();
	Node<T>* A = a.head;
	Node<T>* B = head;
	while (A->next != a.head)
	{
		A = A->next;
		B->next = new Node<T>(A->data);
		B = B->next;
	}
	B->next = head;
	current = head;
	return *this;
}

template <typename T>
void list<T>::Insert(T elem)  //вставка элемента в упорядоченный список
{
	Node<T>* actual = head;
	Node<T>* el = new Node<T>(elem);

	while ((actual->next != head) && (*(actual->next) < *el))
		actual = actual->next;
	Node<T>* actual_2 = actual->next;
	actual->next = el;
	actual->next->next = actual_2;
}

template<typename T>
bool list<T>::operator==(const list<T>& sp) const
{
	bool res = true;
	if (this != &sp)
	{
		Node<T>* a = head->next;
		Node<T>* b = sp.head->next;

		while (a->data == b->data && a != head && b != sp.head)
		{
			a = a->next;
			b = b->next;
		}
		if (a != head || b != sp.head)
			res = false;
	}
	return res;
}

template<typename T>
void list<T> ::InsertToTail(T elem)  //вставка в конец списка 
{
	Reset();
	while (current->next != head)
		Step();
	Node<T>* temp = current->next;
	current->next = new Node<T>(elem);
	current->next->next = temp;
}
template <class T>
void list<T>::InsertAfter(Node<T>* N, T Data)  //вставка после определенного звена
{
	Node<T>* temp = N->next;
	N->next = new Node<T>(Data);
	N->next->next = temp;
}
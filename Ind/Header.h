#pragma once

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

template <typename T>
struct Node
{
	T data;
	Node* next;
	Node* previous;

	Node(T data, Node* next, Node* previous)
	{
		this->data = data;
		this->next = next;
		this->previous = previous;
	}

	friend ostream& operator << (ostream& out, const Node& node)
	{
		out << node.data;
		return out;
	}
};

class Error {};

template <typename T>
class Set
{
private:
	Node<T>* first;
	Node<T>* last;
	Error err;
public:
	Set()
	{
		first = nullptr;
		last = nullptr;
	}

	Set(const Set<T>& set)
	{
		first = last = 0;
		Node<T>* t = set.first;

		while (t)
		{
			*this |= t->data;
			t = t->next;
		}
	}

	~Set()
	{
		while (first)
		{
			Node<T>* current = first;
			first = first->next;
			delete current;
		}

		first = last = 0;
	}

	void add(const T& elem)
	{
		*this |= elem;
	}

	void remove(const T& elem)
	{
		*this /= elem;
	}

	bool isEmpty() const
	{
		return first == nullptr;
	}

	int cardinality() const
	{
		Node<T>* t = first;
		int count = 0;

		while (t)
		{
			count++;
			t = t->next;
		}

		return count;
	}

	bool checkPresence(const T value) const
	{
		Node<T>* t = first;

		while (t)
		{
			if (t->data == value)
				return true;
			t = t->next;
		}

		return false;
	}


	Set<T>& operator = (const Set<T> & set)
	{
		if (this != &set)
		{
			this->~Set<T>();

			Node<T>* t = set.begin;

			while (t)
			{
				*this |= t->data;
				t = t->next;
			}
		}

		return *this;
	}

	Set<T>& operator |= (const T value)
	{
		if (!checkPresence(value))
		{
			if (first)
			{
				Node<T>* t = new Node<T>(value, 0, last);
				last->next = t;
				last = t;
			}
			else
			{
				Node<T>* t = new Node<T>(value, 0, 0);
				first = last = t;
			}
		}

		return *this;
	}

	Set<T>& operator /= (const T value)
	{
		if (!checkPresence(value))
			return *this;

		Node<T>* t1 = first;

		while (t1->data == value)
			t1 = t1->next;

		Node<T> * t2 = t1->previous;
		t2->next = t1->next;
		delete t1;
	}

	Set<T> operator || (const Set<T> & set)
	{
		Set<T> newSet;
		Node<T>* t1 = first;
		Node<T>* t2 = set.first;

		while (t1)
		{
			newSet |= t1->data;
			t1 = t1->next;
		}

		while (t2)
		{
			newSet |= t2->data;
			t2 = t2->next;
		}

		return newSet;
	}

	Set<T> operator && (const Set<T> & set)
	{
		Set<T> newSet;
		Node<T>* t = first;

		while (t)
		{
			if (set.checkPresence(t->data))
				newSet |= t->data;
			t = t->next;
		}

		return newSet;
	}

	bool operator == (const Set<T> other) const
	{
		Node<T>* t = other.first;

		for (int i = 0; t; ++i)
		{
			if (!(*this->checkPresence(t->data)))
				return false;

			t = t->next;
		}

		return true;
	}

	bool operator != (const Set<T> other) const
	{
		return !(*this == other);
	}

	friend istream& operator >> (istream & in, Set<T> & set)
	{
		int number;
		T elem;

		cout << "Number of set >>> ";
		in >> number;

		for (int i = 0; i < number; ++i)
		{
			cout << i + 1 << " elem >>> ";
			in >> elem;

			set |= elem;
		}

		return in;
	}

	friend ostream& operator << (ostream & out, const Set<T> & set)
	{
		Node<T>* t = set.first;

		for (int i = 0; t; ++i)
		{
			out << i + 1 << " >>> " << t->data << endl;
			t = t->next;
		}

		out << endl;

		return out;
	}
};

template <typename T>
void read_file(Set<T> & set, string filename)
{
	T c;

	ifstream file(filename);

	if (!file.is_open())
		cerr << "Error!";

	while (file)
	{
		file >> c;
		set |= c;
	}
}
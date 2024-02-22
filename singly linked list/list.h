#pragma once
#include <iostream>
template<typename>
class Iterator;
template <typename T>
class list
{
private:
	template <typename T>
	struct node
	{
		node() { data = 0; next = nullptr; };
		node(T data_) :data(data_), next(nullptr) {}
		node(T data_, node<T>* next_) :data(data_), next(next_) {}
		T data;
		node<T>* next = nullptr;
	};
	node<T>* head = nullptr;
	node<T>* tail = nullptr;
public:
	list() : head(nullptr), tail(nullptr) {}
	explicit list(size_t Count)
	{
		if (Count < 1)
			return;
		else
		{
			for (int i = 0; i != Count; ++i)
			{
				node<T>* tmp = new node<T>(0);
				if (head == nullptr)
				{
					head = tmp;
					tail = tmp;
					tmp = nullptr;
				}
				else
				{
					tail->next = tmp;
					tail = tmp;
					tmp = nullptr;
				}
			}
		}

	}
	list(size_t Count, const T& Val)
	{
		if (Count < 1)
			return;
		else
		{
			for (int i = 0; i != Count; ++i)
			{
				node<T>* tmp = new node<T>(Val);
				if (head == nullptr)
				{
					head = tmp;
					tail = tmp;
					tmp = nullptr;
				}
				else
				{
					tail->next = tmp;
					tail = tmp;
					tmp = nullptr;
				}
			}
		}
	}
	~list() 
	{
		clear(); 
	}
	list(const list& Right)
	{	
		node<T>* tmp = Right.head;
		while (tmp)
		{
			node<T>* curr = new node<T>(tmp->data);
			if (head == nullptr)
			{
				head = curr;
				tail = curr;
				tmp = tmp->next;
				curr = nullptr;
			}
			else
			{
				tail->next = curr;
				tail = curr;
				tmp = tmp->next;
				curr = nullptr;
			}
		}
	}
	list& operator=(const list& right)
	{
		if (this == &right) return *this;
		if (head != nullptr)
		{
			clear();
		}
		node<T>* tmp = right.head;
		while (tmp)
		{
			node<T>* curr = new node<T>(tmp->data);
			if (head == nullptr)
			{
				head = curr;
				tail = curr;
				tmp = tmp->next;
				curr = nullptr;
			}
			else
			{
				tail->next = curr;
				tail = curr;
				tmp = tmp->next;
				curr = nullptr;
			}
		}
			return *this;
	}
	list(list&& Right) noexcept
	{
		head = Right.head;
		tail = Right.tail;
		Right.head = nullptr;
		Right.tail = nullptr;
	}
	list& operator=(list&& right) noexcept
	{
		if (&right == this)
			return *this;
		clear();
		head = right.head;
		tail = right.tail;
		right.head = nullptr;
		right.tail = nullptr;
		return *this;
	}
	void swap(list<T>& right)
	{
		node<T>* tmp = head;
		head = right.head;
		right.head = tmp;
		node<T>* tmp1 = tail;
		tail = right.tail;
		right.tail= tmp;
	}
	Iterator<T> begin() const { return Iterator<T>(head); }
	void clear()
	{
			node<T>* index = head;
			node<T>* tmp = nullptr;
			while (index)
			{
				tmp = index;
				index = index->next;
				delete tmp;
			}
	}
	bool empty() const { return head; }
	Iterator<T> end() { return Iterator<T>(tail->next); }
	Iterator<T> erase(Iterator<T> Where)
	{
		if (head == nullptr)
		{
			return nullptr;
		}
		if (Where.get_curr() == head)
			pop_front();
		else if (Where.get_curr() == tail->next)
			pop_back();
		else
		{
			node<T>* curr = head;
			node<T>* prev = nullptr;
			while (curr != Where.get_curr())
			{
				prev = curr;
				curr = curr->next;
			}
			prev->next = curr->next;
			curr = nullptr;
			return prev;
		}
	}
	Iterator<T> insert(Iterator<T> Where, const T& Val)
	{
		if (head == nullptr)
		{
			node<T>* tmp = new node<T>;
			tmp->data = Val;
			tmp->next = nullptr;
			head = tmp;
			tail = tmp;
			tmp = nullptr;
		}
		else
		{
			if (Where.get_curr() == head)
			{
				push_front(Val);
			}
			else if (Where.get_curr() == tail->next)
			{
				push_back(Val);
			}
			else
			{
				node<T>* curr = head;
				while (curr != Where.get_curr())
				{
					curr = curr->next;
				}
				node<T>* tmp = new node<T>(Val, curr);
				head->next = tmp;
				tmp = nullptr;
				return curr;
			}
		}
	}
	void pop_back()
	{
		if (head == nullptr)
		{
			head = nullptr;
			tail = nullptr;
		}
		else
		{
			node<T>* curr = head;
			while (curr->next != tail)
			{
				curr = curr->next;
			}
			tail = nullptr;
			tail = curr;
			tail->next = nullptr;
		}
	}
	void pop_front()
	{
		if (head == nullptr)
		{
			head = nullptr;
			tail = nullptr;
		}
		else
		{
			node<T>* forward = head;
			head = head->next;
			forward = nullptr;
		}
	}
	void push_back(const T& val)
	{
		node<T>* tmp = new node<T>(val);
		if (head == nullptr)
		{
			head = tmp;
			tail = tmp;
			tmp = nullptr;
		}
		else
		{
			tail->next = tmp;
			tail = tmp;
			tmp = nullptr;
		}
	}
	void push_front(const T& val)
	{
		if (head == nullptr)
		{
			node<T>* tmp = new node<T>(val);
			head = tmp;
			tail = tmp;
			tmp = nullptr;
		}
		else
		{
			node<T>* tmp = new node<T>(val,head);
			head = tmp;
			tmp = nullptr;
		}
	}
	void remove(const T& val)
	{
		if (!head)
			return;
		node<T>* index = head;
		while (index)
		{
			if (index->data == val)
				erase(index);
			index = index->next;
		}
	}
	void resize(size_t _Newsize)
	{
		if (_Newsize < 1)
			return;
		if (!head)
		{
			for (int i = 0; i != _Newsize; ++i)
			{
				node<T>* tmp = new node<T>(0);
				if (head == nullptr)
				{
					head = tmp;
					tail = tmp;
					tmp = nullptr;
				}
				else
				{
					tail->next = tmp;
					tail = tmp;
					tmp = nullptr;
				}
			}
		}
		else
		{
			if (_Newsize > size())
			{
				int lenght = size();
				for (int i = 0; i != _Newsize - lenght; ++i)
				{
					push_back(0);
				}
			}
			else if (_Newsize < size())
			{
				int lenght = size();
				for (int i = 0; i != lenght - _Newsize; ++i)
				{
					pop_back();
				}
			}
			else
				return;
		}
	}
	void reverse()
	{
		node<T>* prev = nullptr;
		tail = head;
		while (head != nullptr)
		{
			node<T>* forward = head->next;
				head->next = prev;
				prev = head;
				head = forward;
		}
		head = prev;
	}
	size_t size() const
	{
		size_t count = 0;
		node<T>* curr = head;
		while (curr!= nullptr)
		{
			++count;
			curr = curr->next;
		}
		return count;
	}
	void print()
	{
		node<T>* temp = new node<T>;
		temp = head;
		while (temp != nullptr)
		{
			std::cout << temp->data << " ";
			temp = temp->next;
		}
		std::cout << '\n';
	}
	friend class Iterator<T>;
};
template<typename T>
class Iterator
{
private:
	list<T>::node<T>* curr;
public:
	Iterator() { curr = nullptr; }
	Iterator(list<T>::node<T>* rhs) { curr = rhs; }
	list<T>::node<T>* get_curr() { return curr; }
	int& operator *() const { return curr->data; }
	Iterator operator++ (int) { curr = curr->next; return *this; }
	bool operator!=(const Iterator& rhs) { return curr != rhs.curr; }
	Iterator& operator=(const Iterator& rhs) { curr = rhs.curr; return *this; }
	friend class list<T>;
};
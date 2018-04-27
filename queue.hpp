#pragma once
#include <iostream>
using namespace std;
template <typename T>
struct Forwardlist {
	T data;
	Forwardlist<int>* next;
};
template <typename T>
class Queue {
	Forwardlist<int>* first;
	Forwardlist<int>* last;
public:
	Queue()
	{
		first = nullptr;
		last = nullptr;
	}
	Queue(std::initializer_list<T> list)
	{
		for (auto& item : list)
		{
			this->push(item);
		}
	}
	Queue(const Queue& base_q)
	{
		Forwardlist<int>* pntr = base_q.first;
		while (pntr != nullptr)
		{
			this->push(pntr->data);
			pntr = pntr->next;
		}
	}
	auto swap(Queue& base_q) -> void
	{
		Forwardlist<int>* cpfirst = first;
		Forwardlist<int>* cplast = last;
		first = base_q.first;
		last = base_q.last;
		base_q.first = cpfirst;
		base_q.last = cplast;
	}

	auto operator=(const Queue& base_q)->Queue&
	{
		while (first != nullptr)
		{
			Forwardlist<int>* pntr = first;
			first = first->next;
			delete pntr;
		}
		Forwardlist<int>* pntr = base_q.first;
		while (pntr != nullptr)
		{
			this->push(pntr->data);
			pntr = pntr->next;
		}
	}

	auto empty() const -> bool
	{
		if (first != nullptr)
			return false;
		else
			return true;
	}

	auto size() const -> size_t
	{
		size_t q_size = 0;
		if (empty())
			return q_size;
		q_size++;
		Forwardlist<int>* pntr = first;
		while (pntr != last)
		{
			q_size++;
			pntr = pntr->next;
		}
		return q_size;
	}

	auto push(T val) -> void
	{
		if (empty())
		{
			first = new Forwardlist<int>{ val, nullptr };
			last = first;
		}
		else
		{
			Forwardlist<int>* pntr = last;
			last = new Forwardlist<int>{ val, nullptr };
			pntr->next = last;
		}

	}

	auto pop() -> void
	{
		if (empty())
		{
			std::cout << "queue is empty";
			return;
		}
		else
		{
			Forwardlist<int>* pntr = first;
			first = first->next;
			delete pntr;
		}
	}

	auto front()->T&
	{
		if (first != nullptr)
			return first->data;
		else
		{
			first = new Forwardlist<int>{ 0, nullptr };
			last = first;
			return first->data;
		}
	}


	auto back() ->T&
	{
		if (first != nullptr)
			return last->data;
		else
		{
			first = new Forwardlist<int>{ 0, nullptr };
			last = first;
			return first->data;
		}
	}

	bool operator==(const Queue& scnd_q)
	{
		if (this->size() == scnd_q.size())
		{
			Forwardlist<int>* pntr1 = this->first;
			Forwardlist<int>* pntr2 = scnd_q.first;
			while (pntr1 != nullptr)
			{
				if (pntr1->data != pntr2->data)
					return false;
				else
				{
					pntr1 = pntr1->next;
					pntr2 = pntr2->next;
				}
			}
			return true;
		}
		else
			return false;
	}


	friend
		auto operator>>(std::istream & input, Queue<T>& base_q) -> std::istream &
	{
		T entering_val;
		input >> entering_val;
		base_q.push(entering_val);
		return input;
	}

	friend
		auto operator<<(std::ostream & output, Queue<T>& base_q) -> std::ostream &
	{
		Forwardlist<int> *pntr = base_q.first;
		while (pntr != nullptr)
		{
			output << pntr->data << " ";
			pntr = pntr->next;
		}
		return output;
	}

	~Queue()
	{
		while (first != nullptr)
		{
			Forwardlist<int>* pntr = first;
			first = first->next;
			delete pntr;
		}
	}


};
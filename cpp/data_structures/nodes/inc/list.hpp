#pragma once
#include <node.hpp>
#include <cstdlib>
#include <optional>

#include <iostream>

template<typename T>
class LList {
public:
	LList(const T &t)
	: _size{1} {
		tail = head = new DataNode<T>(t);
	}

	LList()
	: head{},tail{},_size{} {

	}

	~LList() {
		while(head != nullptr)
		{
			DataNode<T> *temp= head;
			head = head->next;
			delete(temp);
		}
		tail=head;
		_size=0;
	}


	size_t size() {
		return _size;
	}

	void add_head(T t) {
		if(head == nullptr)
		{
			tail = head = new DataNode<T>(t);
		} else {
			head = new DataNode<T>(t,head);
		}
		_size++;
	}

	void add_tail(T t) {
		if(head == nullptr)
		{
			tail = head = new DataNode<T>(t);
		} else {
			tail = tail->next = new DataNode<T>(t);
		}
		_size++;
	}

	inline bool empty()
	{
		if(head == nullptr)
			return true;
		else
			return false;
	}

	std::optional<T> get_head() {
		if(empty())
			return std::nullopt;
		else
			return std::optional<T> {head->data};
	}

	std::optional<T> get_tail() {
		if(empty())
			return std::nullopt;
		else
			return std::optional<T> {tail->data};
	}


	std::optional<T> delete_head() {
		DataNode<T> *temp = head;
		std::optional<T> head_val {};
		//Head == nullptr, the list is empty
		if(head != nullptr)
		{
			head = head->next;
			head_val = temp->data;
			delete(temp);
			_size--;
		}
		if(head == nullptr)
		{
			tail = head;
		}
		return head_val;
	}

	std::optional<T> delete_tail() {
		DataNode<T> *temp = head;
		std::optional<T> tail_val {};
		if(head != nullptr)
		{
			//Only one element in the list
			if(head->next == nullptr)
			{
				tail_val = temp->data;
				delete(temp);
				tail = head = nullptr;
			}
			else
			{
				//Move temp to a postiion before tail
				while(temp->next != tail)
				{
					temp=temp->next;
				}
				temp->next=nullptr;
				tail_val = tail->data;
				delete(tail);
				tail=temp;
				
			}
			_size--;
		}
		return tail_val;
	}

	void print() {
		std::cout<<"Printing the list"<<std::endl;
		for(DataNode<T> *itr = head; itr != nullptr; itr=itr->next)
		{
			std::cout<< itr->data << ",";
		}

		std::cout<<std::endl;
	}

	// std::optional<T> delete_node(size_t node_idx)
	// {

	// }


private:
	DataNode<T> *head;
	DataNode<T> *tail;
	size_t _size;

};


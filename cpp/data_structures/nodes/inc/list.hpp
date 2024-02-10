#pragma once
#include <node.hpp>
#include <cstdlib>
#include <optional>

#include <iostream>

template<typename T>
class Linked_list {
public:
	Linked_list(const T &t)
	: m_size{1} {
		p_tail = p_head = new DataNode<T>(t);
	}

	Linked_list()
	: p_head{},p_tail{},m_size{} {

	}

	~Linked_list() {
		while(p_head != nullptr)
		{
			DataNode<T> *temp= p_head;
			p_head = p_head->next;
			delete(temp);
		}
		p_tail = p_head;
		m_size = 0;
	}


	size_t size() {
		return m_size;
	}

	void add_head(T t) {
		if(p_head == nullptr)
		{
			p_tail = p_head = new DataNode<T>(t);
		} else {
			p_head = new DataNode<T>(t,p_head);
		}
		m_size++;
	}

	void add_tail(T t) {
		if(p_head == nullptr)
		{
			p_tail = p_head = new DataNode<T>(t);
		} else {
			p_tail = p_tail->next = new DataNode<T>(t);
		}
		m_size++;
	}

	inline bool empty()
	{
		if(p_head == nullptr)
			return true;
		else
			return false;
	}

	std::optional<T> get_head() {
		if(empty())
			return std::nullopt;
		else
			return std::optional<T> {p_head->data};
	}

	std::optional<T> get_tail() {
		if(empty())
			return std::nullopt;
		else
			return std::optional<T> {p_tail->data};
	}


	std::optional<T> delete_head() {
		DataNode<T> *temp = p_head;
		std::optional<T> head_val {};
		//Head == nullptr, the list is empty
		if(p_head != nullptr)
		{
			p_head = p_head->next;
			head_val = temp->data;
			delete(temp);
			m_size--;
		}
		if(p_head == nullptr)
		{
			p_tail = p_head;
		}
		return head_val;
	}

	std::optional<T> delete_tail() {
		DataNode<T> *temp = p_head;
		std::optional<T> tail_val {};
		if(p_head != nullptr)
		{
			//Only one element in the list
			if(p_head->next == nullptr)
			{
				tail_val = temp->data;
				delete(temp);
				p_tail = p_head = nullptr;
			}
			else
			{
				//Move temp to a postiion before tail
				while(temp->next != p_tail)
				{
					temp=temp->next;
				}
				temp->next=nullptr;
				tail_val = p_tail->data;
				delete(p_tail);
				p_tail=temp;
				
			}
			m_size--;
		}
		return tail_val;
	}

	void print() {
		std::cout<<"Printing the list"<<std::endl;
		for(DataNode<T> *itr = p_head; itr != nullptr; itr=itr->next)
		{
			std::cout<< itr->data << ",";
		}

		std::cout<<std::endl;
	}

	// std::optional<T> delete_node(size_t node_idx)
	// {

	// }


private:
	DataNode<T> *p_head;
	DataNode<T> *p_tail;
	size_t m_size;

};


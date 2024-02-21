#pragma once
#include <node.hpp>
#include <cstdlib>
#include <optional>

#include <iostream>


template<typename T>
class Linked_list {
public:
	Linked_list(const T &t)
	: m_size{1}
	{
		p_tail = p_head = new Data_node<T>(t);
	}

	Linked_list()
	: p_head{},p_tail{},m_size{}
	{
	}

	~Linked_list() {
		delete_nodes();
	}

	Linked_list(const Linked_list<T> &r_other_linked_list)
	: p_head{},p_tail{},m_size{}
	{
		auto temp_node =  r_other_linked_list.get_head_node();
		while(temp_node != nullptr)
		{
				add_tail(temp_node->data);
				temp_node = temp_node->next;
		}
	}

	Linked_list<T> & operator=(const Linked_list<T> &r_other_linked_list)
	{
		if(this != &r_other_linked_list)
		{
			//We need to delete the elements in the current list
			delete_nodes();
			auto temp_node =  r_other_linked_list.get_head_node();
			while(temp_node != nullptr)
			{
					add_tail(temp_node->data);
					temp_node = temp_node->next;
			}
		}
		return *this;
	}

	size_t size() {
		return m_size;
	}

	void add_head(T t) {
		if(p_head == nullptr)
		{
			p_tail = p_head = new Data_node<T>(t);
		} else {
			p_head = new Data_node<T>(t,p_head);
		}
		m_size++;
	}

	void add_tail(T t) {
		if(p_head == nullptr)
		{
			p_tail = p_head = new Data_node<T>(t);
		} else {
			p_tail = p_tail->next = new Data_node<T>(t);
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

	std::optional<T> get_head()
	{
		if(empty())
			return std::nullopt;
		else
			return std::optional<T> {p_head->data};
	}

	std::optional<T> get_tail()
	{
		if(empty())
			return std::nullopt;
		else
			return std::optional<T> {p_tail->data};
	}

	bool delete_node(T item)
	{
		//Initialize the temp pointer to the head
		auto p_temp_node = p_head;
		//We assume the data is not int the list
		bool found = false;
		//If the data is nullptr we don't do anything
		if(p_temp_node)
		{
			//Check if the data is in the head
			if(p_temp_node->data == item)
			{
				//Is in the head
				p_head=p_head->next;
				delete(p_temp_node);
				m_size--;
				found = true;
				//If p_head is nullptr, this means the list is empty so we need
				//to adjust the head
				if(p_head == nullptr)
				{
					p_tail = p_head;
				}
			}
			else
			{
				//Set previews the the head
				auto p_prev_node = p_temp_node;
				//set the next ptr to the element after the head since the head
				//case was covered before
				p_temp_node= p_temp_node->next;
				while(p_temp_node != nullptr)
				{
					//If the temp pointer has the data, link the previous node
					//to the current next node and delete the current node
					if(p_temp_node->data == item)
					{
						p_prev_node->next=p_temp_node->next;
						delete(p_temp_node);
						m_size--;
						found = true;
						break;
					}
					//Update previous node to the current node
					p_prev_node = p_temp_node;
					//Move the current node to the next
					p_temp_node= p_temp_node->next;
				}
				if(p_head->next == nullptr)
				{
					p_tail = p_head;
				}
			}

		}
		return found;
	}

	bool is_in_list(T item)
	{
		bool found = false;
		for(auto note_ptr = p_head;
			note_ptr != nullptr;
			note_ptr = note_ptr->next)
		{
			if(note_ptr->data == item)
			{
				found = true;
				break;
			}
		}
		return found;
	}


	std::optional<T> delete_head() {
		Data_node<T> *temp = p_head;
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
		Data_node<T> *temp = p_head;
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

	Data_node<T> *get_head_node() const
	{
		return static_cast<Data_node<T> * const>(p_head);
	}

	Data_node<T> *get_tail_node() const
	{
		return static_cast<Data_node<T> * const>(p_tail);
	}

	void print() const
	{
		std::cout<<"Printing the list"<<std::endl;
		for(Data_node<T> *itr = p_head; itr != nullptr; itr=itr->next)
		{
			std::cout<< itr->data << ",";
		}

		std::cout<<std::endl;
	}

private:
	Data_node<T> *p_head;
	Data_node<T> *p_tail;
	size_t m_size;

	void delete_nodes()
	{
		while(p_head != nullptr)
		{
			Data_node<T> *temp= p_head;
			p_head = p_head->next;
			delete(temp);
		}
		p_tail = p_head;
		m_size = 0;
	}

};


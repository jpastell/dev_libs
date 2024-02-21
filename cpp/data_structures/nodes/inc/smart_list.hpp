#pragma once

#include <smart_node.hpp>
#include <iostream>
#include <optional>

static constexpr bool using_make_shared = true;

template<typename T>
using node = Smart_data_node<T>;

template<typename T>
using node_ptr = std::shared_ptr<node<T>>;


template <typename T>
class Smart_linked_list
{
public:
	Smart_linked_list():m_head_ptr{},m_tail_ptr{},m_size{}{}

	Smart_linked_list(const T &t)
	: m_head_ptr{},m_tail_ptr{},m_size{1}
	{
		if(using_make_shared)
		{
			m_tail_ptr = m_head_ptr = 
				std::make_shared<node<T>>(node<T>(t,nullptr));
		} else {
			m_tail_ptr = m_head_ptr = node_ptr<T>{new node<T>(t,nullptr)};
		}
	}

	~Smart_linked_list()
	{
		delete_nodes();
	}

	Smart_linked_list(const Smart_linked_list<T> &other)
	:m_head_ptr{},m_tail_ptr{},m_size{1}
	{
		//Add other elements
		add_from_other(other);
	}

	Smart_linked_list<T> & operator=(const Smart_linked_list<T> &other)
	{
		if(this != &other)
		{
			//Delete the current list
			delete_nodes();
			//Add other elements
			add_from_other(other);
		}
		return *this;
	}

	void add_head(T t)
	{
		//m_head_ptr will be nullptr at the begining so this case will work
		//for empty and non empty cases
		m_head_ptr = node_ptr<T>{new node<T>(t,m_head_ptr)};
		m_size++;
		//If the list was not initilized tail will be nullptr
		if(m_tail_ptr == nullptr)
		{
			m_tail_ptr=m_head_ptr;
		}
	}

	void add_tail(T t)
	{
		//Empty case
		if(m_tail_ptr == nullptr)
		{
			m_head_ptr = m_tail_ptr = node_ptr<T>{new node<T>(t,nullptr)};
		} else {
			m_tail_ptr = m_tail_ptr->next = node_ptr<T>{new node<T>(t,nullptr)};
		}
		m_size++;
	}

	std::optional<T> get_head()
	{
		if(m_head_ptr == nullptr)
		{
			return std::nullopt;
		}
		else
		{
			return std::optional<T>{m_head_ptr->value};
		}
	}

	std::optional<T> get_tail()
	{
		if(m_tail_ptr == nullptr)
		{
			return std::nullopt;
		}
		else
		{
			return std::optional<T>{m_tail_ptr->value};
		}
	}

	bool delete_node(T t)
	{
		bool found = false;
		if(m_head_ptr != nullptr)
		{
			// 1 Element in the list
			if(m_head_ptr == m_tail_ptr)
			{
				if(m_head_ptr->value == t)
				{
					m_size = 0;
					m_head_ptr = m_tail_ptr = nullptr;
				}
			} else {
				//More than one element
				//
				//Element in the head
				if(m_head_ptr->value == t)
				{
					m_head_ptr = m_head_ptr->next;
					m_size--;
					found = true;
				}
				else
				{
					node_ptr<T> last_ptr = m_head_ptr;
					//More than 1 elemnt in the list
					for(node_ptr<T> itr_ptr = m_head_ptr->next;
						itr_ptr != nullptr;
						itr_ptr= itr_ptr->next)
					{
						if(itr_ptr->value == t)
						{
							last_ptr->next = itr_ptr->next;
							itr_ptr = nullptr;
							m_size--;
							found = true;
							break;
						}
						last_ptr = itr_ptr;
					}
					if(m_head_ptr->next == nullptr)
					{
						m_tail_ptr = m_head_ptr;
					}
				}
			}
		}
		return found;
	}

	bool is_in_list(T t)
	{
		bool found = false;
		for(node_ptr<T> itr_ptr = m_head_ptr;
			itr_ptr != nullptr;
			itr_ptr= itr_ptr->next)
		{
			if(itr_ptr->value == t)
			{
				found = true;
				break;
			}
		}
		return found;
	}

	void print()
	{
		for(node_ptr<T> itr_ptr = m_head_ptr;
			itr_ptr !=nullptr;
			itr_ptr= itr_ptr->next)
		{
			std::cout << itr_ptr->value;
		}
		std::cout<<std::endl;
	}

	void delete_head()
	{
		//Empty
		if(m_head_ptr != nullptr)
		{
			m_head_ptr = m_head_ptr->next;
			m_size--;
			if(m_head_ptr == nullptr)
			{
				m_tail_ptr=m_head_ptr;
			}
		}
	}

	void delete_tail()
	{
		if(m_head_ptr != nullptr)
		{
			if(m_head_ptr->next == nullptr)
			{
				//One element in the list
				m_tail_ptr = m_head_ptr = nullptr;
			}
			else
			{
				//2 or more elements in the list
				node_ptr<T> itr_ptr = m_head_ptr;
				while(itr_ptr->next != m_tail_ptr)
				{
					itr_ptr = itr_ptr->next;
				}
				itr_ptr->next = nullptr;
				m_tail_ptr =  itr_ptr;
			}
			m_size--;
		}
	}

	bool is_empty()
	{
		if(m_head_ptr == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	node_ptr<T> get_head_node() const
	{
		return m_head_ptr;
	}

private:
	node_ptr<T>m_head_ptr;
	node_ptr<T>m_tail_ptr;
	std::size_t m_size;

	void delete_nodes()
	{
		while(m_head_ptr != nullptr)
		{
			m_head_ptr=m_head_ptr->next;
		}
		m_tail_ptr = nullptr;
		m_size = 0;
	}

	void add_from_other(const Smart_linked_list<T> &other)
	{
		//Add other elements
		node_ptr<T> temp_itr = other.get_head_node();
		while(temp_itr != nullptr)
		{
			add_to_tail(temp_itr->value);
			temp_itr=temp_itr->next;
		}
	}
};
#pragma once

#include <memory>
#include <iostream>


template<typename T>
struct Smart_data_node {

	Smart_data_node(const T &t, std::shared_ptr<Smart_data_node<T>> next_ptr)
	:	value{t},
		next{next_ptr}

	{
		next =next_ptr;
	}

	~Smart_data_node()
	{
		std::cout<<"Deliting: " << value << std::endl;
	}

	T value;
	std::shared_ptr<Smart_data_node<T>> next;
};


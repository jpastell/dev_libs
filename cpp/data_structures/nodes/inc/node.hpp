#pragma once

#include <iostream>

template<typename T>
struct Data_node {
	Data_node(const T &t, Data_node *next_ptr = nullptr)
	:	data{t} ,
		next {next_ptr}
	{

	}

	T data;
	Data_node *next;
};


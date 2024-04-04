#pragma once
#include <optional>
#include <iostream>


template <typename T, std::size_t S>
class Circular_buffer {
public:

	Circular_buffer()
	: mem{}, size{}, begin{},end{}
	{

	}

	bool enqueue(T data)
	{
		bool valid_enqueue = true;
		if(begin == nullptr )
		{
			//Empty add to the next element
			end = begin = &mem[0];
			update_and_increase_end(data);
			size = 1;
		}
		else
		{
			if(begin == end)
			{
				//We are full
				valid_enqueue = false;
			}
			else
			{
				update_and_increase_end(data);
				size++;
			}
		}
		return valid_enqueue;
	}

	std::optional<T> dequeue()
	{
		std::optional<T> valid_dequeue = std::nullopt;
		//Empty circular buffer
		if(begin != nullptr)
		{
			T *next_ptr = begin;
			increase_pointer(next_ptr);
			if(next_ptr == end)
			{
				//This means we only have 1 item to get rid off in the
				//queue
				valid_dequeue = *begin;
				end = begin = nullptr;
				size = 0;
			} else {
				valid_dequeue = *begin;
				increase_pointer(begin);
				size--;
			}
		}
		return valid_dequeue;
	}

	std::size_t  get_size()
	{
		return size;
	}

	void print()
	{
		std::cout << "Printing the buffer" <<std::endl;
		T * data_ptr = begin;
		for(std::size_t  idx = 1; idx <= size; idx ++)
		{
			std::cout << *data_ptr << ",";
			increase_pointer(data_ptr);
		}
		std::cout << std::endl;
	}

	void print_array()
	{
		std::cout << "Printing the array" <<std::endl;
		for(std::size_t i = 0; i <= (S-1); i++)
		{
			std::cout << mem[i] << ",";
		}
		std::cout << std::endl;
	}


private:

	void update_and_increase_end( T data)
	{
		*end = data;
		increase_pointer(end);

	}

	void increase_pointer(T * &ptr)
	{
		if(ptr == &mem[S-1])
		{
			ptr = &mem[0];
		}
		else
		{
			ptr++;
		}
	}
	
	std::size_t size;
	T mem[S];
	T *begin;
	T *end;
};




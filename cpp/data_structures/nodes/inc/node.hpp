#pragma once

template<typename T>
struct DataNode {
	DataNode(const T &t, DataNode *next_ptr = nullptr)
	:	data{t} ,
		next {next_ptr}
	{

	}

	T data;
	DataNode *next;
};


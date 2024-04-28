#pragma once

#include <memory>

struct Edge_node
{
	unsigned int adjacent;
	unsigned int weight;
	std::shared_ptr<Edge_node> next;

	Edge_node(unsigned int adjacent, unsigned int weight, std::shared_ptr<Edge_node> next)
	: adjacent{adjacent},weight{weight},next{next}
	{

	}
};